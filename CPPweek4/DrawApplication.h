#pragma once
#include <vector>
#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"

class DrawApplication
{
public:
	DrawApplication(void);
	~DrawApplication(void);
	void StartSelection(CPoint startpoint);
	void StopSelection(CPoint endpoint);
	void DrawSelection(CDC *pDC, CPoint currentMousePosition);
private:
	CPoint startPoint;
	CPoint endPoint;
	std::vector<Shapes::Shape*> *history;
	Shapes::Rectangle *currentDrawShape;
};

