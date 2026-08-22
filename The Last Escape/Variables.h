#ifndef VARIABLES_H
#define VARIABLES_H

extern int x;
extern int y;

extern int loadBg; // Single loading background image
extern int menuBg;  // Menu background image

// About page images (Expanded: 5 new pages + aboutBg1 + aboutBg2)
extern int about1, about2, about3, about4, about5;
extern int aboutBg1, aboutBg2;

extern int backImg;  // Back button image
extern int nextImg;  // Next button image for About pages

// Level Select images
extern int level1Bg;
extern int levelBg;
extern int level1Btn, level2Btn, level3Btn;

// Menu button images
extern int btnPlay, btnAbout, btnSetting, btnExit;
// Menu hover button images
extern int btnPlayHover, btnAboutHover, btnSettingHover, btnExitHover;

// GAME STATES & LOADING CONTROL
extern int gameState;    // Manages current screen state of the game
extern int loadingStep;  // Tracks current loading progress percentage (0 to 100)
extern int btnHoverState; // Tracks which button is currently hovered

#endif