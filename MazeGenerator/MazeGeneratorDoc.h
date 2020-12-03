/////////////////////////////////////////////////////////////////////////////
// Copyright (c) W. T. Block, All Rights Reserved
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include "CollectionBase.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////
class CMazeGeneratorDoc : public CDocument
{
// public definitions
public:
	///////////////////////////////////////////////////////////////////////////
	// definition of a maze cell
	class CCell
	{
	// public definitions
	public:
		typedef enum SIDE_TYPE
		{
			stTop = 0,
			stRight,
			stBottom,
			stLeft,

		} SIDE_TYPE;

	// protected data
	protected:
		// row number of this cell
		int m_nRow;

		// column number of this cell
		int m_nColumn;

		// the cell has been visited
		bool m_bVisited;

		// the top side is turned on
		bool m_bTop;

		// the right side is turned on
		bool m_bRight;

		// the bottom side is turned on
		bool m_bBottom;

		// the left side is turned on
		bool m_bLeft;

		// the resistance is based on the number of cell visits
		// and is used to find the path of least resistance
		int m_nResistance;

	// public properties
	public:
		// row number of this cell
		inline int GetRow()
		{
			return m_nRow;
		}
		// row number of this cell
		inline void SetRow( int value )
		{
			m_nRow = value;
		}
		// row number of this cell
		__declspec( property( get = GetRow, put = SetRow ) )
			int Row;

		// column number of this cell
		inline int GetColumn()
		{
			return m_nColumn;
		}
		// column number of this cell
		inline void SetColumn( int value )
		{
			m_nColumn = value;
		}
		// column number of this cell
		__declspec( property( get = GetColumn, put = SetColumn ) )
			int Column;

		// the cell has been visited
		inline bool GetVisited()
		{
			return m_bVisited;
		}
		// the cell has been visited
		inline void SetVisited( bool value )
		{
			m_bVisited = value;
		}
		// the cell has been visited
		__declspec( property( get = GetVisited, put = SetVisited ) )
			bool Visited;

		// the top side is turned on
		inline bool GetTop()
		{
			return m_bTop;
		}
		// the top side is turned on
		inline void SetTop( bool value )
		{
			m_bTop = value;
		}
		// the top side is turned on
		__declspec( property( get = GetTop, put = SetTop ) )
			bool Top;

		// the right side is turned on
		inline bool GetRight()
		{
			return m_bRight;
		}
		// the right side is turned on
		inline void SetRight( bool value )
		{
			m_bRight = value;
		}
		// the right side is turned on
		__declspec( property( get = GetRight, put = SetRight ) )
			bool Right;

		// the bottom side is turned on
		inline bool GetBottom()
		{
			return m_bBottom;
		}
		// the bottom side is turned on
		inline void SetBottom( bool value )
		{
			m_bBottom = value;
		}
		// the bottom side is turned on
		__declspec( property( get = GetBottom, put = SetBottom ) )
			bool Bottom;

		// the left side is turned on
		inline bool GetLeft()
		{
			return m_bLeft;
		}
		// the left side is turned on
		inline void SetLeft( bool value )
		{
			m_bLeft = value;
		}
		// the left side is turned on
		__declspec( property( get = GetLeft, put = SetLeft ) )
			bool Left;

		// the resistance is based on the number of cell visits
		// and is used to find the path of least resistance
		inline int GetResistance()
		{
			return m_nResistance;
		}
		// the resistance is based on the number of cell visits
		// and is used to find the path of least resistance
		inline void SetResistance( int value )
		{
			m_nResistance = value;
		}
		// the resistance is based on the number of cell visits
		// and is used to find the path of least resistance
		__declspec( property( get = GetResistance, put = SetResistance ) )
			int Resistance;

	// protected methods
	protected:

	// public methods
	public:

	// protected overrides
	protected:

	// public overrides
	public:

