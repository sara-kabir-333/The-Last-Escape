#include "iGraphics.h"
#include "Variables.h"

// Define global variables declared as 'extern' in Variables.h
int x = 0;
int y = 0;

int loadBg;
int menuBg;

int about1, about2, about3, about4, about5;
int aboutBg1, aboutBg2;

int backImg;
int nextImg;

int levelBg;
int level1Btn, level2Btn, level3Btn;
int level1Bg;

int btnPlay, btnAbout, btnSetting, btnExit;
int btnPlayHover, btnAboutHover, btnSettingHover, btnExitHover;

int gameState = 0;
int loadingStep = 0;
int btnHoverState = 0;

// Include your logic functions
#include "Functions.h"

int main()
{
	iInitialize(800, 600, "The Last Escape");

	// Load single loading background image
	loadBg = iLoadImage("loadbg.png");

	// Load Main Menu background and normal button overlay images
	menuBg = iLoadImage("menubg.png");
	btnPlay = iLoadImage("menubg1.png");
	btnAbout = iLoadImage("menubg2.png");
	btnSetting = iLoadImage("menubg3.png");
	btnExit = iLoadImage("menubg4.png");

	// Load Hover button overlay images
	btnPlayHover = iLoadImage("menubg5.png");
	btnAboutHover = iLoadImage("menubg6.png");
	btnSettingHover = iLoadImage("menubg7.png");
	btnExitHover = iLoadImage("menubg8.png");

	// Load About page images and buttons
	about1 = iLoadImage("about1.png");
	about2 = iLoadImage("about2.png");
	about3 = iLoadImage("about3.png");
	about4 = iLoadImage("about4.png");
	about5 = iLoadImage("about5.png");
	aboutBg1 = iLoadImage("aboutbg1.png");
	aboutBg2 = iLoadImage("aboutbg2.png");

	backImg = iLoadImage("backimage.png");
	nextImg = iLoadImage("next.png");

	// Load Level Select images
	level1Bg = iLoadImage("level1bg.png");
	levelBg = iLoadImage("levelbg.png");
	level1Btn = iLoadImage("levelbg1.png");
	level2Btn = iLoadImage("levelbg2.png");
	level3Btn = iLoadImage("levelbg3.png");

	// Loading timer set to 50 milliseconds
	iSetTimer(50, loadingUpdate);

	iStart();
	return 0;
}