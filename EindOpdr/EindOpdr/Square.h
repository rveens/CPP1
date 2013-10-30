#pragma once
#include "Shape.h"

namespace Shapes {
	class Square :
		public Shapes::Shape
	{
	public:
		Square(int id = -1);
		~Square(void);
		void Draw(CDC *pDC);
		void SetPoints(vector<CPoint> points);
		std::shared_ptr<Shape> clone() const;
	};
}