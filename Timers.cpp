#include <bangtal>
#include "Timers.h"
#include "PlatformFuncs.h"
#include "Arrow.h"
#include "ScoreBoards.h"
using namespace bangtal;

extern PlatformPtr platforms[13];
extern ScenePtr scene;
extern ArrowPtr arrow;
extern RestartButtonPtr reStartButton;
extern ChangeDirectionButtonPtr changeButton;
extern MakePlatformTimerPtr platformTimer;
extern SpeedupTimerPtr speedupTimer;
extern ScoreBoardPtr clickNumScore;
extern SurviveBoardPtr surviveTimeScore;
extern HighscoreBoardPtr highscore;
extern SpeedMeterPtr speedMeter;

const float TIMER_CONST::INIT_SPEED				= 1.0f;
const float TIMER_CONST::INIT_SPEED_UPDATE_TIME	= 2.0f;
const int	TIMER_CONST::NUM_OF_UPDATE			= 45;
const float TIMER_CONST::UPDATE_SIZE			= 0.02f;


/********************** �÷����� �������ִ� Ÿ�̸� **********************/
MakePlatformTimerPtr MakePlatformTimer::create(const Second& second)
{
	auto timer = MakePlatformTimerPtr(new MakePlatformTimer(second));
	Timer::add(timer);
	return timer;
}

MakePlatformTimer::MakePlatformTimer(const Second& second) : Timer(second), speed(second)
{
	onTimerCallback = [&](TimerPtr t)->bool {
		movingPlatform();

		if (arrow->getDirection() == DIRECTION::LEFT) {
			arrow->setX(arrow->getX() + PLAT_CONST::LEFT_DX);
		}
		else {
			arrow->setX(arrow->getX() + PLAT_CONST::RIGHT_DX);
		}
		arrow->locate(scene, arrow->getX(), arrow->getY());

		if (!arrow->isOnPlatform(platforms[0])) {
			int total_score = clickNumScore->getScore() * surviveTimeScore->getScore();
			string str;

			if (total_score > highscore->getScore()) {
				str += "�ű�� ����!";
				highscore->setScore(total_score);
				highscore->showScore();
				highscore->writeScore(total_score);
			}
			else {
				str += "���ӿ���!";
			}

			str += "\n�� ����: " + to_string(total_score);
			showMessage(str);

			changeButton->hide();
			reStartButton->show();
			speedupTimer->stop();
			surviveTimeScore->timerStop();
		}
		else {
			t->set(speed);
			t->start();
		}
		return true;
	};
}
/*************************************************************************/

/********************** ���� ���ǵ带 �÷��ִ� Ÿ�̸� **********************/
SpeedupTimerPtr SpeedupTimer::create(const Second& second)
{
	auto timer = SpeedupTimerPtr(new SpeedupTimer(second));
	Timer::add(timer);
	return timer;
}

SpeedupTimer::SpeedupTimer(const Second& second) : Timer(second), iterNum(0)
{
	onTimerCallback = [&](TimerPtr t)->bool {
		platformTimer->speed -= TIMER_CONST::UPDATE_SIZE;
		iterNum++;

		speedMeter->setScore(speedMeter->getScore() + 1);
		speedMeter->showScore();

		if (iterNum < TIMER_CONST::NUM_OF_UPDATE) {
			t->set(second);
			t->start();
		}
		return true;
	};
}

void SpeedupTimer::setIterNumZero()
{
	iterNum = 0;
	platformTimer->speed = TIMER_CONST::INIT_SPEED;
}
/*************************************************************************/