#pragma once

#include "stdafx.h"
#include "Shape.h"


namespace Shapes {

	class Circle :
		public Shape
	{
	public:
		Circle(int id = -1);
		virtual ~Circle(void);
		void Draw(CDC *pDC);
		void SetPoints(vector<CPoint> points);
		std::shared_ptr<Shape> clone() const;
	};
}