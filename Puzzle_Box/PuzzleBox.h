#pragma once
#include "EasyGraphics.h"
#include <string>
#include <vector>
#include <time.h>

class PuzzleBox :
	public EasyGraphics
{
public:
	PuzzleBox();
	~PuzzleBox();

	enum direction { none, up, right, left, down };

	struct tile {
		std::wstring file;
		direction animDir = { none };
		int startTime = { 0 };
	};
	const int gridS = 300;
	int divs = 3;
	std::vector<std::vector<tile>> grid;

	const int time = 1000;
	const int pixels = 100;

	virtual void onDraw();
	virtual void onLButtonDown(UINT nflags, int x, int y);
	virtual void onTimer(UINT nIDEvent);
	UINT TIMER_ID;
	virtual void onCreate();

	void getAnimDir(int i, int j);
	void initGrid();
	void displayGrid();
};

