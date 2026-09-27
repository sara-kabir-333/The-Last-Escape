#pragma once
#include "Menu.h"
#include "Level2Variables.h"

void resetInvestPuzzle() {
	investStage = 1;
	investPiecesFoundCount = 0;
	investPuzzleCompletedFlag = false;
	investDraggedPiece = -1;
	investIsDragging = false;

	int defaultPieceX[6] = { 50, 400, 50, 400, 50, 400 };
	int defaultPieceY[6] = { 50, 50, 250, 250, 400, 400 };

	for (int i = 0; i < 6; i++) {
		investCollected[i] = false;
		investPlaced[i] = false;
		investPieceX[i] = defaultPieceX[i];
		investPieceY[i] = defaultPieceY[i];
	}
}

void checkInvestSearchLocation(int mx, int my) {
	if (investStage != 1) return;

	if (mx >= 350 && mx <= 480 && my >= 100 && my <= 180) { if (!investCollected[0]) { investCollected[0] = true; investPiecesFoundCount++; } }
	if (mx >= 60 && mx <= 160 && my >= 280 && my <= 360)  { if (!investCollected[1]) { investCollected[1] = true; investPiecesFoundCount++; } }
	if (mx >= 550 && mx <= 680 && my >= 240 && my <= 360) { if (!investCollected[2]) { investCollected[2] = true; investPiecesFoundCount++; } }
	if (mx >= 30 && mx <= 130 && my >= 40 && my <= 120)   { if (!investCollected[3]) { investCollected[3] = true; investPiecesFoundCount++; } }
	if (mx >= 190 && mx <= 260 && my >= 40 && my <= 160)  { if (!investCollected[4]) { investCollected[4] = true; investPiecesFoundCount++; } }
	if (mx >= 380 && mx <= 450 && my >= 220 && my <= 280) { if (!investCollected[5]) { investCollected[5] = true; investPiecesFoundCount++; } }

	if (investPiecesFoundCount >= 6) {
		investStage = 2;
	}
}

void checkInvestPiecePlacement(int pieceIndex) {
	int diffX = investPieceX[pieceIndex] - investCorrectX[pieceIndex];
	int diffY = investPieceY[pieceIndex] - investCorrectY[pieceIndex];

	if (diffX > -40 && diffX < 40 && diffY > -40 && diffY < 40) {
		investPieceX[pieceIndex] = investCorrectX[pieceIndex];
		investPieceY[pieceIndex] = investCorrectY[pieceIndex];
		investPlaced[pieceIndex] = true;
	}
}

bool checkIfInvestPuzzleComplete() {
	for (int i = 0; i < 6; i++) {
		if (!investPlaced[i]) return false;
	}
	return true;
}

void drawInvestPuzzle() {
	if (investStage == 1) {
		if (investRoomImg > 0) iShowImage(0, 0, 800, 600, investRoomImg);
		if (investNoteImg > 0) iShowImage(150, -25, 480, 280, investNoteImg);

		iSetColor(0, 0, 0);
		iText(220, 35, "Collect 6 torn pieces from the room", GLUT_BITMAP_HELVETICA_18);

		// Piece counter now uses piece.png (same position/style as the
		// score.png counter used in the traffic-runner / vault-runner games)
		// instead of plain "Pieces Found: X/6" text.
		if (investPieceCountImg > 0) iShowImage(560, 535, 220, 45, investPieceCountImg);

		char counterText[50];
		sprintf(counterText, "%d/6", investPiecesFoundCount);
		iSetColor(255, 215, 0);
		iText(700, 549, counterText, GLUT_BITMAP_HELVETICA_18);
	}
	else if (investStage == 2) {
		if (investTableImg > 0) iShowImage(0, 0, 800, 600, investTableImg);
		if (investNoteImg > 0) iShowImage(150, -25, 480, 280, investNoteImg);

		iSetColor(0, 0, 0);
		iText(190, 45, "Stage 2: Arrange the 6 pieces into position", GLUT_BITMAP_HELVETICA_18);

		for (int i = 0; i < 6; i++) {
			iSetColor(255, 255, 255);
			iRectangle(investCorrectX[i], investCorrectY[i], 80, 40);

			char outlineNum[10];
			sprintf(outlineNum, "Point %d", i + 1);
			iText(investCorrectX[i] + 15, investCorrectY[i] + 12, outlineNum, GLUT_BITMAP_HELVETICA_12);
		}

		for (int i = 0; i < 6; i++) {
			if (investPieceImg[i] > 0) {
				iShowImage(investPieceX[i], investPieceY[i], INVEST_PIECE_SIZE_W, INVEST_PIECE_SIZE_H, investPieceImg[i]);
			}
		}

		if (checkIfInvestPuzzleComplete() && !investPuzzleCompletedFlag) {
			investPuzzleCompletedFlag = true;
			investCompletionTimerStart = GetTickCount64();
		}

		if (investPuzzleCompletedFlag) {
			double elapsedTime = (GetTickCount64() - investCompletionTimerStart) / 1000.0;

			if (elapsedTime < 3.0) {
				iSetColor(0, 0, 0);
				iText(280, 20, "Assembling Room Data...", GLUT_BITMAP_HELVETICA_18);
			}
			else {
				vaultUnlocked = true;
				resetInvestPuzzle();
				gameState = GAMESTATE_LEVEL2_MAP;
			}
		}
	}

	iShowImage(50, 50, 80, 32, backImg);
}

