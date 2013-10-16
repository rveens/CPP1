#pragma once

#include "stdafx.h"
#include <string>

namespace Shapes {
	class Shape
	{
	public:
		Shape();
		//Shape(const Shapes::Shape &ander);
		//Shape &operator=(const Shapes::Shape &ander);
		virtual ~Shape(void);
		virtual void Draw(CDC *pDC) = 0;
		void SetPoints(CPoint start, CPoint end);
		std::string Shapes::Shape::toString() const;
	protected:
		CPen pen;
		CPoint start;
		CPoint end;
	};
}
