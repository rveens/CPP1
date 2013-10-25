#include "stdafx.h"
#include "Shape.h"
#include <sstream>


Shapes::Shape::Shape()
{
	pen.CreatePen(PS_DOT, 1, RGB(0,0,255));
}

// regel van drie (rule of three)

/* 1. Copy constructor, als een object nog niet geinitialiseerd is, zoals bijv Shape s = r; s is nog niet geinitialiseerd, copy constructor wordt aangeroepen. */
/*Shapes::Shape::Shape(const Shapes::Shape &ander) : pen(ander.pen), start(ander.start), end(ander.end)
{
}*/

/* 2. Assignement operator */
/*Shapes::Shape &Shapes::Shape::operator=(const Shapes::Shape &ander)
{
	// belangrijk! gooi oude data weg/reset.

	this->pen = ander.pen;
	this->start = ander.start;
	this->end = ander.end;

	return *this; // Geef een referentie terug, geen pointer.
}*/

/* 3. Destructor */
Shapes::Shape::~Shape(void)
{
}

void Shapes::Shape::Draw(CDC *pDC)
{
	pDC->SetROP2(R2_NOTXORPEN);
	pDC->SelectObject(&pen);
}

void Shapes::Shape::SetPoints(vector<CPoint> points)
{
	if (points.size() < 2)
		throw std::invalid_argument("shape expected at least two points");
	else
		this->points = points;
}

std::string Shapes::Shape::toString() const
{
	std::stringstream ss;
	
	ss << "startx: " << this->points[0].x << " starty:" << this->points[0].y << std::endl;
	ss << "endx: " << this->points[1].x << " endy:" << this->points[1].y << std::endl;
	//ss << "pen: " << this->pen;
	
	return ss.str();
}

void Shapes::Shape::SetPen(int nPenStyle, int nWidth, COLORREF crColor)
{
	this->pen.DeleteObject();
	this->pen.CreatePen(nPenStyle, nWidth, crColor);
}

bool Shapes::Shape::IsOn(CPoint point) const
{
	return true;
}