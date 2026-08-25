#ifndef VARIABLES_H
#define VARIABLES_H

#include <time.h>

// --- IMAGES ---
int loadBg;
int menuBg;

int about1, about2, about3, about4, about5;
int aboutBg1, aboutBg2;

int backImg;
int nextImg;

int levelBg;
int level1Bg;
int level1Btn, level2Btn, level3Btn;

int btnPlay, btnAbout, btnSetting, btnExit;
int btnPlayHover, btnAboutHover, btnSettingHover, btnExitHover;

int bgOne;
int bgTwo;

int wpOne;
int wpTwo;
int wpThree;

int playerImg;
int playerOne;
int playerTwo;
int playerThree;

int guard1;
int guard3;
int guard4;
int guard5;

int que1, que2, que3, que4, que5;

int imgBackground;    // b1.png
int imgLockScreen;    // b3.png
int imgEscapeScreen;  // b4.png
int imgnote;          // note.png
int imgsit1;          // sit1.png
int imgsit2;          // sit2.png

// --- SWITCH PUZZLE IMAGES ---
int imgCommonRoute;
int imgCCTVBackground;
int imgChar[4];

// --- GAME STATES & CONTROLS ---
int gameState = 0;
int loadingStep = 0;
int btnHoverState = 0;

// --- GUARD & PLAYER & NUMBER PUZZLE VARIABLES ---
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
clock_t questionStartTime;

bool showQuestion = true;
bool solved = false;
bool wrong = false;

bool keyReleased = true;
bool digitReleased = true;
bool rReleased = true;

bool playerRunning = false;
bool startRun = false;
bool playerEscaped = false;
bool finalMessageStarted = false;
bool finalMessageShown = false;

bool backScene = false;
bool levelFinished = false;

// --- COLOR SEQUENCE PUZZLE VARIABLES ---
int boxSize = 120;
int redX = 100, redY = 300;
int blueX = 250, blueY = 300;
int greenX = 400, greenY = 300;
int yellowX = 550, yellowY = 300;

int sequence[5];
int level = 3;
int playerInput[5];
int inputIndex = 0;

int currentDisplayIndex = 0;
int activeDisplayColor = -1;
int displayTimer = 0;

// --- SWITCH PUZZLE VARIABLES ---
int switchSequence[5];
int switchCurrentInput = 0;

bool switchShowSequence = true;
bool switchSolved = false;
bool switchWrong = false;
bool switchKeyReleased = true;
bool switchPlayerRunning = false;

int switchTickCounter = 0;
int switchSolvedTickCounter = 0;

// Prisoner character position & movement for Switch Puzzle / Common Route
int charX = 50;
int charY = 150;
int charFrame = 0;
int targetX = -1;

// --- TIMING & TRANSITION VARIABLES ---
int solvedTickCounter = 0;
bool isWaitingToRun = false;
int switchLevelDelayCounter = 0;
bool isWaitingForSwitchLevel = false;

// --- NARRATIVE TIMERS ---
int sit1Timer = 0;
int gameplayCounter = 0;

#endif