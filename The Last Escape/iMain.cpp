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
#pragma comment(lib, "winmm.lib")

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

int map1Img = 0;
int cellMapImg = 0;
int cellMap2Img = 0;
int cctvMapImg = 0;
int alarmMapImg = 0;
bool cctvUnlocked = false;
bool switchPuzzleCompleted = false;

int note1Img = 0;
int note2Img = 0;
int note3Img = 0;
int note4Img = 0;
int mapHoverState = 0; // 0: none, 1: note1, 2: note2, 3: note3, 4: note4

int btnPlay = 0, btnAbout = 0, btncredit = 0, btnExit = 0;
int btnPlayHover = 0, btnAboutHover = 0, btncreditHover = 0, btnExitHover = 0;

int bgOne = 0;
int bgTwo = 0;

int wpTwo = 0;
int wpThree = 0;

int playerImg = 0;
int playerOne = 0;
int playerTwo = 0;
int playerThree = 0;

int guard1 = 0;
int guard3 = 0;
int guard4 = 0;
int guard5 = 0;
int guard6 = 0;
int caughtPlayer = 0;

int que1 = 0, que2 = 0, que3 = 0, que4 = 0, que5 = 0;

int imgBackground = 0;
int imgLockScreen = 0;
int imgEscapeScreen = 0;
int imgnote = 0;
int imgsit1 = 0;
int imgsit2 = 0;

int imgCommonRoute = 0;
int imgCCTVBackground = 0;

int gameState = 0;
int loadingStep = 0;
int btnHoverState = 0;

int x = 0;
int y = 0;

int playerIdleFrame = 0;
int playerIdleCounter = 0;

int playerX = 580;
int playerY = 130;
bool playerRun = false;
int playerFrame = 0;

int guardX = 40;
int guardY = 276;
bool moveRight = true;
int guardFrame = 0;
int guardAnimCounter = 0;

bool puzzleStart = false;
bool puzzleSolved = false;
bool puzzleWrong = false;
bool memoryWrong = false;

bool showWpOne = false;
bool showWpTwo = false;
bool showWpThree = false;
bool puzzleScreen = false;

char answer[5][4] =
{
	"496",
	"859",
	"274",
	"631",
	"512"
};

int currentPuzzle = 0;
int current = 0;
clock_t questionStartTime = 0;

bool showQuestion = true;
bool solved = false;
bool wrong = false;

bool keyReleased = true;
bool digitReleased = true;

bool playerRunning = false;
bool startRun = false;
bool playerEscaped = false;
bool finalMessageStarted = false;
bool finalMessageShown = false;

bool backScene = false;
bool levelFinished = false;

int boxSize = 85;
int redX = 120, redY = 380;
int blueX = 270, blueY = 380;
int greenX = 420, greenY = 380;
int yellowX = 570, yellowY = 380;
int cyanX = 195, cyanY = 480;
int magentaX = 345, magentaY = 480;
int orangeX = 495, orangeY = 480;

int sequence[10] = { 0 };
int level = 5;
int playerInput[10] = { 0 };
int inputIndex = 0;

int currentDisplayIndex = 0;
int activeDisplayColor = -1;
int displayTimer = 0;

int switchSequence[5] = { 0 };
int switchCurrentInput = 0;

bool switchShowSequence = true;
bool switchSolved = false;
bool switchWrong = false;
bool switchKeyReleased = true;
bool switchPlayerRunning = false;

int switchTickCounter = 0;
int switchSolvedTickCounter = 0;

int charX = 50;
int charY = 150;
int charFrame = 0;
int targetX = -1;

int solvedTickCounter = 0;
bool isWaitingToRun = false;
int switchLevelDelayCounter = 0;
bool isWaitingForSwitchLevel = false;

int sit1Timer = 0;
int gameplayCounter = 0;

int aboutBg1, aboutBg2, btnSetting, btnSettingHover, wpOne;
int menuHover = 0;

// ==========================================================
// IMAGE MEMORY PUZZLE (ADDED AFTER CCTV SWITCH PUZZLE)
// Game states 80-83 are reserved for this puzzle.
// ==========================================================
const int STATE_MEMORY_WALK = 80;
const int STATE_MEMORY_SHOW_SEQUENCE = 81;
const int STATE_MEMORY_SHUFFLING = 82;
const int STATE_MEMORY_HOLD_AFTER_SHUFFLE = 83;
const int STATE_MEMORY_PLAY = 84;
const int STATE_MEMORY_EXIT = 85;

