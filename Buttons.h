#pragma once
#include <bangtal>
using namespace bangtal;
using namespace std;

namespace BUTTON_CONST {
	enum {
		START_BUTTON_X		= 980,
		START_BUTTON_Y		= 100,
		RESTART_BUTTON_X	= 980,
		RESTART_BUTTON_Y	= 200,
		QUIT_BUTTON_Y		= 600
	};
}


/************************************** 버튼 *******************************************/
class Button;
typedef shared_ptr<Button> ButtonPtr;
class Button : public Object {
public:
	static ButtonPtr create(const string& image, ScenePtr scene = nullptr, int x = 0, int y = 0, bool shown = true);

protected:
	Button(const string& image, ScenePtr scene, int x, int y, bool shown);
};


/************************************** 방향바꾸기버튼 *******************************************/
class ChangeDirectionButton;
typedef shared_ptr<ChangeDirectionButton> ChangeDirectionButtonPtr;
class ChangeDirectionButton : public Button {
public:
	static ChangeDirectionButtonPtr create(const string& image, ScenePtr scene = nullptr, int x = 0, int y = 0, bool shown = true);

protected:
	ChangeDirectionButton(const string& image, ScenePtr scene, int x, int y, bool shown);

private:

public:
	virtual bool onMouse(int x, int y, MouseAction action);
};


/************************************** 시작버튼 *******************************************/
class StartButton;
typedef shared_ptr<StartButton> StartButtonPtr;
class StartButton : public Button {
public:
	static StartButtonPtr create(const string& image, ScenePtr scene = nullptr, int x = 0, int y = 0, bool shown = true);

protected:
	StartButton(const string& image, ScenePtr scene, int x, int y, bool shown);

private:

public:
	virtual bool onMouse(int x, int y, MouseAction action);
};


/************************************** 재시작버튼 *******************************************/
class RestartButton;
typedef shared_ptr<RestartButton> RestartButtonPtr;
class RestartButton : public Button {
public:
	static RestartButtonPtr create(const string& image, ScenePtr scene = nullptr, int x = 0, int y = 0, bool shown = true);

protected:
	RestartButton(const string& image, ScenePtr scene, int x, int y, bool shown);

private:

public:
	virtual bool onMouse(int x, int y, MouseAction action);
};