#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Variables.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

void loadingUpdate()
{
	// Handle loading updates for both initial startup (gameState 0) and Level 1 loading (gameState 5)
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

void iDraw()
{
	iClear();

	// Draw a solid black background first
	iSetColor(0, 0, 0);
	iFilledRectangle(0, 0, 800, 600);

	if (gameState == 0 || gameState == 5) // Loading Screen States (Initial & Level 1)
	{
		// Display different background image based on current state
		if (gameState == 0)
		{
			iShowImage(0, 0, 800, 600, loadBg); // Show initial loading screen background
		}
		else
		{
			iShowImage(0, 0, 800, 600, level1Bg); // Show Level 1 loading background
		}

		// Draw Loading text in Golden color with a larger font
		iSetColor(180, 122, 33); // Golden RGB color
		iText(100, 120, "LOADING...", GLUT_BITMAP_TIMES_ROMAN_24);

		// Draw Outer Progress Bar Rectangle Border
		iSetColor(180, 122, 33); // Golden border
		iRectangle(100, 80, 600, 30);

		// Draw Inner Golden Filled Progress Bar based on loadingStep
		iSetColor(180, 122, 33); // Golden fill color
		int barWidth = (loadingStep * 600) / 100; // Calculate fill width proportionally (Max width = 600)
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
	else if (gameState == 2) // About Screen State 1
	{
		iShowImage(0, 0, 800, 600, aboutBg1);
		iShowImage(50, 50, 100, 40, backImg);
		iShowImage(650, 50, 100, 40, nextImg);
	}
	else if (gameState == 4) // About Screen State 2
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
	// Track mouse hover position in Main Menu without clicking
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
		if (gameState == 1) // Active only in Main Menu
		{
			// Check Play button click area -> Switch to Level Select Screen
			if (mx >= 340 && mx <= 640 && my >= 365 && my <= 415)
			{
				gameState = 3;
				printf("Play Button Clicked -> Opening Level Select!\n");
			}
			// Check About button click area -> Switch to About Screen 1
			else if (mx >= 340 && mx <= 640 && my >= 295 && my <= 345)
			{
				gameState = 2;
				printf("About Button Clicked!\n");
			}
			// Check Setting button click area
			else if (mx >= 340 && mx <= 640 && my >= 235 && my <= 285)
			{
				printf("Setting Button Clicked!\n");
			}
			// Check Exit button click area
			else if (mx >= 340 && mx <= 640 && my >= 175 && my <= 225)
			{
				exit(0); // Exit the game completely
			}
		}
		else if (gameState == 2) // Active only in About Screen 1
		{
			// Check Back button click area -> Return to Main Menu
			if (mx >= 50 && mx <= 150 && my >= 50 && my <= 90)
			{
				gameState = 1;
				printf("Back Button Clicked, returning to Menu!\n");
			}
			// Check Next button click area -> Go to About Screen 2
			else if (mx >= 650 && mx <= 750 && my >= 50 && my <= 90)
			{
				gameState = 4;
				printf("Next Button Clicked, opening About Page 2!\n");
			}
		}
		else if (gameState == 4) // Active only in About Screen 2
		{
			// Check Back button click area -> Return to About Screen 1
			if (mx >= 50 && mx <= 150 && my >= 50 && my <= 90)
			{
				gameState = 2;
				printf("Back Button Clicked, returning to About Page 1!\n");
			}
		}
		else if (gameState == 3) // Active only in Level Select Screen
		{
			// Check Back button click area
			if (mx >= 68 && mx <= 188 && my >= 26 && my <= 79)
			{
				gameState = 1; // Return back to Main Menu
				printf("Returned to Main Menu from Level Select!\n");
			}
			// Check Level 1 click area -> Trigger Level 1 Loading (State 5)
			else if (mx >= 120 && mx <= 295 && my >= 120 && my <= 462)
			{
				gameState = 5;      // Switch to Level 1 Loading Screen
				loadingStep = 0;    // Reset progress bar from 0%
				printf("Level 1 Selected -> Loading Level 1...\n");
			}
			// Check Level 2 click area
			else if (mx >= 307 && mx <= 482 && my >= 115 && my <= 457)
			{
				printf("Level 2 Selected!\n");
			}
			// Check Level 3 click area
			else if (mx >= 492 && mx <= 667 && my >= 115 && my <= 457)
			{
				printf("Level 3 Selected!\n");
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
		mciSendString("play ggsong from 0", NULL, 0, NULL); // Play background audio on spacebar
	}
}

#endif