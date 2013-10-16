
// EindOpdrDoc.cpp : implementation of the CEindOpdrDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "EindOpdr.h"
#endif

#include "EindOpdrDoc.h"
#include <fstream>
#include <string>

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CEindOpdrDoc

IMPLEMENT_DYNCREATE(CEindOpdrDoc, CDocument)

BEGIN_MESSAGE_MAP(CEindOpdrDoc, CDocument)
END_MESSAGE_MAP()


// CEindOpdrDoc construction/destruction

CEindOpdrDoc::CEindOpdrDoc()
{
	// TODO: add one-time construction code here
	history = std::vector<std::unique_ptr<Shapes::Shape>>();
	savedShapes = std::vector<std::unique_ptr<Shapes::Shape>>();
	startPoint.x = -1;
	endPoint.x = -1;

	// Set default selection shape
	this->selectionDrawShape = std::unique_ptr<Shapes::Shape>(new Shapes::Rectangle());
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

void CEindOpdrDoc::SetCurrentDrawShape(Shapes::Shape *s)
{
	/* Als je geen smart pointers gebruikt, dan moet je eerst de oude pointer weggooien. */
	this->selectionDrawShape = s;
}

void CEindOpdrDoc::StartSelection(CPoint startpoint)
{
	this->startPoint = startpoint;
}

void CEindOpdrDoc::StopSelection(CPoint endpoint)
{
	// TODO save drawing points into a shape variable.

	/* sla de huidige op in de savedShapes lijst. */
	savedShapes.push_back(selectionDrawShape);

	/* Zet de huidige selectie pointer op null. */
	this->selectionDrawShape = nullptr;

	this->startPoint.x = -1;
	this->endPoint.x = -1;
}

void CEindOpdrDoc::DrawSelection(CDC *pDC, CPoint currentMousePosition)
{
	if (startPoint.x != -1 && this->selectionDrawShape)
	{
		// Trek vorige vorm over. 2 x XOR geeft oorspronkelijke waarde
		if (endPoint.x != -1) {
			this->selectionDrawShape->SetPoints(startPoint, endPoint);
			this->selectionDrawShape->Draw(pDC);
		}

		// Teken huidige vorm met XOR
		this->selectionDrawShape->SetPoints(startPoint, currentMousePosition);
		this->selectionDrawShape->Draw(pDC);
		endPoint = currentMousePosition;
	}
}

void CEindOpdrDoc::DrawSavedShapes(CDC *pDC)
{
	std::vector<std::unique_ptr<Shapes::Shape>>::iterator it, end;
	
	end = this->savedShapes.end();

	for (it = this->savedShapes.begin(); it != end; ++it)
		(*it)->Draw(pDC); // TODO tekenwaardes opslaan bij shape.
}



// CEindOpdrDoc serialization

void CEindOpdrDoc::Serialize(CArchive& ar)
{
	
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
		return FALSE;;

	return 0;
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


// CEindOpdrDoc commands
