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

int mapHoverState = 0;

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

#define DODGE_MAX_BOXES 5

const int GAMESTATE_DODGE = 80;

bool dodgeGameStarted = false;
bool dodgeGameOver = false;
bool dodgeLevelComplete = false;

int dodgePlayerX;
int dodgePlayerY = 30;
int dodgePlayerWidth = 330;
int dodgePlayerHeight = 130;
int dodgePlayerSpeed = 6;
int dodgeActualPlayerWidth = 70;

int dodgeLevel = 1;
float dodgeLevelTimeLeft = 10.0f;

int dodgeBgImg = 0;
int dodgeBoxImg = 0;
int dodgeNoteImg = 0;
int dodgeImgStand = 0;
int dodgeImgLeft1 = 0, dodgeImgLeft2 = 0;
int dodgeImgRight1 = 0, dodgeImgRight2 = 0;
int dodgeCaughtPlayerImg = 0;

int dodgeCurrentAnimState = 0;
int dodgeAnimTimer = 0;

typedef struct
{
	int x;
	int y;
	int width;
	int height;
	int speed;
} DodgeBox;

DodgeBox dodgeBoxes[DODGE_MAX_BOXES];

void resetDodgeBox(int i);
void resetDodgeGame();
void nextDodgeLevel();
bool checkDodgeCollision(DodgeBox b);
void updateDodgeGame();
void drawDodgeGame();
void handleDodgeMouseClick(int mx, int my);
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

#define USB_GRID_SIZE 8
#define USB_TILE_SIZE 55
#define USB_BOARD_X ((800 - (USB_GRID_SIZE * USB_TILE_SIZE)) / 2)
#define USB_BOARD_Y 75

int usbSubState = 0;
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

bool usbCompletionTimerStarted = false;
double usbCompletionTimerStart = 0;

const int GAMESTATE_LEVEL2_MAP = 450;

int level2MapImg = 0;
int vaultImg = 0;
bool vaultUnlocked = false;

const int GAMESTATE_INVESTIGATION = 460;

int investStage = 1;
int investPiecesFoundCount = 0;

int investPieceX[6] = { 50, 400, 50, 400, 50, 400 };
int investPieceY[6] = { 50, 50, 250, 250, 400, 400 };

int investCorrectX[6] = { 265, 378, 470, 245, 350, 447 };
int investCorrectY[6] = { 316, 310, 317, 220, 220, 211 };

bool investCollected[6] = { false, false, false, false, false, false };
bool investPlaced[6] = { false, false, false, false, false, false };

int investDraggedPiece = -1;
bool investIsDragging = false;
int investGrabOffsetX = 0;
int investGrabOffsetY = 0;

const int INVEST_PIECE_SIZE_W = 120;
const int INVEST_PIECE_SIZE_H = 120;

bool investPuzzleCompletedFlag = false;
double investCompletionTimerStart = 0;

int investRoomImg = 0;
int investTableImg = 0;
int investPieceImg[6] = { 0, 0, 0, 0, 0, 0 };
int investNoteImg = 0;

void resetInvestPuzzle();
void checkInvestSearchLocation(int mx, int my);
void checkInvestPiecePlacement(int pieceIndex);
bool checkIfInvestPuzzleComplete();
void drawInvestPuzzle();
void handleInvestMouseDown(int mx, int my);
void handleInvestMouseUp(int mx, int my);
void handleInvestMouseMove(int mx, int my);

// ============================================================================
// VAULT RUNNER MINIGAME (merged from second project)
// Triggered by clicking the vault image on the GAMESTATE_LEVEL2_MAP screen
// once vaultUnlocked is true. All variables/functions are prefixed with "vr"
// to avoid name clashes with the rest of the game.
// ============================================================================
const int GAMESTATE_VAULT_RUNNER = 470;

bool vrIsStarted = false;
bool vrShowVault3 = false;
int vrVault1Img = 0;
int vrVault2Img = 0;
int vrVault3Img = 0;
int vrNoteImg = 0;

