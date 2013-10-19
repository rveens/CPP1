
// EindOpdrDoc.h : interface of the CEindOpdrDoc class
//


#pragma once
#include <vector>
#include "Shape.h"
#include "Rectangle.h"
#include <memory>


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
	void SetCurrentDrawShape(std::unique_ptr<Shapes::Shape> s);
	void DrawSavedShapes(CDC *pDC);
	void AddPolygonPoint(CPoint point);
	void DrawPolygon(CDC *pDC);
	void FinishPolygon();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	std::vector<std::unique_ptr<Shapes::Shape>> history;
	std::vector<std::unique_ptr<Shapes::Shape>> savedShapes;
	std::unique_ptr<Shapes::Shape> selectionDrawShape;
	CPoint startPoint;
	CPoint endPoint;
	std::vector<CPoint> polygonpoints;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
