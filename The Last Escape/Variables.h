#ifndef VARIABLES_H
#define VARIABLES_H

extern int x;
extern int y;

extern int loadBg; // Single loading background image
extern int menuBg;  // Menu background image
extern int aboutBg1, aboutBg2; // About page images
extern int backImg;  // Back button image
extern int nextImg;  // Next button image for About page

// Level Select images
extern int level1Bg;
extern int levelBg;
extern int level1Btn, level2Btn, level3Btn;

// Menu button images
extern int btnPlay, btnAbout, btnSetting, btnExit;
// Menu hover button images
extern int btnPlayHover, btnAboutHover, btnSettingHover, btnExitHover;

// GAME STATES & LOADING CONTROL
extern int gameState;    // 0: Loading, 1: Main Menu, 2: About Page 1, 3: Level Select, 4: About Page 2
extern int loadingStep; // Tracks current loading progress percentage (0 to 100)
extern int btnHoverState; // Tracks which button is currently hovered

#endif