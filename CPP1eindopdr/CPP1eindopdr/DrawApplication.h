#pragma once

#include "stdafx.h"
#include <vector>
#include "Shape.h"
#include "Rectangle.h"

class DrawApplication
{
public:
	DrawApplication(void);
	~DrawApplication(void);
	void StartSelection(CPoint startpoint);
	void StopSelection(CPoint endpoint);
	void DrawSelection(CDC *pDC, CPoint currentMousePosition);
	void SetCurrentDrawShape(Shapes::Shape *s);
	void DrawSavedShapes(CDC *pDC);
private:
	std::vector<Shapes::Shape*> *history;
	std::vector<Shapes::Shape*> *savedShapes;
	Shapes::Shape *selectionDrawShape;
	CPoint startPoint;
	CPoint endPoint;
};