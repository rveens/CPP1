#include "stdafx.h"
#include "ChildView.h"
#include "Shape.h"


Shapes::Shape::Shape()
{
	pen.CreatePen(PS_DOT, 1, RGB(0,0,0));
}

Shapes::Shape::~Shape(void)
{
}

void Shapes::Shape::Draw(CDC *pDC)
{
	this->start = start;
	this->end = end;
	pDC->SetROP2(R2_NOTXORPEN);
	pDC->SelectObject(&pen);
}

void Shapes::Shape::SetPoints(CPoint start, CPoint end)
{
	this->start = start;
	this->end = end;
}