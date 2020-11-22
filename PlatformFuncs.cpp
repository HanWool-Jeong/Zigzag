#include "PlatformFuncs.h"
#include "Arrow.h"
#include "Timers.h"

extern PlatformPtr platforms[13];
extern ScenePtr scene;
extern ArrowPtr arrow;
extern MakePlatformTimerPtr platformTimer;
extern SpeedupTimerPtr speedupTimer;

void attachPlatform(PlatformPtr& elem, const PlatformPtr& prev)
{
	int r;

	if (prev->getX() == PLAT_CONST::MAX_LEFT_POS) {	// ÇÃ·§Æû xÁÂÇ¥°¡ 120º¸´Ù ÀÛÁö ¾Êµµ·Ï
		r = DIRECTION::RIGHT;
	}
	else if (prev->getX() == PLAT_CONST::MAX_RIGHT_POS) {	// ÇÃ·§Æû xÁÂÇ¥°¡ 670º¸´Ù Å©Áö ¾Êµµ·Ï
		r = DIRECTION::LEFT;
	}
	else {
		r = rand() % 2;
	}

	if (r == DIRECTION::LEFT) {
		elem = Platform::create("images/platform.png", scene, prev->getX() + PLAT_CONST::LEFT_DX, prev->getY() + PLAT_CONST::UP_DX);
	}
	else {
		elem = Platform::create("images/platform.png", scene, prev->getX() + PLAT_CONST::RIGHT_DX, prev->getY() + PLAT_CONST::UP_DX);
	}
}

void initPlatform()
{
	platforms[0] = Platform::create("images/platform.png", scene, PLAT_CONST::INIT_X, PLAT_CONST::INIT_Y);

	for (int i = 1; i < sizeof(platforms) / sizeof(platforms[0]); i++) {
		attachPlatform(platforms[i], platforms[i - 1]);
	}
}

void movingPlatform()
{
	platforms[0]->hide();

	int arySize = sizeof(platforms) / sizeof(platforms[0]);

	for (int i = 1; i < sizeof(platforms) / sizeof(platforms[0]); i++) {
		platforms[i]->setY(platforms[i]->getY() - PLAT_CONST::UP_DX);
		platforms[i]->locate(scene, platforms[i]->getX(), platforms[i]->getY());
		platforms[i - 1] = platforms[i];
	}
	attachPlatform(platforms[arySize - 1], platforms[arySize - 2]);
}

void reInitGame()
{
	for (int i = 0; i < sizeof(platforms) / sizeof(platforms[0]); i++)
		platforms[i]->hide();

	initPlatform();

	arrow->locate(scene, ARROW_INIT::X, ARROW_INIT::Y);
	arrow->setX(ARROW_INIT::X);
	arrow->setY(ARROW_INIT::Y);

	platformTimer->set(TIMER_CONST::INIT_SPEED);
	speedupTimer->set(TIMER_CONST::INIT_SPEED_UPDATE_TIME);
	speedupTimer->setIterNumZero();
}