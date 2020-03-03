#include "PuzzleBox.h"

PuzzleBox::PuzzleBox()
{
	setImmediateDrawMode(false);

}


PuzzleBox::~PuzzleBox()
{
}

void PuzzleBox::onCreate() {
	//start_time = GetTickCount();
	setTimer(TIMER_ID, 10);
	initGrid();
	EasyGraphics::onCreate();
}

void PuzzleBox::onDraw() {
	clearScreen(WHITE);

	displayGrid();

	setTextColour(BLACK);
	setFont(20, L"Helvetica");
	drawTime();
	//drawText(("Time: " + std::to_string(timer).substr(0,4)).c_str(), 20, 330);

	EasyGraphics::onDraw();
}

void PuzzleBox::onTimer(UINT nIDEvent) {
	if (nIDEvent == TIMER_ID) {
		timer += (1 / 100.0f);
		onDraw();
	}
}

void PuzzleBox::drawTime() {
	int subStrCnt = 4;
	int tempTime = timer;
	float test = tempTime / 10.00f;

	while (test > 1.00f) {
		subStrCnt++;
		test = test / 10.00f;
	}

	drawText(("Time: " + std::to_string(timer).substr(0, subStrCnt)).c_str(), 20, 330);

}

void PuzzleBox::onLButtonDown(UINT nflags, int x, int y) {
	for (int i = 0; i < divs; i++) {
		for (int j = 0; j < divs; j++) {

			int w = gridS / divs;
			int curX = j * ((gridS / divs) + 2) + 20;
			int curY = i * ((gridS / divs) + 2) + 20;


			if (x >= curX && x <= curX + w && y >= curY && y <= curY + w) {
				// move the tile;
				grid.at(i).at(j).startTime = GetTickCount();
				getAnimDir(i, j);
				break;
			}
		}
	}
	onDraw();
}

void PuzzleBox::getAnimDir(int row, int col) {
	tile temp;
	tile cur = grid.at(row).at(col);

	if (row - 1 >= 0 && grid.at(row - 1).at(col).file == L"EMPTY") { // Above is empty
		/*temp = grid.at(row - 1).at(col);
		grid.at(row - 1).at(col) = grid.at(row).at(col);
		grid.at(row).at(col) = temp;*/
		grid.at(row).at(col).animDir = up;
	}
	else if (col + 1 < divs && grid.at(row).at(col + 1).file == L"EMPTY") { // Right is empty
		/*temp = grid.at(row).at(col + 1);
		grid.at(row).at(col + 1) = grid.at(row).at(col);
		grid.at(row).at(col) = temp;*/
		grid.at(row).at(col).animDir = right;

	}
	else if (row + 1 < divs && grid.at(row + 1).at(col).file == L"EMPTY") { // Below is empty
		/*temp = grid.at(row + 1).at(col);
		grid.at(row + 1).at(col) = grid.at(row).at(col);
		grid.at(row).at(col) = temp;*/
		grid.at(row).at(col).animDir = down;

	}
	else if (col - 1 >= 0 && grid.at(row).at(col - 1).file == L"EMPTY") { // Left is empty
		/*temp = grid.at(row).at(col - 1);
		grid.at(row).at(col - 1) = grid.at(row).at(col);
		grid.at(row).at(col) = temp;*/
		grid.at(row).at(col).animDir = left;

	}

	onDraw();
}

void PuzzleBox::initGrid() {
	int cnt = 1;

	for (int i = 0; i < divs; i++) {
		std::vector<tile>row;
		row.clear();
		for (int j = 0; j < divs; j++) {

			if (i == 0 && j == 2) {
				tile newT = { L"EMPTY" };

				row.push_back(newT);
			}
			else {
				std::wstring fl = L"assets/ogCats_0";
				tile newT = { fl + std::to_wstring(cnt) + L".bmp" };

				row.push_back(newT);
			}
			cnt++;
		}
		grid.push_back(row);
	}
}

void PuzzleBox::displayGrid() {
	for (int i = 0; i < divs; i++) {
		for (int j = 0; j < divs; j++) {

			std::wstring fl = grid.at(i).at(j).file;
			//tile cur = grid.at(i).at(j);

			int w = gridS / divs;
			int x = j * ((gridS / divs) + 2) + 20;
			int y = i * ((gridS / divs) + 2) + 20;

			if (grid.at(i).at(j).animDir != none) {
				int diff = GetTickCount() - grid.at(i).at(j).startTime;

				if (diff >= time) {
					swapTiles(grid.at(i).at(j).animDir, i, j);
				}

				diff = diff % time;

				int move = pixels * diff / time;
						
				switch (grid.at(i).at(j).animDir){
				case up:
					y-=move;

					break;
				case right:
					x+=move;

					break;
				case down:
					y+=move;

					break;
				case left:
					x-=move;

					break;
				}
			}

			//drawRectangle(j * w + 20, i * w + 20, w, w, true);
			drawBitmap(fl.c_str(), x, y, w, w);
		}
	}
}

void PuzzleBox::swapTiles(direction dir, int row, int col) {
	tile temp;
	grid.at(row).at(col).animDir = none;

	switch (dir) {
	case (up):
		temp = grid.at(row - 1).at(col);
		grid.at(row - 1).at(col) = grid.at(row).at(col);
		grid.at(row).at(col) = temp;

		break;
	case (right):
		temp = grid.at(row).at(col + 1);
		grid.at(row).at(col + 1) = grid.at(row).at(col);
		grid.at(row).at(col) = temp;

		break;
	case (down):
		temp = grid.at(row + 1).at(col);
		grid.at(row + 1).at(col) = grid.at(row).at(col);
		grid.at(row).at(col) = temp;
		break;
	case (left):
		temp = grid.at(row).at(col - 1);
		grid.at(row).at(col - 1) = grid.at(row).at(col);
		grid.at(row).at(col) = temp;
		break;
	}
}
