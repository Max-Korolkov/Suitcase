#include "Suitcase.h"
#include <Windows.h>

extern HDC hdc;
extern int init_x;
extern int init_y;

#define COLOR_BLACK RGB(0, 0, 0)
#define COLOR_WHITE RGB(255, 255, 255)
#define COLOR_RED RGB(255, 0, 0)
#define COLOR_YELLOW RGB(255, 255, 0)
#define COLOR_GREEN RGB(0, 255, 0)
#define COLOR_BLUE RGB(0, 0, 255)
#define COLOR_VIOLET RGB(128, 0, 128)
#define COLOR_BROWN RGB(134, 89, 55)
#define COLOR_GOLD RGB(204, 164, 61)
#define COLOR_CONSOLE RGB(12, 12, 12)

#define KEY_PRESSED(vk_code) ((GetAsyncKeyState(vk_code) & 0x01) ? 1 : 0)

Coordinates::Coordinates()
{
	x = 0;
	y = 0;
}

Coordinates::Coordinates(int _x, int _y)
{
	x = _x;
	y = _y;
}

Coordinates::~Coordinates(void)
{
}

int Coordinates::GetX()
{
	return x;
}

int Coordinates::GetY()
{
	return y;
}

void Coordinates::SetX(int _x)
{
	x = _x;
}

void Coordinates::SetY(int _y)
{
	y = _y;
}

Point::Point() : Coordinates()
{
	isVisible = false;
	color = COLOR_WHITE;
	step = 5;
}

Point::Point(int _x, int _y, COLORREF _color) : Coordinates(_x, _y)
{
	isVisible = false;
	color = _color;
	step = 5;
}

Point::~Point(void)
{
}

COLORREF Point::GetColor()
{
	return color;
}

int Point::GetStep()
{
	return step;
}

bool Point::GetVisibility()
{
	return isVisible;
}

void Point::Show()
{
	isVisible = true;
	SetPixel(hdc, x, y, color);
}

void Point::Hide()
{
	isVisible = false;
	SetPixel(hdc, x, y, COLOR_CONSOLE);
}

void Point::SetColor(COLORREF _color)
{
	color = _color;
}

void Point::SetStep(int _step)
{
	step = _step;
}

void Point::SetVisibility(bool _isVisible)
{
	isVisible = _isVisible;
}

void Point::Drag()
{
	if (isVisible == false) return;
	// up
	if (KEY_PRESSED(0x57) == 1)
	{
		y = y - step;
	}

	// down
	if (KEY_PRESSED(0x53) == 1)
	{
		y = y + step;
	}
	// right
	if (KEY_PRESSED(0x44) == 1)
	{
		x = x + step;
	}

	// left
	if (KEY_PRESSED(0x41) == 1)
	{
		x = x - step;
	}
}

Suitcase::Suitcase()
{
	size = 0;
	color_body = COLOR_WHITE;
	color_handle = COLOR_WHITE;
}

Suitcase::Suitcase(int _x, int _y, int _size) : Point(_x, _y, COLOR_WHITE)
{
	x = _x;
	y = _y;
	size = _size;
	color_body = COLOR_WHITE;
	color_handle = COLOR_WHITE;
}

Suitcase::~Suitcase()
{
}

int Suitcase::GetSize()
{
	return size;
}

COLORREF Suitcase::GetHandleColor()
{
	return color_handle;
}

COLORREF Suitcase::GetBodyColor()
{
	return color_body;
}

