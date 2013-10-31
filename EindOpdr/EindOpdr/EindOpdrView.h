
// EindOpdrView.h : interface of the CEindOpdrView class
//

#pragma once

namespace viewmode {
	enum viewmode { NORMAL, POLYGON, LINE };
};

class CEindOpdrView : public CView
{
protected: // create from serialization only
	CEindOpdrView();
	DECLARE_DYNCREATE(CEindOpdrView)

// Attributes
public:
	CEindOpdrDoc* GetDocument() const;
private:
	viewmode::viewmode viewmode;
	bool setDrag;
	CPoint lastDragPoint;
	CFont fntTitle1;
	CFont fntTitle2;

// Operations
public:

private:
	void SetCircle();
	void SetEllipse();
	void SetPolygon();
	void SetRectangle();
	void SetSquare();
	void SetLine();
	void ResetChosenShapeExceptPolygon(); // clears the chosen shape to draw (menu vinkjes etc)

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo *pInfo);

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
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnShapeLine();
	afx_msg void OnShapeShapecolor();
	afx_msg void OnShapeLinecolor();
	afx_msg void OnLinesize1();
	afx_msg void OnLinesize2();
	afx_msg void OnLinesize3();
	afx_msg void OnLinestyleNormal();
	afx_msg void OnLinestyleDots();
	afx_msg void OnEditUndo();
	afx_msg void OnToolBarButtonCircle();
	afx_msg void OnToolBarButtonEllipse();
	afx_msg void OnToolBarButtonSquare();
	afx_msg void OnToolBarButtonRectangle();
	afx_msg void OnToolBarButtonPolygon();
	afx_msg void OnToolBarButtonLine();
//	afx_msg void OnMouseLeave();
};

#ifndef _DEBUG  // debug version in EindOpdrView.cpp
inline CEindOpdrDoc* CEindOpdrView::GetDocument() const
   { return reinterpret_cast<CEindOpdrDoc*>(m_pDocument); }
#endif

