
#pragma once

#include "stdafx.h"
#include "Shape.h"

namespace Shapes {

	class Rectangle :
		public Shape
	{
	public:
		Rectangle(int id = -1);
		virtual ~Rectangle(void);
		void Draw(CDC *pDC);
		std::shared_ptr<Shape> clone() const;
	};
}