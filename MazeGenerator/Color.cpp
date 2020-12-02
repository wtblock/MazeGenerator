/////////////////////////////////////////////////////////////////////////////
//	Datei  : Color.cpp
//	Projekt: Farbverwaltung
//	Inhalt : CColor Implementierung
//	Datum  : 10.01.1999
//	Autor  : Christian Rodemeyer
//	Hinweis: © 1999 by Christian Rodemeyer
//	         Info über HLS Konvertierungsfunktion
//	         - Foley and Van Dam: "Fundamentals of Interactive Computer Graphics"  
//	         - MSDN: 'HLS Color Spaces'
//	         - MSDN: 'Converting Colors Between RGB and HLS' 
/////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "Color.h"

/////////////////////////////////////////////////////////////////////////////
// CColor: Implementierung
/////////////////////////////////////////////////////////////////////////////
const CColor::DNamedColor CColor::m_namedColor[CColor::numNamedColors] =
{
  {aliceblue            , _T( "aliceblue" )},
  {antiquewhite         , _T( "antiquewhite" )},
  {aqua                 , _T( "aqua" )},
  {aquamarine           , _T( "aquamarine" )},
  {azure                , _T( "azure" )},
  {beige                , _T( "beige" )},
  {bisque               , _T( "bisque" )},
  {black                , _T( "black" )},
  {blanchedalmond       , _T( "blanchedalmond" )},
  {blue                 , _T( "blue" )},
  {blueviolet           , _T( "blueviolet" )},
  {brown                , _T( "brown" )},
  {burlywood            , _T( "burlywood" )},
  {cadetblue            , _T( "cadetblue" )},
  {chartreuse           , _T( "chartreuse" )},
  {chocolate            , _T( "chocolate" )},
  {coral                , _T( "coral" )},
  {cornflower           , _T( "cornflower" )},
  {cornsilk             , _T( "cornsilk" )},
  {crimson              , _T( "crimson" )},
  {cyan                 , _T( "cyan" )},
  {darkblue             , _T( "darkblue" )},
  {darkcyan             , _T( "darkcyan" )},
  {darkgoldenrod        , _T( "darkgoldenrod" )},
  {darkgray             , _T( "darkgray" )},
  {darkgreen            , _T( "darkgreen" )},
  {darkkhaki            , _T( "darkkhaki" )},
  {darkmagenta          , _T( "darkmagenta" )},
  {darkolivegreen       , _T( "darkolivegreen" )},
  {darkorange           , _T( "darkorange" )},
  {darkorchid           , _T( "darkorchid" )},
  {darkred              , _T( "darkred" )},
  {darksalmon           , _T( "darksalmon" )},
  {darkseagreen         , _T( "darkseagreen" )},
  {darkslateblue        , _T( "darkslateblue" )},
  {darkslategray        , _T( "darkslategray" )},
  {darkturquoise        , _T( "darkturquoise" )},
  {darkviolet           , _T( "darkviolet" )},
  {deeppink             , _T( "deeppink" )},
  {deepskyblue          , _T( "deepskyblue" )},
  {dimgray              , _T( "dimgray" )},
  {dodgerblue           , _T( "dodgerblue" )},
  {firebrick            , _T( "firebrick" )},
  {floralwhite          , _T( "floralwhite" )},
  {forestgreen          , _T( "forestgreen" )},
  {fuchsia              , _T( "fuchsia" )},
  {gainsboro            , _T( "gainsboro" )},
  {ghostwhite           , _T( "ghostwhite" )},
  {gold                 , _T( "gold" )},
  {goldenrod            , _T( "goldenrod" )},
  {gray                 , _T( "gray" )},
  {green                , _T( "green" )},
  {greenyellow          , _T( "greenyellow" )},
  {honeydew             , _T( "honeydew" )},
  {hotpink              , _T( "hotpink" )},
  {indianred            , _T( "indianred" )},
  {indigo               , _T( "indigo" )},
  {ivory                , _T( "ivory" )},
  {khaki                , _T( "khaki" )},
  {lavender             , _T( "lavender" )},
  {lavenderblush        , _T( "lavenderblush" )},
  {lawngreen            , _T( "lawngreen" )},
  {lemonchiffon         , _T( "lemonchiffon" )},
  {lightblue            , _T( "lightblue" )},
  {lightcoral           , _T( "lightcoral" )},
  {lightcyan            , _T( "lightcyan" )},
  {lightgoldenrodyellow , _T( "lightgoldenrodyellow" )},
  {lightgreen           , _T( "lightgreen" )},
  {lightgrey            , _T( "lightgrey" )},
  {lightpink            , _T( "lightpink" )},
  {lightsalmon          , _T( "lightsalmon" )},
  {lightseagreen        , _T( "lightseagreen" )},
  {lightskyblue         , _T( "lightskyblue" )},
  {lightslategray       , _T( "lightslategray" )},
  {lightsteelblue       , _T( "lightsteelblue" )},
  {lightyellow          , _T( "lightyellow" )},
  {lime                 , _T( "lime" )},
  {limegreen            , _T( "limegreen" )},
  {linen                , _T( "linen" )},
  {magenta              , _T( "magenta" )},
  {maroon               , _T( "maroon" )},
  {mediumaquamarine     , _T( "mediumaquamarine" )},
  {mediumblue           , _T( "mediumblue" )},
  {mediumorchid         , _T( "mediumorchid" )},
  {mediumpurple         , _T( "mediumpurple" )},
  {mediumseagreen       , _T( "mediumseagreen" )},
  {mediumslateblue      , _T( "mediumslateblue" )},
  {mediumspringgreen    , _T( "mediumspringgreen" )},
  {mediumturquoise      , _T( "mediumturquoise" )},
  {mediumvioletred      , _T( "mediumvioletred" )},
  {midnightblue         , _T( "midnightblue" )},
  {mintcream            , _T( "mintcream" )},
  {mistyrose            , _T( "mistyrose" )},
  {moccasin             , _T( "moccasin" )},
  {navajowhite          , _T( "navajowhite" )},
  {navy                 , _T( "navy" )},
  {oldlace              , _T( "oldlace" )},
  {olive                , _T( "olive" )},
  {olivedrab            , _T( "olivedrab" )},
  {orange               , _T( "orange" )},
  {orangered            , _T( "orangered" )},
  {orchid               , _T( "orchid" )},
  {palegoldenrod        , _T( "palegoldenrod" )},
  {palegreen            , _T( "palegreen" )},
  {paleturquoise        , _T( "paleturquoise" )},
  {palevioletred        , _T( "palevioletred" )},
  {papayawhip           , _T( "papayawhip" )},
  {peachpuff            , _T( "peachpuff" )},
  {peru                 , _T( "peru" )},
  {pink                 , _T( "pink" )},
  {plum                 , _T( "plum" )},
  {powderblue           , _T( "powderblue" )},
  {purple               , _T( "purple" )},
  {red                  , _T( "red" )},
  {rosybrown            , _T( "rosybrown" )},
  {royalblue            , _T( "royalblue" )},
  {saddlebrown          , _T( "saddlebrown" )},
  {salmon               , _T( "salmon" )},
  {sandybrown           , _T( "sandybrown" )},
  {seagreen             , _T( "seagreen" )},
  {seashell             , _T( "seashell" )},
  {sienna               , _T( "sienna" )},
  {silver               , _T( "silver" )},
  {skyblue              , _T( "skyblue" )},
  {slateblue            , _T( "slateblue" )},
  {slategray            , _T( "slategray" )},
  {snow                 , _T( "snow" )},
  {springgreen          , _T( "springgreen" )},
  {steelblue            , _T( "steelblue" )},
  {tan                  , _T( "tan" )},
  {teal                 , _T( "teal" )},
  {thistle              , _T( "thistle" )},
  {tomato               , _T( "tomato" )},
  {turquoise            , _T( "turquoise" )},
  {violet               , _T( "violet" )},
  {wheat                , _T( "wheat" )},
  {white                , _T( "white" )},
  {whitesmoke           , _T( "whitesmoke" )},
  {yellow               , _T( "yellow" )},
  {yellowgreen          , _T( "yellowgreen" )},
  {moneygreen           , _T( "moneygreen" )},
  {spanishwhite         , _T("spanishwhite")},
  {mediumgray           , _T("mediumgray")},
  {midgray              , _T("midgray")},
  {midcyan              , _T("midcyan")},
  {grayishgreen         , _T("grayishgreen")}
};

