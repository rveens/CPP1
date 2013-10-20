#include "stdafx.h"
#include "Polygon.h"


Shapes::Polygon::Polygon(void)
{
}

Shapes::Polygon::~Polygon(void)
{
}

void Shapes::Polygon::Draw(CDC *pDC)
{
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