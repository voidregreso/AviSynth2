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


//avisynth include
#include "blender.h"


namespace avs { namespace bw {


void blender<1>::operator()(BufferWindow& blendIn, BufferWindow const& blendFrom, float factor) const
{

  int weight = int(factor * 32767.0f);            //NB: it is the weight for other (plane)

  if ( blendIn == blendFrom || weight <= 0 )      //if true nothing to do
    return;
  
  if ( weight >= 32767 )                        //full blend of the other window
  {
    blendIn = blendFrom;                        //we replace by the other one
    return;
  }
                                     
  //we have to work     
  WindowPtr dst = blendIn.Write();
  CWindowPtr src = blendFrom.Read();
  
  weight = (weight << 16) + 32767 - weight;   //aka weight-other | weight-this
  __int64 weight64  = __int64(weight) | (__int64(weight) << 32); //WO | WT | WO | WT

  static __int64 const rounder = 0x0000400000004000;		         //(0.5)<<15 in each dword

  /////////////////////
  // Blends two planes.
  // A weight between the two planes are given.
  // Has rather ok pairing, 
  // and has very little memory usage.
  // Processes four pixels per loop, so rowsize must be mod 4.
  // Thanks to ARDA for squeezing out a bit more performance.
  // (c) 2002 by sh0dan.
  /////////
 
  __asm
  {
    movq mm5, [rounder]
    pxor mm6, mm6
    movq mm7, [weight64]
    mov  ebx, [dst.width]
    mov  esi, [dst.ptr]
    mov  edi, [src.ptr]
    mov  ecx, [dst.height]

    align 16

  yloop:

    xor  eax, eax
    align 16

  xloop:

    punpcklbw mm0, [esi + eax]  // 4 pixels
     pxor mm3, mm3
    punpcklbw mm1, [edi + eax]  // y300 y200 y100 y000
     psrlw mm0, 8               // 00y3 00y2 00y1 00y0
    psrlw mm1, 8                // 00y3 00y2 00y1 00y0  
     pxor mm2, mm2
    movq mm4, mm1
     punpcklwd mm2, mm0
    punpckhwd mm3, mm0  
     punpcklwd mm4, mm6
    punpckhwd mm1, mm6
     por mm2, mm4
    por mm3, mm1
     pmaddwd mm2, mm7     // Multiply pixels by weights.  pixel = img1*weight + img2*invweight (twice)
    pmaddwd mm3, mm7      // Stalls 1 cycle (multiply unit stall)
     paddd mm2, mm5       // Add rounder
    paddd mm3, mm5
     psrld mm2, 15        // Shift down, so there is no fraction.
    psrld mm3, 15        
    packssdw mm2, mm3
    packuswb mm2, mm6 
    movd [esi + eax], mm2

    add eax, 4
    cmp ebx, eax
    jg xloop

    add esi, [dst.pitch];
    add edi, [src.pitch];
    dec ecx
    jnz yloop

    emms
  }
}



} }