
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "Mainfrm.h"
#include "CPP1eindopdr.h"
#include "ChildView.h"
#include "Circle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	dapp = new DrawApplication();
}

CChildView::~CChildView()
{
	delete dapp;
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_SHAPE_RECTANGLE, &CChildView::OnShapeRectangle)
	ON_COMMAND(ID_SHAPE_CIRCLE, &CChildView::OnShapeCircle)
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CDC *pDC = GetDC();

	pDC->LineTo(50, 50);

	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
}

// View implementation file

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	dapp->StartSelection(point);

	CWnd::OnLButtonDown(nFlags, point);
}

void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	dapp->StopSelection(point);

	CWnd::OnLButtonUp(nFlags, point);
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	CDC *pDC = GetDC();

	if (GetKeyState(VK_LBUTTON) & 0x80)
		dapp->DrawSelection(pDC, point);

	ReleaseDC(pDC);

	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnShapeRectangle()
{
	dapp->SetCurrentDrawShape(new Shapes::Rectangle());
}


void CChildView::OnShapeCircle()
{
	dapp->SetCurrentDrawShape(new Shapes::Circle());
}