int memoryState = STATE_MEMORY_WALK;

float memoryCharX = -80.0f;
float memoryTargetCharX = 350.0f;
int memoryCharFrame = 1;
int memoryCharAnimCounter = 0;

int memorySequenceLength = 8;
int memoryTargetSequence[10];
int memoryGridCardIDs[8];
float memoryGridCardX[8], memoryGridCardY[8];
int memoryPlayerSequence[10];
int memoryPlayerInputIndex = 0;

int memoryShuffleAnimStep = 0;
const int memoryMaxShuffleSteps = 25;

bool memoryPuzzleSolved = false;
bool memoryPuzzleFailed = false;

int memoryImgCardBack = -1;
int memoryImgBackground = -1;
int memoryImgWp = -1;
int memoryImgChar[5] = { -1, -1, -1, -1, -1 };
int memoryImgItem[9] = { -1, -1, -1, -1, -1, -1, -1, -1, -1 };

void initMemoryPuzzle(int length);
void memoryStartShuffleTransition();
void memoryStartPlayerTurn();
void memoryAnimationTimer();
void drawMemoryPuzzle();
void resetLevel1();


void showQuestionPattern();
void startPlayerRun();
void resetSwitchPuzzle();
void startSwitchPuzzleLevel();
void drawMenu();
void handleMenuPassiveMouse(int mx, int my);
void handleMenuMouse(int mx, int my);
void updateSequence();
void createSequence();

// ==========================================================
// USB COLLECTION MINI-GAME (LEVEL 2) - MERGED MODULE
// Runs entirely inside gameState == 400. Nothing about any
// other gameState was changed to add this.
// ==========================================================
#define USB_GRID_SIZE 8
#define USB_TILE_SIZE 55
#define USB_BOARD_X ((800 - (USB_GRID_SIZE * USB_TILE_SIZE)) / 2)
#define USB_BOARD_Y 75

int usbSubState = 0; // 0: Instructions, 1: Playing, 2: Won, 3: Lost
int usbGrid[USB_GRID_SIZE][USB_GRID_SIZE];
int usbSelectedRow = -1, usbSelectedCol = -1;
int usbScore = 0;
int usbMovesLeft = 30;

int usbImgKey = 0, usbImgHandcuff = 0, usbImgTorch = 0, usbImgCamera = 0, usbImgStair = 0;
int usbImgBg = 0;
int usbImgWp = 0;
int usbImgChar[4] = { 0, 0, 0, 0 };
int usbImgUsbIcon = 0;

int usbCurrentFrame = 0;
float usbCharX = -50.0f;
float usbCharY = 150.0f;

void usbGenerateBoard();
int usbCheckMatchesExist();
void usbResolveBoard();
void usbApplyGravity();
void usbRefillBoard();
void usbInitGame();
void usbAnimateCharacter();
void usbDrawGame();
void usbHandleMouseClick(int mx, int my);
void usbHandleKeyboard(unsigned char key);

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
	charFrame = (charFrame + 1) % 3;

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
	charFrame = (charFrame + 1) % 3;
	if (charX < 50) {
		charX = 50;
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
			gameState = 350;
			loadingStep = 0;
			if (musicPlaying) {
				mciSendString(TEXT("play bgm repeat"), NULL, 0, NULL);
			}
		}
		else if (gameState == 6)
		{
			gameState = 400;
			usbInitGame();
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
			if ((clock() - questionStartTime) / CLOCKS_PER_SEC >= 10)
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
}


void initMemoryPuzzle(int length) {
	memorySequenceLength = length;
	if (memorySequenceLength > 8) memorySequenceLength = 8;

	memoryCharX = -80.0f;
	memoryTargetCharX = 350.0f;
	memoryCharFrame = 1;
	memoryCharAnimCounter = 0;

	for (int i = 0; i < 8; i++) {
		int row = i / 4;
		int col = i % 4;
		memoryGridCardX[i] = 145.0f + col * 135.0f;
		memoryGridCardY[i] = 370.0f - row * 135.0f;
		memoryGridCardIDs[i] = i + 1;
	}

	for (int i = 0; i < memorySequenceLength; i++) {
		int candidate;
		bool duplicate;
		do {
			duplicate = false;
			candidate = (rand() % 8) + 1;
			for (int j = 0; j < i; j++) {
				if (memoryTargetSequence[j] == candidate) {
					duplicate = true;
					break;
				}
			}
		} while (duplicate);
		memoryTargetSequence[i] = candidate;
	}

	memoryPlayerInputIndex = 0;
	memoryShuffleAnimStep = 0;
	memoryPuzzleSolved = false;
	memoryPuzzleFailed = false;
	memoryState = STATE_MEMORY_WALK;
}

