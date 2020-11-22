#include <bangtal>
#include "Timers.h"
#include "PlatformFuncs.h"
#include "Arrow.h"
using namespace bangtal;

extern PlatformPtr platforms[13];
extern ScenePtr scene;
extern ArrowPtr arrow;
extern RestartButtonPtr reStartButton;
extern ChangeDirectionButtonPtr changeButton;
extern MakePlatformTimerPtr platformTimer;
extern SpeedupTimerPtr speedupTimer;

const float TIMER_CONST::INIT_SPEED				= 1.0f;
const float TIMER_CONST::INIT_SPEED_UPDATE_TIME	= 6.0f;
const int	TIMER_CONST::NUM_OF_UPDATE			= 18;
const float TIMER_CONST::UPDATE_SIZE			= 0.05f;


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
			showMessage("게임오버!");
			changeButton->hide();
			reStartButton->show();
			speedupTimer->stop();
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

SpeedupTimer::SpeedupTimer(const Second& second) : Timer(second), iterNum(0)
{
	onTimerCallback = [&](TimerPtr t)->bool {
		platformTimer->speed -= TIMER_CONST::UPDATE_SIZE;
		iterNum++;

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