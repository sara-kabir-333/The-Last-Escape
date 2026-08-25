#define _CRT_SECURE_NO_WARNINGS

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Variables.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

void showQuestionPattern();
void startPlayerRun();
void resetSwitchPuzzle();
void startSwitchPuzzleLevel();

// --- SWITCH PUZZLE FUNCTIONS ---
void generateSwitchSequence() {
	for (int i = 0; i < 5; i++) {
		switchSequence[i] = rand() % 2; // 0 for OFF, 1 for ON
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
	generateSwitchSequence();
}

void moveCharacterRight() {
	charX += 8;
	charFrame = (charFrame + 1) % 4;

	if (gameState == 70) {
		// Common Route -> Transition to CCTV Room at right boundary
		if (charX >= 680) {
			gameState = 71;
			charX = 50;
			charY = 210;
			resetSwitchPuzzle();
		}
	}
}

void showFinalEscapeScreen() {
	gameState = 56; // Final Escape Screen
}

void startSwitchPuzzleLevel() {
	gameState = 70; // Common Route
	charX = 50;
	charY = 150;
	charFrame = 0;
	targetX = -1;
	resetSwitchPuzzle();
}

// --- COLOR SEQUENCE PUZZLE FUNCTIONS ---
void createSequence() {
	for (int i = 0; i < level; i++) {
		sequence[i] = rand() % 4;
	}
	currentDisplayIndex = 0;
	activeDisplayColor = -1;
	displayTimer = 0;
	gameState = 53;
}

void updateSequence() {
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
	if (gameState == 50) {
		sit1Timer++;
		if (sit1Timer >= 3) {
			sit1Timer = 0;
			gameState = 51;
		}
	}
}

void loadingUpdate()
{
	if (gameState != 0 && gameState != 5)
		return;

	loadingStep += 4;

	if (loadingStep >= 100)
	{
		loadingStep = 100;
		if (gameState == 0)
		{
			gameState = 100;
		}
		else if (gameState == 5)
		{
			gameState = 50;
			sit1Timer = 0;
			gameplayCounter = 0;
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
void backToScene(){ puzzleScreen = false; backScene = true; }
void showFinalMessage(){}

void guardMove(){
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

void playerRunAnimation(){
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

void startPlayerRun(){
	playerRunning = true;
	puzzleScreen = false;
	levelFinished = true;
	showWpTwo = false;
	showWpOne = false;
}

void guardAnimation(){
	guardAnimCounter++;
	if (guardAnimCounter >= 20)
	{
		guardAnimCounter = 0;
		guardFrame++;
		if (guardFrame > 2)
			guardFrame = 0;
	}
}

void generatePuzzle(){
	current = 0;
}

void showQuestionPattern(){
	if (currentPuzzle == 0) iShowImage(200, 220, 400, 350, que1);
	else if (currentPuzzle == 1) iShowImage(200, 220, 400, 350, que2);
	else if (currentPuzzle == 2) iShowImage(200, 220, 400, 350, que3);
	else if (currentPuzzle == 3) iShowImage(200, 220, 400, 350, que4);
	else if (currentPuzzle == 4) iShowImage(200, 220, 400, 350, que5);
}

void fixedUpdate(){
	// --- PENDING TRANSITIONS MANAGEMENT ---
	if (isWaitingToRun) {
		solvedTickCounter++;
		if (solvedTickCounter >= 7) {
			isWaitingToRun = false;
			startPlayerRun();
		}
	}

	// --- SWITCH PUZZLE TIMING & MOVEMENT LOGIC (Only in Common Route gameState 70) ---
	if (gameState == 70) {
		if (isKeyPressed('d') || isKeyPressed('D') || isKeyPressed(' ') || isSpecialKeyPressed(GLUT_KEY_RIGHT)) {
			moveCharacterRight();
			targetX = -1;
		}

		if (targetX != -1 && charX < targetX) {
			moveCharacterRight();
			if (charX >= targetX) {
				targetX = -1;
			}
		}
	}

	// CCTV Room & Switch Puzzle Screen (gameState 71)
	if (gameState == 71) {
		if (switchShowSequence) {
			switchTickCounter++;
			if (switchTickCounter >= 120) {
				switchShowSequence = false;
			}
		}

		if (switchSolved && !switchPlayerRunning) {
			switchPlayerRunning = true;
		}

		if (switchPlayerRunning) {
			charX += 8;
			charFrame = (charFrame + 1) % 4;
			if (charX > 850) {
				switchPlayerRunning = false;
				showFinalEscapeScreen();
			}
		}
	}

	if (gameState == 60)
	{
		guardAnimation();
		guardMove();
		playerRunAnimation();

		if (!levelFinished && !puzzleScreen)
		{
			gameplayCounter++;
			if (gameplayCounter == 25)
			{
				hideFirstMessage();
			}
		}

		if (!playerRunning && !playerEscaped && !puzzleScreen)
		{
			playerIdleCounter++;
			if (playerIdleCounter >= 60)
			{
				playerIdleCounter = 0;
				playerIdleFrame = 1 - playerIdleFrame;
			}
		}

		if (puzzleScreen && showQuestion)
		{
			if ((clock() - questionStartTime) >= (5 * CLOCKS_PER_SEC))
			{
				showQuestion = false;
				current = 0;
				digitReleased = true;
			}
		}

		if (showWpTwo)
		{
			if (isKeyPressed('s') || isKeyPressed('S'))
			{
				if (keyReleased)
				{
					keyReleased = false;
					showWpTwo = false;
					showWpOne = false;
					puzzleScreen = true;
					showQuestion = true;
					current = 0;
					wrong = false;
					solved = false;
					currentPuzzle = rand() % 5;
					current = 0;
					questionStartTime = clock();
				}
			}
			else
			{
				keyReleased = true;
			}
		}

		if (puzzleScreen && !showQuestion && !solved)
		{
			char pressed = -1;

			if (isKeyPressed('0')) pressed = '0';
			else if (isKeyPressed('1')) pressed = '1';
			else if (isKeyPressed('2')) pressed = '2';
			else if (isKeyPressed('3')) pressed = '3';
			else if (isKeyPressed('4')) pressed = '4';
			else if (isKeyPressed('5')) pressed = '5';
			else if (isKeyPressed('6')) pressed = '6';
			else if (isKeyPressed('7')) pressed = '7';
			else if (isKeyPressed('8')) pressed = '8';
			else if (isKeyPressed('9')) pressed = '9';

			if (pressed == -1)
			{
				digitReleased = true;
			}
			else if (digitReleased)
			{
				digitReleased = false;

				if (pressed == answer[currentPuzzle][current])
				{
					current++;

					if (current == 3)
					{
						solved = true;
						solvedTickCounter = 0;
						isWaitingToRun = true;
					}
				}
				else
				{
					wrong = true;
					current = 0;
					digitReleased = true;
				}
			}
		}

		if (puzzleScreen && wrong)
		{
			if (isKeyPressed('r') || isKeyPressed('R'))
			{
				if (rReleased)
				{
					rReleased = false;
					wrong = false;
					solved = false;
					showQuestion = true;
					current = 0;
					currentPuzzle = rand() % 5;
					digitReleased = true;
					questionStartTime = clock();
				}
			}
			else
			{
				rReleased = true;
			}
		}
	}
}

void iDraw()
{
	iClear();
	iSetColor(0, 0, 0);
	iFilledRectangle(0, 0, 800, 600);

	if (gameState == 0 || gameState == 5)
	{
		if (gameState == 0) iShowImage(0, 0, 800, 600, loadBg);
		else iShowImage(0, 0, 800, 600, level1Bg);

		iSetColor(180, 122, 33);
		iText(100, 120, "LOADING...", GLUT_BITMAP_TIMES_ROMAN_24);

		iRectangle(100, 80, 600, 30);
		int barWidth = (loadingStep * 600) / 100;
		iFilledRectangle(100, 80, barWidth, 30);
	}
	else if (gameState == 100)
	{
		iShowImage(0, 0, 800, 600, menuBg);

		if (btnHoverState == 1) iShowImage(340, 365, 300, 50, btnPlayHover);
		else iShowImage(340, 365, 300, 50, btnPlay);

		if (btnHoverState == 2) iShowImage(340, 295, 300, 50, btnAboutHover);
		else iShowImage(340, 295, 300, 50, btnAbout);

		if (btnHoverState == 3) iShowImage(340, 235, 300, 50, btnSettingHover);
		else iShowImage(340, 235, 300, 50, btnSetting);

		if (btnHoverState == 4) iShowImage(340, 175, 300, 50, btnExitHover);
		else iShowImage(340, 175, 300, 50, btnExit);
	}
	else if (gameState >= 200 && gameState <= 206)
	{
		int currentAbout = about1;
		if (gameState == 200) currentAbout = about1;
		else if (gameState == 201) currentAbout = about2;
		else if (gameState == 202) currentAbout = about3;
		else if (gameState == 203) currentAbout = about4;
		else if (gameState == 204) currentAbout = about5;
		else if (gameState == 205) currentAbout = aboutBg1;
		else if (gameState == 206) currentAbout = aboutBg2;

		if (gameState == 205 || gameState == 206)
		{
			iShowImage(50, 50, 700, 500, currentAbout);
		}
		else
		{
			iShowImage(0, 0, 800, 600, currentAbout);
		}

		iShowImage(50, 50, 100, 40, backImg);
		if (gameState != 206) iShowImage(650, 50, 100, 40, nextImg);
	}
	else if (gameState == 300)
	{
		iShowImage(0, 0, 800, 600, levelBg);
		iShowImage(120, 120, 175, 342, level1Btn);
		iShowImage(307, 115, 175, 342, level2Btn);
		iShowImage(492, 115, 175, 342, level3Btn);
		iShowImage(68, 26, 120, 53, backImg);
	}
	else if (gameState == 70) // Switch Puzzle Common Route
	{
		iShowImage(0, 0, 800, 600, imgCommonRoute);
		iShowImage(charX, charY, 130, 200, imgChar[charFrame]);

		iSetColor(0, 0, 0);
		iFilledRectangle(180, 500, 440, 60);
		iSetColor(255, 255, 255);
		iText(200, 530, "PRESS 'D', SPACE, RIGHT ARROW OR CLICK TO MOVE", GLUT_BITMAP_HELVETICA_12);
		iSetColor(200, 200, 200);
		iText(245, 510, "Head to the Security Control Room...", GLUT_BITMAP_HELVETICA_12);
	}
	else if (gameState == 71) // CCTV Room & Switch Puzzle Screen
	{
		iShowImage(0, 0, 800, 600, imgCCTVBackground);
		iShowImage(charX, charY, 140, 220, imgChar[charFrame]);

		iSetColor(0, 0, 0);
		iFilledRectangle(150, 460, 500, 110);
		iSetColor(255, 255, 255);

		if (switchShowSequence) {
			iText(180, 540, "MEMORIZE PATTERN (CLICK ANYWHERE TO SKIP):", GLUT_BITMAP_HELVETICA_12);

			for (int i = 0; i < 5; i++) {
				char text[10];
				sprintf(text, "[%s]", switchSequence[i] == 1 ? "ON" : "OFF");
				if (switchSequence[i] == 1) iSetColor(50, 255, 50);
				else iSetColor(255, 80, 80);
				iText(200 + (i * 70), 495, text, GLUT_BITMAP_HELVETICA_18);
			}
		}
		else {
			iSetColor(255, 255, 255);
			iText(180, 540, "CLICK [ON] / [OFF] BUTTONS OR PRESS O / F", GLUT_BITMAP_HELVETICA_12);

			for (int i = 0; i < 5; i++) {
				if (i < switchCurrentInput) {
					iSetColor(0, 255, 0);
					iText(200 + (i * 70), 495, "[OK]", GLUT_BITMAP_HELVETICA_18);
				}
				else {
					iSetColor(180, 180, 180);
					iText(200 + (i * 70), 495, "[ ? ]", GLUT_BITMAP_HELVETICA_18);
				}
			}

			// Draw Clickable ON Button
			iSetColor(0, 180, 0);
			iFilledRectangle(260, 400, 120, 45);
			iSetColor(255, 255, 255);
			iText(295, 415, "ON", GLUT_BITMAP_HELVETICA_18);

			// Draw Clickable OFF Button
			iSetColor(180, 0, 0);
			iFilledRectangle(420, 400, 120, 45);
			iSetColor(255, 255, 255);
			iText(445, 415, "OFF", GLUT_BITMAP_HELVETICA_18);

			if (switchSolved) {
				iSetColor(0, 0, 0);
				iFilledRectangle(150, 250, 500, 100);
				iSetColor(50, 255, 50);
				iText(210, 310, "CCTV CAMERA DISABLED!", GLUT_BITMAP_HELVETICA_18);
				iText(220, 275, "ESCAPE NOW!", GLUT_BITMAP_HELVETICA_12);
			}

			if (switchWrong) {
				iSetColor(0, 0, 0);
				iFilledRectangle(150, 250, 500, 100);
				iSetColor(255, 50, 50);
				iText(230, 310, "WRONG PATTERN! ALARM TRIGGERED", GLUT_BITMAP_HELVETICA_18);
				iText(250, 275, "CLICK ANYWHERE TO RETRY", GLUT_BITMAP_HELVETICA_12);
			}
		}
	}
	else if (gameState == 50) {
		if (imgsit1 > 0) iShowImage(0, 0, 800, 600, imgsit1);
	}
	else if (gameState == 51) {
		if (imgsit2 > 0) iShowImage(0, 0, 800, 600, imgsit2);
		if (imgnote > 0) iShowImage(40, -27, 600, 320, imgnote);
		iSetColor(0, 0, 0);
		iText(130, 40, "CLICK ON SCREEN TO MOVE FORWARD", GLUT_BITMAP_HELVETICA_18);
	}
	else if (gameState == 52) {
		if (imgBackground > 0) iShowImage(0, 0, 800, 600, imgBackground);
		if (imgnote > 0) iShowImage(40, -27, 600, 320, imgnote);
		iSetColor(0, 0, 0);
		iText(150, 40, "CLICK ANYWHERE TO INSPECT LOCK", GLUT_BITMAP_HELVETICA_18);
	}
	else if (gameState == 53 || gameState == 54 || gameState == 57) {
		if (imgLockScreen > 0) iShowImage(0, 0, 800, 600, imgLockScreen);
		if (imgnote > 0) iShowImage(0, 0, 600, 350, imgnote);

		iSetColor(0, 0, 0);
		if (gameState == 53) iText(100, 75, "MEMORIZE THE SEQUENCE...", GLUT_BITMAP_HELVETICA_18);
		else if (gameState == 54) iText(100, 75, "YOUR TURN: CLICK THE BOXES", GLUT_BITMAP_HELVETICA_18);
		else if (gameState == 57) {
			iSetColor(255, 0, 0);
			iText(100, 75, "WRONG! CLICK ANYWHERE TO RETRY", GLUT_BITMAP_HELVETICA_18);
		}

		if (gameState == 53 && activeDisplayColor == 0) iSetColor(255, 150, 150);
		else iSetColor(255, 0, 0);
		iFilledRectangle(redX, redY, boxSize, boxSize);

		if (gameState == 53 && activeDisplayColor == 1) iSetColor(150, 150, 255);
		else iSetColor(0, 0, 255);
		iFilledRectangle(blueX, blueY, boxSize, boxSize);

		if (gameState == 53 && activeDisplayColor == 2) iSetColor(150, 255, 150);
		else iSetColor(0, 255, 0);
		iFilledRectangle(greenX, greenY, boxSize, boxSize);

		if (gameState == 53 && activeDisplayColor == 3) iSetColor(255, 255, 180);
		else iSetColor(255, 255, 0);
		iFilledRectangle(yellowX, yellowY, boxSize, boxSize);
	}
	else if (gameState == 55) {
		if (imgLockScreen > 0) iShowImage(0, 0, 800, 600, imgLockScreen);
		if (imgnote > 0) iShowImage(0, 0, 600, 350, imgnote);

		if (playerImg > 0) iShowImage(530, 180, 140, 180, playerImg);
		if (nextImg > 0) iShowImage(600, 50, 100, 40, nextImg);

		iSetColor(0, 0, 0);
		iText(80, 75, "LOCK UNLOCKED! CLICK NEXT", GLUT_BITMAP_HELVETICA_18);
	}
	else if (gameState == 60)
	{
		iShowImage(0, 0, 800, 600, bgOne);

		if (moveRight)
		{
			if (guardFrame == 0 || guardFrame == 2)
				iShowImage(guardX, guardY, 50, 70, guard1);
			else if (guardFrame == 1)
				iShowImage(guardX, guardY, 50, 70, guard3);
		}
		else
		{
			if (guardFrame == 0 || guardFrame == 2)
				iShowImage(guardX, guardY, 50, 70, guard4);
			else if (guardFrame == 1)
				iShowImage(guardX, guardY, 50, 70, guard5);
		}

		if (playerRunning)
		{
			if (playerFrame == 0)
				iShowImage(playerX, playerY, 70, 110, playerOne);
			else if (playerFrame == 1)
				iShowImage(playerX, playerY, 70, 110, playerTwo);
			else if (playerFrame == 2)
				iShowImage(playerX, playerY, 70, 110, playerThree);
		}
		else
		{
			if (!playerEscaped)
			{
				if (playerIdleFrame == 0)
					iShowImage(playerX, playerY, 60, 80, playerImg);
				else
					iShowImage(playerX, playerY - 2, 60, 77, playerImg);
			}
		}

		if (showWpOne)
		{
			iShowImage(30, 60, 740, 120, wpOne);
		}

		if (showWpTwo && !puzzleScreen)
		{
			iShowImage(30, 60, 740, 120, wpTwo);
		}

		if (playerEscaped)
		{
			if (nextImg > 0) iShowImage(650, 30, 100, 40, nextImg);
		}

		if (puzzleScreen)
		{
			iShowImage(0, 0, 800, 600, bgTwo);

			iSetColor(255, 255, 255);

			if (showQuestion)
			{
				iText(325, 480, "Study the Patrol Pattern");
				showQuestionPattern();
			}
			else
			{
				iText(325, 440, "FIND THE 3 DIGIT CODE");

				if (solved)
				{
					iText(340, 400, "PATH IS CLEAR");
				}

				if (wrong)
				{
					iText(340, 400, "YOU WERE SPOTTED");
					iText(325, 370, "PRESS R TO TRY AGAIN");
				}
			}
		}
	}
	else if (gameState == 56) {
		if (imgEscapeScreen > 0) iShowImage(0, 0, 800, 600, imgEscapeScreen);
	}
}

void iMouseMove(int mx, int my) {}

void iPassiveMouseMove(int mx, int my)
{
	if (gameState == 100)
	{
		if (mx >= 340 && mx <= 640 && my >= 365 && my <= 415) btnHoverState = 1;
		else if (mx >= 340 && mx <= 640 && my >= 295 && my <= 345) btnHoverState = 2;
		else if (mx >= 340 && mx <= 640 && my >= 235 && my <= 285) btnHoverState = 3;
		else if (mx >= 340 && mx <= 640 && my >= 175 && my <= 225) btnHoverState = 4;
		else btnHoverState = 0;
	}
}

void iKeyboard(unsigned char key) {
	if (key == 'q' || key == 'Q' || key == 27) {
		exit(0);
	}

	// Switch Puzzle Keyboard Input (gameState 71)
	if (gameState == 71) {
		if (switchPlayerRunning) return;

		if (switchShowSequence) {
			if (key == ' ' || key == 13) {
				switchShowSequence = false;
			}
			return;
		}

		if (switchWrong) {
			if (key == ' ' || key == 'r' || key == 'R') {
				resetSwitchPuzzle();
			}
			return;
		}

		int pressed = -1;
		if (key == 'o' || key == 'O' || key == '1') pressed = 1;
		else if (key == 'f' || key == 'F' || key == '0') pressed = 0;

		if (pressed != -1) {
			if (pressed == switchSequence[switchCurrentInput]) {
				switchCurrentInput++;
				if (switchCurrentInput == 5) {
					switchSolved = true;
				}
			}
			else {
				switchWrong = true;
			}
		}
	}
}

void iSpecialKeyboard(int key) {
	// Allow right arrow movement ONLY in Common Route (gameState 70)
	if (key == GLUT_KEY_RIGHT && gameState == 70) {
		moveCharacterRight();
	}
}

#endif