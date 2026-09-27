#pragma once
#include "Menu.h"
#include "Level1Variables.h"

void resetLevel1() {
	loadingStep = 0;
	sit1Timer = 0;
	gameplayCounter = 0;
	playerX = 580;
	playerY = 130;
	playerRunning = false;
	playerEscaped = false;
	finalMessageStarted = false;
	levelFinished = false;
	puzzleScreen = false;
	showWpOne = false;
	showWpTwo = false;
	wrong = false;
	solved = false;
	memoryWrong = false;
	switchPuzzleCompleted = false;
	cctvUnlocked = false;
	puzzleWrongHold = false;
	digitWrongHoldTimer = 0;
}

void generateSwitchSequence() {
	for (int i = 0; i < 5; i++) {
		switchSequence[i] = rand() % 2;
	}
}

void resetSwitchPuzzle() {
	switchCurrentInput = 0;
	switchWrong = false;
	switchSolved = false;
	switchShowSequence = true;
	switchTickCounter = 0;
	switchSolvedTickCounter = 0;
	switchKeyReleased = true;
	switchPlayerRunning = false;
	targetX = -1;

	for (int i = 0; i < 5; i++) {
		switchSlotState[i] = 0;
	}

	generateSwitchSequence();
}

// Draws the 5 switch-puzzle indicator slots using on3/off3 (correct),
// on4/off4 (wrong) or page1 (not answered yet) images, based on
// switchSlotState[]. Position/size/spacing match the old text indicators.
void drawSwitchSlots() {
	for (int i = 0; i < 5; i++) {
		int slotImg = page1Img;

		if (switchSlotState[i] == 1) slotImg = on3Img;
		else if (switchSlotState[i] == 2) slotImg = off3Img;
		else if (switchSlotState[i] == 3) slotImg = on4Img;
		else if (switchSlotState[i] == 4) slotImg = off4Img;

		if (slotImg > 0) {
			iShowImage(200 + (i * 75), 425, 70, 40, slotImg);
		}
	}
}

// Draws the single (bigger) page1.png background for the 3-digit patrol
// code puzzle, with each correctly-entered digit written on top of it in
// black, and - while puzzleWrongHold is active - the expected digit at the
// mistaken slot written in red.
void drawNumberPuzzleSlots() {
	if (page1Img > 0) {
		iShowImage(NUM_PUZZLE_IMG_X, NUM_PUZZLE_IMG_Y, NUM_PUZZLE_IMG_W, NUM_PUZZLE_IMG_H, page1Img);
	}

	for (int i = 0; i < 3; i++) {
		bool showDigit = false;
		bool isWrongSlot = false;

		if (i < current) {
			showDigit = true;
		}
		else if (i == current && puzzleWrongHold) {
			showDigit = true;
			isWrongSlot = true;
		}

		if (showDigit) {
			char digitStr[2];
			digitStr[0] = answer[currentPuzzle][i];
			digitStr[1] = '\0';

			if (isWrongSlot) iSetColor(200, 0, 0);
			else iSetColor(0, 0, 0);

			iText(NUM_PUZZLE_IMG_X + 45 + i * 60, NUM_PUZZLE_IMG_Y + 40, digitStr, GLUT_BITMAP_TIMES_ROMAN_24);
		}
	}
}

void moveCharacterRight() {
	if (isGamePaused) return;
	charX += 8;
	charFrame = (charFrame + 1) % 3;

	if (gameState == 70) {
		if (charX >= 680) {
			gameState = 71;
			charX = 50;
			charY = 170;
			resetSwitchPuzzle();
		}
	}
	else if (gameState == 71) {
		if (charX > 750) {
			charX = 750;
		}
	}
}

void moveCharacterLeft() {
	if (isGamePaused) return;
	charX -= 8;
	charFrame = (charFrame + 1) % 3;
	if (charX < 50) {
		charX = 50;
	}
}

void startSwitchPuzzleLevel() {
	gameState = 70;
	charX = 50;
	charY = 50;
	charFrame = 0;
	targetX = -1;
	resetSwitchPuzzle();
}

void createSequence() {
	for (int i = 0; i < level; i++) {
		sequence[i] = rand() % 7;
	}
	currentDisplayIndex = 0;
	activeDisplayColor = -1;
	displayTimer = 0;
	gameState = 53;
}

void updateSequence() {
	if (isGamePaused) return;
	if (gameState != 53) return;

	displayTimer++;
	if (displayTimer % 2 == 0) {
		if (activeDisplayColor == -1) {
			if (currentDisplayIndex < level) {
				activeDisplayColor = sequence[currentDisplayIndex];
				currentDisplayIndex++;
			}
			else {
				gameState = 54;
				activeDisplayColor = -1;
			}
		}
		else {
			activeDisplayColor = -1;
		}
	}
}

void narrativeTimer() {
	if (isGamePaused) return;
	if (gameState == 50) {
		sit1Timer++;
		if (sit1Timer >= 5) {
			sit1Timer = 0;
			gameState = 51;
		}
	}
}

