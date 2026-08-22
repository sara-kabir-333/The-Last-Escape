#include "iGraphics.h"
#include "Variables.h"

// Define global variables here
int x = 0;
int y = 0;

int loadBg; // Single loading background image
int menuBg;  // Menu background image
int aboutBg1, aboutBg2; // About page images
int backImg;  // Back button image
int nextImg;  // Next button image for About page

// Level Select images
int levelBg;
int level1Btn, level2Btn, level3Btn;

// Menu button images
int btnPlay, btnAbout, btnSetting, btnExit;
// Menu hover button images
int btnPlayHover, btnAboutHover, btnSettingHover, btnExitHover;

// GAME STATES & LOADING CONTROL
int gameState = 0;    // 0: Loading, 1: Main Menu, 2: About Page 1, 3: Level Select, 4: About Page 2
int loadingStep = 0; // Tracks loading progress (0 to 100)
int btnHoverState = 0; // Tracks which button is currently hovered

// Include functions header file
#include "Functions.h"
int level1Bg;

int main()
{
	iInitialize(800, 600, "The Last Escape"); // Initialize window size and title

	// Load single loading background image (Ensure loadbg.png is in your project folder)
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

	// Loading timer set to 50 milliseconds for smooth progress filling
	iSetTimer(50, loadingUpdate);

	iStart();
	return 0;
}