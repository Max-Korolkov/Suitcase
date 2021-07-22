#pragma once
#include <Windows.h>

class Coordinates
{
protected:
	int x;
	int y;
public:
	Coordinates();
	Coordinates(int _x, int _y);
	~Coordinates();
	int GetX();
	int GetY();
	void SetX(int _x);
	void SetY(int _y);
};

class Point : public Coordinates
{
protected:
	bool isVisible;
	int step;
	COLORREF color;
public:
	Point();
	Point(int _x, int _y, COLORREF _color);
	~Point();

	COLORREF GetColor();
	int GetStep();
	bool GetVisibility();

	virtual void Show();
	virtual void Hide();

	void SetColor(COLORREF _color);
	void SetStep(int _step);
	void SetVisibility(bool _isVisible);
	void Drag();
};

class ISuitcase
{
	virtual void DrawSmiley() = 0;
	virtual void DrawLocks() = 0;
	virtual void DrawHandle() = 0;
	virtual void DrawBody() = 0;
};

class Suitcase : public Point, public ISuitcase
{
protected:
	int size;
	COLORREF color_handle;
	COLORREF color_body;
public:
	Suitcase();
	Suitcase(int _x, int _y, int _size);
	~Suitcase();

	int GetSize();
	COLORREF GetHandleColor();
	COLORREF GetBodyColor();

	virtual void DrawSmiley();
	virtual void DrawLocks();
	virtual void DrawHandle();
	virtual void DrawBody();

	virtual void Show();
	virtual void Hide();

	void SetHandleColor(COLORREF _color_handle);
	void SetBodyColor(COLORREF _color_body);
	void SetSize(int _size);
};

class SuitcaseNoLocks : public Suitcase
{
public:
	SuitcaseNoLocks();
	SuitcaseNoLocks(int _x, int _y, int _size);
	~SuitcaseNoLocks();

	virtual void DrawLocks();
};

class SuitcaseNoSmiley : public Suitcase
{
public:
	SuitcaseNoSmiley();
	SuitcaseNoSmiley(int _x, int _y, int _size);
	~SuitcaseNoSmiley();

	virtual void DrawSmiley();
};

class SuitcaseNoSmileyLocks : public Suitcase
{
public:
	SuitcaseNoSmileyLocks();
	SuitcaseNoSmileyLocks(int _x, int _y, int _size);
	~SuitcaseNoSmileyLocks();

	virtual void DrawLocks();
	virtual void DrawSmiley();
};

class SuitcaseRedLocks : public SuitcaseNoSmiley
{
public:
	SuitcaseRedLocks();
	SuitcaseRedLocks(int _x, int _y, int _size);
	~SuitcaseRedLocks();

	virtual void DrawLocks();
};

class PowerUp : public Point
{
protected:
	int size;

public:
	PowerUp();
	PowerUp(int _x, int _y, int _size);

	int GetSize();
	virtual int GetType() = 0;

	bool CheckCollision(Suitcase** _Suitcase);
	virtual void Interact(Suitcase** _Suitcase) = 0;

	virtual void Show() = 0;
	void Hide();

	void SetSize(int _size);
};

class PowerUp0 : public PowerUp
{
public:
	PowerUp0();
	PowerUp0(int _x, int _y, int _size);
	~PowerUp0();

	virtual int GetType();
	virtual void Interact(Suitcase** _Suitcase);
	virtual void Show();
};

class PowerUp1 : public PowerUp
{
public:
	PowerUp1();
	PowerUp1(int _x, int _y, int _size);
	~PowerUp1();

	virtual int GetType();
	virtual void Interact(Suitcase** _Suitcase);
	virtual void Show();
};

class PowerUp2 : public PowerUp
{
public:
	PowerUp2();
	PowerUp2(int _x, int _y, int _size);
	~PowerUp2();

	virtual int GetType();
	virtual void Interact(Suitcase** _Suitcase);
	virtual void Show();
};

class PowerUp3 : public PowerUp
{
public:
	PowerUp3();
	PowerUp3(int _x, int _y, int _size);
	~PowerUp3();

	virtual int GetType();
	virtual void Interact(Suitcase** _Suitcase);
	virtual void Show();
};

class PowerUp4 : public PowerUp
{
public:
	PowerUp4();
	PowerUp4(int _x, int _y, int _size);
	~PowerUp4();

	virtual int GetType();
	virtual void Interact(Suitcase** _Suitcase);
	virtual void Show();
};

class PowerUp5 : public PowerUp
{
public:
	PowerUp5();
	PowerUp5(int _x, int _y, int _size);
	~PowerUp5();

	virtual int GetType();
	virtual void Interact(Suitcase** _Suitcase);
	virtual void Show();
};