void Suitcase::DrawSmiley()
{
	int xC = x + 10 * size;
	int yC = y + 5 * size;
	int sizeC = (size < 4) ? 1 : (size / 2);

	HPEN Pen = CreatePen(PS_SOLID, sizeC, COLOR_BLACK);
	SelectObject(hdc, Pen);
	HBRUSH Brush = CreateSolidBrush(COLOR_YELLOW);
	SelectObject(hdc, Brush);
	Ellipse(hdc, xC - 7 * sizeC, yC - 7 * sizeC, xC + 7 * sizeC, yC + 7 * sizeC);

	DeleteObject(Pen);
	DeleteObject(Brush);

	Pen = CreatePen(PS_SOLID, 1, COLOR_BLACK);
	SelectObject(hdc, Pen);
	Brush = CreateSolidBrush(COLOR_BLACK);
	SelectObject(hdc, Brush);

	Ellipse(hdc, xC - 3 * sizeC, yC - 3 * sizeC, xC - 1 * sizeC, yC - 1 * sizeC);
	Ellipse(hdc, xC + 1 * sizeC, yC - 3 * sizeC, xC + 3 * sizeC, yC - 1 * sizeC);
	Ellipse(hdc, xC - 4 * sizeC, yC + 0 * sizeC, xC + 4 * sizeC, yC + 5 * sizeC);

	DeleteObject(Pen);
	DeleteObject(Brush);

	Pen = CreatePen(PS_SOLID, 1, COLOR_YELLOW);
	SelectObject(hdc, Pen);
	Brush = CreateSolidBrush(COLOR_YELLOW);
	SelectObject(hdc, Brush);

	Rectangle(hdc, xC - 4 * sizeC, yC + 0 * sizeC, xC + 4 * sizeC, yC + 2 * sizeC);

	DeleteObject(Pen);
	DeleteObject(Brush);
}

void Suitcase::DrawLocks()
{
	HPEN Pen = CreatePen(PS_SOLID, 1, COLOR_BLACK);
	SelectObject(hdc, Pen);
	HBRUSH Brush = CreateSolidBrush(color_handle);
	SelectObject(hdc, Brush);

	Rectangle(hdc, x + 2 * size, y + 0 * size, x + 4 * size, y + 4 * size);
	Rectangle(hdc, x + 16 * size, y + 0 * size, x + 18 * size, y + 4 * size);

	DeleteObject(Pen);
	DeleteObject(Brush);

	Pen = CreatePen(PS_SOLID, 1, COLOR_BLACK);
	SelectObject(hdc, Pen);
	Brush = CreateSolidBrush(COLOR_GOLD);
	SelectObject(hdc, Brush);

	Rectangle(hdc, x + 2 * size, y + 3 * size, x + 4 * size, y + 4 * size);
	Rectangle(hdc, x + 16 * size, y + 3 * size, x + 18 * size, y + 4 * size);

	DeleteObject(Pen);
	DeleteObject(Brush);

	return;
}

void Suitcase::DrawHandle()
{
	HPEN Pen = CreatePen(PS_SOLID, 1, COLOR_WHITE);
	SelectObject(hdc, Pen);
	HBRUSH Brush;

	Brush = CreateSolidBrush(color_handle);
	SelectObject(hdc, Brush);
	Rectangle(hdc, x + 7 * size, y - 2 * size, x + 8 * size, y);
	Rectangle(hdc, x + 12 * size, y - 2 * size, x + 13 * size, y);
	Rectangle(hdc, x + 7 * size, y - 2 * size, x + 13 * size, y - 1 * size);

	DeleteObject(Pen);
	DeleteObject(Brush);
}

void Suitcase::DrawBody()
{
	HPEN Pen = CreatePen(PS_SOLID, 1, COLOR_WHITE);
	SelectObject(hdc, Pen);
	HBRUSH Brush;

	Brush = CreateSolidBrush(color_body);
	SelectObject(hdc, Brush);
	Rectangle(hdc, x, y, x + 20 * size, y + 10 * size);

	DeleteObject(Pen);
	DeleteObject(Brush);
}

void Suitcase::Show()
{
	if (isVisible == false) return;

	DrawBody();
	DrawHandle();
	DrawSmiley();
	DrawLocks();
}

void Suitcase::Hide()
{
	HPEN Pen = CreatePen(PS_SOLID, 1, COLOR_CONSOLE);
	SelectObject(hdc, Pen);
	HBRUSH Brush;

	Brush = CreateSolidBrush(COLOR_CONSOLE);
	SelectObject(hdc, Brush);
	Rectangle(hdc, x, y - 2 * size, x + 20 * size, y + 10 * size);

	DeleteObject(Pen);
	DeleteObject(Brush);
}

void Suitcase::SetHandleColor(COLORREF _color_handle)
{
	color_handle = _color_handle;
}

