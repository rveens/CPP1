#include "stdafx.h"
#include "Shape.h"
#include "ChildView.h"


#pragma once

namespace Shapes {

	class Rectangle :
		public Shape
	{
	public:
		Rectangle(CChildView *view);
		virtual ~Rectangle(void);
		void Draw(CPoint begin, CPoint end);
	};
}