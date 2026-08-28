#ifndef VARIABLES_H
#define VARIABLES_H

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

#endif