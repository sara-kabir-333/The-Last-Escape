#pragma once

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

const int GAMESTATE_VAULT_RUNNER = 470;

bool vrIsStarted = false;
bool vrShowVault3 = false;
int vrVault1Img = 0;
int vrVault2Img = 0;
int vrVault3Img = 0;
int vrNoteImg = 0;

const int VR_RUNNER_W = 115;  
const int VR_RUNNER_H = 125;  

int vrRunnerX = 50;
int vrRunnerY = 200;
int vrRunnerDy = 0;
bool vrIsJumping = false;
int vrJumpCount = 0;
bool vrIsMouseHeld = false;
int vrFallCounter = 0;

int vrBoxX = 800;
int vrBoxY = 200;
int vrBoxWidth = 65;    
int vrBoxHeight = 58;   
int vrGameSpeed = 4;

const int VR_RUNNER_HITBOX_INSET_X = 32; 
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

bool vrVault3TimerStarted = false;
double vrVault3TimerStart = 0;

const int GAMESTATE_VR_WIN_LOADING = 480;

bool level2Completed = false;

int vrWinBgImg = 0; 

void vrResetGame();
void vrFixedUpdate();
void vrDraw();
void vrHandleMouseDown(int mx, int my);

const int GAMESTATE_LEVEL2_NOTE = 510;      
const int GAMESTATE_USB_NOTE = 520;         
const int GAMESTATE_INVEST_NOTE = 530;      

int level2NoteImg = 0;         
int usbNoteImg = 0;           
int evidenceRoomNoteImg = 0;   