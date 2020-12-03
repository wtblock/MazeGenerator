/////////////////////////////////////////////////////////////////////////////
// Copyright (c) W. T. Block, All Rights Reserved
/////////////////////////////////////////////////////////////////////////////

#pragma once

/////////////////////////////////////////////////////////////////////////////
class CMazeGeneratorView : public CView
{
// public definitions
public:

// protected data
protected:
	CSize m_sizeClient;
	int m_nPhysicalPageWidth;
	int m_nPhysicalPageHeight;
	int m_nLogicalPageWidth;
	int m_nLogicalPageHeight;

// public properties
public:
	// get a pointer to the document
	CMazeGeneratorDoc* GetDocument() const;
	// get a pointer to the document
	__declspec( property( get = GetDocument ) )
		CMazeGeneratorDoc* Document;

	// dots per inch
	inline int GetDotsPerInch()
	{
		CMazeGeneratorDoc* pDoc = Document;
		return pDoc->DotsPerInch;
	}
	// dots per inch
	__declspec( property( get = GetDotsPerInch ) )
		int DotsPerInch;

	// convert logical co-ordinate value to inches
	float GetLogicalToInches( int nValue )
	{
		CMazeGeneratorDoc* pDoc = Document;
		return pDoc->LogicalToInches[ nValue ];
	}
	// convert logical co-ordinate value to inches
	__declspec( property( get = GetLogicalToInches ) )
		float LogicalToInches[];

	// convert inches to logical co-ordinate value
	int GetInchesToLogical( float fValue )
	{
		CMazeGeneratorDoc* pDoc = Document;
		return pDoc->InchesToLogical[ fValue ];
	}
	// convert inches to logical co-ordinate value
	__declspec( property( get = GetInchesToLogical ) )
		int InchesToLogical[];

	// height of view in pixels
	LONG GetPhysicalViewHeight()
	{
		return m_sizeClient.cy;
	}
	// height of view in pixels
	__declspec( property( get = GetPhysicalViewHeight ) )
		LONG PhysicalViewHeight;

	// width of view in pixels
	LONG GetPhysicalViewWidth()
	{
		return m_sizeClient.cx;
	}
	// width of view in pixels
	__declspec( property( get = GetPhysicalViewWidth ) )
		LONG PhysicalViewWidth;

	// get height of the view in inches
	LONG GetLogicalViewHeight()
	{
		CClientDC dc( this );
		SetDrawDC( &dc );
		CSize sizeLogical = m_sizeClient;
		dc.DPtoLP( &sizeLogical );
		return sizeLogical.cy;
	}
	// get height of the view in inches
	__declspec( property( get = GetLogicalViewHeight ) )
		LONG LogicalViewHeight;

	// get width of the view in inches
	LONG GetLogicalViewWidth()
	{
		CClientDC dc( this );
		SetDrawDC( &dc );
		CSize sizeLogical = m_sizeClient;
		dc.DPtoLP( &sizeLogical );
		return sizeLogical.cx;
	}
	// get width of the view in inches
	__declspec( property( get = GetLogicalViewWidth ) )
		LONG LogicalViewWidth;

	// get height of the view in inches
	inline float GetVisibleHeight()
	{
		return LogicalToInches[ LogicalViewHeight ];
	}
	// get height of the view in inches
	__declspec( property( get = GetVisibleHeight ) )
		float VisibleHeight;

	// get width of the view in inches
	inline float GetVisibleWidth()
	{
		return LogicalToInches[ LogicalViewWidth ];
	}
	// get width of the view in inches
	__declspec( property( get = GetVisibleWidth ) )
		float VisibleWidth;

// protected methods
protected:
	// prepare the device context for printing
	void SetPrintDC
	( 
		CDC* pDC,
		int& nPhysicalWidth, // in pixels         
		int& nPhysicalHeight, // in pixels         	
		int& nLogicalWidth, // in inches * GetMap()
		int& nLogicalHeight // in inches * GetMap()	
	);

	// prepare the device context for drawing and
	// return the logical width
	int SetDrawDC( CDC* pDC );

	// render the maze image
	void Render( CDC* pTargetDC );

	// render the maze image
	void RenderSolution( CDC* pTargetDC );

	// render the maze image
	void RenderResistance( CDC* pTargetDC );

	// generate font characteristics from given font enumeration, where
	// the enumeration is based on Atlas PDF definition
	static void BuildFont
	( 
		int nTextHeight, // text height in pixels
		CFont& font, // generated font
		CString csFace = _T( "ARIAL" ), 
		bool bVertical = false, // vertical orientation
		bool bBold = false, 
		bool bItalic = false,
		BYTE nCharSet = ANSI_CHARSET, // current character set
		bool bFlipX = false, // flip horizontally
		bool bFlipY = false, // flip vertically
		short nUp = -1, // moving up is a negative value
		int nTextWidth = 0 // default width
	);

// public methods
public:

// protected overrides
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint( CDC* pDC, CPrintInfo* pInfo );

// public overrides
public:
	virtual void OnPrepareDC( CDC* pDC, CPrintInfo* pInfo = NULL );
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// public constructor
public:
	CMazeGeneratorView() noexcept;
	virtual ~CMazeGeneratorView();
	DECLARE_DYNCREATE(CMazeGeneratorView)

// Generated message map functions
protected:
	afx_msg BOOL OnEraseBkgnd( CDC* pDC );
	afx_msg void OnSize( UINT nType, int cx, int cy );
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MazeGeneratorView.cpp
inline CMazeGeneratorDoc* CMazeGeneratorView::GetDocument() const
   { return reinterpret_cast<CMazeGeneratorDoc*>(m_pDocument); }
#endif

