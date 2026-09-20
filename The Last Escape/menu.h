#pragma once

// ============================================================================
// Menu.h
// Common (game-wide) variables + Main Menu functions
// ============================================================================

int loadBg = 0;
int menuBg = 0;
int settingsImg = 0;
int settingsOnImg = 0;
int on1 = 0, on2 = 0;
int off1 = 0, off2 = 0;

int pauseImg = 0;
int pauseToPlayImg = 0;

bool isGamePaused = false;
bool showSettingsPanel = false;
bool musicPlaying = true;
bool soundEnabled = true;

int about1 = 0, about2 = 0, about3 = 0, about4 = 0, about5 = 0;
int creditnoteImg = 0;

int backImg = 0;
int nextImg = 0;

int levelBg = 0;
int level1Bg = 0;
int level2Bg = 0;
int level1Btn = 0, level2Btn = 0, level3Btn = 0, level2UnlockedBtn = 0;
bool level1Completed = false;

int btnPlay = 0, btnAbout = 0, btncredit = 0, btnExit = 0;
int btnPlayHover = 0, btnAboutHover = 0, btncreditHover = 0, btnExitHover = 0;

int gameState = 0;
int loadingStep = 0;
int btnHoverState = 0;

int x = 0;
int y = 0;

int aboutBg1, aboutBg2, btnSetting, btnSettingHover, wpOne;
int menuHover = 0;

void drawMenu();
void handleMenuPassiveMouse(int mx, int my);
void handleMenuMouse(int mx, int my);

void drawMenu() {
	if (menuBg > 0) {
		iShowImage(0, 0, 800, 600, menuBg);
	}

	if (menuHover == 1) iShowImage(340, 363, 280, 50, btnPlayHover);
	else iShowImage(340, 363, 280, 50, btnPlay);

	if (menuHover == 2) iShowImage(340, 297, 280, 50, btnAboutHover);
	else iShowImage(340, 297, 280, 50, btnAbout);

	if (menuHover == 3) iShowImage(340, 237, 280, 50, btncreditHover);
	else iShowImage(340, 237, 280, 50, btncredit);

	if (menuHover == 4) iShowImage(340, 175, 280, 50, btnExitHover);
	else iShowImage(340, 175, 280, 50, btnExit);
}

void handleMenuPassiveMouse(int mx, int my) {
	if (mx >= 340 && mx <= 620 && my >= 363 && my <= 413) menuHover = 1;
	else if (mx >= 340 && mx <= 620 && my >= 297 && my <= 347) menuHover = 2;
	else if (mx >= 340 && mx <= 620 && my >= 237 && my <= 287) menuHover = 3;
	else if (mx >= 340 && mx <= 620 && my >= 175 && my <= 225) menuHover = 4;
	else menuHover = 0;
}

void handleMenuMouse(int mx, int my) {
	if (mx >= 340 && mx <= 620 && my >= 363 && my <= 413) {
		gameState = 300;
	}
	else if (mx >= 340 && mx <= 620 && my >= 297 && my <= 347) {
		gameState = 200;
	}
	else if (mx >= 340 && mx <= 620 && my >= 237 && my <= 287) {
		gameState = 210;
	}
	else if (mx >= 340 && mx <= 620 && my >= 175 && my <= 225) {
		exit(0);
	}
}