/////////////////////////////////////////////////////////////////////////////
CColor::CColor(COLORREF cr, bool bIndex ) 
	: m_bIsRGB(true), m_bIsHLS(false), m_colorref(cr)
{	NamedColorsIndexed( false );
	if ( !bIndex )
	{	return;
	}
	IndexNamedColors();
}

/////////////////////////////////////////////////////////////////////////////
// find a named color -- returns none if not found
COLORREF CColor::FindNamedColor( LPCTSTR pcszColor )
{	if ( !NamedColorsIndexed())
	{	IndexNamedColors();
	}
	CString csColor( pcszColor );
	csColor.Replace( _T( " " ), _T( "" ));
	csColor.MakeLower();

	COLORREF rgb = none;
	const POS_NAME_RGB posEnd = m_mapColors.end();
	const POS_NAME_RGB pos = m_mapColors.find( csColor );
	if ( pos != posEnd )
	{	rgb = pos->second;
	}
	return rgb;
} // FindNamedColor

/////////////////////////////////////////////////////////////////////////////
// color from string will do a test for leading "0x" and do FromString
// conversion if true, otherwise and named lookup will attempt to 
// resolve the color, and finally if all else fails, a standard
// numeric hex conversion of the string will be attempted.
COLORREF CColor::ColorFromString( LPCTSTR pcszColor )
{	CString csColor( pcszColor );
	
	COLORREF rgb = none;
	// leading "0x" indicates a format of "0xRRGGBB"
	if ( csColor.Left( 2 ) == _T( "0x" ))
	{	rgb = CColor::FromString( pcszColor );
	} else
	{	rgb = FindNamedColor( pcszColor );
		if ( rgb == none )
		{	// try to convert the text as straight hex numeric
			// based on format of "00BBGGRR"
			TCHAR* pEnd = 0;
			rgb = _tcstol( csColor, &pEnd, 16 );
		}
	}
	return rgb;
} // 

