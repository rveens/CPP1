#include "stdafx.h"
#include "Polygon.h"
#include <algorithm>

using std::for_each;

Shapes::Polygon::Polygon(int id) : Shape(id)
{
}

Shapes::Polygon::~Polygon(void)
{
}

void Shapes::Polygon::Draw(CDC *pDC)
{
	CPen tp2, tp3;
	Shapes::Shape::Draw(pDC);

	CBrush b(this->fill);
	pDC->SelectObject(&b);

	if (this->isSelected) { // pak speciale selectie pen
		tp2.CreatePenIndirect(&this->selectionPen);
		pDC->SelectObject(&tp2);
	} else { // neem de normale pen
		tp3.CreatePenIndirect(&this->pen);
		pDC->SelectObject(&tp3);
	}

	if (!points.empty()) {
		pDC->Polygon(&points[0], points.size());

		/* teken de tekst, eerst het rect bepalen van de polygon (max x, max y) */
		int yHighest, xHighest, yLowest, xLowest;

		yHighest = xHighest = points[0].x;
		yLowest = xLowest = points[0].x;

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

		CRect textRect(xLowest, yLowest, xHighest, yHighest);
		pDC->DrawText(this->text.c_str(), textRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
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

std::shared_ptr<Shapes::Shape> Shapes::Polygon::clone() const
{
	return std::shared_ptr<Polygon>(new Polygon(*this)); // copy constructor
}