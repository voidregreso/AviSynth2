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


#ifndef __AVS_OWNEDBLOCK_H__
#define __AVS_OWNEDBLOCK_H__

//avisynth includes
#include "block/base.h"
#include "block/align.h"
#include "block/ownedholder.h"


namespace avs { 


//forward declaration
namespace block { class OwnedCreator; }



///////////////////////////////////////////////////////////////////////////////////////
//  owned_block<align>
//
//  provides same service than Block (from block.h)
//  but the memory is considered owned by an environment
//  which sees its memory usage updated accordingly
//
template <int align>
class owned_block : public block::base<block::OwnedHolder, align>
{

public:  //typedefs

  typedef owned_block<align> BlockType;
  typedef block::base<block::OwnedHolder, align> BaseBlockType;
  typedef typename boost::enable_if<block::align_compatible<block::Align, align>, block::OwnedCreator>::type Creator;


public:  //structors

  template <class Holder>
  explicit owned_block(Holder * holder)
    :  BaseBlockType( holder ) { }

  template <int alignOther>
  explicit owned_block(owned_block<alignOther> const& other)
    : BaseBlockType( other ) { }

  //spawning constructor
  owned_block(BlockType const& other, int size, bool recycle)
    : BaseBlockType( other, size, recycle ) { }

  //generated copy constructor and destructor are fine


public:  //assignment

  template <int alignOther>
  BlockType& operator=(owned_block<alignOther> const& other)
  {
    return static_cast<BlockType&>( BaseBlockType::operator=(other) );
  }

  //generated operator= is fine
  //swap inherited from superclass


public:  //misc

  void reset(int size, bool recycle)
  { 
    spawn(size, recycle).swap(*this);
  }

  //spawn method, just calls the spawning constructor, but is more explicit
  BlockType spawn(int size, bool recycle) const 
  { 
    return BlockType(*this, size, recycle); 
  }

};



//////////////////////////////////////////////////////////////////////////////////////////////////
//  owned_block<block::Align>
//
//  specialisation of the above
//  
//  Just adds two constructors, allocating memory from avisynth
//  Everything else is the same
//
template <>
class owned_block<block::Align> : public block::base<block::OwnedHolder, block::Align>
{

public:  //typedefs

  typedef owned_block<block::Align> BlockType;
  typedef block::OwnedCreator Creator;


public:  //structors

  explicit owned_block(PEnvironment const& env, bool recycle);

  //normal constructor
  owned_block(PEnvironment const& env, int size, bool recycle);

  template <class Holder>
  explicit owned_block(Holder * holder)
    :  BaseBlockType( holder ) { }

  template <int alignOther>
  explicit owned_block(owned_block<alignOther> const& other)
    : BaseBlockType( other ) { }

  //spawning constructor
  owned_block(BlockType const& other, int size, bool recycle)
    : BaseBlockType( other, size, recycle ) { }

  //generated copy constructor and destructor are fine


public:  //assignment

  template <int alignOther>
  BlockType& operator=(owned_block<alignOther> const& other)
  {
    return static_cast<BlockType>( BaseBlockType::operator=(other) );
  }

  //generated operator= is fine
  //swap inherited from superclass


public:  //misc

  void reset(int size, bool recycle)
  { 
    spawn(size, recycle).swap(*this); 
  }

  //spawn method, just calls the spawning constructor, but is more explicit
  BlockType spawn(int size, bool recycle) const 
  { 
    return BlockType(*this, size, recycle); 
  }

};




namespace block {



///////////////////////////////////////////////////////////////////////////////////////////////////////
//  block::OwnedCreator
//
//  This functor is used by the buffer_window template to flatten its interface.
//
//  Its introduction has been necessary when Buffer became a template parameter.
//
//  The allocating constructor now takes the buffer associated creator as parameter instead of an env
//  And since we are implicitly convertible from an env, one can still write :
//
//  BufferWindow buffer(dim, env);
//
class OwnedCreator
{

  PEnvironment env_;


public:  //structors

  OwnedCreator(PEnvironment const& env)
    : env_( env ) { }

  template <int align>
  OwnedCreator(owned_block<align> const& block)
    : env_( block.GetEnvironment() ) { }

  //generated copy constructor and destructor are fine


public:  //operator(), the block creation method

  owned_block<block::Align> operator()(int size, bool recycle) const 
  { 
    return owned_block<block::Align>(env_, size, recycle); 
  }

};


} } //namespace avs::block

#endif //__AVS_OWNEDBLOCK_H__
