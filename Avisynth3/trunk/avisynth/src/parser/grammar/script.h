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


#ifndef __AVS_PARSER_GRAMMAR_SCRIPT_H__
#define __AVS_PARSER_GRAMMAR_SCRIPT_H__

//avisynth includes
#include "types.h"
#include "statement.h"


namespace avs { namespace parser { namespace grammar {



namespace closure {


struct Script : spirit::closure
    < Script
    , CodeCouple
    , boost::reference_wrapper<VarTable>
    , boost::reference_wrapper<boost::optional<int> >
    , boost::reference_wrapper<VarTable>
    , boost::reference_wrapper<function::Table>
    >
{
  member1 value;
  member2 localTable;
  member3 last;
  member4 globalTable;
  member5 functionTable;
};


struct Function : spirit::closure
    < Function
    , function::FunctionId
    , VarTable
    , StatementCode
    >
{
  member1 ident;
  member2 localTable;
  member3 code;
};



struct FunctionBody : spirit::closure
    < FunctionBody
    , CodeCouple
    , boost::optional<int>
    >
{
  member1 code;
  member2 last;
};


} //namespace closure


struct Script : public spirit::grammar<Script, closure::Script::context_t>
{

  template <typename ScannerT>
  struct definition
  {

    definition(Script const& self)
    {

      using namespace lazy;
      using namespace phoenix;

      top
          =  *(   statement( CodeCouple(), self.localTable, self.last, self.globalTable, self.functionTable, 'c' )
                  [
                    self.value += arg1
                  ]
              |   spirit::str_p("function")
              >>  function
              |   spirit::eol_p
              )
          ;

      function
        =   Types::instance
              [
                first(function.ident) = arg1
              ]
          >>  name
              [
                second(function.ident) = construct_<std::string>(arg1, arg2)
              ]
          >>  '('
          >>  !(  arg   %   ','   )
          >>  spirit::ch_p(')')
              [
                bind(&function::Table::DeclareScriptFunction)( unwrap(self.functionTable), function.ident )
              ]
          >>  functionBody
              [
                function.code = arg1
              ]
          >>  spirit::eol_p
              [
                bind(&function::Table::DefineScriptFunction)
                    ( unwrap(self.functionTable), function.ident, function.code )                    
              ]
          ;

      arg
        =   Types::instance
              [
                arg.value = arg1
              ]
          >>  (   name - spirit::lazy_p( function.localTable )  )
              [
                bind(&VarTable::DefineVar)(function.localTable, construct_<std::string>(arg1, arg2), arg.value),
                third(function.ident) += arg.value
              ]
          ;

      functionBody
          =   *   spirit::eol_p
          >>  '{'
          >> *(   statement( CodeCouple(), wrap(function.localTable), wrap(functionBody.last), self.globalTable, self.functionTable, first(function.ident) ) 
                  [
                    functionBody.code += arg1
                  ]
              |   spirit::eol_p
              )
          >>  '}'
          ;

    }


    spirit::rule<ScannerT> const & start() const { return top; }

  private:

    spirit::rule<ScannerT> top;
    spirit::rule<ScannerT, closure::Function::context_t> function;
    spirit::rule<ScannerT, closure::Value<char>::context_t> arg;
    spirit::rule<ScannerT, closure::FunctionBody::context_t> functionBody;

    Name name;                    //Name grammar
    Statement statement;          //statement grammar

  };

};



} } } //namespace avs::parser::grammar

#endif //__AVS_PARSER_GRAMMAR_SCRIPT_H__
