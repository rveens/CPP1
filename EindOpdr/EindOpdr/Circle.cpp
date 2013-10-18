#include "stdafx.h"
#include "Circle.h"

Shapes::Circle::Circle() : Shape()
{
}


Shapes::Circle::~Circle(void)
{
}

void Shapes::Circle::Draw(CDC *pDC)
{
	Shapes::Shape::Draw(pDC);

	pDC->Ellipse(start.x, start.y, end.x, end.y);
}

void Shapes::Circle::SetPoints(CPoint start, CPoint end)
{
	this->start = start;
	this->end.y = (end.x - start.x) + start.y;
	this->end.x = end.x;
}