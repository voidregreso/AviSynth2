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


#ifndef __AVS_COM_BASE_H__
#define __AVS_COM_BASE_H__

//avisynth include
#include "../utility/instancecounted.h"

//windows includes
#define NOMINMAX          //prevents generation of min and max macros
#include "initguid.h"
#include "objbase.h"

//boost include
#include <boost/utility.hpp>


namespace avs { namespace com {


//declaration and typedef
struct Tag { };
typedef instance_counted<Tag> InstanceCounted;



//////////////////////////////////////////////////////////////////////////////
//  com::Base
//
//  a base class for implementations of COM interfaces
//
class Base : public boost::noncopyable
{

  ULONG refCount_;
  InstanceCounted instCounted_;


public:  //structors

  Base()
    : refCount_( 1 ) { }

  virtual ~Base() { }


protected:  //IUnknown like

  ULONG AddRef_();
	ULONG Release_();

};



} } //namespace avs::com

#endif //__AVS_COM_BASE_H__
