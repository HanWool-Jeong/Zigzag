#include "Arrow.h"

ArrowPtr Arrow::create(const string& image, ScenePtr scene, int x, int y, bool shown)
{
	auto object = ArrowPtr(new Arrow(image, scene, x, y, shown));
	Object::add(object);
	return object;
}

Arrow::Arrow(const string& image, ScenePtr scene, int x, int y, bool shown)
	: Object(image, scene, x, y, shown), direction(DIRECTION::LEFT), xpos(x), ypos(y)
{}

int Arrow::getX() const
{
	return xpos;
}

int Arrow::getY() const
{
	return ypos;
}

void Arrow::setX(const int x)
{
	xpos = x;
}

void Arrow::setY(const int y)
{
	ypos = y;
}

int Arrow::getDirection() const
{
	return direction;
}

void Arrow::setDirection(int d)
{
	direction = d;
}

bool Arrow::isOnPlatform(PlatformPtr& platform)
{
	if (platform->getX() + 20 == this->getX())
		return true;
	else {
		return false;
	}
}