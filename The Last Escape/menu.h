#ifndef MENU_H
#define MENU_H

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

#endif