#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>
#include "iGraphics.h"

#pragma comment(lib, "winmm.lib")

#define SCREEN_W 800
#define SCREEN_H 600

// Helper functions for audio control
inline void playBGM(const char* fileName) {
	char command[128];
	sprintf_s(command, sizeof(command), "open \"%s\" type mpegvideo alias bgm", fileName);
	mciSendString(command, NULL, 0, NULL);
	mciSendString("play bgm repeat", NULL, 0, NULL);
}

inline void stopBGM() {
	mciSendString("close bgm", NULL, 0, NULL);
}

#endif