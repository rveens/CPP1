
// EindOpdrDoc.cpp : implementation of the CEindOpdrDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "EindOpdr.h"
#endif

#include "EindOpdrDoc.h"
#include "Polygon.h"
#include <fstream>
#include <string>
#include <algorithm>

using std::find_if;
using std::for_each;

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CEindOpdrDoc

IMPLEMENT_DYNCREATE(CEindOpdrDoc, CDocument)

BEGIN_MESSAGE_MAP(CEindOpdrDoc, CDocument)
//	ON_COMMAND(ID_SHAPE_SQUARE, &CEindOpdrDoc::OnShapeSquare)
END_MESSAGE_MAP()


// CEindOpdrDoc construction/destruction

CEindOpdrDoc::CEindOpdrDoc() : shapeOutLineColor(RGB(0, 0, 0)), shapOutLineStyle(PS_COSMETIC), shapeOutLineThickness(1),
	lineColor(RGB(0, 0, 0)), lineStyle(PS_DASH), lineThickness(1)
{
	// TODO: add one-time construction code here
	savedShapes = std::vector<std::shared_ptr<Shapes::Shape>>();
	startPoint.x = -1;
	endPoint.x = -1;
}

CEindOpdrDoc::~CEindOpdrDoc()
{
	// Geen delete! smart pointers hahaha
}

BOOL CEindOpdrDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

void CEindOpdrDoc::SetCurrentDrawShape(std::unique_ptr<Shapes::Shape> s)
{
	/* Als je geen smart pointers gebruikt, dan moet je eerst de oude pointer weggooien. met delete. */
	this->selectionDrawShape = std::move(s);
	this->polygonpoints.clear();
	this->startPoint.x = -1;
	this->endPoint.x = -1;
}

void CEindOpdrDoc::StartSelection(CPoint startpoint)
{
	this->startPoint = startpoint;
}

void CEindOpdrDoc::StopSelection(CPoint endpoint)
{
	/* sla de huidige op in de savedShapes lijst. */
	saveCurrentDrawShape();
	this->startPoint.x = -1;
	this->endPoint.x = -1;
}

void CEindOpdrDoc::DrawSelection(CDC *pDC, CPoint currentMousePosition)
{
	vector<CPoint> t;

	if (startPoint.x != -1 && this->selectionDrawShape)
	{
		// Trek vorige vorm over. 2 x XOR geeft oorspronkelijke waarde
		if (endPoint.x != -1) {
			// vector<CPoint> v = { startPoint, endPoint }; ooh ja, stomme microsoft compiler ondersteund dit niet.
			t.push_back(startPoint);
			t.push_back(endPoint);
			this->selectionDrawShape->SetPoints(t);
			this->selectionDrawShape->Draw(pDC);
		}

		// Teken huidige vorm met XOR
		t.clear();
		t.push_back(startPoint);
		t.push_back(currentMousePosition);
		this->selectionDrawShape->SetPoints(t);
		this->selectionDrawShape->Draw(pDC);
		endPoint = currentMousePosition;
	}
}

void CEindOpdrDoc::DrawSavedShapes(CDC *pDC)
{
	std::for_each(std::begin(savedShapes), std::end(savedShapes), [&](std::shared_ptr<Shapes::Shape> s) {
		s->Draw(pDC);
	});
}

// polygon teken functies
void CEindOpdrDoc::AddPolygonPoint(CPoint point)
{
	this->polygonpoints.push_back(point);
}

void CEindOpdrDoc::DrawPolygon(CDC *pDC)
{
	this->selectionDrawShape->SetPoints(this->polygonpoints);
	this->selectionDrawShape->Draw(pDC);
}

std::weak_ptr<Shapes::Shape> CEindOpdrDoc::TrySelection(CPoint p)
{
	std::weak_ptr<Shapes::Shape> shape;

	if (!this->selectionDrawShape && !this->savedShapes.empty()) {
		find_if(begin(savedShapes), end(savedShapes), [&](std::shared_ptr<Shapes::Shape> s) {
			if (s->IsOn(p)) {
				s->SetIsSelected(true);
				shape = s;
				return true;
			}
			return false;
		});
	}

	return shape;
}

