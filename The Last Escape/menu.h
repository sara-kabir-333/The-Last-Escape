#ifndef MENU_H
#define MENU_H

#include "variables.h"
#include "iGraphics.h"
#include <cstdlib>

void drawMenu() {
	iShowImage(0, 0, 800, 600, menuBg);

	if (btnHoverState == 1) iShowImage(340, 363, 300, 50, btnPlayHover);
	else iShowImage(340, 363, 300, 50, btnPlay);

	if (btnHoverState == 2) iShowImage(340, 297, 300, 50, btnAboutHover);
	else iShowImage(340, 297, 300, 50, btnAbout);

	if (btnHoverState == 3) iShowImage(340, 237, 300, 50, btncreditHover);
	else iShowImage(340, 237, 300, 50, btncredit);

	if (btnHoverState == 4) iShowImage(340, 175, 300, 50, btnExitHover);
	else iShowImage(340, 175, 300, 50, btnExit);
}

void handleMenuMouse(int mx, int my) {
	if (mx >= 340 && mx <= 640 && my >= 365 && my <= 415)
	{
		gameState = 300;
	}
	else if (mx >= 340 && mx <= 640 && my >= 295 && my <= 345)
	{
		gameState = 200;
	}
	else if (mx >= 340 && mx <= 640 && my >= 235 && my <= 285)
	{
		// Credits
	}
	else if (mx >= 340 && mx <= 640 && my >= 175 && my <= 225)
	{
		exit(0);
	}
}

void handleMenuPassiveMouse(int mx, int my) {
	if (mx >= 340 && mx <= 640 && my >= 365 && my <= 415) btnHoverState = 1;
	else if (mx >= 340 && mx <= 640 && my >= 295 && my <= 345) btnHoverState = 2;
	else if (mx >= 340 && mx <= 640 && my >= 235 && my <= 285) btnHoverState = 3;
	else if (mx >= 340 && mx <= 640 && my >= 175 && my <= 225) btnHoverState = 4;
	else btnHoverState = 0;
}

#endif