	// public constructor
	public:
		CCell()
		{
			Row = -1;
			Column = -1;
			Visited = false;
			Top = true;
			Right = true;
			Bottom = true;
			Left = true;
			Resistance = 0;
		}
		virtual ~CCell()
		{
		}
	};

	///////////////////////////////////////////////////////////////////////////
	// a collection of cells that make up a single row
	class CRow
	{
	// public definitions
	public:

	// protected data
	protected:
		CCollectionBase<CCell> Row;

	// public properties
	public:
		// number of columns
		inline int GetColumns()
		{
			return (int)Row.Count;
		}
		// number of columns
		inline void SetColumns( int value )
		{
			Row.clear();
			while ( Row.Count < value )
			{
				Row.add();
			}
		}
		// number of columns
		__declspec( property( get = GetColumns, put = SetColumns ))
			int Columns;

		// get a pointer to a cell
		inline CCell* GetCell( int nColumn )
		{
			CCell* value = nullptr;
			if ( Row.Valid[ nColumn ] )
			{
				value = Row.Items[ nColumn ];
			}
			return value;
		}
		// get a pointer to a cell
		__declspec( property( get = GetCell ))
			CCell* Cell[];

	// protected methods
	protected:

	// public methods
	public:

	// protected overrides
	protected:

	// public overrides
	public:

	// public constructor
	public:
		CRow()
		{
		}
		virtual ~CRow()
		{
		}
	};

	///////////////////////////////////////////////////////////////////////////
	// a collection of maze rows that make up a grid of cells
	class CGrid
	{
	// public definitions
	public:

	// protected data
	protected:
		CCollectionBase<CRow> Grid;

	// public properties
	public:
		// number of rows
		inline int GetRows()
		{
			return (int)Grid.Count;
		}
		// number of rows
		inline void SetRows( int value )
		{
			Grid.clear();
			while ( Grid.Count < value )
			{
				Grid.add();
			}
		}
		// number of rows
		__declspec( property( get = GetRows, put = SetRows ) )
			int Rows;

		// number of columns
		inline int GetColumns()
		{
			int value = 0;
			if ( Rows > 0 )
			{
				CRow* pRow = Row[ 0 ];
				if ( pRow != nullptr )
				{
					value = pRow->Columns;
				}
			}
			return value;
		}
		// number of columns
		inline void SetColumns( int value )
		{
			for ( CRow* pRow : Grid.Items )
			{
				pRow->Columns = value;
			}
		}
		// number of columns
		__declspec( property( get = GetColumns, put = SetColumns ) )
			int Columns;

		// get a pointer to a row
		inline CRow* GetRow( int nRow )
		{
			CRow* value = nullptr;
			if ( Grid.Valid[ nRow ] )
			{
				value = Grid.Items[ nRow ];
			}
			return value;
		}
		// get a pointer to a row
		__declspec( property( get = GetRow ) )
			CRow* Row[];

		// get a pointer to a cell
		inline CCell* GetCell( int nRow, int nColumn )
		{
			CCell* value = nullptr;
			if ( Grid.Valid[ nRow ] )
			{
				CRow* pRow = Row[ nRow ];
				if ( pRow != nullptr )
				{
					value = pRow->Cell[ nColumn ];
				}
			}
			return value;
		}
		// get a pointer to a cell
		__declspec( property( get = GetCell ) )
			CCell* Cell[][];

	// protected methods
	protected:

	// public methods
	public:

	// protected overrides
	protected:

	// public overrides
	public:

	// public constructor
	public:
		CGrid()
		{
		}
		virtual ~CGrid()
		{
		}

	};

// protected data
protected:
	// current date and time
	COleDateTime m_oDT;

	// grid of cells
	CGrid m_grid;

	// the grid has a solution
	bool m_bSolved;

// public properties
public:
	// the grid has a solution
	inline bool GetSolved()
	{
		return m_bSolved;
	}
	// the grid has a solution
	inline void SetSolved( bool value )
	{
		m_bSolved = value;
	}
	// the grid has a solution
	__declspec( property( get = GetSolved, put = SetSolved ))
		bool Solved;

