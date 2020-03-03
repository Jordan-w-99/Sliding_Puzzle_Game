#include <windows.h>
#include "PuzzleBox.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdline, int show)
{
	PuzzleBox pb;
	pb.create(hInstance, 364, 600, 100, true);

	return 0;
}
