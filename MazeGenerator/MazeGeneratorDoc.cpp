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

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

///////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CMazeGeneratorDoc, CDocument)

BEGIN_MESSAGE_MAP(CMazeGeneratorDoc, CDocument)
	ON_COMMAND( ID_RUN, &CMazeGeneratorDoc::OnEditSolve )
	ON_UPDATE_COMMAND_UI( ID_RUN, &CMazeGeneratorDoc::OnUpdateEditSolve )
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////
CMazeGeneratorDoc::CMazeGeneratorDoc() noexcept
{
	Solved = false;
}

///////////////////////////////////////////////////////////////////////////
CMazeGeneratorDoc::~CMazeGeneratorDoc()
{
}

///////////////////////////////////////////////////////////////////////////
	// create document
void CMazeGeneratorDoc::CreateDocument()
{
	COleDateTime oDT = DateAndTime;

	const int nHour = oDT.GetHour();
	const int nMin = oDT.GetMinute();
	const int nSec = oDT.GetSecond();

	const int nRand = nHour * 3600 + nMin * 60 + nSec;
	srand( nRand );

	CString csFile;
	csFile.Format( _T( "%02d%02d%02d.maze" ), nHour, nMin, nSec );
	this->SetTitle( csFile );

	// calculate the number of rows and columns
	const int nRows = Rows;
	const int nCols = Columns;

	// create the rows and columns
	Grid->Rows = nRows;
	Grid->Columns = nCols;

	// mark the cell's row and column property
	for ( int nRow = 0; nRow < nRows; nRow++ )
	{
		for ( int nCol = 0; nCol < nCols; nCol++ )
		{
			CMazeGeneratorDoc::CCell* pCell =
				Grid->Cell[ nRow ][ nCol ];
			pCell->Row = nRow;
			pCell->Column = nCol;
		}
	}

	// the entry cell
	CMazeGeneratorDoc::CCell* pEntry =
		Grid->Cell[ 0 ][ 0 ];

	// the exit cell
	CMazeGeneratorDoc::CCell* pExit =
		Grid->Cell[ nRows - 1 ][ nCols - 1 ];

	// open the door for the entry
	pEntry->Top = false;

	// open the door for the exit
	pExit->Bottom = false;

	// generate the maze
	VisitCells( 0, 0 );

} // CreateDocument

///////////////////////////////////////////////////////////////////////////
BOOL CMazeGeneratorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// create a random seed from time
	COleDateTime oDT = COleDateTime::GetCurrentTime();
	DateAndTime = oDT;

	CreateDocument();

	return TRUE;
} // OnNewDocument

///////////////////////////////////////////////////////////////////////////
// visit the cells and build the maze
// Given a current cell as a parameter,
// Mark the current cell as visited
// While the current cell has any unvisited neighbor cells
//   Choose one of the unvisited neighbors
//   Remove the wall between the current cell and the chosen cell
//   Invoke the routine recursively for a chosen cell
bool CMazeGeneratorDoc::VisitCells( int nRow, int nCol )
{
	CGrid* pGrid = Grid;
	const int nRows = pGrid->Rows;
	const int nCols = pGrid->Columns;
	CCell* pCurrent = pGrid->Cell[ nRow ][ nCol ];
	pCurrent->Visited = true;

	// return value is true when all sides of the cell have been visited
	bool value = false;

	// randomly choose the starting side
	CCell::SIDE_TYPE eSide = CCell::SIDE_TYPE( rand() % 4 );
	CCell::SIDE_TYPE eNext = eSide;
	do
	{
		switch ( eNext )
		{
			case CCell::stTop:
			{
				// we cannot go above the top row
				if ( nRow == 0 )
				{
					break;
				}

				CCell* pCell = pGrid->Cell[ nRow - 1 ][ nCol ];
				if ( pCell->Visited )
				{
					break;
				}

				// turn off the sides so they do not draw
				pCurrent->Top = false;
				pCell->Bottom = false;

				VisitCells( nRow - 1, nCol );
				break;
			}
			case CCell::stRight:
			{
				// we cannot go beyond the last column
				if ( nCol == nCols - 1 )
				{
					break;
				}

				CCell* pCell = pGrid->Cell[ nRow ][ nCol + 1 ];
				if ( pCell->Visited )
				{
					break;
				}

				// turn off the sides so they do not draw
				pCurrent->Right = false;
				pCell->Left = false;

				VisitCells( nRow, nCol + 1 );
				break;
			}
			case CCell::stBottom:
			{
				// we cannot go below the bottom row
				if ( nRow == nRows - 1 )
				{
					break;
				}

				// get the cell below
				CCell* pCell = pGrid->Cell[ nRow + 1 ][ nCol ];
				if ( pCell->Visited )
				{
					break;
				}

				// turn off the sides that do not draw
				pCurrent->Bottom = false;
				pCell->Top = false;

				VisitCells( nRow + 1, nCol );
				break;
			}
			case CCell::stLeft:
			{
				// we cannot go beyond the first column
				if ( nCol == 0 )
				{
					break;
				}

				// get the cell to the left
				CCell* pCell = pGrid->Cell[ nRow ][ nCol - 1 ];
				if ( pCell->Visited )
				{
					break;
				}

				// turn off the sides so they do not draw
				pCurrent->Left = false;
				pCell->Right = false;
				
				VisitCells( nRow, nCol - 1 );
			}
		}

		// go to the next side
		int nTemp = int( eNext );
		nTemp = ( nTemp + 1 ) % 4;
		eNext = CCell::SIDE_TYPE( nTemp );

		// set the return value to true when we get back to the 
		// original side
		value = eNext == eSide;

	} while ( value != true );

	return value;
} // VisitCells

