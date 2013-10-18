
// EindOpdrView.cpp : implementation of the CEindOpdrView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "EindOpdr.h"
#endif

#include "EindOpdrDoc.h"
#include "EindOpdrView.h"
#include "Shape.h"
#include "Circle.h"
#include "Square.h"
#include "Ellipse.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEindOpdrView

IMPLEMENT_DYNCREATE(CEindOpdrView, CView)

BEGIN_MESSAGE_MAP(CEindOpdrView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_SHAPE_RECTANGLE, &CEindOpdrView::OnShapeRectangle)
	ON_COMMAND(ID_SHAPE_CIRCLE, &CEindOpdrView::OnShapeCircle)
	ON_COMMAND(ID_SHAPE_SQUARE, &CEindOpdrView::OnShapeSquare)
	ON_COMMAND(ID_SHAPE_ELLIPSE, &CEindOpdrView::OnShapeEllipse)
END_MESSAGE_MAP()

// CEindOpdrView construction/destruction

CEindOpdrView::CEindOpdrView()
{
	// TODO: add construction code here

}

CEindOpdrView::~CEindOpdrView()
{
}

BOOL CEindOpdrView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CEindOpdrView drawing

void CEindOpdrView::OnDraw(CDC* pDC)
{
	CEindOpdrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	pDoc->DrawSavedShapes(pDC);

	ReleaseDC(pDC);
}


// CEindOpdrView printing

BOOL CEindOpdrView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEindOpdrView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEindOpdrView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CEindOpdrView diagnostics

#ifdef _DEBUG
void CEindOpdrView::AssertValid() const
{
	CView::AssertValid();
}

void CEindOpdrView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEindOpdrDoc* CEindOpdrView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEindOpdrDoc)));
	return (CEindOpdrDoc*)m_pDocument;
}
#endif //_DEBUG


// CEindOpdrView message handlers


void CEindOpdrView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CEindOpdrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->StartSelection(point);

	CView::OnLButtonDown(nFlags, point);
}


void CEindOpdrView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CEindOpdrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->StopSelection(point);

	CView::OnLButtonUp(nFlags, point);
}


void CEindOpdrView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CEindOpdrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CDC *pDC = GetDC();

	if (GetKeyState(VK_LBUTTON) & 0x80)
		pDoc->DrawSelection(pDC, point);

	ReleaseDC(pDC);

	CView::OnMouseMove(nFlags, point);
}


void CEindOpdrView::OnShapeRectangle()
{
	// TODO: Add your command handler code here
	CEindOpdrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->SetCurrentDrawShape(std::unique_ptr<Shapes::Shape>(new Shapes::Rectangle()));
}


void CEindOpdrView::OnShapeCircle()
{
	// TODO: Add your command handler code here
	CEindOpdrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->SetCurrentDrawShape(std::unique_ptr<Shapes::Shape>(new Shapes::Circle()));
}


void CEindOpdrView::OnShapeSquare()
{
	// TODO: Add your command handler code here
	CEindOpdrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->SetCurrentDrawShape(std::unique_ptr<Shapes::Shape>(new Shapes::Square()));
}


void CEindOpdrView::OnShapeEllipse()
{
	// TODO: Add your command handler code here
	CEindOpdrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->SetCurrentDrawShape(std::unique_ptr<Shapes::Shape>(new Shapes::Ellipse()));
}