/////////////////////////////////////////////////////////////////////////////
// index the named colors
int CColor::IndexNamedColors()
{	if ( NamedColorsIndexed())
	{	return IndexedColors();
	}
	NamedColorsIndexed( true );

	// add the named colors to an index
	for ( int nColor = 0; nColor < numNamedColors; nColor++ )
	{	PAIR_NAME_RGB pairColor
		(	m_namedColor[ nColor ].name, 
			m_namedColor[ nColor ].color 
		);
		addColor( pairColor );
	}
	return IndexedColors();
} // IndexNamedColors

/////////////////////////////////////////////////////////////////////////////
LPCTSTR CColor::GetNameFromIndex(int i)
{
  ASSERT(0 <= i && i < numNamedColors);
  return m_namedColor[i].name;
}

/////////////////////////////////////////////////////////////////////////////
CColor CColor::GetColorFromIndex(int i)
{
  ASSERT(0 <= i && i < numNamedColors);
  return m_namedColor[i].color;
}

/////////////////////////////////////////////////////////////////////////////
CColor CColor::FromString(LPCTSTR pcColor)
{
  CColor t;
  if( !t.SetString(pcColor) )
  {
	  return CColor(RGB(1,1,1));
  }
  return t;
}

/////////////////////////////////////////////////////////////////////////////
CColor CColor::FromName(LPCTSTR pcColor, bool bConvertHex )
{	
	CString csColor( pcColor );

	// remove all the white space inside the string
	int iS = 0;
	for( int iC = 0; iC < csColor.GetLength(); iC++ )
	{
		csColor.SetAt( iC, ' ' );
		if( pcColor[iC] == ' ' ) continue;
		csColor.SetAt(iS++, pcColor[iC] );
	}
	csColor.TrimRight();  

	csColor.MakeLower();
	CColor t(RGB(1,1,1));
	int nColors = GetNumNames();
	for ( int nColor = 0; nColor < nColors; nColor++ )
	{	if ( csColor == m_namedColor[ nColor ].name )
		{	return GetColorFromIndex( nColor );
		}
	}
	if( bConvertHex ) 
	{
		return CColor::FromString( pcColor );
	}
	return t;
}

/////////////////////////////////////////////////////////////////////////////
CColor::operator COLORREF() const
{
  const_cast<CColor*>(this)->ToRGB();
  return m_colorref;
}