void handleInvestMouseDown(int mx, int my) {
	if (mx >= 50 && mx <= 150 && my >= 50 && my <= 90) {
		gameState = GAMESTATE_LEVEL2_MAP;
		return;
	}

	if (investStage == 1) {
		checkInvestSearchLocation(mx, my);
	}
	else if (investStage == 2 && !investPuzzleCompletedFlag) {
		for (int i = 5; i >= 0; i--) {
			if (!investPlaced[i]) {
				if (mx >= investPieceX[i] && mx <= investPieceX[i] + INVEST_PIECE_SIZE_W &&
					my >= investPieceY[i] && my <= investPieceY[i] + INVEST_PIECE_SIZE_H) {

					investDraggedPiece = i;
					investIsDragging = true;
					investGrabOffsetX = mx - investPieceX[i];
					investGrabOffsetY = my - investPieceY[i];
					break;
				}
			}
		}
	}
}

void handleInvestMouseUp(int mx, int my) {
	if (investStage == 2 && investIsDragging && investDraggedPiece != -1) {
		checkInvestPiecePlacement(investDraggedPiece);
		investDraggedPiece = -1;
		investIsDragging = false;
	}
}

void handleInvestMouseMove(int mx, int my) {
	if (investStage == 2 && investIsDragging && investDraggedPiece != -1) {
		investPieceX[investDraggedPiece] = mx - investGrabOffsetX;
		investPieceY[investDraggedPiece] = my - investGrabOffsetY;
	}
}


void vrResetGame() {
	vrIsStarted = false;
	vrShowVault3 = false;
	vrGameOver = false;
	vrGameWon = false;
	vrBoxX = 800;
	vrRockX = 1100;
	vrDistance = 0;
	vrDistCounter = 0;
	vrCoinScore = 0;
	vrRunnerY = 200;
	vrIsJumping = false;
	vrJumpCount = 0;
	vrIsMouseHeld = false;
	vrFallCounter = 0;
	vrGameSpeed = 4;
	vrBgX1 = 0;
	vrBgX2 = 800;
	vrBall1X = 700; vrBall1Y = 220;
	vrBall2X = 1100; vrBall2Y = 285;
	vrRedBallX = 1500; vrRedBallY = 285;
	vrVault3TimerStarted = false;
}