void Suitcase::SetBodyColor(COLORREF _color_body)
{
	color_body = _color_body;
}

void Suitcase::SetSize(int _size)
{
	size = _size;
}

SuitcaseNoLocks::SuitcaseNoLocks() : Suitcase()
{

}

SuitcaseNoLocks::SuitcaseNoLocks(int _x, int _y, int _size) : Suitcase(_x, _y, _size)
{
	x = _x;
	y = _y;
	size = _size;
}

SuitcaseNoLocks::~SuitcaseNoLocks() 
{

}

void SuitcaseNoLocks::DrawLocks() 
{

}

SuitcaseNoSmiley::SuitcaseNoSmiley() : Suitcase()
{

}

SuitcaseNoSmiley::SuitcaseNoSmiley(int _x, int _y, int _size) : Suitcase(_x, _y, _size)
{
	x = _x;
	y = _y;
	size = _size;
}

SuitcaseNoSmiley::~SuitcaseNoSmiley()
{

}

void SuitcaseNoSmiley::DrawSmiley()
{

}

SuitcaseNoSmileyLocks::SuitcaseNoSmileyLocks() : Suitcase()
{

}

SuitcaseNoSmileyLocks::SuitcaseNoSmileyLocks(int _x, int _y, int _size) : Suitcase(_x, _y, _size)
{
	x = _x;
	y = _y;
	size = _size;
}

SuitcaseNoSmileyLocks::~SuitcaseNoSmileyLocks()
{

}

void SuitcaseNoSmileyLocks::DrawLocks()
{

}

void SuitcaseNoSmileyLocks::DrawSmiley()
{

}

SuitcaseRedLocks::SuitcaseRedLocks() : SuitcaseNoSmiley()
{

}

SuitcaseRedLocks::SuitcaseRedLocks(int _x, int _y, int _size) : SuitcaseNoSmiley(_x, _y, _size)
{
	x = _x;
	y = _y;
	size = _size;
}

SuitcaseRedLocks::~SuitcaseRedLocks()
{

}

void SuitcaseRedLocks::DrawLocks()
{
	HPEN Pen = CreatePen(PS_SOLID, 1, COLOR_BLACK);
	SelectObject(hdc, Pen);
	HBRUSH Brush = CreateSolidBrush(COLOR_RED);
	SelectObject(hdc, Brush);

	Rectangle(hdc, x + 2 * size, y + 0 * size, x + 4 * size, y + 4 * size);
	Rectangle(hdc, x + 16 * size, y + 0 * size, x + 18 * size, y + 4 * size);

	DeleteObject(Pen);
	DeleteObject(Brush);

	Pen = CreatePen(PS_SOLID, 1, COLOR_BLACK);
	SelectObject(hdc, Pen);
	Brush = CreateSolidBrush(COLOR_GOLD);
	SelectObject(hdc, Brush);

	Rectangle(hdc, x + 2 * size, y + 3 * size, x + 4 * size, y + 4 * size);
	Rectangle(hdc, x + 16 * size, y + 3 * size, x + 18 * size, y + 4 * size);

	DeleteObject(Pen);
	DeleteObject(Brush);

	return;
}

PowerUp::PowerUp()
{
	size = 0;
}

PowerUp::PowerUp(int _x, int _y, int _size) : Point(_x, _y, COLOR_WHITE)
{
	x = _x;
	y = _y;
	size = _size;
}

int PowerUp::GetSize()
{
	return size;
}

