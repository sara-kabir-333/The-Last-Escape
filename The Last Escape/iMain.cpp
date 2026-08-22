#include "iGraphics.h"
#include "Variables.h"

// Define global variables here
int x = 0;
int y = 0;

int loadBg; // Single loading background image
int menuBg;  // Menu background image

// About page images (Expanded: 5 new pages + aboutBg1 + aboutBg2)
int about1, about2, about3, about4, about5;
int aboutBg1, aboutBg2;

int backImg;  // Back button image
int nextImg;  // Next button image for About pages

// Level Select images
int levelBg;
int level1Btn, level2Btn, level3Btn;

// Menu button images
int btnPlay, btnAbout, btnSetting, btnExit;
// Menu hover button images
int btnPlayHover, btnAboutHover, btnSettingHover, btnExitHover;

// GAME STATES & LOADING CONTROL
int gameState = 0;    // Tracks the current active game state/screen
int loadingStep = 0;  // Tracks loading progress (0 to 100)
int btnHoverState = 0; // Tracks which button is currently hovered

// Include functions header file
#include "Functions.h"
int level1Bg;

int main()
{
	iInitialize(800, 600, "The Last Escape"); // Initialize window size and title

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

	// Load About page images (about1 to about5, plus aboutBg1 and aboutBg2) and buttons
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

	// Loading timer set to 50 milliseconds for smooth progress filling
	iSetTimer(50, loadingUpdate);

	iStart();
	return 0;
}