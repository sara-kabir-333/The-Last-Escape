#pragma once
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include "Menu.h"
#include "Level1Variables.h"
#include "Level2Variables.h"
#include "Level3Variables.h"

const int GAMESTATE_SAVE_CHOICE = 220;

#define SAVE_FILE_NAME "savegame.bin"
#define SAVE_MAGIC 771305

struct SaveData {
	int magic;
	int resumeState;
	int l1, l2, l3, vault, cctv, sw;
	int checksum;
};

int saveChoiceHover = 0;

int svPageImg = 0;
int svContinueImg = 0;
int svContinueHoverImg = 0;
int svNewGameImg = 0;
int svNewGameHoverImg = 0;
int svBackImg = 0;
int svBackHoverImg = 0;

void svLoadImages() {
	svPageImg = iLoadImage("Images/page.png");
	svContinueImg = iLoadImage("Images/continue.png");
	svContinueHoverImg = iLoadImage("Images/continue1.png");
	svNewGameImg = iLoadImage("Images/newgame.png");
	svNewGameHoverImg = iLoadImage("Images/newgame1.png");
	svBackImg = iLoadImage("Images/back.png");
	svBackHoverImg = iLoadImage("Images/back1.png");
}

int svChecksum(const SaveData &d) {
	return d.magic + d.resumeState * 3 + d.l1 * 5 + d.l2 * 7 +
		d.l3 * 11 + d.vault * 13 + d.cctv * 17 + d.sw * 19;
}

bool svIsValidResumeState(int s) {
	return s == 300 || s == 350 || s == 50 || s == 70 ||
		s == GAMESTATE_DODGE_NOTE ||
		s == GAMESTATE_LEVEL2_MAP || s == GAMESTATE_USB_NOTE ||
		s == GAMESTATE_INVEST_NOTE || s == GAMESTATE_VAULT_RUNNER ||
		s == GAMESTATE_GUNCOLLECT_NOTE || s == GAMESTATE_LEVEL3_SHOOTOUT ||
		s == GAMESTATE_TRAFFIC;
}

int svComputeResumeState() {
	int gs = gameState;

	if (gs == 300 || gs == 57) return 300;

	if (gs == 5 || gs == GAMESTATE_LEVEL1_NOTE || gs == 350 || gs == 56)
		return level1Completed ? 300 : 350;

	if ((gs >= 50 && gs <= 55) || gs == 60)
		return level1Completed ? 300 : 50;

	if (gs == 70 || gs == 71)
		return level1Completed ? 300 : 70;

	if (gs == GAMESTATE_DODGE_NOTE || gs == GAMESTATE_DODGE)
		return level1Completed ? 300 : GAMESTATE_DODGE_NOTE;

	if (gs == 6 || gs == GAMESTATE_LEVEL2_NOTE || gs == GAMESTATE_LEVEL2_MAP)
		return level2Completed ? 300 : GAMESTATE_LEVEL2_MAP;

	if (gs == GAMESTATE_USB_NOTE || gs == 400)
		return level2Completed ? 300 : GAMESTATE_USB_NOTE;

	if (gs == GAMESTATE_INVEST_NOTE || gs == GAMESTATE_INVESTIGATION)
		return level2Completed ? 300 : GAMESTATE_INVEST_NOTE;

	if (gs == GAMESTATE_VAULT_RUNNER)
		return level2Completed ? 300 : GAMESTATE_VAULT_RUNNER;

	if (gs == GAMESTATE_VR_WIN_LOADING) return 300;

	if (gs == GAMESTATE_LEVEL3_LOADING || gs == GAMESTATE_GUNCOLLECT_NOTE || gs == GAMESTATE_LEVEL3_FIGHT)
		return GAMESTATE_GUNCOLLECT_NOTE;
	if (gs == GAMESTATE_LEVEL3_SHOOTOUT) return GAMESTATE_LEVEL3_SHOOTOUT;
	if (gs == GAMESTATE_TRAFFIC) return GAMESTATE_TRAFFIC;
	if (gs == GAMESTATE_TRAFFIC_LOADING) return 300;

	return -1;
}

bool svReadFile(SaveData &d) {
	FILE *fp = fopen(SAVE_FILE_NAME, "rb");
	if (fp == NULL) return false;

	size_t n = fread(&d, sizeof(SaveData), 1, fp);
	fclose(fp);

	if (n != 1) return false;
	if (d.magic != SAVE_MAGIC) return false;
	if (d.checksum != svChecksum(d)) return false;
	if (!svIsValidResumeState(d.resumeState)) return false;

	return true;
}

bool svHasSave() {
	SaveData d;
	return svReadFile(d);
}

