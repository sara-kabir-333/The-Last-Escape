#ifndef FUNCTIONS_H
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#define FUNCTIONS_H

#include "variables.h"
#include "menu.h"
#include "iGraphics.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <mmsystem.h>

void showQuestionPattern();
void startPlayerRun();
void resetSwitchPuzzle();
void startSwitchPuzzleLevel();

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
	generateSwitchSequence();
}

void moveCharacterRight() {
	if (isGamePaused) return;
	charX += 8;
	charFrame = (charFrame + 1) % 4;

	if (gameState == 70) {
		if (charX >= 680) {
			gameState = 71;
			charX = 50;
			charY = 210;
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
	charFrame = (charFrame + 1) % 4;
	if (charX < 50) {
		charX = 50;
	}
}

void showFinalEscapeScreen() {
	gameState = 56;
	loadingStep = 0;
	if (musicPlaying) {
		mciSendString(TEXT("pause bgm"), NULL, 0, NULL);
	}
}

void startSwitchPuzzleLevel() {
	gameState = 70;
	charX = 50;
	charY = 150;
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

void loadingUpdate()
{
	if (isGamePaused) return;
	if (gameState != 0 && gameState != 5 && gameState != 6 && gameState != 56)
		return;

	loadingStep += 4;

	if (loadingStep >= 100)
	{
		loadingStep = 100;
		if (gameState == 0)
		{
			gameState = 100;
			if (musicPlaying) {
				mciSendString(TEXT("play bgm repeat"), NULL, 0, NULL);
			}
		}
		else if (gameState == 5)
		{
			gameState = 50;
			sit1Timer = 0;
			gameplayCounter = 0;
			if (musicPlaying) {
				mciSendString(TEXT("play bgm repeat"), NULL, 0, NULL);
			}
		}
		else if (gameState == 6)
		{
			gameState = 400;
			if (musicPlaying) {
				mciSendString(TEXT("play bgm repeat"), NULL, 0, NULL);
			}
		}
		else if (gameState == 56)
		{
			gameState = 300;
			level1Completed = true;
			if (musicPlaying) {
				mciSendString(TEXT("play bgm repeat"), NULL, 0, NULL);
			}
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

void fixedUpdate() {
	if (isGamePaused) return;

	if (isWaitingToRun) {
		solvedTickCounter++;
		if (solvedTickCounter >= 7) {
			isWaitingToRun = false;
			startPlayerRun();
		}
	}

	if (gameState == 70) {
		if (isKeyPressed(' ') || isSpecialKeyPressed(GLUT_KEY_RIGHT)) {
			moveCharacterRight();
			targetX = -1;
		}
		if (isSpecialKeyPressed(GLUT_KEY_LEFT) || isKeyPressed('a') || isKeyPressed('A')) {
			moveCharacterLeft();
			targetX = -1;
		}

		if (targetX != -1 && charX < targetX) {
			moveCharacterRight();
			if (charX >= targetX) {
				targetX = -1;
			}
		}
	}

	if (gameState == 71) {
		if (switchShowSequence) {
			switchTickCounter++;
			if (switchTickCounter >= 120) {
				switchShowSequence = false;
			}
			if (isKeyPressed(' ') || isKeyPressed(13)) {
				switchShowSequence = false;
			}
		}
		else if (switchWrong) {
			if (isKeyPressed(' ') || isKeyPressed('r') || isKeyPressed('R')) {
				resetSwitchPuzzle();
			}
		}
		else if (!switchSolved && !switchPlayerRunning) {
			int pressed = -1;
			if (isKeyPressed('o') || isKeyPressed('O') || isKeyPressed('1')) {
				if (switchKeyReleased) {
					switchKeyReleased = false;
					pressed = 1;
				}
			}
			else if (isKeyPressed('f') || isKeyPressed('F') || isKeyPressed('0')) {
				if (switchKeyReleased) {
					switchKeyReleased = false;
					pressed = 0;
				}
			}
			else {
				switchKeyReleased = true;
			}

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

	if (gameState == 0 || gameState == 5 || gameState == 6)
	{
		if (gameState == 0) {
			iShowImage(0, 0, 800, 600, loadBg);
		}
		else if (gameState == 5) {
			iShowImage(0, 0, 800, 600, level1Bg);
		}
		else if (gameState == 6) {
			iShowImage(0, 0, 800, 600, level2Bg);
		}

		iSetColor(180, 122, 33);
		iText(100, 120, "LOADING...", GLUT_BITMAP_TIMES_ROMAN_24);

		iRectangle(100, 80, 600, 30);
		int barWidth = (loadingStep * 600) / 100;
		iFilledRectangle(100, 80, barWidth, 30);
	}
	else if (gameState == 100)
	{
		drawMenu();
	}
	else if (gameState >= 200 && gameState <= 204)
	{
		int currentAbout = about1;
		if (gameState == 200) currentAbout = about1;
		else if (gameState == 201) currentAbout = about2;
		else if (gameState == 202) currentAbout = about3;
		else if (gameState == 203) currentAbout = about4;
		else if (gameState == 204) currentAbout = about5;

		iShowImage(0, 0, 800, 600, currentAbout);

		iShowImage(50, 50, 100, 40, backImg);
		if (gameState != 204) iShowImage(650, 50, 100, 40, nextImg);
	}
	else if (gameState == 300)
	{
		iShowImage(0, 0, 800, 600, levelBg);
		iShowImage(120, 120, 175, 342, level1Btn);

		if (level1Completed) {
			iShowImage(307, 115, 175, 342, level2UnlockedBtn);
		}
		else {
			iShowImage(307, 115, 175, 342, level2Btn);
		}

		iShowImage(492, 115, 175, 342, level3Btn);
		iShowImage(68, 26, 120, 53, backImg);
	}
	else if (gameState == 400)
	{
		iShowImage(0, 0, 800, 600, level2Bg);
		iShowImage(50, 50, 100, 40, backImg);
	}
	else if (gameState == 70)
	{
		iShowImage(0, 0, 800, 600, imgCommonRoute);
		iShowImage(charX, charY, 130, 200, imgChar[charFrame]);
		iShowImage(50, 50, 100, 40, backImg);

		if (imgnote > 0) {
			iShowImage(150, 20, 500, 120, imgnote);
		}

		iSetColor(0, 0, 0);
		iText(250, 45, "USE ARROW KEYS TO MOVE", GLUT_BITMAP_HELVETICA_10);
		iText(250, 35, "Head to the Security Control Room...", GLUT_BITMAP_HELVETICA_10);
	}
	else if (gameState == 71)
	{
		iShowImage(0, 0, 800, 600, imgCCTVBackground);
		iShowImage(charX, charY, 140, 220, imgChar[charFrame]);
		iShowImage(50, 50, 100, 40, backImg);

		if (imgnote > 0) {
			iShowImage(150, 20, 500, 120, imgnote);
		}

		if (switchShowSequence) {
			iSetColor(0, 0, 0);
			iText(250, 40, "MEMORIZE PATTERN (SPACE TO SKIP)", GLUT_BITMAP_HELVETICA_10);

			for (int i = 0; i < 5; i++) {
				char text[10];
				sprintf(text, "[%s]", switchSequence[i] == 1 ? "ON" : "OFF");
				if (switchSequence[i] == 1) iSetColor(0, 150, 0);
				else iSetColor(200, 0, 0);
				iText(220 + (i * 75), 450, text, GLUT_BITMAP_HELVETICA_18);
			}
		}
		else if (switchWrong) {
			iSetColor(255, 0, 0);
			iText(250, 40, "WRONG PATTERN! ALARM TRIGGERED", GLUT_BITMAP_HELVETICA_12);
			iSetColor(0, 0, 0);
			iText(260, 20, "PRESS SPACE OR R TO RETRY", GLUT_BITMAP_HELVETICA_10);
		}
		else if (switchSolved) {
			iSetColor(0, 180, 0);
			iText(270, 40, "CCTV CAMERA DISABLED!", GLUT_BITMAP_HELVETICA_12);
			iSetColor(0, 0, 0);
			iText(310, 20, "ESCAPE NOW!", GLUT_BITMAP_HELVETICA_10);
		}
		else {
			iSetColor(0, 0, 0);
			iText(250, 40, "PRESS O FOR 'ON' / F FOR 'OFF'", GLUT_BITMAP_HELVETICA_10);

			for (int i = 0; i < 5; i++) {
				if (i < switchCurrentInput) {
					iSetColor(0, 180, 0);
					iText(230 + (i * 75), 450, "[OK]", GLUT_BITMAP_HELVETICA_18);
				}
				else {
					iSetColor(100, 100, 100);
					iText(230 + (i * 75), 450, "[ ? ]", GLUT_BITMAP_HELVETICA_18);
				}
			}
		}
	}
	else if (gameState == 50) {
		if (imgsit1 > 0) iShowImage(0, 0, 800, 600, imgsit1);
		iShowImage(50, 50, 100, 40, backImg);
	}
	else if (gameState == 51) {
		if (imgsit2 > 0) iShowImage(0, 0, 800, 600, imgsit2);
		if (imgnote > 0) iShowImage(150, 20, 500, 120, imgnote);
		iShowImage(50, 50, 100, 40, backImg);
		iSetColor(0, 0, 0);
		iText(250, 40, "click on screen to move forward");
	}
	else if (gameState == 52) {
		if (imgBackground > 0) iShowImage(0, 0, 800, 600, imgBackground);
		if (imgnote > 0) iShowImage(150, 20, 500, 120, imgnote);
		iShowImage(50, 50, 100, 40, backImg);
		iSetColor(0, 0, 0);
		iText(250, 40, "click anywhere to break the lock");
	}
	else if (gameState == 53 || gameState == 54 || gameState == 57) {
		if (imgLockScreen > 0) iShowImage(0, 0, 800, 600, imgLockScreen);
		if (imgnote > 0) iShowImage(150, 20, 500, 120, imgnote);
		iShowImage(50, 50, 100, 40, backImg);

		iSetColor(0, 0, 0);
		if (gameState == 53) iText(250, 40, "memorize the sequence...");
		else if (gameState == 54) iText(250, 40, "your turn: click the boxes");
		else if (gameState == 57) iText(250, 40, "wrong! click anywhere to retry");

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

		if (gameState == 53 && activeDisplayColor == 4) iSetColor(180, 255, 255);
		else iSetColor(0, 255, 255);
		iFilledRectangle(cyanX, cyanY, boxSize, boxSize);

		if (gameState == 53 && activeDisplayColor == 5) iSetColor(255, 180, 255);
		else iSetColor(255, 0, 255);
		iFilledRectangle(magentaX, magentaY, boxSize, boxSize);

		if (gameState == 53 && activeDisplayColor == 6) iSetColor(255, 210, 150);
		else iSetColor(255, 128, 0);
		iFilledRectangle(orangeX, orangeY, boxSize, boxSize);
	}
	else if (gameState == 55) {
		if (imgLockScreen > 0) iShowImage(0, 0, 800, 600, imgLockScreen);
		if (imgnote > 0) iShowImage(150, 20, 500, 120, imgnote);
		iShowImage(50, 50, 100, 40, backImg);

		if (playerImg > 0) iShowImage(530, 180, 140, 180, playerImg);
		if (nextImg > 0) iShowImage(600, 50, 100, 40, nextImg);

		iSetColor(0, 0, 0);
		iText(180, 70, "lock unlocked! click next");
	}
	else if (gameState == 60)
	{
		iShowImage(0, 0, 800, 600, bgOne);
		iShowImage(50, 50, 100, 40, backImg);

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

		iSetColor(180, 122, 33);
		iText(100, 120, "LOADING...", GLUT_BITMAP_TIMES_ROMAN_24);

		iRectangle(100, 80, 600, 30);
		int barWidth = (loadingStep * 600) / 100;
		iFilledRectangle(100, 80, barWidth, 30);
	}

	if (gameState == 100 || gameState == 300 || gameState == 400 || gameState == 70 || gameState == 71 || ((gameState >= 50 && gameState <= 60) && gameState != 56))
	{
		if (settingsImg > 0) {
			iShowImage(20, 520, 50, 50, settingsImg);
		}

		if (showSettingsPanel && settingsOnImg > 0) {
			iShowImage(20, 375, 290, 135, settingsOnImg);

			if (musicPlaying && on1 > 0) {
				iShowImage(199, 450, 100, 38, on1);
			}
			else if (!musicPlaying && off1 > 0) {
				iShowImage(199, 450, 100, 38, off1);
			}

			if (soundEnabled && on2 > 0) {
				iShowImage(199, 400, 100, 38, on2);
			}
			else if (!soundEnabled && off2 > 0) {
				iShowImage(199, 400, 100, 38, off2);
			}
		}
	}

	if (gameState == 70 || gameState == 71 || ((gameState >= 50 && gameState <= 60) && gameState != 56))
	{
		if (isGamePaused) {
			if (pauseToPlayImg > 0) {
				iShowImage(74, 509, 60, 70, pauseToPlayImg);
			}
		}
		else {
			if (pauseImg > 0) {
				iShowImage(74, 509, 60, 70, pauseImg);
			}
		}
	}
}

void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (soundEnabled) {
			mciSendString(TEXT("seek clicksound to start"), NULL, 0, NULL);
			mciSendString(TEXT("play clicksound"), NULL, 0, NULL);
		}

		if (gameState == 100 || gameState == 300 || gameState == 400 || gameState == 70 || gameState == 71 || ((gameState >= 50 && gameState <= 60) && gameState != 56))
		{
			if (mx >= 20 && mx <= 70 && my >= 520 && my <= 570)
			{
				showSettingsPanel = !showSettingsPanel;
				return;
			}

			if (showSettingsPanel)
			{
				if (mx >= 20 && mx <= 310 && my >= 375 && my <= 510)
				{
					if (mx >= 220 && mx <= 300 && my >= 460 && my <= 495)
					{
						musicPlaying = !musicPlaying;
						if (musicPlaying) {
							mciSendString(TEXT("resume bgm"), NULL, 0, NULL);
						}
						else {
							mciSendString(TEXT("pause bgm"), NULL, 0, NULL);
						}
					}
					else if (mx >= 220 && mx <= 300 && my >= 415 && my <= 450)
					{
						soundEnabled = !soundEnabled;
					}
					return;
				}
				else
				{
					showSettingsPanel = false;
				}
			}
		}

		if (gameState == 70 || gameState == 71 || ((gameState >= 50 && gameState <= 60) && gameState != 56))
		{
			if (mx >= 78 && mx <= 132 && my >= 518 && my <= 572)
			{
				isGamePaused = !isGamePaused;
				if (isGamePaused) {
					if (musicPlaying) {
						mciSendString(TEXT("pause bgm"), NULL, 0, NULL);
					}
				}
				else {
					if (musicPlaying) {
						mciSendString(TEXT("resume bgm"), NULL, 0, NULL);
					}
				}
				return;
			}
		}

		if (isGamePaused) return;

		if (gameState == 400 || gameState == 50 || gameState == 51 || gameState == 52 || gameState == 53 || gameState == 54 || gameState == 57 || gameState == 55 || gameState == 60 || gameState == 70 || gameState == 71)
		{
			if (mx >= 50 && mx <= 150 && my >= 50 && my <= 90)
			{
				gameState = 300;
				return;
			}
		}

		if (gameState == 71) {
			if (switchShowSequence) {
				switchShowSequence = false;
				return;
			}
			if (switchWrong) {
				resetSwitchPuzzle();
				return;
			}
			if (switchSolved) {
				return;
			}
		}

		if (gameState == 100)
		{
			handleMenuMouse(mx, my);
		}
		else if (gameState >= 200 && gameState <= 204)
		{
			if (mx >= 50 && mx <= 150 && my >= 50 && my <= 90)
			{
				if (gameState == 200) gameState = 100;
				else gameState--;
			}
			else if (mx >= 650 && mx <= 750 && my >= 50 && my <= 90 && gameState != 204)
			{
				gameState++;
			}
		}
		else if (gameState == 300)
		{
			if (mx >= 68 && mx <= 188 && my >= 26 && my <= 79)
			{
				gameState = 100;
			}
			else if (mx >= 120 && mx <= 295 && my >= 120 && my <= 462)
			{
				resetLevel1();
				gameState = 5;
				loadingStep = 0;
				if (musicPlaying) {
					mciSendString(TEXT("pause bgm"), NULL, 0, NULL);
				}
			}
			else if (mx >= 307 && mx <= 482 && my >= 115 && my <= 457)
			{
				gameState = 6;
				loadingStep = 0;
				if (musicPlaying) {
					mciSendString(TEXT("pause bgm"), NULL, 0, NULL);
				}
			}
		}
		else if (gameState == 51) {
			gameState = 52;
			return;
		}
		else if (gameState == 52) {
			createSequence();
			return;
		}
		else if (gameState == 57) {
			inputIndex = 0;
			createSequence();
			return;
		}
		else if (gameState == 55) {
			if (mx >= 600 && mx <= 700 && my >= 50 && my <= 90) {
				gameState = 60;
				gameplayCounter = 0;
				showWpOne = true;
				showWpTwo = false;
			}
			return;
		}
		else if (gameState == 60 && playerEscaped) {
			if (mx >= 650 && mx <= 750 && my >= 30 && my <= 70) {
				startSwitchPuzzleLevel();
			}
			return;
		}
		else if (gameState == 56) {
			return;
		}

		if (gameState == 54) {
			int clicked = -1;
			if (mx >= redX && mx <= redX + boxSize && my >= redY && my <= redY + boxSize) clicked = 0;
			else if (mx >= blueX && mx <= blueX + boxSize && my >= blueY && my <= blueY + boxSize) clicked = 1;
			else if (mx >= greenX && mx <= greenX + boxSize && my >= greenY && my <= greenY + boxSize) clicked = 2;
			else if (mx >= yellowX && mx <= yellowX + boxSize && my >= yellowY && my <= yellowY + boxSize) clicked = 3;
			else if (mx >= cyanX && mx <= cyanX + boxSize && my >= cyanY && my <= cyanY + boxSize) clicked = 4;
			else if (mx >= magentaX && mx <= magentaX + boxSize && my >= magentaY && my <= magentaY + boxSize) clicked = 5;
			else if (mx >= orangeX && mx <= orangeX + boxSize && my >= orangeY && my <= orangeY + boxSize) clicked = 6;

			if (clicked != -1) {
				playerInput[inputIndex] = clicked;
				if (playerInput[inputIndex] != sequence[inputIndex]) {
					gameState = 57;
					return;
				}
				inputIndex++;
				if (inputIndex == level) {
					gameState = 55;
					inputIndex = 0;
				}
			}
		}
	}
}

void iMouseMove(int mx, int my) {}

void iPassiveMouseMove(int mx, int my)
{
	if (gameState == 100)
	{
		handleMenuPassiveMouse(mx, my);
	}
}

void iKeyboard(unsigned char key) {
	if (key == 'q' || key == 'Q' || key == 27) {
		exit(0);
	}

	if (isGamePaused) return;

	if (gameState == 70) {
		if (key == ' ') {
			moveCharacterRight();
		}
		else if (key == 'a' || key == 'A') {
			moveCharacterLeft();
		}
	}

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
	if (isGamePaused) return;
	if (gameState == 70 || gameState == 71) {
		if (key == GLUT_KEY_RIGHT) {
			moveCharacterRight();
		}
		else if (key == GLUT_KEY_LEFT) {
			moveCharacterLeft();
		}
	}
}

#endif