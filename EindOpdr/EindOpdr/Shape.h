#pragma once

#include "stdafx.h"
#include <string>
#include <vector>
#include <stdexcept> // std::invalid_argument
#include <memory>

using std::vector;
using std::weak_ptr;
using std::wstring;
using std::ostream;
using std::istream;

namespace Shapes {
	class Shape
	{
	// functions
	public:
		Shape(int id = -1);
		//Shape(const Shapes::Shape &ander);
		//virtual Shape &operator=(const Shapes::Shape &ander);
		virtual ~Shape(void);
		virtual std::shared_ptr<Shape> clone() const = 0;
		virtual void Draw(CDC *pDC) = 0;
		virtual bool IsOn(CPoint point) const;
		virtual std::string toString() const;

		/* virtuele friend operator idoom */
		friend ostream &operator<<(ostream &os, const Shape &s);
		friend istream &operator>>(istream &is, Shape &s);
		
		/* getters/setters */
		virtual void SetPoints(vector<CPoint> points);
		vector<CPoint> GetPoints();
		virtual void SetPen(LOGPEN p);
		void SetLinePen(LOGPEN p);
		void SetText(wstring newstring);
		wstring GetText();
		void SetIsSelected(bool newselected);
		bool GetIsSelected();
		void SetChild(weak_ptr<Shape> s);
		weak_ptr<Shape> GetChild();
		unsigned int GetID();
		void SetID(unsigned int newID);

	protected:
		virtual ostream &print(ostream &o) const;
		virtual istream &read(istream &is);
		virtual void DrawLine(CDC *pDC);

	// values
	protected:
		int id;
		LOGPEN pen;
		LOGPEN selectionPen;
		LOGPEN linePen;
		wstring text;
		vector<CPoint> points; // usually 0 for start and 1 for end.
		weak_ptr<Shape> child; // kind shape in de boom van gelinkte nodes.
		bool isSelected;
	};
	
	/* operator<< en operator>> zijn niet virtueel omdat het friend functions zijn! 
	daarom roepen we een functie van Shape aan die het werkt doet, en virtueel is. */
	inline ostream &operator<<(ostream &o, const Shapes::Shape &s)
	{
		s.print(o); // delegate the work to a polymorphic member function.
		return o;
	}

	inline istream &operator>>(istream &is, Shapes::Shape &s)
	{
		s.read(is); // delegate the work to a polymorphic member function.
		return is;
	}
}
