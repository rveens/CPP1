#include "stdafx.h"
#include "Polygon.h"
#include <algorithm>

using std::for_each;

Shapes::Polygon::Polygon(void)
{
}

Shapes::Polygon::~Polygon(void)
{
}

void Shapes::Polygon::Draw(CDC *pDC)
{
	Shapes::Shape::Draw(pDC);
	if (!points.empty())
		pDC->Polygon(&points[0], points.size());
}

void Shapes::Polygon::SetPoints(vector<CPoint> points)
{
	if (points.size() < 1)
		throw std::invalid_argument("polygon expected at least one point");

	this->points = points;
}

string Shapes::Polygon::toString() const
{
	// TODO tostring voor polygon.

	return string();
}

bool Shapes::Polygon::IsOn(CPoint point) const
{
	// neem de grootste x en y waardes in alle punten van de polygon.
	int yHighest, xHighest, yLowest, xLowest;

	yHighest = xHighest = point.y;
	yLowest = xLowest = point. x;

	for_each(begin(this->points), end(this->points), [&](CPoint p) {
		// hoger dan hoogst?
		if (p.x > xHighest)
			xHighest = p.x;
		if (p.y > yHighest)
			yHighest = p.y;
		// lager dan laagst?
		if (p.x < xLowest)
			xLowest = p.x;
		if (p.y < yLowest)
			yLowest = p.y;
	});

	if (point.x > xLowest && point.x < xHighest &&
		point.y > yLowest && point.y < yHighest)
		return true;
	else
		return false;
}