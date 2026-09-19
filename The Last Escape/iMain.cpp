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

// ----------------------------------------------------------------------------
// LEVEL 1 (gameState 60) sprite sizes. The guard and the player were drawn too
// small, so only their width/height are scaled up here - every x/y position in
// the scene is left exactly as it was.
//   too small -> increase these
//   too big   -> decrease these
// ----------------------------------------------------------------------------
const int L1_GUARD_W = 75;
const int L1_GUARD_H = 105;
const int L1_PLAYER_RUN_W = 105;
const int L1_PLAYER_RUN_H = 165;
const int L1_PLAYER_STAND_W = 90;
const int L1_PLAYER_STAND_H = 120;

// "Caught by the guard" screen: same x/y as before, only bigger.
const int L1_CAUGHT_GUARD_W = 75;
const int L1_CAUGHT_GUARD_H = 105;
const int L1_CAUGHT_PLAYER_W = 90;
const int L1_CAUGHT_PLAYER_H = 120;

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
// to avoid name clashes with the rest of the game. No gameplay logic was
// changed.
// ============================================================================
const int GAMESTATE_VAULT_RUNNER = 470;

bool vrIsStarted = false;
bool vrShowVault3 = false;
int vrVault1Img = 0;
int vrVault2Img = 0;
int vrVault3Img = 0;
int vrNoteImg = 0;

// CHANGED: the runner sprite was a bit small, so it is now drawn slightly
// bigger. Its y position (vrRunnerY) is untouched - only the drawn size (and
// therefore the hitbox width/height) grew.
//   too small -> increase these
//   too big   -> decrease these
const int VR_RUNNER_W = 100;
const int VR_RUNNER_H = 125;

int vrRunnerX = 50;
int vrRunnerY = 200;
int vrRunnerDy = 0;
bool vrIsJumping = false;
int vrJumpCount = 0;
bool vrIsMouseHeld = false;
int vrFallCounter = 0;

// CHANGED: the box obstacle was far too small compared to the stone, so its
// width/height were scaled up to roughly match the rock's size. vrBoxY is
// unchanged, so it still sits on exactly the same ground line.
int vrBoxX = 800;
int vrBoxY = 200;
int vrBoxWidth = 55;
int vrBoxHeight = 50;
int vrGameSpeed = 4;

// Runner sprite is drawn at VR_RUNNER_W x VR_RUNNER_H but has transparent
// padding around the visible character, so a full-size hitbox triggers
// collisions well before the character visually touches anything. These
// insets shrink the hitbox down to roughly the visible character silhouette.
//   still triggering too early  -> increase the inset
//   overlapping visibly before game over -> decrease the inset
const int VR_RUNNER_HITBOX_INSET_X = 27;
const int VR_RUNNER_HITBOX_INSET_Y = 19;
const int VR_OBSTACLE_HITBOX_INSET = 8;

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
// shown after clicking the unlocked Level 3 button.
int level3UnlockedBtn = 0; // Images/levelbg5.png
int level3BgImg = 0;       // Images/level3bg.png
const int GAMESTATE_LEVEL3_LOADING = 490;



void vrResetGame();
void vrFixedUpdate();
void vrDraw();
void vrHandleMouseDown(int mx, int my);

// ----------------------------------------------------------------------------
// NEW: instruction/"note" screens inserted ahead of a few minigames. Each one
// just shows a background plus a note image and a Next button; clicking Next
// starts the game exactly like it used to start before these were added.
// ----------------------------------------------------------------------------
const int GAMESTATE_DODGE_NOTE = 500;       // shown before GAMESTATE_DODGE
const int GAMESTATE_LEVEL2_NOTE = 510;      // shown once, right after the level 2 loading screen, before GAMESTATE_LEVEL2_MAP
const int GAMESTATE_USB_NOTE = 520;         // shown before the USB match-3 minigame (gameState 400)
const int GAMESTATE_INVEST_NOTE = 530;      // shown before GAMESTATE_INVESTIGATION
const int GAMESTATE_GUNCOLLECT_NOTE = 540;  // shown right after the level 3 loading bar finishes

// NEW: exactly the same idea as GAMESTATE_LEVEL2_NOTE, but for Level 1. It is
// shown once right after the level 1 loading screen: map1.png with intro.png
// in the middle (same size/place as the level 2 note) plus a Next button.
// Clicking Next drops the player on the normal level 1 map (gameState 350),
// which then behaves exactly as it did before.
const int GAMESTATE_LEVEL1_NOTE = 590;

int dodgeIntroNoteImg = 0;     // Images/dodgenote.png
int level2NoteImg = 0;         // Images/level2note.png
int usbNoteImg = 0;            // Images/usbnote.png
int evidenceRoomNoteImg = 0;   // Images/evidenceroomnote.png
int gunCollectImg = 0;         // Images/guncollect.png
int introImg = 0;              // Images/intro.png  (level 1 map instruction)

// ============================================================================
// LEVEL 3 FIGHT MINIGAME (merged from the "Level 3 - Prison Fight" project)
// Triggered by clicking Next on the GAMESTATE_GUNCOLLECT_NOTE screen. All
// variables/functions are prefixed with "lv3" to avoid name clashes with the
// rest of the game, same convention as the "vr" (Vault Runner) minigame.
// Gameplay logic kept as close to the original standalone file as possible.
// ============================================================================
const int GAMESTATE_LEVEL3_FIGHT = 550;

// lv3SubState: 0 = fighting the guard, 1 = guard defeated / collect the gun,
// 2 = walking to the door after collecting the gun, 3 = stopped at the door.
int lv3SubState = 0;

const int LV3_HERO_START_X = 100;
const int LV3_HERO_START_Y = 100;
const int LV3_HERO_START_HEALTH = 50;

int lv3HeroX = LV3_HERO_START_X;
int lv3HeroY = LV3_HERO_START_Y;
int lv3HeroWidth = 200;
int lv3HeroHeight = 150;
int lv3HeroHealth = LV3_HERO_START_HEALTH;

// Hero Combat & Movement States
bool lv3IsAttacking = false;
int lv3AttackCooldown = 0;
int lv3HeroActionType = 1; // 1 = Punch, 2 = Kick

// Hero Walking Animation Frames (maincharstand -> mainchar2 -> mainchar3)
int lv3HeroWalkFrame = 0;
int lv3HeroWalkAnimTimer = 0;

// Tracks whether hero has reached/collided with the guard
bool lv3HeroReachedGuard = false;

// Cooldown between registered attack clicks (slows the fight down)
int lv3ClickCooldownTimer = 0;
const int LV3_CLICK_COOLDOWN = 20; // frames between allowed hits

// Screen centre both fighters walk to and stop at, so the fight happens in
// the middle of the screen instead of wherever they happened to collide.
const int LV3_CENTER_X = 400;
const int LV3_FIGHT_OVERLAP = 125;
const int LV3_HERO_STOP_X = 263;
const int LV3_GUARD_STOP_X = 338;

// Guard Structure
struct Lv3Guard {
	int x, y;
	int width, height;
	int health;
	bool isAlive;
};

const int LV3_GUARD_START_X = 600;
const int LV3_GUARD_START_HEALTH = 45;

Lv3Guard lv3Guard = { LV3_GUARD_START_X, 100, 200, 150, LV3_GUARD_START_HEALTH, true };
int lv3GuardActionFrame = 0;
int lv3GuardAnimTimer = 0;
int lv3AttackTimer = 0;

// Walking-to-the-door sequence played once the gun has been collected.
const int LV3_DOOR_STOP_X = 620;

int lv3BgImageId = 0;
int lv3HeroStandId = 0;
int lv3HeroAnim2Id = 0;
int lv3HeroAnim3Id = 0;
int lv3HeroPunchId = 0;
int lv3HeroKickId = 0;
int lv3GuardStId = 0;
int lv3GuardPunch1Id = 0;
int lv3GuardPunch2Id = 0;
int lv3GunImageId = 0;
int lv3NoteImg = 0;

// Image-based Hero/Guard health bars.
int lv3HeroLifeImg[5] = { 0, 0, 0, 0, 0 };  // charlife100/75/50/25/0.png
int lv3GuardLifeImg[4] = { 0, 0, 0, 0 };    // guardlife100/75/50/25.png