int vrRunnerX = 50;
int vrRunnerY = 200;
int vrRunnerDy = 0;
bool vrIsJumping = false;
int vrJumpCount = 0;
bool vrIsMouseHeld = false;
int vrFallCounter = 0;

int vrBoxX = 800;
int vrBoxY = 200;
int vrBoxWidth = 40;
int vrBoxHeight = 45;
int vrGameSpeed = 4;

int vrRockX = 1100;
int vrRockY = 200;

int vrDistance = 0;
int vrDistCounter = 0;
int vrCoinScore = 0;

int vrBgImage = 0;
int vrBgX1 = 0;
int vrBgX2 = 800;

int vrRunnerImg[3] = { 0, 0, 0 };
int vrCurrentFrame = 0;
int vrAnimTimer = 0;

int vrBall1X = 700, vrBall1Y = 220;
int vrBall2X = 1100, vrBall2Y = 285;
int vrRedBallX = 1500;
int vrRedBallY = 285;

bool vrGameOver = false;
bool vrGameWon = false;

// Vault3 "access granted" screen -> auto-advance to a loading screen after
// showing it for 2 seconds, then return to the level page.
bool vrVault3TimerStarted = false;
double vrVault3TimerStart = 0;

// New gamestate used only for the loading bar shown right after Vault
// Runner is won (background1.png with the same loading bar as elsewhere).
const int GAMESTATE_VR_WIN_LOADING = 480;

// True once the Vault Runner minigame (Level 2) has been completed. Used to
// unlock the Level 3 button on the level select page.
bool level2Completed = false;

int vrWinBgImg = 0; // Images/background1.png

// Level 3 button (locked/unlocked) + its background + the loading gamestate
// shown after clicking the unlocked Level 3 button. Level 3 gameplay itself
// is not implemented yet - it is left as a placeholder for later.
int level3UnlockedBtn = 0; // Images/levelbg5.png
int level3BgImg = 0;       // Images/level3bg.png
const int GAMESTATE_LEVEL3_LOADING = 490;

void vrResetGame();
void vrFixedUpdate();
void vrDraw();
void vrHandleMouseDown(int mx, int my);

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
	if (gameState != 0 && gameState != 5 && gameState != 6 && gameState != 56 && gameState != 57 &&
		gameState != GAMESTATE_VR_WIN_LOADING && gameState != GAMESTATE_LEVEL3_LOADING)
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
			gameState = GAMESTATE_LEVEL2_MAP;
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
			// Level 3 gameplay isn't built yet, so the bar just fills up
			// and stays on the level3bg.png placeholder screen.
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

	dodgeLevel = 1;
	dodgeLevelTimeLeft = 4.0f;
	dodgeCurrentAnimState = 0;

	for (int i = 0; i < DODGE_MAX_BOXES; i++)
		resetDodgeBox(i);
}

void nextDodgeLevel()
{
	dodgeLevel++;
	dodgeLevelTimeLeft = 3.0f;
	dodgeLevelComplete = false;

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

	dodgeLevelTimeLeft -= 0.02f;

	int rightBoundary = 800 - 250 - dodgeActualPlayerWidth;
	if (dodgePlayerX >= rightBoundary - 5)
	{
		dodgeLevelComplete = true;

		if (dodgeLevel == 1) {
			level1Completed = true;
		}
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

		iShowImage(50, 50, 100, 40, backImg);
		return;
	}

	iShowImage(0, 0, 800, 600, dodgeBgImg);

	iSetColor(255, 255, 255);
	iText(20, 570, "DODGE & REACH THE RIGHT SIDE!", GLUT_BITMAP_HELVETICA_18);

	char str[100];
	sprintf(str, "Level : %d", dodgeLevel);
	iText(20, 540, str, GLUT_BITMAP_HELVETICA_18);

	sprintf(str, "Time Left : %.1f s", dodgeLevelTimeLeft);
	iText(20, 515, str, GLUT_BITMAP_HELVETICA_18);

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

		iSetColor(0, 150, 0);
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

		iSetColor(255, 0, 0);
		iText(320, 55, "CAUGHT BY GUARD!", GLUT_BITMAP_TIMES_ROMAN_24);

		iSetColor(0, 0, 0);
		iText(305, 30, "Click Mouse to Restart", GLUT_BITMAP_HELVETICA_18);
	}

	iShowImage(50, 50, 100, 40, backImg);
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

