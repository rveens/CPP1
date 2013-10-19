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
		Polygon(void);
		~Polygon(void);
		void Draw(CDC *pDC);
		void SetPoints(vector<CPoint> points);
		string toString() const;
	};
}
