#include "stdafx.h"
#include "Square.h"


Shapes::Square::Square(void)
{
}

Shapes::Square::~Square(void)
{
}

void Shapes::Square::Draw(CDC *pDC)
{
	Shapes::Shape::Draw(pDC);
	if (points.empty())
		return;

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