void resetInvestPuzzle() {
	investStage = 1;
	investPiecesFoundCount = 0;
	investPuzzleCompletedFlag = false;
	investDraggedPiece = -1;
	investIsDragging = false;

	int defaultPieceX[6] = { 50, 400, 50, 400, 50, 400 };
	int defaultPieceY[6] = { 50, 50, 250, 250, 400, 400 };

	for (int i = 0; i < 6; i++) {
		investCollected[i] = false;
		investPlaced[i] = false;
		investPieceX[i] = defaultPieceX[i];
		investPieceY[i] = defaultPieceY[i];
	}
}

void checkInvestSearchLocation(int mx, int my) {
	if (investStage != 1) return;

	if (mx >= 350 && mx <= 480 && my >= 100 && my <= 180) { if (!investCollected[0]) { investCollected[0] = true; investPiecesFoundCount++; } }
	if (mx >= 60 && mx <= 160 && my >= 280 && my <= 360)  { if (!investCollected[1]) { investCollected[1] = true; investPiecesFoundCount++; } }
	if (mx >= 550 && mx <= 680 && my >= 240 && my <= 360) { if (!investCollected[2]) { investCollected[2] = true; investPiecesFoundCount++; } }
	if (mx >= 30 && mx <= 130 && my >= 40 && my <= 120)   { if (!investCollected[3]) { investCollected[3] = true; investPiecesFoundCount++; } }
	if (mx >= 190 && mx <= 260 && my >= 40 && my <= 160)  { if (!investCollected[4]) { investCollected[4] = true; investPiecesFoundCount++; } }
	if (mx >= 380 && mx <= 450 && my >= 220 && my <= 280) { if (!investCollected[5]) { investCollected[5] = true; investPiecesFoundCount++; } }

	if (investPiecesFoundCount >= 6) {
		investStage = 2;
	}
}

void checkInvestPiecePlacement(int pieceIndex) {
	int diffX = investPieceX[pieceIndex] - investCorrectX[pieceIndex];
	int diffY = investPieceY[pieceIndex] - investCorrectY[pieceIndex];

	if (diffX > -40 && diffX < 40 && diffY > -40 && diffY < 40) {
		investPieceX[pieceIndex] = investCorrectX[pieceIndex];
		investPieceY[pieceIndex] = investCorrectY[pieceIndex];
		investPlaced[pieceIndex] = true;
	}
}

bool checkIfInvestPuzzleComplete() {
	for (int i = 0; i < 6; i++) {
		if (!investPlaced[i]) return false;
	}
	return true;
}

