// Avisynth v3.0 alpha.  Copyright 2003 Ben Rudiak-Gould et al.
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


//avisynth includes
#include "../vframe_yuy2.h"
#include "../vframe_rgb32.h"
#include "../../colorspace.h"


namespace avs {


VideoFrame::RGB32::RGB32(YUY2 const& source)
  : RGB( ColorSpace::rgb32(), source )
{

  CWindowPtr src = source.GetMain().GetReadPtr();
  WindowPtr dst = GetMain().GetWritePtr();

//yv12_to_rgb32_mmx(srcp, dstp, srcp + vi.height * src_pitch, src_pitch, src->GetRowSize(), rec709)


//use asm from convert_a.asm

}


}//namespace avs