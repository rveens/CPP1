#include "stdafx.h"
#include "Shape.h"
#include "ChildView.h"


Shapes::Shape::Shape(CChildView *view)
{
	this->start.x = -1;
	this->end.x = -1;
	
	this->view = view;

	pen.CreatePen(PS_DOT, 1, RGB(255,0,0));
}

Shapes::Shape::~Shape(void)
{
}

void Shapes::Shape::Draw(CPoint start, CPoint end)
{
	CDC* pDC = view->GetDC();

	// Teken met NOT XOR
	pDC->SetROP2(R2_NOTXORPEN);

	view->ReleaseDC(pDC);

	pDC->SelectObject(&pen);
}
