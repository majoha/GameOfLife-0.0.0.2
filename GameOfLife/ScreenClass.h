#pragma once
#include <Windows.h>
#include <string>

using namespace std;

class ScreenClass
{
private:

	DWORD n;

	HANDLE wHnd;//write (ouput) handle
	HANDLE rHnd;//read (input) handle

	SMALL_RECT WINDOW_SIZE;
	COORD BUFFER_SIZE;

	COORD characterBufferSize;
	COORD characterPosition;
	SMALL_RECT consoleWriteArea;
public:
	static const int WIDTH_OF_WINDOW = 70;
	static const int HEIGHT_OF_WINDOW = 40;
	CHAR_INFO consoleBuffer[WIDTH_OF_WINDOW * HEIGHT_OF_WINDOW];//we need to initialise this
private:
public:
	void writeToScreen(void);
	void writeToConsoleBackBuffer(int, int, char, int);

	ScreenClass(void);
	~ScreenClass(void);
};

