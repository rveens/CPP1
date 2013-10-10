#include "stdafx.h"
#include "DrawApplication.h"


DrawApplication::DrawApplication(void)
{
	history = new std::vector<Shapes::Shape *>();
	startPoint.x = -1;
	endPoint.x = -1;
}

DrawApplication::~DrawApplication(void)
{
	delete history;
}

void DrawApplication::StartSelection(CPoint startpoint)
{
	this->startPoint = startpoint;
}

void DrawApplication::StopSelection(CPoint endpoint)
{
	// TODO save drawing points into a shape variable.
	this->startPoint.x = -1;
	this->endPoint.x = -1;
}

void DrawApplication::DrawSelection(CDC *pDC, CPoint currentMousePosition)
{
	if (startPoint.x == -1) {
		Shapes::Rectangle *r = new Shapes::Rectangle();
		history->push_back(r);
	}

	if (startPoint.x != -1)
	{
		//Shapes::Rectangle r = Shapes::Rectangle();
		Shapes::Rectangle *r = new Shapes::Rectangle();
		history->push_back(r);

		// Trek vorige rechthoek over. 2 x XOR geeft oorspronkelijke waarde
		if (endPoint.x != -1)
			r->Draw(pDC, startPoint, endPoint);

		// Teken huidige rechthoek met XOR
		r->Draw(pDC, startPoint, currentMousePosition);
		endPoint = currentMousePosition;
	}
}