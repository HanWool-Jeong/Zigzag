#pragma once
#include <cstdio>
#include <bangtal>
using namespace bangtal;
using namespace std;


/************************************** ���ھ�� *******************************************/
class ScoreBoard;
typedef shared_ptr<ScoreBoard> ScoreBoardPtr;
class ScoreBoard : public Object {
public:
	static ScoreBoardPtr create(const string& image, ScenePtr scene = nullptr, int x = 0, int y = 0, bool shown = true);

protected:
	ScoreBoard(const string& image, ScenePtr scene, int x, int y, bool shown);

private:
	int score;
	ObjectPtr labels[8];
	
public:
	int getScore() const;
	void setScore(int s);
	void showScore() const;
	void resetScoreLabel() const;

	friend class SpeedMeter;
};


/************************************** ��Ƴ��� �ð� ���ھ�� *******************************************/
class SurviveBoard;
typedef shared_ptr<SurviveBoard> SurviveBoardPtr;
class SurviveBoard : public ScoreBoard {
public:
	static SurviveBoardPtr create(const string& image, ScenePtr scene = nullptr, int x = 0, int y = 0, bool shown = true);

protected:
	SurviveBoard(const string& image, ScenePtr scene, int x, int y, bool shown);

private:
	TimerPtr timer;

public:
	void timerStart() const;
	void timerStop() const;
};


/************************************** �ְ��� ���ھ�� *******************************************/
class HighscoreBoard;
typedef shared_ptr<HighscoreBoard> HighscoreBoardPtr;
class HighscoreBoard : public ScoreBoard {
public:
	static HighscoreBoardPtr create(const string& image, ScenePtr scene = nullptr, int x = 0, int y = 0, bool shown = true);

protected:
	HighscoreBoard(const string& image, ScenePtr scene, int x, int y, bool shown);

private:
	FILE* f;

public:
	void writeScore(int s);
};


/************************************** �ӵ� ���� *******************************************/
class SpeedMeter;
typedef shared_ptr<SpeedMeter> SpeedMeterPtr;
class SpeedMeter : public ScoreBoard {
public:
	static SpeedMeterPtr create(const string& image, ScenePtr scene = nullptr, int x = 0, int y = 0, bool shown = true);

protected:
	SpeedMeter(const string& image, ScenePtr scene, int x, int y, bool shown);

private:

public:
	
};