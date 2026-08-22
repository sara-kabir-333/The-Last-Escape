#ifndef HEADER_H
#define HEADER_H

#include "Utils.h"

// Variables
int x = 0;
int y = 0;

int loadBg;
int menuBg;

int about1, about2, about3, about4, about5;
int aboutBg1, aboutBg2;

int backImg;
int nextImg;

int levelBg;
int level1Btn, level2Btn, level3Btn;
int level1Bg;

int btnPlay, btnAbout, btnSetting, btnExit;
int btnPlayHover, btnAboutHover, btnSettingHover, btnExitHover;

int gameState = 0;
int loadingStep = 0;
int btnHoverState = 0;

// Loading Update Function
void loadingUpdate()
{
	if (gameState != 0 && gameState != 5)
		return;

	loadingStep += 2;

	if (loadingStep >= 100)
	{
		loadingStep = 100;
		if (gameState == 0)
		{
			gameState = 1;
		}
		else if (gameState == 5)
		{
			gameState = 6;
		}
	}
}

// Draw Function
void iDraw()
{
	iClear();

	iSetColor(0, 0, 0);
	iFilledRectangle(0, 0, 800, 600);

	if (gameState == 0 || gameState == 5)
	{
		if (gameState == 0)
		{
			iShowImage(0, 0, 800, 600, loadBg);
		}
		else
		{
			iShowImage(0, 0, 800, 600, level1Bg);
		}

		iSetColor(180, 122, 33);
		iText(100, 120, "LOADING...", GLUT_BITMAP_TIMES_ROMAN_24);

		iSetColor(180, 122, 33);
		iRectangle(100, 80, 600, 30);

		int barWidth = (loadingStep * 600) / 100;
		iFilledRectangle(100, 80, barWidth, 30);
	}
	else if (gameState == 1)
	{
		iShowImage(0, 0, 800, 600, menuBg);

		if (btnHoverState == 1)
			iShowImage(340, 365, 300, 50, btnPlayHover);
		else
			iShowImage(340, 365, 300, 50, btnPlay);

		if (btnHoverState == 2)
			iShowImage(340, 295, 300, 50, btnAboutHover);
		else
			iShowImage(340, 295, 300, 50, btnAbout);

		if (btnHoverState == 3)
			iShowImage(340, 235, 300, 50, btnSettingHover);
		else
			iShowImage(340, 235, 300, 50, btnSetting);

		if (btnHoverState == 4)
			iShowImage(340, 175, 300, 50, btnExitHover);
		else
			iShowImage(340, 175, 300, 50, btnExit);
	}
	else if (gameState == 2)
	{
		iShowImage(0, 0, 800, 600, about1);
		iShowImage(50, 50, 100, 40, backImg);
		iShowImage(650, 50, 100, 40, nextImg);
	}
	else if (gameState == 7)
	{
		iShowImage(0, 0, 800, 600, about2);
		iShowImage(50, 50, 100, 40, backImg);
		iShowImage(650, 50, 100, 40, nextImg);
	}
	else if (gameState == 8)
	{
		iShowImage(0, 0, 800, 600, about3);
		iShowImage(50, 50, 100, 40, backImg);
		iShowImage(650, 50, 100, 40, nextImg);
	}
	else if (gameState == 9)
	{
		iShowImage(0, 0, 800, 600, about4);
		iShowImage(50, 50, 100, 40, backImg);
		iShowImage(650, 50, 100, 40, nextImg);
	}
	else if (gameState == 10)
	{
		iShowImage(0, 0, 800, 600, about5);
		iShowImage(50, 50, 100, 40, backImg);
		iShowImage(650, 50, 100, 40, nextImg);
	}
	else if (gameState == 11)
	{
		iShowImage(0, 0, 800, 600, aboutBg1);
		iShowImage(50, 50, 100, 40, backImg);
		iShowImage(650, 50, 100, 40, nextImg);
	}
	else if (gameState == 12)
	{
		iShowImage(0, 0, 800, 600, aboutBg2);
		iShowImage(50, 50, 100, 40, backImg);
	}
	else if (gameState == 3)
	{
		iShowImage(0, 0, 800, 600, levelBg);
		iShowImage(120, 120, 175, 342, level1Btn);
		iShowImage(307, 115, 175, 342, level2Btn);
		iShowImage(492, 115, 175, 342, level3Btn);
		iShowImage(68, 26, 120, 53, backImg);
	}
	else if (gameState == 6) // Level 1 Gameplay Escape State
	{
		iShowImage(0, 0, 800, 600, level1Bg);

		// Draw the escaping character using your (x, y) coordinates
		iSetColor(255, 0, 0);
		iFilledRectangle(x, y, 30, 50);
	}
}

