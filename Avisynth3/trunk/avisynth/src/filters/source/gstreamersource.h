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


#ifndef __AVS_FILTERS_GSTREAMERSOURCE_H__
#define __AVS_FILTERS_GSTREAMERSOURCE_H__

//avisynth includes
#include "gstreamer/forward.h"                //for PPipeline
#include "../../../clip/nochild.h"
#include "../../gstreamer/importer.h"         //for PImporter
#include "../../clip/framemaker/concrete.h"

//stl include
#include <string>


namespace avs { namespace filters {



///////////////////////////////////////////////////////////////////////////////////////
//  GstreamerSource
//
//
//
class GstreamerSource : public clip::NoChild
                      , public clip::framemaker::Concrete
{

  CPVideoInfo vi_;
  gstreamer::PImporter importer_;
  gstreamer::PPipeline pipeline_;


private:  //structors

  GstreamerSource(std::string const& fileName, PEnvironment const& env);

  //generated destructor is fine


public:  //Clip general interface

  virtual CPVideoInfo GetVideoInfo() const { return vi_; }


public:  //FrameMaker interface

  CPVideoFrame MakeFrame(int n) const;


public:  //factory functor

  struct Creator
  {
    PClip operator()(std::string const& fileName, PEnvironment const& env) const 
    { 
      return PClip( static_cast<Clip *>(new GstreamerSource(fileName, env) );  
    }
  };

};



} } //namespace avs::filters

#endif //__AVS_FILTERS_GSTREAMERSOURCE_H__