bool PowerUp::CheckCollision(Suitcase** _Suitcase)
{
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

	if ((*_Suitcase)->GetVisibility() == false) return false;
	bool doIntersect = false;
	int SizeSuitcase = (*_Suitcase)->GetSize();
	int SizePowerUp = size;

	int xSuitcase = (*_Suitcase)->GetX();
	int ySuitcase = (*_Suitcase)->GetY();

	int xPowerUp = x;
	int yPowerUp = y;

	bool c1 = (xSuitcase) < (xPowerUp + 10 * SizePowerUp);
	bool c2 = (xSuitcase + 20 * SizeSuitcase) > (xPowerUp - 10 * SizePowerUp);
	bool c3 = (ySuitcase - 2 * SizeSuitcase) < (yPowerUp + 10 * SizePowerUp);
	bool c4 = (ySuitcase + 10 * SizeSuitcase) > (yPowerUp - 10 * SizePowerUp);

	if (c1 && c2 && c3 && c4) doIntersect = true;

	if (doIntersect)
	{
		(*_Suitcase)->Hide();
		(*_Suitcase)->SetX(init_x);
		(*_Suitcase)->SetY(init_y);

		Suitcase* PowerUpSuitcase = new SuitcaseRedLocks(init_x, init_y, SizeSuitcase + 2);
		PowerUpSuitcase->SetVisibility(true);

		COLORREF MainColor = COLOR_BLACK;

		switch (GetType())
		{
		case 0:
			MainColor = COLOR_WHITE;
			break;
		case 1:
			MainColor = COLOR_RED;
			break;
		case 2:
			MainColor = COLOR_GREEN;
			break;
		case 3:
			MainColor = COLOR_YELLOW;
			break;
		case 4:
			MainColor = COLOR_BLUE;
			break;
		case 5:
			MainColor = COLOR_VIOLET;
			break;
		}

		PowerUpSuitcase->SetBodyColor(MainColor);
		PowerUpSuitcase->SetHandleColor(MainColor);

		Interact(_Suitcase);

		for (int i = 0; i < 2; i++)
		{
			PowerUpSuitcase->Show();
			Sleep(400);
			PowerUpSuitcase->Hide();
			Sleep(400);
		}

		delete PowerUpSuitcase;

		(*_Suitcase)->Show();
	}

	return doIntersect;
}

void PowerUp::Hide()
{
	HPEN Pen = CreatePen(PS_SOLID, 2, COLOR_CONSOLE);
	SelectObject(hdc, Pen);
	HBRUSH Brush;

	Brush = CreateSolidBrush(COLOR_CONSOLE);
	SelectObject(hdc, Brush);
	Rectangle(hdc, x - 10 * size, y - 10 * size, x + 10 * size, y + 10 * size);

	DeleteObject(Pen);
	DeleteObject(Brush);
}

void PowerUp::SetSize(int _size)
{
	size = _size;
}

PowerUp0::PowerUp0() : PowerUp()
{
	size = 0;
}

PowerUp0::PowerUp0(int _x, int _y, int _size) : PowerUp(_x, _y, _size)
{
	x = _x;
	y = _y;
	size = _size;
}

PowerUp0::~PowerUp0()
{
}

int PowerUp0::GetType()
{
	return 0;
}

void PowerUp0::Interact(Suitcase** _Suitcase)
{
	(*_Suitcase)->SetHandleColor(RGB(rand() % 255, rand() % 255, rand() % 255));
	(*_Suitcase)->SetBodyColor(RGB(rand() % 255, rand() % 255, rand() % 255));
}

void PowerUp0::Show()
{
	COLORREF typeColor = COLOR_WHITE;

	// Границы
	HPEN Pen = CreatePen(PS_SOLID, 2, typeColor);
	SelectObject(hdc, Pen);
	HBRUSH Brush;

	Brush = CreateSolidBrush(COLOR_CONSOLE);
	SelectObject(hdc, Brush);
	Rectangle(hdc, x - 10 * size, y - 10 * size, x + 10 * size, y + 10 * size);

	DeleteObject(Pen);
	DeleteObject(Brush);


	Pen = CreatePen(PS_NULL, 1, COLOR_WHITE);
	SelectObject(hdc, Pen);
	Brush = CreateSolidBrush(COLOR_GREEN);
	SelectObject(hdc, Brush);

	Rectangle(hdc, x - 9 * size, y - 9 * size, x + 9 * size, y + 9 * size);

	DeleteObject(Pen);
	DeleteObject(Brush);

	Pen = CreatePen(PS_NULL, 1, COLOR_WHITE);
	SelectObject(hdc, Pen);
	Brush = CreateSolidBrush(COLOR_RED);
	SelectObject(hdc, Brush);

	POINT vertices1[] = { {x - 9 * size, y - 9 * size}, {x + 3 * size, y - 9 * size}, {x - 9 * size, y + 3 * size} };
	Polygon(hdc, vertices1, sizeof(vertices1) / sizeof(vertices1[0]));

	DeleteObject(Pen);
	DeleteObject(Brush);

	Pen = CreatePen(PS_NULL, 1, COLOR_WHITE);
	SelectObject(hdc, Pen);
	Brush = CreateSolidBrush(COLOR_BLUE);
	SelectObject(hdc, Brush);

	POINT vertices2[] = { {x + 9 * size, y + 9 * size}, {x - 3 * size, y + 9 * size}, {x + 9 * size, y - 3 * size} };
	Polygon(hdc, vertices2, sizeof(vertices2) / sizeof(vertices2[0]));

	DeleteObject(Pen);
	DeleteObject(Brush);

	Pen = CreatePen(PS_SOLID, size - 1, COLOR_CONSOLE);
	SelectObject(hdc, Pen);

	MoveToEx(hdc, x + 3 * size, y - 9 * size, NULL);
	LineTo(hdc, x - 9 * size, y + 3 * size);

	MoveToEx(hdc, x - 3 * size, y + 9 * size, NULL);
	LineTo(hdc, x + 9 * size, y - 3 * size);

	DeleteObject(Pen);
	
}

