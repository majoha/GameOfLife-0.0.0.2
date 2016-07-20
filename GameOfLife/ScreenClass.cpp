#include "ScreenClass.h"

void ScreenClass::writeToConsoleBackBuffer(int x, int y, char character, int attribute)
{
	consoleBuffer[x + WIDTH_OF_WINDOW * y].Char.AsciiChar = character;
	consoleBuffer[x + WIDTH_OF_WINDOW * y].Attributes = attribute;
}
void ScreenClass::writeToScreen(void)
{
	WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
	//memset(consoleBuffer, 0, sizeof(consoleBuffer));
	for(int y = 0; y < HEIGHT_OF_WINDOW; y++){
	
		for(int x = 0; x < WIDTH_OF_WINDOW; x++){
		
			consoleBuffer[x + WIDTH_OF_WINDOW * y].Char.AsciiChar = 0;
		}
	}
}
ScreenClass::ScreenClass(void)
{
	SetConsoleTitle(L"Game of Life");

	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	rHnd = GetStdHandle(STD_INPUT_HANDLE);

	SMALL_RECT WINDOW_SIZE_SMALL_RECT = {0, 0, WIDTH_OF_WINDOW - 1, HEIGHT_OF_WINDOW - 1};
	WINDOW_SIZE = WINDOW_SIZE_SMALL_RECT;

	COORD BUFFER_SIZE_COORD = {WIDTH_OF_WINDOW, HEIGHT_OF_WINDOW};
	BUFFER_SIZE = BUFFER_SIZE_COORD;

	COORD characterBufferSizeCOORD = {WIDTH_OF_WINDOW, HEIGHT_OF_WINDOW};
	characterBufferSize = characterBufferSizeCOORD;

	COORD characterPositionCOORD = {0, 0};
	characterPosition = characterPositionCOORD;

	SMALL_RECT consoleWriteArea_SMALL_RECT = {0, 0, WIDTH_OF_WINDOW, HEIGHT_OF_WINDOW};
	consoleWriteArea = consoleWriteArea_SMALL_RECT;

	SetConsoleWindowInfo(wHnd, TRUE, &WINDOW_SIZE);
	SetConsoleScreenBufferSize(wHnd, BUFFER_SIZE);
}
ScreenClass::~ScreenClass(void)
{
}
