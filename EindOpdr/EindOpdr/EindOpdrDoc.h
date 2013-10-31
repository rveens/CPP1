
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
	void StopSelection();
	void DrawSelection(CDC *pDC, CPoint currentMousePosition);
	void SetCurrentDrawShape(std::unique_ptr<Shapes::Shape> s);
	void DrawSavedShapes(CDC *pDC);
	void DoUndo();

	void AddPolygonPoint(CPoint point);
	void DrawPolygon(CDC *pDC);
	std::weak_ptr<Shapes::Shape> TrySelection(CPoint p);
	void ClearSelections();
	void DeleteSelections();
	bool TryLine(CPoint p);
	void ClearLineTemp();
	void SetShapeOutLineColor(COLORREF c);
	void SetLineColor(COLORREF c);
	void SetOutLineThinkness(int thinkness);
	void SetLineThickness(int thinkness);
	void SetOutLineStyle(int style);
	void SetLineStyle(int style);
	void SetFill(COLORREF b);
	void ChangeShapeColorsSelected();
	void saveCurrentDrawShape();
	void MoveSelectedShapes(CPoint p);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	std::vector<std::shared_ptr<Shapes::Shape>> savedShapes;
	std::vector<std::shared_ptr<Shapes::Shape>> savedShapesForUndo;
	std::unique_ptr<Shapes::Shape> selectionDrawShape;
	CPoint startPoint;
	CPoint endPoint;
	std::vector<CPoint> polygonpoints;
	std::weak_ptr<Shapes::Shape> linetemp;

	// stijlen en kleuren die atm zijn ingesteld.
	COLORREF shapeOutLineColor;
	int shapOutLineStyle;
	int shapeOutLineThickness;
	COLORREF lineColor;
	COLORREF fill;
	int lineStyle;
	int lineThickness;
	unsigned int idCounter;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
