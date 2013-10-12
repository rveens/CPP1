#include "stdafx.h"
#include "Circle.h"
#include "ChildView.h"

Shapes::Circle::Circle() : Shape()
{
}


Shapes::Circle::~Circle(void)
{
}

void Shapes::Circle::Draw(CDC *pDC, CPoint start, CPoint end)
{
	Shapes::Shape::Draw(pDC, start, end);

	pDC->Ellipse(start.x, start.y, end.x, end.y);
}
