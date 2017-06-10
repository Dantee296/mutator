
/***************************************************Project Mutator****************************************************/
//-*-c++-*-
/*first line intentionally left blank.*/
/*the header for bruiser's main.*/
/*Copyright (C) 2017 Farzad Sadeghi

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.*/
/*code structure inspired by Eli Bendersky's tutorial on Rewriters.*/
/**********************************************************************************************************************/
/*inclusion guard*/
#ifndef BRUISER_H
#define BRUISER_H
/**********************************************************************************************************************/
/*included modules*/
/*project headers*/
#include "../tinyxml2/tinyxml2.h"
/*standard library headers*/
#include <string>
#include <fstream>
/*clang headers*/
#include "clang/AST/ASTContext.h"
#include "clang/AST/Expr.h"
#include "clang/AST/Type.h"
#include "clang/AST/ASTTypeTraits.h"
/*llvm headers*/

/*boost*/
#include "boost/circular_buffer.hpp"
/**********************************************************************************************************************/
/*using*/
using namespace tinyxml2;
using namespace llvm;
using namespace clang;
/**********************************************************************************************************************/
namespace bruiser
{ //start of namespace bruiser
/**********************************************************************************************************************/
  const char* M0REP = "../test/misrareport.xml";
/**********************************************************************************************************************/
#define RED "\033[1;31m"
#define CYAN "\033[1;36m"
#define GREEN "\033[1;32m"
#define BLUE "\033[1;34m"
#define BLACK "\033[1;30m"
#define BROWN "\033[1;33m"
#define MAGENTA "\033[1;35m"
#define GRAY "\033[1;37m"
#define DARKGRAY "\033[1;30m"
#define YELLOW "\033[1;33m"
#define NORMAL "\033[0m"
#define CLEAR	"\033[2J"

#define LN_RED 31
#define LN_GREEN 32
#define LN_YELLOW 33
#define LN_BLUE 34
#define LN_MAGENTA 35
#define LN_CYAN 36
#define LN_WHITE 37

#define BOLD 1
#define NO_BOLD 0

#define SHELL_HISTORY_SIZE  100
#define SHELL_HISTORY_FILE "bruiser-history.txt"

#define NOT_IMPLEMENTED \
  do{\
    printf(BROWN "not implemented yet.");\
    printf(NORMAL"\n");\
  }while(0)

#define  PRINT_WITH_COLOR(X,Y) \
  do{\
    printf(X Y NORMAL);\
  }while(0)

#define  PRINT_WITH_COLOR_LB(X,Y) \
  do{\
    printf(X "%s", Y);\
    printf(NORMAL"\n");\
  }while(0)
/**********************************************************************************************************************/
/*Error Codes*/
#define M0_ERROR_CODES \
  X(BAD_M0_XML, "bad m0 xml.", 100) \
  X(CANT_OPEN_M0_XML, "could not open m0 xml.", 101) \

#define X(__x1, __x2, __x3) __x1,
  enum class M0_ERR {M0_ERROR_CODES};
#undef X
/**********************************************************************************************************************/
/*Enums*/
/**********************************************************************************************************************/
struct help
{
  public:
    std::string name;
    std::string proto;
    std::string descr;
    std::string protoprefix;
    std::string retval;
};

help CMDHelp[] = {
  {"help()", "", "display general help", "", ""},
  {"quit()", "", "quit bruiser", "", ""},
  {"exit()", "", "quit bruiser", "", ""},
  {"m0()", "", "bruiser reads the report generated by mutator-lvl0", "", ""},
  {"hijack()", "hijack main", "runs a specific matcher that replaces the main with a new main", "", ""},
  {"clear()", "", "clears the terminal", "", ""},
  {"shell()", "", "opens up a bash shell inside bruiser", "", ""},
  {"history()", "", "prints bruiser's history", "", ""},
  {"!", "", "prints the command from history", "", ""},
  {"Vars()", "lists all variables", "lists all available variable declarations", "", ""},
  {"Funcs()", "lists all functions", "lists all available function declarations", "", ""},
  {"Classess()", "lists all classes", "lists all available class declarations", "", ""},
  {"Structs()", "lists all structs", "lists all available struct declarations", "", ""},
  {"Arrays()", "lists all arrays", "lists all available array declarations", "", ""},
  {"Unions()", "lists all unions", "lists all available union declarations", "", ""},
  {"make()", "runs your make command", "runs your make command", "", ""},
  {"historysize()", "sets the history size", "sets the history size", "", ""}
};
/**********************************************************************************************************************/
/**
 * @brief This class handles the logging for bruiser.
 */
class BruiserReport
{
  public:
    BruiserReport ();

    ~BruiserReport();

    template <typename T>
    bool PrintToLog(T __arg);

  private:
    std::ofstream BruiserLog;
};
/**********************************************************************************************************************/
/**
 * @brief looks through types.
 */
class TypeInfo
{
  public:
    explicit TypeInfo(const clang::ast_type_traits::DynTypedNode* __dtn);

    ~TypeInfo();

    const clang::Type* getTypeInfo(clang::ASTContext* __astc);

  private:
    const clang::ast_type_traits::DynTypedNode* DTN;
};
/**********************************************************************************************************************/
class ReadM0
{
  public:
    ReadM0() 
    {
      try
      {
      XMLError eResult [[maybe_unused]] = IntermediateXMLDoc.LoadFile(M0REP);

      RootPointer = IntermediateXMLDoc.FirstChild();
      }
      catch (std::exception& e)
      {

      }
    }

    ~ReadM0() {}

    XMLError LoadXMLDoc(void)
    {
      XMLError eResult = IntermediateXMLDoc.LoadFile(M0REP);

      return eResult;
    }

    XMLError ReadFirstElement(void)
    {
      RootPointer = IntermediateXMLDoc.FirstChild();

      if (RootPointer == nullptr)
      {
        return XML_ERROR_FILE_READ_ERROR;
      }
      else
      {
        return XML_SUCCESS;
      }
    }

    XMLNode* getRootPointer(void)
    {
      return RootPointer;
    }

  private:
    void Debug(void)
    {

    }

    XMLDocument IntermediateXMLDoc;
    XMLNode* RootPointer;
};
/**********************************************************************************************************************/
class SearchM0
{
  public:
    SearchM0(XMLNode* __rptr) : RootPointer(__rptr) {}

    ~SearchM0() {};

    void Debug(void) 
    {
      if (!RootPointer->NoChildren())
      {
        const XMLElement* XMLE [[maybe_unused]] = RootPointer->FirstChildElement();

      }
    }

  private:
    XMLNode* RootPointer;
};
/**********************************************************************************************************************/
class ShellHistory
{
  public:
    ShellHistory() {}
    boost::circular_buffer<std::string> History{SHELL_HISTORY_SIZE};
};
/**********************************************************************************************************************/
class Daemonize
{
  public:
    Daemonize (std::string __exe, std::string __opts) : Exe(__exe), Opts(__opts) {}



  private:
    std::string Exe;
    std::string Opts;
};
/**********************************************************************************************************************/
/**********************************************************************************************************************/
} // end of namespace bruiser
#endif
/*last line intentionally left balnk.*/

