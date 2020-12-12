#pragma once
#include <bangtal>
using namespace bangtal;
using namespace std;

class TIMER_CONST {
public:
	static const float INIT_SPEED;
	static const float INIT_SPEED_UPDATE_TIME;
	static const int   NUM_OF_UPDATE;
	static const float UPDATE_SIZE;
};

/********************** 플랫폼을 생성해주는 타이머 **********************/
class MakePlatformTimer;
typedef shared_ptr<MakePlatformTimer> MakePlatformTimerPtr;
class MakePlatformTimer : public Timer {
public:
	static MakePlatformTimerPtr create(const Second& second);

protected:
	MakePlatformTimer(const Second& second);
	
private:
	float speed;

	friend class SpeedupTimer;
};
/*************************************************************************/

/********************** 점점 스피드를 올려주는 타이머 **********************/
class SpeedupTimer;
typedef shared_ptr<SpeedupTimer> SpeedupTimerPtr;
class SpeedupTimer : public Timer {
public:
	static SpeedupTimerPtr create(const Second& second);

protected:
	SpeedupTimer(const Second& second);

private:

public:
	void setIterNumZero();
};
/*************************************************************************/