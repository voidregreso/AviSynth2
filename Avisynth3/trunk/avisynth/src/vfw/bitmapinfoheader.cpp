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


//avisynth includes
#include "bitmapinfoheader.h"
#include "../core/videoinfo.h"
#include "../core/colorspace.h"


namespace avs { namespace vfw {




BitmapInfoHeader::BitmapInfoHeader(VideoInfo const& vi)
{
  memset( static_cast<BITMAPINFOHEADER *>(this), 0, sizeof(BITMAPINFOHEADER) );

  biSize        = sizeof(BITMAPINFOHEADER);
  biPlanes      = 1;

  SetDimension(vi.GetDimension());
  SetColorSpace(vi.GetColorSpace());
}


PColorSpace BitmapInfoHeader::GetColorSpace() const
{
  switch( biCompression )
  {
  case BI_RGB:
    switch( biBitCount )
    {
    case 24: return ColorSpace::rgb24();
    case 32: return ColorSpace::rgb32();

    default: return PColorSpace();
    }

  case '2YUY': return ColorSpace::yuy2();
  case '21VY': return ColorSpace::yv12();

  default: return PColorSpace();
  }
}


void BitmapInfoHeader::SetColorSpace(PColorSpace const& space)
{
  biBitCount    = space->GetBitsPerPixel();
  biCompression = space->GetFourCC();
  biSizeImage   = space->GetBitmapSize(GetDimension());
}


void BitmapInfoHeader::SetDimension(Dimension const& dim)
{
  biWidth       = dim.GetWidth();
  biHeight      = dim.GetHeight();

  PColorSpace space = GetColorSpace();
  if ( ! space )
    biSizeImage = space->GetBitmapSize(dim);
}


} } //namespace avs::vfw
