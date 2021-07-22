#include "Suitcase.h"
#include <conio.h>
#include <iostream>
#include <Windows.h>
#include <ctime>

#define COLOR_BLACK RGB(0, 0, 0)
#define COLOR_WHITE RGB(255, 255, 255)
#define COLOR_RED RGB(255, 0, 0)
#define COLOR_YELLOW RGB(255, 255, 0)
#define COLOR_GREEN RGB(0, 255, 0)
#define COLOR_BLUE RGB(0, 0, 255)
#define COLOR_VIOLET RGB(128, 0, 128)
#define COLOR_CONSOLE RGB(12, 12, 12)

#define KEY_PRESSED(vk_code) ((GetAsyncKeyState(vk_code) & 0x01) ? 1 : 0)

HDC hdc;
int init_x, init_y;

bool PowerUpCollision(Suitcase* _Suitcase, PowerUp* _PowerUp, int _x, int _y);

int main()
{
	srand(time(0));
	init_x = 200;
	init_y = 200;
	COLORREF init_color = COLOR_RED;
	int init_step = 11;
	int init_size = 5;

	POINT Cursor;
	HWND hwnd = GetConsoleWindow();

	if (hwnd != NULL)
	{
		hdc = GetWindowDC(hwnd);

		if (hdc != 0)
		{
			Suitcase* SuitcaseBuf[4];
			Suitcase* pSuitcase;

			Suitcase testSuitcase0(init_x, init_y, init_size);
			SuitcaseNoLocks testSuitcase1(init_x, init_y, init_size);
			SuitcaseNoSmiley testSuitcase2(init_x, init_y, init_size);
			SuitcaseNoSmileyLocks testSuitcase3(init_x, init_y, init_size);

			SuitcaseBuf[0] = &testSuitcase0;
			SuitcaseBuf[1] = &testSuitcase1;
			SuitcaseBuf[2] = &testSuitcase2;
			SuitcaseBuf[3] = &testSuitcase3;

			pSuitcase = SuitcaseBuf[0];
			int pType = 0;

			PowerUp* testPowerUp0 = new PowerUp0(init_x, init_y + 300, 3);
			PowerUp* testPowerUp1 = new PowerUp1(init_x + 200, init_y + 300, 3);
			PowerUp* testPowerUp2 = new PowerUp2(init_x + 400, init_y + 300, 3);
			PowerUp* testPowerUp3 = new PowerUp3(init_x + 600, init_y + 300, 3);
			PowerUp* testPowerUp4 = new PowerUp4(init_x + 800, init_y + 150, 3);
			PowerUp* testPowerUp5 = new PowerUp5(init_x + 800, init_y - 50, 3);

			pSuitcase->SetBodyColor(COLOR_YELLOW);
			pSuitcase->SetHandleColor(COLOR_BLUE);
			pSuitcase->SetVisibility(true);
			pSuitcase->SetStep(5);

			while (1)
			{
				pSuitcase->Drag();

				if (KEY_PRESSED(VK_UP))
				{
					init_size = pSuitcase->GetSize();
					pSuitcase->SetSize(init_size + 1);
				}
				if (KEY_PRESSED(VK_DOWN))
				{
					init_size = pSuitcase->GetSize();
					if (init_size > 1)
						pSuitcase->SetSize(init_size - 1);
				}
				if (KEY_PRESSED(VK_LEFT))
				{
					pSuitcase->SetBodyColor(RGB(rand() % 255, rand() % 255, rand() % 255));
				}
				if (KEY_PRESSED(VK_RIGHT))
				{
					pSuitcase->SetHandleColor(RGB(rand() % 255, rand() % 255, rand() % 255));
				}
				if (KEY_PRESSED(VK_ESCAPE))
				{
					break;
				}
				if (KEY_PRESSED(VK_SPACE))
				{
					pSuitcase->SetVisibility(pSuitcase->GetVisibility() == true ? false : true);
				}

				//PowerUpCollision(pSuitcase, testPowerUp0, init_x, init_y);
				//PowerUpCollision(pSuitcase, testPowerUp1, init_x, init_y);
				//PowerUpCollision(pSuitcase, testPowerUp2, init_x, init_y);
				//PowerUpCollision(pSuitcase, testPowerUp3, init_x, init_y);

				testPowerUp0->CheckCollision(&pSuitcase);
				testPowerUp1->CheckCollision(&pSuitcase);
				testPowerUp2->CheckCollision(&pSuitcase);
				testPowerUp3->CheckCollision(&pSuitcase);

				testPowerUp4->CheckCollision(&pSuitcase);

				if (testPowerUp5->CheckCollision(&pSuitcase) == true)
				{
					int xSuitcase = pSuitcase->GetX();
					int ySuitcase = pSuitcase->GetY();
					int SizeSuitcase = pSuitcase->GetSize();
					int StepSuitcase = pSuitcase->GetStep();
					bool VisibleSuitcase = pSuitcase->GetVisibility();
					COLORREF HandleColorSuitcase = pSuitcase->GetHandleColor();
					COLORREF BodyColorSuitcase = pSuitcase->GetBodyColor();

					switch (pType)
					{
					case 0:
						pType = 1;
						break;
					case 1:
						pType = 0;
						break;
					case 2:
						pType = 3;
						break;
					case 3:
						pType = 2;
						break;
					default:
						break;
					}

					pSuitcase = SuitcaseBuf[pType];

					pSuitcase->SetX(xSuitcase);
					pSuitcase->SetY(ySuitcase);
					pSuitcase->SetSize(SizeSuitcase);
					pSuitcase->SetStep(StepSuitcase);
					pSuitcase->SetVisibility(VisibleSuitcase);
					pSuitcase->SetHandleColor(HandleColorSuitcase);
					pSuitcase->SetBodyColor(BodyColorSuitcase);
				}
				
				testPowerUp0->Show();
				testPowerUp1->Show();
				testPowerUp2->Show();
				testPowerUp3->Show();
				testPowerUp4->Show();
				testPowerUp5->Show();
				pSuitcase->Show();

				Sleep(15);

				pSuitcase->Hide();
				testPowerUp0->Hide();
				testPowerUp1->Hide();
				testPowerUp2->Hide();
				testPowerUp3->Hide();
				testPowerUp4->Hide();
				testPowerUp5->Hide();
			} 
		}//if
	}//if
}//main

