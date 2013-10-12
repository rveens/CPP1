#include "stdafx.h"
#include "ChildView.h"
#include "Shape.h"


Shapes::Shape::Shape()
{
	pen.CreatePen(PS_DOT, 1, RGB(255,0,0));
}

Shapes::Shape::~Shape(void)
{
}

void Shapes::Shape::Draw(CDC *pDC, CPoint start, CPoint end)
{
	pDC->SetROP2(R2_NOTXORPEN);
	pDC->SelectObject(&pen);
}