void saveGame() {
	int resume = svComputeResumeState();
	if (resume == -1) return;

	bool l2 = level2Completed || (gameState == GAMESTATE_VR_WIN_LOADING);

	SaveData d;
	d.magic = SAVE_MAGIC;
	d.resumeState = resume;
	d.l1 = level1Completed ? 1 : 0;
	d.l2 = l2 ? 1 : 0;
	d.l3 = level3Completed ? 1 : 0;
	d.vault = vaultUnlocked ? 1 : 0;
	d.cctv = cctvUnlocked ? 1 : 0;
	d.sw = switchPuzzleCompleted ? 1 : 0;
	d.checksum = svChecksum(d);

	FILE *fp = fopen(SAVE_FILE_NAME, "wb");
	if (fp == NULL) return;

	fwrite(&d, sizeof(SaveData), 1, fp);
	fclose(fp);
}

void svStartNewGame() {
	level1Completed = false;
	level2Completed = false;
	level3Completed = false;
	vaultUnlocked = false;
	cctvUnlocked = false;
	switchPuzzleCompleted = false;

	isGamePaused = false;
	showSettingsPanel = false;

	gameState = 300;
	saveGame();
}

bool svContinueGame() {
	SaveData d;
	if (!svReadFile(d)) return false;

	isGamePaused = false;
	showSettingsPanel = false;

	int s = d.resumeState;

	if (s == 50) {

		resetLevel1();
		gameState = 50;
		sit1Timer = 0;
	}
	else if (s == 70) {
		startSwitchPuzzleLevel();
	}
	else if (s == GAMESTATE_DODGE_NOTE) {
		resetDodgeGame();
		gameState = GAMESTATE_DODGE_NOTE;
	}
	else if (s == GAMESTATE_VAULT_RUNNER) {
		vrResetGame();
		gameState = GAMESTATE_VAULT_RUNNER;
	}
	else if (s == GAMESTATE_LEVEL3_SHOOTOUT) {
		gsResetGame();
		gsState = -1;
		gameState = GAMESTATE_LEVEL3_SHOOTOUT;
	}
	else if (s == GAMESTATE_TRAFFIC) {
		trResetGame();
		trGameStarted = false;
		gameState = GAMESTATE_TRAFFIC;
	}
	else {
		gameState = s;
	}

	level1Completed = (d.l1 != 0);
	level2Completed = (d.l2 != 0);
	level3Completed = (d.l3 != 0);
	vaultUnlocked = (d.vault != 0);
	cctvUnlocked = (d.cctv != 0);
	switchPuzzleCompleted = (d.sw != 0);

	return true;
}

const int SV_BOX_X = 240;
const int SV_BOX_Y = 150;
const int SV_BOX_W = 320;
const int SV_BOX_H = 250;

const int SV_BTN_W = 170;
const int SV_BTN_H = 50;
const int SV_BTN_X = SV_BOX_X + (SV_BOX_W - SV_BTN_W) / 2;
const int SV_BTN1_Y = 320;
const int SV_BTN2_Y = 250;
const int SV_BTN3_Y = 180;

int svButtonAt(int mx, int my) {
	if (mx < SV_BTN_X || mx > SV_BTN_X + SV_BTN_W) return 0;
	if (my >= SV_BTN1_Y && my <= SV_BTN1_Y + SV_BTN_H) return 1;
	if (my >= SV_BTN2_Y && my <= SV_BTN2_Y + SV_BTN_H) return 2;
	if (my >= SV_BTN3_Y && my <= SV_BTN3_Y + SV_BTN_H) return 3;
	return 0;
}

void svDrawImgButton(int bx, int by, int normalImg, int hoverImg, bool hover) {
	int img = hover ? hoverImg : normalImg;
	if (img > 0) iShowImage(bx, by, SV_BTN_W, SV_BTN_H, img);
}

void drawSaveChoice() {
	if (menuBg > 0) iShowImage(0, 0, 800, 600, menuBg);

	if (svPageImg > 0) iShowImage(SV_BOX_X, SV_BOX_Y, SV_BOX_W, SV_BOX_H, svPageImg);

	svDrawImgButton(SV_BTN_X, SV_BTN1_Y, svContinueImg, svContinueHoverImg, saveChoiceHover == 1);
	svDrawImgButton(SV_BTN_X, SV_BTN2_Y, svNewGameImg, svNewGameHoverImg, saveChoiceHover == 2);
	svDrawImgButton(SV_BTN_X, SV_BTN3_Y, svBackImg, svBackHoverImg, saveChoiceHover == 3);
}

void svChoiceMouseMove(int mx, int my) {
	saveChoiceHover = svButtonAt(mx, my);
}

void svChoiceMouseClick(int mx, int my) {
	int b = svButtonAt(mx, my);
	if (b == 1) {
		if (!svContinueGame()) svStartNewGame();
	}
	else if (b == 2) {
		svStartNewGame();
	}
	else if (b == 3) {
		gameState = 100;
	}
}