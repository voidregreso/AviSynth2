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


#ifndef __AVS_PARSER_FUNCTOR_POPPER_H__
#define __AVS_PARSER_FUNCTOR_POPPER_H__

//avisynth includes
#include "../optype.h"
#include "../vmstate.h"


namespace avs { namespace parser { namespace functor {



/////////////////////////////////////////////////////////////////////////////
//  popper<n>
//
//  pops the stack n times
//
template <int n>
struct popper 
{ 
  OpType operator()(VMState& state) const
  {
    state.pop();
    popper<n-1>()(state);
    return NORMAL;
  }
};


////////////////////////////////////////////////////////////////////////////////
//  popper<0>
//
//  provides stop condition for the popper<n> self recurring template
//
template <>
struct popper<0>
{
  OpType operator()(VMState& state) const { return NORMAL; }
};



/////////////////////////////////////////////////////////////////////////////////
//  Popper
//
//  same thing but with a non-template argument
//
struct Popper
{

  int n_;

  Popper(int n)
    : n_( n ) { }

  OpType operator()(VMState& state) const
  {
    for(int i = n_; i-- > 0; )
      state.pop();
    return NORMAL;
  }

};


} } } //namespace avs::parser::functor

#endif //__AVS_PARSER_FUNCTOR_POPPER_H__
