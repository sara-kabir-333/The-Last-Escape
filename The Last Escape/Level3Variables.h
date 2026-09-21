#pragma once

int level3UnlockedBtn = 0; 
int level3BgImg = 0;       
const int GAMESTATE_LEVEL3_LOADING = 490;

const int GAMESTATE_GUNCOLLECT_NOTE = 540;  

int gunCollectImg = 0;         

const int GAMESTATE_LEVEL3_FIGHT = 550;

int lv3SubState = 0;

const int LV3_HERO_START_X = 100;
const int LV3_HERO_START_Y = 100;
const int LV3_HERO_START_HEALTH = 60;

int lv3HeroX = LV3_HERO_START_X;
int lv3HeroY = LV3_HERO_START_Y;
int lv3HeroWidth = 200;
int lv3HeroHeight = 150;
int lv3HeroHealth = LV3_HERO_START_HEALTH;

bool lv3IsAttacking = false;
int lv3AttackCooldown = 0;
int lv3HeroActionType = 1; 

int lv3HeroWalkFrame = 0;
int lv3HeroWalkAnimTimer = 0;

bool lv3HeroReachedGuard = false;

int lv3ClickCooldownTimer = 0;
const int LV3_CLICK_COOLDOWN = 20; 

const int LV3_CENTER_X = 400;
const int LV3_FIGHT_OVERLAP = 125;
const int LV3_HERO_STOP_X = 263;
const int LV3_GUARD_STOP_X = 338;

struct Lv3Guard {
	int x, y;
	int width, height;
	int health;
	bool isAlive;
};

const int LV3_GUARD_START_X = 600;
const int LV3_GUARD_START_HEALTH = 55;

Lv3Guard lv3Guard = { LV3_GUARD_START_X, 100, 200, 150, LV3_GUARD_START_HEALTH, true };
int lv3GuardActionFrame = 0;
int lv3GuardAnimTimer = 0;
int lv3AttackTimer = 0;

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

int lv3HeroLifeImg[5] = { 0, 0, 0, 0, 0 };  
int lv3GuardLifeImg[4] = { 0, 0, 0, 0 };    

void lv3RestartGame();
void lv3UpdateGame();
void lv3Draw();
void lv3HandleMouseDown(int mx, int my);
int lv3GetHeroLifeImg(int health, int maxHealth);
int lv3GetGuardLifeImg(int health, int maxHealth);

const int GAMESTATE_LEVEL3_SHOOTOUT = 560;

bool level3Completed = false;

int gsState = -1;

void gsResetGame();
void gsUpdateGame();
void gsDraw();
void gsMouseMove(int mx, int my);
void gsHandleLeftClick(int mx, int my);
void gsHandleRightClick(int mx, int my);

const int GS_SCREEN_W = 800;
const int GS_SCREEN_H = 600;

const int GS_MAX_MISS = 5;

int gsPrisonerX = 100;
int gsPrisonerY = 50;
int gsPrisonerWidth = 160;
int gsPrisonerHeight = 200;

int gsPrisonerVelY = 0;
bool gsIsJumping = false;
int gsGroundY = 50;
int gsJumpStrength = 24;
int gsGravity = 1;

int gsGangsterX = 580;
int gsGangsterY = 50;
int gsGangsterWidth = 160;
int gsGangsterHeight = 200;

int gsDeadX1 = 0, gsDeadX2 = 0, gsDeadX3 = 0;

int gsCurrentGangster = 1; 
int gsGangsterHits = 0;   
int gsGangsterShootCounter = 0;

int gsBgImg = 0, gsWpImg = 0, gsPrisonerImg = 0, gsGangsterImg = 0, gsPbImg = 0, gsGbImg = 0;
int gsDeadImg1 = 0, gsDeadImg2 = 0, gsDeadImg3 = 0;
int gsH1Img = 0, gsG1Img = 0, gsD1Img = 0;
#define GS_MAX_BULLETS 50

struct GsBullet {
	int x, y;
	bool active;
};

GsBullet gsPBullets[GS_MAX_BULLETS]; 
GsBullet gsGBullets[GS_MAX_BULLETS]; 


int gsScore = 0;
int gsMiss = 0;

const int GAMESTATE_TRAFFIC = 570;
const int GAMESTATE_TRAFFIC_LOADING = 580;

const int TR_SCREEN_W = 800;
const int TR_SCREEN_H = 600;

const int TR_TICK_MS = 25;           
const int TR_SCROLL_SPEED = 11;       
const int TR_BG_SCROLL_SPEED = 8;    
const int TR_SIDE_MOVE_SPEED = 10;    
const int TR_JUMP_SPEED = 10;        
const int TR_JUMP_MAX_HEIGHT = 100;  
const int TR_RUN_ANIM_TICKS = 6;     

int trBgY1 = 0;
int trBgY2 = 600;

int trStartImg = 0, trBgImg = 0, trWinImg1 = 0, trWinImg2 = 0, trWinImg3 = 0, trFinalBgImg = 0;
int trNoteImg = 0;
int trScoreImg = 0; 
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