PowerUp1::PowerUp1() : PowerUp()
{
	size = 0;
}

PowerUp1::PowerUp1(int _x, int _y, int _size) : PowerUp(_x, _y, _size)
{
	x = _x;
	y = _y;
	size = _size;
}

PowerUp1::~PowerUp1()
{
}

int PowerUp1::GetType()
{
	return 1;
}

void PowerUp1::Interact(Suitcase** _Suitcase)
{
	int StepSuitcase = (*_Suitcase)->GetStep();
	if (StepSuitcase > 10) StepSuitcase -= 10;
	else StepSuitcase = 1;
	(*_Suitcase)->SetStep(StepSuitcase);
}

void PowerUp1::Show()
{
	COLORREF typeColor = COLOR_RED;

	// Границы
	HPEN Pen = CreatePen(PS_SOLID, 2, typeColor);
	SelectObject(hdc, Pen);
	HBRUSH Brush;

	Brush = CreateSolidBrush(COLOR_CONSOLE);
	SelectObject(hdc, Brush);
	Rectangle(hdc, x - 10 * size, y - 10 * size, x + 10 * size, y + 10 * size);

	DeleteObject(Pen);
	DeleteObject(Brush);

	Pen = CreatePen(PS_SOLID, 1, typeColor);
	SelectObject(hdc, Pen);
	Brush = CreateSolidBrush(typeColor);
	SelectObject(hdc, Brush);

	Rectangle(hdc, x - 3 * size, y - 10 * size, x + 3 * size, y);

	POINT vertices[] = { {x - 10 * size + 1, y}, {x, y + 10 * size - 1}, {x + 10 * size - 1, y} };
	Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));

	DeleteObject(Pen);
	DeleteObject(Brush);
}

PowerUp2::PowerUp2() : PowerUp()
{
	size = 0;
}

PowerUp2::PowerUp2(int _x, int _y, int _size) : PowerUp(_x, _y, _size)
{
	x = _x;
	y = _y;
	size = _size;
}

PowerUp2::~PowerUp2()
{
}

int PowerUp2::GetType()
{
	return 2;
}

void PowerUp2::Interact(Suitcase** _Suitcase)
{
	int StepSuitcase = (*_Suitcase)->GetStep();
	if (StepSuitcase < 51) StepSuitcase += 5;
	(*_Suitcase)->SetStep(StepSuitcase);
}

void PowerUp2::Show()
{
	COLORREF typeColor = COLOR_GREEN;

	// Границы
	HPEN Pen = CreatePen(PS_SOLID, 2, typeColor);
	SelectObject(hdc, Pen);
	HBRUSH Brush;

	Brush = CreateSolidBrush(COLOR_CONSOLE);
	SelectObject(hdc, Brush);
	Rectangle(hdc, x - 10 * size, y - 10 * size, x + 10 * size, y + 10 * size);

	DeleteObject(Pen);
	DeleteObject(Brush);

	Pen = CreatePen(PS_SOLID, 1, typeColor);
	SelectObject(hdc, Pen);
	Brush = CreateSolidBrush(typeColor);
	SelectObject(hdc, Brush);

	Rectangle(hdc, x - 3 * size, y + 10 * size, x + 3 * size, y);

	POINT vertices[] = { {x - 10 * size + 1, y}, {x, y - 10 * size + 1}, {x + 10 * size - 1, y} };
	Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));

	DeleteObject(Pen);
	DeleteObject(Brush);
}

