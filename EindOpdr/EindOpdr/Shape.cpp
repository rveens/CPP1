#include "stdafx.h"
#include "Shape.h"
#include <sstream>


Shapes::Shape::Shape() : text(L""), isSelected(false)
{
	pen.CreatePen(PS_DOT, 1, RGB(0,0,255)); // pen used for drag/draw
	linePen.CreatePen(PS_DASH, 1, RGB(0, 0, 0)); // pen used for lines
	selectionPen.CreatePen(PS_DASH, 2, RGB(255, 0, 0)); // pen used for selection on click
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

	// Probeer de lijn te tekenen.
	pDC->SelectObject(&linePen); // speciale lijn pen
	this->DrawLine(pDC);

	if (this->isSelected) // pak speciale selectie pen
		pDC->SelectObject(&selectionPen);
	else // neem de normale pen
		pDC->SelectObject(&pen);
}

void Shapes::Shape::DrawLine(CDC *pDC)
{
	CPoint originalPos = pDC->GetCurrentPosition(); // positie die we nu even opslaan.
	auto scp = this->child.lock(); // shared_ptr die nu even strong is (mits de shape wel bestaat), gedurende de scope van de ze functie.
	int childMiddleX, childMiddleY; // voor het bepalen van het midden.

	/* teken van de huidige shape naar de child shape, als die bestaat, een lijn. */
	if (scp && !this->points.empty() && !scp->GetPoints().empty()) { // punten van de shapes mogen niet leeg zijn.
		pDC->MoveTo( (this->points[1].x - this->points[0].x) / 2 + this->points[0].x, (this->points[1].y - this->points[0].y ) / 2 + this->points[0].y);
		/* shape gaat uit van twee punten, andere vormen moeten drawline maar overriden */
		/* we bepane het midden van de twee punten, van de child shape */
		childMiddleX = (scp->GetPoints()[1].x - scp->GetPoints()[0].x) / 2 + scp->GetPoints()[0].x;
		childMiddleY = (scp->GetPoints()[1].y - scp->GetPoints()[0].y) / 2 + scp->GetPoints()[0].y;

		pDC->LineTo(childMiddleX, childMiddleY);
		// Zet de positie terug op de oude
		pDC->MoveTo(originalPos);
	}
}

void Shapes::Shape::SetPoints(vector<CPoint> points)
{
	if (points.size() < 2)
		throw std::invalid_argument("shape expected at least two points");
	else
		this->points = points;
}

vector<CPoint> Shapes::Shape::GetPoints()
{
	return this->points;
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
	bool returnValue = false;

	if (points.size() == 2)
		if (point.x > points[0].x && point.x < points[1].x &&
			point.y > points[0].y && point.y < points[1].y)
			returnValue = true;

	return returnValue;
}

void Shapes::Shape::SetText(wstring newstring)
{
	this->text = newstring;
}

wstring Shapes::Shape::GetText()
{
	return this->text;
}

void Shapes::Shape::SetIsSelected(bool newselected)
{
	this->isSelected = newselected;
}

bool Shapes::Shape::GetIsSelected()
{
	return this->isSelected;
}

void Shapes::Shape::SetChild(weak_ptr<Shapes::Shape> s)
{
	this->child = s;
}
	
weak_ptr<Shapes::Shape> Shapes::Shape::GetChild()
{
	return this->child;
}