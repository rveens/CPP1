#pragma once

#include "stdafx.h"
#include "Shape.h"


namespace Shapes {

	class Circle :
		public Shape
	{
	public:
		Circle();
		virtual ~Circle(void);
		void Draw(CDC *pDC);
	};
}