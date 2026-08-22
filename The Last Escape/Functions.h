#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Variables.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

// Function to update loading progress for initial startup and level loading
void loadingUpdate()
{
	if (gameState != 0 && gameState != 5)
		return;

	loadingStep += 2; // Increase loading progress step

	if (loadingStep >= 100)
	{
		loadingStep = 100;
		if (gameState == 0)
		{
			gameState = 1; // Switch to Main Menu when initial loading reaches 100%
		}
		else if (gameState == 5)
		{
			gameState = 6; // Switch to Level 1 Gameplay when level loading reaches 100%
		}
	}
}

// Function to render graphics based on current game state
void iDraw()
{
	iClear();

	// Draw a solid black background first
	iSetColor(0, 0, 0);
	iFilledRectangle(0, 0, 800, 600);

	if (gameState == 0 || gameState == 5) // Loading Screen States
	{
		if (gameState == 0)
		{
			iShowImage(0, 0, 800, 600, loadBg);
		}
		else
		{
			iShowImage(0, 0, 800, 600, level1Bg);
		}

		// Draw Loading text
		iSetColor(180, 122, 33);
		iText(100, 120, "LOADING...", GLUT_BITMAP_TIMES_ROMAN_24);

		// Draw Progress Bar border and fill
		iSetColor(180, 122, 33);
		iRectangle(100, 80, 600, 30);

		int barWidth = (loadingStep * 600) / 100;
		iFilledRectangle(100, 80, barWidth, 30);
	}
	else if (gameState == 1) // Main Menu State
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
	else if (gameState == 2) // About Page 1
	{
		iShowImage(0, 0, 800, 600, about1);
		iShowImage(50, 50, 100, 40, backImg);
		iShowImage(650, 50, 100, 40, nextImg);
	}
	else if (gameState == 7) // About Page 2
	{
		iShowImage(0, 0, 800, 600, about2);
		iShowImage(50, 50, 100, 40, backImg);
		iShowImage(650, 50, 100, 40, nextImg);
	}
	else if (gameState == 8) // About Page 3
	{
		iShowImage(0, 0, 800, 600, about3);
		iShowImage(50, 50, 100, 40, backImg);
		iShowImage(650, 50, 100, 40, nextImg);
	}
	else if (gameState == 9) // About Page 4
	{
		iShowImage(0, 0, 800, 600, about4);
		iShowImage(50, 50, 100, 40, backImg);
		iShowImage(650, 50, 100, 40, nextImg);
	}
	else if (gameState == 10) // About Page 5
	{
		iShowImage(0, 0, 800, 600, about5);
		iShowImage(50, 50, 100, 40, backImg);
		iShowImage(650, 50, 100, 40, nextImg);
	}
	else if (gameState == 11) // About Page 6 (aboutBg1)
	{
		iShowImage(0, 0, 800, 600, aboutBg1);
		iShowImage(50, 50, 100, 40, backImg);
		iShowImage(650, 50, 100, 40, nextImg);
	}
	else if (gameState == 12) // About Final Page (aboutBg2) - Only Back button, no Next button
	{
		iShowImage(0, 0, 800, 600, aboutBg2);
		iShowImage(50, 50, 100, 40, backImg);
	}
	else if (gameState == 3) // Level Select Screen State
	{
		iShowImage(0, 0, 800, 600, levelBg);
		iShowImage(120, 120, 175, 342, level1Btn);
		iShowImage(307, 115, 175, 342, level2Btn);
		iShowImage(492, 115, 175, 342, level3Btn);
		iShowImage(68, 26, 120, 53, backImg);
	}
	else if (gameState == 6) // Level 1 Gameplay State
	{
		iShowImage(0, 0, 800, 600, level1Bg);
	}
}

void iMouseMove(int mx, int my)
{
}

void iPassiveMouseMove(int mx, int my)
{
	// Track mouse hover position in Main Menu
	if (gameState == 1)
	{
		if (mx >= 340 && mx <= 640 && my >= 365 && my <= 415)
		{
			btnHoverState = 1; // Hovering on Play
		}
		else if (mx >= 340 && mx <= 640 && my >= 295 && my <= 345)
		{
			btnHoverState = 2; // Hovering on About
		}
		else if (mx >= 340 && mx <= 640 && my >= 235 && my <= 285)
		{
			btnHoverState = 3; // Hovering on Setting
		}
		else if (mx >= 340 && mx <= 640 && my >= 175 && my <= 225)
		{
			btnHoverState = 4; // Hovering on Exit
		}
		else
		{
			btnHoverState = 0; // Mouse outside buttons
		}
	}
}

