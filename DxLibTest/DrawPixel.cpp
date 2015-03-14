#include "DxLib.h"
#include <math.h>

int WINAPI WinMain(HINSTANCE hInstans, HINSTANCE hPrevInstans, LPSTR lpCmdLine, int nCmdShow)
{
	// 画面モードの設定
	ChangeWindowMode(TRUE);
	SetGraphMode(640, 480, 16);

	if (DxLib_Init() == -1){
		return -1;
	}

	LoadGraphScreen(0, 0, "ball.png", TRUE);
	LoadGraphScreen(50,0, "wall.png", TRUE);

	SetDrawScreen(DX_SCREEN_BACK);

	int BallGHandle = LoadGraph("ball.png");
	int WallGHandle = LoadGraph("wall.png");

	//getGraphicSize
	int BallGSizeX;
	int BallGSizeY;
	GetGraphSize(BallGHandle, &BallGSizeX, &BallGSizeY);

	//getGraphicSize
	int WallGSizeX;
	int WallGSizeY;
	GetGraphSize(WallGHandle, &WallGSizeX, &WallGSizeY);

	//BallPosition
	int BallX = 100;
	int BallY = 50;
	//BallSpeed
	int BallVX = 10;
	int BallVY = 5;

	//ボールの中心
	double BallCenterX;
	double BallCenterY;

	int WallX = 300;
	int WallY = 200;

	//ブロックの中心
	double WallCenterX;
	double WallCenterY;

	//MainLoop
	while (ProcessMessage() == 0 && CheckHitKeyAll() == 0)
	{
		ClearDrawScreen();

		//ボールと枠の衝突判定(速度にマイナス1をかけることで向きを逆にする)
		//この場合ボールはX座標100～500,Y座標50～400の範囲を移動することになります。
		if (BallX + BallGSizeX >= 500)	BallVX *= -1;
		if (BallX <= 90)	BallVX *= -1;
		if (BallY + BallGSizeY >= 400)	BallVY *= -1;
		if (BallY <= 40)	BallVY *= -1;

		//calcCenterPositionOfBall&Wall
		BallCenterX = BallX + BallGSizeX / 2;
		BallCenterY = BallY + BallGSizeY / 2;

		WallCenterX = WallX + WallGSizeX / 2;
		WallCenterY = WallY + WallGSizeY / 2;

		if (abs(BallCenterX - WallCenterX) <= (BallGSizeX+WallGSizeX)/2)
		{
			//fromUnder
			if ((BallY - BallVY >= WallY + WallGSizeY)&&(BallY <= WallY+WallGSizeY))
			{
				BallVY *= -1;
				BallY = (WallY + WallGSizeY) * 2 - BallY;
			}
			//fromUP
			if ((BallY-BallVY + BallGSizeY <= WallY)&&(BallY + BallGSizeY >= WallY))
			{
				BallVY *= -1;
				BallY = (WallY - BallGSizeY) * 2 - BallY;
			}
			//piledUpToSide
			if (abs(BallCenterY - WallCenterY) <= (BallGSizeY + WallGSizeY)/2)
			{
				//fromLeft
				if ((BallX - BallVX >= WallX + WallGSizeX) && (BallX <= WallX + WallGSizeX))
				{
					BallVX *= -1;
					BallX = (WallX + WallGSizeX) * 2 - BallX;
				}
				//fromRight
				if ((BallX - BallVX + BallGSizeX <= WallX) && (BallX <= BallX+BallGSizeX >= WallX))
				{
					BallVX *= -1;
					BallX = (WallX - BallGSizeX) * 2 - BallX;
				}

			}
		}

		// ボールを移動させる(＝表示させる座標を変更する)
		DrawGraph(BallX, BallY, BallGHandle, TRUE);
		DrawGraph(WallX, WallY, WallGHandle, TRUE);

		BallX += BallVX;
		BallY += BallVY;

		ScreenFlip();

		WaitTimer(20);
	}

	WaitKey();

	DxLib_End();

	return 0;

}