void CEindOpdrDoc::ClearSelections()
{
	if (!this->selectionDrawShape && !this->savedShapes.empty()) {
		for_each(begin(savedShapes), end(savedShapes), [&](std::shared_ptr<Shapes::Shape> s) {
			s->SetIsSelected(false);
		});
	}
}

void CEindOpdrDoc::DeleteSelections()
{
	auto remiter = std::remove_if(begin(this->savedShapes), end(this->savedShapes), [&](std::shared_ptr<Shapes::Shape> s) {
		return s->GetIsSelected();
	});
	this->savedShapes.erase(remiter, end(this->savedShapes));
}


void CEindOpdrDoc::ClearLineTemp()
{
	this->linetemp.reset(); // gooi linetemp weg
}

bool CEindOpdrDoc::TryLine(CPoint p)
{
	/* 
	* Kijk naar linetemp:
	* Bestaat hij niet? -> stel hem in.
	* Bestaat hij wel? -> leg de verbinding.
	*/

	auto sp_p1 = this->linetemp.lock(); // krijg ik een reference? niet? dan is deze shared_ptr verlopen.

	if (!sp_p1) { // verlopen? stel in en klaar
		this->linetemp = this->TrySelection(p); // sla linetemp op
		return false;
	} else { // linetemp is een bestaand object
		auto sp_p2 = this->TrySelection(p).lock(); // neem een referentie naar de tweede vorm.

		if (sp_p1 && sp_p2 && (sp_p1 != sp_p2)) { // bestaan beide objecten nog? (en zijn ze niet gelijk aan elkaar)
			// stel een reference in van de een naar de ander...
			// verder moet de ondraw maar goed werken.
			sp_p1->SetChild(sp_p2);
			// Als het goed gegaan is, resetten we de linetemp pointer.
			this->linetemp.reset();
			return true;
		} else
			return false;
	}	
}

/* Getters / Setters */
void CEindOpdrDoc::SetShapeOutLineColor(COLORREF c)
{
	this->shapeOutLineColor = c;
}

COLORREF CEindOpdrDoc::GetShapeOutLineColor()
{
	return this->shapeOutLineColor;
}

void CEindOpdrDoc::SetLineColor(COLORREF c)
{
	this->lineColor = c;
}

COLORREF CEindOpdrDoc::GetLineColor()
{
	return this->lineColor;
}

void CEindOpdrDoc::ChangeShapeColorsSelected()
{
	for_each(begin(this->savedShapes), end(this->savedShapes), [&](std::shared_ptr<Shapes::Shape> s){
		if (s->GetIsSelected()) {
			s->SetPen(this->shapOutLineStyle, this->shapeOutLineThickness, this->shapeOutLineColor);
			s->SetLinePen(this->lineStyle, this->lineThickness, this->lineColor);
		}
	});
}

/* private functies */
void CEindOpdrDoc::saveCurrentDrawShape()
{
	if (this->selectionDrawShape) {
		/* verander de pen naar de uiteindelijke kleur */
		selectionDrawShape->SetPen(this->shapOutLineStyle, this->shapeOutLineThickness, this->shapeOutLineColor);
		selectionDrawShape->SetLinePen(this->lineStyle, this->lineThickness, this->lineColor);
		savedShapes.push_back(std::move(selectionDrawShape));
	}
	/* selectiondraw shape is nu null, omdat move is uitgevoerd. */
}

// CEindOpdrDoc serialization

void CEindOpdrDoc::Serialize(CArchive& ar)
{
	// niks!
}

BOOL CEindOpdrDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	std::wstring s_wstr(lpszPathName);
	std::ifstream ifs (s_wstr, std::ifstream::in);
	if (ifs) {
		//ifs >> ...;
		ifs.close();
		return TRUE;
	} else
		return FALSE;
}

BOOL CEindOpdrDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnSaveDocument(lpszPathName))
		return FALSE;

	std::wstring s_wstr(lpszPathName);

	std::ofstream ofs (s_wstr, std::ofstream::out);
	if (ofs) {
		ofs << this->selectionDrawShape->toString();
		ofs.close();
		return TRUE;
	} else
		return FALSE;
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CEindOpdrDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CEindOpdrDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CEindOpdrDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CEindOpdrDoc diagnostics

#ifdef _DEBUG
void CEindOpdrDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEindOpdrDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG