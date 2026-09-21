#define _CRT_SECURE_NO_WARNINGS
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "iGraphics.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <mmsystem.h>
#include <stdlib.h>
#pragma comment(lib, "winmm.lib")

#include "Menu.h"
#include "Level1Variables.h"
#include "Level2Variables.h"
#include "Level3Variables.h"
#include "Level1Functions.h"
#include "Level2Functions.h"
#include "Level3Functions.h"
#include "SaveSystem.h"

bool isLoadingState(int gs) {
	return gs == 0 || gs == 5 || gs == 6 || gs == 56 || gs == 57 ||
		gs == GAMESTATE_VR_WIN_LOADING || gs == GAMESTATE_LEVEL3_LOADING ||
		gs == GAMESTATE_TRAFFIC_LOADING;
}

bool isNoteScreenState(int gs) {
	return gs == GAMESTATE_DODGE_NOTE || gs == GAMESTATE_LEVEL2_NOTE ||
		gs == GAMESTATE_USB_NOTE || gs == GAMESTATE_INVEST_NOTE ||
		gs == GAMESTATE_GUNCOLLECT_NOTE || gs == GAMESTATE_LEVEL1_NOTE;
}

bool isSettingsVisibleState(int gs) {
	
	return !isLoadingState(gs);
}

bool isPauseVisibleState(int gs) {
	if (isLoadingState(gs)) return false;
	if (isNoteScreenState(gs)) return false;

	return gs == 70 || gs == 71 ||
		(gs >= 50 && gs <= 60 && gs != 56 && gs != 57) ||
		gs == GAMESTATE_DODGE || gs == 400 ||
		gs == GAMESTATE_VAULT_RUNNER || gs == GAMESTATE_INVESTIGATION ||
		gs == GAMESTATE_LEVEL3_FIGHT ||
		(gs == GAMESTATE_LEVEL3_SHOOTOUT && gsState != -1) ||
		(gs == GAMESTATE_TRAFFIC && trGameStarted);
}

void loadingUpdate()
{
	if (isGamePaused) return;
	if (gameState != 0 && gameState != 5 && gameState != 6 && gameState != 56 && gameState != 57 &&
		gameState != GAMESTATE_VR_WIN_LOADING && gameState != GAMESTATE_LEVEL3_LOADING &&
		gameState != GAMESTATE_TRAFFIC_LOADING)
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
			gameState = GAMESTATE_LEVEL1_NOTE;
			loadingStep = 0;
			if (musicPlaying) {
				mciSendString(TEXT("play bgm repeat"), NULL, 0, NULL);
			}
		}
		else if (gameState == 6)
		{
			gameState = GAMESTATE_LEVEL2_NOTE;
			loadingStep = 0;
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
		else if (gameState == 57)
		{
			gameState = 300;
			loadingStep = 0;
			if (musicPlaying) {
				mciSendString(TEXT("play bgm repeat"), NULL, 0, NULL);
			}
		}
		else if (gameState == GAMESTATE_VR_WIN_LOADING)
		{
			gameState = 300;
			loadingStep = 0;
			level2Completed = true;
			if (musicPlaying) {
				mciSendString(TEXT("play bgm repeat"), NULL, 0, NULL);
			}
		}
		else if (gameState == GAMESTATE_LEVEL3_LOADING)
		{
			gameState = GAMESTATE_GUNCOLLECT_NOTE;
			loadingStep = 0;
			if (musicPlaying) {
				mciSendString(TEXT("play bgm repeat"), NULL, 0, NULL);
			}
		}
		else if (gameState == GAMESTATE_TRAFFIC_LOADING)
		{
			gameState = 300;
			loadingStep = 0;
			if (musicPlaying) {
				mciSendString(TEXT("play bgm repeat"), NULL, 0, NULL);
			}
		}
	}
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
			if (switchTickCounter >= 270) {
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
			charFrame = (charFrame + 1) % 3;
			if (charX > 850) {
				switchPlayerRunning = false;
				switchPuzzleCompleted = true;
				gameState = 350;
				if (musicPlaying) {
					mciSendString(TEXT("play bgm repeat"), NULL, 0, NULL);
				}
			}
		}
	}

	if (gameState == 60)
	{
		if (!wrong) {
			guardAnimation();
			guardMove();
		}
		playerRunAnimation();

		if (!levelFinished && !puzzleScreen)
		{
			gameplayCounter++;
			if (gameplayCounter == 25)
			{
				hideFirstMessage();
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

		if (puzzleScreen && showQuestion)
		{
			if ((clock() - questionStartTime) / CLOCKS_PER_SEC >= L1_QUESTION_SECONDS)
			{
				showQuestion = false;
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
					puzzleScreen = false;
					digitReleased = true;
				}
			}
		}
	}

	if (gameState == GAMESTATE_DODGE)
	{
		updateDodgeGame();

		bool isMovingRight = false;
		bool isMovingLeft = false;

		if (dodgeGameStarted && !dodgeGameOver && !dodgeLevelComplete)
		{
			if (isSpecialKeyPressed(GLUT_KEY_LEFT))
			{
				dodgePlayerX -= dodgePlayerSpeed;
				if (dodgePlayerX < -320)
					dodgePlayerX = -320;

				isMovingLeft = true;
				dodgeAnimTimer++;
				if ((dodgeAnimTimer / 5) % 2 == 0) dodgeCurrentAnimState = 1;
				else dodgeCurrentAnimState = 2;
			}

			if (isSpecialKeyPressed(GLUT_KEY_RIGHT))
			{
				dodgePlayerX += dodgePlayerSpeed;
				if (dodgePlayerX + 320 + dodgeActualPlayerWidth > 800)
					dodgePlayerX = 800 - 250 - dodgeActualPlayerWidth;

				isMovingRight = true;
				dodgeAnimTimer++;

				int frame = (dodgeAnimTimer / 6) % 3;
				if (frame == 0) dodgeCurrentAnimState = 0;
				else if (frame == 1) dodgeCurrentAnimState = 3;
				else dodgeCurrentAnimState = 4;
			}
		}

		if (!isMovingRight && !isMovingLeft)
		{
			if (dodgeAnimTimer > 0)
			{
				dodgeAnimTimer--;
				if (dodgeAnimTimer == 0)
				{
					dodgeCurrentAnimState = 0;
				}
			}
		}
	}

	if (gameState == GAMESTATE_VAULT_RUNNER)
	{
		vrFixedUpdate();
	}

	if (gameState == GAMESTATE_LEVEL3_FIGHT)
	{
		lv3UpdateGame();
	}

	if (gameState == GAMESTATE_LEVEL3_SHOOTOUT)
	{
		gsUpdateGame();
	}
}

