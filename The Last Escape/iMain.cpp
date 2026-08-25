#define _CRT_SECURE_NO_WARNINGS
#include "iGraphics.h"
#include <stdlib.h>
#include <time.h>
#include "Variables.h"
#include "Functions.h"

int main()
{
	iInitialize(800, 600, "The Last Escape");

	srand((unsigned)time(0));

	// --- LOAD MENU & UI IMAGES ---
	loadBg = iLoadImage("loadbg.png");
	menuBg = iLoadImage("menubg.png");
	btnPlay = iLoadImage("menubg1.png");
	btnAbout = iLoadImage("menubg2.png");
	btnSetting = iLoadImage("menubg3.png");
	btnExit = iLoadImage("menubg4.png");

	btnPlayHover = iLoadImage("menubg5.png");
	btnAboutHover = iLoadImage("menubg6.png");
	btnSettingHover = iLoadImage("menubg7.png");
	btnExitHover = iLoadImage("menubg8.png");

	about1 = iLoadImage("about1.png");
	about2 = iLoadImage("about2.png");
	about3 = iLoadImage("about3.png");
	about4 = iLoadImage("about4.png");
	about5 = iLoadImage("about5.png");
	aboutBg1 = iLoadImage("aboutbg1.png");
	aboutBg2 = iLoadImage("aboutbg2.png");

	backImg = iLoadImage("backimage.png");
	nextImg = iLoadImage("next.png");

	level1Bg = iLoadImage("level1bg.png");
	levelBg = iLoadImage("levelbg.png");
	level1Btn = iLoadImage("levelbg1.png");
	level2Btn = iLoadImage("levelbg2.png");
	level3Btn = iLoadImage("levelbg3.png");

	// --- LOAD PUZZLE & NARRATIVE & GAMEPLAY IMAGES ---
	imgBackground = iLoadImage("b1.png");
	imgLockScreen = iLoadImage("b3.png");
	imgEscapeScreen = iLoadImage("b4.png");
	imgnote = iLoadImage("note.png");
	imgsit1 = iLoadImage("sit1.png");
	imgsit2 = iLoadImage("sit2.png");

	bgOne = iLoadImage("bgone.png");
	bgTwo = iLoadImage("bgtwo.png");

	wpOne = iLoadImage("wpone.png");
	wpTwo = iLoadImage("wptwo.png");
	wpThree = iLoadImage("wpthree.png");

	playerImg = iLoadImage("player.png");
	playerOne = iLoadImage("player1.png");
	playerTwo = iLoadImage("player2.png");
	playerThree = iLoadImage("player3.png");

	guard1 = iLoadImage("guard1.png");
	guard3 = iLoadImage("guard3.png");
	guard4 = iLoadImage("guard4.png");
	guard5 = iLoadImage("guard5.png");

	que1 = iLoadImage("que1.png");
	que2 = iLoadImage("que2.png");
	que3 = iLoadImage("que3.png");
	que4 = iLoadImage("que4.png");
	que5 = iLoadImage("que5.png");

	// --- LOAD SWITCH PUZZLE & CCTV IMAGES ---
	imgCommonRoute = iLoadImage("Images/common route.png");
	imgCCTVBackground = iLoadImage("Images/cctv.png");

	imgChar[0] = iLoadImage("Images/mainchar1.png");
	imgChar[1] = iLoadImage("Images/mainchar2.png");
	imgChar[2] = iLoadImage("Images/mainchar3.png");
	imgChar[3] = iLoadImage("Images/mainchar4.png");

	// --- TIMERS SETUP ---
	iSetTimer(200, loadingUpdate);
	iSetTimer(200, fixedUpdate);
	iSetTimer(400, updateSequence);
	iSetTimer(1000, narrativeTimer);

	iStart();
	return 0;
}