#include "stdafx.h"
#include "Square.h"


Shapes::Square::Square(int id) : Shape(id)
{
}

Shapes::Square::~Square(void)
{
}

void Shapes::Square::Draw(CDC *pDC)
{
	CPen tp2, tp3;

	Shapes::Shape::Draw(pDC);
	if (points.empty())
		return;

	CBrush b(this->fill);
	pDC->SelectObject(&b);

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

void Shapes::Square::SetPoints(vector<CPoint> points)
{
	Shapes::Shape::SetPoints(points); // doet check op min. 2 punten.

	// aanpassingen van circle.
	this->points[1].y = (points[1].x - points[0].x) + points[0].y;

	/* Dit stond er eerst
		this->end.y = (end.x - start.x) + start.y;
		this->end.x = end.x;
	*/
}

std::shared_ptr<Shapes::Shape> Shapes::Square::clone() const
{
	return std::shared_ptr<Square>(new Square(*this)); // copy constructor
}