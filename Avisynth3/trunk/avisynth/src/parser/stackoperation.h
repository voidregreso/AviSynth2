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


#ifndef __AVS_PARSER_STACKOPERATION_H__
#define __AVS_PARSER_STACKOPERATION_H__

//boost include
#include <boost/shared_ptr.hpp>


namespace avs { namespace parser {


class Stack;


//typedef boost::function<void (Stack&)> StackOperation


class StackOperation
{

  struct CallBack
  {
    virtual void operator()(Stack& stack) const = 0;
  };

  template <class Functor>
  struct functor_callback : CallBack
  {
    Functor functor_;

    functor_callback(Functor const& functor)
      : functor_( functor ) { }

    virtual void operator()(Stack& stack) const { functor_(stack); }
  };


  boost::shared_ptr<CallBack const> cb_;


public:  //structors
  
  StackOperation() { }

  StackOperation(StackOperation const& other)
    : cb_( other.cb_ ) { }

  template <class Functor>
  StackOperation(Functor const& functor)
  : cb_( new functor_callback<Functor>(functor) ) { }


public:  //function-like interface

  void operator()(Stack& stack) const { (*cb_)(stack); }

  bool empty() const { return ! cb_; }

};



} } //namespace avs::parser

#endif //__AVS_PARSER_STACKOPERATION_H__
