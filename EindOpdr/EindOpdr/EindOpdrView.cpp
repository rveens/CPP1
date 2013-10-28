
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
#include "Polygon.h"
#include "InputTextDialog.h"

#include <memory>

using std::unique_ptr;

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
	ON_COMMAND(ID_SHAPE_POLYGON, &CEindOpdrView::OnShapePolygon)
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_SHAPE_LINE, &CEindOpdrView::OnShapeLine)
END_MESSAGE_MAP()

// CEindOpdrView construction/destruction

CEindOpdrView::CEindOpdrView()
{
	// TODO: add construction code here
	this->viewmode = viewmode::NORMAL;
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
	if (this->viewmode == viewmode::POLYGON)
		pDoc->DrawPolygon(pDC);
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

	if (!pDoc->TrySelection(point))
		pDoc->ClearSelections();

	if (this->viewmode == viewmode::POLYGON) {
		pDoc->AddPolygonPoint(point);
		CDC *pDC = GetDC();
		pDoc->DrawPolygon(pDC);
		ReleaseDC(pDC);
	} else
		pDoc->StartSelection(point);

	this->Invalidate();
	CView::OnLButtonDown(nFlags, point);
}

void CEindOpdrView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CEindOpdrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Shapes::Shape *s = pDoc->TrySelection(point);

	if (s) {
		std::unique_ptr<InputTextDialog> dialog = std::unique_ptr<InputTextDialog>(new InputTextDialog());
		dialog->SetValue(s->GetText().c_str());
		dialog->DoModal();

		s->SetText(wstring(dialog->GetValue()));
		s->SetIsSelected(false);
		this->Invalidate();
	}

	CView::OnRButtonDown(nFlags, point);
}

void CEindOpdrView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CMenu *pMenu = AfxGetMainWnd()->GetMenu();
	CEindOpdrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (this->viewmode == viewmode::POLYGON)
		; // niets
	else
		pDoc->StopSelection(point);

	this->Invalidate();

	/* zet alle vinkjes uit */
	pMenu->CheckMenuItem(ID_SHAPE_SQUARE, MF_UNCHECKED | MF_BYCOMMAND);
	pMenu->CheckMenuItem(ID_SHAPE_CIRCLE, MF_UNCHECKED | MF_BYCOMMAND);
	pMenu->CheckMenuItem(ID_SHAPE_SQUARE, MF_UNCHECKED | MF_BYCOMMAND);
	pMenu->CheckMenuItem(ID_SHAPE_ELLIPSE, MF_UNCHECKED | MF_BYCOMMAND);
	pMenu->CheckMenuItem(ID_SHAPE_CIRCLE, MF_UNCHECKED | MF_BYCOMMAND);
	pMenu->CheckMenuItem(ID_SHAPE_RECTANGLE, MF_UNCHECKED | MF_BYCOMMAND);

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

	if (GetKeyState(VK_LBUTTON) & 0x80) {
		if (this->viewmode == viewmode::POLYGON)
			; // niets
		else
			pDoc->DrawSelection(pDC, point);
	}

	ReleaseDC(pDC);

	CView::OnMouseMove(nFlags, point);
}


void CEindOpdrView::OnShapeRectangle()
{
	// TODO: Add your command handler code here
	CMenu *pMenu = AfxGetMainWnd()->GetMenu();
	CEindOpdrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (this->viewmode != viewmode::POLYGON) { // mag alleen als polygonmode uitstaat
		pDoc->SetCurrentDrawShape(std::unique_ptr<Shapes::Shape>(new Shapes::Rectangle()));

		pMenu->CheckMenuItem(ID_SHAPE_SQUARE, MF_UNCHECKED | MF_BYCOMMAND);
		pMenu->CheckMenuItem(ID_SHAPE_CIRCLE, MF_UNCHECKED | MF_BYCOMMAND);
		pMenu->CheckMenuItem(ID_SHAPE_SQUARE, MF_UNCHECKED | MF_BYCOMMAND);
		pMenu->CheckMenuItem(ID_SHAPE_ELLIPSE, MF_UNCHECKED | MF_BYCOMMAND);
		pMenu->CheckMenuItem(ID_SHAPE_CIRCLE, MF_UNCHECKED | MF_BYCOMMAND);

		pMenu->CheckMenuItem(ID_SHAPE_RECTANGLE, MF_CHECKED | MF_BYCOMMAND);
	}
}