void memoryStartShuffleTransition() {
	if (memoryState != STATE_MEMORY_SHOW_SEQUENCE) return;

	memoryState = STATE_MEMORY_SHUFFLING;
	memoryShuffleAnimStep = 0;

	for (int i = 7; i > 0; i--) {
		int j = rand() % (i + 1);
		int temp = memoryGridCardIDs[i];
		memoryGridCardIDs[i] = memoryGridCardIDs[j];
		memoryGridCardIDs[j] = temp;
	}
}

void memoryStartPlayerTurn() {
	if (memoryState == STATE_MEMORY_HOLD_AFTER_SHUFFLE) {
		memoryState = STATE_MEMORY_PLAY;
	}
}

void memoryAnimationTimer() {
	if (isGamePaused) return;

	if (memoryState == STATE_MEMORY_WALK) {
		memoryCharX += 4.0f;
		memoryCharAnimCounter++;

		if (memoryCharAnimCounter >= 5) {
			memoryCharFrame++;
			if (memoryCharFrame > 4) memoryCharFrame = 1;
			memoryCharAnimCounter = 0;
		}

		if (memoryCharX >= memoryTargetCharX) {
			memoryCharX = memoryTargetCharX;
			memoryState = STATE_MEMORY_SHOW_SEQUENCE;
			iSetTimer(8000, memoryStartShuffleTransition);
		}
	}
	else if (memoryState == STATE_MEMORY_EXIT) {
		memoryCharX += 5.0f;
		memoryCharAnimCounter++;

		if (memoryCharAnimCounter >= 4) {
			memoryCharFrame++;
			if (memoryCharFrame > 4) memoryCharFrame = 1;
			memoryCharAnimCounter = 0;
		}

		if (memoryCharX > 850) {
			memoryState = STATE_MEMORY_WALK;
			level1Completed = true;
			gameState = 300;
		}
	}

	if (memoryState == STATE_MEMORY_SHUFFLING) {
		memoryShuffleAnimStep++;

		for (int i = 0; i < 8; i++) {
			int row = i / 4;
			int col = i % 4;
			float finalX = 145.0f + col * 135.0f;
			float finalY = 370.0f - row * 135.0f;

			if (memoryShuffleAnimStep < memoryMaxShuffleSteps) {
				memoryGridCardX[i] += (finalX - memoryGridCardX[i]) * 0.25f;
				memoryGridCardY[i] += (finalY - memoryGridCardY[i]) * 0.25f;
			}
		}

		if (memoryShuffleAnimStep >= memoryMaxShuffleSteps) {
			for (int i = 0; i < 8; i++) {
				int row = i / 4;
				int col = i % 4;
				memoryGridCardX[i] = 145.0f + col * 135.0f;
				memoryGridCardY[i] = 370.0f - row * 135.0f;
			}

			memoryState = STATE_MEMORY_HOLD_AFTER_SHUFFLE;
			iSetTimer(5000, memoryStartPlayerTurn);
		}
	}
}