void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (gameState == 1) // Main Menu clicks
		{
			if (mx >= 340 && mx <= 640 && my >= 365 && my <= 415)
			{
				gameState = 3; // Switch to Level Select
				printf("Play Button Clicked -> Opening Level Select!\n");
			}
			else if (mx >= 340 && mx <= 640 && my >= 295 && my <= 345)
			{
				gameState = 2; // Switch to About Page 1 (about1)
				printf("About Button Clicked -> Opening About Page 1!\n");
			}
			else if (mx >= 340 && mx <= 640 && my >= 235 && my <= 285)
			{
				printf("Setting Button Clicked!\n");
			}
			else if (mx >= 340 && mx <= 640 && my >= 175 && my <= 225)
			{
				exit(0); // Exit game
			}
		}
		else if (gameState == 2) // About Page 1 navigation
		{
			if (mx >= 50 && mx <= 150 && my >= 50 && my <= 90)
			{
				gameState = 1; // Back to Menu
			}
			else if (mx >= 650 && mx <= 750 && my >= 50 && my <= 90)
			{
				gameState = 7; // Next to About Page 2
			}
		}
		else if (gameState == 7) // About Page 2 navigation
		{
			if (mx >= 50 && mx <= 150 && my >= 50 && my <= 90)
			{
				gameState = 2; // Back to About Page 1
			}
			else if (mx >= 650 && mx <= 750 && my >= 50 && my <= 90)
			{
				gameState = 8; // Next to About Page 3
			}
		}
		else if (gameState == 8) // About Page 3 navigation
		{
			if (mx >= 50 && mx <= 150 && my >= 50 && my <= 90)
			{
				gameState = 7; // Back to About Page 2
			}
			else if (mx >= 650 && mx <= 750 && my >= 50 && my <= 90)
			{
				gameState = 9; // Next to About Page 4
			}
		}
		else if (gameState == 9) // About Page 4 navigation
		{
			if (mx >= 50 && mx <= 150 && my >= 50 && my <= 90)
			{
				gameState = 8; // Back to About Page 3
			}
			else if (mx >= 650 && mx <= 750 && my >= 50 && my <= 90)
			{
				gameState = 10; // Next to About Page 5
			}
		}
		else if (gameState == 10) // About Page 5 navigation
		{
			if (mx >= 50 && mx <= 150 && my >= 50 && my <= 90)
			{
				gameState = 9; // Back to About Page 4
			}
			else if (mx >= 650 && mx <= 750 && my >= 50 && my <= 90)
			{
				gameState = 11; // Next to About Page 6 (aboutBg1)
			}
		}
		else if (gameState == 11) // About Page 6 (aboutBg1) navigation
		{
			if (mx >= 50 && mx <= 150 && my >= 50 && my <= 90)
			{
				gameState = 10; // Back to About Page 5
			}
			else if (mx >= 650 && mx <= 750 && my >= 50 && my <= 90)
			{
				gameState = 12; // Next to About Final Page (aboutBg2)
			}
		}
		else if (gameState == 12) // About Final Page (aboutBg2) navigation (Back only)
		{
			if (mx >= 50 && mx <= 150 && my >= 50 && my <= 90)
			{
				gameState = 11; // Back to aboutBg1
			}
		}
		else if (gameState == 3) // Level Select Screen State
		{
			if (mx >= 68 && mx <= 188 && my >= 26 && my <= 79)
			{
				gameState = 1; // Return to Main Menu
			}
			else if (mx >= 120 && mx <= 295 && my >= 120 && my <= 462)
			{
				gameState = 5;      // Switch to Level 1 Loading Screen
				loadingStep = 0;    // Reset progress bar
			}
			else if (mx >= 307 && mx <= 482 && my >= 115 && my <= 457)
			{
				// Level 2
			}
			else if (mx >= 492 && mx <= 667 && my >= 115 && my <= 457)
			{
				// Level 3
			}
		}
	}
}

void fixedUpdate()
{
	if (gameState == 1)
	{
		if (isKeyPressed('w') || isSpecialKeyPressed(GLUT_KEY_UP))
		{
			y++;
		}
		if (isKeyPressed('a') || isSpecialKeyPressed(GLUT_KEY_LEFT))
		{
			x--;
		}
		if (isKeyPressed('s') || isSpecialKeyPressed(GLUT_KEY_DOWN))
		{
			y--;
		}
		if (isKeyPressed('d') || isSpecialKeyPressed(GLUT_KEY_RIGHT))
		{
			x++;
		}
	}

	if (isKeyPressed(' ')) {
		mciSendString("play ggsong from 0", NULL, 0, NULL);
	}
}

#endif