/////////////////////////////////////////////////////////////////////////////
// RGB
/////////////////////////////////////////////////////////////////////////////
void CColor::SetRed(int red)
{
  ASSERT(0 <= red && red <= 255);
  ToRGB();
  m_color[c_red] = static_cast<unsigned char>(red);
  m_bIsHLS = false;
}

/////////////////////////////////////////////////////////////////////////////
void CColor::SetGreen(int green)
{
  ASSERT(0 <= green && green <= 255);
  ToRGB();
  m_color[c_green] = static_cast<unsigned char>(green);
  m_bIsHLS = false;
}

/////////////////////////////////////////////////////////////////////////////
void CColor::SetBlue(int blue)
{
  ASSERT(0 <= blue && blue <= 255);
  ToRGB();
  m_color[c_blue] = static_cast<unsigned char>(blue);
  m_bIsHLS = false;
}

/////////////////////////////////////////////////////////////////////////////
void CColor::SetRGB(int red, int blue, int green)
{
  ASSERT(0 <= red && red <= 255);
  ASSERT(0 <= green && green <= 255);
  ASSERT(0 <= blue && blue <= 255);

  m_color[c_red]   = static_cast<unsigned char>(red);
  m_color[c_green] = static_cast<unsigned char>(green);
  m_color[c_blue]  = static_cast<unsigned char>(blue);
  m_bIsHLS = false;
  m_bIsRGB = true;
}

/////////////////////////////////////////////////////////////////////////////
int CColor::GetRed() const
{
  const_cast<CColor*>(this)->ToRGB();
  return m_color[c_red];
}

/////////////////////////////////////////////////////////////////////////////
int CColor::GetGreen() const
{
  const_cast<CColor*>(this)->ToRGB();
  return m_color[c_green];
}

/////////////////////////////////////////////////////////////////////////////
int CColor::GetBlue() const
{
  const_cast<CColor*>(this)->ToRGB();
  return m_color[c_blue];
}

/////////////////////////////////////////////////////////////////////////////
// HSL
/////////////////////////////////////////////////////////////////////////////
void CColor::SetHue(float hue)
{
  ASSERT(hue >= 0.0 && hue <= 360.0);

  ToHLS();
  m_hue = hue;
  m_bIsRGB = false;
}

/////////////////////////////////////////////////////////////////////////////
void CColor::SetSaturation(float saturation)
{
  ASSERT(saturation >= 0.0 && saturation <= 1.0); // 0.0 ist undefiniert

  ToHLS();
  m_saturation = saturation;
  m_bIsRGB = false;
}

/////////////////////////////////////////////////////////////////////////////
void CColor::SetLuminance(float luminance)
{
  ASSERT(luminance >= 0.0 && luminance <= 1.0);

  ToHLS();
  m_luminance = luminance;
  m_bIsRGB = false;
}

/////////////////////////////////////////////////////////////////////////////
void CColor::SetHLS(float hue, float luminance, float saturation)
{
  ASSERT(hue >= 0.0 && hue <= 360.0);
  ASSERT(luminance >= 0.0 && luminance <= 1.0);
  ASSERT(saturation >= 0.0 && saturation <= 1.0); // 0.0 ist undefiniert

  m_hue = hue;
  m_luminance = luminance;
  m_saturation = saturation;
  m_bIsRGB = false;
  m_bIsHLS = true;
}

/////////////////////////////////////////////////////////////////////////////
float CColor::GetHue() const
{
  const_cast<CColor*>(this)->ToHLS();
  return m_hue;
}

/////////////////////////////////////////////////////////////////////////////
float CColor::GetSaturation() const
{
  const_cast<CColor*>(this)->ToHLS();
  return m_saturation;
}

/////////////////////////////////////////////////////////////////////////////
float CColor::GetLuminance() const
{
  const_cast<CColor*>(this)->ToHLS();
  return m_luminance;
}

