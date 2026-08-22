#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Loading progress timer callback
void loadingUpdate() {
	if (loadingStep < 100) {
		loadingStep++;
	}
}

// Draw callback
void iDraw() {
	iClear();

	if (gameState == 0) {
		iShowImage(0, 0, 800, 600, loadBg);
	}
	// Add your other gameState rendering here...
}

// Mouse click callback
void iMouse(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (gameState == 0) {
			gameState = 100; // Go to menu
		}
	}
}
// Add these at the bottom of Functions.h to satisfy iGraphics requirements:

void fixedUpdate() {
	// Leave empty if not used
}

void iPassiveMouseMove(int mx, int my) {
	// Leave empty if not used
}

// Empty required iGraphics callbacks
void iKeyboard(unsigned char key) {}
void iMouseMove(int mx, int my) {}
void iSpecialKeyboard(unsigned char key) {}

#endif