void showFirstMessage()
{
	if (!levelFinished && gameState == 60)
	{
		showWpOne = true;
	}
}

void hideFirstMessage()
{
	if (!levelFinished && gameState == 60)
	{
		showWpOne = false;
		showWpTwo = true;
	}
}

void showSecondMessage() {}
void backToScene() { puzzleScreen = false; backScene = true; }
void showFinalMessage() {}

void guardMove() {
	if (moveRight)
	{
		guardX++;
		if (guardX >= 720)
			moveRight = false;
	}
	else
	{
		guardX--;
		if (guardX <= 40)
			moveRight = true;
	}
}

void playerRunAnimation() {
	if (!playerRunning)
		return;

	playerFrame++;
	if (playerFrame > 2)
	{
		playerFrame = 0;
	}

	playerX += 8;

	if (playerX > 850 && !finalMessageStarted)
	{
		playerRunning = false;
		playerEscaped = true;
		finalMessageStarted = true;
	}
}

void startPlayerRun() {
	playerRunning = true;
	puzzleScreen = false;
	levelFinished = true;
	showWpTwo = false;
	showWpOne = false;
}

void guardAnimation() {
	guardAnimCounter++;
	if (guardAnimCounter >= 20)
	{
		guardAnimCounter = 0;
		guardFrame++;
		if (guardFrame > 2)
			guardFrame = 0;
	}
}

void generatePuzzle() {
	current = 0;
}

void showQuestionPattern() {
	if (currentPuzzle == 0) iShowImage(200, 220, 400, 350, que1);
	else if (currentPuzzle == 1) iShowImage(200, 220, 400, 350, que2);
	else if (currentPuzzle == 2) iShowImage(200, 220, 400, 350, que3);
	else if (currentPuzzle == 3) iShowImage(200, 220, 400, 350, que4);
	else if (currentPuzzle == 4) iShowImage(200, 220, 400, 350, que5);
}

void resetDodgeBox(int i)
{
	dodgeBoxes[i].width = 50 + rand() % 25;
	dodgeBoxes[i].height = 40 + rand() % 15;

	dodgeBoxes[i].x = rand() % (800 - dodgeBoxes[i].width);
	dodgeBoxes[i].y = 600 + rand() % 300;

	dodgeBoxes[i].speed = 4 + dodgeLevel + rand() % 3;
}

void resetDodgeGame()
{
	dodgePlayerX = -320;

	dodgeGameStarted = false;
	dodgeGameOver = false;
	dodgeLevelComplete = false;
	dodgeRunningToDoor = false;

	dodgeLevel = 1;
	dodgeLevelTimeLeft = 4.0f;
	dodgeCurrentAnimState = 0;

	for (int i = 0; i < DODGE_MAX_BOXES; i++)
		resetDodgeBox(i);
}

void nextDodgeLevel()
{
	dodgeLevel++;
	dodgeLevelTimeLeft = 4.0f;
	dodgeLevelComplete = false;
	dodgeRunningToDoor = false;

	dodgePlayerX = -320;
	dodgeCurrentAnimState = 0;

	for (int i = 0; i < DODGE_MAX_BOXES; i++)
	{
		resetDodgeBox(i);
	}
}

bool checkDodgeCollision(DodgeBox b)
{
	int leftBound = dodgePlayerX + 320 + 20;
	int rightBound = dodgePlayerX + 320 + 50;
	int topBound = dodgePlayerY + dodgePlayerHeight - 35;
	int bottomBound = dodgePlayerY + 5;

	return (leftBound < b.x + b.width &&
		rightBound > b.x &&
		bottomBound < b.y + b.height &&
		topBound > b.y);
}

void updateDodgeGame()
{
	if (!dodgeGameStarted || dodgeGameOver || dodgeLevelComplete)
		return;

	if (dodgeRunningToDoor)
	{
		dodgePlayerX += dodgePlayerSpeed;

		dodgeAnimTimer++;
		int frame = (dodgeAnimTimer / 6) % 2;
		dodgeCurrentAnimState = (frame == 0) ? 3 : 4;

		if (dodgePlayerX >= DODGE_DOOR_X)
		{
			dodgePlayerX = DODGE_DOOR_X;
			dodgeCurrentAnimState = 0;
			dodgeRunningToDoor = false;
			dodgeLevelComplete = true;

			if (dodgeLevel == 1) {
				level1Completed = true;
			}
		}
		return;
	}

	dodgeLevelTimeLeft -= 0.02f;

	int rightBoundary = 800 - 250 - dodgeActualPlayerWidth;
	if (dodgePlayerX >= rightBoundary - 5)
	{
		dodgeRunningToDoor = true;
		return;
	}

	if (dodgeLevelTimeLeft <= 0.0f)
	{
		dodgeLevelTimeLeft = 0.0f;
		if (soundEnabled) {
			PlaySound(TEXT("caughtalarm.wav"), NULL, SND_ASYNC | SND_FILENAME);
		}
		dodgeGameOver = true;
		return;
	}

	for (int i = 0; i < DODGE_MAX_BOXES; i++)
	{
		dodgeBoxes[i].y -= dodgeBoxes[i].speed;

		if (checkDodgeCollision(dodgeBoxes[i]))
		{
			if (soundEnabled) {
				PlaySound(TEXT("caughtalarm.wav"), NULL, SND_ASYNC | SND_FILENAME);
			}
			dodgeGameOver = true;
			return;
		}

		if (dodgeBoxes[i].y + dodgeBoxes[i].height < 0)
		{
			resetDodgeBox(i);
		}
	}
}