void vrFixedUpdate() {
	if (!vrIsStarted || vrGameOver) return;

	vrBgX1 -= vrGameSpeed;
	vrBgX2 -= vrGameSpeed;

	if (vrBgX1 <= -800) {
		vrBgX1 = vrBgX2 + 800;
	}
	if (vrBgX2 <= -800) {
		vrBgX2 = vrBgX1 + 800;
	}

	vrAnimTimer++;
	if (vrAnimTimer >= 6) {
		vrCurrentFrame = (vrCurrentFrame + 1) % 3;
		vrAnimTimer = 0;
	}

	vrDistCounter++;
	int threshold = vrIsMouseHeld ? 4 : 8;
	if (vrDistCounter % threshold == 0) {
		vrDistance++;
	}

	vrGameSpeed = 4 + (vrDistance / 150);
	if (vrGameSpeed > 12) {
		vrGameSpeed = 12;
	}

	vrBoxX -= vrGameSpeed;
	if (vrBoxX < -vrBoxWidth) {
		vrBoxX = 850 + (rand() % 300);
	}

	vrRockX -= vrGameSpeed;
	if (vrRockX < -60) {
		vrRockX = 900 + (rand() % 400);
	}

	vrBall1X -= vrGameSpeed;
	if (vrBall1X < -20) {
		vrBall1X = 800 + (rand() % 300);
		vrBall1Y = (rand() % 2 == 0) ? 220 : 285;
	}

	vrBall2X -= vrGameSpeed;
	if (vrBall2X < -20) {
		vrBall2X = 900 + (rand() % 350);
		vrBall2Y = (rand() % 2 == 0) ? 220 : 285;
	}

	vrRedBallX -= vrGameSpeed;
	if (vrRedBallX < -20) {
		vrRedBallX = 1600 + (rand() % 500);
		vrRedBallY = (rand() % 2 == 0) ? 220 : 285;
	}

	if (vrIsJumping) {
		vrRunnerY += vrRunnerDy;

		if (vrRunnerDy > 0) {
			vrRunnerDy -= 2;
		}
		else {
			if (vrIsMouseHeld) {
				vrFallCounter++;
				if (vrFallCounter % 3 == 0) {
					vrRunnerDy -= 1;
				}
			}
			else {
				vrRunnerDy -= 2;
			}
		}

		if (vrRunnerY <= 200) {
			vrRunnerY = 200;
			vrIsJumping = false;
			vrJumpCount = 0;
			vrRunnerDy = 0;
			vrFallCounter = 0;
		}
	}

	if (vrBall1X + 12 >= vrRunnerX && vrBall1X - 12 <= vrRunnerX + VR_RUNNER_W && vrBall1Y + 12 >= vrRunnerY && vrBall1Y - 12 <= vrRunnerY + VR_RUNNER_H) {
		vrCoinScore += 5;
		vrBall1X = 900 + (rand() % 300);
		vrBall1Y = (rand() % 2 == 0) ? 220 : 285;
		if (vrCoinScore >= 150) {
			vrGameOver = true;
			vrGameWon = true;
		}
	}

	if (vrBall2X + 12 >= vrRunnerX && vrBall2X - 12 <= vrRunnerX + VR_RUNNER_W && vrBall2Y + 12 >= vrRunnerY && vrBall2Y - 12 <= vrRunnerY + VR_RUNNER_H) {
		vrCoinScore += 5;
		vrBall2X = 1000 + (rand() % 300);
		vrBall2Y = (rand() % 2 == 0) ? 220 : 285;
		if (vrCoinScore >= 150) {
			vrGameOver = true;
			vrGameWon = true;
		}
	}

	if (vrRedBallX + 12 >= vrRunnerX && vrRedBallX - 12 <= vrRunnerX + VR_RUNNER_W && vrRedBallY + 12 >= vrRunnerY && vrRedBallY - 12 <= vrRunnerY + VR_RUNNER_H) {
		vrCoinScore += 15;
		vrRedBallX = 1600 + (rand() % 500);
		vrRedBallY = (rand() % 2 == 0) ? 220 : 285;
		if (vrCoinScore >= 150) {
			vrGameOver = true;
			vrGameWon = true;
		}
	}

	if (vrRunnerX + VR_RUNNER_W - VR_RUNNER_HITBOX_INSET_X >= vrBoxX + VR_OBSTACLE_HITBOX_INSET &&
		vrRunnerX + VR_RUNNER_HITBOX_INSET_X <= vrBoxX + vrBoxWidth - VR_OBSTACLE_HITBOX_INSET &&
		vrRunnerY <= vrBoxY + vrBoxHeight - VR_RUNNER_HITBOX_INSET_Y) {
		vrGameOver = true;
		vrGameWon = false;
	}

	if (vrRunnerX + VR_RUNNER_W - VR_RUNNER_HITBOX_INSET_X >= vrRockX + VR_OBSTACLE_HITBOX_INSET &&
		vrRunnerX + VR_RUNNER_HITBOX_INSET_X <= vrRockX + 50 - VR_OBSTACLE_HITBOX_INSET &&
		vrRunnerY <= vrRockY + 38 - VR_RUNNER_HITBOX_INSET_Y) {
		vrGameOver = true;
		vrGameWon = false;
	}
}

