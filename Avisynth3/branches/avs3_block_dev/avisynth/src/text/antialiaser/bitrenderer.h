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


#ifndef __AVS_TEXT_ALIASER_BITRENDERER_H__
#define __AVS_TEXT_ALIASER_BITRENDERER_H__

//avisynth includes
#include "../font.h"
#include "../align.h"
#include "../../core/window_ptr.h"
#include "../../core/geometry/dimension.h"

//boost include
#include <boost/utility.hpp>

//windows includes
#include <windows.h>
#include <wingdi.h>  


namespace avs { namespace text { namespace aliaser {



class BitRenderer : private boost::noncopyable
{

  Font font_;
  Dimension dim_;

  HDC hdc_;
  //HBITMAP hbm_;
  void * antialiasBits_;

  HFONT hfontDefault_;
  HBITMAP hbmDefault_;


public:  //structors

  BitRenderer(Dimension const& dim, Font const& font);
  ~BitRenderer();


public: 

  void SetText(std::string const& text, Vecteur const& coords, Align align);

  CWindowPtr ReadBits() const;


private:

  static int ToWinAlign(Align align);

};


} } } //namespace avs::text::aliaser

#endif //__AVS_TEXT_ALIASER_BITRENDERER_H__
