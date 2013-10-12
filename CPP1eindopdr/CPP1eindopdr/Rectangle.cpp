#include "stdafx.h"
#include "Rectangle.h"
#include "ChildView.h"


Shapes::Rectangle::Rectangle() : Shape()
{
}

Shapes::Rectangle::~Rectangle(void)
{
}

void Shapes::Rectangle::Draw(CDC *pDC, CPoint start, CPoint end)
{
	Shapes::Shape::Draw(pDC, start, end);

	pDC->Rectangle(start.x, start.y, end.x, end.y);
}
