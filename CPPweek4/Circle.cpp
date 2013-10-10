#include "stdafx.h"
#include "ChildView.h"
#include "Circle.h"


Shapes::Circle::Circle(CChildView *view)
{
}


Shapes::Circle::~Circle(void)
{
}

void Shapes::Circle::Draw(CPoint begin, CPoint end)
{
	CDC* pDC = view->GetDC();

	Shape::Draw(begin, end);
	pDC->Ellipse(start.x, start.y, begin.x, end.y);

	view->ReleaseDC(pDC);
}
