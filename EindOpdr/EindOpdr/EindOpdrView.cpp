
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
	ON_COMMAND(ID_SHAPE_SHAPECOLOR, &CEindOpdrView::OnShapeShapecolor)
	ON_COMMAND(ID_SHAPE_LINECOLOR, &CEindOpdrView::OnShapeLinecolor)
	ON_COMMAND(ID_LINESIZE_1, &CEindOpdrView::OnLinesize1)
	ON_COMMAND(ID_LINESIZE_2, &CEindOpdrView::OnLinesize2)
	ON_COMMAND(ID_LINESIZE_3, &CEindOpdrView::OnLinesize3)
	ON_COMMAND(ID_LINESTYLE_NORMAL, &CEindOpdrView::OnLinestyleNormal)
	ON_COMMAND(ID_LINESTYLE_DOTS, &CEindOpdrView::OnLinestyleDots)
	ON_COMMAND(ID_EDIT_UNDO, &CEindOpdrView::OnEditUndo)
//	ON_WM_MOUSELEAVE()
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

	/* probeer de selectie weg te gooien als er geen object wordt aangeklikt. */
	auto sp = pDoc->TrySelection(point);
	if (!sp.lock()) { // we krijgen geen lock? dan hebben we niks kunnen vinden op de positie
		pDoc->ClearSelections(); // gooi selecties weg,
		pDoc->ClearLineTemp(); // en clear de linetemp.
	}

	if (this->viewmode == viewmode::POLYGON) {
		pDoc->AddPolygonPoint(point);
		CDC *pDC = GetDC();
		pDoc->DrawPolygon(pDC);
		ReleaseDC(pDC);
	} else if (this->viewmode == viewmode::NORMAL)
		pDoc->StartSelection(point);
	else if (this->viewmode == viewmode::LINE)
		if (pDoc->TryLine(point)) { // is het gelukt om een lijn te verbinden?
			pDoc->ClearSelections(); // selecties weghalen
			/* en viewmode weer terug! */
			this->viewmode = viewmode::NORMAL;
			CMenu *pMenu = AfxGetMainWnd()->GetMenu();
			pMenu->CheckMenuItem(ID_SHAPE_LINE, MFS_UNCHECKED | MF_BYCOMMAND);
		}

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

	auto sp = pDoc->TrySelection(point).lock();

	if (sp) {
		std::unique_ptr<InputTextDialog> dialog = std::unique_ptr<InputTextDialog>(new InputTextDialog());
		dialog->SetValue(sp->GetText().c_str());
		dialog->DoModal();

		sp->SetText(wstring(dialog->GetValue()));
		sp->SetIsSelected(false);
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
	else if (this->viewmode == viewmode::NORMAL)
		pDoc->StopSelection();

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

	SetCapture();               //  Capture the mouse input
	CRect wndRect;
	GetWindowRect(&wndRect);
	ScreenToClient(&wndRect);

	if (wndRect.PtInRect(point))	
	{
		if (GetKeyState(VK_LBUTTON) & 0x80) {
			if (this->viewmode == viewmode::POLYGON)
				; // niets
			else
				pDoc->DrawSelection(pDC, point);
		}
	} else {
		if (GetKeyState(VK_LBUTTON) & 0x80) {
			pDoc->StopSelection();
			this->Invalidate();
		}
		ReleaseCapture();
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

	if (this->viewmode == viewmode::NORMAL) { // mag alleen als polygonmode uitstaat
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

	if (this->viewmode == viewmode::NORMAL) { // mag alleen als polygonmode uitstaat
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

	if (this->viewmode == viewmode::NORMAL) { // mag alleen als polygonmode uitstaat
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

	if (this->viewmode == viewmode::NORMAL) { // mag alleen als polygonmode uitstaat
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

	if (this->viewmode == viewmode::POLYGON) {
		pMenu->CheckMenuItem(ID_SHAPE_POLYGON, MF_UNCHECKED | MF_BYCOMMAND); // uit
		pDoc->saveCurrentDrawShape();
		this->Invalidate();
		this->viewmode = viewmode::NORMAL;
	} else if(this->viewmode == viewmode::NORMAL) {
		pMenu->CheckMenuItem(ID_SHAPE_POLYGON, MF_CHECKED | MF_BYCOMMAND); // aan
		this->viewmode = viewmode::POLYGON;
		pDoc->SetCurrentDrawShape(std::unique_ptr<Shapes::Shape>(new Shapes::Polygon));
	}
}

void CEindOpdrView::OnShapeLine()
{
	// TODO: Add your command handler code here
	CMenu *pMenu = AfxGetMainWnd()->GetMenu();
	CEindOpdrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (this->viewmode == viewmode::NORMAL) {
		// zet alle vinkjes uit
		pMenu->CheckMenuItem(ID_SHAPE_SQUARE, MF_UNCHECKED | MF_BYCOMMAND);
		pMenu->CheckMenuItem(ID_SHAPE_CIRCLE, MF_UNCHECKED | MF_BYCOMMAND);
		pMenu->CheckMenuItem(ID_SHAPE_SQUARE, MF_UNCHECKED | MF_BYCOMMAND);
		pMenu->CheckMenuItem(ID_SHAPE_ELLIPSE, MF_UNCHECKED | MF_BYCOMMAND);
		pMenu->CheckMenuItem(ID_SHAPE_CIRCLE, MF_UNCHECKED | MF_BYCOMMAND);
		pMenu->CheckMenuItem(ID_SHAPE_RECTANGLE, MF_UNCHECKED | MF_BYCOMMAND);
		pMenu->CheckMenuItem(ID_SHAPE_POLYGON, MF_UNCHECKED | MF_BYCOMMAND); // ook polygon

		// zet lijn aan
		pMenu->CheckMenuItem(ID_SHAPE_LINE, MFS_CHECKED | MF_BYCOMMAND);
		// selecties gaan weg als we in line mode gaan
		pDoc->ClearSelections();
		this->Invalidate();

		this->viewmode = viewmode::LINE;
	} else if (this->viewmode == viewmode::LINE) {
		this->viewmode = viewmode::NORMAL;
		pMenu->CheckMenuItem(ID_SHAPE_LINE, MFS_UNCHECKED | MF_BYCOMMAND);
	}
}

void CEindOpdrView::OnShapeShapecolor()
{
	// TODO: Add your command handler code here
	CEindOpdrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	/* Maak een kleurendialoog */
	CMFCColorDialog cd;

	if (cd.DoModal() == IDOK) 
		pDoc->SetShapeOutLineColor(cd.GetColor());
	pDoc->ChangeShapeColorsSelected();
	this->Invalidate();
}

void CEindOpdrView::OnShapeLinecolor()
{
	// TODO: Add your command handler code here
	CEindOpdrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	/* Maak een kleurendialoog */
	CMFCColorDialog cd;

	if (cd.DoModal() == IDOK) 
		pDoc->SetLineColor(cd.GetColor());
	pDoc->ChangeShapeColorsSelected();
	this->Invalidate();
}

void CEindOpdrView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	CEindOpdrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (nChar == VK_DELETE) {
		pDoc->DeleteSelections();
		this->Invalidate();
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CEindOpdrView::OnLinesize1()
{
	// TODO: Add your command handler code here
	CEindOpdrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->SetOutLineThinkness(1);
	pDoc->SetLineThickness(1);
	pDoc->ChangeShapeColorsSelected();
}


void CEindOpdrView::OnLinesize2()
{
	// TODO: Add your command handler code here
	CEindOpdrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->SetOutLineThinkness(2);
	pDoc->SetLineThickness(2);
	pDoc->ChangeShapeColorsSelected();
}


void CEindOpdrView::OnLinesize3()
{
	// TODO: Add your command handler code here
	CEindOpdrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->SetOutLineThinkness(3);
	pDoc->SetLineThickness(3);
	pDoc->ChangeShapeColorsSelected();
}


void CEindOpdrView::OnLinestyleNormal()
{
	// TODO: Add your command handler code here
	CEindOpdrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->SetOutLineStyle(PS_SOLID);
	pDoc->SetLineStyle(PS_SOLID);
	pDoc->ChangeShapeColorsSelected();
}


void CEindOpdrView::OnLinestyleDots()
{
	// TODO: Add your command handler code here
	CEindOpdrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->SetOutLineStyle(PS_DOT);
	pDoc->SetLineStyle(PS_DOT);
	pDoc->ChangeShapeColorsSelected();
}


void CEindOpdrView::OnEditUndo()
{
	// TODO: Add your command handler code here
	CEindOpdrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->DoUndo();
	this->Invalidate();
}