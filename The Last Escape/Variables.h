#ifndef VARIABLES_H
#define VARIABLES_H

#include <ctime>

extern int loadBg;
extern int menuBg;
extern int settingsImg;
extern int settingsOnImg;
extern int on1, on2;
extern int off1, off2;

extern int pauseImg;
extern int pauseToPlayImg;
extern bool isGamePaused;

extern bool showSettingsPanel;
extern bool musicPlaying;
extern bool soundEnabled;

extern int about1, about2, about3, about4, about5;

extern int backImg;
extern int nextImg;

extern int levelBg;
extern int level1Bg;
extern int level2Bg;
extern int level1Btn, level2Btn, level3Btn, level2UnlockedBtn;
extern bool level1Completed;

extern int btnPlay, btnAbout, btncredit, btnExit;
extern int btnPlayHover, btnAboutHover, btncreditHover, btnExitHover;

extern int bgOne;
extern int bgTwo;

extern int wpTwo;
extern int wpThree;

extern int playerImg;
extern int playerOne;
extern int playerTwo;
extern int playerThree;

extern int guard1;
extern int guard3;
extern int guard4;
extern int guard5;

extern int que1, que2, que3, que4, que5;

extern int imgBackground;
extern int imgLockScreen;
extern int imgEscapeScreen;
extern int imgnote;
extern int imgsit1;
extern int imgsit2;

extern int imgCommonRoute;
extern int imgCCTVBackground;
extern int imgChar[4];

extern int gameState;
extern int loadingStep;
extern int btnHoverState;

extern int x;
extern int y;

extern int playerIdleFrame;
extern int playerIdleCounter;

extern int playerX;
extern int playerY;
extern bool playerRun;
extern int playerFrame;

extern int guardX;
extern int guardY;
extern bool moveRight;
extern int guardFrame;
extern int guardAnimCounter;

extern bool puzzleStart;
extern bool puzzleSolved;
extern bool puzzleWrong;

extern bool showWpOne;
extern bool showWpTwo;
extern bool showWpThree;
extern bool puzzleScreen;

extern char answer[5][4];

extern int currentPuzzle;
extern int current;
extern clock_t questionStartTime;

extern bool showQuestion;
extern bool solved;
extern bool wrong;

extern bool keyReleased;
extern bool digitReleased;
extern bool rReleased;

extern bool playerRunning;
extern bool startRun;
extern bool playerEscaped;
extern bool finalMessageStarted;
extern bool finalMessageShown;

extern bool backScene;
extern bool levelFinished;

extern int boxSize;
extern int redX, redY;
extern int blueX, blueY;
extern int greenX, greenY;
extern int yellowX, yellowY;
extern int cyanX, cyanY;
extern int magentaX, magentaY;
extern int orangeX, orangeY;

extern int sequence[10];
extern int level;
extern int playerInput[10];
extern int inputIndex;

extern int currentDisplayIndex;
extern int activeDisplayColor;
extern int displayTimer;

extern int switchSequence[5];
extern int switchCurrentInput;

extern bool switchShowSequence;
extern bool switchSolved;
extern bool switchWrong;
extern bool switchKeyReleased;
extern bool switchPlayerRunning;

extern int switchTickCounter;
extern int switchSolvedTickCounter;

extern int charX;
extern int charY;
extern int charFrame;
extern int targetX;

extern int solvedTickCounter;
extern bool isWaitingToRun;
extern int switchLevelDelayCounter;
extern bool isWaitingForSwitchLevel;

extern int sit1Timer;
extern int gameplayCounter;

#endif