	// current date and time
	inline COleDateTime GetDateAndTime()
	{
		return m_oDT;
	}
	// current date and time
	inline void SetDateAndTime( COleDateTime VALUE )
	{
		m_oDT = VALUE;
	}
	// current date and time
	__declspec( property( get = GetDateAndTime, put = SetDateAndTime ))
		COleDateTime DateAndTime;

	// dots per inch
	inline int GetDotsPerInch()
	{
		return 1000;
	}
	// dots per inch
	__declspec( property( get = GetDotsPerInch ) )
		int DotsPerInch;

	// convert logical co-ordinate value to inches
	float GetLogicalToInches( int nValue )
	{
		return ( float( nValue ) / DotsPerInch );
	}
	// convert logical co-ordinate value to inches
	__declspec( property( get = GetLogicalToInches ) )
		float LogicalToInches[];

	// convert inches to logical co-ordinate value
	int GetInchesToLogical( float fValue )
	{
		return int( fValue * DotsPerInch );
	}
	// convert inches to logical co-ordinate value
	__declspec( property( get = GetInchesToLogical ) )
		int InchesToLogical[];

	// cell wall size
	inline float GetCellWallSize()
	{
		return 0.25f;
	}
	// cell wall size
	__declspec( property( get = GetCellWallSize ) )
		float CellWallSize;

	// margin of view
	inline float GetMargin()
	{
		return 0.25f;
	}
	// margin of view
	__declspec( property( get = GetMargin ) )
		float Margin;

	// height of view
	inline float GetHeight()
	{
		return 11.0f;
	}
	// height of view
	__declspec( property( get = GetHeight ) )
		float Height;

	// width of view
	inline float GetWidth()
	{
		return 8.5f;
	}
	// width of view
	__declspec( property( get = GetWidth ) )
		float Width;

	// number of rows
	inline int GetRows()
	{
		int value = 0;

		// margin at the top and bottom of maze
		const float fMargin = Margin;

		// adjust the height of the maze by removing the margins
		const float fHeight = Height - 2 * fMargin;

		// height of a cell
		const float fCellWallSize = CellWallSize;

		// number of cells that will fit into the height
		value = int( fHeight / fCellWallSize );

		return value;
	}
	// number of rows
	__declspec( property( get = GetRows ) )
		int Rows;

	// number of columns
	inline int GetColumns()
	{
		int value = 0;

		// margin at the top and bottom of maze
		const float fMargin = Margin;

		// adjust the width of the maze by removing the margins
		const float fWidth = Width - 2 * fMargin;

		// width of a cell
		const float fCellWallSize = CellWallSize;

		// number of cells that will fit into the width
		value = int( fWidth / fCellWallSize );

		return value;
	}
	// number of columns
	__declspec( property( get = GetColumns ) )
		int Columns;

	// pointer to the grid
	inline CGrid* GetGrid()
	{
		return &m_grid;
	}
	// pointer to the m_grid
	__declspec( property( get = GetGrid ) )
		CGrid* Grid;

// protected methods
protected:
	// create document using the DateAndTime property to define a random seed
	void CreateDocument();

	// visit the cells and build the maze
	// Given a current cell coordinates as a parameter,
	// Mark the current cell as visited
	// While the current cell has any unvisited neighbor cells
	//   Choose one of the unvisited neighbors
	//   Remove the wall between the current cell and the chosen cell
	//   Invoke the routine recursively for a chosen cell
	bool VisitCells( int nRow, int nCol );

	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

// public methods
public:

// protected overrides
protected:

// public overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// public constructor
public:
	CMazeGeneratorDoc() noexcept;
	virtual ~CMazeGeneratorDoc();
	DECLARE_DYNCREATE(CMazeGeneratorDoc)

	afx_msg void OnEditSolve();
	afx_msg void OnUpdateEditSolve( CCmdUI *pCmdUI );
};