///////////////////////////////////////////////////////////////////////////
void CMazeGeneratorDoc::Serialize(CArchive& ar)
{
	CString csTitle;
	if (ar.IsStoring())
	{
		// read the title
		csTitle = GetTitle();

		// write the title into the document
		ar.WriteString( csTitle );
	}
	else
	{
		// create a random seed from time
		COleDateTime oDT = COleDateTime::GetCurrentTime();

		// read the title from the archive
		ar.ReadString( csTitle );

		// set the new title
		SetTitle( csTitle );

		// parse the time of day from the title
		const CString csSecond = csTitle.Mid( 4, 2 );
		const CString csMinute = csTitle.Mid( 2, 2 );
		const CString csHour = csTitle.Left( 2 );
		
		// convert to time of day
		const int nHour = _tstol( csHour );
		const int nMinute = _tstol( csMinute );
		const int nSecond = _tstol( csSecond );

		// change the current time to the time of the document
		oDT.SetTime( nHour, nMinute, nSecond );

		// record the date and time property
		DateAndTime = oDT;

		// create the document based on the time of day
		CreateDocument();
	}
} // Serialize

///////////////////////////////////////////////////////////////////////////
#ifdef SHARED_HANDLERS

///////////////////////////////////////////////////////////////////////////
// Support for thumbnails
void CMazeGeneratorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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

///////////////////////////////////////////////////////////////////////////
// Support for Search Handlers
void CMazeGeneratorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

///////////////////////////////////////////////////////////////////////////
void CMazeGeneratorDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

///////////////////////////////////////////////////////////////////////////
#endif // SHARED_HANDLERS
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG

///////////////////////////////////////////////////////////////////////////
void CMazeGeneratorDoc::AssertValid() const
{
	CDocument::AssertValid();
} // AssertValid

///////////////////////////////////////////////////////////////////////////
void CMazeGeneratorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
} // Dump

#endif //_DEBUG

///////////////////////////////////////////////////////////////////////////
void CMazeGeneratorDoc::OnEditSolve()
{
	CGrid* pGrid = Grid;
	const int nRows = pGrid->Rows;
	const int nCols = pGrid->Columns;
	const int nExitRow = nRows - 1;
	const int nExitCol = nCols - 1;
	int nRow = 0;
	int nCol = 0;
	int nResistance;

	CCell* pCell = pGrid->Cell[ nRow ][ nCol ];
	do 
	{
		nResistance = pCell->Resistance + 1;
		pCell->Resistance = nResistance;

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
		CCell* pTop = nullptr;
		CCell* pRight = nullptr;
		CCell* pBottom = nullptr;
		CCell* pLeft = nullptr;

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

		CCell::SIDE_TYPE eSide = CCell::stTop;

		// find the side with the minimum resistance;
		nResistance = INT_MAX;
		for ( int nSide = 0; nSide < 4; nSide++ )
		{
			switch ( nSide )
			{
				case 0:
				{
					if ( nBottom < nResistance )
					{
						nResistance = nBottom;
						eSide = CCell::stBottom;
					}
					break;
				}
				case 1:
				{
					if ( nRight < nResistance )
					{
						nResistance = nRight;
						eSide = CCell::stRight;
					}
					break;
				}
				case 2:
				{
					if ( nTop < nResistance )
					{
						nResistance = nTop;
						eSide = CCell::stTop;
					}
					break;
				}
				case 3:
				{
					if ( nLeft < nResistance )
					{
						nResistance = nLeft;
						eSide = CCell::stLeft;
					}
					break;
				}
			}
		}

		switch ( eSide )
		{
			case CCell::stTop:
			{
				pCell = pTop;
				nRow = pCell->Row;
				break;
			}
			case CCell::stRight:
			{
				pCell = pRight;
				nCol = pCell->Column;
				break;
			}
			case CCell::stBottom:
			{
				pCell = pBottom;
				nRow = pCell->Row;
				break;
			}
			case CCell::stLeft:
			{
				pCell = pLeft;
				nCol = pCell->Column;
				break;
			}
		}
	} while ( nRow != nExitRow || nCol != nExitCol );

	pCell = pGrid->Cell[ nExitRow ][ nExitCol ];
	nResistance = pCell->Resistance + 1;
	pCell->Resistance = nResistance;

	Solved = true;

	// force the view to repaint
	POSITION pos = GetFirstViewPosition();
	while ( pos )
	{
		CView* pView = GetNextView( pos );
		if ( pView->IsKindOf( RUNTIME_CLASS( CMazeGeneratorView ) ) )
		{
			pView->Invalidate();
			break;
		}
	}

} // OnEditSolve

///////////////////////////////////////////////////////////////////////////
void CMazeGeneratorDoc::OnUpdateEditSolve( CCmdUI *pCmdUI )
{
	pCmdUI->Enable( Solved != true );

} // OnUpdateEditSolve

///////////////////////////////////////////////////////////////////////////
