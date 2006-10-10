// Avisynth v3.0 alpha.  Copyright 2003-2006 David Pierre - Ben Rudiak-Gould et al.
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


#ifndef __AVS_PARSER_GRAMMAR_BINARYOPMAP_H__
#define __AVS_PARSER_GRAMMAR_BINARYOPMAP_H__

//STL include
#include <map>

namespace avs { namespace parser { namespace grammar {



class BinaryOpMap
{

public:  //inner structs

  struct OpInfo
  {
    char op;
    char left;
    char right;
  }

  struct ResultInfo
  {
    char result;
    char * symbol;
  };


private: //members

  typedef std::map<OpInfo, ResultInfo> OpMap;

  OpMap opMap_;


private: //structors

  BinaryOpMap();
  //generated destructor is fine


public: //sole instance

  BinaryOpMap const instance;

};


} } } //namespace avs::parser::grammar

#endif // __AVS_PARSER_GRAMMAR_BINARYOPMAP_H__