void drawInvestPuzzle() {
	if (investStage == 1) {
		if (investRoomImg > 0) iShowImage(0, 0, 800, 600, investRoomImg);
		if (investNoteImg > 0) iShowImage(150, -25, 480, 280, investNoteImg);

		iSetColor(0, 0, 0);
		iText(220, 35, "Collect 6 torn pieces from the room", GLUT_BITMAP_HELVETICA_18);

		char counterText[50];
		sprintf(counterText, "Pieces Found: %d/6", investPiecesFoundCount);
		iSetColor(255, 255, 255);
		iText(30, 560, counterText, GLUT_BITMAP_HELVETICA_18);
	}
	else if (investStage == 2) {
		if (investTableImg > 0) iShowImage(0, 0, 800, 600, investTableImg);
		if (investNoteImg > 0) iShowImage(150, -25, 480, 280, investNoteImg);

		iSetColor(0, 0, 0);
		iText(190, 45, "Stage 2: Arrange the 6 pieces into position", GLUT_BITMAP_HELVETICA_18);

		for (int i = 0; i < 6; i++) {
			iSetColor(255, 255, 255);
			iRectangle(investCorrectX[i], investCorrectY[i], 80, 40);

			char outlineNum[10];
			sprintf(outlineNum, "Point %d", i + 1);
			iText(investCorrectX[i] + 15, investCorrectY[i] + 12, outlineNum, GLUT_BITMAP_HELVETICA_12);
		}

		for (int i = 0; i < 6; i++) {
			if (investPieceImg[i] > 0) {
				iShowImage(investPieceX[i], investPieceY[i], INVEST_PIECE_SIZE_W, INVEST_PIECE_SIZE_H, investPieceImg[i]);
			}
		}

		if (checkIfInvestPuzzleComplete() && !investPuzzleCompletedFlag) {
			investPuzzleCompletedFlag = true;
			investCompletionTimerStart = GetTickCount64();
		}

		if (investPuzzleCompletedFlag) {
			double elapsedTime = (GetTickCount64() - investCompletionTimerStart) / 1000.0;

			if (elapsedTime < 3.0) {
				iSetColor(0, 0, 255);
				iText(280, 20, "Assembling Room Data...", GLUT_BITMAP_HELVETICA_18);
			}
			else {
				vaultUnlocked = true;
				resetInvestPuzzle();
				gameState = GAMESTATE_LEVEL2_MAP;
			}
		}
	}

	iShowImage(50, 50, 100, 40, backImg);
}

void handleInvestMouseDown(int mx, int my) {
	if (mx >= 50 && mx <= 150 && my >= 50 && my <= 90) {
		gameState = GAMESTATE_LEVEL2_MAP;
		return;
	}

	if (investStage == 1) {
		checkInvestSearchLocation(mx, my);
	}
	else if (investStage == 2 && !investPuzzleCompletedFlag) {
		for (int i = 5; i >= 0; i--) {
			if (!investPlaced[i]) {
				if (mx >= investPieceX[i] && mx <= investPieceX[i] + INVEST_PIECE_SIZE_W &&
					my >= investPieceY[i] && my <= investPieceY[i] + INVEST_PIECE_SIZE_H) {

					investDraggedPiece = i;
					investIsDragging = true;
					investGrabOffsetX = mx - investPieceX[i];
					investGrabOffsetY = my - investPieceY[i];
					break;
				}
			}
		}
	}
}

void handleInvestMouseUp(int mx, int my) {
	if (investStage == 2 && investIsDragging && investDraggedPiece != -1) {
		checkInvestPiecePlacement(investDraggedPiece);
		investDraggedPiece = -1;
		investIsDragging = false;
	}
}

void handleInvestMouseMove(int mx, int my) {
	if (investStage == 2 && investIsDragging && investDraggedPiece != -1) {
		investPieceX[investDraggedPiece] = mx - investGrabOffsetX;
		investPieceY[investDraggedPiece] = my - investGrabOffsetY;
	}
}

// ----------------------------------------------------------------------------
// VAULT RUNNER MINIGAME - function definitions
// (Ported as-is from the second project; only variable/function names were
// prefixed with "vr" to avoid clashing with the rest of the game. No gameplay
// logic was changed.)
// ----------------------------------------------------------------------------

void vrResetGame() {
	vrIsStarted = false;
	vrShowVault3 = false;
	vrGameOver = false;
	vrGameWon = false;
	vrBoxX = 800;
	vrRockX = 1100;
	vrDistance = 0;
	vrDistCounter = 0;
	vrCoinScore = 0;
	vrRunnerY = 200;
	vrIsJumping = false;
	vrJumpCount = 0;
	vrIsMouseHeld = false;
	vrFallCounter = 0;
	vrGameSpeed = 4;
	vrBgX1 = 0;
	vrBgX2 = 800;
	vrBall1X = 700; vrBall1Y = 220;
	vrBall2X = 1100; vrBall2Y = 285;
	vrRedBallX = 1500; vrRedBallY = 285;
}

