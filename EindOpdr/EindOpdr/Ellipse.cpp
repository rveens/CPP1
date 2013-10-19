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
	pDC->Ellipse(points[0].x, points[0].y, points[1].x, points[1].y);
}