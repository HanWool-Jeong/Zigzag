#include "Buttons.h"
#include "Arrow.h"
#include "PlatformFuncs.h"
#include "Timers.h"

extern MakePlatformTimerPtr platformTimer;
extern StartButtonPtr startButton;
extern SpeedupTimerPtr speedupTimer;
extern ChangeDirectionButtonPtr changeButton;


/************************************** 버튼 *******************************************/
ButtonPtr Button::create(const string& image, ScenePtr scene, int x, int y, bool shown)
{
	auto object = ButtonPtr(new Button(image, scene, x, y, shown));
	Object::add(object);
	return object;
}

Button::Button(const string& image, ScenePtr scene, int x, int y, bool shown) : Object(image, scene, x, y, shown)
{}


/************************************** 방향바꾸기버튼 *******************************************/
ChangeDirectionButtonPtr ChangeDirectionButton::create(const string& image, ScenePtr scene, int x, int y, bool shown)
{
	auto object = ChangeDirectionButtonPtr(new ChangeDirectionButton(image, scene, x, y, shown));
	Object::add(object);
	return object;
}

ChangeDirectionButton::ChangeDirectionButton(const string& image, ScenePtr scene, int x, int y, bool shown) : Button(image, scene, x, y, shown)
{}

extern ArrowPtr arrow;
bool ChangeDirectionButton::onMouse(int x, int y, MouseAction action)
{
	if (arrow->getDirection() == DIRECTION::LEFT) {
		arrow->setDirection(DIRECTION::RIGHT);
		arrow->setImage("images/right_arrow.png");
	}
	else {
		arrow->setDirection(DIRECTION::LEFT);
		arrow->setImage("images/left_arrow.png");
	}
	return true;
}


/************************************** 시작버튼 *******************************************/
StartButtonPtr StartButton::create(const string& image, ScenePtr scene, int x, int y, bool shown)
{
	auto object = StartButtonPtr(new StartButton(image, scene, x, y, shown));
	Object::add(object);
	return object;
}

StartButton::StartButton(const string& image, ScenePtr scene, int x, int y, bool shown)
	: Button(image, scene, x, y, shown)
{}

bool StartButton::onMouse(int x, int y, MouseAction action)
{
	platformTimer->start();
	speedupTimer->start();
	this->hide();
	return true;
}


/************************************** 재시작버튼 *******************************************/
RestartButtonPtr RestartButton::create(const string& image, ScenePtr scene, int x, int y, bool shown)
{
	auto object = RestartButtonPtr(new RestartButton(image, scene, x, y, shown));
	Object::add(object);
	return object;
}

RestartButton::RestartButton(const string& image, ScenePtr scene, int x, int y, bool shown)
	: Button(image, scene, x, y, shown)
{}

bool RestartButton::onMouse(int x, int y, MouseAction action)
{
	this->hide();
	changeButton->show();
	startButton->show();
	reInitGame();
	return true;
}