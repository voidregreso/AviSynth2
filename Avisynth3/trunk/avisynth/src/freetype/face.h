// Avisynth v3.0 alpha.  Copyright 2004 David Pierre - Ben Rudiak-Gould et al.
// http://www.avisynth.org

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA, or visit
// http://www.gnu.org/copyleft/gpl.html .
//
// Linking Avisynth statically or dynamically with other modules is making a
// combined work based on Avisynth.  Thus, the terms and conditions of the GNU
// General Public License cover the whole combination.


#ifndef __AVS_FREETYPE_FACE_H__
#define __AVS_FREETYPE_FACE_H__

//avisynth includes
#include "glyph.h"
//#include "bitmapglyph.h"
#include "../core/geometry/vecteur.h"

//boost include
#include <boost/shared_ptr.hpp>

// STL include
#include <string>


//declaration
struct FT_FaceRec_;


namespace avs { namespace freetype {



/////////////////////////////////////////////////////////////////////////////////
//  freetype::Face
//
//  C++ wrapper around the FT_Face handle
//
class Face
{
    
  boost::shared_ptr<FT_FaceRec_> face_;  //underlying handle


public:  //structors
    
  Face(std::string const& fileName, int index = 0);

  //generated copy constructor and destructor are fine


public:  //Basic API

/*  void SetCharSize(Dimension const& size, Dimension const& resolution);
    
  void SetPixelSize(Dimension const& dim);  */
  
  unsigned GetCharIndex(unsigned charCode);

  Glyph GetGlyph(unsigned glyphIndex);

//  BitmapGlyp GetBitmapGlyp(unsigned glyphIndex);
    
//void LoadChar(unsigned charCode, int loadFlags);

  bool HasKerning() const;
       
  Vecteur GetKerning(unsigned leftGlyph, unsigned rightGlyph) const;

  //std::string GetGlyphName(unsigned glyphIndex);

  //std::string GetPostscriptName();

};


} } // namespace avs::freetype

#endif //__AVS_FREETYPE_FACE_H__