void vrDraw() {
	if (!vrIsStarted) {
		iShowImage(0, 0, 800, 600, vrVault1Img);
		iShowImage(150, 20, 500, 200, vrNoteImg);
		iSetColor(0, 0, 0);
		iText(230, 65, "Click anywhere to disable the laser", GLUT_BITMAP_HELVETICA_18);
		iText(255, 50, "Click to Jump - Avoid the Boxes!", GLUT_BITMAP_HELVETICA_18);
		if (backImg > 0) iShowImage(50, 50, 80, 32, backImg);
		return;
	}

	if (vrGameOver && vrGameWon) {
		if (!vrShowVault3) {
			iShowImage(0, 0, 800, 600, vrVault2Img);
			iShowImage(200, 45, 390, 180, vrNoteImg);
			iSetColor(0, 0, 0);
			iText(220, 80, "Click anywhere to use the access card", GLUT_BITMAP_HELVETICA_18);
		}
		else {
			iShowImage(0, 0, 800, 600, vrVault3Img);

			if (!vrVault3TimerStarted) {
				vrVault3TimerStarted = true;
				vrVault3TimerStart = GetTickCount64();
			}
			else {
				double elapsedTime = (GetTickCount64() - vrVault3TimerStart) / 1000.0;
				if (elapsedTime >= 2.0) {
					vrVault3TimerStarted = false;
					gameState = GAMESTATE_VR_WIN_LOADING;
					loadingStep = 0;
					if (musicPlaying) {
						mciSendString(TEXT("pause bgm"), NULL, 0, NULL);
					}
				}
			}
		}
		if (backImg > 0) iShowImage(50, 50, 80, 32, backImg);
		return;
	}

	iShowImage(vrBgX1, 0, 800, 600, vrBgImage);
	iShowImage(vrBgX2, 0, 800, 600, vrBgImage);

	iSetColor(255, 215, 0);
	iFilledCircle(vrBall1X, vrBall1Y, 12);
	iSetColor(255, 255, 200);
	iFilledCircle(vrBall1X - 3, vrBall1Y + 3, 3);

	iSetColor(255, 215, 0);
	iFilledCircle(vrBall2X, vrBall2Y, 12);
	iSetColor(255, 255, 200);
	iFilledCircle(vrBall2X - 3, vrBall2Y + 3, 3);

	iSetColor(220, 20, 60);
	iFilledCircle(vrRedBallX, vrRedBallY, 12);
	iSetColor(255, 182, 193);
	iFilledCircle(vrRedBallX - 3, vrRedBallY + 3, 3);

	iShowImage(vrRunnerX, vrRunnerY, VR_RUNNER_W, VR_RUNNER_H, vrRunnerImg[vrCurrentFrame]);

	iShowImage(vrBoxX, vrBoxY, vrBoxWidth, vrBoxHeight, dodgeBoxImg);

	iSetColor(95, 85, 75);
	double vrRockPolyX[] = { (double)vrRockX, (double)vrRockX + 10, (double)vrRockX + 25, (double)vrRockX + 45, (double)vrRockX + 52, (double)vrRockX };
	double vrRockPolyY[] = { (double)vrRockY, (double)vrRockY + 22, (double)vrRockY + 38, (double)vrRockY + 28, (double)vrRockY, (double)vrRockY };
	iFilledPolygon(vrRockPolyX, vrRockPolyY, 6);

	iSetColor(130, 120, 110);
	iFilledCircle(vrRockX + 22, vrRockY + 22, 5);

	iShowImage(560, 535, 220, 45, trScoreImg);

	iSetColor(255, 215, 0);
	char vrScoreStr[50];
	sprintf(vrScoreStr, "%d", vrCoinScore);
	iText(700, 549, vrScoreStr, GLUT_BITMAP_HELVETICA_18);

	if (vrGameOver && !vrGameWon) {
		iShowImage(30, -15, 740, 300, vrNoteImg);

		iSetColor(0, 0, 0);
		iText(340, 55, "GAME OVER", GLUT_BITMAP_TIMES_ROMAN_24);

		iSetColor(0, 0, 0);
		iText(305, 30, "CLICK TO RETRY", GLUT_BITMAP_HELVETICA_18);
	}

	if (backImg > 0) iShowImage(50, 50, 80, 32, backImg);
}

