// Avisynth v3.0 alpha.  Copyright 2004 Ben Rudiak-Gould et al.
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


#ifndef __AVS_VFW_AVISTREAM_YV12_H__
#define __AVS_VFW_AVISTREAM_YV12_H__

//avisynth include
#include "video.h"

//windows include
#include <mmsystem.h>  //for MAKEFOURCC


namespace avs { namespace vfw { namespace avistream {



/////////////////////////////////////////////////////////////////////////////////
//  avistream::YV12
//
//  YV12 specific AviStream subclass
//
class YV12 : public Video
{

public:  //constructor

  YV12(AviFile& parent)
    : Video( parent, MAKEFOURCC('Y','V','1','2') ) { }


protected:  //Video implementation

  virtual int GetBMPSize(Dimension const& dim);

  virtual void ReadFrame(VideoFrame const& frame, BYTE * ptr); 

};


} } } //namespace avs::vfw::avistream

#endif //__AVS_VFW_AVISTREAM_YV12_H__