void iDraw()
{
	iClear();
	iSetColor(0, 0, 0);
	iFilledRectangle(0, 0, 800, 600);

	if (gameState == 0 || gameState == 5 || gameState == 6 || gameState == 57 ||
		gameState == GAMESTATE_VR_WIN_LOADING || gameState == GAMESTATE_LEVEL3_LOADING ||
		gameState == GAMESTATE_TRAFFIC_LOADING)
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
		else if (gameState == 57) {
			iShowImage(0, 0, 800, 600, imgEscapeScreen);
		}
		else if (gameState == GAMESTATE_VR_WIN_LOADING) {
			iShowImage(0, 0, 800, 600, vrWinBgImg);
		}
		else if (gameState == GAMESTATE_LEVEL3_LOADING) {
			iShowImage(0, 0, 800, 600, level3BgImg);
		}
		else if (gameState == GAMESTATE_TRAFFIC_LOADING) {
			iShowImage(0, 0, 800, 600, trFinalBgImg);
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
	else if (gameState == 210)
	{
		if (creditnoteImg > 0) iShowImage(0, 0, 800, 600, creditnoteImg);
		if (backImg > 0) iShowImage(50, 50, 100, 40, backImg);
	}
	else if (gameState == GAMESTATE_SAVE_CHOICE)
	{
		drawSaveChoice();
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

		if (level2Completed) {
			iShowImage(492, 115, 175, 342, level3UnlockedBtn);
		}
		else {
			iShowImage(492, 115, 175, 342, level3Btn);
		}
		iShowImage(68, 26, 120, 53, backImg);
	}
	else if (gameState == GAMESTATE_LEVEL1_NOTE)
	{
		if (map1Img > 0) iShowImage(0, 0, 800, 600, map1Img);
		if (cellMapImg > 0) iShowImage(150, 80, 480, 150, cellMapImg);
		if (cctvMapImg > 0) iShowImage(62, 335, 200, 228, cctvMapImg);
		if (alarmMapImg > 0) iShowImage(530, 333, 200, 228, alarmMapImg);

		if (introImg > 0) iShowImage(150, 150, 500, 300, introImg);
		if (nextImg > 0) iShowImage(650, 50, 100, 40, nextImg);
	}
	else if (gameState == 350)
	{
		if (map1Img > 0) iShowImage(0, 0, 800, 600, map1Img);
		if (cctvUnlocked) {
			if (cellMap2Img > 0) iShowImage(150, 80, 480, 150, cellMap2Img);
		}
		else {
			if (cellMapImg > 0) iShowImage(150, 80, 480, 150, cellMapImg);
		}
		if (cctvMapImg > 0) iShowImage(62, 335, 200, 228, cctvMapImg);
		if (alarmMapImg > 0) iShowImage(530, 333, 200, 228, alarmMapImg);

		if (backImg > 0) iShowImage(50, 50, 100, 40, backImg);
	}
	else if (gameState == 400)
	{
		usbDrawGame();
	}
	else if (gameState == 70)
	{
		if (imgCommonRoute > 0) {
			iShowImage(0, 0, 800, 600, imgCommonRoute);
		}

		int currentAvatar = playerOne;
		if (charFrame == 1) currentAvatar = playerTwo;
		else if (charFrame == 2) currentAvatar = playerThree;

		iShowImage(charX, charY, 130, 200, currentAvatar);
		iShowImage(50, 50, 100, 40, backImg);

		if (imgnote > 0) {
			iShowImage(150, 20, 500, 200, imgnote);
		}

		iSetColor(0, 0, 0);
		iText(260, 65, "USE ARROW KEYS TO MOVE", GLUT_BITMAP_HELVETICA_18);
		iText(250, 50, "Head to the Security Control Room...", GLUT_BITMAP_HELVETICA_18);
	}
	else if (gameState == 71)
	{
		if (imgCCTVBackground > 0) {
			iShowImage(0, 0, 800, 600, imgCCTVBackground);
		}

		int currentAvatar = playerOne;
		if (charFrame == 1) currentAvatar = playerTwo;
		else if (charFrame == 2) currentAvatar = playerThree;

		iShowImage(charX, charY, 140, 220, currentAvatar);
		iShowImage(50, 50, 100, 40, backImg);

		if (imgnote > 0) {
			iShowImage(150, 20, 500, 200, imgnote);
		}

		if (switchShowSequence) {
			iSetColor(0, 0, 0);
			iText(255, 60, "MEMORIZE PATTERN........... ", GLUT_BITMAP_HELVETICA_18);

			for (int i = 0; i < 5; i++) {
				char text[10];
				sprintf(text, "[%s]", switchSequence[i] == 1 ? "ON" : "OFF");
				if (switchSequence[i] == 1) iSetColor(0, 150, 0);
				else iSetColor(200, 0, 0);
				iText(220 + (i * 75), 450, text, GLUT_BITMAP_HELVETICA_18);
			}
		}
		else if (switchWrong) {
			iSetColor(0, 0, 0);
			iText(245, 65, "WRONG PATTERN! ALARM TRIGGERED", GLUT_BITMAP_HELVETICA_18);
			iSetColor(0, 0, 0);
			iText(245, 50, "PRESS SPACE OR R TO RETRY", GLUT_BITMAP_HELVETICA_18);
		}
		else if (switchSolved) {
			iSetColor(0, 0, 0);
			iText(250, 65, "CCTV CAMERA DISABLED!", GLUT_BITMAP_HELVETICA_18);
			iSetColor(0, 0, 0);
			iText(250, 50, "ESCAPE NOW!", GLUT_BITMAP_HELVETICA_18);
		}
		else {
			iSetColor(0, 0, 0);
			iText(250, 60, "PRESS O FOR 'ON' / F FOR 'OFF'", GLUT_BITMAP_HELVETICA_18);

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
		if (imgnote > 0) iShowImage(150, 20, 500, 200, imgnote);
		iShowImage(50, 50, 100, 40, backImg);
		iSetColor(0, 0, 0);
		iText(300, 60, "CLICK ANYWHERE TO START", GLUT_BITMAP_HELVETICA_18);
	}
	else if (gameState == 52) {
		if (imgBackground > 0) iShowImage(0, 0, 800, 600, imgBackground);
		if (imgnote > 0) iShowImage(150, 20, 500, 200, imgnote);
		iShowImage(50, 50, 100, 40, backImg);
		iSetColor(0, 0, 0);
		iText(250, 60, "click anywhere to break the lock");
	}
	else if (gameState == 53 || gameState == 54) {
		if (imgLockScreen > 0) iShowImage(0, 0, 800, 600, imgLockScreen);
		if (imgnote > 0) iShowImage(150, 20, 500, 200, imgnote);
		iShowImage(50, 50, 100, 40, backImg);

		iSetColor(0, 0, 0);
		if (memoryWrong) {
			
			iSetColor(0, 0, 0);
			iText(230, 65, "WRONG SEQUENCE!", GLUT_BITMAP_HELVETICA_18);
			iSetColor(0, 0, 0);
			iText(230, 50, "CLICK ANYWHERE TO RETRY", GLUT_BITMAP_HELVETICA_18);
		}
		else if (gameState == 53) {
			iText(250, 60, "memorize the sequence...", GLUT_BITMAP_HELVETICA_18);
		}
		else if (gameState == 54) {
			iText(250, 60, "your turn: click the boxes", GLUT_BITMAP_HELVETICA_18);
		}

		if (!memoryWrong) {
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
	}
	else if (gameState == 55) {
		if (imgLockScreen > 0) iShowImage(0, 0, 800, 600, imgLockScreen);
		if (imgnote > 0) iShowImage(150, 20, 500, 200, imgnote);
		iShowImage(50, 50, 100, 40, backImg);

		if (playerImg > 0) iShowImage(530, 180, 140, 180, playerImg);
		if (nextImg > 0) iShowImage(600, 50, 100, 40, nextImg);

		iSetColor(0, 0, 0);
		iText(250, 60, "lock unlocked! click next");
	}
	else if (gameState == 60)
	{
		iShowImage(0, 0, 800, 600, bgOne);
		iShowImage(50, 50, 100, 40, backImg);

		if (wrong)
		{
			int totalWidth = 50 + 60;
			int startX = (800 - totalWidth) / 2;

			iShowImage(startX, L1_CAUGHT_GUARD_Y, L1_CAUGHT_GUARD_W, L1_CAUGHT_GUARD_H, guard6);
			iShowImage(startX + 50, L1_CAUGHT_PLAYER_Y, L1_CAUGHT_PLAYER_W, L1_CAUGHT_PLAYER_H, caughtPlayer);

			if (imgnote > 0) {
				iShowImage(150, 20, 500, 200, imgnote);
			}

			iSetColor(0, 0, 0);
			iText(265, 65, "YOU WERE SPOTTED", GLUT_BITMAP_HELVETICA_18);
			iText(230, 50, "CLICK ANYWHERE TO START OVER", GLUT_BITMAP_HELVETICA_18);
		}
		else
		{
			if (moveRight)
			{
				if (guardFrame == 0 || guardFrame == 2)
					iShowImage(guardX, guardY, L1_GUARD_W, L1_GUARD_H, guard1);
				else if (guardFrame == 1)
					iShowImage(guardX, guardY, L1_GUARD_W, L1_GUARD_H, guard3);
			}
			else
			{
				if (guardFrame == 0 || guardFrame == 2)
					iShowImage(guardX, guardY, L1_GUARD_W, L1_GUARD_H, guard4);
				else if (guardFrame == 1)
					iShowImage(guardX, guardY, L1_GUARD_W, L1_GUARD_H, guard5);
			}

			if (playerRunning)
			{
				if (playerFrame == 0)
					iShowImage(playerX, playerY, L1_PLAYER_RUN_W, L1_PLAYER_RUN_H, playerOne);
				else if (playerFrame == 1)
					iShowImage(playerX, playerY, L1_PLAYER_RUN_W, L1_PLAYER_RUN_H, playerTwo);
				else if (playerFrame == 2)
					iShowImage(playerX, playerY, L1_PLAYER_RUN_W, L1_PLAYER_RUN_H, playerThree);
			}
			else
			{
				if (!playerEscaped)
				{
					iShowImage(playerX, playerY, L1_PLAYER_STAND_W, L1_PLAYER_STAND_H, playerImg);
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

				if (imgnote > 0) {
					iShowImage(150, 20, 500, 200, imgnote);
				}

				iSetColor(0, 0, 0);

				if (showQuestion)
				{
					iText(260, 60, "Study the Patrol Pattern", GLUT_BITMAP_HELVETICA_18);
					showQuestionPattern();
				}
				else
				{
					if (solved)
					{
						iText(265, 60, "PATH IS CLEAR", GLUT_BITMAP_HELVETICA_18);
					}
					else
					{
						iText(260, 60, "FIND THE 3 DIGIT CODE", GLUT_BITMAP_HELVETICA_18);
					}
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
	else if (gameState == GAMESTATE_DODGE)
	{
		drawDodgeGame();
	}
	else if (gameState == GAMESTATE_LEVEL2_MAP)
	{
		if (level2MapImg > 0) iShowImage(0, 0, 800, 600, level2MapImg);
		if (vaultUnlocked && vaultImg > 0) {
			iShowImage(154, 57, 204, 193, vaultImg);
		}
		if (backImg > 0) iShowImage(50, 50, 100, 40, backImg);
	}
	else if (gameState == GAMESTATE_INVESTIGATION)
	{
		drawInvestPuzzle();
	}
	else if (gameState == GAMESTATE_VAULT_RUNNER)
	{
		vrDraw();
	}
	else if (gameState == GAMESTATE_DODGE_NOTE)
	{
		if (dodgeBgImg > 0) iShowImage(0, 0, 800, 600, dodgeBgImg);
		if (dodgeIntroNoteImg > 0) iShowImage(130, 150, 500, 280, dodgeIntroNoteImg);
		if (nextImg > 0) iShowImage(650, 50, 100, 40, nextImg);
	}
	else if (gameState == GAMESTATE_LEVEL2_NOTE)
	{
		if (level2MapImg > 0) iShowImage(0, 0, 800, 600, level2MapImg);
		if (level2NoteImg > 0) iShowImage(150, 150, 500, 200, level2NoteImg);
		if (nextImg > 0) iShowImage(650, 50, 100, 40, nextImg);
	}
	else if (gameState == GAMESTATE_USB_NOTE)
	{
		if (usbImgBg > 0) iShowImage(0, 0, 800, 600, usbImgBg);
		else iShowImage(0, 0, 800, 600, level2Bg);
		if (usbNoteImg > 0) iShowImage(50, 200, 700, 180, usbNoteImg);
		if (nextImg > 0) iShowImage(650, 50, 100, 40, nextImg);
	}
	else if (gameState == GAMESTATE_INVEST_NOTE)
	{
		if (investRoomImg > 0) iShowImage(0, 0, 800, 600, investRoomImg);
		if (evidenceRoomNoteImg > 0) iShowImage(150, 150, 480, 280, evidenceRoomNoteImg);
		if (nextImg > 0) iShowImage(650, 50, 100, 40, nextImg);
	}
	else if (gameState == GAMESTATE_GUNCOLLECT_NOTE)
	{
		if (lv3BgImageId > 0) iShowImage(0, 0, 800, 600, lv3BgImageId);
		else if (level3BgImg > 0) iShowImage(0, 0, 800, 600, level3BgImg);
		if (gunCollectImg > 0) iShowImage(150, 150, 480, 280, gunCollectImg);
		if (nextImg > 0) iShowImage(650, 50, 100, 40, nextImg);
	}
	else if (gameState == GAMESTATE_LEVEL3_FIGHT)
	{
		lv3Draw();
	}
	else if (gameState == GAMESTATE_LEVEL3_SHOOTOUT)
	{
		gsDraw();
	}
	else if (gameState == GAMESTATE_TRAFFIC)
	{
		trDraw();
	}

	if (isSettingsVisibleState(gameState))
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

	if (isPauseVisibleState(gameState))
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

		if (isSettingsVisibleState(gameState))
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

		if (isPauseVisibleState(gameState))
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

		if (gameState == GAMESTATE_SAVE_CHOICE)
		{
			svChoiceMouseClick(mx, my);
			return;
		}

		if (gameState == GAMESTATE_LEVEL1_NOTE)
		{
			if (mx >= 650 && mx <= 750 && my >= 50 && my <= 90)
			{
				gameState = 350;
			}
			return;
		}

		if (gameState == GAMESTATE_DODGE_NOTE)
		{
			if (mx >= 650 && mx <= 750 && my >= 50 && my <= 90)
			{
				resetDodgeGame();
				gameState = GAMESTATE_DODGE;
			}
			return;
		}

		if (gameState == GAMESTATE_LEVEL2_NOTE)
		{
			if (mx >= 650 && mx <= 750 && my >= 50 && my <= 90)
			{
				gameState = GAMESTATE_LEVEL2_MAP;
			}
			return;
		}

		if (gameState == GAMESTATE_USB_NOTE)
		{
			if (mx >= 650 && mx <= 750 && my >= 50 && my <= 90)
			{
				gameState = 400;
				usbInitGame();
			}
			return;
		}

		if (gameState == GAMESTATE_INVEST_NOTE)
		{
			if (mx >= 650 && mx <= 750 && my >= 50 && my <= 90)
			{
				resetInvestPuzzle();
				gameState = GAMESTATE_INVESTIGATION;
			}
			return;
		}

		if (gameState == GAMESTATE_GUNCOLLECT_NOTE)
		{
			if (mx >= 650 && mx <= 750 && my >= 50 && my <= 90)
			{
				lv3RestartGame();
				gameState = GAMESTATE_LEVEL3_FIGHT;
			}
			return;
		}

		if (gameState == GAMESTATE_LEVEL3_FIGHT)
		{
			lv3HandleMouseDown(mx, my);
			return;
		}

		if (gameState == GAMESTATE_LEVEL3_SHOOTOUT)
		{
			if (mx >= 50 && mx <= 150 && my >= 50 && my <= 90)
			{
				gameState = 300;
				return;
			}
			gsHandleLeftClick(mx, my);
			return;
		}

		if (gameState == GAMESTATE_TRAFFIC)
		{
			trHandleMouseDown(mx, my);
			return;
		}

		if (gameState == 60 && wrong)
		{
			resetLevel1();
			gameState = 50;
			sit1Timer = 0;
			return;
		}

		if (gameState == 50 || gameState == 51 || gameState == 52 || gameState == 53 || gameState == 54 || gameState == 55 || gameState == 60 || gameState == 70 || gameState == 71)
		{
			if (mx >= 50 && mx <= 150 && my >= 50 && my <= 90)
			{
				gameState = 350;
				return;
			}
		}

		if (gameState == 400)
		{
			if (mx >= 50 && mx <= 150 && my >= 50 && my <= 90)
			{
				gameState = GAMESTATE_LEVEL2_MAP;
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

		if (memoryWrong) {
			memoryWrong = false;
			inputIndex = 0;
			createSequence();
			return;
		}

		if (gameState == GAMESTATE_DODGE)
		{
			if (mx >= 50 && mx <= 150 && my >= 50 && my <= 90)
			{
				gameState = 350;
				return;
			}

			handleDodgeMouseClick(mx, my);
			return;
		}

		if (gameState == GAMESTATE_LEVEL2_MAP)
		{
			if (mx >= 50 && mx <= 150 && my >= 50 && my <= 90)
			{
				gameState = 300;
				return;
			}
			else if (mx >= 15 && mx <= 240 && my >= 320 && my <= 590)
			{
				gameState = GAMESTATE_USB_NOTE;
				return;
			}
			else if (mx >= 320 && mx <= 480 && my >= 350 && my <= 550)
			{
				gameState = GAMESTATE_INVEST_NOTE;
				return;
			}
			else if (vaultUnlocked && mx >= 154 && mx <= 362 && my >= 56 && my <= 253)
			{
				vrResetGame();
				gameState = GAMESTATE_VAULT_RUNNER;
				return;
			}
			return;
		}

		if (gameState == GAMESTATE_INVESTIGATION)
		{
			handleInvestMouseDown(mx, my);
			return;
		}

		if (gameState == GAMESTATE_VAULT_RUNNER)
		{
			vrHandleMouseDown(mx, my);
			return;
		}

		if (gameState == 100)
		{
			handleMenuMouse(mx, my);

			if (gameState == 300 && svHasSave())
			{
				gameState = GAMESTATE_SAVE_CHOICE;
			}
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
		else if (gameState == 210)
		{
			if (mx >= 50 && mx <= 150 && my >= 50 && my <= 90)
			{
				gameState = 100;
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
				if (level1Completed) {
					vaultUnlocked = false;
					gameState = 6;
					loadingStep = 0;
					if (musicPlaying) {
						mciSendString(TEXT("pause bgm"), NULL, 0, NULL);
					}
				}
			}
			else if (mx >= 492 && mx <= 667 && my >= 115 && my <= 457)
			{
				if (level2Completed) {
					gameState = GAMESTATE_LEVEL3_LOADING;
					loadingStep = 0;
					if (musicPlaying) {
						mciSendString(TEXT("pause bgm"), NULL, 0, NULL);
					}
				}
			}
		}
		else if (gameState == 350)
		{
			if (mx >= 50 && mx <= 150 && my >= 50 && my <= 90)
			{
				gameState = 300;
				return;
			}
			else if (mx >= 150 && mx <= 650 && my >= 20 && my <= 270)
			{
				if (!cctvUnlocked)
				{
					resetLevel1();
					gameState = 50;
					sit1Timer = 0;
				}
				return;
			}
			else if (mx >= 35 && mx <= 285 && my >= 310 && my <= 570)
			{
				if (cctvUnlocked) {
					gameState = 70;
					charX = 50;
					charY = 150;
					charFrame = 0;
					targetX = -1;
				}
				return;
			}
			else if (mx >= 530 && mx <= 730 && my >= 333 && my <= 561)
			{
				if (switchPuzzleCompleted && cctvUnlocked && !level1Completed) {
					gameState = GAMESTATE_DODGE_NOTE;
				}
				return;
			}
		}
		else if (gameState == 400)
		{
			usbHandleMouseClick(mx, my);
		}
		else if (gameState == 51) {
			createSequence();
			return;
		}
		else if (gameState == 52) {
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
				cctvUnlocked = true;
				gameState = 350;
			}
			return;
		}
		else if (gameState == 56 || gameState == 57) {
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
					memoryWrong = true;
					inputIndex = 0;
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
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (gameState == GAMESTATE_INVESTIGATION)
		{
			handleInvestMouseUp(mx, my);
		}
		else if (gameState == GAMESTATE_VAULT_RUNNER)
		{
			vrIsMouseHeld = false;
		}
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		if (isGamePaused) return;
		if (gameState == GAMESTATE_LEVEL3_SHOOTOUT)
		{
			gsHandleRightClick(mx, my);
		}
	}
}

void iMouseMove(int mx, int my)
{
	if (gameState == GAMESTATE_INVESTIGATION)
	{
		handleInvestMouseMove(mx, my);
	}
	else if (gameState == GAMESTATE_LEVEL3_SHOOTOUT)
	{
		if (isGamePaused) return;
		gsMouseMove(mx, my);
	}
}

void iPassiveMouseMove(int mx, int my)
{
	if (gameState == 100)
	{
		handleMenuPassiveMouse(mx, my);
	}

	else if (gameState == GAMESTATE_SAVE_CHOICE)
	{
		svChoiceMouseMove(mx, my);
	}

	else if (gameState == 350)
	{
		mapHoverState = 0;
		if (mx >= 150 && mx <= 630 && my >= 80 && my <= 230) {
			if (cctvUnlocked) mapHoverState = 2;
			else mapHoverState = 1;
		}
		else if (mx >= 62 && mx <= 262 && my >= 335 && my <= 563) {
			mapHoverState = 3;
		}
		else if (mx >= 530 && mx <= 730 && my >= 333 && my <= 561) {
			mapHoverState = 4;
		}
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

	if (gameState == 400) {
		usbHandleKeyboard(key);
	}

	if (gameState == GAMESTATE_TRAFFIC) {
		if (key == 'r' || key == 'R') {
			trResetGame();
		}
	}
}

void iSpecialKeyboard(int key) {
	if (key == GLUT_KEY_END) {
		exit(0);
	}

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

int main()
{
	iInitialize(800, 600, "The Last Escape");

	mciSendString(TEXT("open \"audio2.mp3\" type mpegvideo alias bgm"), NULL, 0, NULL);
	mciSendString(TEXT("open \"mouse.mp3\" type mpegvideo alias clicksound"), NULL, 0, NULL);

	srand((unsigned)time(0));
	atexit(saveGame);
	svLoadImages();

	loadBg = iLoadImage("Images/loadbg.png");
	menuBg = iLoadImage("Images/menubg.png");
	settingsImg = iLoadImage("Images/settings.png");
	settingsOnImg = iLoadImage("Images/settingson.png");

	pauseImg = iLoadImage("Images/pause.png");
	pauseToPlayImg = iLoadImage("Images/pausetoplay.png");

	on1 = iLoadImage("Images/on1.png");
	on2 = iLoadImage("Images/on2.png");
	off1 = iLoadImage("Images/off1.png");
	off2 = iLoadImage("Images/off2.png");

	btnPlay = iLoadImage("Images/menubg1.png");
	btnAbout = iLoadImage("Images/menubg2.png");
	btncredit = iLoadImage("Images/menubg3.png");
	btnExit = iLoadImage("Images/menubg4.png");

	btnPlayHover = iLoadImage("Images/menubg5.png");
	btnAboutHover = iLoadImage("Images/menubg6.png");
	btncreditHover = iLoadImage("Images/menubg7.png");
	btnExitHover = iLoadImage("Images/menubg8.png");

	about1 = iLoadImage("Images/about1.png");
	about2 = iLoadImage("Images/about2.png");
	about3 = iLoadImage("Images/about3.png");
	about4 = iLoadImage("Images/about4.png");
	about5 = iLoadImage("Images/about5.png");
	creditnoteImg = iLoadImage("Images/creditnote.png");

	backImg = iLoadImage("Images/backimage.png");
	nextImg = iLoadImage("Images/next.png");

	level1Bg = iLoadImage("Images/level1bg.png");
	level2Bg = iLoadImage("Images/level2bg.png");
	levelBg = iLoadImage("Images/levelbg.png");
	level1Btn = iLoadImage("Images/levelbg1.png");
	level2Btn = iLoadImage("Images/levelbg2.png");
	level3Btn = iLoadImage("Images/levelbg3.png");
	level2UnlockedBtn = iLoadImage("Images/levelbg4.png");
	level3UnlockedBtn = iLoadImage("Images/levelbg5.png");
	level3BgImg = iLoadImage("Images/level3bg.png");

	map1Img = iLoadImage("Images/map1.png");
	cellMapImg = iLoadImage("Images/cellmap1.png");
	cellMap2Img = iLoadImage("Images/cellmap1.png");
	cctvMapImg = iLoadImage("Images/cctvmap1.png");
	alarmMapImg = iLoadImage("Images/alarmmap1.png");

	imgBackground = iLoadImage("Images/b1.png");
	imgLockScreen = iLoadImage("Images/b3.png");
	imgEscapeScreen = iLoadImage("Images/b4.png");
	imgnote = iLoadImage("Images/note.png");
	imgsit1 = iLoadImage("Images/sit1.png");
	imgsit2 = iLoadImage("Images/sit2.png");

	bgOne = iLoadImage("Images/bgone.png");
	bgTwo = iLoadImage("Images/bgtwo.png");

	wpTwo = iLoadImage("Images/wptwo.png");
	wpThree = iLoadImage("Images/wpthree.png");

	playerImg = iLoadImage("Images/player.png");
	playerOne = iLoadImage("Images/player1.png");
	playerTwo = iLoadImage("Images/player2.png");
	playerThree = iLoadImage("Images/player3.png");

	guard1 = iLoadImage("Images/guard1.png");
	guard3 = iLoadImage("Images/guard3.png");
	guard4 = iLoadImage("Images/guard4.png");
	guard5 = iLoadImage("Images/guard5.png");
	guard6 = iLoadImage("Images/guard6.png");
	caughtPlayer = iLoadImage("Images/caughtplayer.png");

	que1 = iLoadImage("Images/que1.png");
	que2 = iLoadImage("Images/que2.png");
	que3 = iLoadImage("Images/que3.png");
	que4 = iLoadImage("Images/que4.png");
	que5 = iLoadImage("Images/que5.png");

	dodgeBgImg = iLoadImage("Images/fallingboxbg.png");
	dodgeBoxImg = iLoadImage("Images/box.png");
	dodgeNoteImg = iLoadImage("Images/note.png");
	dodgeImgStand = iLoadImage("Images/stand.png");
	dodgeImgLeft1 = iLoadImage("Images/left1.png");
	dodgeImgLeft2 = iLoadImage("Images/left2.png");
	dodgeImgRight1 = iLoadImage("Images/right1.png");
	dodgeImgRight2 = iLoadImage("Images/right2.png");
	dodgeCaughtPlayerImg = iLoadImage("Images/caughtplayer.png");

	timerImg = iLoadImage("Images/timer.png");

	resetDodgeGame();

	imgCommonRoute = iLoadImage("Images/common route.png");
	imgCCTVBackground = iLoadImage("Images/cctv.png");


	usbImgBg = iLoadImage("Images/usb room.png");
	usbImgWp = iLoadImage("Images/wp.png");
	
	imgS1 = iLoadImage("Images/S1.png");
	imgM1 = iLoadImage("Images/M1.png");

	usbImgKey = iLoadImage("Images/key_1.png");
	usbImgHandcuff = iLoadImage("Images/handcuff_1.png");
	usbImgTorch = iLoadImage("Images/torch_1.png");
	usbImgCamera = iLoadImage("Images/camera_1.png");
	usbImgStair = iLoadImage("Images/stair_1.png");
	usbImgChar[0] = iLoadImage("Images/mainchar1.png");
	usbImgChar[1] = iLoadImage("Images/mainchar2.png");
	usbImgChar[2] = iLoadImage("Images/mainchar3.png");
	usbImgChar[3] = iLoadImage("Images/mainchar4.png");
	usbImgUsbIcon = iLoadImage("Images/usb.png");
	usbInitGame();

	level2MapImg = iLoadImage("Images/level2map.png");
	vaultImg = iLoadImage("Images/vault.png");

	investRoomImg = iLoadImage("Images/room.png");
	investTableImg = iLoadImage("Images/table.png");
	investNoteImg = iLoadImage("Images/note.png");
	investPieceImg[0] = iLoadImage("Images/piece1.png");
	investPieceImg[1] = iLoadImage("Images/piece2.png");
	investPieceImg[2] = iLoadImage("Images/piece3.png");
	investPieceImg[3] = iLoadImage("Images/piece4.png");
	investPieceImg[4] = iLoadImage("Images/piece5.png");
	investPieceImg[5] = iLoadImage("Images/piece6.png");

	vrVault1Img = iLoadImage("Images/vault1.png");
	vrVault2Img = iLoadImage("Images/vault2.png");
	vrVault3Img = iLoadImage("Images/vault3.png");
	vrNoteImg = iLoadImage("Images/note.png");
	vrBgImage = iLoadImage("Images/background.png");
	vrRunnerImg[0] = iLoadImage("Images/player1.png");
	vrRunnerImg[1] = iLoadImage("Images/player2.png");
	vrRunnerImg[2] = iLoadImage("Images/player3.png");
	vrWinBgImg = iLoadImage("Images/background1.png");

	dodgeIntroNoteImg = iLoadImage("Images/dodgenote.png");
	level2NoteImg = iLoadImage("Images/level2note.png");
	usbNoteImg = iLoadImage("Images/usbnote.png");
	evidenceRoomNoteImg = iLoadImage("Images/evidenceroomnote.png");
	gunCollectImg = iLoadImage("Images/guncollect.png");

	introImg = iLoadImage("Images/intro.png");

	lv3BgImageId = iLoadImage("Images/insideprison.png");
	lv3HeroStandId = iLoadImage("Images/maincharstand.png");
	lv3HeroAnim2Id = iLoadImage("Images/mainchar2.png");
	lv3HeroAnim3Id = iLoadImage("Images/mainchar3.png");
	lv3HeroPunchId = iLoadImage("Images/maincharpunch.png");
	lv3HeroKickId = iLoadImage("Images/maincharkick.png");
	lv3GuardStId = iLoadImage("Images/guardst.png");
	lv3GuardPunch1Id = iLoadImage("Images/guardpunch1.png");
	lv3GuardPunch2Id = iLoadImage("Images/guardpunch2.png");
	lv3GunImageId = iLoadImage("Images/gun.png");
	lv3NoteImg = iLoadImage("Images/note.png");

	lv3HeroLifeImg[0] = iLoadImage("Images/charlife100.png");
	lv3HeroLifeImg[1] = iLoadImage("Images/charlife75.png");
	lv3HeroLifeImg[2] = iLoadImage("Images/charlife50.png");
	lv3HeroLifeImg[3] = iLoadImage("Images/charlife25.png");
	lv3HeroLifeImg[4] = iLoadImage("Images/charlife0.png");

	lv3GuardLifeImg[0] = iLoadImage("Images/guardlife100.png");
	lv3GuardLifeImg[1] = iLoadImage("Images/guardlife75.png");
	lv3GuardLifeImg[2] = iLoadImage("Images/guardlife50.png");
	lv3GuardLifeImg[3] = iLoadImage("Images/guardlife25.png");

	gsBgImg = iLoadImage("Images/collison room.png");
	gsWpImg = iLoadImage("Images/wp.png");
	gsPrisonerImg = iLoadImage("Images/prisoner.png");
	gsGangsterImg = iLoadImage("Images/gangster.png");
	gsPbImg = iLoadImage("Images/pb.png");
	gsGbImg = iLoadImage("Images/gb.png");
	gsDeadImg1 = iLoadImage("Images/dead1.png");
	gsDeadImg2 = iLoadImage("Images/dead2.png");
	gsDeadImg3 = iLoadImage("Images/dead3.png");

	gsH1Img = iLoadImage("Images/H1.png");
	gsG1Img = iLoadImage("Images/G1.png");
	gsD1Img = iLoadImage("Images/D1.png");

	for (int i = 0; i < GS_MAX_BULLETS; i++) {
		gsPBullets[i].active = false;
		gsGBullets[i].active = false;
	}

	trStartImg = iLoadImage("Images/temple1.png");
	trBgImg = iLoadImage("Images/temple2.png");
	trWinImg1 = iLoadImage("Images/temple3.png");
	trWinImg2 = iLoadImage("Images/temple4.png");
	trWinImg3 = iLoadImage("Images/temple5.png");
	trFinalBgImg = iLoadImage("Images/background2.png");
	trNoteImg = iLoadImage("Images/note.png");
	trScoreImg = iLoadImage("Images/score.png");

	trRunImg1 = iLoadImage("Images/temprun1.png");
	trRunImg2 = iLoadImage("Images/temprun2.png");

	trCarImgs[0] = iLoadImage("Images/car1.png");
	trCarImgs[1] = iLoadImage("Images/car2.png");
	trCarImgs[2] = iLoadImage("Images/car3.png");
	trCarImgs[3] = iLoadImage("Images/car4.png");
	trCarImgs[4] = iLoadImage("Images/car5.png");
	trCarImgs[5] = iLoadImage("Images/car6.png");

	trTruckImgs[0] = iLoadImage("Images/truck1.png");
	trTruckImgs[1] = iLoadImage("Images/truck2.png");
	trTruckImgs[2] = iLoadImage("Images/truck3.png");
	trTruckImgs[3] = iLoadImage("Images/truck4.png");

	trResetGame();

	iSetTimer(20, fixedUpdate);
	iSetTimer(100, loadingUpdate);
	iSetTimer(1000, narrativeTimer);
	iSetTimer(400, updateSequence);

	iSetTimer(120, usbAnimateCharacter);

	iSetTimer(TR_TICK_MS, trFixedUpdate);
	iSetTimer(2000, saveGame);
	
	iStart();
	return 0;
}