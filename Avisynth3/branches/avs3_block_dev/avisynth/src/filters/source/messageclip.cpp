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
#include "messageclip.h"
#include "../../text/rasterizer.h"
#include "../../core/videoinfo.h"
#include "../../core/videoframe.h"
#include "../../core/colorspace.h"
#include "../../core/colorspace/get.h"
#include "../../core/ownedblock.h"
#include "../../core/bufferwindow.h"
#include "../../core/geometry/vecteur.h"
#include "../../core/runtime_environment.h"


namespace avs { namespace filters {



MessageClip::MessageClip(std::string const& msg, PEnvironment const& env)
  : StaticImage( CreateFrame(msg, env) )
  , msg_( msg ) { }


MessageClip::MessageClip(std::string const& msg, CPVideoInfo const& vi, PEnvironment const& env)
  : StaticImage( CreateFrame(msg, text::freetype::Font("C:\\WINNT\\Fonts\\Arial.ttf", 28), vi->GetDimension(), vi->GetColorSpace(), env), vi )
  , msg_( msg ) { }


CPVideoFrame MessageClip::CreateFrame(std::string const& msg, text::freetype::Font const& font, Dimension const& dim, PColorSpace const& space, PEnvironment const& env)
{
  PVideoFrame result = env->CreateFrame(space, dim, PROGRESSIVE);

  BufferWindow masks(dim.Multiply<2, 1>(), env);

  text::Rasterizer rasterizer(font);
  rasterizer(msg, masks.Write(), text::freetype::VecteurFP6(dim.GetWidth() >> 1, 0), text::TOP_CENTER);
  rasterizer.ApplyTo(masks.Read(), 0xF0F0F0, 0, *result);


  return result;
}


CPVideoFrame MessageClip::CreateFrame(std::string const& msg, PEnvironment const& env)
{
  using namespace text::freetype;

  Font font("C:\\WINNT\\Fonts\\Arial.ttf", 28);

  DimensionFP6 dimFP6 = font.GetTextBoundingBox(msg).GetDimension();
  Dimension dim( dimFP6.GetWidth().GetRoundedUp(), dimFP6.GetHeight().GetRoundedUp() );

  return CreateFrame(msg, font, dim, colorspace::Get::RGB32(), env);
}


} } //namespace avs::filters