void drawDodgeGame()
{
	if (!dodgeGameStarted)
	{
		iShowImage(0, 0, 800, 600, dodgeBgImg);
		iShowImage(dodgePlayerX, dodgePlayerY, dodgePlayerWidth, dodgePlayerHeight, dodgeImgStand);
		iShowImage(130, -25, 500, 280, dodgeNoteImg);

		iSetColor(0, 0, 0);
		iText(230, 40, "REACH THE RIGHT SIDE IN 4 SEC", GLUT_BITMAP_HELVETICA_18);
		iText(280, 15, "Click Mouse to Start", GLUT_BITMAP_HELVETICA_18);

		iShowImage(50, 50, 80, 32, backImg);
		return;
	}

	iShowImage(0, 0, 800, 600, dodgeBgImg);

	iShowImage(560, 535, 220, 70, timerImg);

	iSetColor(255, 215, 0);
	char str[100];
	sprintf(str, "%.1f s", dodgeLevelTimeLeft);
	iText(680, 568, str, GLUT_BITMAP_HELVETICA_18);

	if (!dodgeGameOver)
	{
		if (dodgeCurrentAnimState == 0)
			iShowImage(dodgePlayerX, dodgePlayerY, dodgePlayerWidth, dodgePlayerHeight, dodgeImgStand);
		else if (dodgeCurrentAnimState == 1)
			iShowImage(dodgePlayerX, dodgePlayerY, dodgePlayerWidth, dodgePlayerHeight, dodgeImgLeft1);
		else if (dodgeCurrentAnimState == 2)
			iShowImage(dodgePlayerX, dodgePlayerY, dodgePlayerWidth, dodgePlayerHeight, dodgeImgLeft2);
		else if (dodgeCurrentAnimState == 3)
			iShowImage(dodgePlayerX, dodgePlayerY, dodgePlayerWidth, dodgePlayerHeight, dodgeImgRight1);
		else if (dodgeCurrentAnimState == 4)
			iShowImage(dodgePlayerX, dodgePlayerY, dodgePlayerWidth, dodgePlayerHeight, dodgeImgRight2);
	}

	for (int i = 0; i < DODGE_MAX_BOXES; i++)
	{
		iShowImage(dodgeBoxes[i].x, dodgeBoxes[i].y, dodgeBoxes[i].width, dodgeBoxes[i].height, dodgeBoxImg);
	}

	if (dodgeLevelComplete)
	{
		iShowImage(30, -15, 740, 300, dodgeNoteImg);

		iSetColor(0, 0, 0);
		iText(315, 55, "LEVEL COMPLETE!", GLUT_BITMAP_TIMES_ROMAN_24);

		iSetColor(0, 0, 0);
		if (level1Completed) {
			iText(275, 30, "Click Mouse to Return to the Map", GLUT_BITMAP_HELVETICA_18);
		}
		else {
			iText(290, 30, "Click Mouse for Next Level", GLUT_BITMAP_HELVETICA_18);
		}
	}

	if (dodgeGameOver)
	{
		iShowImage(dodgePlayerX, dodgePlayerY, dodgePlayerWidth, dodgePlayerHeight, dodgeCaughtPlayerImg);

		iShowImage(30, -15, 740, 300, dodgeNoteImg);

		// CHANGED: was red, now black (note.png text).
		iSetColor(0, 0, 0);
		iText(320, 55, "CAUGHT BY GUARD!", GLUT_BITMAP_TIMES_ROMAN_24);

		iSetColor(0, 0, 0);
		iText(305, 30, "Click Mouse to Restart", GLUT_BITMAP_HELVETICA_18);
	}

	iShowImage(50, 50, 80, 32, backImg);
}

void handleDodgeMouseClick(int mx, int my)
{
	if (!dodgeGameStarted)
	{
		dodgeGameStarted = true;
		return;
	}
	else if (dodgeGameOver)
	{
		resetDodgeGame();
		return;
	}
	else if (dodgeLevelComplete)
	{
		if (level1Completed) {
			gameState = 57;
			loadingStep = 0;
			if (musicPlaying) {
				mciSendString(TEXT("pause bgm"), NULL, 0, NULL);
			}
		}
		else {
			nextDodgeLevel();
		}
		return;
	}
}