bool PowerUpCollision(Suitcase* _Suitcase, PowerUp* _PowerUp, int _x, int _y)
{
	if (_Suitcase->GetVisibility() == false) return false;
	bool doIntersect = false;
	int SizeSuitcase = _Suitcase->GetSize();
	int SizePowerUp = _PowerUp->GetSize();
	int TypePowerUp = _PowerUp->GetType();

	// Suitcase
	/*
	Rectangle(hdc, x, y - 2 * size, x + 20 * size, y + 10 * size);
	*/

	// PowerUp
	/*
	Rectangle(hdc, x - 10 * size, y - 10 * size, x + 10 * size, y + 10 * size);
	*/

	// Intersection
	/*
	A - Suitcase
	A.X1 = xSuitcase
	A.X2 = xSuitcase + 20 * SizeSuitcase
	A.Y1 = ySuitcase - 2 * SizeSuitcase
	A.Y2 = ySuitcase + 10 * SizeSuitcase

	B - PowerUp
	B.X1 = xPowerUp - 10 * SizePowerUp
	B.X2 = xPowerUp + 10 * SizePowerUp
	B.Y1 = yPowerUp - 10 * SizePowerUp
	B.Y2 = yPowerUp + 10 * SizePowerUp

	c1 = A.X1 < B.X2
	c2 = A.X2 > B.X1
	c3 = A.Y1 < B.Y2
	c4 = A.Y2 > B.Y1

	if (c1 && c2 && c3 && c4) => Rectangles intersect (true)
	*/

	int xSuitcase = _Suitcase->GetX();
	int ySuitcase = _Suitcase->GetY();

	int xPowerUp = _PowerUp->GetX();
	int yPowerUp = _PowerUp->GetY();

	bool c1 = (xSuitcase) < (xPowerUp + 10 * SizePowerUp);
	bool c2 = (xSuitcase + 20 * SizeSuitcase) > (xPowerUp - 10 * SizePowerUp);
	bool c3 = (ySuitcase - 2 * SizeSuitcase) < (yPowerUp + 10 * SizePowerUp);
	bool c4 = (ySuitcase + 10 * SizeSuitcase) > (yPowerUp - 10 * SizePowerUp);

	if (c1 && c2 && c3 && c4) doIntersect = true;

	if (doIntersect)
	{
		_Suitcase->Hide();
		_Suitcase->SetX(_x);
		_Suitcase->SetY(_y);

		Suitcase* PowerUpSuitcase = new SuitcaseRedLocks(_x, _y, SizeSuitcase + 2);
		PowerUpSuitcase->SetVisibility(true);
		
		if (TypePowerUp == 0)
		{
			PowerUpSuitcase->SetBodyColor(COLOR_WHITE);
			PowerUpSuitcase->SetHandleColor(COLOR_WHITE);

			_Suitcase->SetHandleColor(RGB(rand() % 255, rand() % 255, rand() % 255));
			_Suitcase->SetBodyColor(RGB(rand() % 255, rand() % 255, rand() % 255));
		}
		else if (TypePowerUp == 1)
		{
			PowerUpSuitcase->SetBodyColor(COLOR_RED);
			PowerUpSuitcase->SetHandleColor(COLOR_RED);

			int StepSuitcase = _Suitcase->GetStep();
			if (StepSuitcase > 10) StepSuitcase -= 10;
			else StepSuitcase = 1;
			_Suitcase->SetStep(StepSuitcase);
		}
		else if (TypePowerUp == 2)
		{
			PowerUpSuitcase->SetBodyColor(COLOR_GREEN);
			PowerUpSuitcase->SetHandleColor(COLOR_GREEN);

			int StepSuitcase = _Suitcase->GetStep();
			if (StepSuitcase < 51) StepSuitcase += 5;
			_Suitcase->SetStep(StepSuitcase);
		}
		else if (TypePowerUp == 3)
		{
			PowerUpSuitcase->SetBodyColor(COLOR_YELLOW);
			PowerUpSuitcase->SetHandleColor(COLOR_YELLOW);

			if (SizeSuitcase < 20) _Suitcase->SetSize(SizeSuitcase + 5);
			else _Suitcase->SetSize(5);
		}
		else if (TypePowerUp == 4)
		{
			PowerUpSuitcase->SetBodyColor(COLOR_BLUE);
			PowerUpSuitcase->SetHandleColor(COLOR_BLUE);
		}
		else if (TypePowerUp == 5)
		{
			PowerUpSuitcase->SetBodyColor(COLOR_VIOLET);
			PowerUpSuitcase->SetHandleColor(COLOR_VIOLET);
		}

		for (int i = 0; i < 2; i++)
		{
			PowerUpSuitcase->Show();
			Sleep(400);
			PowerUpSuitcase->Hide();
			Sleep(400);
		}

		delete PowerUpSuitcase;

		_Suitcase->Show();
	}

	return doIntersect;
}