PowerUp3::PowerUp3() : PowerUp()
{
	size = 0;
}

PowerUp3::PowerUp3(int _x, int _y, int _size) : PowerUp(_x, _y, _size)
{
	x = _x;
	y = _y;
	size = _size;
}

PowerUp3::~PowerUp3()
{
}

int PowerUp3::GetType()
{
	return 3;
}

void PowerUp3::Interact(Suitcase** _Suitcase)
{
	int SizeSuitcase = (*_Suitcase)->GetSize();
	if (SizeSuitcase < 20) (*_Suitcase)->SetSize(SizeSuitcase + 5);
	else (*_Suitcase)->SetSize(5);
}

void PowerUp3::Show()
{
	COLORREF typeColor = COLOR_YELLOW;

	// Границы
	HPEN Pen = CreatePen(PS_SOLID, 2, typeColor);
	SelectObject(hdc, Pen);
	HBRUSH Brush;

	Brush = CreateSolidBrush(COLOR_CONSOLE);
	SelectObject(hdc, Brush);
	Rectangle(hdc, x - 10 * size, y - 10 * size, x + 10 * size, y + 10 * size);

	DeleteObject(Pen);
	DeleteObject(Brush);

	Pen = CreatePen(PS_SOLID, 1, typeColor);
	SelectObject(hdc, Pen);
	Brush = CreateSolidBrush(typeColor);
	SelectObject(hdc, Brush);

	POINT vertices1[] = { {x - 8 * size, y - 8 * size}, {x - 2 * size, y - 8 * size}, {x - 8 * size, y - 2 * size} };
	Polygon(hdc, vertices1, sizeof(vertices1) / sizeof(vertices1[0]));

	POINT vertices2[] = { {x + 8 * size, y + 8 * size}, {x + 2 * size, y + 8 * size}, {x + 8 * size, y + 2 * size} };
	Polygon(hdc, vertices2, sizeof(vertices2) / sizeof(vertices2[0]));

	DeleteObject(Pen);
	DeleteObject(Brush);
}

PowerUp4::PowerUp4() : PowerUp()
{
	size = 0;
}

PowerUp4::PowerUp4(int _x, int _y, int _size) : PowerUp(_x, _y, _size)
{
	x = _x;
	y = _y;
	size = _size;
}

PowerUp4::~PowerUp4()
{
}

int PowerUp4::GetType()
{
	return 4;
}

void PowerUp4::Interact(Suitcase** _Suitcase)
{
	int xSuitcase = (*_Suitcase)->GetX();
	int ySuitcase = (*_Suitcase)->GetY();
	int SizeSuitcase = (*_Suitcase)->GetSize();
	int StepSuitcase = (*_Suitcase)->GetStep();
	bool VisibleSuitcase = (*_Suitcase)->GetVisibility();
	COLORREF HandleColorSuitcase = (*_Suitcase)->GetHandleColor();
	COLORREF BodyColorSuitcase = (*_Suitcase)->GetBodyColor();

	Suitcase* newSuitcase;

	switch (GetType())
	{
	case 0:
		newSuitcase = new SuitcaseNoSmiley(xSuitcase, ySuitcase, SizeSuitcase);
		break;
	case 1:
		newSuitcase = new SuitcaseNoSmiley(xSuitcase, ySuitcase, SizeSuitcase);
		break;
	case 2:
		newSuitcase = new Suitcase(xSuitcase, ySuitcase, SizeSuitcase);
		break;
	case 3:
		newSuitcase = new SuitcaseNoLocks(xSuitcase, ySuitcase, SizeSuitcase);
		break;
	default:
		newSuitcase = new Suitcase(xSuitcase, ySuitcase, SizeSuitcase);
		break;
	}

	newSuitcase->SetStep(StepSuitcase);
	newSuitcase->SetVisibility(VisibleSuitcase);
	newSuitcase->SetHandleColor(HandleColorSuitcase);
	newSuitcase->SetBodyColor(BodyColorSuitcase);

	delete _Suitcase;
	_Suitcase = &newSuitcase;
}

