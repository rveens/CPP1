
#pragma once

#include "stdafx.h"
#include "Shape.h"

namespace Shapes {

	class Rectangle :
		public Shape
	{
	public:
		Rectangle();
		virtual ~Rectangle(void);
		void Draw(CDC *pDC);
		std::shared_ptr<Shape> clone() const;
	};
}