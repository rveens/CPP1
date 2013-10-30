#pragma once
#include "Shape.h"

namespace Shapes {
	class Square :
		public Shapes::Shape
	{
	public:
		Square(void);
		~Square(void);
		void Draw(CDC *pDC);
		void SetPoints(vector<CPoint> points);
		std::shared_ptr<Shape> clone() const;
	};
}