/////////////////////////////////////////////////////////////////////////////
// Copyright (c) W. T. Block, All Rights Reserved
/////////////////////////////////////////////////////////////////////////////

#pragma once

#ifdef _DEBUG
	#define new DEBUG_NEW
#endif

#include <vector>
using namespace std;

// template class to manage arrays of pointers to any class
template<class TYPE>
class CCollectionBase
{

// protected data
protected:
	// array of items
	vector<TYPE*> m_arrItems;
	
// construction / destruction
public:
	CCollectionBase()
	{	
	}

	virtual ~CCollectionBase()
	{	
		clear();
	}

// properties
public:
	// array of items
	vector<TYPE*>& GetItems()
	{ 
		return m_arrItems; 
	}
	// array of items
	__declspec( property( get=GetItems )) 
		vector<TYPE*> Items;

	// number of Items
	inline int count()
	{ 
		return (int)m_arrItems.size(); 
	}
	// number of Items
	__declspec( property( get=count ))
		int Count;

	// valid index?
	bool valid( int nIndex )
	{
		const int nItems = Count;
		return ( 0 <= nIndex && nIndex < nItems );
	}
	// valid index?
	__declspec( property( get = valid ))
		bool Valid[];

// methods
public:
	// clear all Items from array
	void clear()
	{
		const int nItems = Count;
		
		// free up the resources in each item
		for ( int nItem = 0; nItem < nItems; nItem++ )
		{
			TYPE* pItem = m_arrItems[ nItem ];
			if ( pItem )
			{
				delete pItem;
				pItem = nullptr;
			}

			m_arrItems[ nItem ] = pItem;
		}

		// empty the array
		m_arrItems.clear();
	}
	
	// resize Item array
	void resize( int nSize )
	{
		const int nItems = Count;
		int nItem;
		
		// if the array size is increased
		if ( nSize > nItems )
		{
			m_arrItems.resize( nSize );
			for ( nItem = nItems; nItem < count(); nItem++ )
			{
				m_arrItems[ nItem ] = new TYPE();
			} 
		} else // free up removed Items
		{
			for ( nItem = nSize; nItem < nItems; nItem++ )
			{
				TYPE* pItem = get( nItem );
				if ( pItem )
				{
					delete pItem;
					pItem = 0;
					set( nItem, pItem );
				}
			}

			m_arrItems.resize( nSize );
		}
	}

	// add a new Item and return its index
	int add()
	{
		TYPE* pItem = new TYPE();
		m_arrItems.push_back( pItem );
		return count() - 1;
	}
	
	// remove an item
	bool remove( int nIndex )
	{
		bool bOK = false;
		if ( valid( nIndex ))
		{
			// free the item's resources
			TYPE* pItem = m_arrItems[ nIndex ];
			if ( pItem )
			{
				delete pItem;
				pItem = 0;
				m_arrItems[ nIndex ] = pItem;
			}

			// remove the item's position from the array
			vector<TYPE*>::iterator pos = m_arrItems.begin();
			pos += nIndex;
			m_arrItems.erase( pos ); 
			bOK = true;	
		}

		return bOK;
	}
	
	// Item at an index, NULL if out of range
	// if the optional release is true, the method copying the pointer
	// is responsible for deleting it and the array's pointer is 
	// set to zero.
	TYPE* get( int nIndex, bool bRelease = false )
	{
		TYPE* pItem = 0;
		if ( valid( nIndex ))
		{
			pItem = m_arrItems[ nIndex ];
			if ( bRelease )
			{
				m_arrItems[ nIndex ] = 0;
			}
		}

		return pItem;
	}
	// Item pointer at an index--will extend the size if necessary,
	// delete the contents of the existing pointer, and copy the
	// given pointer to the location
	void set( int nIndex, TYPE* pItem )
	{	// resize if necessary
		if ( nIndex >= count() )
		{
			resize( nIndex + 1 );
		}
		
		// clean up existing Item at this index
		TYPE* pC = get( nIndex );
		if ( pC )
		{
			delete pC;
			pC = 0;
		}
		
		// put the item in the array
		if ( valid( nIndex ))
		{
			m_arrItems[ nIndex ] = pItem;
		}
	}
	// Item at an index--will extend the size if necessary,
	// and replace the contents of the existing element
	void append( TYPE* pItem )
	{
		m_arrItems.push_back( pItem );
	}
};
