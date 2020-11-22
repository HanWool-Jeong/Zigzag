#include "ScoreBoards.h"

/************************************** 스코어보드 *******************************************/
ScoreBoardPtr ScoreBoard::create(const string& image, ScenePtr scene, int x, int y, bool shown)
{
	auto object = ScoreBoardPtr(new ScoreBoard(image, scene, x, y, shown));
	Object::add(object);
	return object;
}

ScoreBoard::ScoreBoard(const string& image, ScenePtr scene, int x, int y, bool shown) : Object(image, scene, x, y, shown), score(0)
{
	for (int i = 0; i < sizeof(labels) / sizeof(labels[0]); i++)
		labels[i] = Object::create("images/blank.png", scene, x + 220 - (i * 13), y);

	labels[0]->setImage("images/0.png");
}

int ScoreBoard::getScore() const
{
	return score;
}

void ScoreBoard::setScore(int s)
{
	score = s;
}

void ScoreBoard::showScore() const
{
	int sco = score;
	string t;

	for (int i = 0, n = sco % 10; sco > 0 && i < sizeof(labels) / sizeof(labels[0]); sco /= 10, n = sco % 10, i++) {
		t = "images/" + to_string(n) + ".png";
		labels[i]->setImage(t);
	}
}

void ScoreBoard::resetScoreLabel() const
{
	labels[0]->setImage("images/0.png");

	for (int i = 1; i < sizeof(labels) / sizeof(labels[0]); i++)
		labels[i]->setImage("images/blank.png");
}


/************************************** 살아남은 시간 스코어보드 *******************************************/
SurviveBoardPtr SurviveBoard::create(const string& image, ScenePtr scene, int x, int y, bool shown)
{
	auto object = SurviveBoardPtr(new SurviveBoard(image, scene, x, y, shown));
	Object::add(object);
	return object;
}

SurviveBoard::SurviveBoard(const string& image, ScenePtr scene, int x, int y, bool shown) : ScoreBoard(image, scene, x, y, shown)
{
	timer = Timer::create(1.0f);
	timer->setOnTimerCallback([&](TimerPtr t)->bool {
		setScore(getScore() + 1);
		showScore();

		timer->set(1.0f);
		timer->start();
		return true;
	});
}

void SurviveBoard::timerStart() const
{
	timer->start();
}

void SurviveBoard::timerStop() const
{
	timer->stop();
}


/************************************** 최고기록 스코어보드 *******************************************/
HighscoreBoardPtr HighscoreBoard::create(const string& image, ScenePtr scene, int x, int y, bool shown)
{
	auto object = HighscoreBoardPtr(new HighscoreBoard(image, scene, x, y, shown));
	Object::add(object);
	return object;
}

HighscoreBoard::HighscoreBoard(const string& image, ScenePtr scene, int x, int y, bool shown) : ScoreBoard(image, scene, x, y, shown), f(NULL)
{
	int s = 0;

	if (fopen_s(&f, "highscore.txt", "r") == 0) {
		fscanf_s(f, " %d", &s);
		setScore(s);
		showScore();
		fclose(f);
	}
}

void HighscoreBoard::writeScore(int s)
{
	if (fopen_s(&f, "highscore.txt", "w") == 0) {
		fprintf(f, "%d", s);
		fclose(f);
	}
	else {
		showMessage("하이스코어 파일을 여는데 오류가 발생했습니다.");
	}
}


/************************************** 속도 보드 *******************************************/
SpeedMeterPtr SpeedMeter::create(const string& image, ScenePtr scene, int x, int y, bool shown)
{
	auto object = SpeedMeterPtr(new SpeedMeter(image, scene, x, y, shown));
	Object::add(object);
	return object;
}

SpeedMeter::SpeedMeter(const string& image, ScenePtr scene, int x, int y, bool shown) : ScoreBoard(image, scene, x, y, shown)
{
	labels[0]->setImage("images/1.png");
}