void PowerUp4::Show()
{
	COLORREF typeColor = COLOR_BLUE;

	// Границы
	HPEN Pen = CreatePen(PS_SOLID, 2, typeColor);
	SelectObject(hdc, Pen);
	HBRUSH Brush;

	Brush = CreateSolidBrush(COLOR_CONSOLE);
	SelectObject(hdc, Brush);
	Rectangle(hdc, x - 10 * size, y - 10 * size, x + 10 * size, y + 10 * size);

	DeleteObject(Pen);
	DeleteObject(Brush);

	Pen = CreatePen(PS_SOLID, size, COLOR_BLACK);
	SelectObject(hdc, Pen);
	Brush = CreateSolidBrush(COLOR_YELLOW);
	SelectObject(hdc, Brush);
	Ellipse(hdc, x - 7 * size, y - 7 * size, x + 7 * size, y + 7 * size);

	DeleteObject(Pen);
	DeleteObject(Brush);

	Pen = CreatePen(PS_SOLID, 1, COLOR_BLACK);
	SelectObject(hdc, Pen);
	Brush = CreateSolidBrush(COLOR_BLACK);
	SelectObject(hdc, Brush);

	Ellipse(hdc, x - 3 * size, y - 3 * size, x - 1 * size, y - 1 * size);
	Ellipse(hdc, x + 1 * size, y - 3 * size, x + 3 * size, y - 1 * size);
	Ellipse(hdc, x - 4 * size, y + 0 * size, x + 4 * size, y + 5 * size);

	DeleteObject(Pen);
	DeleteObject(Brush);

	Pen = CreatePen(PS_SOLID, 1, COLOR_YELLOW);
	SelectObject(hdc, Pen);
	Brush = CreateSolidBrush(COLOR_YELLOW);
	SelectObject(hdc, Brush);

	Rectangle(hdc, x - 4 * size, y + 0 * size, x + 4 * size, y + 2 * size);

	DeleteObject(Pen);
	DeleteObject(Brush);
}

PowerUp5::PowerUp5() : PowerUp()
{
	size = 0;
}

PowerUp5::PowerUp5(int _x, int _y, int _size) : PowerUp(_x, _y, _size)
{
	x = _x;
	y = _y;
	size = _size;
}

PowerUp5::~PowerUp5()
{
}

int PowerUp5::GetType()
{
	return 5;
}

void PowerUp5::Interact(Suitcase** _Suitcase)
{

}

void PowerUp5::Show()
{
	COLORREF typeColor = COLOR_VIOLET;

	// Границы
	HPEN Pen = CreatePen(PS_SOLID, 2, typeColor);
	SelectObject(hdc, Pen);
	HBRUSH Brush;

	Brush = CreateSolidBrush(COLOR_CONSOLE);
	SelectObject(hdc, Brush);
	Rectangle(hdc, x - 10 * size, y - 10 * size, x + 10 * size, y + 10 * size);

	DeleteObject(Pen);
	DeleteObject(Brush);

	Pen = CreatePen(PS_SOLID, size, COLOR_BLACK);
	SelectObject(hdc, Pen);
	Brush = CreateSolidBrush(COLOR_BROWN);
	SelectObject(hdc, Brush);
	
	Rectangle(hdc, x - 2 * size, y - 4 * size, x + 2 * size, y + 4 * size);

	DeleteObject(Pen);
	DeleteObject(Brush);

	Pen = CreatePen(PS_SOLID, 1, COLOR_BLACK);
	SelectObject(hdc, Pen);
	Brush = CreateSolidBrush(COLOR_GOLD);
	SelectObject(hdc, Brush);

	Rectangle(hdc, x - 1 * size, y - 1 * size, x + 1 * size, y + 2 * size);

	DeleteObject(Pen);
	DeleteObject(Brush);
}
