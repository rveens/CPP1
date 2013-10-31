#include "stdafx.h"
#include "Shape.h"
#include <sstream>
#include <algorithm>


Shapes::Shape::Shape(int id) : id(id), text(L""), isSelected(false)
{
	/* pen pen used for drag/draw */
	pen.lopnStyle = PS_DOT;
	POINT p;
	p.x = 1;
	pen.lopnWidth = p;
	pen.lopnColor = RGB(0,0,255);

	/* linePen, pen used for lines */
	linePen.lopnStyle = PS_DASH;
	linePen.lopnWidth = p;
	linePen.lopnColor = RGB(0,0,0);

	/* selectionPen, pen used for selection on click */
	selectionPen.lopnStyle = PS_DASH;
	p.x = 2;
	selectionPen.lopnWidth = p;
	selectionPen.lopnColor = RGB(255,0,0);
}

// regel van drie (rule of three)

/* 1. Copy constructor, als een object nog niet geinitialiseerd is, zoals bijv Shape s = r; s is nog niet geinitialiseerd, copy constructor wordt aangeroepen. */
/*Shapes::Shape::Shape(const Shapes::Shape &ander) 
	: pen(ander.pen), selectionPen(ander.selectionPen), linePen(ander.linePen), points(ander.points), text(ander.text), child(ander.child)
{
}*/

/* 2. Assignement operator */
/*Shapes::Shape &Shapes::Shape::operator=(const Shapes::Shape &ander)
{
	// belangrijk! gooi oude data weg/reset.
	this->pen = ander.pen;
	this->selectionPen = ander.selectionPen;
	this->linePen = ander.linePen;
	this->points = ander.points;
	this->text = ander.text;
	this->child = ander.child;

	return *this; // Geef een referentie (objectwaarde) terug, geen pointer.
}*/

/* 3. Destructor */
Shapes::Shape::~Shape(void)
{
}

void Shapes::Shape::Draw(CDC *pDC)
{
	CPen tp1;

	pDC->SetROP2(R2_NOTXORPEN);

	// Probeer de lijn te tekenen.
	tp1.CreatePenIndirect(&this->linePen);
	pDC->SelectObject(&tp1); // speciale lijn pen
	this->DrawLine(pDC);
}

void Shapes::Shape::DrawLine(CDC *pDC)
{
	CPoint originalPos = pDC->GetCurrentPosition(); // positie die we nu even opslaan.
	auto scp = this->child.lock(); // shared_ptr die nu even strong is (mits de shape wel bestaat), gedurende de scope van de ze functie.
	int currShapeMiddleX, currShapeMiddleY, childMiddleX, childMiddleY; // voor het bepalen van het midden.

	/* teken van de huidige shape naar de child shape, als die bestaat, een lijn. */
	if (scp && !this->points.empty() && !scp->GetPoints().empty()) { // punten van de shapes mogen niet leeg zijn.
		/* shape gaat uit van twee punten, andere vormen moeten drawline maar overriden */

		/* we bepalen het midden van de twee punten, van de huidige shape (this) */
		currShapeMiddleX = (this->points[1].x - this->points[0].x) / 2 + this->points[0].x;
		currShapeMiddleY = (this->points[1].y - this->points[0].y ) / 2 + this->points[0].y;
		pDC->MoveTo(currShapeMiddleX, currShapeMiddleY);

		/* we bepalen het midden van de twee punten, van de child shape */
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

void Shapes::Shape::SetPen(LOGPEN p)
{
	this->pen = p;
}

void Shapes::Shape::SetLinePen(LOGPEN p)
{
	this->linePen = p;
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

unsigned int Shapes::Shape::GetID()
{
	return this->id;
}

void Shapes::Shape::SetID(unsigned int newID)
{
	this->id = newID;
}

ostream &Shapes::Shape::print(ostream &o) const
{
	// pak de child id;
	int childid = -1;
	auto sp = child.lock();
	if (sp)
		childid = sp->GetID();

	std::string textstring(text.begin(), text.end());

	// class name
	std::string classnamefull(typeid(*this).name());
	std::string classname = classnamefull.substr(classnamefull.find("::")+2, classnamefull.size()-1);

	// RECT + ' id text points[0].x points[0].y points[1].x points[1].y childid isselected'
	o << classname << " " << id << " " << textstring << " STRINGEND ";

	// punten er in stoppen
	std::for_each(begin(points), end(points), [&](CPoint p) {
		o << p.x << " ";
		o << p.y << " ";
	});
	o << "POINTSEND " << childid << " " << isSelected << " " << std::endl;

	return o;
}

istream &Shapes::Shape::read(istream &is)
{
	// points clearen
	this->points.clear();

	// string
	std::string s;

	is >> id;

	/* string pakken*/
	is >> s;
	if (s != "STRINGEND") {
		text = wstring(s.begin(), s.end());
		is >> s; // STRINGEND weghalen
	}

	// blijf punten in laden totdat we POINTSEND tegenkomen
	int x, y;
	bool toggle = true, makePoint = false;
	while (s != "POINTSEND") {
		is >> s;
		if (s == "POINTSEND")
			break;
		if (toggle) {
			x = std::stoi(s);
			toggle = false;
		} else {
			y = std::stoi(s);
			makePoint = true;
			toggle = true;
		}

		if (makePoint) {
			points.push_back(CPoint(x, y));
			makePoint = false;
		}
	}

	is >> s; // TODO childid
	is >> isSelected;

	return is;
}