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


#include "videoframe.h"
#include <functional>   //for unary_function 
#include <algorithm>    //for remove_if()  
#pragma warning(disable:4786)



/**********************************************************************************************/
/*************************************** VideoFrame *******************************************/
/**********************************************************************************************/


void VideoFrame::SizeChange(const Vecteur& topLeft, const Vecteur& bottomRight) //args in pixels
{
  //fetch ColorSpace
  const ColorSpace& space = GetColorSpace();
  //partial check of args validity (otherwise errors from side can compensate themselves)
  space.IsLegalCoords(topLeft);

  //now we do the full change in vidProps;
  vidProps.ensureOwning();        
  vidProps->SetDimension(vidProps->GetDimension() + bottomRight - topLeft);
  //exception if illegal

  //otherwise we have to do the job
  for(int i = PLANE_COUNT; i-- > 0; )
  {
    Plane p = IndexToPlane(i);
    if (space.HasPlane(p))    
      GetPlane(p).SizeChange( space.ToPlaneVecteur(topLeft), space.ToPlaneVecteur(bottomRight) );     
  }//done
}

void VideoFrame::Copy(const VideoFrame& other, const Vecteur& coords)
{
  //fetch ColorSpace
  const ColorSpace& space = GetColorSpace();

  //check other has same colorspace
  if ( space != other.GetColorSpace() )  //what about frame types ?
    throw std::logic_error("Colorspaces don't match");
  //check left and top are valid copy coords in the frame
  space.IsLegalCoords(coords);

  //now we do the job
  for(int i = PLANE_COUNT; i-- > 0; )
  {
    Plane p = IndexToPlane(i);
    if (space.HasPlane(p))    
      GetPlane(p).Copy(
        other.GetPlane(p),
        space.WidthToRowSize(left, p),
        space.HeightToPlaneHeight(top, p)
      );            
  }//done

}


