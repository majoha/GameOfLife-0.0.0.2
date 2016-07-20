#pragma once

#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <iostream>
#include <string>
#include <stdint.h>
#include <conio.h>

#ifndef main_H
#define main_H

const int WIDTH_OF_WORLD = 70;
const int HEIGHT_OF_WORLD = 30;

char world[WIDTH_OF_WORLD * HEIGHT_OF_WORLD];
char tempWorld[WIDTH_OF_WORLD * HEIGHT_OF_WORLD];

const char populated = 254;//ascii block
const char unpopulated = 250;//ascii dot
const char QUIT_KEY = 27;//ascii esc
const char RESTART_KEY = 114;//ascii r
const char TICK_INCREASE_KEY = 119;//ascii w
const char TICK_DECREASE_KEY = 115;//ascii s
const char simPauseKey = 112;//ascii p

int tempTickCount = 0;
int generationCount = 0;
int TICKS_PER_SECOND = 10;
int TIME_BETWEEN_FRAMES = 1000 / TICKS_PER_SECOND;
int FPSCount = 0.0f;
int FPS = 0;
bool toContinue = true;
bool isPaused = false;

#endif