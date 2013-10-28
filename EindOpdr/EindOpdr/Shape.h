#pragma once

#include "stdafx.h"
#include <string>
#include <vector>
#include <stdexcept> // std::invalid_argument
#include <memory>

using std::vector;
using std::weak_ptr;
using std::wstring;

namespace Shapes {
	class Shape
	{
	public:
		Shape();
		Shape(const Shapes::Shape &ander);
		Shape &operator=(const Shapes::Shape &ander);
		virtual ~Shape(void);
		virtual void Draw(CDC *pDC) = 0;
		virtual void SetPoints(vector<CPoint> points);
		vector<CPoint> GetPoints();
		virtual std::string toString() const;
		virtual bool IsOn(CPoint point) const;
		virtual void SetPen(int nPenStyle, int nWidth, COLORREF crColor);
		void SetLinePen(int nPenStyle, int nWidth, COLORREF crColor);
		void SetText(wstring newstring);
		wstring GetText();
		void SetIsSelected(bool newselected);
		bool GetIsSelected();
		void SetChild(weak_ptr<Shape> s);
		weak_ptr<Shape> GetChild();
	// values
	protected:
		CPen pen;
		CPen selectionPen;
		CPen linePen;
		wstring text;
		vector<CPoint> points; // usually 0 for start and 1 for end.
		weak_ptr<Shape> child; // kind shape in de boom van gelinkte nodes.
		bool isSelected;
	// functions
	protected:
		virtual void DrawLine(CDC *pDC);
	};

}