void lv3RestartGame();
void lv3UpdateGame();
void lv3Draw();
void lv3HandleMouseDown(int mx, int my);
int lv3GetHeroLifeImg(int health, int maxHealth);
int lv3GetGuardLifeImg(int health, int maxHealth);

// ----------------------------------------------------------------------------
// LEVEL 3 - GANGSTER SHOOTOUT MINIGAME
// ----------------------------------------------------------------------------
const int GAMESTATE_LEVEL3_SHOOTOUT = 560;

// True once all 3 gangsters have been defeated (Level 3 fully completed).
bool level3Completed = false;

int gsState = -1;

void gsResetGame();
void gsUpdateGame();
void gsDraw();
void gsMouseMove(int mx, int my);
void gsHandleLeftClick(int mx, int my);
void gsHandleRightClick(int mx, int my);

// ============================================================================
// TRAFFIC RUNNER MINIGAME
// ============================================================================
const int GAMESTATE_TRAFFIC = 570;
const int GAMESTATE_TRAFFIC_LOADING = 580;

const int TR_SCREEN_W = 800;
const int TR_SCREEN_H = 600;

int trBgY1 = 0;
int trBgY2 = 600;

int trStartImg = 0, trBgImg = 0, trWinImg1 = 0, trWinImg2 = 0, trWinImg3 = 0, trFinalBgImg = 0;
int trNoteImg = 0;
int trScoreImg = 0; // Images/score.png - also reused by the Vault Runner HUD
int trRunImg1 = 0, trRunImg2 = 0;
int trCarImgs[6] = { 0, 0, 0, 0, 0, 0 };
int trTruckImgs[4] = { 0, 0, 0, 0 };

bool trGameStarted = false;

int trCurrentRunFrame = 0;
bool trIsJumping = false;
int trPlayerLane = 1;

int trLaneX[3] = { 230, 370, 510 };
int trBasePlayerY = 80;
int trPlayerY = 80;
int trJumpHeight = 0;
bool trJumpUp = true;
bool trIsOnRoof = false;

double trPlayerDrawX = 375.0;

const int TR_MAX_OBS = 25;

struct TrObstacle {
	int lane;
	int y;
	int type;
	int colorIndex;
	bool active;
};

TrObstacle trObsList[TR_MAX_OBS];

const int TR_CAR_W = 70, TR_CAR_H = 120;
const int TR_TRUCK_W = 80, TR_TRUCK_H = 190;

const int TR_MAX_ROOF_GEMS = 200;

struct TrGem {
	int lane;
	int y;
	bool active;
};

TrGem trRoofGems[TR_MAX_ROOF_GEMS];

const int TR_MAX_MANHOLES = 5;

struct TrManhole {
	int lane;
	int y;
	bool active;
};

TrManhole trManholeList[TR_MAX_MANHOLES];
const int TR_MANHOLE_W = 65, TR_MANHOLE_H = 65;

int trScore = 0;
bool trGameOver = false;

int trWinState = 0;
int trWinTimer = 0;

void trResetGame();
void trSpawnTrafficCluster(int startY);
void trUpdateObstacles();
void trUpdateRoofGems();
void trUpdateManholes();
void trDrawGreenGem(int x, int y);
void trDrawManhole(int x, int y);
void trDrawCar(int x, int y, int colorIndex);
void trDrawTruck(int x, int y, int colorIndex);
void trDraw();
void trFixedUpdate();
void trHandleMouseDown(int mx, int my);