void vrHandleMouseDown(int mx, int my) {
	if (!vrIsStarted) {
		vrIsStarted = true;
		return;
	}
	if (vrGameOver) {
		if (vrGameWon) {
			if (!vrShowVault3) {
				vrShowVault3 = true;
				return;
			}
			return;
		}
		else {
			vrGameOver = false;
			vrGameWon = false;
			vrShowVault3 = false;
			vrBoxX = 800;
			vrRockX = 1100;
			vrDistance = 0;
			vrDistCounter = 0;
			vrCoinScore = 0;
			vrRunnerY = 200;
			vrIsJumping = false;
			vrJumpCount = 0;
			vrIsMouseHeld = false;
			vrFallCounter = 0;
			vrGameSpeed = 4;
			vrBgX1 = 0;
			vrBgX2 = 800;
			vrBall1X = 700; vrBall1Y = 220;
			vrBall2X = 1100; vrBall2Y = 285;
			vrRedBallX = 1500;
		}
	}
	else {
		vrIsMouseHeld = true;
		if (!vrIsJumping) {
			vrIsJumping = true;
			vrJumpCount = 1;
			vrRunnerDy = 22;
			vrFallCounter = 0;
		}
		else if (vrJumpCount == 1) {
			vrJumpCount = 2;
			vrRunnerDy = 20;
			vrFallCounter = 0;
		}
	}
}

void usbGenerateBoard() {
	for (int r = 0; r < USB_GRID_SIZE; r++) {
		for (int c = 0; c < USB_GRID_SIZE; c++) {
			usbGrid[r][c] = (rand() % 5) + 1;
		}
	}
	while (usbCheckMatchesExist()) {
		usbGenerateBoard();
	}
}

int usbCheckMatchesExist() {
	for (int r = 0; r < USB_GRID_SIZE; r++) {
		for (int c = 0; c < USB_GRID_SIZE - 2; c++) {
			if (usbGrid[r][c] != 0 && usbGrid[r][c] == usbGrid[r][c + 1] && usbGrid[r][c] == usbGrid[r][c + 2])
				return 1;
		}
	}
	for (int c = 0; c < USB_GRID_SIZE; c++) {
		for (int r = 0; r < USB_GRID_SIZE - 2; r++) {
			if (usbGrid[r][c] != 0 && usbGrid[r][c] == usbGrid[r + 1][c] && usbGrid[r][c] == usbGrid[r + 2][c])
				return 1;
		}
	}
	return 0;
}

void usbApplyGravity() {
	for (int c = 0; c < USB_GRID_SIZE; c++) {
		int writeRow = 0;
		for (int r = 0; r < USB_GRID_SIZE; r++) {
			if (usbGrid[r][c] != 0) {
				usbGrid[writeRow][c] = usbGrid[r][c];
				if (writeRow != r) {
					usbGrid[r][c] = 0;
				}
				writeRow++;
			}
		}
	}
}

void usbRefillBoard() {
	for (int r = 0; r < USB_GRID_SIZE; r++) {
		for (int c = 0; c < USB_GRID_SIZE; c++) {
			if (usbGrid[r][c] == 0) {
				usbGrid[r][c] = (rand() % 5) + 1;
			}
		}
	}
}

