#include <ctime>
#include <cstdlib>
#include "Arrow.h"
#include "Platform.h"
#include "PlatformFuncs.h"
#include "Buttons.h"
#include "Timers.h"
#include "ScoreBoards.h"

PlatformPtr platforms[13];
ScenePtr scene;
ArrowPtr arrow;

MakePlatformTimerPtr platformTimer;
SpeedupTimerPtr speedupTimer;

ChangeDirectionButtonPtr changeButton;
StartButtonPtr startButton;
RestartButtonPtr reStartButton;

ScoreBoardPtr clickNumScore;
SurviveBoardPtr surviveTimeScore;
HighscoreBoardPtr highscore;
SpeedMeterPtr speedMeter;

int main(void)
{
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	scene = Scene::create("지그재그", "images/background.png");

	srand((unsigned int)time(NULL));
	initPlatform();

	arrow = Arrow::create("images/left_arrow.png", scene, ARROW_INIT::X, ARROW_INIT::Y);

	changeButton = ChangeDirectionButton::create("images/change_button.png", scene, BUTTON_CONST::START_BUTTON_X, BUTTON_CONST::START_BUTTON_Y);
	startButton = StartButton::create("images/start_button.png", scene, BUTTON_CONST::START_BUTTON_X, BUTTON_CONST::START_BUTTON_Y);
	reStartButton = RestartButton::create("images/restart_button.png", scene, BUTTON_CONST::RESTART_BUTTON_X, BUTTON_CONST::RESTART_BUTTON_Y, false);

	clickNumScore = ScoreBoard::create("images/change_num.png", scene, 950, 500);
	surviveTimeScore = SurviveBoard::create("images/survive_time.png", scene, 950, 450);
	highscore = HighscoreBoard::create("images/highscore.png", scene, 950, 400);
	speedMeter = SpeedMeter::create("images/speed.png", scene, 950, 550);

	platformTimer = MakePlatformTimer::create(TIMER_CONST::INIT_SPEED);
	speedupTimer = SpeedupTimer::create(TIMER_CONST::INIT_SPEED_UPDATE_TIME);

	auto quitButton = Button::create("images/quit_button.png", scene, BUTTON_CONST::START_BUTTON_X, BUTTON_CONST::QUIT_BUTTON_Y);
	quitButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		endGame();
		return true;
	});

	startGame(scene);
	return 0;
}