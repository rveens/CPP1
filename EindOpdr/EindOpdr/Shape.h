#pragma once

#include "stdafx.h"
#include <string>
#include <vector>
#include <stdexcept> // std::invalid_argument

using std::vector;

namespace Shapes {
	class Shape
	{
	public:
		Shape();
		Shape(const Shapes::Shape &ander);
		Shape &operator=(const Shapes::Shape &ander);
		virtual ~Shape(void);
		virtual void Draw(CDC *pDC) = 0;
		virtual void SetPoints(vector<CPoint> points);
		virtual std::string Shapes::Shape::toString() const;
	protected:
		CPen pen;
		vector<CPoint> points; // usually 0 for start and 1 for end.
	};
}
