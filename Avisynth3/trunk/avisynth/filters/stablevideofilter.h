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


#ifndef __AVS_STABLEVIDEOFILTER_H__
#define __AVS_STABLEVIDEOFILTER_H__

//avisynth includes
#include "childclip.h"
#include "cachingclip.h"


#pragma warning ( push )           //push warning state
#pragma warning (disable : 4250)   //get rid of MI dominance decisions



///////////////////////////////////////////////////////////////////////
// StableVideoFilter
//
// instanciable null filter with a child, and caching frames
// subclasses must override MakeFrame and no longer GetFrame
//
// it's called stable, because it forwards videoinfo from child
//
class StableVideoFilter : public ChildClip, public CachingClip
{
  
public:  //constructors

  StableVideoFilter(PClip child, const CachePolicy& policy = DefaultCachePolicy())
    : ChildClip( child )
    , CachingClip( child->GetEnvironment(), policy )
  {
    DispatchTo( GetChild() );    
  }

  StableVideoFilter(const StableVideoFilter& other)
    : ChildClip( other )
    , CachingClip( other )
  {
    DispatchTo( GetChild() );
  }

  virtual ~StableVideoFilter()
  {
    WithdrawFrom( GetChild() );
  }


public:  //clip public interface

  //resolving MI ambiguity
  virtual CPVideoFrame GetFrame(int n, const CachingClip& client) const { return CachingClip::GetFrame(n, client); }
  

public:  //cache hints methods

  //resolving MI ambiguity
  virtual void Dispatch(const CacheRequest& request) const { CachingClip::Dispatch(request); }
  virtual void Withdraw(const CacheRequest& request) const { CachingClip::Withdraw(request); }


protected:  //write access

  void SetChild(PClip child)
  {
    WithdrawFrom( GetChild() );
    ChildClip::SetChild( child );
    DispatchTo( GetChild() );
  }

};



#pragma warning ( pop )

#endif  //__AVS_STABLEVIDEOFILTER_H__