#include "stdafx.h"
#include "Circle.h"

Shapes::Circle::Circle() : Shape()
{
}


Shapes::Circle::~Circle(void)
{
}

void Shapes::Circle::Draw(CDC *pDC)
{
	Shapes::Shape::Draw(pDC);

	pDC->Ellipse(points[0].x, points[0].y, points[1].x, points[1].y);
}

void Shapes::Circle::SetPoints(vector<CPoint> points)
{
	Shapes::Shape::SetPoints(points); // doet check op min. 2 punten.

	// aanpassingen van circle.
	this->points[1].y = (points[1].x - points[0].x) + points[0].y;

	/* Dit stond er eerst
		this->end.y = (end.x - start.x) + start.y;
		this->end.x = end.x;
	*/
}