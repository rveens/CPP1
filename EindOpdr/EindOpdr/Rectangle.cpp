#include "stdafx.h"
#include "Rectangle.h"


Shapes::Rectangle::Rectangle() : Shape()
{
}

Shapes::Rectangle::~Rectangle(void)
{
}

void Shapes::Rectangle::Draw(CDC *pDC)
{
	Shapes::Shape::Draw(pDC);

	pDC->Rectangle(start.x, start.y, end.x, end.y);
}