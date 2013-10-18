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
	pDC->Ellipse(start.x, start.y, end.x, end.y);
}