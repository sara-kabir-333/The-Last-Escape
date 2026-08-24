#define _CRT_SECURE_NO_WARNINGS
#include "iGraphics.h"
#include <stdlib.h>
#include <time.h>
#include "Variables.h"
#include "Functions.h"
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

int main()
{
	iInitialize(800, 600, "The Last Escape");

	// --- BACKGROUND MUSIC SETUP (MP3 via MCI) ---
	mciSendString(TEXT("open \"audio1.mp3\" type mpegvideo alias bgm"), NULL, 0, NULL);
	mciSendString(TEXT("play bgm repeat"), NULL, 0, NULL);

	// --- MOUSE CLICK SOUND SETUP (MP3 via MCI) ---
	mciSendString(TEXT("open \"mouse.mp3\" type mpegvideo alias clicksound"), NULL, 0, NULL);

	srand((unsigned)time(0));

	// --- LOAD MENU & UI IMAGES ---
	loadBg = iLoadImage("loadbg.png");
	menuBg = iLoadImage("menubg.png");
	btnPlay = iLoadImage("menubg1.png");
	btnAbout = iLoadImage("menubg2.png");
	btnSetting = iLoadImage("menubg3.png");
	btnExit = iLoadImage("menubg4.png");

	btnPlayHover = iLoadImage("menubg5.png");
	btnAboutHover = iLoadImage("menubg6.png");
	btnSettingHover = iLoadImage("menubg7.png");
	btnExitHover = iLoadImage("menubg8.png");

	about1 = iLoadImage("about1.png");
	about2 = iLoadImage("about2.png");
	about3 = iLoadImage("about3.png");
	about4 = iLoadImage("about4.png");
	about5 = iLoadImage("about5.png");
	aboutBg1 = iLoadImage("aboutbg1.png");
	aboutBg2 = iLoadImage("aboutbg2.png");

	backImg = iLoadImage("backimage.png");
	nextImg = iLoadImage("next.png");

	level1Bg = iLoadImage("level1bg.png");
	levelBg = iLoadImage("levelbg.png");
	level1Btn = iLoadImage("levelbg1.png");
	level2Btn = iLoadImage("levelbg2.png");
	level3Btn = iLoadImage("levelbg3.png");

	// --- LOAD PUZZLE & NARRATIVE & GAMEPLAY IMAGES ---
	imgBackground = iLoadImage("b1.png");
	imgLockScreen = iLoadImage("b3.png");
	imgEscapeScreen = iLoadImage("b4.png");
	imgnote = iLoadImage("note.png");
	imgsit1 = iLoadImage("sit1.png");
	imgsit2 = iLoadImage("sit2.png");

	bgOne = iLoadImage("bgone.png");
	bgTwo = iLoadImage("bgtwo.png");

	wpOne = iLoadImage("wpone.png");
	wpTwo = iLoadImage("wptwo.png");
	wpThree = iLoadImage("wpthree.png");

	playerImg = iLoadImage("player.png");
	playerOne = iLoadImage("player1.png");
	playerTwo = iLoadImage("player2.png");
	playerThree = iLoadImage("player3.png");

	guard1 = iLoadImage("guard1.png");
	guard3 = iLoadImage("guard3.png");
	guard4 = iLoadImage("guard4.png");
	guard5 = iLoadImage("guard5.png");

	que1 = iLoadImage("que1.png");
	que2 = iLoadImage("que2.png");
	que3 = iLoadImage("que3.png");
	que4 = iLoadImage("que4.png");
	que5 = iLoadImage("que5.png");

	// --- LOAD SWITCH PUZZLE & CCTV IMAGES ---
	imgCommonRoute = iLoadImage("Images/common route.png");
	imgCCTVBackground = iLoadImage("Images/cctv.png");

	imgChar[0] = iLoadImage("Images/mainchar1.png");
	imgChar[1] = iLoadImage("Images/mainchar2.png");
	imgChar[2] = iLoadImage("Images/mainchar3.png");
	imgChar[3] = iLoadImage("Images/mainchar4.png");

	// --- TIMERS SETUP ---
	iSetTimer(200, loadingUpdate);
	iSetTimer(200, fixedUpdate);
	iSetTimer(400, updateSequence);
	iSetTimer(1000, narrativeTimer);

	iStart();
	return 0;
}

// --- MOUSE CLICK FUNCTION MANAGED ENTIRELY IN IMAIN.CPP ---
void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		// Rewind and play mouse.mp3 instantly on click using MCI
		mciSendString(TEXT("seek clicksound to start"), NULL, 0, NULL);
		mciSendString(TEXT("play clicksound"), NULL, 0, NULL);

		// Allow movement ONLY in Common Route (gameState 70)
		if (gameState == 70 && mx > charX) {
			targetX = mx;
		}

		// Switch Puzzle Mouse Click Handling (gameState 71)
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

			// Click ON button
			if (mx >= 260 && mx <= 380 && my >= 400 && my <= 445) {
				int pressed = 1;
				if (pressed == switchSequence[switchCurrentInput]) {
					switchCurrentInput++;
					if (switchCurrentInput == 5) {
						switchSolved = true;
					}
				}
				else {
					switchWrong = true;
				}
				return;
			}
			// Click OFF button
			else if (mx >= 420 && mx <= 540 && my >= 400 && my <= 445) {
				int pressed = 0;
				if (pressed == switchSequence[switchCurrentInput]) {
					switchCurrentInput++;
					if (switchCurrentInput == 5) {
						switchSolved = true;
					}
				}
				else {
					switchWrong = true;
				}
				return;
			}
		}

		if (gameState == 100)
		{
			if (mx >= 340 && mx <= 640 && my >= 365 && my <= 415)
			{
				gameState = 300;
			}
			else if (mx >= 340 && mx <= 640 && my >= 295 && my <= 345)
			{
				gameState = 200;
			}
			else if (mx >= 340 && mx <= 640 && my >= 175 && my <= 225)
			{
				exit(0);
			}
		}
		else if (gameState >= 200 && gameState <= 206)
		{
			if (mx >= 50 && mx <= 150 && my >= 50 && my <= 90)
			{
				if (gameState == 200) gameState = 100;
				else gameState--;
			}
			else if (mx >= 650 && mx <= 750 && my >= 50 && my <= 90 && gameState != 206)
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
				gameState = 5;
				loadingStep = 0;
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