void usbResolveBoard() {
	int matched[USB_GRID_SIZE][USB_GRID_SIZE] = { 0 };

	for (int r = 0; r < USB_GRID_SIZE; r++) {
		for (int c = 0; c < USB_GRID_SIZE - 2; c++) {
			if (usbGrid[r][c] != 0 && usbGrid[r][c] == usbGrid[r][c + 1] && usbGrid[r][c] == usbGrid[r][c + 2]) {
				matched[r][c] = matched[r][c + 1] = matched[r][c + 2] = 1;
			}
		}
	}
	for (int c = 0; c < USB_GRID_SIZE; c++) {
		for (int r = 0; r < USB_GRID_SIZE - 2; r++) {
			if (usbGrid[r][c] != 0 && usbGrid[r][c] == usbGrid[r + 1][c] && usbGrid[r][c] == usbGrid[r + 2][c]) {
				matched[r][c] = matched[r + 1][c] = matched[r + 2][c] = 1;
			}
		}
	}

	for (int r = 0; r < USB_GRID_SIZE; r++) {
		for (int c = 0; c < USB_GRID_SIZE; c++) {
			if (matched[r][c]) {
				usbGrid[r][c] = 0;
				usbScore += 1;
			}
		}
	}

	usbApplyGravity();
	usbRefillBoard();

	if (usbCheckMatchesExist()) {
		usbResolveBoard();
	}
}

void usbInitGame() {
	usbSubState = 0;
	usbScore = 0;
	usbMovesLeft = 30;
	usbSelectedRow = -1;
	usbSelectedCol = -1;
	usbCurrentFrame = 0;
	usbCharX = -50.0f;
	usbCharY = 150.0f;
	usbCompletionTimerStarted = false;
	usbGenerateBoard();
}

void usbAnimateCharacter() {
	if (isGamePaused) return;
	if (gameState == 400 && usbSubState == 2) {
		usbCharX += 4.0f;
		if (usbCharX > 480.0f) {
			usbCharX = 480.0f;
			usbCurrentFrame = 0;
		}
		else {
			usbCurrentFrame = (usbCurrentFrame + 1) % 4;
		}
	}
}

