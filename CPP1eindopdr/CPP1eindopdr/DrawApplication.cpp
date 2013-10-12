#include "stdafx.h"
#include "DrawApplication.h"


DrawApplication::DrawApplication(void)
{
	history = new std::vector<Shapes::Shape *>();
	savedShapes = new std::vector<Shapes::Shape *>();
	startPoint.x = -1;
	endPoint.x = -1;

	// Set default selection shape
	this->selectionDrawShape = new Shapes::Rectangle();
}

DrawApplication::~DrawApplication(void)
{
	// FIXME vector waardes deleten.
	delete history;
	delete savedShapes;
	delete selectionDrawShape;
}

void DrawApplication::SetCurrentDrawShape(Shapes::Shape *s)
{
	if (this->selectionDrawShape)
		delete this->selectionDrawShape;
	this->selectionDrawShape = s;
}

void DrawApplication::StartSelection(CPoint startpoint)
{
	this->startPoint = startpoint;
}

void DrawApplication::StopSelection(CPoint endpoint)
{
	// TODO save drawing points into a shape variable.

	/* sla de huidige op in de savedShapes lijst. */
	this->savedShapes->push_back(selectionDrawShape);

	if (this->selectionDrawShape) {
		std::string s = this->selectionDrawShape->toString();
		TRACE(s.c_str());
	}
	
	/* Zet de huidige selectie pointer op null. */
	this->selectionDrawShape = nullptr;

	this->startPoint.x = -1;
	this->endPoint.x = -1;
}

void DrawApplication::DrawSelection(CDC *pDC, CPoint currentMousePosition)
{
	if (startPoint.x != -1 && this->selectionDrawShape)
	{
		// Trek vorige vorm over. 2 x XOR geeft oorspronkelijke waarde
		if (endPoint.x != -1) {
			this->selectionDrawShape->SetPoints(startPoint, endPoint);
			this->selectionDrawShape->Draw(pDC);
		}

		// Teken huidige vorm met XOR
		this->selectionDrawShape->SetPoints(startPoint, currentMousePosition);
		this->selectionDrawShape->Draw(pDC);
		endPoint = currentMousePosition;
	}
}

void DrawApplication::DrawSavedShapes(CDC *pDC)
{
	std::vector<Shapes::Shape*>::iterator it, end;
	
	end = this->savedShapes->end();

	for (it = this->savedShapes->begin(); it != end; ++it)
		(*it)->Draw(pDC); // TODO tekenwaardes opslaan bij shape.
}