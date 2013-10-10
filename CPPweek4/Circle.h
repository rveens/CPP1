#include "stdafx.h"
#include "Shape.h"
#include "ChildView.h"

#pragma once

namespace Shapes {

	class Circle :
		public Shape
	{
	public:
		Circle(CChildView *view);
		virtual ~Circle(void);
		void Draw(CPoint begin, CPoint end);
	};
}