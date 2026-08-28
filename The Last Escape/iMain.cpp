#define _CRT_SECURE_NO_WARNINGS
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "iGraphics.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#include "variables.h"
#include "menu.h"
#include "functions.h"

int main()
{
	iInitialize(800, 600, "The Last Escape");

	mciSendString(TEXT("open \"audio1.mp3\" type mpegvideo alias bgm"), NULL, 0, NULL);
	mciSendString(TEXT("open \"mouse.mp3\" type mpegvideo alias clicksound"), NULL, 0, NULL);

	srand((unsigned)time(0));

	loadBg = iLoadImage("Images/loadbg.png");
	menuBg = iLoadImage("Images/menubg.png");
	settingsImg = iLoadImage("Images/settings.png");
	settingsOnImg = iLoadImage("Images/settingson.png");

	pauseImg = iLoadImage("Images/pause.png");
	pauseToPlayImg = iLoadImage("Images/pausetoplay.png");

	on1 = iLoadImage("Images/on1.png");
	on2 = iLoadImage("Images/on2.png");
	off1 = iLoadImage("Images/off1.png");
	off2 = iLoadImage("Images/off2.png");

	btnPlay = iLoadImage("Images/menubg1.png");
	btnAbout = iLoadImage("Images/menubg2.png");
	btncredit = iLoadImage("Images/menubg3.png");
	btnExit = iLoadImage("Images/menubg4.png");

	btnPlayHover = iLoadImage("Images/menubg5.png");
	btnAboutHover = iLoadImage("Images/menubg6.png");
	btncreditHover = iLoadImage("Images/menubg7.png");
	btnExitHover = iLoadImage("Images/menubg8.png");

	about1 = iLoadImage("Images/about1.png");
	about2 = iLoadImage("Images/about2.png");
	about3 = iLoadImage("Images/about3.png");
	about4 = iLoadImage("Images/about4.png");
	about5 = iLoadImage("Images/about5.png");
	creditnoteImg = iLoadImage("Images/creditnote.png");

	backImg = iLoadImage("Images/backimage.png");
	nextImg = iLoadImage("Images/next.png");

	level1Bg = iLoadImage("Images/level1bg.png");
	level2Bg = iLoadImage("Images/level2bg.png");
	levelBg = iLoadImage("Images/levelbg.png");
	level1Btn = iLoadImage("Images/levelbg1.png");
	level2Btn = iLoadImage("Images/levelbg2.png");
	level3Btn = iLoadImage("Images/levelbg3.png");
	level2UnlockedBtn = iLoadImage("Images/levelbg4.png");

	map1Img = iLoadImage("Images/map1.png");
	cellMapImg = iLoadImage("Images/cellmap.png");
	cellMap2Img = iLoadImage("Images/cellmap2.png");
	cctvMapImg = iLoadImage("Images/cctvmap.png");
	alarmMapImg = iLoadImage("Images/alarmmap.png");

	note1Img = iLoadImage("Images/mapnote1.png");
	note2Img = iLoadImage("Images/mapnote2.png");
	note3Img = iLoadImage("Images/mapnote3.png");
	note4Img = iLoadImage("Images/mapnote4.png");

	imgBackground = iLoadImage("Images/b1.png");
	imgLockScreen = iLoadImage("Images/b3.png");
	imgEscapeScreen = iLoadImage("Images/b4.png");
	imgnote = iLoadImage("Images/note.png");
	imgsit1 = iLoadImage("Images/sit1.png");
	imgsit2 = iLoadImage("Images/sit2.png");

	bgOne = iLoadImage("Images/bgone.png");
	bgTwo = iLoadImage("Images/bgtwo.png");

	wpTwo = iLoadImage("Images/wptwo.png");
	wpThree = iLoadImage("Images/wpthree.png");

	playerImg = iLoadImage("Images/player.png");
	playerOne = iLoadImage("Images/player1.png");
	playerTwo = iLoadImage("Images/player2.png");
	playerThree = iLoadImage("Images/player3.png");

	guard1 = iLoadImage("Images/guard1.png");
	guard3 = iLoadImage("Images/guard3.png");
	guard4 = iLoadImage("Images/guard4.png");
	guard5 = iLoadImage("Images/guard5.png");
	guard6 = iLoadImage("Images/guard6.png");
	caughtPlayer = iLoadImage("Images/caughtplayer.png");

	que1 = iLoadImage("Images/que1.png");
	que2 = iLoadImage("Images/que2.png");
	que3 = iLoadImage("Images/que3.png");
	que4 = iLoadImage("Images/que4.png");
	que5 = iLoadImage("Images/que5.png");

	imgCommonRoute = iLoadImage("Images/common route.png");
	imgCCTVBackground = iLoadImage("Images/cctv.png");

	iSetTimer(20, fixedUpdate);
	iSetTimer(100, loadingUpdate);
	iSetTimer(1000, narrativeTimer);
	iSetTimer(400, updateSequence);

	iStart();
	return 0;
}