#include "stdafx.h"
#include "Rectangle.h"
#include "ChildView.h"


Shapes::Rectangle::Rectangle(CChildView *view)
{
}

Shapes::Rectangle::~Rectangle(void)
{
}

void Shapes::Rectangle::Draw(CPoint begin, CPoint end)
{
	CDC* pDC = view->GetDC();

	Shape::Draw(begin, end);
	pDC->Rectangle(begin.x, begin.y, end.x, end.y);

	view->ReleaseDC(pDC);
}
