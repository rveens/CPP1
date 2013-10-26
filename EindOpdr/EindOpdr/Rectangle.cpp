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

	CRect textRect(points[0].x, points[0].y, points[1].x, points[1].y);
	pDC->DrawText(this->text.c_str(), textRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}