void usbDrawGame() {
	if (usbImgBg > 0) {
		iShowImage(0, 0, 800, 600, usbImgBg);
	}
	else {
		iShowImage(0, 0, 800, 600, level2Bg);
	}

	if (usbSubState == 0) {
		int noteW = 500, noteH = 250;
		int noteX = (800 - noteW) / 2;
		int noteY = 20;

		if (imgnote > 0) iShowImage(noteX, noteY, noteW, noteH, imgnote);

		iSetColor(0, 0, 0);
		iText(noteX + 55, noteY + 63, "Play this match-3 game to get the USB!", GLUT_BITMAP_HELVETICA_18);
		iText(noteX + 45, noteY + 40, "Click anywhere or press ENTER to Start", GLUT_BITMAP_HELVETICA_18);
	}
	else if (usbSubState == 1) {
		iSetColor(30, 30, 40);
		iFilledRectangle(USB_BOARD_X - 10, USB_BOARD_Y - 10, USB_GRID_SIZE * USB_TILE_SIZE + 20, USB_GRID_SIZE * USB_TILE_SIZE + 20);

		for (int r = 0; r < USB_GRID_SIZE; r++) {
			for (int c = 0; c < USB_GRID_SIZE; c++) {
				int px = USB_BOARD_X + c * USB_TILE_SIZE;
				int py = USB_BOARD_Y + r * USB_TILE_SIZE;

				if (usbSelectedRow == r && usbSelectedCol == c) {
					iSetColor(255, 215, 0);
				}
				else {
					iSetColor(50, 50, 70);
				}
				iFilledRectangle(px + 2, py + 2, USB_TILE_SIZE - 4, USB_TILE_SIZE - 4);

				int imgToDraw = -1;
				if (usbGrid[r][c] == 1) imgToDraw = usbImgKey;
				else if (usbGrid[r][c] == 2) imgToDraw = usbImgHandcuff;
				else if (usbGrid[r][c] == 3) imgToDraw = usbImgTorch;
				else if (usbGrid[r][c] == 4) imgToDraw = usbImgCamera;
				else if (usbGrid[r][c] == 5) imgToDraw = usbImgStair;

				if (usbGrid[r][c] != 0 && imgToDraw > 0) {
					iShowImage(px + 5, py + 5, USB_TILE_SIZE - 10, USB_TILE_SIZE - 10, imgToDraw);
				}
			}
		}

		iShowImage(100, 530, 240, 65, imgS1);
		iShowImage(460, 530, 240, 65, imgM1);

		char scoreStr[20], movesStr[20];
		sprintf_s(scoreStr, sizeof(scoreStr), "%d / 150", usbScore);
		sprintf_s(movesStr, sizeof(movesStr), "%d", usbMovesLeft);

		iSetColor(255, 255, 255);
		iText(210, 560, scoreStr, GLUT_BITMAP_HELVETICA_18);
		iText(585, 560, movesStr, GLUT_BITMAP_HELVETICA_18);
	}
	else if (usbSubState == 2) {
		if (usbImgUsbIcon > 0) iShowImage(325, 225, 150, 150, usbImgUsbIcon);

		int noteW = 500, noteH = 250;
		int noteX = (800 - noteW) / 2;
		int noteY = 20;

		if (imgnote > 0) iShowImage(noteX, noteY, noteW, noteH, imgnote);

		iSetColor(0, 0, 0);
		iText(noteX + 125, noteY + 63, "SECURITY BYPASSED!", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(noteX + 105, noteY + 40, "Character acquired the USB!", GLUT_BITMAP_HELVETICA_18);

		if (!usbCompletionTimerStarted) {
			usbCompletionTimerStarted = true;
			usbCompletionTimerStart = GetTickCount64();
		}
		else {
			double elapsedTime = (GetTickCount64() - usbCompletionTimerStart) / 1000.0;
			if (elapsedTime >= 3.0) {
				usbCompletionTimerStarted = false;
				gameState = GAMESTATE_LEVEL2_MAP;
			}
		}
	}
	else if (usbSubState == 3) {
		int noteW = 500, noteH = 250;
		int noteX = (800 - noteW) / 2;
		int noteY = 20;

		if (imgnote > 0) iShowImage(noteX, noteY, noteW, noteH, imgnote);

		iSetColor(0, 0, 0);
		iText(noteX + 110, noteY + 63, "LOCKDOWN TRIGGERED!", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(noteX + 165, noteY + 40, "Press R to Retry", GLUT_BITMAP_HELVETICA_18);
	}

	iShowImage(50, 50, 80, 32, backImg);
}

void usbHandleMouseClick(int mx, int my) {
	if (usbSubState == 0) {
		usbSubState = 1;
		return;
	}

	if (usbSubState == 2 || usbSubState == 3) return;

	if (mx >= USB_BOARD_X && mx < USB_BOARD_X + USB_GRID_SIZE * USB_TILE_SIZE &&
		my >= USB_BOARD_Y && my < USB_BOARD_Y + USB_GRID_SIZE * USB_TILE_SIZE) {

		int c = (mx - USB_BOARD_X) / USB_TILE_SIZE;
		int r = (my - USB_BOARD_Y) / USB_TILE_SIZE;

		if (usbSelectedRow == -1 && usbSelectedCol == -1) {
			usbSelectedRow = r;
			usbSelectedCol = c;
		}
		else {
			if (abs(usbSelectedRow - r) + abs(usbSelectedCol - c) == 1) {
				int temp = usbGrid[usbSelectedRow][usbSelectedCol];
				usbGrid[usbSelectedRow][usbSelectedCol] = usbGrid[r][c];
				usbGrid[r][c] = temp;

				if (usbCheckMatchesExist()) {
					usbMovesLeft--;
					usbResolveBoard();

					if (usbScore >= 150) {
						usbSubState = 2;
					}
					else if (usbMovesLeft <= 0) {
						usbSubState = 3;
					}
				}
				else {
					temp = usbGrid[usbSelectedRow][usbSelectedCol];
					usbGrid[usbSelectedRow][usbSelectedCol] = usbGrid[r][c];
					usbGrid[r][c] = temp;
				}
			}
			usbSelectedRow = -1;
			usbSelectedCol = -1;
		}
	}
}

void usbHandleKeyboard(unsigned char key) {
	if (usbSubState == 0) {
		if (key == '\r' || key == ' ') {
			usbSubState = 1;
		}
		return;
	}

	if (key == 'r' || key == 'R') {
		usbInitGame();
		usbSubState = 1;
	}
}