void vrFixedUpdate() {
	if (!vrIsStarted || vrGameOver) return;

	vrBgX1 -= vrGameSpeed;
	vrBgX2 -= vrGameSpeed;

	if (vrBgX1 <= -800) {
		vrBgX1 = vrBgX2 + 800;
	}
	if (vrBgX2 <= -800) {
		vrBgX2 = vrBgX1 + 800;
	}

	vrAnimTimer++;
	if (vrAnimTimer >= 6) {
		vrCurrentFrame = (vrCurrentFrame + 1) % 3;
		vrAnimTimer = 0;
	}

	vrDistCounter++;
	int threshold = vrIsMouseHeld ? 4 : 8;
	if (vrDistCounter % threshold == 0) {
		vrDistance++;
	}

	vrGameSpeed = 4 + (vrDistance / 150);
	if (vrGameSpeed > 12) {
		vrGameSpeed = 12;
	}

	vrBoxX -= vrGameSpeed;
	if (vrBoxX < -40) {
		vrBoxX = 850 + (rand() % 300);
	}

	vrRockX -= vrGameSpeed;
	if (vrRockX < -60) {
		vrRockX = 900 + (rand() % 400);
	}

	vrBall1X -= vrGameSpeed;
	if (vrBall1X < -20) {
		vrBall1X = 800 + (rand() % 300);
		vrBall1Y = (rand() % 2 == 0) ? 220 : 285;
	}

	vrBall2X -= vrGameSpeed;
	if (vrBall2X < -20) {
		vrBall2X = 900 + (rand() % 350);
		vrBall2Y = (rand() % 2 == 0) ? 220 : 285;
	}

	vrRedBallX -= vrGameSpeed;
	if (vrRedBallX < -20) {
		vrRedBallX = 1600 + (rand() % 500);
		vrRedBallY = (rand() % 2 == 0) ? 220 : 285;
	}

	if (vrIsJumping) {
		vrRunnerY += vrRunnerDy;

		if (vrRunnerDy > 0) {
			vrRunnerDy -= 2;
		}
		else {
			if (vrIsMouseHeld) {
				vrFallCounter++;
				if (vrFallCounter % 3 == 0) {
					vrRunnerDy -= 1;
				}
			}
			else {
				vrRunnerDy -= 2;
			}
		}

		if (vrRunnerY <= 200) {
			vrRunnerY = 200;
			vrIsJumping = false;
			vrJumpCount = 0;
			vrRunnerDy = 0;
			vrFallCounter = 0;
		}
	}

	if (vrBall1X + 12 >= vrRunnerX && vrBall1X - 12 <= vrRunnerX + 80 && vrBall1Y + 12 >= vrRunnerY && vrBall1Y - 12 <= vrRunnerY + 100) {
		vrCoinScore += 5;
		vrBall1X = 900 + (rand() % 300);
		vrBall1Y = (rand() % 2 == 0) ? 220 : 285;
		if (vrCoinScore >= 150) {
			vrGameOver = true;
			vrGameWon = true;
		}
	}

	if (vrBall2X + 12 >= vrRunnerX && vrBall2X - 12 <= vrRunnerX + 80 && vrBall2Y + 12 >= vrRunnerY && vrBall2Y - 12 <= vrRunnerY + 100) {
		vrCoinScore += 5;
		vrBall2X = 1000 + (rand() % 300);
		vrBall2Y = (rand() % 2 == 0) ? 220 : 285;
		if (vrCoinScore >= 150) {
			vrGameOver = true;
			vrGameWon = true;
		}
	}

	if (vrRedBallX + 12 >= vrRunnerX && vrRedBallX - 12 <= vrRunnerX + 80 && vrRedBallY + 12 >= vrRunnerY && vrRedBallY - 12 <= vrRunnerY + 100) {
		vrCoinScore += 15;
		vrRedBallX = 1600 + (rand() % 500);
		vrRedBallY = (rand() % 2 == 0) ? 220 : 285;
		if (vrCoinScore >= 150) {
			vrGameOver = true;
			vrGameWon = true;
		}
	}

	if (vrRunnerX + 50 >= vrBoxX && vrRunnerX <= vrBoxX + vrBoxWidth && vrRunnerY <= vrBoxY + vrBoxHeight) {
		vrGameOver = true;
		vrGameWon = false;
	}

	if (vrRunnerX + 50 >= vrRockX && vrRunnerX <= vrRockX + 50 && vrRunnerY <= vrRockY + 38) {
		vrGameOver = true;
		vrGameWon = false;
	}
}