// ----------------------------------------------------------------------------
// Centralised helpers deciding on which game states the Settings icon and the
// Pause icon should be visible / clickable. Both the drawing code (iDraw) and
// the input code (iMouse) call these SAME functions, so the two can never
// drift apart.
//
// CHANGED:
//   * Settings is now shown on EVERY screen except the loading screens.
//   * Pause is now also available in every Level 3 screen (fight, shootout,
//     traffic runner) exactly like it already was in Levels 1 and 2 - but it
//     is still hidden on every instruction/note screen (and on the shootout's
//     own instruction screen, gsState == -1, and on the traffic runner's
//     "click to start" screen).
// ----------------------------------------------------------------------------
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
	// Everywhere except the loading screens.
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
			// CHANGED: level 1 now shows its own instruction screen
			// (map1.png + intro.png + Next) before the normal map, exactly
			// like level 2 already did.
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
			// CHANGED: the patrol pattern question is only visible for 5
			// seconds now (it used to stay up for 10).
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
	dodgeRunningToDoor = false;

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
	dodgeRunningToDoor = false;

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

	if (dodgeRunningToDoor)
	{
		dodgePlayerX += dodgePlayerSpeed;

		dodgeAnimTimer++;
		int frame = (dodgeAnimTimer / 6) % 2;
		dodgeCurrentAnimState = (frame == 0) ? 3 : 4;

		if (dodgePlayerX >= DODGE_DOOR_X)
		{
			dodgePlayerX = DODGE_DOOR_X;
			dodgeCurrentAnimState = 0;
			dodgeRunningToDoor = false;
			dodgeLevelComplete = true;

			if (dodgeLevel == 1) {
				level1Completed = true;
			}
		}
		return;
	}

	dodgeLevelTimeLeft -= 0.02f;

	int rightBoundary = 800 - 250 - dodgeActualPlayerWidth;
	if (dodgePlayerX >= rightBoundary - 5)
	{
		dodgeRunningToDoor = true;
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
	vrVault3TimerStarted = false;
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
	if (vrBoxX < -vrBoxWidth) {
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

	if (vrBall1X + 12 >= vrRunnerX && vrBall1X - 12 <= vrRunnerX + VR_RUNNER_W && vrBall1Y + 12 >= vrRunnerY && vrBall1Y - 12 <= vrRunnerY + VR_RUNNER_H) {
		vrCoinScore += 5;
		vrBall1X = 900 + (rand() % 300);
		vrBall1Y = (rand() % 2 == 0) ? 220 : 285;
		if (vrCoinScore >= 150) {
			vrGameOver = true;
			vrGameWon = true;
		}
	}

	if (vrBall2X + 12 >= vrRunnerX && vrBall2X - 12 <= vrRunnerX + VR_RUNNER_W && vrBall2Y + 12 >= vrRunnerY && vrBall2Y - 12 <= vrRunnerY + VR_RUNNER_H) {
		vrCoinScore += 5;
		vrBall2X = 1000 + (rand() % 300);
		vrBall2Y = (rand() % 2 == 0) ? 220 : 285;
		if (vrCoinScore >= 150) {
			vrGameOver = true;
			vrGameWon = true;
		}
	}

	if (vrRedBallX + 12 >= vrRunnerX && vrRedBallX - 12 <= vrRunnerX + VR_RUNNER_W && vrRedBallY + 12 >= vrRunnerY && vrRedBallY - 12 <= vrRunnerY + VR_RUNNER_H) {
		vrCoinScore += 15;
		vrRedBallX = 1600 + (rand() % 500);
		vrRedBallY = (rand() % 2 == 0) ? 220 : 285;
		if (vrCoinScore >= 150) {
			vrGameOver = true;
			vrGameWon = true;
		}
	}

	// Hitboxes shrunk with VR_RUNNER_HITBOX_INSET_X/Y and
	// VR_OBSTACLE_HITBOX_INSET so game over only triggers once the visible
	// character actually touches the box/stone.
	if (vrRunnerX + VR_RUNNER_W - VR_RUNNER_HITBOX_INSET_X >= vrBoxX + VR_OBSTACLE_HITBOX_INSET &&
		vrRunnerX + VR_RUNNER_HITBOX_INSET_X <= vrBoxX + vrBoxWidth - VR_OBSTACLE_HITBOX_INSET &&
		vrRunnerY <= vrBoxY + vrBoxHeight - VR_RUNNER_HITBOX_INSET_Y) {
		vrGameOver = true;
		vrGameWon = false;
	}

	if (vrRunnerX + VR_RUNNER_W - VR_RUNNER_HITBOX_INSET_X >= vrRockX + VR_OBSTACLE_HITBOX_INSET &&
		vrRunnerX + VR_RUNNER_HITBOX_INSET_X <= vrRockX + 50 - VR_OBSTACLE_HITBOX_INSET &&
		vrRunnerY <= vrRockY + 38 - VR_RUNNER_HITBOX_INSET_Y) {
		vrGameOver = true;
		vrGameWon = false;
	}
}

void vrDraw() {
	if (!vrIsStarted) {
		iShowImage(0, 0, 800, 600, vrVault1Img);
		iShowImage(150, 20, 500, 200, vrNoteImg);
		iSetColor(20, 20, 20);
		iText(230, 65, "Click anywhere to disable the laser", GLUT_BITMAP_HELVETICA_18);
		iText(255, 50, "Click to Jump - Avoid the Boxes!", GLUT_BITMAP_HELVETICA_18);
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

	// CHANGED: runner is drawn slightly bigger now (same y position).
	iShowImage(vrRunnerX, vrRunnerY, VR_RUNNER_W, VR_RUNNER_H, vrRunnerImg[vrCurrentFrame]);

	// CHANGED: box.png is drawn bigger (vrBoxWidth/vrBoxHeight above), sized
	// to roughly match the stone obstacle. Same y position as before.
	iShowImage(vrBoxX, vrBoxY, vrBoxWidth, vrBoxHeight, dodgeBoxImg);

	iSetColor(95, 85, 75);
	double vrRockPolyX[] = { (double)vrRockX, (double)vrRockX + 10, (double)vrRockX + 25, (double)vrRockX + 45, (double)vrRockX + 52, (double)vrRockX };
	double vrRockPolyY[] = { (double)vrRockY, (double)vrRockY + 22, (double)vrRockY + 38, (double)vrRockY + 28, (double)vrRockY, (double)vrRockY };
	iFilledPolygon(vrRockPolyX, vrRockPolyY, 6);

	iSetColor(130, 120, 110);
	iFilledCircle(vrRockX + 22, vrRockY + 22, 5);

	// Score badge (score.png), same position/size/colour as Traffic Runner.
	iShowImage(560, 535, 220, 45, trScoreImg);

	iSetColor(255, 215, 0); // Golden Color
	char vrScoreStr[50];
	sprintf(vrScoreStr, "%d", vrCoinScore);
	iText(700, 549, vrScoreStr, GLUT_BITMAP_HELVETICA_18);

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
			return;
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

// ----------------------------------------------------------------------------
// LEVEL 3 FIGHT MINIGAME - function definitions
// ----------------------------------------------------------------------------

void lv3RestartGame() {
	lv3HeroX = LV3_HERO_START_X;
	lv3HeroY = LV3_HERO_START_Y;
	lv3HeroHealth = LV3_HERO_START_HEALTH;
	lv3IsAttacking = false;
	lv3AttackCooldown = 0;
	lv3HeroActionType = 1;
	lv3HeroWalkFrame = 0;
	lv3HeroWalkAnimTimer = 0;
	lv3HeroReachedGuard = false;
	lv3ClickCooldownTimer = 0;

	lv3Guard.x = LV3_GUARD_START_X;
	lv3Guard.health = LV3_GUARD_START_HEALTH;
	lv3Guard.isAlive = true;
	lv3GuardActionFrame = 0;
	lv3GuardAnimTimer = 0;
	lv3AttackTimer = 0;

	lv3SubState = 0;
}

void lv3UpdateGame() {
	if (lv3SubState == 0) {
		if (lv3IsAttacking) {
			lv3AttackCooldown--;
			if (lv3AttackCooldown <= 0) {
				lv3IsAttacking = false;
			}
		}

		if (lv3ClickCooldownTimer > 0) {
			lv3ClickCooldownTimer--;
		}

		lv3GuardAnimTimer++;
		if (lv3GuardAnimTimer >= 15) {
			lv3GuardActionFrame = (lv3GuardActionFrame + 1) % 3;
			lv3GuardAnimTimer = 0;
		}

		if (!lv3HeroReachedGuard) {
			if (lv3HeroX < LV3_HERO_STOP_X) {
				lv3HeroX += 3;
				lv3HeroWalkAnimTimer++;
				if (lv3HeroWalkAnimTimer >= 10) {
					lv3HeroWalkFrame = (lv3HeroWalkFrame + 1) % 3;
					lv3HeroWalkAnimTimer = 0;
				}
			}

			if (lv3Guard.isAlive && lv3Guard.x > LV3_GUARD_STOP_X) {
				lv3Guard.x -= 2;
			}

			if (lv3HeroX >= LV3_HERO_STOP_X && (!lv3Guard.isAlive || lv3Guard.x <= LV3_GUARD_STOP_X)) {
				lv3HeroX = LV3_HERO_STOP_X;
				lv3Guard.x = LV3_GUARD_STOP_X;
				lv3HeroReachedGuard = true;
				lv3HeroWalkFrame = 0;
			}
		}
		else {
			if (lv3Guard.isAlive) {
				lv3AttackTimer++;
				if (lv3AttackTimer >= 40) {
					lv3HeroHealth -= 5;
					lv3AttackTimer = 0;
					if (lv3HeroHealth < 0) lv3HeroHealth = 0;

					if (lv3HeroHealth <= 0) {
						lv3RestartGame();
					}
				}
			}
		}
	}
	else if (lv3SubState == 2) {
		if (lv3HeroX < LV3_DOOR_STOP_X) {
			lv3HeroX += 3;
			lv3HeroWalkAnimTimer++;
			if (lv3HeroWalkAnimTimer >= 10) {
				lv3HeroWalkFrame = (lv3HeroWalkFrame + 1) % 3;
				lv3HeroWalkAnimTimer = 0;
			}
		}
		else {
			lv3HeroX = LV3_DOOR_STOP_X;
			lv3HeroWalkFrame = 0;
			lv3SubState = 3;
		}
	}
}

int lv3GetHeroLifeImg(int health, int maxHealth) {
	if (health <= 0) return lv3HeroLifeImg[4];
	else if (health <= maxHealth / 4) return lv3HeroLifeImg[3];
	else if (health <= maxHealth / 2) return lv3HeroLifeImg[2];
	else if (health <= (maxHealth * 3) / 4) return lv3HeroLifeImg[1];
	else return lv3HeroLifeImg[0];
}

int lv3GetGuardLifeImg(int health, int maxHealth) {
	if (health <= maxHealth / 4) return lv3GuardLifeImg[3];
	else if (health <= maxHealth / 2) return lv3GuardLifeImg[2];
	else if (health <= (maxHealth * 3) / 4) return lv3GuardLifeImg[1];
	else return lv3GuardLifeImg[0];
}

void lv3Draw() {
	iShowImage(0, 0, 800, 600, lv3BgImageId);

	if (lv3SubState == 0) {
		if (lv3IsAttacking) {
			if (lv3HeroActionType == 1) {
				iShowImage(lv3HeroX, lv3HeroY, lv3HeroWidth, lv3HeroHeight, lv3HeroPunchId);
			}
			else {
				iShowImage(lv3HeroX, lv3HeroY, lv3HeroWidth, lv3HeroHeight, lv3HeroKickId);
			}
		}
		else {
			if (lv3HeroWalkFrame == 0) {
				iShowImage(lv3HeroX, lv3HeroY, lv3HeroWidth, lv3HeroHeight, lv3HeroStandId);
			}
			else if (lv3HeroWalkFrame == 1) {
				iShowImage(lv3HeroX, lv3HeroY, lv3HeroWidth, lv3HeroHeight, lv3HeroAnim2Id);
			}
			else {
				iShowImage(lv3HeroX, lv3HeroY, lv3HeroWidth, lv3HeroHeight, lv3HeroAnim3Id);
			}
		}

		iSetColor(255, 255, 255);
		iText(50, 560, "Hero Health:", GLUT_BITMAP_HELVETICA_18);
		{
			int heroLifeImg = lv3GetHeroLifeImg(lv3HeroHealth, LV3_HERO_START_HEALTH);
			if (heroLifeImg > 0) iShowImage(170, 545, 170, 60, heroLifeImg);//width,height
		}

		if (lv3Guard.isAlive) {
			if (lv3GuardActionFrame == 0) {
				iShowImage(lv3Guard.x, lv3Guard.y, lv3Guard.width, lv3Guard.height, lv3GuardStId);
			}
			else if (lv3GuardActionFrame == 1) {
				iShowImage(lv3Guard.x, lv3Guard.y, lv3Guard.width, lv3Guard.height, lv3GuardPunch1Id);
			}
			else {
				iShowImage(lv3Guard.x, lv3Guard.y, lv3Guard.width, lv3Guard.height, lv3GuardPunch2Id);
			}

			iSetColor(255, 255, 255);
			iText(500, 560, "Guard Health:", GLUT_BITMAP_HELVETICA_18);
			{
				int guardLifeImg = lv3GetGuardLifeImg(lv3Guard.health, LV3_GUARD_START_HEALTH);
				if (guardLifeImg > 0) iShowImage(630, 545, 170, 60, guardLifeImg);
			}
		}

		iShowImage(30, -15, 740, 300, lv3NoteImg);

		iSetColor(0, 0, 0);
		if (!lv3HeroReachedGuard) {
			iText(310, 55, "Moving towards the guard...", GLUT_BITMAP_HELVETICA_18);
		}
		else {
			iText(285, 55, "MOUSE CLICK = Punch/Kick", GLUT_BITMAP_HELVETICA_18);
		}
	}
	else if (lv3SubState == 1) {
		iShowImage(30, -15, 740, 300, lv3NoteImg);

		iSetColor(0, 150, 0);
		iText(290, 55, "GUARD DEFEATED!", GLUT_BITMAP_TIMES_ROMAN_24);

		iSetColor(0, 0, 0);
		iText(305, 30, "COLLECT THE GUN!", GLUT_BITMAP_HELVETICA_18);

		iShowImage(330, 200, 180, 100, lv3GunImageId);

		iSetColor(255, 0, 0); // Red arrow

		for (int offset = -2; offset <= 2; offset++) {
			iLine(410 + offset, 330, 410 + offset, 290);
		}

		for (int offset = -2; offset <= 2; offset++) {
			iLine(410 + offset, 290, 400 + offset, 305);
			iLine(410 + offset, 290, 420 + offset, 305);
		}
	}
	else if (lv3SubState == 2) {
		if (lv3HeroWalkFrame == 0) {
			iShowImage(lv3HeroX, lv3HeroY, lv3HeroWidth, lv3HeroHeight, lv3HeroStandId);
		}
		else if (lv3HeroWalkFrame == 1) {
			iShowImage(lv3HeroX, lv3HeroY, lv3HeroWidth, lv3HeroHeight, lv3HeroAnim2Id);
		}
		else {
			iShowImage(lv3HeroX, lv3HeroY, lv3HeroWidth, lv3HeroHeight, lv3HeroAnim3Id);
		}
	}
	else if (lv3SubState == 3) {
		iShowImage(lv3HeroX, lv3HeroY, lv3HeroWidth, lv3HeroHeight, lv3HeroStandId);

		iShowImage(30, -15, 740, 300, lv3NoteImg);
		iSetColor(0, 0, 0);
		iText(280, 55, "YOU REACHED THE DOOR!", GLUT_BITMAP_HELVETICA_18);
		iText(240, 30, "3 More Gangsters Are Waiting Outside...", GLUT_BITMAP_HELVETICA_18);

		if (nextImg > 0) iShowImage(650, 50, 100, 40, nextImg);
	}
}


void lv3HandleMouseDown(int mx, int my) {
	if (lv3SubState == 0 && lv3HeroReachedGuard) {
		if (lv3ClickCooldownTimer <= 0) {
			lv3IsAttacking = true;
			lv3AttackCooldown = 15;
			lv3ClickCooldownTimer = LV3_CLICK_COOLDOWN;

			if (lv3Guard.isAlive) {
				lv3Guard.health -= 5;

				if (lv3Guard.health <= 0) {
					lv3Guard.health = 0;
					lv3Guard.isAlive = false;
					lv3SubState = 1;
				}
			}

			if (lv3HeroActionType == 1) {
				lv3HeroActionType = 2;
			}
			else {
				lv3HeroActionType = 1;
			}
		}
	}
	else if (lv3SubState == 1) {
		if (mx >= 380 && mx <= 440 && my >= 250 && my <= 280) {
			lv3SubState = 2;
			lv3HeroWalkFrame = 0;
			lv3HeroWalkAnimTimer = 0;
		}
	}
	else if (lv3SubState == 3) {
		if (mx >= 650 && mx <= 750 && my >= 50 && my <= 90) {
			gsResetGame();
			gsState = -1;
			gameState = GAMESTATE_LEVEL3_SHOOTOUT;
		}
	}
}

// ----------------------------------------------------------------------------
// LEVEL 3 - GANGSTER SHOOTOUT MINIGAME - globals & function definitions
// ----------------------------------------------------------------------------
const int GS_SCREEN_W = 800;
const int GS_SCREEN_H = 600;

// CHANGED: the prisoner can now take 5 hits before dying (used to be 3). The
// on-screen damage counter uses this same constant, so it reads "/ 5".
const int GS_MAX_MISS = 5;

// Prisoner (Player)
int gsPrisonerX = 100;
int gsPrisonerY = 50;
int gsPrisonerWidth = 160;
int gsPrisonerHeight = 200;

// Jump
int gsPrisonerVelY = 0;
bool gsIsJumping = false;
int gsGroundY = 50;
int gsJumpStrength = 18;
int gsGravity = 1;

// Gangster (Enemy)
int gsGangsterX = 580;
int gsGangsterY = 50;
int gsGangsterWidth = 160;
int gsGangsterHeight = 200;

// Fixed positions for dead gangsters so they don't move with the active one
int gsDeadX1 = 0, gsDeadX2 = 0, gsDeadX3 = 0;

// Progression
int gsCurrentGangster = 1; // 1, 2, or 3
int gsGangsterHits = 0;    // Hits on current gangster (out of 20)
int gsGangsterShootCounter = 0;

// Images
int gsBgImg = 0, gsWpImg = 0, gsPrisonerImg = 0, gsGangsterImg = 0, gsPbImg = 0, gsGbImg = 0;
int gsDeadImg1 = 0, gsDeadImg2 = 0, gsDeadImg3 = 0;
int gsH1Img = 0, gsG1Img = 0, gsD1Img = 0;
#define GS_MAX_BULLETS 50

struct GsBullet {
	int x, y;
	bool active;
};

GsBullet gsPBullets[GS_MAX_BULLETS]; // Prisoner bullets (moving right)
GsBullet gsGBullets[GS_MAX_BULLETS]; // Gangster bullets (moving left)

// Stats
int gsScore = 0;
int gsMiss = 0;
// -1: Instruction Screen, 0: Playing, 1: Win, 2: Game Over

void gsResetGame() {
	gsScore = 0;
	gsMiss = 0;
	gsGangsterHits = 0;
	gsCurrentGangster = 1;
	gsPrisonerX = 100;
	gsGangsterX = 580;
	gsDeadX1 = 0;
	gsDeadX2 = 0;
	gsDeadX3 = 0;
	gsPrisonerY = gsGroundY;
	gsPrisonerVelY = 0;
	gsIsJumping = false;
	gsGangsterShootCounter = 0;
	for (int i = 0; i < GS_MAX_BULLETS; i++) {
		gsPBullets[i].active = false;
		gsGBullets[i].active = false;
	}
}

void gsUpdateGame() {
	if (gsState != 0) return;

	// Apply jump physics
	if (gsIsJumping) {
		gsPrisonerY += gsPrisonerVelY;
		gsPrisonerVelY -= gsGravity;

		if (gsPrisonerY <= gsGroundY) {
			gsPrisonerY = gsGroundY;
			gsPrisonerVelY = 0;
			gsIsJumping = false;
		}
	}

	// Gangster shooting every 3 seconds (150 frames at 20ms)
	gsGangsterShootCounter++;
	if (gsGangsterShootCounter >= 150) {
		gsGangsterShootCounter = 0;
		for (int i = 0; i < GS_MAX_BULLETS; i++) {
			if (!gsGBullets[i].active) {
				gsGBullets[i].x = gsGangsterX;
				gsGBullets[i].y = gsGangsterY + gsGangsterHeight / 2 - 12;
				gsGBullets[i].active = true;
				break;
			}
		}
	}

	// Update Prisoner Bullets & Collision with Gangster
	for (int i = 0; i < GS_MAX_BULLETS; i++) {
		if (gsPBullets[i].active) {
			gsPBullets[i].x += 15;

			if (gsPBullets[i].x > GS_SCREEN_W) {
				gsPBullets[i].active = false;
			}

			if (gsCurrentGangster <= 3 &&
				gsPBullets[i].x + 30 >= gsGangsterX && gsPBullets[i].x <= gsGangsterX + gsGangsterWidth &&
				gsPBullets[i].y + 15 >= gsGangsterY && gsPBullets[i].y <= gsGangsterY + gsGangsterHeight) {

				gsPBullets[i].active = false;
				gsGangsterHits++;
				gsScore++;

				if (gsGangsterHits >= 20) {
					if (gsCurrentGangster == 1) gsDeadX1 = gsGangsterX;
					else if (gsCurrentGangster == 2) gsDeadX2 = gsGangsterX;
					else if (gsCurrentGangster == 3) gsDeadX3 = gsGangsterX;

					gsCurrentGangster++;
					gsGangsterHits = 0;
					gsGangsterX = 580;

					if (gsCurrentGangster > 3) {
						gsState = 1; // Win
						level3Completed = true;
					}
				}
			}
		}
	}

	// Update Gangster Bullets & Collision with Prisoner
	for (int i = 0; i < GS_MAX_BULLETS; i++) {
		if (gsGBullets[i].active) {
			gsGBullets[i].x -= 12;

			if (gsGBullets[i].x < 0) {
				gsGBullets[i].active = false;
			}

			if (gsGBullets[i].x <= gsPrisonerX + gsPrisonerWidth && gsGBullets[i].x + 50 >= gsPrisonerX &&
				gsGBullets[i].y + 25 >= gsPrisonerY && gsGBullets[i].y <= gsPrisonerY + gsPrisonerHeight) {

				gsGBullets[i].active = false;
				gsMiss++;

				// CHANGED: 5 hits instead of 3.
				if (gsMiss >= GS_MAX_MISS) {
					gsState = 2; // Game Over
				}
			}
		}
	}
}

void gsDraw() {
	if (gsState == -1) {
		iShowImage(0, 0, GS_SCREEN_W, GS_SCREEN_H, gsBgImg);
		iShowImage(20, 50, 760, 140, gsWpImg);

		iSetColor(50, 20, 10);
		iText(220, 95, "Prisoner has to fight 3 gangsters sequentially!", GLUT_BITMAP_HELVETICA_18);
		iText(220, 75, "Left-Click to Shoot | Right-Click to Jump!", GLUT_BITMAP_HELVETICA_18);

		iSetColor(255, 255, 255);
		iText(255, 20, "Click NEXT to Start", GLUT_BITMAP_HELVETICA_18);

		iShowImage(50, 50, 100, 40, backImg);
		if (nextImg > 0) iShowImage(650, 50, 100, 40, nextImg);
		return;
	}

	if (gsState == 1) {
		iShowImage(0, 0, GS_SCREEN_W, GS_SCREEN_H, gsBgImg);
		iShowImage(20, 50, 760, 140, gsWpImg);

		iSetColor(0, 100, 0); // Dark Green
		iText(220, 95, "YOU WIN! All Gangsters Defeated!", GLUT_BITMAP_TIMES_ROMAN_24);

		iSetColor(255, 255, 255);
		iText(230, 75, "LEVEL 3 COMPLETE! Click to Continue", GLUT_BITMAP_HELVETICA_18);
		return;
	}

	if (gsState == 2) {
		iShowImage(0, 0, GS_SCREEN_W, GS_SCREEN_H, gsBgImg);
		iShowImage(20, 50, 760, 140, gsWpImg);

		iSetColor(150, 0, 0); // Dark Red
		iText(220, 95, "GAME OVER", GLUT_BITMAP_TIMES_ROMAN_24);

		iSetColor(255, 255, 255);
		iText(220, 75, "Click anywhere with Mouse to Restart", GLUT_BITMAP_HELVETICA_18);

		iShowImage(50, 50, 100, 40, backImg);
		return;
	}

	// Gameplay Screen
	iShowImage(0, 0, GS_SCREEN_W, GS_SCREEN_H, gsBgImg);

	if (gsCurrentGangster > 1) {
		iShowImage(gsDeadX1, gsGangsterY, gsGangsterWidth, gsGangsterHeight, gsDeadImg1);
	}
	if (gsCurrentGangster > 2) {
		iShowImage(gsDeadX2, gsGangsterY, gsGangsterWidth, gsGangsterHeight, gsDeadImg2);
	}
	if (gsState == 1) {
		iShowImage(gsDeadX3, gsGangsterY, gsGangsterWidth, gsGangsterHeight, gsDeadImg3);
	}

	if (gsCurrentGangster <= 3 && gsState == 0) {
		iShowImage(gsGangsterX, gsGangsterY, gsGangsterWidth, gsGangsterHeight, gsGangsterImg);
	}

	iShowImage(gsPrisonerX, gsPrisonerY, gsPrisonerWidth, gsPrisonerHeight, gsPrisonerImg);

	for (int i = 0; i < GS_MAX_BULLETS; i++) {
		if (gsPBullets[i].active) {
			iShowImage(gsPBullets[i].x, gsPBullets[i].y, 30, 15, gsPbImg);
		}
	}

	for (int i = 0; i < GS_MAX_BULLETS; i++) {
		if (gsGBullets[i].active) {
			iShowImage(gsGBullets[i].x, gsGBullets[i].y, 50, 25, gsGbImg);
		}
	}

	// Display Stats
	// Render HUD Banner Images (All equal 230x40 size)
	// Render HUD Banners stacked vertically on the top right
	iShowImage(550, 545, 230, 40, gsH1Img);
	iShowImage(550, 495, 230, 40, gsG1Img);
	iShowImage(550, 445, 230, 40, gsD1Img);

	// Display Stats centered inside the dark box on the right side of each banner
	char gsScoreStr[20], gsMissStr[20], gsBossStr[20];
	sprintf(gsScoreStr, "%d / 20", gsGangsterHits);
	sprintf(gsBossStr, "%d / 3", gsCurrentGangster);
	sprintf(gsMissStr, "%d / %d", gsMiss, GS_MAX_MISS);

	iSetColor(255, 255, 255);
	iText(685, 558, gsScoreStr, GLUT_BITMAP_HELVETICA_12);
	iText(685, 508, gsBossStr, GLUT_BITMAP_HELVETICA_12);
	iText(685, 458, gsMissStr, GLUT_BITMAP_HELVETICA_12);
}

void gsMouseMove(int mx, int my) {
	if (gsState != 0) return;

	int oldPrisonerX = gsPrisonerX;

	gsPrisonerX = mx - gsPrisonerWidth / 2;
	if (gsPrisonerX < 0) gsPrisonerX = 0;
	if (gsPrisonerX > GS_SCREEN_W / 2 - gsPrisonerWidth) gsPrisonerX = GS_SCREEN_W / 2 - gsPrisonerWidth;

	int deltaX = gsPrisonerX - oldPrisonerX;
	gsGangsterX += deltaX;

	if (gsGangsterX < GS_SCREEN_W / 2 + 50) gsGangsterX = GS_SCREEN_W / 2 + 50;
	if (gsGangsterX > GS_SCREEN_W - gsGangsterWidth - 20) gsGangsterX = GS_SCREEN_W - gsGangsterWidth - 20;
}

void gsHandleLeftClick(int mx, int my) {
	if (gsState == -1) {
		if (mx >= 650 && mx <= 750 && my >= 50 && my <= 90) {
			gsResetGame();
			gsState = 0;
		}
		return;
	}

	if (gsState == 2) {
		gsResetGame();
		gsState = 0;
		return;
	}

	if (gsState == 1) {
		gsResetGame();
		gsState = -1;
		trResetGame();
		trGameStarted = false;
		gameState = GAMESTATE_TRAFFIC;
		return;
	}

	if (gsState == 0) {
		for (int i = 0; i < GS_MAX_BULLETS; i++) {
			if (!gsPBullets[i].active) {
				gsPBullets[i].x = gsPrisonerX + gsPrisonerWidth;
				gsPBullets[i].y = gsPrisonerY + gsPrisonerHeight / 2 - 7;
				gsPBullets[i].active = true;
				break;
			}
		}
	}
}

void gsHandleRightClick(int mx, int my) {
	if (gsState != 0) return;
	if (!gsIsJumping) {
		gsIsJumping = true;
		gsPrisonerVelY = gsJumpStrength;
	}
}

// ----------------------------------------------------------------------------
// TRAFFIC RUNNER MINIGAME - function definitions
// ----------------------------------------------------------------------------

void trDrawCar(int x, int y, int colorIndex) {
	if (colorIndex >= 0 && colorIndex < 6) {
		iShowImage(x, y, TR_CAR_W, TR_CAR_H, trCarImgs[colorIndex]);
	}
}

void trDrawTruck(int x, int y, int colorIndex) {
	if (colorIndex >= 0 && colorIndex < 4) {
		iShowImage(x, y, TR_TRUCK_W, TR_TRUCK_H, trTruckImgs[colorIndex]);
	}
}

void trDrawManhole(int x, int y) {
	int cx = x + TR_MANHOLE_W / 2;
	int cy = y + TR_MANHOLE_H / 2;
	int r = TR_MANHOLE_W / 2;

	iSetColor(15, 15, 15);
	iFilledCircle(cx, cy, r + 2);

	iSetColor(50, 50, 50);
	iFilledCircle(cx, cy, r);

	iSetColor(110, 110, 110);
	iCircle(cx, cy, r - 2);
	iCircle(cx, cy, r - 5);

	iSetColor(35, 35, 35);
	iFilledCircle(cx, cy, r - 8);

	iSetColor(75, 75, 75);
	iLine(cx - (r - 10), cy, cx + (r - 10), cy);
	iLine(cx, cy - (r - 10), cx, cy + (r - 10));

	iLine(cx - (r - 12), cy - (r - 12), cx + (r - 12), cy + (r - 12));
	iLine(cx - (r - 12), cy + (r - 12), cx + (r - 12), cy - (r - 12));

	iSetColor(85, 85, 85);
	iFilledCircle(cx, cy, 8);
	iSetColor(25, 25, 25);
	iFilledCircle(cx, cy, 4);
}

void trDrawGreenGem(int x, int y) {
	int size = 25;
	int cx = x + size / 2;
	int topY = y + size;
	int midY = y + size / 2;
	int botY = y;
	int leftX = x;
	int rightX = x + size;

	iSetColor(20, 130, 55);
	double x1[] = { (double)cx, (double)leftX, (double)cx };
	double y1[] = { (double)topY, (double)midY, (double)botY };
	iFilledPolygon(x1, y1, 3);

	iSetColor(70, 210, 100);
	double x2[] = { (double)cx, (double)rightX, (double)cx };
	double y2[] = { (double)topY, (double)midY, (double)botY };
	iFilledPolygon(x2, y2, 3);

	iSetColor(200, 255, 215);
	double x3[] = { (double)cx, (double)cx - 5, (double)cx + 5 };
	double y3[] = { (double)topY, (double)midY - 3, (double)midY - 3 };
	iFilledPolygon(x3, y3, 3);

	iSetColor(10, 80, 35);
	iLine(cx, topY, leftX, midY);
	iLine(leftX, midY, cx, botY);
	iLine(cx, botY, rightX, midY);
	iLine(rightX, midY, cx, topY);
}

void trDraw() {
	if (!trGameStarted) {
		iShowImage(0, 0, TR_SCREEN_W, TR_SCREEN_H, trStartImg);

		int noteW = 500, noteH = 250;
		int noteX = (TR_SCREEN_W - noteW) / 2;
		int noteY = 20;
		iShowImage(noteX, noteY, noteW, noteH, trNoteImg);

		iSetColor(0, 0, 0);
		iText(noteX + 35, noteY + 63, "Press Right/Left Arrow to move,Space/Up to jump", GLUT_BITMAP_HELVETICA_18);
		iText(noteX + 100, noteY + 40, "Click anywhere to start the game", GLUT_BITMAP_HELVETICA_18);

		return;
	}

	if (trWinState == 1) {
		iShowImage(0, 0, TR_SCREEN_W, TR_SCREEN_H, trWinImg1);

		int noteW = 500, noteH = 250;
		int noteX = (TR_SCREEN_W - noteW) / 2;
		int noteY = 20;
		iShowImage(noteX, noteY, noteW, noteH, trNoteImg);

		iSetColor(0, 0, 0);
		iText(noteX + 190, noteY + 63, "YOU WIN!", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(noteX + 110, noteY + 40, "Click anywhere to continue...", GLUT_BITMAP_HELVETICA_18);

		return;
	}
	else if (trWinState == 2) {
		iShowImage(0, 0, TR_SCREEN_W, TR_SCREEN_H, trWinImg2);
		return;
	}
	else if (trWinState == 3) {
		iShowImage(0, 0, TR_SCREEN_W, TR_SCREEN_H, trWinImg3);
		return;
	}
	else if (trWinState == 4) {
		iShowImage(0, 0, TR_SCREEN_W, TR_SCREEN_H, trFinalBgImg);
		return;
	}

	iShowImage(0, trBgY1, TR_SCREEN_W, TR_SCREEN_H, trBgImg);
	iShowImage(0, trBgY2, TR_SCREEN_W, TR_SCREEN_H, trBgImg);

	for (int i = 0; i < TR_MAX_MANHOLES; i++) {
		if (trManholeList[i].active) {
			trDrawManhole(trLaneX[trManholeList[i].lane] + 2, trManholeList[i].y);
		}
	}

	for (int i = 0; i < TR_MAX_OBS; i++) {
		if (trObsList[i].active) {
			int l = trObsList[i].lane;
			if (trObsList[i].type == 0) {
				trDrawCar(trLaneX[l], trObsList[i].y, trObsList[i].colorIndex);
			}
			else {
				trDrawTruck(trLaneX[l] - 5, trObsList[i].y, trObsList[i].colorIndex);
			}
		}
	}

	for (int i = 0; i < TR_MAX_ROOF_GEMS; i++) {
		if (trRoofGems[i].active) {
			trDrawGreenGem(trLaneX[trRoofGems[i].lane] + 20, trRoofGems[i].y);
		}
	}

	int drawX = (int)trPlayerDrawX;
	int drawY = trPlayerY + trJumpHeight;

	if (trCurrentRunFrame == 0)
		iShowImage(drawX, drawY, 60, 90, trRunImg1);
	else
		iShowImage(drawX, drawY, 60, 90, trRunImg2);

	// Draw Score Image and Golden Score Number
	iShowImage(560, 535, 220, 45, trScoreImg);

	iSetColor(255, 215, 0); // Golden Color
	char scoreStr[50];
	sprintf(scoreStr, "%d", trScore);
	iText(700, 549, scoreStr, GLUT_BITMAP_HELVETICA_18);

	if (trGameOver) {
		iSetColor(255, 0, 0);
		iText(260, 300, "GAME OVER! Press 'R' to Restart.", GLUT_BITMAP_HELVETICA_18);
	}
}

void trSpawnTrafficCluster(int startY) {
	int jamLane = rand() % 3;
	int currentY = startY;

	bool isFullJam = (rand() % 2 == 0);
	int count = isFullJam ? (4 + rand() % 3) : (2 + rand() % 2);

	int modeChoice = rand() % 100;
	bool gemOnJam = false;
	bool gemOnManhole = false;
	bool gemOnSideCars = false;

	if (modeChoice < 20) {
		gemOnJam = true; gemOnManhole = true;
	}
	else if (modeChoice < 40) {
		gemOnManhole = true; gemOnSideCars = true;
	}
	else if (modeChoice < 60) {
		gemOnJam = true; gemOnSideCars = true;
	}
	else if (modeChoice < 75) {
		gemOnJam = true;
	}
	else if (modeChoice < 90) {
		gemOnManhole = true;
	}
	else {
		gemOnSideCars = true;
	}

	for (int c = 0; c < count; c++) {
		int slot = -1;
		for (int j = 0; j < TR_MAX_OBS; j++) {
			if (!trObsList[j].active) {
				slot = j;
				break;
			}
		}

		if (slot != -1) {
			trObsList[slot].lane = jamLane;
			trObsList[slot].y = currentY;
			trObsList[slot].type = rand() % 2;

			int h = (trObsList[slot].type == 1) ? TR_TRUCK_H : TR_CAR_H;
			trObsList[slot].colorIndex = (trObsList[slot].type == 0) ? rand() % 6 : rand() % 4;
			trObsList[slot].active = true;

			if (gemOnJam && (isFullJam ? (c >= 1 && c < count - 1) : true)) {
				for (int gy = currentY + 20; gy <= currentY + h - 20; gy += 40) {
					for (int k = 0; k < TR_MAX_ROOF_GEMS; k++) {
						if (!trRoofGems[k].active) {
							trRoofGems[k].lane = jamLane;
							trRoofGems[k].y = gy;
							trRoofGems[k].active = true;
							break;
						}
					}
				}
			}

			int jamGap = isFullJam ? 5 : 80;
			currentY += h + jamGap;
		}
	}

	int otherLanes[2];
	int idx = 0;
	for (int i = 0; i < 3; i++) {
		if (i != jamLane) {
			otherLanes[idx++] = i;
		}
	}

	int manholeLane = otherLanes[0];
	int sideCarLane = otherLanes[1];

	if (rand() % 2 == 1) {
		manholeLane = otherLanes[1];
		sideCarLane = otherLanes[0];
	}

	int mY = startY + (rand() % (abs(currentY - startY - 100) + 1));

	for (int m = 0; m < TR_MAX_MANHOLES; m++) {
		if (!trManholeList[m].active) {
			trManholeList[m].lane = manholeLane;
			trManholeList[m].y = mY;
			trManholeList[m].active = true;
			break;
		}
	}

	if (gemOnManhole) {
		int gemCount = 0;
		for (int gy = mY - 30; gy <= mY + 110; gy += 35) {
			if (gemCount >= 5) break;
			for (int k = 0; k < TR_MAX_ROOF_GEMS; k++) {
				if (!trRoofGems[k].active) {
					trRoofGems[k].lane = manholeLane;
					trRoofGems[k].y = gy;
					trRoofGems[k].active = true;
					gemCount++;
					break;
				}
			}
		}
	}

	int vehicleCount = (rand() % 2 == 0) ? 1 : 2;
	int sideY = startY + (rand() % (abs(currentY - startY - 260) + 1));

	for (int v = 0; v < vehicleCount; v++) {
		int slot = -1;
		for (int j = 0; j < TR_MAX_OBS; j++) {
			if (!trObsList[j].active) {
				slot = j;
				break;
			}
		}

		if (slot != -1) {
			trObsList[slot].lane = sideCarLane;
			trObsList[slot].y = sideY;
			trObsList[slot].type = rand() % 2;

			int sH = (trObsList[slot].type == 1) ? TR_TRUCK_H : TR_CAR_H;
			trObsList[slot].colorIndex = (trObsList[slot].type == 0) ? rand() % 6 : rand() % 4;
			trObsList[slot].active = true;

			if (gemOnSideCars) {
				int gCount = 0;
				for (int gy = sideY + 20; gy <= sideY + sH - 20; gy += 35) {
					if (gCount >= 3) break;
					for (int k = 0; k < TR_MAX_ROOF_GEMS; k++) {
						if (!trRoofGems[k].active) {
							trRoofGems[k].lane = sideCarLane;
							trRoofGems[k].y = gy;
							trRoofGems[k].active = true;
							gCount++;
							break;
						}
					}
				}
			}

			int gap = 80;
			sideY += sH + gap;
		}
	}
}

void trUpdateObstacles() {
	bool anyActive = false;
	int maxObsY = -999;

	int pX = (int)trPlayerDrawX;
	int pW = 60;

	bool currentlyOnVehicleRoof = false;

	for (int i = 0; i < TR_MAX_OBS; i++) {
		if (trObsList[i].active) {
			anyActive = true;
			trObsList[i].y -= 7;

			if (trObsList[i].y > maxObsY) {
				maxObsY = trObsList[i].y;
			}

			if (trObsList[i].y < -400) {
				trObsList[i].active = false;
			}

			int l = trObsList[i].lane;
			int obsW = (trObsList[i].type == 1) ? TR_TRUCK_W : TR_CAR_W;
			int obsH = (trObsList[i].type == 1) ? TR_TRUCK_H : TR_CAR_H;
			int obsX = trLaneX[l];
			if (trObsList[i].type == 1) obsX -= 5;

			int obsBottom = trObsList[i].y;
			int obsTop = trObsList[i].y + obsH;

			bool xOverlap = (pX + pW - 15 > obsX) && (pX + 15 < obsX + obsW);

			if (xOverlap && l == trPlayerLane) {
				int curPlayerY = trPlayerY + trJumpHeight;

				if (curPlayerY >= obsBottom - 10 && curPlayerY <= obsTop + 30) {
					currentlyOnVehicleRoof = true;
				}

				if (trIsJumping && curPlayerY >= obsBottom) {
					trIsOnRoof = true;
				}

				if (!trIsJumping && !trIsOnRoof) {
					if (trPlayerY + 15 >= obsBottom && trPlayerY + 15 <= obsBottom + 35) {
						trGameOver = true;
					}
				}
			}
		}
	}

	if (!currentlyOnVehicleRoof && !trIsJumping) {
		trIsOnRoof = false;
	}

	if (!anyActive || maxObsY < TR_SCREEN_H - 150) {
		trSpawnTrafficCluster(TR_SCREEN_H + 100);
	}
}

void trUpdateRoofGems() {
	int currentPPosY = trPlayerY + trJumpHeight;

	for (int i = 0; i < TR_MAX_ROOF_GEMS; i++) {
		if (trRoofGems[i].active) {
			trRoofGems[i].y -= 7;

			if (trRoofGems[i].lane == trPlayerLane) {
				if (abs(trRoofGems[i].y - currentPPosY) < 45) {
					trScore += 10;
					trRoofGems[i].active = false;
				}
			}

			if (trRoofGems[i].y < -100) {
				trRoofGems[i].active = false;
			}
		}
	}
}

void trUpdateManholes() {
	int pX = (int)trPlayerDrawX;
	int pW = 60;

	for (int i = 0; i < TR_MAX_MANHOLES; i++) {
		if (trManholeList[i].active) {
			trManholeList[i].y -= 7;

			if (trManholeList[i].lane == trPlayerLane) {
				int mX = trLaneX[trManholeList[i].lane] + 2;
				bool xOverlap = (pX + pW - 15 > mX) && (pX + 15 < mX + TR_MANHOLE_W);

				if (xOverlap && !trIsJumping && !trIsOnRoof) {
					if (trPlayerY + 20 >= trManholeList[i].y && trPlayerY <= trManholeList[i].y + TR_MANHOLE_H) {
						trGameOver = true;
					}
				}
			}

			if (trManholeList[i].y < -100) {
				trManholeList[i].active = false;
			}
		}
	}
}

void trResetGame() {
	trGameOver = false;
	trWinState = 0;
	trWinTimer = 0;
	trScore = 0;
	trJumpHeight = 0;
	trIsJumping = false;
	trJumpUp = true;
	trIsOnRoof = false;
	trPlayerLane = 1;
	trPlayerY = trBasePlayerY;
	trPlayerDrawX = trLaneX[trPlayerLane] + 5;
	trBgY1 = 0;
	trBgY2 = 600;

	for (int i = 0; i < TR_MAX_OBS; i++) {
		trObsList[i].active = false;
	}

	for (int k = 0; k < TR_MAX_ROOF_GEMS; k++) {
		trRoofGems[k].active = false;
	}

	for (int m = 0; m < TR_MAX_MANHOLES; m++) {
		trManholeList[m].active = false;
	}

	trSpawnTrafficCluster(500);
}

void trFixedUpdate() {
	if (gameState != GAMESTATE_TRAFFIC) return;
	if (isGamePaused) return;

	if (isKeyPressed('r') || isKeyPressed('R')) {
		trResetGame();
	}

	if (!trGameStarted) return;

	if (trGameOver) return;

	if (trWinState == 1) return;

	if (trWinState == 2) {
		trWinTimer += 50;
		if (trWinTimer >= 4000) {
			trWinState = 3;
			trWinTimer = 0;
		}
		return;
	}
	else if (trWinState == 3) {
		trWinTimer += 50;
		if (trWinTimer >= 7000) {
			trWinState = 4;
			trWinTimer = 0;

			gameState = GAMESTATE_TRAFFIC_LOADING;
			loadingStep = 0;
			if (musicPlaying) {
				mciSendString(TEXT("pause bgm"), NULL, 0, NULL);
			}
		}
		return;
	}
	else if (trWinState == 4) {
		return;
	}

	if (trScore >= 1500) {
		trWinState = 1;
		return;
	}

	if (isSpecialKeyPressed(GLUT_KEY_LEFT)) {
		trPlayerDrawX -= 10.0;
		if (trPlayerDrawX < trLaneX[0] + 5) {
			trPlayerDrawX = trLaneX[0] + 5;
		}
	}

	if (isSpecialKeyPressed(GLUT_KEY_RIGHT)) {
		trPlayerDrawX += 10.0;
		if (trPlayerDrawX > trLaneX[2] + 5) {
			trPlayerDrawX = trLaneX[2] + 5;
		}
	}

	if (trPlayerDrawX < (trLaneX[0] + trLaneX[1]) / 2.0 + 5) {
		trPlayerLane = 0;
	}
	else if (trPlayerDrawX >(trLaneX[1] + trLaneX[2]) / 2.0 + 5) {
		trPlayerLane = 2;
	}
	else {
		trPlayerLane = 1;
	}

	if (isSpecialKeyPressed(GLUT_KEY_UP)) {
		if (!trIsJumping) {
			trIsJumping = true;
			trJumpUp = true;
		}
	}

	if (isKeyPressed(' ')) {
		if (!trIsJumping) {
			trIsJumping = true;
			trJumpUp = true;
		}
	}

	trBgY1 -= 6;
	trBgY2 -= 6;

	if (trBgY1 <= -TR_SCREEN_H)
		trBgY1 = trBgY2 + TR_SCREEN_H;

	if (trBgY2 <= -TR_SCREEN_H)
		trBgY2 = trBgY1 + TR_SCREEN_H;

	trUpdateObstacles();
	trUpdateRoofGems();
	trUpdateManholes();

	if (trIsJumping) {
		if (trJumpUp) {
			trJumpHeight += 12;
			if (trJumpHeight >= 150)
				trJumpUp = false;
		}
		else {
			trJumpHeight -= 12;
			if (trJumpHeight <= 0) {
				trJumpHeight = 0;
				trIsJumping = false;
			}
		}
	}

	static int trAnimCounter = 0;
	trAnimCounter++;
	if (trAnimCounter >= 10) {
		trCurrentRunFrame = 1 - trCurrentRunFrame;
		trAnimCounter = 0;
	}
}

void trHandleMouseDown(int mx, int my) {
	if (!trGameStarted) {
		trGameStarted = true;
		return;
	}

	if (trWinState == 1) {
		trWinState = 2;
		trWinTimer = 0;
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
		// NEW: level 1 instruction screen - the normal level 1 map with
		// intro.png in the middle (same size/place as the level 2 note) and
		// a Next button on the right. Clicking Next goes to gameState 350
		// where the map behaves exactly as it always did.
		if (map1Img > 0) iShowImage(0, 0, 800, 600, map1Img);
		if (cellMapImg > 0) iShowImage(150, 80, 480, 150, cellMapImg);
		if (cctvMapImg > 0) iShowImage(62, 335, 200, 228, cctvMapImg);
		if (alarmMapImg > 0) iShowImage(530, 333, 200, 228, alarmMapImg);

		if (introImg > 0) iShowImage(150, 150, 500, 200, introImg);
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
			// CHANGED: same x/y as before (totalWidth kept at 50 + 60 so the
			// two sprites keep their original positions), only the drawn
			// width/height of the guard and the caught player were
			// increased.
			int totalWidth = 50 + 60;
			int startX = (800 - totalWidth) / 2;

			iShowImage(startX, guardY, L1_CAUGHT_GUARD_W, L1_CAUGHT_GUARD_H, guard6);
			iShowImage(startX + 50, playerY, L1_CAUGHT_PLAYER_W, L1_CAUGHT_PLAYER_H, caughtPlayer);

			if (imgnote > 0) {
				iShowImage(150, 20, 500, 200, imgnote);
			}

			iSetColor(0, 0, 0);
			iText(265, 65, "YOU WERE SPOTTED", GLUT_BITMAP_HELVETICA_18);
			iText(230, 50, "CLICK ANYWHERE TO START OVER", GLUT_BITMAP_HELVETICA_18);
		}
		else
		{
			// CHANGED: guard sprites are drawn bigger (same guardX/guardY).
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

			// CHANGED: player sprites are drawn bigger (same playerX/playerY).
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
		if (usbNoteImg > 0) iShowImage(50, 200, 700, 140, usbNoteImg);
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

		// ------------------------------------------------------------------
		// Intro/"note" screens. Each just waits for a click on the Next
		// button (same 650,50 - 750,90 hotspot used elsewhere in the game)
		// and then starts the level/minigame exactly the way it used to.
		// ------------------------------------------------------------------
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
		// CHANGED: the first of the three lines ("PRISON ESCAPE: SECURITY
		// OVERRIDE") has been removed. The remaining two lines now sit on a
		// note.png box placed at exactly the same spot/size the Traffic
		// Runner uses for its own note, with the same text offsets.
		int noteW = 500, noteH = 250;
		int noteX = (800 - noteW) / 2;
		int noteY = 20;

		if (imgnote > 0) iShowImage(noteX, noteY, noteW, noteH, imgnote);

		iSetColor(0, 0, 0);
		iText(noteX + 55, noteY + 63, "Play this match-3 game to get the USB!", GLUT_BITMAP_HELVETICA_18);
		iText(noteX + 45, noteY + 40, "Click anywhere or press ENTER to Start", GLUT_BITMAP_HELVETICA_18);
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
		// CHANGED: the win text is now drawn on a note.png box using exactly
		// the Traffic Runner win-screen layout, and the running character
		// animation that used to be drawn underneath has been removed.
		if (usbImgUsbIcon > 0) iShowImage(520, 220, 40, 40, usbImgUsbIcon);

		int noteW = 500, noteH = 250;
		int noteX = (800 - noteW) / 2;
		int noteY = 20;

		if (imgnote > 0) iShowImage(noteX, noteY, noteW, noteH, imgnote);

		iSetColor(0, 0, 0);
		iText(noteX + 125, noteY + 63, "SECURITY BYPASSED!", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(noteX + 105, noteY + 40, "Character acquired the USB!", GLUT_BITMAP_HELVETICA_18);

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

	dodgeBgImg = iLoadImage("Images/fallingboxbg.png");
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

	// Note/instruction screen images
	dodgeIntroNoteImg = iLoadImage("Images/dodgenote.png");
	level2NoteImg = iLoadImage("Images/level2note.png");
	usbNoteImg = iLoadImage("Images/usbnote.png");
	evidenceRoomNoteImg = iLoadImage("Images/evidenceroomnote.png");
	gunCollectImg = iLoadImage("Images/guncollect.png");

	// NEW: level 1 map instruction image (shown on top of map1.png)
	introImg = iLoadImage("Images/intro.png");

	// Level 3 fight minigame images
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

	// Level 3 - Gangster Shootout minigame images
	gsBgImg = iLoadImage("Images/collison room.png");
	gsWpImg = iLoadImage("Images/wp.png");
	gsPrisonerImg = iLoadImage("Images/prisoner.png");
	gsGangsterImg = iLoadImage("Images/gangster.png");
	gsPbImg = iLoadImage("Images/pb.png");
	gsGbImg = iLoadImage("Images/gb.png");
	gsDeadImg1 = iLoadImage("Images/dead1.png");
	gsDeadImg2 = iLoadImage("Images/dead2.png");
	gsDeadImg3 = iLoadImage("Images/dead3.png");

	// HUD Banner Images
	gsH1Img = iLoadImage("Images/H1.png");
	gsG1Img = iLoadImage("Images/G1.png");
	gsD1Img = iLoadImage("Images/D1.png");

	for (int i = 0; i < GS_MAX_BULLETS; i++) {
		gsPBullets[i].active = false;
		gsGBullets[i].active = false;
	}

	// Traffic Runner minigame images
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

	iSetTimer(50, trFixedUpdate);

	iStart();
	return 0;
}