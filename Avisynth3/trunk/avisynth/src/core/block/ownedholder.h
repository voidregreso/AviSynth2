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


#ifndef __AVS_BLOCK_OWNEDHOLDER_H__
#define __AVS_BLOCK_OWNEDHOLDER_H__

//avisynth include
#include "../forward.h"          //for BYTE


namespace avs { namespace block {


/////////////////////////////////////////////////////////////////////////////////////////
//  OwnedHolder
//
//  polymorphic interface of the owned_block template memory holder
//
//  this is pretty much the same as Holder, but adds a method to fetch the owning env
//
class OwnedHolder
{

public:  //structors

  OwnedHolder() { }
  virtual ~OwnedHolder() { }


public:  //OwnedHolder interface

  virtual int size() const = 0;
  virtual BYTE * get() const = 0;
  virtual PEnvironment const& GetEnvironment() const = 0;

  //spawns a new holder of the same type holding mem of the asked size
  virtual OwnedHolder * spawn(int size) const = 0;


public:  //definition for subclasses

  enum { Align = 1 };               //default alignment guarantee (ie not aligned)

};


} } //namespace avs::block

#endif //__AVS_BLOCK_OWNEDHOLDER_H__