void StackHorizontal(const VideoFrame& other)
{
  CheckCompatibleColorSpace(other);
  //check that height are same ? or just leave it be...

  int width = GetWidth();
  //enlarge so other frame can be fitted at right
  SizeChange(Vecteur(), Vecteur(other.GetWidth(), 0)); 
  Copy(other, Vecteur(width, 0);     //copy it at the right place             
}

void StackVertical(const VideoFrame& other)
{
  CheckCompatibleColorSpace(other);
  //same width ?

  int height = GetHeight();
  SizeChange(Vecteur(), Vecteur(0, other.GetHeight());
  Copy(other, Vecteur(0, height));
}






/**********************************************************************************************/
/************************************ TaggedVideoFrame ****************************************/
/**********************************************************************************************/








void TaggedVideoFrame::Copy(CPVideoFrame other, int left, int top)
{
  //TODO: the checks


}


/**********************************************************************************************/
/************************************* RGBVideoFrame ******************************************/
/**********************************************************************************************/

/*
void RGBVideoFrame::FlipHorizontal()
{  
  int row_size = main.GetRowSize();
  int height   = main.GetHeight();
  BufferWindow dst(row_size, height, -main.GetAlign());
  
  BYTE * dstp = dst.GetWritePtr();  
  const BYTE * srcp = main.GetReadPtr();
  int src_pitch = main.GetPitch();
  int dst_pitch = dst.GetPitch();

  int step = WidthToRowSize(1);
  int width = row_size/step;
  srcp += row_size - step;
  for(int h = height; h--> 0; )
  {
    for(int x = width; x--> 0; ) 
      for(int i = step; i-->0; )
        dstp[step*x+i] = srcp[-step*x+i];
    srcp += src_pitch;
    dstp += dst_pitch;
  }
  main = dst;  //replace window by the flipped one  
}*/


/**********************************************************************************************/
/************************************ RGB32VideoFrame *****************************************/
/**********************************************************************************************/

CPVideoFrame RGB32VideoFrame::ConvertTo(const ColorSpace& space) const
{
  switch(space.id)
  {
    case I_RGB24: return new RGB24VideoFrame(*this);
    case I_YUY2:  return new YUY2VideoFrame(*this);
    case I_YV12:  return new YV12VideoFrame(*this);
  }
  AddRef();   
  return this; //aka case I_RGB32:
}



/**********************************************************************************************/
/************************************ RGB24VideoFrame *****************************************/
/**********************************************************************************************/

CPVideoFrame RGB24VideoFrame::ConvertTo(const ColorSpace& space) const
{
  switch(space.id)
  {
    case I_RGB32: return new RGB32VideoFrame(*this);
    case I_YUY2:  return new YUY2VideoFrame(*this);
    case I_YV12:  return new YV12VideoFrame(*this);
  }
  AddRef();   
  return this; //aka case I_RGB24:
}


/**********************************************************************************************/
/************************************* YUY2VideoFrame *****************************************/
/**********************************************************************************************/





CPVideoFrame YUY2VideoFrame::ConvertTo(const ColorSpace& space) const
{
  switch(space.id)
  {
    case I_RGB32: return new RGB32VideoFrame(*this);
    case I_RGB24: return new RGB24VideoFrame(*this);
    case I_YV12:  return new YV12VideoFrame(*this);
  }
  AddRef();   
  return this; //aka case I_YUY2:
}

void YUY2VideoFrame::FlipHorizontal()
{  
  int row_size = main.GetRowSize();
  int height   = main.GetHeight();
  BufferWindow dst(row_size, height);  
  
  BYTE * dstp = dst.GetWritePtr();  
  const BYTE * srcp = main.GetReadPtr();
  int src_pitch = main.GetPitch();
  int dst_pitch = dst.GetPitch();

  srcp += row_size - 4;
  for(int h = height; h--> 0; )
  {
    for(int x = row_size>>2; x--> 0; ) {
      dstp[4*x]   = srcp[-4*x+2];
      dstp[4*x+1] = srcp[-4*x+1];
      dstp[4*x+2] = srcp[-4*x];
      dstp[4*x+3] = srcp[-4*x+3];
    }
    srcp += src_pitch;
    dstp += dst_pitch;
  }
  main = dst;  //replace window by the flipped one  
}

/**********************************************************************************************/
/************************************ PlanarVideoFrame ****************************************/
/**********************************************************************************************/





void PlanarVideoFrame::FlipVertical()
{
  for(int i = 3; i--> 0; ) //reverse loop  
    GetPlane(IndexToPlane(i)).FlipVertical();
}

void PlanarVideoFrame::FlipHorizontal()
{
  for(int i = 3; i--> 0; ) //reverse loop
  {
    BufferWindow& src = GetPlane(IndexToPlane(i));
    int row_size = src.GetRowSize();
    int height   = src.GetHeight();
    BufferWindow dst(row_size, height);
    BYTE* dstp = dst.GetWritePtr();  
    const BYTE* srcp = src.GetReadPtr();
    int src_pitch = src.GetPitch();
    int dst_pitch = dst.GetPitch();

    srcp +=row_size-1;
    for(int h = height; h--> 0; )
    {
      for(int x = row_size; x--> 0; )
        dstp[x] = srcp[-x];
      srcp += src_pitch;
      dstp += dst_pitch;
    }
    src = dst;  //replace window by the flipped one
  }
}



CPVideoFrame YV12VideoFrame::ConvertTo(const ColorSpace& space) const
{
  switch(space.id)
  {
    case I_RGB32: return new RGB32VideoFrame(*this);
    case I_RGB24: return new RGB24VideoFrame(*this);
    case I_YUY2:  return new YUY2VideoFrame(*this);
  }
  AddRef();   
  return this; //aka case I_YV12:
}




void YV12VideoFrame::InitPlanes(int width, int height)
{
  y.NewWindow(width, height);
  u.NewWindow(width>>1, height>>1);
  v.NewWindow(width>>1, height>>1);
}

void VFWYV12VideoFrame::InitPlanes(int width, int height)
{
  int pitchY = (width + 3) & -4;  //mod 4 pitch
  int neededSize = (pitchY * height * 3) >> 1 + 4;
  PVideoFrameBuffer solid = new SolidFrameBuffer(neededSize);
  int solidOffset = -int(solid->GetReadPtr()) & 3; 
  
  y.NewSolidWindow(width, height, pitchY, solid, solidOffset);
  u.NewSolidWindow(width>>1, height>>1, pitchY>>1, solid, solidOffset + pitchY * height);
  v.NewSolidWindow(width>>1, height>>1, pitchY>>1, solid, solidOffset + (pitchY * height * 5 >>2));
}