void CEindOpdrView::OnShapeCircle()
{
	// TODO: Add your command handler code here
	CMenu *pMenu = AfxGetMainWnd()->GetMenu();
	CEindOpdrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (this->viewmode != viewmode::POLYGON) { // mag alleen als polygonmode uitstaat
		pDoc->SetCurrentDrawShape(std::unique_ptr<Shapes::Shape>(new Shapes::Circle()));

		pMenu->CheckMenuItem(ID_SHAPE_SQUARE, MF_UNCHECKED | MF_BYCOMMAND);
		pMenu->CheckMenuItem(ID_SHAPE_CIRCLE, MF_UNCHECKED | MF_BYCOMMAND);
		pMenu->CheckMenuItem(ID_SHAPE_SQUARE, MF_UNCHECKED | MF_BYCOMMAND);
		pMenu->CheckMenuItem(ID_SHAPE_RECTANGLE, MF_UNCHECKED | MF_BYCOMMAND);
		pMenu->CheckMenuItem(ID_SHAPE_ELLIPSE, MF_UNCHECKED | MF_BYCOMMAND);

		pMenu->CheckMenuItem(ID_SHAPE_CIRCLE, MF_CHECKED | MF_BYCOMMAND);
	}
}


void CEindOpdrView::OnShapeSquare()
{
	// TODO: Add your command handler code here
	CMenu *pMenu = AfxGetMainWnd()->GetMenu();
	CEindOpdrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (this->viewmode != viewmode::POLYGON) { // mag alleen als polygonmode uitstaat
		pDoc->SetCurrentDrawShape(std::unique_ptr<Shapes::Shape>(new Shapes::Square()));
		pMenu->CheckMenuItem(ID_SHAPE_CIRCLE, MF_UNCHECKED | MF_BYCOMMAND);
		pMenu->CheckMenuItem(ID_SHAPE_SQUARE, MF_UNCHECKED | MF_BYCOMMAND);
		pMenu->CheckMenuItem(ID_SHAPE_RECTANGLE, MF_UNCHECKED | MF_BYCOMMAND);
		pMenu->CheckMenuItem(ID_SHAPE_ELLIPSE, MF_UNCHECKED | MF_BYCOMMAND);

		pMenu->CheckMenuItem(ID_SHAPE_SQUARE, MF_CHECKED | MF_BYCOMMAND);
	}
}


void CEindOpdrView::OnShapeEllipse()
{
	// TODO: Add your command handler code here
	CMenu *pMenu = AfxGetMainWnd()->GetMenu();
	CEindOpdrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (!this->viewmode != viewmode::POLYGON) { // mag alleen als polygonmode uitstaat
		pDoc->SetCurrentDrawShape(std::unique_ptr<Shapes::Shape>(new Shapes::Ellipse()));
		pMenu->CheckMenuItem(ID_SHAPE_CIRCLE, MF_UNCHECKED | MF_BYCOMMAND);
		pMenu->CheckMenuItem(ID_SHAPE_SQUARE, MF_UNCHECKED | MF_BYCOMMAND);
		pMenu->CheckMenuItem(ID_SHAPE_RECTANGLE, MF_UNCHECKED | MF_BYCOMMAND);
		pMenu->CheckMenuItem(ID_SHAPE_SQUARE, MF_UNCHECKED | MF_BYCOMMAND);

		pMenu->CheckMenuItem(ID_SHAPE_ELLIPSE, MF_CHECKED | MF_BYCOMMAND);
	}
}


void CEindOpdrView::OnShapePolygon()
{
	// TODO: Add your command handler code here
	CMenu *pMenu = AfxGetMainWnd()->GetMenu();
	CEindOpdrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pMenu->CheckMenuItem(ID_SHAPE_SQUARE, MF_UNCHECKED | MF_BYCOMMAND);
	pMenu->CheckMenuItem(ID_SHAPE_CIRCLE, MF_UNCHECKED | MF_BYCOMMAND);
	pMenu->CheckMenuItem(ID_SHAPE_SQUARE, MF_UNCHECKED | MF_BYCOMMAND);
	pMenu->CheckMenuItem(ID_SHAPE_ELLIPSE, MF_UNCHECKED | MF_BYCOMMAND);
	pMenu->CheckMenuItem(ID_SHAPE_CIRCLE, MF_UNCHECKED | MF_BYCOMMAND);
	pMenu->CheckMenuItem(ID_SHAPE_RECTANGLE, MF_UNCHECKED | MF_BYCOMMAND);

	if (pMenu->GetMenuState(ID_SHAPE_POLYGON, MF_CHECKED) == MF_CHECKED) {
		pMenu->CheckMenuItem(ID_SHAPE_POLYGON, MF_UNCHECKED | MF_BYCOMMAND); // uit
		pDoc->FinishPolygon();
		this->Invalidate();
		this->viewmode = viewmode::NORMAL;

	} else {
		pMenu->CheckMenuItem(ID_SHAPE_POLYGON, MF_CHECKED | MF_BYCOMMAND); // aan
		this->viewmode = viewmode::POLYGON;
		pDoc->SetCurrentDrawShape(std::unique_ptr<Shapes::Shape>(new Shapes::Polygon));
	}
}

void CEindOpdrView::OnShapeLine()
{
	// TODO: Add your command handler code here
}

void CEindOpdrView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	CEindOpdrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//if (nChar == VK_DELETE)
	pDoc->DeleteSelections(); // TODO delete items
	this->Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
