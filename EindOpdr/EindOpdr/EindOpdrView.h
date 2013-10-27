
// EindOpdrView.h : interface of the CEindOpdrView class
//

#pragma once


class CEindOpdrView : public CView
{
protected: // create from serialization only
	CEindOpdrView();
	DECLARE_DYNCREATE(CEindOpdrView)

// Attributes
public:
	CEindOpdrDoc* GetDocument() const;
private:
	BOOL poligonmode;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CEindOpdrView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnShapeRectangle();
	afx_msg void OnShapeCircle();
	afx_msg void OnShapeSquare();
	afx_msg void OnShapeEllipse();
	afx_msg void OnShapePolygon();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in EindOpdrView.cpp
inline CEindOpdrDoc* CEindOpdrView::GetDocument() const
   { return reinterpret_cast<CEindOpdrDoc*>(m_pDocument); }
#endif