void iMouseMove(int mx, int my) {}

void iPassiveMouseMove(int mx, int my)
{
	if (gameState == 1)
	{
		if (mx >= 340 && mx <= 640 && my >= 365 && my <= 415)
			btnHoverState = 1;
		else if (mx >= 340 && mx <= 640 && my >= 295 && my <= 345)
			btnHoverState = 2;
		else if (mx >= 340 && mx <= 640 && my >= 235 && my <= 285)
			btnHoverState = 3;
		else if (mx >= 340 && mx <= 640 && my >= 175 && my <= 225)
			btnHoverState = 4;
		else
			btnHoverState = 0;
	}
}

void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (gameState == 1)
		{
			if (mx >= 340 && mx <= 640 && my >= 365 && my <= 415)
				gameState = 3;
			else if (mx >= 340 && mx <= 640 && my >= 295 && my <= 345)
				gameState = 2;
			else if (mx >= 340 && mx <= 640 && my >= 175 && my <= 225)
				exit(0);
		}
		else if (gameState == 2)
		{
			if (mx >= 50 && mx <= 150 && my >= 50 && my <= 90) gameState = 1;
			else if (mx >= 650 && mx <= 750 && my >= 50 && my <= 90) gameState = 7;
		}
		else if (gameState == 7)
		{
			if (mx >= 50 && mx <= 150 && my >= 50 && my <= 90) gameState = 2;
			else if (mx >= 650 && mx <= 750 && my >= 50 && my <= 90) gameState = 8;
		}
		else if (gameState == 8)
		{
			if (mx >= 50 && mx <= 150 && my >= 50 && my <= 90) gameState = 7;
			else if (mx >= 650 && mx <= 750 && my >= 50 && my <= 90) gameState = 9;
		}
		else if (gameState == 9)
		{
			if (mx >= 50 && mx <= 150 && my >= 50 && my <= 90) gameState = 8;
			else if (mx >= 650 && mx <= 750 && my >= 50 && my <= 90) gameState = 10;
		}
		else if (gameState == 10)
		{
			if (mx >= 50 && mx <= 150 && my >= 50 && my <= 90) gameState = 9;
			else if (mx >= 650 && mx <= 750 && my >= 50 && my <= 90) gameState = 11;
		}
		else if (gameState == 11)
		{
			if (mx >= 50 && mx <= 150 && my >= 50 && my <= 90) gameState = 10;
			else if (mx >= 650 && mx <= 750 && my >= 50 && my <= 90) gameState = 12;
		}
		else if (gameState == 12)
		{
			if (mx >= 50 && mx <= 150 && my >= 50 && my <= 90) gameState = 11;
		}
		else if (gameState == 3)
		{
			if (mx >= 68 && mx <= 188 && my >= 26 && my <= 79)
				gameState = 1;
			else if (mx >= 120 && mx <= 295 && my >= 120 && my <= 462)
			{
				gameState = 5;
				loadingStep = 0;
			}
		}
	}
}

// Escape movement & audio controls
void fixedUpdate()
{
	if (gameState == 6)
	{
		if (isKeyPressed('w') || isSpecialKeyPressed(GLUT_KEY_UP))
			y++;
		if (isKeyPressed('a') || isSpecialKeyPressed(GLUT_KEY_LEFT))
			x--;
		if (isKeyPressed('s') || isSpecialKeyPressed(GLUT_KEY_DOWN))
			y--;
		if (isKeyPressed('d') || isSpecialKeyPressed(GLUT_KEY_RIGHT))
			x++;
	}

	if (isKeyPressed(' ')) {
		mciSendString("play ggsong from 0", NULL, 0, NULL);
	}
}

#endif