#include "iGraphics.h"
#include "Variables.h"

// Define global variables here
int x = 0;
int y = 0;

int img[25]; // Array to store loading images
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
int loadingStep = 1; // Tracks current loading frame
int btnHoverState = 0; // Tracks which button is currently hovered (0: None, 1: Play, 2: About, 3: Setting, 4: Exit)

// Include functions header file
#include "Functions.h"

int main()
{
	iInitialize(800, 600, "The Last Escape"); // Initialize window size and title

	// Load images into the array
	img[1] = iLoadImage("load1.png");
	img[2] = iLoadImage("load2.png");
	img[3] = iLoadImage("load3.png");
	img[4] = iLoadImage("load4.png");
	img[5] = iLoadImage("load5.png");
	img[6] = iLoadImage("load6.png");
	img[7] = iLoadImage("load7.png");
	img[8] = iLoadImage("load8.png");
	img[9] = iLoadImage("load9.png");
	img[10] = iLoadImage("load10.png");
	img[11] = iLoadImage("load11.png");
	img[12] = iLoadImage("load12.png");
	img[13] = iLoadImage("load13.png");
	img[14] = iLoadImage("load14.png");
	img[15] = iLoadImage("load15.png");
	img[16] = iLoadImage("load16.png");
	img[17] = iLoadImage("load17.png");
	img[18] = iLoadImage("load18.png");
	img[19] = iLoadImage("load19.png");
	img[20] = iLoadImage("load20.png");
	img[21] = iLoadImage("load21.png");
	img[22] = iLoadImage("load22.png");
	img[23] = iLoadImage("load23.png");
	img[24] = iLoadImage("load100.png");

	// Load Main Menu background and normal button overlay images
	menuBg = iLoadImage("menubg.png");
	btnPlay = iLoadImage("menubg1.png");
	btnAbout = iLoadImage("menubg2.png");
	btnSetting = iLoadImage("menubg3.png");
	btnExit = iLoadImage("menubg4.png");

	// Load Hover button overlay images (menubg5, menubg6, menubg7, menubg8)
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
	levelBg = iLoadImage("levelbg.png");
	level1Btn = iLoadImage("levelbg1.png");
	level2Btn = iLoadImage("levelbg2.png");
	level3Btn = iLoadImage("levelbg3.png");

	// Fast and smooth loading timer set to 80 milliseconds
	iSetTimer(80, loadingUpdate);

	iStart();
	return 0;
}