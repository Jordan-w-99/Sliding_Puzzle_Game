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

	EasyGraphics::onDraw();
}

void PuzzleBox::onTimer(UINT nIDEvent) {
	if (nIDEvent == TIMER_ID) {
		onDraw();
	}
}

void PuzzleBox::onLButtonDown(UINT nflags, int x, int y) {
	for (int i = 0; i < divs; i++) {
		for (int j = 0; j < divs; j++) {
			tile cur = grid.at(i).at(j);

			int w = gridS / divs;
			int curX = j * (w + 2) + (800 / 2 - gridS / 2);
			int curY = i * (w + 2) + (600 / 2 - gridS / 2);


			if (x >= curX && x <= curX + w && y >= curY && y <= curY + w) {
				// move the tile;
				cur.startTime = GetTickCount();
				getAnimDir(i, j);
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
		cur.animDir = { up };
	}
	else if (col + 1 < divs && grid.at(row).at(col + 1).file == L"EMPTY") { // Right is empty
		/*temp = grid.at(row).at(col + 1);
		grid.at(row).at(col + 1) = grid.at(row).at(col);
		grid.at(row).at(col) = temp;*/
		cur.animDir = { right };

	}
	else if (row + 1 < divs && grid.at(row + 1).at(col).file == L"EMPTY") { // Below is empty
		/*temp = grid.at(row + 1).at(col);
		grid.at(row + 1).at(col) = grid.at(row).at(col);
		grid.at(row).at(col) = temp;*/
		cur.animDir = { down };

	}
	else if (col - 1 >= 0 && grid.at(row).at(col - 1).file == L"EMPTY") { // Left is empty
		/*temp = grid.at(row).at(col - 1);
		grid.at(row).at(col - 1) = grid.at(row).at(col);
		grid.at(row).at(col) = temp;*/
		cur.animDir = { left };

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
			tile cur = grid.at(i).at(j);

			int w = gridS / divs;
			int x = j * (w + 2) + (800 / 2 - gridS / 2);
			int y = i * (w + 2) + (600 / 2 - gridS / 2);

			if (cur.animDir != none) {
				int diff = GetTickCount() - cur.startTime;
				diff = diff % time;

				int move = pixels * diff / time;



				switch (cur.animDir){
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