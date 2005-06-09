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


#ifndef __AVS_GSTREAMER_BIN_H__
#define __AVS_GSTREAMER_BIN_H__

//avisynth includes
#include "forward.h"              //for Element

//gstreamer include
#include <gst/gstbin.h>


namespace avs { namespace gstreamer {



class Bin : public GstBin
{

private:  //declared but not implemented

  Bin();
  ~Bin();


public:

  Element& AddNewElement(char const * type, char const * name)
  {
    Element * element = Element::Create(type, name);  
    gst_bin_add(this, element);
    return *element;
  }

  Element * GetByName(char const * name)
  {
    return static_cast<Element *>( gst_bin_get_by_name(this, name) );
  }


public:

  void SyncChildrenState()
  {
    gst_bin_sync_children_state(this);
  }

  bool Iterate()
  {
    return gst_bin_iterate(this) != 0;
  }

};



} } //namespace avs::gstreamer

#endif //__AVS_GSTREAMER_BIN_H__
