#include "stdafx.h"
#include "Ellipse.h"


Shapes::Ellipse::Ellipse(void)
{
}


Shapes::Ellipse::~Ellipse(void)
{
}

void Shapes::Ellipse::Draw(CDC *pDC)
{
	Shapes::Shape::Draw(pDC);
	if (points.empty())
		return;

	pDC->Ellipse(points[0].x, points[0].y, points[1].x, points[1].y);

	CRect textRect(points[0].x, points[0].y, points[1].x, points[1].y);
	pDC->DrawText(this->text.c_str(), textRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}