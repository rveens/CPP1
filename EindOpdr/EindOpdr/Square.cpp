#include "stdafx.h"
#include "Square.h"


Shapes::Square::Square(void)
{
}

Shapes::Square::~Square(void)
{
}

void Shapes::Square::Draw(CDC *pDC)
{
	Shapes::Shape::Draw(pDC);
	pDC->Rectangle(start.x, start.y, end.x, end.y);
}

void Shapes::Square::SetPoints(CPoint start, CPoint end)
{
	this->start = start;
	this->end.y = (end.x - start.x) + start.y;
	this->end.x = end.x;
}