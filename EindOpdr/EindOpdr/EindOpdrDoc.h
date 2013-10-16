
// EindOpdrDoc.h : interface of the CEindOpdrDoc class
//


#pragma once
#include <vector>
#include "Shape.h"
#include "Rectangle.h"


class CEindOpdrDoc : public CDocument
{
protected: // create from serialization only
	CEindOpdrDoc();
	DECLARE_DYNCREATE(CEindOpdrDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL CEindOpdrDoc::OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL CEindOpdrDoc::OnSaveDocument(LPCTSTR lpszPathName);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CEindOpdrDoc();
	void StartSelection(CPoint startpoint);
	void StopSelection(CPoint endpoint);
	void DrawSelection(CDC *pDC, CPoint currentMousePosition);
	void SetCurrentDrawShape(Shapes::Shape *s);
	void DrawSavedShapes(CDC *pDC);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	std::vector<Shapes::Shape*> *history;
	std::vector<Shapes::Shape*> *savedShapes;
	Shapes::Shape *selectionDrawShape;
	CPoint startPoint;
	CPoint endPoint;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
