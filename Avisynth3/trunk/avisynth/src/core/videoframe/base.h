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


#ifndef __AVS_VIDEOFRAME_BASE_H__
#define __AVS_VIDEOFRAME_BASE_H__


//avisynth includes
#include "../dimension.h"
#include "../videoframe.h"

//stl include
#include <hash_map>  //for hash_map


namespace avs { namespace vframe {



/////////////////////////////////////////////////////////////////////////////////////////
//  Base
//
//  provides common features for all VideoFrame subclasses
//
class Base : public VideoFrame
{

private:  //declarations and typedefs

  struct HashPKey
  {
    unsigned operator()(PKey const& key) const { return key->hash(); }
  };
  struct EqualPKey
  {
    bool operator()(PKey const& left, PKey const& right) const { return *left == *right; }
  };

	typedef std::hash_map<PKey, CPProperty, HashPKey, EqualPKey> PropertyMap;
  typedef std::hash_multimap<PKey, CPProperty, HashPKey, EqualPKey> PropertyMultiMap;


private:  //members

  FrameType type_;                    //type of the frame
  Dimension dim_;                //dimension of the frame

  PropertyMultiMap flows_;       //holds flow properties
  mutable PropertyMap statics_;  //holds static properties


public: //constructors

  //normal constructor
  Base(ColorSpace& space, Dimension const& dim, FrameType type);

  //colorspace conversion constructor
  Base(ColorSpace& space, Base const& other);

  //generated copy constructor and destructor are fine


public:  //general frame info

  //queries
  virtual FrameType GetType() const { return type_; }
  virtual Dimension const& GetDimension() const { return dim_; }

  //write access
  virtual void SetType(FrameType type);


protected:  //write access

  void SetDimension(Dimension const& dim) { dim_ = dim; }
  void ProtectedSetType(FrameType type) { type_ = type; }


public:  //properties methods

  virtual void SetProperty(CPProperty const& prop);
  virtual void SetStaticProperty(CPProperty const& prop) const;

  virtual CPProperty GetStaticProperty(PKey const& key) const;
  virtual void GetFlowProperties(PKey const& key, PropertyVector& propVector) const;

  virtual void RemoveFlowProperties(PKey const& key);


protected:  //helper methods

  void ClearStaticProperties() { statics_.clear(); }

};//Base




} } //namespace avs::vframe

#endif //__AVS_VIDEOFRAME_BASE_H__