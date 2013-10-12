#pragma once

#include "stdafx.h"

namespace Shapes {
	class Shape
	{
	public:
		Shape();
		virtual ~Shape(void);
		virtual void Draw(CDC *pDC) = 0;
		void SetPoints(CPoint start, CPoint end);
	protected:
		CPen pen;
		CPoint start;
		CPoint end;
	};
}
