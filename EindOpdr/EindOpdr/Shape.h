#pragma once

#include "stdafx.h"
#include <string>

namespace Shapes {
	class Shape
	{
	public:
		Shape();
		virtual ~Shape(void);
		virtual void Draw(CDC *pDC) = 0;
		void SetPoints(CPoint start, CPoint end);
		friend std::ostream& operator<<(std::ostream& stream, const Shape& shape);
		std::string toString() const;
	protected:
		CPen pen;
		CPoint start;
		CPoint end;
	};
}
