#pragma once

#include "Shape.h"

namespace Shapes {
	class Ellipse
		: public Shape
	{
	public:
		Ellipse(int id = -1);
		~Ellipse(void);
		void Draw(CDC *pDC);
		std::shared_ptr<Shape> clone() const;
	};
}