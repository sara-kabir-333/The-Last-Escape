#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Variables.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <mmsystem.h>

// Visual Studio specific library linking for audio (mciSendString)
#pragma comment(lib, "winmm.lib")

void loadingUpdate()
{
	if (gameState != 0)
		return;

	loadingStep++; // Move to the next loading frame

	if (loadingStep >= 24)
	{
		loadingStep = 24;
		gameState = 1; // Switch to Main Menu when loading is finished
	}
}

void iDraw()
{
	iClear();

	// Draw a solid black background first
	iSetColor(0, 0, 0);
	iFilledRectangle(0, 0, 800, 600);

	if (gameState == 0) // Loading Screen State
	{
		// Loop from 1 up to current loadingStep so images stack up sequentially without overlapping issues
		for (int i = 1; i <= loadingStep; i++)
		{
			if (i >= 1 && i <= 23)
			{
				iShowImage(0, 0, 800, 600, img[i]); // Display loading frames progressively
			}
			else if (i == 24)
			{
				iShowImage(0, 0, 800, 600, img[24]); // Display final loading frame (load100)
			}
		}
	}
	else if (gameState == 1) // Main Menu State
	{
		// 1. Draw the main menu background
		iShowImage(0, 0, 800, 600, menuBg);

		// 2. Draw buttons with hover effect
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
	else if (gameState == 2) // About Screen State 1 (aboutbg1)
	{
		// 1. Draw About page 1 background image
		iShowImage(0, 0, 800, 600, aboutBg1);

		// 2. Draw Back button at bottom-left corner
		iShowImage(50, 50, 100, 40, backImg);

		// 3. Draw Next button on the right side
		iShowImage(650, 50, 100, 40, nextImg);
	}
	else if (gameState == 4) // About Screen State 2 (aboutbg2)
	{
		// 1. Draw About page 2 background image
		iShowImage(0, 0, 800, 600, aboutBg2);

		// 2. Draw Back button at bottom to return to aboutbg1
		iShowImage(50, 50, 100, 40, backImg);
	}
	else if (gameState == 3) // Level Select Screen State
	{
		// 1. Draw Level Select Background
		iShowImage(0, 0, 800, 600, levelBg);

		// 2. Draw the 3 level cards matching the layout
		iShowImage(120, 120, 175, 342, level1Btn); // Level 1 Card
		iShowImage(307, 115, 175, 342, level2Btn); // Level 2 Card
		iShowImage(492, 115, 175, 342, level3Btn); // Level 3 Card

		// 3. Draw Back button at bottom-left corner
		iShowImage(68, 26, 120, 53, backImg);
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
		else if (gameState == 2) // Active only in About Screen 1 (aboutbg1)
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
		else if (gameState == 4) // Active only in About Screen 2 (aboutbg2)
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
			// Check Level 1 click area
			else if (mx >= 120 && mx <= 295 && my >= 120 && my <= 462)
			{
				printf("Level 1 Selected!\n");
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

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
	}
}

void fixedUpdate()
{
	if (gameState == 1) // Movement active only after loading/in game
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