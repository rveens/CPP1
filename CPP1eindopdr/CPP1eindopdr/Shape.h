#pragma once

#include "stdafx.h"

namespace Shapes {
	class Shape
	{
	public:
		Shape();
		virtual ~Shape(void);
		virtual void Draw(CDC *pDC, CPoint start, CPoint end) = 0;
	protected:
		CPen pen;
	};
}
