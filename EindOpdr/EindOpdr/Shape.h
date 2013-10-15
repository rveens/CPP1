#pragma once

#include "stdafx.h"
#include <string>

namespace Shapes {
	class Shape : public CObject
	{
		
	public:
		Shape();
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