/////////////////////////////////////////////////////////////////////////////
// Konvertierung
/////////////////////////////////////////////////////////////////////////////
void CColor::ToHLS() 
{
  if (!m_bIsHLS)
  {
    // Konvertierung
    unsigned char minval = min(m_color[c_red], min(m_color[c_green], m_color[c_blue]));
    unsigned char maxval = max(m_color[c_red], max(m_color[c_green], m_color[c_blue]));
    float mdiff  = float(maxval) - float(minval);
    float msum   = float(maxval) + float(minval);
   
    m_luminance = msum / 510.0f;

    if (maxval == minval) 
    {
      m_saturation = 0.0f;
      m_hue = 0.0f; 
    }   
    else 
    { 
      float rnorm = (maxval - m_color[c_red]  ) / mdiff;      
      float gnorm = (maxval - m_color[c_green]) / mdiff;
      float bnorm = (maxval - m_color[c_blue] ) / mdiff;   

      m_saturation = (m_luminance <= 0.5f) ? (mdiff / msum) : (mdiff / (510.0f - msum));

      if (m_color[c_red]   == maxval) m_hue = 60.0f * (6.0f + bnorm - gnorm);
      if (m_color[c_green] == maxval) m_hue = 60.0f * (2.0f + rnorm - bnorm);
      if (m_color[c_blue]  == maxval) m_hue = 60.0f * (4.0f + gnorm - rnorm);
      if (m_hue > 360.0f) m_hue = m_hue - 360.0f;
    }
    m_bIsHLS = true;
  }
}

/////////////////////////////////////////////////////////////////////////////
void CColor::ToRGB() 
{
  if (!m_bIsRGB)
  {
    if (m_saturation == 0.0) // Grauton, einfacher Fall
    {
      m_color[c_red] = m_color[c_green] = m_color[c_blue] = unsigned char(m_luminance * 255.0);
    }
    else
    {
      float rm1, rm2;
         
      if (m_luminance <= 0.5f) rm2 = m_luminance + m_luminance * m_saturation;  
      else                     rm2 = m_luminance + m_saturation - m_luminance * m_saturation;
      rm1 = 2.0f * m_luminance - rm2;   
      m_color[c_red]   = ToRGB1(rm1, rm2, m_hue + 120.0f);   
      m_color[c_green] = ToRGB1(rm1, rm2, m_hue);
      m_color[c_blue]  = ToRGB1(rm1, rm2, m_hue - 120.0f);
    }
    m_bIsRGB = true;
  }
}

/////////////////////////////////////////////////////////////////////////////
unsigned char CColor::ToRGB1(float rm1, float rm2, float rh)
{
  if      (rh > 360.0f) rh -= 360.0f;
  else if (rh <   0.0f) rh += 360.0f;
 
  if      (rh <  60.0f) rm1 = rm1 + (rm2 - rm1) * rh / 60.0f;   
  else if (rh < 180.0f) rm1 = rm2;
  else if (rh < 240.0f) rm1 = rm1 + (rm2 - rm1) * (240.0f - rh) / 60.0f;      
                   
  return static_cast<unsigned char>(rm1 * 255);
}

/////////////////////////////////////////////////////////////////////////////
// Stringkonvertierung im Format RRGGBB
/////////////////////////////////////////////////////////////////////////////
CString CColor::GetString() const 
{
  CString color;
  color.Format(_T( "%02X%02X%02X" ), GetRed(), GetGreen(), GetBlue());
  return color;
}

/////////////////////////////////////////////////////////////////////////////
bool CColor::SetString(LPCTSTR pcColor) 
{
  ASSERT(pcColor);
  CString strText = pcColor;

  strText.MakeLower();
  int nP = strText.Find(_T("#"));
  if( nP == 0 ) strText = strText.Mid(nP+1);
  nP = strText.Find(_T("x"));
  if( nP == 1 ) strText = strText.Mid(nP+1);

  int r, g, b;
  if (_stscanf(strText, _T( "%2x%2x%2x" ), &r, &g, &b) != 3) 
  {
    m_color[c_red] = m_color[c_green] = m_color[c_blue] = 0;
    return false;
  }
  else
  {
    m_color[c_red]   = static_cast<unsigned char>(r);
    m_color[c_green] = static_cast<unsigned char>(g);
    m_color[c_blue]  = static_cast<unsigned char>(b);
    m_bIsRGB = true;
    m_bIsHLS = false;
    return true;
  }
}

/////////////////////////////////////////////////////////////////////////////
CString CColor::GetName( CString prefix ) const
{
  const_cast<CColor*>(this)->ToRGB();
  int i = numNamedColors; 
  while (i-- && m_colorref != m_namedColor[i].color);
  if (i < 0) 
  {
    return prefix + GetString();
  }
  else return m_namedColor[i].name;
}

/////////////////////////////////////////////////////////////////////////////
