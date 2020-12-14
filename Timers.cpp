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

const float TIMER_CONST::INIT_SPEED				= 0.8f;
const float TIMER_CONST::INIT_SPEED_UPDATE_TIME	= 2.0f;
const float TIMER_CONST::UPDATE_SIZE			= 0.02f;


/********************** 플랫폼을 생성해주는 타이머 **********************/
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
				str += "신기록 갱신!";
				highscore->setScore(total_score);
				highscore->showScore();
				highscore->writeScore(total_score);
			}
			else {
				str += "게임오버!";
			}

			str += "\n총 점수: " + to_string(total_score);
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

/********************** 점점 스피드를 올려주는 타이머 **********************/
SpeedupTimerPtr SpeedupTimer::create(const Second& second)
{
	auto timer = SpeedupTimerPtr(new SpeedupTimer(second));
	Timer::add(timer);
	return timer;
}

SpeedupTimer::SpeedupTimer(const Second& second) : Timer(second)
{
	onTimerCallback = [&](TimerPtr t)->bool {
		if (platformTimer->speed > 0.6f) {
			platformTimer->speed -= TIMER_CONST::UPDATE_SIZE * 2;
		}
		else if (platformTimer->speed > 0.4f) {
			platformTimer->speed -= TIMER_CONST::UPDATE_SIZE;
		}
		else if (platformTimer->speed > 0.2f) {
			platformTimer->speed -= TIMER_CONST::UPDATE_SIZE / 2;
		}
		else if (platformTimer->speed > 0.1f) {
			platformTimer->speed -= TIMER_CONST::UPDATE_SIZE / 4;
		}

		speedMeter->setScore(speedMeter->getScore() + 1);
		speedMeter->showScore();

		if (platformTimer->speed > 0.4f) {
			t->set(second / 2);
			t->start();
		}
		else if (platformTimer->speed > 0.2f) {
			t->set(second);
			t->start();
		}
		else if (platformTimer->speed > 0.1f) {
			t->set(second * 2);
			t->start();
		}
		return true;
	};
}

void SpeedupTimer::setIterNumZero()
{
	platformTimer->speed = TIMER_CONST::INIT_SPEED;
}
/*************************************************************************/