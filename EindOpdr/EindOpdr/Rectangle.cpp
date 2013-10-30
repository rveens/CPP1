#include "stdafx.h"
#include "Rectangle.h"

Shapes::Rectangle::Rectangle(int id) : Shape(id)
{
}

Shapes::Rectangle::~Rectangle(void)
{
}

void Shapes::Rectangle::Draw(CDC *pDC)
{
	CPen tp2, tp3;

	Shapes::Shape::Draw(pDC);
	if (points.empty())
		return;

	if (this->isSelected) { // pak speciale selectie pen
		tp2.CreatePenIndirect(&this->selectionPen);
		pDC->SelectObject(&tp2);
	} else { // neem de normale pen
		tp3.CreatePenIndirect(&this->pen);
		pDC->SelectObject(&tp3);
	}

	pDC->Rectangle(points[0].x, points[0].y, points[1].x, points[1].y);

	CRect textRect(points[0].x, points[0].y, points[1].x, points[1].y);
	pDC->DrawText(this->text.c_str(), textRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

std::shared_ptr<Shapes::Shape> Shapes::Rectangle::clone() const
{
	return std::shared_ptr<Rectangle>(new Rectangle(*this)); // copy constructor
}