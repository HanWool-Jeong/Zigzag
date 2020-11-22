#include <ctime>
#include <cstdlib>
#include "Arrow.h"
#include "Platform.h"
#include "PlatformFuncs.h"
#include "Buttons.h"
#include "Timers.h"

PlatformPtr platforms[13];
ScenePtr scene;
ArrowPtr arrow;
MakePlatformTimerPtr platformTimer;
SpeedupTimerPtr speedupTimer;
ChangeDirectionButtonPtr changeButton;
StartButtonPtr startButton;
RestartButtonPtr reStartButton;

int main(void)
{
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	scene = Scene::create("지그재그", "images/background.png");

	srand((unsigned int)time(NULL));
	initPlatform();

	arrow = Arrow::create("images/left_arrow.png", scene, ARROW_INIT::X, ARROW_INIT::Y);

	platformTimer = MakePlatformTimer::create(TIMER_CONST::INIT_SPEED);
	speedupTimer = SpeedupTimer::create(TIMER_CONST::INIT_SPEED_UPDATE_TIME);

	changeButton = ChangeDirectionButton::create("images/change_button.png", scene, BUTTON_CONST::START_BUTTON_X, BUTTON_CONST::START_BUTTON_Y);
	startButton = StartButton::create("images/start_button.png", scene, BUTTON_CONST::START_BUTTON_X, BUTTON_CONST::START_BUTTON_Y);
	reStartButton = RestartButton::create("images/restart_button.png", scene, BUTTON_CONST::RESTART_BUTTON_X, BUTTON_CONST::RESTART_BUTTON_Y, false);
	
	startGame(scene);
	return 0;
}