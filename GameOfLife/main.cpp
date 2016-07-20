#include "main_H.h"
#include "ScreenClass.h"

using namespace std;

void keyPressIncreaseTick();
void keyPressDecreaseTick();
void keyPressPause();

ScreenClass screenClass;

DWORD lastUpdateTime1 = GetTickCount();
	int lastSecondTime1 = (lastUpdateTime1 / 1000);
	int tickCount1 = 0;//used for displaying tick/s
	int timeDifference = 0;

void clearbackBuffer()
{

}
bool toGenerate()
{
	//return rand() % 2;//generates random number to see if we fill the relevant 2D array position with something
	int upperLimt = 93;

	int temp = rand() % 100;
	if(temp < upperLimt){
		return false;
	}
	else if(temp > upperLimt){
		return true;
	}
}
int generateRandomValue()
{
	return 0;
}
void generate()
{
	//first fill the array with unpopulated cells
	for(int y = 0; y < HEIGHT_OF_WORLD; y++){
		for(int x = 0; x < WIDTH_OF_WORLD; x++){
			world[y * WIDTH_OF_WORLD + x] = unpopulated;
			tempWorld[y * WIDTH_OF_WORLD + x] = unpopulated;
		}
	}

	//for each live single cell, we randomly generate 8 cells around it
	for(int y = 0; y < HEIGHT_OF_WORLD; y++){
		for(int x = 0; x < WIDTH_OF_WORLD; x++){
			if(toGenerate()){
				world[y * WIDTH_OF_WORLD + x] = populated;

				for(int row = -1; row <= 1; row ++){
					for(int col = -1; col <= 1; col ++){

						int currentX = x + col;
						int currentY = y + row;

						if(currentX == x && currentY == y){
						}else if(currentX >= 0 && currentX < WIDTH_OF_WORLD && currentY >= 0 && currentY < HEIGHT_OF_WORLD){
							if(toGenerate()){
								world[currentY * WIDTH_OF_WORLD + currentX] = populated;
							}else{
								world[currentY * WIDTH_OF_WORLD + currentX] = unpopulated;
							}
						}//else if
					}//nested x loop
				}//nested y loop
			}//if toGenerate center cell
		}//for x
	}//for y
}
void initialiseConsoleWindow()
{
}
void initialiseGameOfLife()
{
	generationCount = 0;
	generate();
}
void clearUp()
{
	//this was/is used to return the console back to the default configuration if changes made in this program are permanent
}
void allRules(int x, int y)
{
	//basic box blue algorithm
	unsigned char count = 0;
	for(int row = -1; row <= 1; row++){
		for(int col = -1; col <= 1; col++){

			int currentX = x + col;
			int currentY = y + row;

			if(currentX == x && currentY == y){
			}else if(currentX >= 0 && currentX < WIDTH_OF_WORLD && currentY >= 0 && currentY < HEIGHT_OF_WORLD){
				if(world[currentY * WIDTH_OF_WORLD + currentX] == populated){
					count++;
				}
			}//else if
		}//x loop
	}//y loop

	if(world[y * WIDTH_OF_WORLD + x] == populated){
		if(count < 2){
			tempWorld[y * WIDTH_OF_WORLD + x] = unpopulated;
		}else if((count == 2) || (count == 3)){
			tempWorld[y * WIDTH_OF_WORLD + x] = populated;
		}else if(count > 3){
			tempWorld[y * WIDTH_OF_WORLD + x] = unpopulated;
		}
	}else if(tempWorld[y * WIDTH_OF_WORLD + x] == unpopulated){
		if(count == 3){
			tempWorld[y * WIDTH_OF_WORLD + x] = populated;
		}
	}
}
void ruleCheck()
{
	for(int y = 0; y < HEIGHT_OF_WORLD; y++){
		for(int x = 0; x < WIDTH_OF_WORLD; x++){
			allRules(x, y);
		}
	}
	generationCount++;
}
void writeToConsoleBackBuffer()
{
	//this is where we write to the buffer array, this only writes to the world coords!
	for(int y = 0; y < HEIGHT_OF_WORLD; y++){
		for(int x = 0; x < WIDTH_OF_WORLD; x++){
			screenClass.writeToConsoleBackBuffer(x, y, world[x + WIDTH_OF_WORLD * y], 7);
		}
	}
}
void gameUpdate()
{
	ruleCheck();

	//we must apply the GOL algorithm to the world but the results are saved into a temp world.
	//the temp world is then copied to the world and that is displayed
	memcpy(world, tempWorld, sizeof(world));
}
void temp()
{
	writeToConsoleBackBuffer();
}
void keyPress()
{
	if (_kbhit())
	{
		int keypressed = _getch();

		switch (keypressed)
		{
		case QUIT_KEY://ascii esc
			toContinue = false;
			break;
		case RESTART_KEY://ascii r
			clearbackBuffer();
			initialiseGameOfLife();
			break;
		case TICK_INCREASE_KEY://ascii w
			keyPressIncreaseTick();
			break;
		case TICK_DECREASE_KEY://ascii s
			keyPressDecreaseTick();
			break;
		case simPauseKey://ascii p
			keyPressPause();
			break;
		default:
			break;
		}
	}
}
void keyPressPause()
{
	if(isPaused){ isPaused = false; }else { isPaused = true; }
}
void keyPressIncreaseTick()
{
	int temp1 = TICKS_PER_SECOND + 10;

	if(temp1 <= 10){
		TICKS_PER_SECOND = 10;
	}else if(temp1 >= 90){
		TICKS_PER_SECOND = 90;
	}else{
		TICKS_PER_SECOND += 10;
	}
}
void keyPressDecreaseTick()
{
	int temp1 = TICKS_PER_SECOND - 10;

	if(temp1 <= 10){
		TICKS_PER_SECOND = 10;
	}else{
		TICKS_PER_SECOND -= 10;
	}
}
void writeStringToConsoleBackBuffer(char string[], int x, int y)
{
	for (int i = 0; string[i] != 0; ++i, ++x)
	{
		screenClass.writeToConsoleBackBuffer(x, y, string[i], 7);
	}
}
void printOther()
{
	//this is a placement value that allows us to write under the printed world
	int spacing = 1;

	char tickBuffer[100];
	sprintf_s(tickBuffer, 100, "Tick/s: %i", TICKS_PER_SECOND);
	writeStringToConsoleBackBuffer(tickBuffer, 0, HEIGHT_OF_WORLD);

	char FPSBuffer[100];
	sprintf_s(FPSBuffer, 100, "FPS: %i", FPS);
	writeStringToConsoleBackBuffer(FPSBuffer, 0, HEIGHT_OF_WORLD + spacing++);

	char generationBuffer[100];
	sprintf_s(generationBuffer, 100, "Generation: %i", generationCount);
	writeStringToConsoleBackBuffer(generationBuffer, 0, HEIGHT_OF_WORLD + spacing++);	

	char infoBuffer[100];
	sprintf_s(infoBuffer, 100, "Press 'w' to increase tick count (max: 90)");
	writeStringToConsoleBackBuffer(infoBuffer, 0, HEIGHT_OF_WORLD + spacing++);

	char infoBuffer2[100];
	sprintf_s(infoBuffer2, 100, "Press 's' to decrease tick count (min: 10)");
	writeStringToConsoleBackBuffer(infoBuffer2, 0, HEIGHT_OF_WORLD + spacing++);

	char infoBuffer3[100];
	sprintf_s(infoBuffer3, 100, "Press 'r' to regenerate");
	writeStringToConsoleBackBuffer(infoBuffer3, 0, HEIGHT_OF_WORLD + spacing++);

	char pauseBuffer[100];
	sprintf_s(pauseBuffer, 100, "Press 'p' to pause");
	writeStringToConsoleBackBuffer(pauseBuffer, 0, HEIGHT_OF_WORLD + spacing++);

	char infoBuffer4[100];
	sprintf_s(infoBuffer4, 100, "Press 'esc' to exit");
	writeStringToConsoleBackBuffer(infoBuffer4, 0, HEIGHT_OF_WORLD + spacing++);
}
int main()
{
	srand(time(NULL));

	DWORD lastUpdateTime = GetTickCount();
	int lastSecondTime = (lastUpdateTime / 1000);
	int tickCount = 0;//used for displaying tick/s

	initialiseConsoleWindow();
	initialiseGameOfLife();

	while(toContinue)
	{
		if(!isPaused){

			lastUpdateTime1 = GetTickCount();
			lastSecondTime1 = (lastUpdateTime / 1000);

			TIME_BETWEEN_FRAMES = 1000 / TICKS_PER_SECOND;
			while(GetTickCount() - lastUpdateTime > TIME_BETWEEN_FRAMES)
			{
				keyPress();
				gameUpdate();

				lastUpdateTime += TIME_BETWEEN_FRAMES;
				tickCount++;

			}//while getTickCount()

			int thisSecond = (lastUpdateTime / 1000);
			if (thisSecond > lastSecondTime)
			{
				//cout << "New Second: " << thisSecond << " tickCount: " << tickCount << endl;
				tempTickCount = tickCount;
				tickCount = 0;
				lastSecondTime = thisSecond;

				FPS = FPSCount;
				FPSCount = 0;
			}

			temp();
			printOther();
			screenClass.writeToScreen();
			FPSCount++;
		}//!isPaused

		else{ 
			keyPress();
			temp();
			printOther();
			screenClass.writeToScreen();
			lastUpdateTime = GetTickCount();
			lastSecondTime = (lastUpdateTime / 1000);}

	}//while gameIsRunning

	return 0;
}


void writeImageToBuffer(CHAR_INFO buffer[], char chars[], int colours[], int width, int height, int xOffSet, int yOffSet){

	for(int y = 0; y < height; y++){
		for(int x = 0; x < width; x++){
			screenClass.consoleBuffer[(x + xOffSet) + screenClass.WIDTH_OF_WINDOW * (y + yOffSet)].Char.AsciiChar = chars[x + width * y];
		}
	}
}