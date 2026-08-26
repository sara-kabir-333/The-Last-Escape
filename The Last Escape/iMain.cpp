#define _CRT_SECURE_NO_WARNINGS
#include "iGraphics.h"
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

// Define all global variables
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

int backImg = 0;
int nextImg = 0;

int levelBg = 0;
int level1Bg = 0;
int level2Bg = 0;
int level1Btn = 0, level2Btn = 0, level3Btn = 0, level2UnlockedBtn = 0;
bool level1Completed = false;

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

int que1 = 0, que2 = 0, que3 = 0, que4 = 0, que5 = 0;

int imgBackground = 0;
int imgLockScreen = 0;
int imgEscapeScreen = 0;
int imgnote = 0;
int imgsit1 = 0;
int imgsit2 = 0;

int imgCommonRoute = 0;
int imgCCTVBackground = 0;
int imgChar[4] = { 0 };

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
bool rReleased = true;

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

#include "variables.h"
#include "menu.h"
#include "functions.h"

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

	backImg = iLoadImage("Images/backimage.png");
	nextImg = iLoadImage("Images/next.png");

	level1Bg = iLoadImage("Images/level1bg.png");
	level2Bg = iLoadImage("Images/level2bg.png");
	levelBg = iLoadImage("Images/levelbg.png");
	level1Btn = iLoadImage("Images/levelbg1.png");
	level2Btn = iLoadImage("Images/levelbg2.png");
	level3Btn = iLoadImage("Images/levelbg3.png");
	level2UnlockedBtn = iLoadImage("Images/levelbg4.png");

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

	que1 = iLoadImage("Images/que1.png");
	que2 = iLoadImage("Images/que2.png");
	que3 = iLoadImage("Images/que3.png");
	que4 = iLoadImage("Images/que4.png");
	que5 = iLoadImage("Images/que5.png");

	imgCommonRoute = iLoadImage("Images/common route.png");
	imgCCTVBackground = iLoadImage("Images/cctv.png");

	imgChar[0] = iLoadImage("Images/mainchar1.png");
	imgChar[1] = iLoadImage("Images/mainchar2.png");
	imgChar[2] = iLoadImage("Images/mainchar3.png");
	imgChar[3] = iLoadImage("Images/mainchar4.png");

	iSetTimer(200, loadingUpdate);
	iSetTimer(200, fixedUpdate);
	iSetTimer(400, updateSequence);
	iSetTimer(1000, narrativeTimer);

	iStart();
	return 0;
}