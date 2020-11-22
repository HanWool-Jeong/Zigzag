#include "Platform.h"
//#include <string>

PlatformPtr Platform::create(const string& image, ScenePtr scene, int x, int y, bool shown) 
{
	auto object = PlatformPtr(new Platform(image, scene, x, y, shown));
	Object::add(object);
	return object;
}

Platform::Platform(const string& image, ScenePtr scene, int x, int y, bool shown) : Object(image, scene, x, y, shown), xpos(x), ypos(y)
{}

int Platform::getX() const
{
	return xpos;
}

int Platform::getY() const
{
	return ypos;
}

void Platform::setX(const int x)
{
	xpos = x;
}

void Platform::setY(const int y)
{
	ypos = y;
}