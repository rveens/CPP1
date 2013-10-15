#include "stdafx.h"
#include "Shape.h"
#include <sstream>


Shapes::Shape::Shape()
{
	pen.CreatePen(PS_DOT, 1, RGB(0,0,0));
}

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

/* let op globale scope, in shape staat een declaratie met friend. */
std::ostream& operator<<(std::ostream& stream, const Shapes::Shape& shape)
{
	return stream << shape.toString();
}

