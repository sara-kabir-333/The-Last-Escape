#pragma once
#include <ctime>


int map1Img = 0;
int cellMapImg = 0;
int cellMap2Img = 0;
int cctvMapImg = 0;
int alarmMapImg = 0;
bool cctvUnlocked = false;
bool switchPuzzleCompleted = false;

int mapHoverState = 0;

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

int playerIdleFrame = 0;
int playerIdleCounter = 0;

int playerX = 580;
int playerY = 130;
bool playerRun = false;
int playerFrame = 0;

int guardX = 40;
int guardY = 271;

bool moveRight = true;
int guardFrame = 0;
int guardAnimCounter = 0;

const int L1_GUARD_W = 85;    // was 75
const int L1_GUARD_H = 115;   // was 105
const int L1_PLAYER_RUN_W = 105;
const int L1_PLAYER_RUN_H = 165;
const int L1_PLAYER_STAND_W = 105;  // was 90 (width only)
const int L1_PLAYER_STAND_H = 120;  // unchanged

const int L1_CAUGHT_GUARD_W = 85;    // was 75
const int L1_CAUGHT_GUARD_H = 115;   // was 105
const int L1_CAUGHT_PLAYER_W = 105;  // was 90
const int L1_CAUGHT_PLAYER_H = 130;  // was 120
const int L1_CAUGHT_GUARD_Y = 271;   // was guardY (276)
const int L1_CAUGHT_PLAYER_Y = 125;  // was playerY (130)

// The patrol-pattern question is only shown for 5 seconds now (was 10).
const int L1_QUESTION_SECONDS = 5;

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
int charY = 146;
int charFrame = 0;
int targetX = -1;

int solvedTickCounter = 0;
bool isWaitingToRun = false;
int switchLevelDelayCounter = 0;
bool isWaitingForSwitchLevel = false;

int sit1Timer = 0;
int gameplayCounter = 0;

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

// Timer HUD image (timer.png) used by the Dodge Game screen. Drawn at the
// same position/size as the score HUD (score.png), with the countdown value
// drawn on top of it.
int timerImg = 0;

int dodgeCurrentAnimState = 0;
int dodgeAnimTimer = 0;

// After successfully dodging all the boxes, the character keeps auto-running
// right towards the door (drawn in fallingboxbg.png) instead of freezing in
// place, so the level ending reads as "reaching the door" rather than just
// stopping mid-air.
bool dodgeRunningToDoor = false;
const int DODGE_DOOR_X = 750;

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
void updateSequence();
void createSequence();

// ----------------------------------------------------------------------------
// NEW: instruction/"note" screens inserted ahead of a few minigames. Each one
// just shows a background plus a note image and a Next button; clicking Next
// starts the game exactly like it used to start before these were added.
// ----------------------------------------------------------------------------
const int GAMESTATE_DODGE_NOTE = 500;       // shown before GAMESTATE_DODGE

// NEW: exactly the same idea as GAMESTATE_LEVEL2_NOTE, but for Level 1. It is
// shown once right after the level 1 loading screen: map1.png with intro.png
// in the middle (same size/place as the level 2 note) plus a Next button.
// Clicking Next drops the player on the normal level 1 map (gameState 350),
// which then behaves exactly as it did before.
const int GAMESTATE_LEVEL1_NOTE = 590;

int dodgeIntroNoteImg = 0;     // Images/dodgenote.png
int introImg = 0;              // Images/intro.png  (level 1 map instruction)