void drawMemoryPuzzle() {
	if (memoryImgBackground != -1)
		iShowImage(0, 0, 800, 600, memoryImgBackground);
	else {
		iSetColor(20, 30, 45);
		iFilledRectangle(0, 0, 800, 600);
	}

	if (memoryImgWp != -1)
		iShowImage(100, 20, 600, 90, memoryImgWp);

	if (memoryState == STATE_MEMORY_WALK || memoryState == STATE_MEMORY_EXIT) {
		if (memoryImgChar[memoryCharFrame] != -1)
			iShowImage((int)memoryCharX, 150, 80, 100, memoryImgChar[memoryCharFrame]);
	}
	else {
		if (memoryImgChar[1] != -1)
			iShowImage((int)memoryCharX, 150, 80, 100, memoryImgChar[1]);
	}

	iSetColor(50, 25, 0);

	if (memoryPuzzleFailed) {
		if (imgnote > 0) {
			iShowImage(150, 20, 500, 200, imgnote);
		}
		iSetColor(150, 0, 0);
		iText(245, 65, "ALARM TRIGGERED! YOU WERE CAUGHT.", GLUT_BITMAP_HELVETICA_18);
		iSetColor(0, 0, 0);
		iText(200, 50, "CLICK ANYWHERE TO RESTART FROM THE BOX PUZZLE", GLUT_BITMAP_HELVETICA_18);
		return;
	}

	if (memoryState == STATE_MEMORY_WALK) {
		iText(190, 40, "PRISONER ESCAPING...", GLUT_BITMAP_HELVETICA_12);
	}
	else if (memoryState == STATE_MEMORY_SHOW_SEQUENCE) {
		iText(190, 40, "STEP 1: MEMORIZE ALL 8 ITEMS IN SEQUENCE", GLUT_BITMAP_HELVETICA_12);

		for (int i = 0; i < 8; i++) {
			int xPos = (int)memoryGridCardX[i];
			int yPos = (int)memoryGridCardY[i];

			iSetColor(40, 50, 70);
			iFilledRectangle(xPos, yPos, 100, 100);

			int seqOrder = -1;
			for (int t = 0; t < memorySequenceLength; t++) {
				if (memoryTargetSequence[t] == memoryGridCardIDs[i]) {
					seqOrder = t + 1;
					break;
				}
			}

			if (seqOrder != -1) {
				iSetColor(255, 215, 0);
				iRectangle(xPos, yPos, 100, 100);
				iRectangle(xPos - 1, yPos - 1, 102, 102);
			}
			else {
				iSetColor(0, 255, 204);
				iRectangle(xPos, yPos, 100, 100);
			}

			int itemID = memoryGridCardIDs[i];
			if (memoryImgItem[itemID] != -1)
				iShowImage(xPos + 18, yPos + 18, 64, 64, memoryImgItem[itemID]);

			if (seqOrder != -1) {
				char orderStr[10];
				sprintf(orderStr, "#%d", seqOrder);
				iSetColor(255, 255, 0);
				iText(xPos + 8, yPos + 75, orderStr, GLUT_BITMAP_HELVETICA_18);
			}
		}
	}
	else if (memoryState == STATE_MEMORY_SHUFFLING ||
		memoryState == STATE_MEMORY_HOLD_AFTER_SHUFFLE) {

		iText(190, 40, "STUDY FINAL POSITIONS (CARDS REMAIN FACE-UP)",
			GLUT_BITMAP_HELVETICA_12);

		for (int i = 0; i < 8; i++) {
			int xPos = (int)memoryGridCardX[i];
			int yPos = (int)memoryGridCardY[i];

			iSetColor(40, 50, 70);
			iFilledRectangle(xPos, yPos, 100, 100);
			iSetColor(255, 215, 0);
			iRectangle(xPos, yPos, 100, 100);

			int itemID = memoryGridCardIDs[i];
			if (memoryImgItem[itemID] != -1)
				iShowImage(xPos + 18, yPos + 18, 64, 64, memoryImgItem[itemID]);

			int seqOrder = -1;
			for (int t = 0; t < memorySequenceLength; t++) {
				if (memoryTargetSequence[t] == memoryGridCardIDs[i]) {
					seqOrder = t + 1;
					break;
				}
			}

			if (seqOrder != -1) {
				char orderStr[10];
				sprintf(orderStr, "#%d", seqOrder);
				iSetColor(255, 255, 0);
				iText(xPos + 8, yPos + 75, orderStr, GLUT_BITMAP_HELVETICA_18);
			}
		}
	}
	else if (memoryState == STATE_MEMORY_PLAY) {
		iText(190, 40, "STEP 2: CLICK ALL 8 CARDS IN SEQUENCE",
			GLUT_BITMAP_HELVETICA_12);

		for (int i = 0; i < 8; i++) {
			int xPos = (int)memoryGridCardX[i];
			int yPos = (int)memoryGridCardY[i];

			iSetColor(60, 70, 90);
			iFilledRectangle(xPos, yPos, 100, 100);

			iSetColor(255, 255, 255);
			iRectangle(xPos, yPos, 100, 100);

			if (memoryImgCardBack != -1)
				iShowImage(xPos + 18, yPos + 18, 64, 64, memoryImgCardBack);

			char cardNum[20];
			sprintf(cardNum, "Slot %d", i + 1);
			iText(xPos + 25, yPos - 20, cardNum, GLUT_BITMAP_HELVETICA_12);
		}
	}
	else if (memoryState == STATE_MEMORY_EXIT) {
		iSetColor(0, 100, 0);
		iText(300, 40, "ACCESS GRANTED!", GLUT_BITMAP_HELVETICA_18);
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
	else if (gameState == 210)
	{
		if (creditnoteImg > 0) iShowImage(0, 0, 800, 600, creditnoteImg);
		if (backImg > 0) iShowImage(50, 50, 100, 40, backImg);
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

		if (switchPuzzleCompleted && cctvUnlocked && !level1Completed) {
			iSetColor(255, 255, 0);
			iRectangle(530, 333, 200, 228);
			iRectangle(531, 334, 198, 226);
			iText(548, 320, "CLICK: MEMORY PUZZLE", GLUT_BITMAP_HELVETICA_18);
		}

		if (mapHoverState == 1 && note1Img > 0) {
			iShowImage(200, 240, 400, 100, note1Img);
		}
		else if (mapHoverState == 2 && note2Img > 0) {
			iShowImage(200, 240, 400, 100, note2Img);
		}
		else if (mapHoverState == 3 && note3Img > 0) {
			iShowImage(275, 335, 200, 200, note3Img);
		}
		else if (mapHoverState == 4 && note4Img > 0) {
			iShowImage(320, 333, 200, 200, note4Img);
		}

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
			iSetColor(255, 0, 0);
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
			iSetColor(255, 0, 0);
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

			iShowImage(startX, guardY, 50, 70, guard6);
			iShowImage(startX + 50, playerY, 60, 80, caughtPlayer);

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
					iShowImage(playerX, playerY, 60, 80, playerImg);
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
	else if (gameState >= STATE_MEMORY_WALK && gameState <= STATE_MEMORY_EXIT)
	{
		drawMemoryPuzzle();
	}

	if (gameState == 100 || gameState == 210 || gameState == 300 || gameState == 350 || gameState == 400 || gameState == 70 || gameState == 71 || ((gameState >= 50 && gameState <= 60) && gameState != 56) || (gameState >= STATE_MEMORY_WALK && gameState <= STATE_MEMORY_EXIT))
	{
		if (settingsImg > 0 && gameState != 210) {
			iShowImage(20, 520, 50, 50, settingsImg);
		}

		if (showSettingsPanel && settingsOnImg > 0 && gameState != 210) {
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

	if (gameState == 70 || gameState == 71 || ((gameState >= 50 && gameState <= 60) && gameState != 56) || (gameState >= STATE_MEMORY_WALK && gameState <= STATE_MEMORY_EXIT))
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

		if (gameState == 100 || gameState == 300 || gameState == 350 || gameState == 400 || gameState == 70 || gameState == 71 || ((gameState >= 50 && gameState <= 60) && gameState != 56) || (gameState >= STATE_MEMORY_WALK && gameState <= STATE_MEMORY_EXIT))
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

		if (gameState == 70 || gameState == 71 || ((gameState >= 50 && gameState <= 60) && gameState != 56) || (gameState >= STATE_MEMORY_WALK && gameState <= STATE_MEMORY_EXIT))
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

		if (gameState == 60 && wrong)
		{
			resetLevel1();
			gameState = 50;
			sit1Timer = 0;
			return;
		}

		if (gameState == 400 || gameState == 50 || gameState == 51 || gameState == 52 || gameState == 53 || gameState == 54 || gameState == 55 || gameState == 60 || gameState == 70 || gameState == 71)
		{
			if (mx >= 50 && mx <= 150 && my >= 50 && my <= 90)
			{
				gameState = 350;
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

		// ======================================================
		// IMAGE MEMORY PUZZLE MOUSE INPUT
		// ======================================================
		if (gameState >= STATE_MEMORY_WALK && gameState <= STATE_MEMORY_EXIT)
		{
			if (memoryPuzzleFailed)
			{
				resetLevel1();
				createSequence(); // Restarts directly from the box puzzle state (gameState = 53)
				return;
			}

			if (mx >= 50 && mx <= 150 && my >= 50 && my <= 90)
			{
				gameState = 350;
				return;
			}

			if (memoryState == STATE_MEMORY_PLAY &&
				!memoryPuzzleSolved && !memoryPuzzleFailed)
			{
				for (int i = 0; i < 8; i++)
				{
					int xPos = (int)memoryGridCardX[i];
					int yPos = (int)memoryGridCardY[i];

					if (mx >= xPos && mx <= xPos + 100 &&
						my >= yPos && my <= yPos + 100)
					{
						int clickedItemID = memoryGridCardIDs[i];

						memoryPlayerSequence[memoryPlayerInputIndex] = clickedItemID;
						memoryPlayerInputIndex++;

						if (memoryPlayerSequence[memoryPlayerInputIndex - 1] !=
							memoryTargetSequence[memoryPlayerInputIndex - 1])
						{
							memoryPuzzleFailed = true;
							return;
						}
						else if (memoryPlayerInputIndex == memorySequenceLength)
						{
							memoryPuzzleSolved = true;
							memoryState = STATE_MEMORY_EXIT;
							return;
						}
					}
				}
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
					gameState = 6;
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
					initMemoryPuzzle(8);
					gameState = STATE_MEMORY_WALK;
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
}

void iMouseMove(int mx, int my) {}

void iPassiveMouseMove(int mx, int my)
{
	if (gameState == 100)
	{
		handleMenuPassiveMouse(mx, my);
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

// ==========================================================
// USB COLLECTION MINI-GAME (LEVEL 2) - FUNCTION DEFINITIONS
// ==========================================================

void usbGenerateBoard() {
	for (int r = 0; r < USB_GRID_SIZE; r++) {
		for (int c = 0; c < USB_GRID_SIZE; c++) {
			usbGrid[r][c] = (rand() % 5) + 1;
		}
	}
	while (usbCheckMatchesExist()) {
		usbGenerateBoard();
	}
}

int usbCheckMatchesExist() {
	for (int r = 0; r < USB_GRID_SIZE; r++) {
		for (int c = 0; c < USB_GRID_SIZE - 2; c++) {
			if (usbGrid[r][c] != 0 && usbGrid[r][c] == usbGrid[r][c + 1] && usbGrid[r][c] == usbGrid[r][c + 2])
				return 1;
		}
	}
	for (int c = 0; c < USB_GRID_SIZE; c++) {
		for (int r = 0; r < USB_GRID_SIZE - 2; r++) {
			if (usbGrid[r][c] != 0 && usbGrid[r][c] == usbGrid[r + 1][c] && usbGrid[r][c] == usbGrid[r + 2][c])
				return 1;
		}
	}
	return 0;
}

void usbApplyGravity() {
	for (int c = 0; c < USB_GRID_SIZE; c++) {
		int writeRow = 0;
		for (int r = 0; r < USB_GRID_SIZE; r++) {
			if (usbGrid[r][c] != 0) {
				usbGrid[writeRow][c] = usbGrid[r][c];
				if (writeRow != r) {
					usbGrid[r][c] = 0;
				}
				writeRow++;
			}
		}
	}
}

void usbRefillBoard() {
	for (int r = 0; r < USB_GRID_SIZE; r++) {
		for (int c = 0; c < USB_GRID_SIZE; c++) {
			if (usbGrid[r][c] == 0) {
				usbGrid[r][c] = (rand() % 5) + 1;
			}
		}
	}
}

void usbResolveBoard() {
	int matched[USB_GRID_SIZE][USB_GRID_SIZE] = { 0 };

	for (int r = 0; r < USB_GRID_SIZE; r++) {
		for (int c = 0; c < USB_GRID_SIZE - 2; c++) {
			if (usbGrid[r][c] != 0 && usbGrid[r][c] == usbGrid[r][c + 1] && usbGrid[r][c] == usbGrid[r][c + 2]) {
				matched[r][c] = matched[r][c + 1] = matched[r][c + 2] = 1;
			}
		}
	}
	for (int c = 0; c < USB_GRID_SIZE; c++) {
		for (int r = 0; r < USB_GRID_SIZE - 2; r++) {
			if (usbGrid[r][c] != 0 && usbGrid[r][c] == usbGrid[r + 1][c] && usbGrid[r][c] == usbGrid[r + 2][c]) {
				matched[r][c] = matched[r + 1][c] = matched[r + 2][c] = 1;
			}
		}
	}

	for (int r = 0; r < USB_GRID_SIZE; r++) {
		for (int c = 0; c < USB_GRID_SIZE; c++) {
			if (matched[r][c]) {
				usbGrid[r][c] = 0;
				usbScore += 1;
			}
		}
	}

	usbApplyGravity();
	usbRefillBoard();

	if (usbCheckMatchesExist()) {
		usbResolveBoard();
	}
}

void usbInitGame() {
	usbSubState = 0;
	usbScore = 0;
	usbMovesLeft = 30;
	usbSelectedRow = -1;
	usbSelectedCol = -1;
	usbCurrentFrame = 0;
	usbCharX = -50.0f;
	usbCharY = 150.0f;
	usbGenerateBoard();
}

void usbAnimateCharacter() {
	if (isGamePaused) return;
	if (gameState == 400 && usbSubState == 2) {
		usbCharX += 4.0f;
		if (usbCharX > 480.0f) {
			usbCharX = 480.0f;
			usbCurrentFrame = 0;
		}
		else {
			usbCurrentFrame = (usbCurrentFrame + 1) % 4;
		}
	}
}

void usbDrawGame() {
	if (usbImgBg > 0) {
		iShowImage(0, 0, 800, 600, usbImgBg);
	}
	else {
		iShowImage(0, 0, 800, 600, level2Bg);
	}

	if (usbSubState == 0) {
		if (usbImgWp > 0) iShowImage(50, 80, 700, 140, usbImgWp);

		iSetColor(50, 30, 10);
		iText(150, 160, "PRISON ESCAPE: SECURITY OVERRIDE", GLUT_BITMAP_HELVETICA_18);
		iSetColor(30, 30, 30);
		iText(135, 125, "Play this match-3 game to get the USB!", GLUT_BITMAP_HELVETICA_18);
		iSetColor(180, 40, 40);
		iText(185, 95, "Click anywhere or press ENTER to Start", GLUT_BITMAP_HELVETICA_18);
	}
	else if (usbSubState == 1) {
		iSetColor(30, 30, 40);
		iFilledRectangle(USB_BOARD_X - 10, USB_BOARD_Y - 10, USB_GRID_SIZE * USB_TILE_SIZE + 20, USB_GRID_SIZE * USB_TILE_SIZE + 20);

		for (int r = 0; r < USB_GRID_SIZE; r++) {
			for (int c = 0; c < USB_GRID_SIZE; c++) {
				int px = USB_BOARD_X + c * USB_TILE_SIZE;
				int py = USB_BOARD_Y + r * USB_TILE_SIZE;

				if (usbSelectedRow == r && usbSelectedCol == c) {
					iSetColor(255, 215, 0);
				}
				else {
					iSetColor(50, 50, 70);
				}
				iFilledRectangle(px + 2, py + 2, USB_TILE_SIZE - 4, USB_TILE_SIZE - 4);

				int imgToDraw = -1;
				if (usbGrid[r][c] == 1) imgToDraw = usbImgKey;
				else if (usbGrid[r][c] == 2) imgToDraw = usbImgHandcuff;
				else if (usbGrid[r][c] == 3) imgToDraw = usbImgTorch;
				else if (usbGrid[r][c] == 4) imgToDraw = usbImgCamera;
				else if (usbGrid[r][c] == 5) imgToDraw = usbImgStair;

				if (usbGrid[r][c] != 0 && imgToDraw > 0) {
					iShowImage(px + 5, py + 5, USB_TILE_SIZE - 10, USB_TILE_SIZE - 10, imgToDraw);
				}
			}
		}

		char scoreStr[50], movesStr[50];
		sprintf(scoreStr, "Hacks: %d / 150", usbScore);
		sprintf(movesStr, "Moves: %d", usbMovesLeft);

		iSetColor(255, 255, 255);
		iText(160, 545, scoreStr, GLUT_BITMAP_HELVETICA_18);
		iText(530, 545, movesStr, GLUT_BITMAP_HELVETICA_18);
	}
	else if (usbSubState == 2) {
		if (usbImgUsbIcon > 0) iShowImage(520, 220, 40, 40, usbImgUsbIcon);
		if (usbImgChar[usbCurrentFrame] > 0) iShowImage((int)usbCharX, (int)usbCharY, 80, 100, usbImgChar[usbCurrentFrame]);

		iSetColor(50, 255, 50);
		iText(275, 480, "SECURITY BYPASSED!", GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(255, 255, 255);
		iText(220, 440, "Character acquired the USB!", GLUT_BITMAP_HELVETICA_18);
	}
	else if (usbSubState == 3) {
		iSetColor(255, 50, 50);
		iText(265, 300, "LOCKDOWN TRIGGERED!", GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(255, 255, 255);
		iText(310, 260, "Press r to retry", GLUT_BITMAP_HELVETICA_18);
	}

	iShowImage(50, 50, 100, 40, backImg);
}

void usbHandleMouseClick(int mx, int my) {
	if (usbSubState == 0) {
		usbSubState = 1;
		return;
	}

	if (usbSubState == 2 || usbSubState == 3) return;

	if (mx >= USB_BOARD_X && mx < USB_BOARD_X + USB_GRID_SIZE * USB_TILE_SIZE &&
		my >= USB_BOARD_Y && my < USB_BOARD_Y + USB_GRID_SIZE * USB_TILE_SIZE) {

		int c = (mx - USB_BOARD_X) / USB_TILE_SIZE;
		int r = (my - USB_BOARD_Y) / USB_TILE_SIZE;

		if (usbSelectedRow == -1 && usbSelectedCol == -1) {
			usbSelectedRow = r;
			usbSelectedCol = c;
		}
		else {
			if (abs(usbSelectedRow - r) + abs(usbSelectedCol - c) == 1) {
				int temp = usbGrid[usbSelectedRow][usbSelectedCol];
				usbGrid[usbSelectedRow][usbSelectedCol] = usbGrid[r][c];
				usbGrid[r][c] = temp;

				if (usbCheckMatchesExist()) {
					usbMovesLeft--;
					usbResolveBoard();

					if (usbScore >= 150) {
						usbSubState = 2;
					}
					else if (usbMovesLeft <= 0) {
						usbSubState = 3;
					}
				}
				else {
					temp = usbGrid[usbSelectedRow][usbSelectedCol];
					usbGrid[usbSelectedRow][usbSelectedCol] = usbGrid[r][c];
					usbGrid[r][c] = temp;
				}
			}
			usbSelectedRow = -1;
			usbSelectedCol = -1;
		}
	}
}

void usbHandleKeyboard(unsigned char key) {
	if (usbSubState == 0) {
		if (key == '\r' || key == ' ') {
			usbSubState = 1;
		}
		return;
	}

	if (key == 'r' || key == 'R') {
		usbInitGame();
		usbSubState = 1;
	}
}

int main()
{
	iInitialize(800, 600, "The Last Escape");

	mciSendString(TEXT("open \"audio1.mp3\" type mpegvideo alias bgm"), NULL, 0, NULL);
	mciSendString(TEXT("open \"mouse.mp3\" type mpegvideo alias clicksound"), NULL, 0, NULL);

	srand((unsigned)time(0));

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

	map1Img = iLoadImage("Images/map1.png");
	cellMapImg = iLoadImage("Images/cellmap.png");
	cellMap2Img = iLoadImage("Images/cellmap2.png");
	cctvMapImg = iLoadImage("Images/cctvmap.png");
	alarmMapImg = iLoadImage("Images/alarmmap.png");

	note1Img = iLoadImage("Images/mapnote1.png");
	note2Img = iLoadImage("Images/mapnote2.png");
	note3Img = iLoadImage("Images/mapnote3.png");
	note4Img = iLoadImage("Images/mapnote4.png");

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

	// Image memory puzzle assets
	memoryImgBackground = iLoadImage("Images/route.png");
	memoryImgWp = iLoadImage("Images/wp.png");
	memoryImgCardBack = iLoadImage("Images/back.png");

	memoryImgChar[1] = iLoadImage("Images/mainchar1.png");
	memoryImgChar[2] = iLoadImage("Images/mainchar2.png");
	memoryImgChar[3] = iLoadImage("Images/mainchar3.png");
	memoryImgChar[4] = iLoadImage("Images/mainchar4.png");

	memoryImgItem[1] = iLoadImage("Images/01_prisoner.png");
	memoryImgItem[2] = iLoadImage("Images/02_guard.png");
	memoryImgItem[3] = iLoadImage("Images/03_keys.png");
	memoryImgItem[4] = iLoadImage("Images/04_flashlight.png");
	memoryImgItem[5] = iLoadImage("Images/05_vent.png");
	memoryImgItem[6] = iLoadImage("Images/06_crowbar.png");
	memoryImgItem[7] = iLoadImage("Images/07_screwdriver.png");
	memoryImgItem[8] = iLoadImage("Images/08_cash.png");

	imgCommonRoute = iLoadImage("Images/common route.png");
	imgCCTVBackground = iLoadImage("Images/cctv.png");

	// USB collection mini-game (Level 2) assets
	usbImgBg = iLoadImage("Images/usb room.png");
	usbImgWp = iLoadImage("Images/wp.png");
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

	iSetTimer(20, fixedUpdate);
	iSetTimer(100, loadingUpdate);
	iSetTimer(1000, narrativeTimer);
	iSetTimer(400, updateSequence);

	iSetTimer(30, memoryAnimationTimer);
	iSetTimer(120, usbAnimateCharacter);

	iStart();
	return 0;
}