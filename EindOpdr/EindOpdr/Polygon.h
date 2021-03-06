#pragma once
#include "shape.h"
#include <vector>

using std::vector;
using std::string;

namespace Shapes {
	class Polygon :
		public Shape
	{
	public:
		Polygon(int id = -1);
		~Polygon(void);
		void Draw(CDC *pDC);
		void SetPoints(vector<CPoint> points);
		string toString() const;
		bool IsOn(CPoint point) const;
		std::shared_ptr<Shape> clone() const;
	};
}
