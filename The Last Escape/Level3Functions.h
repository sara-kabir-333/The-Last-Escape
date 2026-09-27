// ===================== Level3Functions.h (only gsDraw() er state == -1 block changed) =====================
#pragma once
#include "Menu.h"
#include "Level3Variables.h"

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
			if (isSpecialKeyPressed(GLUT_KEY_RIGHT) && lv3HeroX < LV3_HERO_STOP_X) {
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

		{
			int heroLifeImg = lv3GetHeroLifeImg(lv3HeroHealth, LV3_HERO_START_HEALTH);
			if (heroLifeImg > 0) iShowImage(120, 545, 170, 60, heroLifeImg);
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

			{
				int guardLifeImg = lv3GetGuardLifeImg(lv3Guard.health, LV3_GUARD_START_HEALTH);
				if (guardLifeImg > 0) iShowImage(580, 545, 170, 60, guardLifeImg);
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

		if (backImg > 0) iShowImage(50, 50, 80, 32, backImg);
	}
	else if (lv3SubState == 1) {
		{
			int noteW = 500, noteH = 250;
			int noteX = (800 - noteW) / 2;
			int noteY = 20;

			iShowImage(noteX, noteY, noteW, noteH, lv3NoteImg);

			iSetColor(0, 0, 0);
			iText(noteX + 105, noteY + 63, "GUARD DEFEATED!", GLUT_BITMAP_TIMES_ROMAN_24);

			iSetColor(0, 0, 0);
			iText(noteX + 120, noteY + 40, "COLLECT THE GUN!", GLUT_BITMAP_HELVETICA_18);
		}

		iShowImage(330, 200, 180, 100, lv3GunImageId);

		iSetColor(255, 0, 0);

		for (int offset = -2; offset <= 2; offset++) {
			iLine(410 + offset, 330, 410 + offset, 290);
		}

		for (int offset = -2; offset <= 2; offset++) {
			iLine(410 + offset, 290, 400 + offset, 305);
			iLine(410 + offset, 290, 420 + offset, 305);
		}

		if (backImg > 0) iShowImage(50, 50, 80, 32, backImg);
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

		if (backImg > 0) iShowImage(50, 50, 80, 32, backImg);
	}
	else if (lv3SubState == 3) {
		iShowImage(lv3HeroX, lv3HeroY, lv3HeroWidth, lv3HeroHeight, lv3HeroStandId);

		{
			int noteW = 500, noteH = 250;
			int noteX = (800 - noteW) / 2;
			int noteY = 20;

			iShowImage(noteX, noteY, noteW, noteH, lv3NoteImg);
			iSetColor(0, 0, 0);
			iText(noteX + 110, noteY + 63, "YOU REACHED THE DOOR!", GLUT_BITMAP_HELVETICA_18);
			iText(noteX + 60, noteY + 40, "2 More Gangsters Are Waiting Outside...", GLUT_BITMAP_HELVETICA_18);
		}

		if (backImg > 0) iShowImage(50, 50, 80, 32, backImg);
		if (nextImg > 0) iShowImage(650, 50, 80, 32, nextImg);
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

void gsResetGame() {
	gsScore = 0;
	gsMiss = 0;
	gsGangsterHits = 0;
	gsCurrentGangster = 1;
	gsPrisonerX = 100;
	gsGangsterX = 580;
	gsGangsterY = GS_GANGSTER_BASE_Y;
	gsDeadX1 = 0;
	gsDeadX2 = 0;
	gsDeadX3 = 0;
	gsDeadY1 = 0;
	gsDeadY2 = 0;
	gsDeadY3 = 0;
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

	if (gsIsJumping) {
		gsPrisonerY += gsPrisonerVelY;
		gsPrisonerVelY -= gsGravity;

		if (gsPrisonerY <= gsGroundY) {
			gsPrisonerY = gsGroundY;
			gsPrisonerVelY = 0;
			gsIsJumping = false;
		}
	}

	gsGangsterShootCounter++;
	if (gsGangsterShootCounter >= 150) {
		gsGangsterShootCounter = 0;
		for (int i = 0; i < GS_MAX_BULLETS; i++) {
			if (!gsGBullets[i].active) {
				gsGBullets[i].x = gsGangsterX - 20;
				gsGBullets[i].y = gsGangsterY + gsGangsterHeight *0.75;
				gsGBullets[i].active = true;
				break;
			}
		}
	}

	for (int i = 0; i < GS_MAX_BULLETS; i++) {
		if (gsPBullets[i].active) {
			gsPBullets[i].x += 15;

			if (gsPBullets[i].x > GS_SCREEN_W) {
				gsPBullets[i].active = false;
			}

			if (gsCurrentGangster <= 2 &&
				gsPBullets[i].x + 30 >= gsGangsterX && gsPBullets[i].x <= gsGangsterX + gsGangsterWidth &&
				gsPBullets[i].y + 15 >= gsGangsterY && gsPBullets[i].y <= gsGangsterY + gsGangsterHeight) {

				gsPBullets[i].active = false;
				gsGangsterHits++;
				gsScore++;

				if (gsGangsterHits >= 10) {
					if (gsCurrentGangster == 1) {
						gsDeadX1 = gsGangsterX;
						gsDeadY1 = gsGangsterY;
					}

					gsCurrentGangster++;
					gsGangsterHits = 0;

					if (gsCurrentGangster == 2) {
						gsGangsterX = GS_GUARD_RIGHT_X;
						gsGangsterY = GS_GUARD_RIGHT_Y;
					}

					if (gsCurrentGangster > 2) {
						gsState = 1;
						level3Completed = true;
					}
				}
			}
		}
	}

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

				if (gsMiss >= GS_MAX_MISS) {
					gsState = 2;
				}
			}
		}
	}
}

