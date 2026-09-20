#pragma once

// ============================================================================
// Level2Variables.h
// Level 2: USB match-3 minigame, Evidence Room (investigation) puzzle,
// Vault Runner minigame
// ============================================================================

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
int imgS1, imgM1;
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

void vrResetGame();
void vrFixedUpdate();
void vrDraw();
void vrHandleMouseDown(int mx, int my);

// ----------------------------------------------------------------------------
// NEW: instruction/"note" screens inserted ahead of a few minigames (Level 2).
// ----------------------------------------------------------------------------
const int GAMESTATE_LEVEL2_NOTE = 510;      // shown once, right after the level 2 loading screen, before GAMESTATE_LEVEL2_MAP
const int GAMESTATE_USB_NOTE = 520;         // shown before the USB match-3 minigame (gameState 400)
const int GAMESTATE_INVEST_NOTE = 530;      // shown before GAMESTATE_INVESTIGATION

int level2NoteImg = 0;         // Images/level2note.png
int usbNoteImg = 0;            // Images/usbnote.png
int evidenceRoomNoteImg = 0;   // Images/evidenceroomnote.png
