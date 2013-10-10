#include "ChildView.h"

#pragma once

namespace Shapes {
	class Shape
	{
	public:
		Shape(CChildView *view);
		virtual ~Shape(void);
		virtual void Draw(CPoint start, CPoint end) = 0;
	protected:
		CPoint start;
		CPoint end;
		CPen pen;
		CChildView *view;
	};
}