void vrDraw() {
	if (!vrIsStarted) {
		iShowImage(0, 0, 800, 600, vrVault1Img);
		iShowImage(200, 45, 390, 180, vrNoteImg);
		iSetColor(20, 20, 20);
		iText(230, 80, "Click anywhere to disable the laser", GLUT_BITMAP_HELVETICA_18);
		return;
	}

	if (vrGameOver && vrGameWon) {
		if (!vrShowVault3) {
			iShowImage(0, 0, 800, 600, vrVault2Img);
			iShowImage(200, 45, 390, 180, vrNoteImg);
			iSetColor(20, 20, 20);
			iText(220, 80, "Click anywhere to use the access card", GLUT_BITMAP_HELVETICA_18);
		}
		else {
			iShowImage(0, 0, 800, 600, vrVault3Img);

			if (!vrVault3TimerStarted) {
				vrVault3TimerStarted = true;
				vrVault3TimerStart = GetTickCount64();
			}
			else {
				double elapsedTime = (GetTickCount64() - vrVault3TimerStart) / 1000.0;
				if (elapsedTime >= 2.0) {
					vrVault3TimerStarted = false;
					gameState = GAMESTATE_VR_WIN_LOADING;
					loadingStep = 0;
					if (musicPlaying) {
						mciSendString(TEXT("pause bgm"), NULL, 0, NULL);
					}
				}
			}
		}
		return;
	}

	iShowImage(vrBgX1, 0, 800, 600, vrBgImage);
	iShowImage(vrBgX2, 0, 800, 600, vrBgImage);

	iSetColor(255, 215, 0);
	iFilledCircle(vrBall1X, vrBall1Y, 12);
	iSetColor(255, 255, 200);
	iFilledCircle(vrBall1X - 3, vrBall1Y + 3, 3);

	iSetColor(255, 215, 0);
	iFilledCircle(vrBall2X, vrBall2Y, 12);
	iSetColor(255, 255, 200);
	iFilledCircle(vrBall2X - 3, vrBall2Y + 3, 3);

	iSetColor(220, 20, 60);
	iFilledCircle(vrRedBallX, vrRedBallY, 12);
	iSetColor(255, 182, 193);
	iFilledCircle(vrRedBallX - 3, vrRedBallY + 3, 3);

	iShowImage(vrRunnerX, vrRunnerY, 80, 100, vrRunnerImg[vrCurrentFrame]);

	iSetColor(139, 69, 19);
	iFilledRectangle(vrBoxX, vrBoxY, vrBoxWidth, vrBoxHeight);
	iSetColor(90, 40, 10);
	iRectangle(vrBoxX, vrBoxY, vrBoxWidth, vrBoxHeight);
	iSetColor(110, 50, 15);
	iLine(vrBoxX, vrBoxY, vrBoxX + vrBoxWidth, vrBoxY + vrBoxHeight);
	iLine(vrBoxX, vrBoxY + vrBoxHeight, vrBoxX + vrBoxWidth, vrBoxY);

	iSetColor(95, 85, 75);
	double vrRockPolyX[] = { (double)vrRockX, (double)vrRockX + 10, (double)vrRockX + 25, (double)vrRockX + 45, (double)vrRockX + 52, (double)vrRockX };
	double vrRockPolyY[] = { (double)vrRockY, (double)vrRockY + 22, (double)vrRockY + 38, (double)vrRockY + 28, (double)vrRockY, (double)vrRockY };
	iFilledPolygon(vrRockPolyX, vrRockPolyY, 6);

	iSetColor(130, 120, 110);
	iFilledCircle(vrRockX + 22, vrRockY + 22, 5);

	char vrDistStr[50], vrScoreStr[50];
	sprintf(vrDistStr, "DISTANCE: %05d m", vrDistance);
	sprintf(vrScoreStr, "SCORE:    %05d", vrCoinScore);

	iSetColor(255, 255, 255);
	iText(570, 550, vrDistStr, GLUT_BITMAP_HELVETICA_18);
	iText(570, 520, vrScoreStr, GLUT_BITMAP_HELVETICA_18);

	if (vrGameOver && !vrGameWon) {
		iSetColor(255, 50, 50);
		iText(340, 320, "GAME OVER", GLUT_BITMAP_HELVETICA_18);
		iSetColor(220, 220, 220);
		iText(295, 280, "CLICK TO RETRY", GLUT_BITMAP_HELVETICA_18);
	}
}

