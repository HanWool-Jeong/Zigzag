#pragma once
#include <bangtal>
#include "Platform.h"
#include "Buttons.h"
using namespace bangtal;
using namespace std;

namespace DIRECTION {
	enum { LEFT, RIGHT };
}

namespace ARROW_INIT {
	enum { X = 440, Y = 30 };
}

class Arrow;
typedef shared_ptr<Arrow> ArrowPtr;

class Arrow : public Object {
public:
	static ArrowPtr create(const string& image, ScenePtr scene = nullptr, int x = 0, int y = 0, bool shown = true);

protected:
	Arrow(const string& image, ScenePtr scene, int x, int y, bool shown);

private:
	int direction;
	int xpos, ypos;

public:
	int getX() const;
	int getY() const;
	void setX(const int);
	void setY(const int);
	int getDirection() const;
	void setDirection(int);
	bool isOnPlatform(PlatformPtr&);
};