void gsDraw() {
	// 1. Instruction Screen State
	// FIX: ekhon note.png (imgnote) use hocche, r text-er cordinate
	// traffic runner-er intro note-er moto (noteX/noteY based) kore deya holo.
	if (gsState == -1) {
		iShowImage(0, 0, GS_SCREEN_W, GS_SCREEN_H, gsBgImg);

		int noteW = 500, noteH = 250;
		int noteX = (GS_SCREEN_W - noteW) / 2;
		int noteY = 20;
		if (imgnote > 0) iShowImage(noteX, noteY, noteW, noteH, imgnote);

		iSetColor(0, 0, 0);
		iText(noteX + 35, noteY + 63, "Prisoner has to fight 2 gangsters sequentially!Left", GLUT_BITMAP_HELVETICA_18);
		iText(noteX + 100, noteY + 40, "Click to Shoot | Right-Click to Jump!", GLUT_BITMAP_HELVETICA_18);

		iShowImage(50, 50, 80, 32, backImg);
		if (nextImg > 0) iShowImage(650, 50, 80, 32, nextImg);
		return;
	}

	// 2. Win Screen State (Draw bodies first, then show the banner)
	if (gsState == 1) {
		iShowImage(0, 0, GS_SCREEN_W, GS_SCREEN_H, gsBgImg);

		if (gsDeadX1 > 0) iShowImage(gsDeadX1, gsDeadY1, gsGangsterWidth, gsGangsterHeight, gsDeadImg);

		iShowImage(gsPrisonerX, gsPrisonerY, gsPrisonerWidth, gsPrisonerHeight, gsPrisonerImg);

		iShowImage(20, 50, 760, 140, gsWpImg);
		iSetColor(0, 0, 0);
		iText(220, 95, "YOU WIN! All Gangsters Defeated!", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(245, 75, " Click to Continue", GLUT_BITMAP_HELVETICA_18);

		if (backImg > 0) iShowImage(50, 50, 80, 32, backImg);
		return;
	}

	// 3. Game Over Screen State
	if (gsState == 2) {
		iShowImage(0, 0, GS_SCREEN_W, GS_SCREEN_H, gsBgImg);
		iShowImage(20, 50, 760, 140, gsWpImg);

		iSetColor(0, 0, 0);
		iText(220, 95, "GAME OVER", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(220, 75, "Click anywhere with Mouse to Restart", GLUT_BITMAP_HELVETICA_18);

		iShowImage(50, 50, 80, 32, backImg);
		return;
	}

	// 4. Active Gameplay Screen
	iShowImage(0, 0, GS_SCREEN_W, GS_SCREEN_H, gsBgImg);

	if (gsCurrentGangster > 1) {
		iShowImage(gsDeadX1, gsDeadY1, gsGangsterWidth, gsGangsterHeight, gsDeadImg);
	}

	if (gsCurrentGangster == 1) {
		if (gsGuardRightImg > 0) iShowImage(GS_GUARD_RIGHT_X, GS_GUARD_RIGHT_Y, gsGangsterWidth, gsGangsterHeight, gsGuardRightImg);
	}

	if (gsCurrentGangster <= 2 && gsState == 0) {
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

	iShowImage(550, 545, 230, 45, gsH1Img);
	iShowImage(550, 495, 230, 40, gsG1Img);
	iShowImage(550, 445, 230, 40, gsD1Img);

	char gsScoreStr[20], gsMissStr[20], gsBossStr[20];
	sprintf(gsScoreStr, "%d / 10", gsGangsterHits);
	sprintf(gsBossStr, "%d / 2", gsCurrentGangster);
	sprintf(gsMissStr, "%d / %d", gsMiss, GS_MAX_MISS);

	iSetColor(255, 255, 255);
	iText(685, 558, gsScoreStr, GLUT_BITMAP_HELVETICA_12);
	iText(685, 508, gsBossStr, GLUT_BITMAP_HELVETICA_12);
	iText(685, 458, gsMissStr, GLUT_BITMAP_HELVETICA_12);

	if (backImg > 0) iShowImage(50, 50, 80, 32, backImg);
}

void gsMouseMove(int mx, int my)
{
	gsPrisonerX = mx - gsPrisonerWidth / 2;

	if (gsPrisonerX < 0)
	{
		gsPrisonerX = 0;
	}
	if (gsPrisonerX > GS_SCREEN_W / 2 - gsPrisonerWidth)
	{
		gsPrisonerX = GS_SCREEN_W / 2 - gsPrisonerWidth;
	}
};


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
				gsPBullets[i].x = gsPrisonerX + gsPrisonerWidth - 20;
				gsPBullets[i].y = gsPrisonerY + gsPrisonerHeight *0.75;
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

		if (backImg > 0) iShowImage(50, 50, 80, 32, backImg);
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

		if (backImg > 0) iShowImage(50, 50, 80, 32, backImg);
		return;
	}
	else if (trWinState == 2) {
		iShowImage(0, 0, TR_SCREEN_W, TR_SCREEN_H, trWinImg2);
		if (backImg > 0) iShowImage(50, 50, 80, 32, backImg);
		return;
	}
	else if (trWinState == 3) {
		iShowImage(0, 0, TR_SCREEN_W, TR_SCREEN_H, trWinImg3);
		if (backImg > 0) iShowImage(50, 50, 80, 32, backImg);
		return;
	}
	else if (trWinState == 4) {
		iShowImage(0, 0, TR_SCREEN_W, TR_SCREEN_H, trFinalBgImg);
		if (backImg > 0) iShowImage(50, 50, 80, 32, backImg);
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

	iShowImage(560, 535, 220, 45, trScoreImg);

	iSetColor(255, 215, 0);
	char scoreStr[50];
	sprintf(scoreStr, "%d", trScore);
	iText(700, 549, scoreStr, GLUT_BITMAP_HELVETICA_18);

	if (trGameOver) {
		int noteW = 500, noteH = 250;
		int noteX = (TR_SCREEN_W - noteW) / 2;
		int noteY = 20;
		iShowImage(noteX, noteY, noteW, noteH, trNoteImg);

		iSetColor(0, 0, 0);
		iText(noteX + 175, noteY + 63, "GAME OVER!", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(noteX + 145, noteY + 40, "Press 'R' to Restart", GLUT_BITMAP_HELVETICA_18);
	}

	if (backImg > 0) iShowImage(50, 50, 80, 32, backImg);
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
			trObsList[i].y -= TR_SCROLL_SPEED;

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
					if (trPlayerY + 15 >= obsBottom && trPlayerY + 15 <= obsBottom + 40) {
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
			trRoofGems[i].y -= TR_SCROLL_SPEED;

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
			trManholeList[i].y -= TR_SCROLL_SPEED;

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
		trWinTimer += TR_TICK_MS;
		if (trWinTimer >= 4000) {
			trWinState = 3;
			trWinTimer = 0;
		}
		return;
	}
	else if (trWinState == 3) {
		trWinTimer += TR_TICK_MS;
		if (trWinTimer >= 4000) {
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
		trPlayerDrawX -= (double)TR_SIDE_MOVE_SPEED;
		if (trPlayerDrawX < trLaneX[0] + 5) {
			trPlayerDrawX = trLaneX[0] + 5;
		}
	}

	if (isSpecialKeyPressed(GLUT_KEY_RIGHT)) {
		trPlayerDrawX += (double)TR_SIDE_MOVE_SPEED;
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

	trBgY1 -= TR_BG_SCROLL_SPEED;
	trBgY2 -= TR_BG_SCROLL_SPEED;

	if (trBgY1 <= -TR_SCREEN_H)
		trBgY1 = trBgY2 + TR_SCREEN_H;

	if (trBgY2 <= -TR_SCREEN_H)
		trBgY2 = trBgY1 + TR_SCREEN_H;

	trUpdateObstacles();
	trUpdateRoofGems();
	trUpdateManholes();

	if (trIsJumping) {
		if (trJumpUp) {
			trJumpHeight += TR_JUMP_SPEED;
			if (trJumpHeight >= TR_JUMP_MAX_HEIGHT)
				trJumpUp = false;
		}
		else {
			trJumpHeight -= TR_JUMP_SPEED;
			if (trJumpHeight <= 0) {
				trJumpHeight = 0;
				trIsJumping = false;
			}
		}
	}

	static int trAnimCounter = 0;
	trAnimCounter++;
	if (trAnimCounter >= TR_RUN_ANIM_TICKS) {
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