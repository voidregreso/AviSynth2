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
#include "concrete.h"
#include "../exception.h"
#include "../colorspace.h"

//boost include
#include <boost/format.hpp>


namespace avs {



CPVideoInfo VideoInfo::Create() { return CPVideoInfo( (VideoInfo *)new videoinfo::Concrete() ); }


int VideoInfo::GetWidth() const { return GetDimension().GetWidth(); }
int VideoInfo::GetHeight() const { return GetDimension().GetHeight(); }

void VideoInfo::SetWidth(int width) { SetDimension( Dimension(width, GetHeight()) ); }
void VideoInfo::SetHeight(int height) { SetDimension( Dimension(GetWidth(), height) ); }



bool VideoInfo::IsRGB() const { return GetColorSpace().IsRGB(); }
bool VideoInfo::IsYUV() const { return GetColorSpace().IsYUV(); }
bool VideoInfo::IsPlanar() const { return GetColorSpace().IsPlanar(); }
bool VideoInfo::IsInterLeaved() const { return GetColorSpace().IsInterleaved(); }

bool VideoInfo::IsColorSpace(ColorSpace& space) { return GetColorSpace() == space; }
  
bool VideoInfo::IsRGB24() const { return GetColorSpace().IsRGB24(); }
bool VideoInfo::IsRGB32() const { return GetColorSpace().IsRGB32(); }
bool VideoInfo::IsRGB45() const { return GetColorSpace().IsRGB45(); }
bool VideoInfo::IsYUY2() const { return GetColorSpace().IsYUY2(); }
bool VideoInfo::IsYV12() const { return GetColorSpace().IsYV12(); }
bool VideoInfo::IsYV24() const { return GetColorSpace().IsYV24(); }
bool VideoInfo::IsYV45() const { return GetColorSpace().IsYV45(); }



int VideoInfo::BitsPerPixel() const
{
  static int bpp[] = { 24, 32, 64, 16, 12, 24, 48 };
  return bpp[ GetColorSpace().id() ];
}

int VideoInfo::BytesPerChannelSample() const
{
  static int bpcs[] = { 1, 2, 3, 4, sizeof(float) };
  return bpcs[ GetSampleType() ];
}

int VideoInfo::AudioSamplesFromFrames(int frames) const
{
  return GetSampleRate() * GetFPSDenominator() / GetFPSNumerator();
}



void VideoInfo::CheckHasVideo() const
{
  if ( ! HasVideo() )
    ThrowNoVideoException();
}

void VideoInfo::CheckHasAudio() const
{
  if ( ! HasVideo() )
    ThrowNoAudioException();
}


void VideoInfo::CheckHasFrame(int n) const
{
  if ( n < 0 || GetFrameCount() <= n )
    ThrowNoSuchFrameException(n);
}


void VideoInfo::ThrowNoVideoException()
{
  throw Exception("clip has no video");
}

void VideoInfo::ThrowNoAudioException()
{
  throw Exception("clip has no audio");
}
 
void VideoInfo::ThrowNoSuchFrameException(int n)
{
  throw Exception(str( boost::format("clip has no frame %d") % n ));
}





} //namespace avs