void vrHandleMouseDown(int mx, int my) {
	if (!vrIsStarted) {
		vrIsStarted = true;
		return;
	}
	if (vrGameOver) {
		if (vrGameWon) {
			if (!vrShowVault3) {
				vrShowVault3 = true;
				return;
			}
			else {
				vrResetGame();
				return;
			}
		}
		else {
			vrGameOver = false;
			vrGameWon = false;
			vrShowVault3 = false;
			vrBoxX = 800;
			vrRockX = 1100;
			vrDistance = 0;
			vrDistCounter = 0;
			vrCoinScore = 0;
			vrRunnerY = 200;
			vrIsJumping = false;
			vrJumpCount = 0;
			vrIsMouseHeld = false;
			vrFallCounter = 0;
			vrGameSpeed = 4;
			vrBgX1 = 0;
			vrBgX2 = 800;
			vrBall1X = 700; vrBall1Y = 220;
			vrBall2X = 1100; vrBall2Y = 285;
			vrRedBallX = 1500;
		}
	}
	else {
		vrIsMouseHeld = true;
		if (!vrIsJumping) {
			vrIsJumping = true;
			vrJumpCount = 1;
			vrRunnerDy = 22;
			vrFallCounter = 0;
		}
		else if (vrJumpCount == 1) {
			vrJumpCount = 2;
			vrRunnerDy = 20;
			vrFallCounter = 0;
		}
	}
}

void iDraw()
{
	iClear();
	iSetColor(0, 0, 0);
	iFilledRectangle(0, 0, 800, 600);

	if (gameState == 0 || gameState == 5 || gameState == 6 || gameState == 57 || gameState == GAMESTATE_VR_WIN_LOADING || gameState == GAMESTATE_LEVEL3_LOADING)
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

		if (level2Completed) {
			iShowImage(492, 115, 175, 342, level3UnlockedBtn);
		}
		else {
			iShowImage(492, 115, 175, 342, level3Btn);
		}
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

	if (gameState == 100 || gameState == 210 || gameState == 300 || gameState == 350 || gameState == 400 || gameState == 70 || gameState == 71 || ((gameState >= 50 && gameState <= 60) && gameState != 56 && gameState != 57) || gameState == GAMESTATE_DODGE || gameState == GAMESTATE_LEVEL2_MAP || gameState == GAMESTATE_INVESTIGATION)
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

	if (gameState == 70 || gameState == 71 || ((gameState >= 50 && gameState <= 60) && gameState != 56 && gameState != 57) || gameState == GAMESTATE_DODGE)
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

		if (gameState == 100 || gameState == 300 || gameState == 350 || gameState == 400 || gameState == 70 || gameState == 71 || ((gameState >= 50 && gameState <= 60) && gameState != 56 && gameState != 57) || gameState == GAMESTATE_DODGE || gameState == GAMESTATE_LEVEL2_MAP || gameState == GAMESTATE_INVESTIGATION)
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

		if (gameState == 70 || gameState == 71 || ((gameState >= 50 && gameState <= 60) && gameState != 56 && gameState != 57) || gameState == GAMESTATE_DODGE)
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
				gameState = 400;
				usbInitGame();
				return;
			}
			else if (mx >= 320 && mx <= 480 && my >= 350 && my <= 550)
			{
				resetInvestPuzzle();
				gameState = GAMESTATE_INVESTIGATION;
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
					resetDodgeGame();
					gameState = GAMESTATE_DODGE;
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
}

