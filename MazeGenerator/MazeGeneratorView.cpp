/////////////////////////////////////////////////////////////////////////////
// Copyright (c) W. T. Block, All Rights Reserved
/////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MazeGenerator.h"
#endif

#include "MazeGeneratorDoc.h"
#include "MazeGeneratorView.h"
#include "Color.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CMazeGeneratorView, CView)

BEGIN_MESSAGE_MAP(CMazeGeneratorView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMazeGeneratorView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
CMazeGeneratorView::CMazeGeneratorView() noexcept
{
	// TODO: add construction code here

}

/////////////////////////////////////////////////////////////////////////////
CMazeGeneratorView::~CMazeGeneratorView()
{
}

/////////////////////////////////////////////////////////////////////////////
void CMazeGeneratorView::OnSize( UINT nType, int cx, int cy )
{
	CView::OnSize( nType, cx, cy );

	m_sizeClient.cx = cx;
	m_sizeClient.cy = cy;

} // OnSize

/////////////////////////////////////////////////////////////////////////////
// prepare the device context for drawing and
// return the logical width
int CMazeGeneratorView::SetDrawDC
( 
	CDC* pDC
)
{
	CMazeGeneratorDoc* pDoc = Document;
	const float fFactor = 1.0f;
	const float fDocumentWidth = pDoc->Width;
	const int nLogicalWidth = InchesToLogical[ fDocumentWidth / fFactor ];
	const int nPhysicalWidth = PhysicalViewWidth;

	if ( nLogicalWidth != 0 )
	{
		pDC->SetMapMode( MM_ISOTROPIC );
		pDC->SetWindowExt( nLogicalWidth, nLogicalWidth );
		pDC->SetViewportExt( nPhysicalWidth, nPhysicalWidth );
	}
	return nLogicalWidth;
} // SetDrawDC

/////////////////////////////////////////////////////////////////////////////
// prepare the device context for printing
void CMazeGeneratorView::SetPrintDC
( 
	CDC* pDC,
	int& nPhysicalWidth, // in pixels
	int& nPhysicalHeight, // in pixels
	int& nLogicalWidth, // in inches * GetMap()
	int& nLogicalHeight // in inches * GetMap()
)
{
	nPhysicalWidth = pDC->GetDeviceCaps( HORZRES );
	nPhysicalHeight = pDC->GetDeviceCaps( VERTRES );
	const int nPixelsPerInchX = pDC->GetDeviceCaps( LOGPIXELSX );
	const int nPixelsPerInchY = pDC->GetDeviceCaps( LOGPIXELSY );

	const float fPrinterWidth = 
		(float)nPhysicalWidth * DotsPerInch / (float)nPixelsPerInchX;
	const int nPrinterWidth = (int)( fPrinterWidth + 0.5 );
	const float fPrinterHeight = 
		(float)nPhysicalHeight * DotsPerInch / (float)nPixelsPerInchY;
	const int nPrinterHeight = (int)( fPrinterHeight + 0.5 );
	
	// length is always accurate
	nLogicalHeight = nPrinterHeight;

	// create custom MM_HIENGLISH mapping mode:
	//	1. accept coordinates in 1/DotsPerInch inches
	//	2. vertical dimensions increase from top to bottom
	nLogicalWidth = nPrinterWidth;
	pDC->SetMapMode( MM_ISOTROPIC );
	pDC->SetWindowExt( nLogicalWidth, nLogicalHeight );
	pDC->SetViewportExt( nPhysicalWidth, nPhysicalHeight );
} // SetPrintDC

/////////////////////////////////////////////////////////////////////////////
BOOL CMazeGeneratorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
#define _DOUBLE_BUFFER

/////////////////////////////////////////////////////////////////////////////
void CMazeGeneratorView::OnPrepareDC( CDC* pDC, CPrintInfo* pInfo )
{
	if ( pInfo != nullptr ) // printing
	{
		SetPrintDC
		( 
			pDC, 
			m_nPhysicalPageWidth, m_nPhysicalPageHeight, 
			m_nLogicalPageWidth, m_nLogicalPageHeight 
		);
	} else
	{
#ifndef _DOUBLE_BUFFER
		SetDrawDC( pDC );
#endif
	}
} // OnPrepareDC

/////////////////////////////////////////////////////////////////////////////
BOOL CMazeGeneratorView::OnEraseBkgnd( CDC* pDC )
{
#ifdef _DOUBLE_BUFFER
	// double buffer output by creating a memory bitmap and drawing
	// directly to it and then copy the bitmap to the screen to reduce flicker
	// need to prevent the default erase background behavior
	return TRUE;
#else
	return CView::OnEraseBkgnd( pDC );
#endif
} // OnEraseBkgnd

/////////////////////////////////////////////////////////////////////////////
// generate font characteristics from given parameters
void CMazeGeneratorView::BuildFont
(
	int nTextHeight, // text height in pixels
	CFont& font, // generated font
	CString csFace /*= _T( "ARIAL" )*/,
	bool bVertical /*= false*/, // vertical orientation
	bool bBold /*= false*/,
	bool bItalic /*= false*/,
	BYTE nCharSet /*= ANSI_CHARSET*/, // current character set
	bool bFlipX /*= false*/, // flip horizontally
	bool bFlipY /*= false*/, // flip vertically
	short nUp /*= -1*/, // moving up is a negative value
	int nTextWidth /*= 0*/ // default width
)
{
	LOGFONT lf;
	// Populate log font with defaults
	::GetObject( GetStockObject( SYSTEM_FONT ), sizeof( LOGFONT ), &lf );
	int nAngle = bVertical ? nUp * 900 : 0;
	// rotate 180 degrees (happens when printing up-side-down)
	if ( bFlipX && bFlipY ) 
	{
		nAngle += ( nUp * 1800 );
		nAngle = nAngle % 3600;
	}

	// customize our font
	if ( nTextHeight != 0 )
	{
		lf.lfHeight = nTextHeight; 
		if ( nTextWidth != 0 )
		{
			lf.lfWidth = nTextWidth;
		
		} else
		{
			lf.lfWidth = lf.lfHeight * 2 / 5;
		}
	}
	
	lf.lfEscapement = nAngle;
	lf.lfOrientation = nAngle;
		
	lf.lfWeight = bBold ? FW_BOLD : FW_NORMAL;
	lf.lfItalic = bItalic == true;
	lf.lfCharSet = nCharSet;
	_tcscpy( lf.lfFaceName, csFace );
	font.CreateFontIndirect( &lf );

} // BuildFont

/////////////////////////////////////////////////////////////////////////////
// render the maze image
void CMazeGeneratorView::RenderResistance( CDC* pTargetDC )
{
	const int nTA = pTargetDC->SetTextAlign( TA_CENTER | TA_BOTTOM );

	// access the data in the document
	CMazeGeneratorDoc* pDoc = Document;

	// margins of the maze to prevent drawing on the edge of the surface
	const float fMargin = pDoc->Margin;

	// offset to the other cells
	const float fDelta = pDoc->CellWallSize;
	const int nDelta = InchesToLogical[ fDelta ];

	// logical home position
	const int nMarginX = InchesToLogical[ fMargin ];
	const int nMarginY = nMarginX;

	// access to the grid of cells
	CMazeGeneratorDoc::CGrid* pGrid = pDoc->Grid;

	// dimensions of the grid
	const int nRows = pGrid->Rows;
	const int nCols = pGrid->Columns;

	for ( int nRow = 0; nRow < nRows; nRow++ )
	{
		int nY = nMarginY + nRow * nDelta + nDelta;

		for ( int nCol = 0; nCol < nCols; nCol++ )
		{
			int nX = nMarginX + nCol * nDelta + nDelta / 2;

			CMazeGeneratorDoc::CCell* pCell = pGrid->Cell[ nRow ][ nCol ];
			const int nResistance = pCell->Resistance;
			if ( nResistance != 0 )
			{
				CString csText;
				csText.Format( _T( "%d" ), nResistance );
				pTargetDC->TextOut( nX, nY, csText );
			}
		}
	}

	pTargetDC->SetTextAlign( nTA );
} // RenderResistance

/////////////////////////////////////////////////////////////////////////////
// render the maze image
void CMazeGeneratorView::RenderSolution( CDC* pTargetDC )
{
	// access the data in the document
	CMazeGeneratorDoc* pDoc = Document;

	// margins of the maze to prevent drawing on the edge of the surface
	const float fMargin = pDoc->Margin;

	// offset to the other cells
	const float fDelta = pDoc->CellWallSize;
	const int nDelta = InchesToLogical[ fDelta ];

	// logical home position
	const int nMarginX = InchesToLogical[ fMargin ];
	const int nMarginY = nMarginX;

	// access to the grid of cells
	CMazeGeneratorDoc::CGrid* pGrid = pDoc->Grid;

	// dimensions of the grid
	const int nRows = pGrid->Rows;
	const int nCols = pGrid->Columns;

	int nX = nMarginX + nDelta / 2;
	int nY = nMarginY + nDelta / 2;
	pTargetDC->MoveTo( nX, nY );

	CPen penSolved;
	penSolved.CreatePen( PS_SOLID, nDelta / 10, CColor::red );
	pTargetDC->SelectObject( &penSolved );

	const int nExitRow = nRows - 1;
	const int nExitCol = nCols - 1;
	int nRow = 0;
	int nCol = 0;
	CMazeGeneratorDoc::CCell* pCell = pGrid->Cell[ nRow ][ nCol ];

	int nResistance = INT_MAX;

	do
	{
		// prevent backups
		pCell->Resistance = pCell->Resistance + 1;

		const bool bTop = pCell->Top;
		const bool bRight = pCell->Right;
		const bool bBottom = pCell->Bottom;
		const bool bLeft = pCell->Left;

		// resistance of the adjacent cells
		int nTop = INT_MAX;
		int nRight = INT_MAX;
		int nBottom = INT_MAX;
		int nLeft = INT_MAX;

		// adjacent cells
		CMazeGeneratorDoc::CCell* pTop = nullptr;
		CMazeGeneratorDoc::CCell* pRight = nullptr;
		CMazeGeneratorDoc::CCell* pBottom = nullptr;
		CMazeGeneratorDoc::CCell* pLeft = nullptr;

		// looking for the path of least resistance
		if ( bTop == false && nRow != 0 )
		{
			pTop = pGrid->Cell[ nRow - 1 ][ nCol ];
			nTop = pTop->Resistance;
		}

		if ( bRight == false && nCol != nExitCol )
		{
			pRight = pGrid->Cell[ nRow ][ nCol + 1 ];
			nRight = pRight->Resistance;
		}

		if ( bBottom == false && nRow != nExitRow )
		{
			pBottom = pGrid->Cell[ nRow + 1 ][ nCol ];
			nBottom = pBottom->Resistance;
		}

		if ( bLeft == false && nCol != 0 )
		{
			pLeft = pGrid->Cell[ nRow ][ nCol - 1 ];
			nLeft = pLeft->Resistance;
		}

		CMazeGeneratorDoc::CCell::SIDE_TYPE eSide = 
			CMazeGeneratorDoc::CCell::stTop;

		// find the side with the minimum resistance
		nResistance = INT_MAX;
		for ( int nSide = 0; nSide < 4; nSide++ )
		{
			switch ( nSide )
			{
				case 0:
				{
					if ( nBottom != 0 && nBottom < nResistance )
					{
						nResistance = nBottom;
						eSide = CMazeGeneratorDoc::CCell::stBottom;
					}
					break;
				}
				case 1:
				{
					if ( nRight != 0 && nRight < nResistance )
					{
						nResistance = nRight;
						eSide = CMazeGeneratorDoc::CCell::stRight;
					}
					break;
				}
				case 2:
				{
					if ( nTop != 0 && nTop < nResistance )
					{
						nResistance = nTop;
						eSide = CMazeGeneratorDoc::CCell::stTop;
					}
					break;
				}
				case 3:
				{
					if ( nLeft != 0 && nLeft < nResistance )
					{
						nResistance = nLeft;
						eSide = CMazeGeneratorDoc::CCell::stLeft;
					}
					break;
				}
			}
		}

		switch ( eSide )
		{
			case CMazeGeneratorDoc::CCell::stTop:
			{
				pCell = pTop;
				nRow = pCell->Row;
				break;
			}
			case CMazeGeneratorDoc::CCell::stRight:
			{
				pCell = pRight;
				nCol = pCell->Column;
				break;
			}
			case CMazeGeneratorDoc::CCell::stBottom:
			{
				pCell = pBottom;
				nRow = pCell->Row;
				break;
			}
			case CMazeGeneratorDoc::CCell::stLeft:
			{
				pCell = pLeft;
				nCol = pCell->Column;
				break;
			}
		}

		nX = nMarginX + nCol * nDelta + nDelta / 2;
		nY = nMarginY + nRow * nDelta + nDelta / 2;
		pTargetDC->LineTo( nX, nY );

	} while ( nRow != nExitRow || nCol != nExitCol );
} // RenderSolution

/////////////////////////////////////////////////////////////////////////////
// render the maze image
void CMazeGeneratorView::Render( CDC* pTargetDC )
{
	// access the data in the document
	CMazeGeneratorDoc* pDoc = Document;

	// margins of the maze to prevent drawing on the edge of the surface
	const float fMargin = pDoc->Margin;

	// offset to the other cells
	const float fDelta = pDoc->CellWallSize;
	const int nDelta = InchesToLogical[ fDelta ];

	// logical home position
	const int nMarginX = InchesToLogical[ fMargin ];
	const int nMarginY = nMarginX;

	// access to the grid of cells
	CMazeGeneratorDoc::CGrid* pGrid = pDoc->Grid;

	// dimensions of the grid
	const int nRows = pGrid->Rows;
	const int nCols = pGrid->Columns;
	int nY = nMarginY;

	CFont font;
	BuildFont( DotsPerInch / 5, font );
	CFont* pFontOld = pTargetDC->SelectObject( &font );
	COLORREF rgbOld = pTargetDC->SetTextColor( CColor::blue );

	const CString csTitle = pDoc->GetTitle();
	CString csLabel;
	csLabel.Format( _T( "Maze Generator: %s" ), csTitle );

	pTargetDC->TextOut
	(
		nMarginX, nY - DotsPerInch / 5, csLabel
	);

	// create a pen to draw with
	CPen pen;
	pen.CreatePen( PS_SOLID, nDelta / 10, CColor::blue );
	CPen* pPenOld = pTargetDC->SelectObject( &pen );

	// loop through all of the rows of the grid
	for ( int nRow = 0; nRow < nRows; nRow++ )
	{
		// top of the row in logical coordinates
		nY = nMarginY + nRow * nDelta;

		// loop through all of the columns of the grid
		for ( int nCol = 0; nCol < nCols; nCol++ )
		{
			// left of the column in logical coordinates
			const int nX = nMarginX + nCol * nDelta;

			// current cell located at this row and column
			CMazeGeneratorDoc::CCell* pCell =
				pGrid->Cell[ nRow ][ nCol ];

			// if the top of the cell is being drawn
			if ( pCell->Top )
			{
				pTargetDC->MoveTo( nX, nY );
				pTargetDC->LineTo( nX + nDelta, nY );
			}

			// if the right side of the cell is being drawn
			if ( pCell->Right )
			{
				pTargetDC->MoveTo( nX + nDelta, nY );
				pTargetDC->LineTo( nX + nDelta, nY + nDelta );
			}

			// if the bottom of the cell is being drawn
			if ( pCell->Bottom )
			{
				pTargetDC->MoveTo( nX, nY + nDelta );
				pTargetDC->LineTo( nX + nDelta, nY + nDelta );
			}

			// if the left side of the cell is being drawn
			if ( pCell->Left )
			{
				pTargetDC->MoveTo( nX, nY );
				pTargetDC->LineTo( nX, nY + nDelta );
			}
		}
	}

	// if the maze has been solved, draw the solution
	const bool bSolved = pDoc->Solved;
	if ( bSolved )
	{
		//RenderResistance( pTargetDC );
		RenderSolution( pTargetDC );
	}

	pTargetDC->SetTextColor( rgbOld );
	pTargetDC->SelectObject( pFontOld );
	pTargetDC->SelectObject( pPenOld );

} // Render

/////////////////////////////////////////////////////////////////////////////
void CMazeGeneratorView::OnDraw( CDC* pDC )
{
	CMazeGeneratorDoc* pDoc = Document;
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CDC* pTargetDC = pDC;

#ifdef _DOUBLE_BUFFER
	// double buffer output by creating a memory bitmap and drawing
	// directly to it and then copy the bitmap to the screen to reduce flicker
	CBitmap bm;
	bm.CreateCompatibleBitmap( pDC, m_sizeClient.cx, m_sizeClient.cy );

	CDC dcMem;
	dcMem.CreateCompatibleDC( pDC );
	CBitmap* pBmOld = dcMem.SelectObject( &bm );
	dcMem.PatBlt( 0, 0, m_sizeClient.cx, m_sizeClient.cy, WHITENESS );
	pTargetDC = &dcMem;
	int nDcOrg = pTargetDC->SaveDC();
#endif

	SetDrawDC( pTargetDC );
	Render( pTargetDC );

#ifdef _DOUBLE_BUFFER
	pTargetDC->RestoreDC( nDcOrg );

	// output the drawing to the screen in a single bitblit
	pDC->BitBlt( 0, 0, m_sizeClient.cx, m_sizeClient.cy, pTargetDC, 0, 0, SRCCOPY );
	dcMem.SelectObject( pBmOld );
#endif
}

/////////////////////////////////////////////////////////////////////////////
void CMazeGeneratorView::OnPrint( CDC* pDC, CPrintInfo* pInfo )
{
	Render( pDC );

} // OnPrint

/////////////////////////////////////////////////////////////////////////////
void CMazeGeneratorView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

/////////////////////////////////////////////////////////////////////////////
BOOL CMazeGeneratorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

/////////////////////////////////////////////////////////////////////////////
void CMazeGeneratorView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo )
{
	// let the print dialog know
	pInfo->SetMinPage( 1 );
	pInfo->SetMaxPage( 1 );
	const UINT nFromPage = pInfo->GetFromPage();
	const UINT nToPage = pInfo->GetToPage();

} // OnBeginPrinting

/////////////////////////////////////////////////////////////////////////////
void CMazeGeneratorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
} //OnEndPrinting

/////////////////////////////////////////////////////////////////////////////
void CMazeGeneratorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

/////////////////////////////////////////////////////////////////////////////
void CMazeGeneratorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu
	(
		IDR_POPUP_EDIT, point.x, point.y, this, TRUE
	);
#endif
}

#ifdef _DEBUG

/////////////////////////////////////////////////////////////////////////////
void CMazeGeneratorView::AssertValid() const
{
	CView::AssertValid();
}

/////////////////////////////////////////////////////////////////////////////
void CMazeGeneratorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

/////////////////////////////////////////////////////////////////////////////
CMazeGeneratorDoc* CMazeGeneratorView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMazeGeneratorDoc)));
	return (CMazeGeneratorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
