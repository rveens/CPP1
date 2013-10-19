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
	pDC->Rectangle(points[0].x, points[0].y, points[1].x, points[1].y);
}