void iMouseMove(int mx, int my)
{
	if (gameState == GAMESTATE_INVESTIGATION)
	{
		handleInvestMouseMove(mx, my);
	}
}

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
	usbCompletionTimerStarted = false;
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
		iText(220, 440, "Character acquired the USB! Press R to Restart.", GLUT_BITMAP_HELVETICA_18);

		if (!usbCompletionTimerStarted) {
			usbCompletionTimerStarted = true;
			usbCompletionTimerStart = GetTickCount64();
		}
		else {
			double elapsedTime = (GetTickCount64() - usbCompletionTimerStart) / 1000.0;
			if (elapsedTime >= 3.0) {
				usbCompletionTimerStarted = false;
				gameState = GAMESTATE_LEVEL2_MAP;
			}
		}
	}
	else if (usbSubState == 3) {
		iSetColor(255, 50, 50);
		iText(265, 300, "LOCKDOWN TRIGGERED!", GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(255, 255, 255);
		iText(310, 260, "Press R to Retry", GLUT_BITMAP_HELVETICA_18);
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
	level3UnlockedBtn = iLoadImage("Images/levelbg5.png");
	level3BgImg = iLoadImage("Images/level3bg.png");

	map1Img = iLoadImage("Images/map1.png");
	cellMapImg = iLoadImage("Images/cellmap.png");
	cellMap2Img = iLoadImage("Images/cellmap2.png");
	cctvMapImg = iLoadImage("Images/cctvmap.png");
	alarmMapImg = iLoadImage("Images/alarmmap.png");

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

	dodgeBgImg = iLoadImage("Images/bk.png");
	dodgeBoxImg = iLoadImage("Images/box.png");
	dodgeNoteImg = iLoadImage("Images/note.png");
	dodgeImgStand = iLoadImage("Images/stand.png");
	dodgeImgLeft1 = iLoadImage("Images/left1.png");
	dodgeImgLeft2 = iLoadImage("Images/left2.png");
	dodgeImgRight1 = iLoadImage("Images/right1.png");
	dodgeImgRight2 = iLoadImage("Images/right2.png");
	dodgeCaughtPlayerImg = iLoadImage("Images/caughtplayer.png");
	resetDodgeGame();

	imgCommonRoute = iLoadImage("Images/common route.png");
	imgCCTVBackground = iLoadImage("Images/cctv.png");

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

	// Vault Runner minigame images
	vrVault1Img = iLoadImage("Images/vault1.png");
	vrVault2Img = iLoadImage("Images/vault2.png");
	vrVault3Img = iLoadImage("Images/vault3.png");
	vrNoteImg = iLoadImage("Images/note.png");
	vrBgImage = iLoadImage("Images/background.png");
	vrRunnerImg[0] = iLoadImage("Images/player1.png");
	vrRunnerImg[1] = iLoadImage("Images/player2.png");
	vrRunnerImg[2] = iLoadImage("Images/player3.png");
	vrWinBgImg = iLoadImage("Images/background1.png");

	iSetTimer(20, fixedUpdate);
	iSetTimer(100, loadingUpdate);
	iSetTimer(1000, narrativeTimer);
	iSetTimer(400, updateSequence);

	iSetTimer(120, usbAnimateCharacter);

	iStart();
	return 0;
}