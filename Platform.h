#pragma once
#include <bangtal>
using namespace bangtal;
using namespace std;

namespace PLAT_CONST {
	enum {
		INIT_X			= 420,
		INIT_Y			= 10,
		RIGHT_DX		= 50,
		LEFT_DX			= -50,
		UP_DX			= 50,
		MAX_RIGHT_POS	= 720,
		MAX_LEFT_POS	= 70,	
	};
}

class Platform;
typedef shared_ptr<Platform> PlatformPtr;

class Platform : public Object {
public:
	static PlatformPtr create(const string& image, ScenePtr scene = nullptr, int x = 0, int y = 0, bool shown = true);

protected:
	Platform(const string& image, ScenePtr scene, int x, int y, bool shown);

private:
	int xpos, ypos;

public:
	int getX() const;
	int getY() const;
	void setX(const int);
	void setY(const int);
};