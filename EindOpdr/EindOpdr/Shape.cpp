#include "stdafx.h"
#include "Shape.h"
#include <sstream>


Shapes::Shape::Shape()
{
	pen.CreatePen(PS_DOT, 1, RGB(0,0,0));
}

/* 1. Copy constructor, als een object nog niet geinitialiseerd is, zoals bijv Shape s = r; s is nog niet geinitialiseerd, copy constructor wordt aangeroepen. */
/*Shapes::Shape::Shape(const Shapes::Shape &ander) : pen(ander.pen), start(ander.start), end(ander.end)
{
}*/

/* 2. Assignement operator */
/*Shapes::Shape &Shapes::Shape::operator=(const Shapes::Shape &ander)
{
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
	this->start = start;
	this->end = end;
	pDC->SetROP2(R2_NOTXORPEN);
	pDC->SelectObject(&pen);
}

void Shapes::Shape::SetPoints(CPoint start, CPoint end)
{
	this->start = start;
	this->end = end;
}

std::string Shapes::Shape::toString() const
{
	std::stringstream ss;
	
	ss << "startx: " << this->start.x << " starty:" << this->start.y << std::endl;
	ss << "endx: " << this->end.x << " endy:" << this->end.y << std::endl;
	//ss << "pen: " << this->pen;
	
	return ss.str();
}