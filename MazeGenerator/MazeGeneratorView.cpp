
// MazeGeneratorView.cpp : implementation of the CMazeGeneratorView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MazeGenerator.h"
#endif

#include "MazeGeneratorDoc.h"
#include "MazeGeneratorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMazeGeneratorView

IMPLEMENT_DYNCREATE(CMazeGeneratorView, CView)

BEGIN_MESSAGE_MAP(CMazeGeneratorView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMazeGeneratorView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMazeGeneratorView construction/destruction

CMazeGeneratorView::CMazeGeneratorView() noexcept
{
	// TODO: add construction code here

}

CMazeGeneratorView::~CMazeGeneratorView()
{
}

BOOL CMazeGeneratorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMazeGeneratorView drawing

void CMazeGeneratorView::OnDraw(CDC* /*pDC*/)
{
	CMazeGeneratorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMazeGeneratorView printing


void CMazeGeneratorView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMazeGeneratorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMazeGeneratorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMazeGeneratorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMazeGeneratorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMazeGeneratorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMazeGeneratorView diagnostics

#ifdef _DEBUG
void CMazeGeneratorView::AssertValid() const
{
	CView::AssertValid();
}

void CMazeGeneratorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMazeGeneratorDoc* CMazeGeneratorView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMazeGeneratorDoc)));
	return (CMazeGeneratorDoc*)m_pDocument;
}
#endif //_DEBUG


// CMazeGeneratorView message handlers
