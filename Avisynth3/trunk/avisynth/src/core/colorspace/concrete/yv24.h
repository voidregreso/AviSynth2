// Avisynth v3.0 alpha.  Copyright 2005 David Pierre - Ben Rudiak-Gould et al.
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


#ifndef __AVS_COLORSPACE_CONCRETE_YV24_H__
#define __AVS_COLORSPACE_CONCRETE_YV24_H__

//avisynth include
#include "yuvplanar8.h"


namespace avs { namespace cspace { namespace concrete {



/////////////////////////////////////////////////////////////////////////////////////////////
//  YV24
//
//
class YV24 : public YuvPlanar8
{

public:  //ColorSpace interface

  virtual ID id() const { return I_YV24; }
  virtual char const * GetName() const { return "YV24"; }
  virtual unsigned long GetFourCC() const;
  virtual long GetBitsPerPixel() const { return 24; }

  virtual long GetBitmapSize(Dimension const& dim) const;

  virtual void Check(long x, long y, bool interlaced = false) const;

  virtual void ToPlane(long& x, long& y, Plane plane) const;


public:  //blank frame creation method

  virtual PVideoFrame CreateFrame(PEnvironment const& env, Dimension const& dim, FrameType type) const;


public:  //yuv::Planar interface

  virtual PVideoFrame CreateFrame(Dimension const& dim, FrameType type, BufferWindow const& y , BufferWindow const& u, BufferWindow const& v) const;

};



} } } //namespace avs::cspace::concrete

#endif //__AVS_COLORSPACE_CONCRETE_YV24_H__
