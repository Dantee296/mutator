
/*first line intentionally left blank.*/
/**********************************************************************************************************************/
/*included modules*/
/*project headers*/
#include "mutator_aux.h"
#include "tinyxml2/tinyxml2.h"
/*standard headers*/
#include <string>
#include <iostream>
#include <cassert>
#include <vector>
/*LLVM headers*/
#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Lex/Lexer.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Lex/PPCallbacks.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Function.h"
/**********************************************************************************************************************/
/*used namespaces*/
using namespace llvm;
using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::driver;
using namespace clang::tooling;
/**********************************************************************************************************************/
/*global vars*/
Devi::XMLReport XMLDocOut;

static llvm::cl::OptionCategory MatcherSampleCategory("Matcher Sample");
/**********************************************************************************************************************/
class MCForCmpless : public MatchFinder::MatchCallback {
public:
  MCForCmpless (Rewriter &Rewrite) : Rewrite (Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::ForStmt>("mcfor") != nullptr)
    {
      const ForStmt *FS = MR.Nodes.getNodeAs<clang::ForStmt>("mcfor");

      SourceLocation SL = FS->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

#if 0
      std::cout << "14.8 : " << "\"For\" statement has no braces {}: " << std::endl;
      std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;
#endif
    }
    else
    {
      std::cout << "matcher -mcfor- returned nullptr." << std::endl;
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCWhileCmpless : public MatchFinder::MatchCallback {
public:
  MCWhileCmpless (Rewriter &Rewrite) : Rewrite (Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::WhileStmt>("mcwhile") != nullptr)
    {
      const WhileStmt *WS = MR.Nodes.getNodeAs<clang::WhileStmt>("mcwhile");

      SourceLocation SL = WS->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

#if 0
      std::cout << "14.8 : " << "\"While\" statement has no braces {}: " << std::endl;
      std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;
#endif
    }
    else
    {
      std::cout << "matcher -mcwhile- returned nullptr." << std::endl;
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCElseCmpless : public MatchFinder::MatchCallback {
public:
  MCElseCmpless (Rewriter &Rewrite) : Rewrite (Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::IfStmt>("mcelse") != nullptr)
    {
      const IfStmt *IS = MR.Nodes.getNodeAs<clang::IfStmt>("mcelse");

      SourceLocation SL = IS->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      std::cout << "14.9 : " << "\"Else\" statement has no braces {}: " << std::endl;
      std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

      XMLDocOut.XMLAddNode(MR.Context, SL, "14.9", "\"Else\" statement has no braces {}: ");
    }
    else
    {
      std::cout << "matcher -mcelse- returned nullptr." << std::endl;
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCIfCmpless : public MatchFinder::MatchCallback {
public:
  MCIfCmpless (Rewriter &Rewrite) : Rewrite (Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::IfStmt>("mcif") != nullptr)
    {
      const IfStmt *IS = MR.Nodes.getNodeAs<clang::IfStmt>("mcif");

      SourceLocation SL = IS->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      std::cout << "14.9 : " << "\"If\" statement has no braces {}: " << std::endl;
      std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

      XMLDocOut.XMLAddNode(MR.Context, SL, "14.9", "\"If\" statement has no braces {}: ");
    }
    else
    {
      std::cout << "matcher -mcif- returned nullptr." << std::endl;
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class IfElseMissingFixer : public MatchFinder::MatchCallback
{
public:
  IfElseMissingFixer (Rewriter &Rewrite) : Rewrite (Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::IfStmt>("mcifelse") != nullptr)
    {
      const IfStmt *ElseIf = MR.Nodes.getNodeAs<clang::IfStmt>("mcifelse");

      SourceLocation IFESL = ElseIf->getLocStart();
      IFESL = Devi::SourceLocationHasMacro(IFESL, Rewrite, "start");

      std::cout << "14.10 : " << "\"If-Else If\" statement has no ending Else: " << std::endl;
      std::cout << IFESL.printToString(*MR.SourceManager) << "\n" << std::endl;

      XMLDocOut.XMLAddNode(MR.Context, IFESL, "14.10", "\"If-Else If\" statement has no ending Else: ");
    }
    else
    {
      std::cout << "matcher -mcifelse- returned nullptr." << std::endl;
    }
  }


private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCSwitchBrkless : public MatchFinder::MatchCallback
{
public:
  MCSwitchBrkless (Rewriter &Rewrite) : Rewrite (Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::SwitchStmt>("mcswitchbrk") != nullptr)
    {
      const SwitchStmt *SS = MR.Nodes.getNodeAs<clang::SwitchStmt>("mcswitchbrk");

      SourceLocation SL = SS->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      std::cout << "15.2 : " << "\"SwitchStmt\" has a caseStmt that's missing a breakStmt: " << std::endl;
      std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

      XMLDocOut.XMLAddNode(MR.Context, SL, "15.2", "\"SwitchStmt\" has a caseStmt that's missing a breakStmt: ");
    }
    else
    {
      std::cout << "matcher -mcswitchbrk- returned nullptr." << std::endl;
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCSwitchDftLess : public MatchFinder::MatchCallback
{
public:
  MCSwitchDftLess (Rewriter &Rewrite) : Rewrite (Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::SwitchStmt>("mcswitchdft") != nullptr)
    {
      const SwitchStmt *SS = MR.Nodes.getNodeAs<clang::SwitchStmt>("mcswitchdft");

      SourceLocation SL = SS->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      std::cout << "15.3 : " << "\"SwitchStmt\" does not have a defaultStmt: " << std::endl;
      std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

      XMLDocOut.XMLAddNode(MR.Context, SL, "15.3", "\"SwitchStmt\" does not have a defaultStmt: ");
    }
    else
    {
      std::cout << "matcher -mcswitchdft- returned nullptr." << std::endl;
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
/*misra-c 2004:15.1*/
class MCSwitch151 : public MatchFinder::MatchCallback
{
public:
  MCSwitch151 (Rewriter &Rewrite) : Rewrite (Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::CompoundStmt>("mccmp151") != nullptr && MR.Nodes.getNodeAs<clang::CaseStmt>("mccase151") != nullptr)
    {
      const CompoundStmt *CS = MR.Nodes.getNodeAs<clang::CompoundStmt>("mccmp151");
      const CaseStmt *SS = MR.Nodes.getNodeAs<clang::CaseStmt>("mccase151");

      SourceLocation SL = SS->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      ASTContext *const ASTC = MR.Context;

      ASTContext::DynTypedNodeList NodeList = ASTC->getParents(*CS);

      /*assumptions:nothing has more than one parent in C.*/
      ast_type_traits::DynTypedNode ParentNode = NodeList[0];

      ast_type_traits::ASTNodeKind ParentNodeKind = ParentNode.getNodeKind();

      std::string StringKind = ParentNodeKind.asStringRef().str();

      if (StringKind != "SwitchStmt")
      {
        std::cout << "15.1 : " << "\"CaseStmt\" has a CompoundStmt ancestor that is not the child of the SwitchStmt: " << std::endl;
        std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

        XMLDocOut.XMLAddNode(MR.Context, SL, "15.1", "\"CaseStmt\" has a CompoundStmt ancestor that is not the child of the SwitchStmt: ");
      }
    }
    else
    {
      std::cout << "matcher -mccmp151- or -mccase151- returned nullptr." << std::endl;
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCSwitch155 : public MatchFinder::MatchCallback
{
public:
  MCSwitch155 (Rewriter &Rewrite) : Rewrite (Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::SwitchStmt>("mcswitch155") != nullptr)
    {
      const SwitchStmt *SS = MR.Nodes.getNodeAs<clang::SwitchStmt>("mcswitch155");

      SourceLocation SL = SS->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      std::cout << "15.5 : " << "\"SwitchStmt\" does not have a CaseStmt: " << std::endl;
      std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

      XMLDocOut.XMLAddNode(MR.Context, SL, "15.5", "\"SwitchStmt\" does not have a CaseStmt: ");
    }
    else
    {
      std::cout << "matcher -mcswitch155- returned nullptr." << std::endl;
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
/**********************************************************************************************************************/
class MCFunction161 : public MatchFinder::MatchCallback
{
public:
  MCFunction161 (Rewriter &Rewrite) : Rewrite (Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::FunctionDecl>("mcfunction161") != nullptr)
    {
      const FunctionDecl *FD = MR.Nodes.getNodeAs<clang::FunctionDecl>("mcfunction161");

      if (FD->isVariadic())
      {
        SourceLocation SL = FD->getLocStart();
        SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

        std::cout << "16.1 : " << "\"FunctionDecl\" is variadic: " << std::endl;
        std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

        XMLDocOut.XMLAddNode(MR.Context, SL, "16.1", "\"FunctionDecl\" is variadic: ");
      }
    }
    else
    {
      std::cout << "matcher -mcfunction161- returned nullptr." << std::endl;
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCFunction162 : public MatchFinder::MatchCallback
{
public:
  MCFunction162 (Rewriter &Rewrite) : Rewrite (Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::CallExpr>("mc162callexpr") != nullptr && MR.Nodes.getNodeAs<clang::FunctionDecl>("mc162funcdec") != nullptr)
    {
      const FunctionDecl *FD = MR.Nodes.getNodeAs<clang::FunctionDecl>("mc162funcdec");
      const CallExpr *CE = MR.Nodes.getNodeAs<clang::CallExpr>("mc162callexpr");

      SourceLocation SL = FD->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      std::string FuncNameStr = FD->getNameInfo().getAsString();

      if (CE->getDirectCallee())
      {
        const FunctionDecl *FDCalled = CE->getDirectCallee();
        std::string CalledFuncNameStr = FDCalled->getNameInfo().getAsString();

        if (FuncNameStr == CalledFuncNameStr)
        {
          std::cout << "16.2 : " << "\"FunctionDecl\" is recursive: " << std::endl;
          std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

          XMLDocOut.XMLAddNode(MR.Context, SL, "16.2", "\"FunctionDecl\" is recursive: ");
        }
        else
        {
          /*intentionally left blank.*/
        }
      }
      else
      {
        /*intentionally left blank.*/
      }
    }
    else
    {
      std::cout << "matcher -mc162funcdec- and/or -mc162callexpr- returned nullptr." << std::endl;
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCFunction164 : public MatchFinder::MatchCallback
{
public:
  MCFunction164 (Rewriter &Rewrite) : Rewrite (Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::FunctionDecl>("mcfunc164") != nullptr)
    {
      const FunctionDecl *FD = MR.Nodes.getNodeAs<clang::FunctionDecl>("mcfunc164");
      const FunctionDecl *FDcl = FD->getDefinition();

      /*to guard against function that have a declaration that is not a definition only.*/
      if (FDcl != nullptr)
      {
        SourceLocation SL = FD->getLocStart();
        SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

        SourceLocation SLDcl = FDcl->getLocStart();
        SLDcl = Devi::SourceLocationHasMacro(SLDcl, Rewrite, "start");

        ArrayRef<ParmVarDecl*> FDParmList = FD->parameters();

        ArrayRef<ParmVarDecl*> FDclParmList = FDcl->parameters();

        if ( FD->getNumParams() != FDcl->getNumParams())
        {
          std::cout << "numparam of functiondefinition and functionDecl dont match! : " << SL.printToString(*MR.SourceManager) << "\n" << std::endl;
        }
        else
        {
          if (FD->getNumParams() != 0)
          {
            for (unsigned x = 0; x < FD->getNumParams(); ++x)
            {
              if (FDParmList[x]->getNameAsString() != FDclParmList[x]->getNameAsString())
              {
                std::cout << "16.4 : " << "FunctionDecl parameter names are not the same as function definition parameter names: " << std::endl;
                std::cout << SL.printToString(*MR.SourceManager) << "  &  " << SLDcl.printToString(*MR.SourceManager) << "\n" << std::endl;

                XMLDocOut.XMLAddNode(MR.Context, SL, "16.4", "FunctionDecl parameter names are not the same as function definition parameter names: ");

                break;
              }
              else
              {
                /*intentionally left blank.*/
              }
            }
          }
        }
      }
    }
    else
    {
      std::cout << "matcher -mcfunc164- returned nullptr." << std::endl;
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCFunction166 : public MatchFinder::MatchCallback
{
public:
  MCFunction166 (Rewriter &Rewrite) : Rewrite (Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::CallExpr>("mcfunc166") != nullptr)
    {
      const CallExpr *CE = MR.Nodes.getNodeAs<clang::CallExpr>("mcfunc166");

      SourceLocation SL = CE->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      const FunctionDecl *FD = CE->getDirectCallee();

      if (CE->getNumArgs() != FD->getNumParams())
      {
        std::cout << "16.6 : " << "CallExpr number of arguments does not equal the number of parameters in the declaration: " << std::endl;
        std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

        XMLDocOut.XMLAddNode(MR.Context, SL, "16.6", "CallExpr number of arguments does not equal the number of parameters in the declaration: ");
      }
    }
    else
    {
      std::cout << "matcher -mcfunc166- returned nullptr." << std::endl;
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
/*the clang parser does not allow for such constructs.*/
class MCFunction168 : public MatchFinder::MatchCallback
{
public:
  MCFunction168 (Rewriter &Rewrite) : Rewrite (Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::ReturnStmt>("mcfunc168") != nullptr)
    {
      const ReturnStmt *RT = MR.Nodes.getNodeAs<clang::ReturnStmt>("mcfunc168");

      const Expr *RE = RT->getRetValue();

      SourceLocation SL = RT->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      SourceLocation SLE = RT->getLocEnd();
      SLE = Devi::SourceLocationHasMacro(SLE, Rewrite, "end");

      SourceRange SR;
      SR.setBegin(SL);
      SR.setEnd(SLE);

      std::string RetType = Rewrite.getRewrittenText(SR);

#if 0
      std::cout << RetType << "\n" << std::endl;
#endif
    }
    else
    {
      std::cout << "matcher -mcfunc168- returned nullptr." << std::endl;
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCFunction169 : public MatchFinder::MatchCallback
{
public:
  MCFunction169 (Rewriter &Rewrite) : Rewrite (Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::ImplicitCastExpr>("mcfunc169") != nullptr)
    {
      const ImplicitCastExpr* ICE = MR.Nodes.getNodeAs<clang::ImplicitCastExpr>("mcfunc169");

      SourceLocation SL = ICE->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      CastKind CK = ICE->getCastKind();

      if (CK == CK_FunctionToPointerDecay)
      {
        std::cout << "16.9 : " << "FunctionToPointerDecay: " << std::endl;
        std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

        XMLDocOut.XMLAddNode(MR.Context, SL, "16.9", "FunctionToPointerDecay: ");
      }
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
/*@DEVI-what is correct: match a pointer then run matcher for implicitcastexpressions of type arraytopointerdecay
that have unary(--,++) and binary(-,+) operators as parents*/
class MCPA171 : public MatchFinder::MatchCallback
{
public:
  MCPA171 (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::VarDecl>("mcpa171") != nullptr)
    {
      const VarDecl *VD = MR.Nodes.getNodeAs<clang::VarDecl>("mcpa171");

      QualType QT = VD->getType();

#if 0
      std::cout << QT.getAsString() << "\n" << std::endl;
#endif
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCSU184 : public MatchFinder::MatchCallback
{
public:
  MCSU184 (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::RecordDecl>("mcsu184") != nullptr)
    {
      const RecordDecl *RD = MR.Nodes.getNodeAs<clang::RecordDecl>("mcsu184");

      SourceLocation SL = RD->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      std::cout << "18.4 : " << "Union declared: " << std::endl;
      std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

      XMLDocOut.XMLAddNode(MR.Context, SL, "18.4", "Union declared: ");
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCTypes6465 : public MatchFinder::MatchCallback
{
public:
  MCTypes6465 (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::FieldDecl>("mctype6465") != nullptr)
    {
      const FieldDecl *FD = MR.Nodes.getNodeAs<clang::FieldDecl>("mctype6465");

      SourceLocation SL = FD->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      QualType QT = FD->getType();
      const clang::Type* TP = QT.getTypePtr();

      if ( !(TP->hasUnsignedIntegerRepresentation() || TP->hasSignedIntegerRepresentation()))
      {
        /*this part is ueless since the clang parser wont let such a bitfield through.*/
        std::cout << "6.4 : " << "BitField has a type other than int or unsigned int: " << std::endl;
        std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

        XMLDocOut.XMLAddNode(MR.Context, SL, "6.4", "BitField has a type other than int or unsigned int: ");
      }

      ASTContext *const ASTC = MR.Context;
      unsigned int BitWidth = FD->getBitWidthValue(*ASTC);

      if (TP->hasSignedIntegerRepresentation())
      {
        if (BitWidth < 2U)
        {
          std::cout << "6.5 : " << "BitField of type signed integer has a length of less than 2 in bits : " << std::endl;
          std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

          XMLDocOut.XMLAddNode(MR.Context, SL, "6.5", "BitField of type signed integer has a length of less than 2 in bits : ");
        }
      }
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCDCDF81 : public MatchFinder::MatchCallback
{
public:
  MCDCDF81 (Rewriter &Rewrite) : Rewrite(Rewrite)
  {
    FuncInfoProto.push_back(FuncInfo());

    VecC = 0U;
  };

  /*underdev*/
  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::FunctionDecl>("mcdcdf81") != nullptr)
    {
      alreadymatched = false;

      const FunctionDecl* FD = MR.Nodes.getNodeAs<clang::FunctionDecl>("mcdcdf81");
      DeclarationNameInfo DNI = FD->getNameInfo();
      std::string MatchedName = DNI.getAsString();

      SourceLocation SL = FD->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      /*going through the already matched functions,making sure we are not adding duplicates.*/
      for (unsigned x = 0; x < VecC; ++x)
      {
        if (FuncInfoProto[x].FuncNameString == MatchedName)
        {
          alreadymatched = true;

          if (!FD->isThisDeclarationADefinition())
          {
            FuncInfoProto[x].HasDecThatisNotDef = true;
          }
        }
      }

      if (alreadymatched == false)
      {
        FuncInfoProto.push_back(FuncInfo());
        FuncInfoProto[VecC].FuncNameString = MatchedName;

        if (!FD->isThisDeclarationADefinition())
        {
          /*this function has a declaration that is not a definition.*/
          FuncInfoProto[VecC].HasDecThatisNotDef = true;
        }
        else
        {
          /*save the sourcelocation only if the functiondecl is a definition.*/
          FuncInfoProto[VecC].StrcSL = SL.printToString(*MR.SourceManager);
          FuncInfoProto[VecC].FuncSL = SL;
          FuncInfoProto[VecC].FuncFSL = MR.Context->getFullLoc(SL);
        }

        VecC++;
      }
    }
  }

  virtual void onEndOfTranslationUnit()
  {

    for (unsigned x = 0; x < VecC; ++x)
    {
      if (FuncInfoProto[x].HasDecThatisNotDef == false)
      {
        std::cout << "8.1 : " << "Function does not have a FunctionDecl that is not a definition : " << std::endl;
        std::cout << FuncInfoProto[x].StrcSL << "\n" << std::endl;

        XMLDocOut.XMLAddNode(FuncInfoProto[x].FuncFSL, FuncInfoProto[x].FuncSL, "8.1", "Function does not have a FunctionDecl that is not a definition : ");
      }
    }

  }

private:
  struct FuncInfo {
    std::string FuncNameString;
    std::string StrcSL;
    bool HasDecThatisNotDef = false;
    SourceLocation FuncSL;
    FullSourceLoc FuncFSL;
  };

  std::vector<FuncInfo> FuncInfoProto;

  unsigned int VecC;

  bool alreadymatched;

  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
/*Notes:clang does not let 8.2 and 8.3 through.*/
/*clang gives the implicitly-typed vardecl and functiondecl a default type in the AST so we cant use that.
we should just get the rewritten text and do string searches inside. thats the only way i can think of.*/
class MCDCDF82 : public MatchFinder::MatchCallback
{
public:
  MCDCDF82 (Rewriter &Rewrite) : Rewrite (Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::VarDecl>("mcdcdf82") != nullptr)
    {
      const VarDecl* VD = MR.Nodes.getNodeAs<clang::VarDecl>("mcdcdf82");

      std::string QualifiedName = VD->getQualifiedNameAsString();

      QualType QT = VD->getType();

#if 0
      std::cout << QualifiedName << "\n" << std::endl;
#endif
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
/*this class also matches aggregate types. a simple aggregate check should fix that, if need be.*/
class MCInit91 : public MatchFinder::MatchCallback
{
public:
  MCInit91 (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::VarDecl>("mcinit91") != nullptr)
    {
      const VarDecl* VD = MR.Nodes.getNodeAs<clang::VarDecl>("mcinit91");

      SourceLocation SL = VD->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");
      SourceLocation SLE = VD->getLocEnd();
      SLE = Devi::SourceLocationHasMacro(SLE, Rewrite, "start");

      QualType QT = VD->getType();

      const clang::Type* TP = QT.getTypePtr();

      /*start of 8.12*/
      if (!VD->hasInit())
      {
        if (VD->hasExternalStorage())
        {
          if (TP->isIncompleteArrayType())
          {
            /*end of 8.12*/
            std::cout << "8.12 : " << "External array type is incomplete and has no initialization : " << std::endl;
            std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

            XMLDocOut.XMLAddNode(MR.Context, SL, "8.12", "External array type is incomplete and has no initialization : ");
          }
        }
      }
      /*start of 9.2*/
      else
      {
        if (TP->isArrayType() || TP->isStructureType())
        {
          /*JANKY*/
          const Expr* InitExpr = VD->getInit();
          SourceRange InitExprSR;
          InitExprSR.setBegin(SL);
          InitExprSR.setEnd(SLE);

          std::string InitExprString = Rewrite.getRewrittenText(InitExprSR);
          size_t openingcbraces = InitExprString.find("{", 0);
          size_t closingcbraces = InitExprString.find("}", 0);

          if (openingcbraces == std::string::npos || closingcbraces == std::string::npos)
          {
            std::cout << "9.2 : " << "Curly braces not used : " << std::endl;
            std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

            XMLDocOut.XMLAddNode(MR.Context, SL, "9.2", "Curly braces not used : ");
          }
        }
      }
      /*end of 9.2*/

      /*we only check for local static since global static is meaningless.*/
      if (!VD->isStaticLocal() && VD->isLocalVarDecl())
      {
        if (!VD->hasInit())
        {
          std::cout << "9.1 : " << "staic local variable does not have initialization : " << std::endl;
          std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

          XMLDocOut.XMLAddNode(MR.Context, SL, "9.1", "staic local variable does not have initialization : ");
        }
      }
    }

  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCInit92 : public MatchFinder::MatchCallback
{
public:
  MCInit92 (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::InitListExpr>("mcinit92") != nullptr)
    {
      const InitListExpr* ILE = MR.Nodes.getNodeAs<clang::InitListExpr>("mcinit92");
      const VarDecl* VD = MR.Nodes.getNodeAs<clang::VarDecl>("mcinit92daddy");

      SourceLocation SL = VD->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      unsigned int NumInits = ILE->getNumInits();

#if 0
      std::cout << NumInits << "\n" << std::endl;
#endif
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCInit93 : public MatchFinder::MatchCallback
{
public:
  MCInit93 (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::EnumConstantDecl>("mcinit93") != nullptr && MR.Nodes.getNodeAs<clang::EnumDecl>("mcinit93daddy") != nullptr)
    {
      const EnumConstantDecl * ECD = MR.Nodes.getNodeAs<clang::EnumConstantDecl>("mcinit93");
      const EnumDecl* ED = MR.Nodes.getNodeAs<clang::EnumDecl>("mcinit93daddy");
      /*do note that this pointer might very well be nullptr. we are actually counting on that.
      it tells us we could not match an integer initialization for this enumconstantdecl.*/
      const IntegerLiteral* IL = MR.Nodes.getNodeAs<clang::IntegerLiteral>("mcinit93kiddy");

      SourceLocation SL = ED->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");
      newSourceLocation = SL;

      if (oldSourceLocation != newSourceLocation)
      {
        someoneHasInit = false;
        everyoneHasInit = true;
        isFirstElement = true;
        if (IL == nullptr)
        {
          doesFirstElementHaveInit = false;
          everyoneHasInit = false;
        }
        else
        {
          doesFirstElementHaveInit = true;
        }
      }
      else
      {
        isFirstElement = false;
      }

      if (oldSourceLocation == newSourceLocation)
      {
        if (IL == nullptr)
        {
          everyoneHasInit = false;
        }
        else
        {
          someoneHasInit = true;
        }

        if (doesFirstElementHaveInit)
        {
          if (!everyoneHasInit && someoneHasInit)
          {
            /*in breach of misrac*/
            std::cout << "9.3 : " << "first enumeration has integerliteral initialization but not all enumerations do : " << std::endl;
            std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

            XMLDocOut.XMLAddNode(MR.Context, SL, "9.3", "first enumeration has integerliteral initialization but not all enumerations do : ");
          }
          else
          {
            /*doesnt mean anything*/
          }
        }
        else
        {
          if (IL != nullptr)
          {
            /*in breach of misrac*/
            std::cout << "9.3 : " << "first enumeration does not have integerliteral initialization but at least one other enumeration does : " << std::endl;
            std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

            XMLDocOut.XMLAddNode(MR.Context, SL, "9.3", "first enumeration does not have integerliteral initialization but at least one other enumeration does : ");
          }
          else
          {
            /*doesnt mean anything*/
          }
        }
      }

      oldSourceLocation = newSourceLocation;
    }
  }

private:
  /*doing this instead of saving everything and then running onendoftranslationunit is faster and less memory-expensive.
  needless to say, for this to work, we are counting on clang's matching pattern.*/
  SourceLocation oldSourceLocation;
  SourceLocation newSourceLocation;

  bool isFirstElement;
  bool doesFirstElementHaveInit;
  bool someoneHasInit = false;
  bool everyoneHasInit = true;

  Rewriter &Rewrite;
};

/**********************************************************************************************************************/
class MCExpr123 : public MatchFinder::MatchCallback
{
public:
  MCExpr123 (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::Expr>("mcexpr123kiddy") != nullptr)
    {
      const Expr* EXP = MR.Nodes.getNodeAs<clang::Expr>("mcexpr123kiddy");

      SourceLocation SL = EXP->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      ASTContext *const ASTC = MR.Context;

      if (EXP->HasSideEffects(*ASTC, true))
      {
        std::cout << "12.3 : " << "sizeof working on an expr with a side-effect : " << std::endl;
        std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

        XMLDocOut.XMLAddNode(MR.Context, SL, "12.3", "sizeof working on an expr with a side-effect : ");
      }
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCExpr124 : public MatchFinder::MatchCallback
{
public:
  MCExpr124 (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::Expr>("mcexpr124") != nullptr)
    {
      const Expr* EXP = MR.Nodes.getNodeAs<clang::Expr>("mcexpr124");

      SourceLocation SL = EXP->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      ASTContext *const ASTC = MR.Context;

      if (EXP->HasSideEffects(*ASTC, true))
      {
        std::cout << "12.4 : " << "Righ-hand expr has side-effect : " << std::endl;
        std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

        XMLDocOut.XMLAddNode(MR.Context, SL, "12.4", "Righ-hand expr has side-effect");
      }
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
/*DEVI-if all operands are boolean, this class will still tag em as inconsistent(with misrac).*/
class MCExpr125 : public MatchFinder::MatchCallback
{
public:
  MCExpr125 (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::Expr>("lrhs") != nullptr)
    {
      const Expr* EXP = MR.Nodes.getNodeAs<clang::Expr>("lrhs");

      SourceLocation SL = EXP->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      ASTContext *const ASTC = MR.Context;

      QualType QT = EXP->getType();

      SourceLocation SLE = EXP->getLocEnd();
      SLE = Devi::SourceLocationHasMacro(SLE, Rewrite, "end");

      SourceRange SR;
      SR.setBegin(SL);
      SR.setEnd(SLE);

      std::string StrText = Rewrite.getRewrittenText(SR);
      if (StrText[0] == '(' && StrText[StrText.length() - 1U] == ')')
      {
        hasParantheses = true;
      }
      else
      {
        hasParantheses = false;
      }

      if (hasParantheses || SL.isMacroID())
      {
        /*intentionally left blank.*/
      }
      else
      {
        std::cout << "12.5 : " << "RHS and/or LHS operands are not primary expressions : " << std::endl;
        std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

        XMLDocOut.XMLAddNode(MR.Context, SL, "12.5", "RHS and/or LHS operands are not primary expressions : ");
      }
    }
  }

private:
  bool hasParantheses = false;

  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCExpr126 : public MatchFinder::MatchCallback
{
public:
  MCExpr126 (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::Expr>("mcexpr126rl") != nullptr)
    {
      const Expr* EXP = MR.Nodes.getNodeAs<clang::Expr>("mcexpr126rl");

      SourceLocation SL = EXP->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      if (!EXP->isKnownToHaveBooleanValue())
      {
        std::cout << "12.6 : " << "RHS and/or LHS operands are not effectively-boolean values : " << std::endl;
        std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

        XMLDocOut.XMLAddNode(MR.Context, SL, "12.6", "RHS and/or LHS operands are not effectively-boolean values : ");
      }
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCExpr127 : public MatchFinder::MatchCallback
{
public:
  MCExpr127 (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::Expr>("mcexpr127rl") != nullptr)
    {
      const Expr* EXP = MR.Nodes.getNodeAs<clang::Expr>("mcexpr127rl");

      SourceLocation SL = EXP->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      QualType QT = EXP->getType();

      const clang::Type* TP = QT.getTypePtr();

      if (TP->hasSignedIntegerRepresentation() && TP->isIntegerType())
      {
        std::cout << "12.7 : " << "Bitwise operator has signed RHS and/or LHS operands: " << std::endl;
        std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

        XMLDocOut.XMLAddNode(MR.Context, SL, "12.7", "Bitwise operator has signed RHS and/or LHS operands: ");
      }
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCExpr128 : public MatchFinder::MatchCallback
{
public:
  MCExpr128 (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::Expr>("mcexpr128lhs") != nullptr && MR.Nodes.getNodeAs<clang::Expr>("mcexpr128rhs") != nullptr)
    {
      const Expr* RHS = MR.Nodes.getNodeAs<clang::Expr>("mcexpr128rhs");
      const Expr* LHS = MR.Nodes.getNodeAs<clang::Expr>("mcexpr128lhs");

      SourceLocation SL = RHS->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      QualType RQT = RHS->getType();
      QualType LQT = LHS->getType();

      const clang::Type* RTP = RQT.getTypePtr();
      const clang::Type* LTP = LQT.getTypePtr();

      /*i need to know the size of underlying types on the target so i cant do much about that.*/
      /*llvm::DataLayout lets you do that but then you need llvm::Module.*/
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCExpr129 : public MatchFinder::MatchCallback
{
public:
  MCExpr129 (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::Expr>("mcexpr129") != nullptr)
    {
      const Expr* EXP = MR.Nodes.getNodeAs<clang::Expr>("mcexpr129");

      SourceLocation SL = EXP->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      QualType QT = EXP->getType();

      const clang::Type* TP = QT.getTypePtr();

      if (TP->isIntegerType() && TP->hasUnsignedIntegerRepresentation())
      {
        std::cout << "12.9 : " << "UnaryOperator - has an expr with an unsigned underlying type: " << std::endl;
        std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

        XMLDocOut.XMLAddNode(MR.Context, SL, "12.9", "UnaryOperator - has an expr with an unsigned underlying type: ");
      }
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCExpr1210 : public MatchFinder::MatchCallback
{
public:
  MCExpr1210 (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::Expr>("mcexpr1210") != nullptr)
    {
      const Expr* EXP = MR.Nodes.getNodeAs<clang::Expr>("mcexpr1210");

      SourceLocation SL = EXP->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      std::cout << "12.10 : " << "Comma used: " << std::endl;
      std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

      XMLDocOut.XMLAddNode(MR.Context, SL, "12.10", "Comma used: ");
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCExpr1213 : public MatchFinder::MatchCallback
{
public:
  MCExpr1213 (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::UnaryOperator>("mcexpr1213") != nullptr)
    {
      const UnaryOperator* UO = MR.Nodes.getNodeAs<clang::UnaryOperator>("mcexpr1213");

      SourceLocation SL = UO->getOperatorLoc();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      std::cout << "12.13 : " << "Unary ++ or -- have been used in an expr with other operators: " << std::endl;
      std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

      XMLDocOut.XMLAddNode(MR.Context, SL, "12.13", "Unary ++ or -- have been used in an expr with other operators: ");
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCCSE131 : public MatchFinder::MatchCallback
{
public:
  MCCSE131 (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::Expr>("cse131rlhs") != nullptr)
    {
      const Expr* EXP = MR.Nodes.getNodeAs<clang::Expr>("cse131rlhs");

      SourceLocation SL = EXP->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      if (EXP->isKnownToHaveBooleanValue())
      {
        std::cout << "13.1 : " << "assignment operator used in an expr that is known to return boolean: " << std::endl;
        std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

        XMLDocOut.XMLAddNode(MR.Context, SL, "13.1", "assignment operator used in an expr that is known to return boolean: ");
      }
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCCSE132 : public MatchFinder::MatchCallback
{
public:
  MCCSE132 (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::Expr>("mccse132") != nullptr)
    {
      const Expr* EXP = MR.Nodes.getNodeAs<clang::Expr>("mccse132");

      SourceLocation SL = EXP->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      if (!EXP->isKnownToHaveBooleanValue())
      {
        std::cout << "13.2 : " << "Implicit test of an expr against zero which is not known to return a boolean result: " << std::endl;
        std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

        XMLDocOut.XMLAddNode(MR.Context, SL, "13.2", "Implicit test of an expr against zero which is not known to return a boolean result: ");
      }
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCCSE1332 : public MatchFinder::MatchCallback
{
public:
  MCCSE1332 (Rewriter &Rewrite) : Rewrite (Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::Expr>("mccse1332rl") != nullptr)
    {
      const Expr* EXP = MR.Nodes.getNodeAs<clang::Expr>("mccse1332rl");
      const BinaryOperator* BO = MR.Nodes.getNodeAs<clang::BinaryOperator>("mccse1332daddy");

      SourceLocation SLD = BO->getLocStart();
      SLD = Devi::SourceLocationHasMacro(SLD, Rewrite, "start");
      NewSL = SLD;

      SourceLocation SL = EXP->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      QualType QT = EXP->getType();

      const clang::Type* TP = QT.getTypePtr();

      if (OldSL != NewSL)
      {
        if (TP->hasFloatingRepresentation())
        {
          std::cout << "13.3 : " << "Float type expression checked for equality/inequality: " << std::endl;
          std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

          XMLDocOut.XMLAddNode(MR.Context, SL, "13.3", "Float type expression checked for equality/inequality: ");
        }
      }

      OldSL = NewSL;
    }
  }

private:
  SourceLocation NewSL;
  SourceLocation OldSL;

  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCCSE134 : public MatchFinder::MatchCallback
{
public:
  MCCSE134 (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::ForStmt>("mccse134") != nullptr)
    {
      AlreadyHaveAHit = false;

      const ForStmt* FS = MR.Nodes.getNodeAs<clang::ForStmt>("mccse134");

      SourceLocation SL = FS->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      const Expr* FSCond = FS->getCond();
      const Expr* FSInc = FS->getInc();

      if (FSCond != nullptr)
      {
        QualType QTCond = FSCond->getType();

        const clang::Type* TPCond = QTCond.getTypePtr();

        if (TPCond->hasFloatingRepresentation())
        {
          std::cout << "13.4 : " << "Float type used in the controlling expression of a forstmt: " << std::endl;
          std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;
          AlreadyHaveAHit = true;

          XMLDocOut.XMLAddNode(MR.Context, SL, "13.4", "Float type used in the controlling expression of a forstmt: ");
        }
      }

      if (FSInc != nullptr && !AlreadyHaveAHit)
      {
        QualType QTInc = FSInc->getType();

        const clang::Type* TPInc = QTInc.getTypePtr();

        if (TPInc->hasFloatingRepresentation())
        {
          std::cout << "13.4 : " << "Float type used in the controlling expression of a forstmt: " << std::endl;
          std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;
          AlreadyHaveAHit = true;

          XMLDocOut.XMLAddNode(MR.Context, SL, "13.4", "Float type used in the controlling expression of a forstmt: ");
        }
      }
    }
  }

private:
  bool AlreadyHaveAHit = false;

  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
/*JANKY*/
/*if a for controlling var is modified in the body using a pointer, then this class wont find it.*/
/*the class will only work properly only if there is one controlling loop variable.
the behavior is undefined for more than one variable.*/
class MCCSE136 : public MatchFinder::MatchCallback
{
public:
  MCCSE136 (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::DeclRefExpr>("mccse136kiddo") != nullptr)
    {
      const DeclRefExpr* DRE = MR.Nodes.getNodeAs<clang::DeclRefExpr>("mccse136kiddo");
      const ForStmt* FS = MR.Nodes.getNodeAs<clang::ForStmt>("mccse136daddy");

      const Stmt* FSInit = FS->getInit();
      const Expr* FSInc = FS->getInc();
      const Expr* FSCond = FS->getCond();

      SourceLocation SLD = FS->getLocStart();
      SLD = Devi::SourceLocationHasMacro(SLD, Rewrite, "start");
      SourceLocation SL = DRE->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      if (FSInit != nullptr && FSInc != nullptr)
      {
        SourceLocation SLFSInit = FSInit->getLocStart();
        SLFSInit = Devi::SourceLocationHasMacro(SLFSInit, Rewrite, "start");
        SourceLocation SLFSInc = FSInc->getLocStart();
        SLFSInc = Devi::SourceLocationHasMacro(SLFSInc, Rewrite, "start");

        DeclarationNameInfo DNI = DRE->getNameInfo();

        std::string NameString = DNI.getAsString();

        /*JANKY*/
        /*the third condition is put in place to accomodate the prefix unary increment or decrement operator.*/
        if (SLFSInit == SL || SLFSInc == SL || SLFSInc.getLocWithOffset(2) == SL)
        {
          ControlVarName = NameString;
        }
        else
        {
          if (ControlVarName == NameString)
          {
            std::cout << "13.6 : " << "ForStmt controlling variable modified in the body of the loop: " << std::endl;
            std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

            XMLDocOut.XMLAddNode(MR.Context, SL, "13.6", "ForStmt controlling variable modified in the body of the loop: ");
          }
        }

      }
    }
  }

private:
  std::string ControlVarName;

  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCCF144 : public MatchFinder::MatchCallback
{
public:
  MCCF144 (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::GotoStmt>("mccf144") != nullptr)
    {
      const GotoStmt* GS = MR.Nodes.getNodeAs<clang::GotoStmt>("mccf144");

      SourceLocation SL = GS->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      std::cout << "14.4 : " << "GotoStmt used: " << std::endl;
      std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

      XMLDocOut.XMLAddNode(MR.Context, SL, "14.4", "GotoStmt used: ");
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCCF145 : public MatchFinder::MatchCallback
{
public:
  MCCF145 (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::ContinueStmt>("mccf145") != nullptr)
    {
      const ContinueStmt* CS = MR.Nodes.getNodeAs<clang::ContinueStmt>("mccf145");

      SourceLocation SL = CS->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      std::cout << "14.5 : " << "ContinueStmt used: " << std::endl;
      std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

      XMLDocOut.XMLAddNode(MR.Context, SL, "14.5", "ContinueStmt used: ");
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCCF146 : public MatchFinder::MatchCallback
{
public:
  MCCF146 (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::ForStmt>("mccffofo") != nullptr)
    {
      const ForStmt* FS =  MR.Nodes.getNodeAs<clang::ForStmt>("mccffofo");

      SL = FS->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");
    }

    if (MR.Nodes.getNodeAs<clang::WhileStmt>("mccfwuwu") != nullptr)
    {
      const WhileStmt* WS =  MR.Nodes.getNodeAs<clang::WhileStmt>("mccfwuwu");

      SL = WS->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");
    }

    if (MR.Nodes.getNodeAs<clang::DoStmt>("mccfdodo") != nullptr)
    {
      const DoStmt* DS =  MR.Nodes.getNodeAs<clang::DoStmt>("mccfdodo");

      SL = DS->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");
    }

    NewSL = SL;

    if (OldSL != NewSL)
    {
      AlreadyTagged = false;
      BreakCounter = 1U;
    }

    if (OldSL == NewSL)
    {
      BreakCounter++;
    }

    if (BreakCounter >= 2U && !AlreadyTagged)
    {
      std::cout << "14.6 : " << "More than one BreakStmt used in the loop counter: " << std::endl;
      std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;
      AlreadyTagged = true;

      XMLDocOut.XMLAddNode(MR.Context, SL, "14.6", "More than one BreakStmt used in the loop counter: ");
    }

    OldSL = NewSL;
  }

private:
  SourceLocation OldSL;
  SourceLocation NewSL;
  bool AlreadyTagged = false;
  unsigned int BreakCounter = 0U;
  SourceLocation SL;

  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCCF147 : public MatchFinder::MatchCallback
{
public:
  MCCF147 (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::FunctionDecl>("mccf147") != nullptr)
    {
      const FunctionDecl* FD = MR.Nodes.getNodeAs<clang::FunctionDecl>("mccf147");

      SourceLocation SL = FD->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      NewSL = SL;

      if (OldSL != NewSL)
      {
        AlreadyTagged = false;
        ReturnCounter = 1U;
      }

      if (OldSL == NewSL)
      {
        ReturnCounter++;
      }

      if (ReturnCounter >= 2U && !AlreadyTagged)
      {
        std::cout << "14.7 : " << "More than one ReturnStmt used in the body of FunctionDecl: " << std::endl;
        std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;
        AlreadyTagged = true;

        XMLDocOut.XMLAddNode(MR.Context, SL, "14.7", "More than one ReturnStmt used in the body of FunctionDecl: ");
      }

      OldSL = NewSL;
    }
  }

private:
  SourceLocation NewSL;
  SourceLocation OldSL;
  unsigned int ReturnCounter = 0U;
  bool AlreadyTagged = false;

  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCCF148 : public MatchFinder::MatchCallback
{
public:
  MCCF148 (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {

    if (MR.Nodes.getNodeAs<clang::ForStmt>("mccf148for") != nullptr)
    {
      const ForStmt* FS = MR.Nodes.getNodeAs<clang::ForStmt>("mccf148for");

      SL = FS->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      std::cout << "14.8 : " << "ForStmt does not have a child CompoundStmt: " << std::endl;
      std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

      XMLDocOut.XMLAddNode(MR.Context, SL, "14.8", "ForStmt does not have a child CompoundStmt: ");
    }

    if (MR.Nodes.getNodeAs<clang::WhileStmt>("mccf148while") != nullptr)
    {
      const WhileStmt* WS = MR.Nodes.getNodeAs<clang::WhileStmt>("mccf148while");

      SL = WS->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      std::cout << "14.8 : " << "WhileStmt does not have a child CompoundStmt: " << std::endl;
      std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

      XMLDocOut.XMLAddNode(MR.Context, SL, "14.8", "WhileStmt does not have a child CompoundStmt: ");
    }

    if (MR.Nodes.getNodeAs<clang::DoStmt>("mccf148do") != nullptr)
    {
      const DoStmt* DS = MR.Nodes.getNodeAs<clang::DoStmt>("mccf148do");

      SL = DS->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      std::cout << "14.8 : " << "DoStmt does not have a child CompoundStmt: " << std::endl;
      std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

      XMLDocOut.XMLAddNode(MR.Context, SL, "14.8", "DoStmt does not have a child CompoundStmt: ");
    }

    if (MR.Nodes.getNodeAs<clang::SwitchStmt>("mccf148switch") != nullptr)
    {
      const SwitchStmt* SS = MR.Nodes.getNodeAs<clang::SwitchStmt>("mccf148switch");

      SL = SS->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      std::cout << "14.8 : " << "SwitchStmt does not have a child CompoundStmt: " << std::endl;
      std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

      XMLDocOut.XMLAddNode(MR.Context, SL, "14.8", "SwitchStmt does not have a child CompoundStmt: ");
    }
  }

private:
  SourceLocation SL;

  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCSwitch154 : public MatchFinder::MatchCallback\
{
public:
  MCSwitch154 (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    const Expr* EXP = MR.Nodes.getNodeAs<clang::Expr>("mcswitch154");

    SourceLocation SL = EXP->getLocStart();
    SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

    if (EXP->isKnownToHaveBooleanValue())
    {
      std::cout << "15.4 : " << "Switch expression is effectively boolean: " << std::endl;
      std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

      XMLDocOut.XMLAddNode(MR.Context, SL, "15.4", "Switch expression is effectively boolean: ");
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCPTC111 : public MatchFinder::MatchCallback
{
public:
  MCPTC111 (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    const DeclRefExpr* DRE = MR.Nodes.getNodeAs<clang::DeclRefExpr>("mcptc111");

    SourceLocation SL = DRE->getLocStart();
    SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

    ASTContext *const ASTC = MR.Context;

    ASTContext::DynTypedNodeList NodeList = ASTC->getParents(*DRE);

    /*assumptions:nothing has more than one parent in C.*/
    ast_type_traits::DynTypedNode ParentNode = NodeList[0];

    ast_type_traits::ASTNodeKind ParentNodeKind = ParentNode.getNodeKind();

    std::string StringKind = ParentNodeKind.asStringRef().str();

    if (StringKind == "ImplicitCastExpr")
    {
      //ParentICE = ParentNode.get();
      /*the tests for CastKind go here*/
    }

  }

private:
  const clang::ImplicitCastExpr* ParentICE;
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCCSE137 : public MatchFinder::MatchCallback
{
public:
  MCCSE137 (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::Expr>("mccse137") != nullptr)
    {
      const Expr* EXP = MR.Nodes.getNodeAs<clang::Expr>("mccse137");

      SourceLocation SL = EXP->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      ASTContext *const ASTC = MR.Context;

      if (EXP->isKnownToHaveBooleanValue())
      {
        if (EXP->isEvaluatable(*ASTC, Expr::SE_NoSideEffects))
        {
          std::cout << "13.7 : " << "EffectivelyBooleanExpr's result is known at compile-time: " << std::endl;
          std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

          XMLDocOut.XMLAddNode(MR.Context, SL, "13.7", "EffectivelyBooleanExpr's result is known at compile-time: ");
        }
      }

      QualType QT = EXP->getType();
      const clang::Type* TP = QT.getTypePtr();

      if (TP->isIntegerType())
      {
        ASTContext::DynTypedNodeList NodeList = ASTC->getParents(*EXP);

        /*assumptions:nothing has more than one parent in C.*/
        ast_type_traits::DynTypedNode ParentNode = NodeList[0];

        ast_type_traits::ASTNodeKind ParentNodeKind = ParentNode.getNodeKind();

        std::string StringKind = ParentNodeKind.asStringRef().str();

        if (StringKind == "ImplicitCastExpr")
        {

        }
      }
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
/*if the call is coming from another file, getdirectcalle returns the definition,
but if its coming from the same file, it returns the declaration that is not a definition.*/
/*if youve already matched the definition, getdefinition returns null.*/
class MCDCDF810 : public MatchFinder::MatchCallback
{
public:
  MCDCDF810 (Rewriter &Rewrite) : Rewrite(Rewrite)
  {
    FuncScopeProto.push_back(FuncScope());

    VecC = 0U;
  }

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::CallExpr>("mcdcdf810") != nullptr && MR.Nodes.getNodeAs<clang::FunctionDecl>("mcdcdf810daddy") != nullptr)
    {
      AlreadyTagged = false;

      const CallExpr* CE = MR.Nodes.getNodeAs<clang::CallExpr>("mcdcdf810");
      const FunctionDecl* FDDad = MR.Nodes.getNodeAs<clang::FunctionDecl>("mcdcdf810daddy");
      const FunctionDecl* FD = CE->getDirectCallee();
      const FunctionDecl* FDDef = FD->getDefinition();;

      if (FDDef == nullptr)
      {
        FDDef = CE->getDirectCallee();
      }

      SourceLocation CESL = CE->getLocStart();
      CESL = Devi::SourceLocationHasMacro(CESL, Rewrite, "start");
      SourceLocation FDDadSL = FDDad->getLocStart();
      FDDadSL = Devi::SourceLocationHasMacro(FDDadSL, Rewrite, "start");
      SourceLocation FDSL = FDDef->getLocStart();
      FDSL = Devi::SourceLocationHasMacro(FDSL, Rewrite, "start");

      ASTContext *const ASTC = MR.Context;

      FullSourceLoc FDDadFullSL = ASTC->getFullLoc(FDDadSL);
      FullSourceLoc FDFullSL = ASTC->getFullLoc(FDSL);

      DeclarationNameInfo DNI = FDDef->getNameInfo();
      std::string MatchedName = DNI.getAsString();

      /*going through the already matched functions,making sure we are not adding duplicates.*/
      for (unsigned x = 0; x < VecC; ++x)
      {
        if (FuncScopeProto[x].FuncNameString == MatchedName && FuncScopeProto[x].DefinitionSL == FDSL.printToString(*MR.SourceManager))
        {
          AlreadyTagged = true;

          if (FDDef->isExternC())
          {
            if (FDDadFullSL.getFileID() != FDFullSL.getFileID())
            {
              FuncScopeProto[x].hasExternalCall = true;
            }
          }
        }
      }

      if (AlreadyTagged == false && FDDef->isExternC())
      {
        FuncScopeProto.push_back(FuncScope());
        FuncScopeProto[VecC].FuncNameString = MatchedName;
        FuncScopeProto[VecC].DefinitionSL = FDSL.printToString(*MR.SourceManager);
        FuncScopeProto[VecC].FuncScopeSL = FDSL;
        FuncScopeProto[VecC].FuncScopeFSL = MR.Context->getFullLoc(FDSL);

        if (FDDef->isExternC())
        {
          if (FDDadFullSL.getFileID() != FDFullSL.getFileID())
          {
            FuncScopeProto[VecC].hasExternalCall = true;
          }
        }

        VecC++;
      }
    }
  }

  virtual void onEndOfTranslationUnit()
  {
    for (unsigned x = 0; x < VecC; ++x)
    {
      if (FuncScopeProto[x].hasExternalCall == false)
      {
        std::cout << "8.11 : " << "Function does not have any external calls but is not declared as static : " << std::endl;
        std::cout << FuncScopeProto[x].DefinitionSL << "\n" << std::endl;

        XMLDocOut.XMLAddNode(FuncScopeProto[x].FuncScopeFSL, FuncScopeProto[x].FuncScopeSL, "8.11", "Function does not have any external calls but is not declared as static : ");
      }
    }
  }

private:
  struct FuncScope {
    std::string FuncNameString;
    bool hasExternalCall = false;
    std::string DefinitionSL;
    SourceLocation FuncScopeSL;
    FullSourceLoc FuncScopeFSL;
  };

  bool AlreadyTagged = false;

  unsigned VecC;

  std::vector<FuncScope> FuncScopeProto;

  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
/*also flags the main.*/
class MCFunction165 : public MatchFinder::MatchCallback
{
public:
  MCFunction165 (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::FunctionDecl>("mcfunction165") != nullptr)
    {
      const FunctionDecl* FD = MR.Nodes.getNodeAs<clang::FunctionDecl>("mcfunction165");

      SourceLocation SL = FD->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      std::cout << "16.5 : " << "Function does not return anything but is missing the void keyword for the return type : " << std::endl;
      std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

      XMLDocOut.XMLAddNode(MR.Context, SL, "16.5", "Function does not return anything but is missing the void keyword for the return type : ");
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCFunction1652 : public MatchFinder::MatchCallback
{
public:
  MCFunction1652 (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::FunctionDecl>("mcfunction1652") != nullptr)
    {
      const FunctionDecl* FD = MR.Nodes.getNodeAs<clang::FunctionDecl>("mcfunction1652");

      SourceLocation SL = FD->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");
      SourceLocation SLE = FD->getBody()->getLocStart();
      SLE = Devi::SourceLocationHasMacro(SLE, Rewrite, "end");

      SourceRange SR;
      SR.setBegin(SL);
      SR.setEnd(SLE);

      std::string FunctionSigAsString = Rewrite.getRewrittenText(SR);

      DeclarationNameInfo DNI = FD->getNameInfo();

      std::string NameAsString = DNI.getAsString();

      size_t voidposition = FunctionSigAsString.find(NameAsString, 0U);
      unsigned lengthofstring = NameAsString.length();
      size_t voidposition2 = FunctionSigAsString.find("void", voidposition + lengthofstring - 1U);

      if (voidposition2 == std::string::npos)
      {
        std::cout << "16.5 : " << "Function does not take any parameters but is not using the void keyword : " << std::endl;
        std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

        XMLDocOut.XMLAddNode(MR.Context, SL, "16.5", "Function does not take any parameters but is not using the void keyword : ");
      }
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
/*has false-positives*/
class MCPointer171 : public MatchFinder::MatchCallback
{
public:
  MCPointer171 (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::DeclRefExpr>("mcpointer171") != nullptr)
    {
      const DeclRefExpr* DRE = MR.Nodes.getNodeAs<clang::DeclRefExpr>("mcpointer171") ;

      SourceLocation SL = DRE->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      QualType QT = DRE->getType();

      const clang::Type* TP = QT.getTypePtr();

      if (TP->isAnyPointerType())
      {
        std::cout << "17.1 : " << "Pointer arithmatic for non-array pointers : " << std::endl;
        std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

        XMLDocOut.XMLAddNode(MR.Context, SL, "17.1", "Pointer arithmatic for non-array pointers : ");
      }
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
/*has a lot of false positives. now works based on array types not the array itself.*/
class MCPointer1723 : public MatchFinder::MatchCallback
{
public:
  MCPointer1723 (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::DeclRefExpr>("mcpointer1723rhs") != nullptr && MR.Nodes.getNodeAs<clang::DeclRefExpr>("mcpointer1723lhs"))
    {
      const DeclRefExpr* DRER = MR.Nodes.getNodeAs<clang::DeclRefExpr>("mcpointer1723rhs");
      const DeclRefExpr* DREL = MR.Nodes.getNodeAs<clang::DeclRefExpr>("mcpointer1723lhs");
      const BinaryOperator* BO = MR.Nodes.getNodeAs<clang::BinaryOperator>("mcpointer1723daddy");

      SourceLocation SL = BO->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      QualType QTR = DRER->getType();
      QualType QTL = DREL->getType();

      const clang::Type* TPR = QTR.getTypePtr();
      const clang::Type* TPL = QTL.getTypePtr();

      if (TPR->getPointeeType() != TPL->getPointeeType())
      {
        std::cout << "17.2 | 17.3 : " << "Pointer-type operands to BinaryOperator dont point to the same array : " << std::endl;
        std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

        XMLDocOut.XMLAddNode(MR.Context, SL, "17.2 | 17.3", "Pointer-type operands to BinaryOperator dont point to the same array : ");
      }
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class MCPointer174 : public MatchFinder::MatchCallback
{
public:
  MCPointer174 (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::CastExpr>("mcpointer174") != nullptr)
    {
      const CastExpr* CE = MR.Nodes.getNodeAs<clang::CastExpr>("mcpointer174");

      SourceLocation SL = CE->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      std::cout << "17.4 : " << "The only allowed form of pointer arithmetic is array indexing : " << std::endl;
      std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

      XMLDocOut.XMLAddNode(MR.Context, SL, "17.4", "The only allowed form of pointer arithmetic is array indexing : ");
    }

    if (MR.Nodes.getNodeAs<clang::DeclRefExpr>("mcpointer1742") != nullptr)
    {
      const DeclRefExpr* DRE = MR.Nodes.getNodeAs<clang::DeclRefExpr>("mcpointer1742");

      SourceLocation SL = DRE->getLocStart();
      SL = Devi::SourceLocationHasMacro(SL, Rewrite, "start");

      std::cout << "17.4 : " << "The only allowed form of pointer arithmetic is array indexing : " << std::endl;
      std::cout << SL.printToString(*MR.SourceManager) << "\n" << std::endl;

      XMLDocOut.XMLAddNode(MR.Context, SL, "17.4", "The only allowed form of pointer arithmetic is array indexing : ");
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class PPInclusion : public PPCallbacks
{
public:
  explicit PPInclusion (SourceManager *SM) : SM(*SM) {}

  virtual void InclusionDirective (SourceLocation HashLoc, const Token &IncludeTok, StringRef FileName, \
                                   bool IsAngled, CharSourceRange FileNameRange, const FileEntry* File, \
                                   StringRef SearchPath, StringRef RelativePath, const clang::Module* Imported)
  {
    if (IsAngled)
    {
      size_t singleQPos = FileName.find("\'", 0);
      size_t doubleQPos = FileName.find("\"", 0);
      size_t whateverSlashPos = FileName.find("\\", 0);
      size_t commentPos = FileName.find("\\*", 0);

      if (singleQPos != std::string::npos || doubleQPos != std::string::npos || whateverSlashPos != std::string::npos || commentPos != std::string::npos)
      {
        std::cout << "19.2 : " << "illegal characters in inclusion directive : " << std::endl;
        std::cout << HashLoc.printToString(SM) << "\n" << std::endl;
      }

      if (FileName == "time.h")
      {
        std::cout << "20.12 : " << "stdlib time.h is included in the project. use is forbidden : " << std::endl;
        std::cout << HashLoc.printToString(SM) << "\n" << std::endl;
      }

      if (FileName == "stdio.h")
      {
        std::cout << "20.9 : " << "stdlib stdio.h is included in the project. use is forbidden : " << std::endl;
        std::cout << HashLoc.printToString(SM) << "\n" << std::endl;
      }

      if (FileName == "signal.h")
      {
        std::cout << "20.8 : " << "stdlib signal.h is included in the project. use is forbidden : " << std::endl;
        std::cout << HashLoc.printToString(SM) << "\n" << std::endl;
      }
    }
    else
    {
      size_t singleQPos = FileName.find("\'", 0);
      size_t whateverSlashPos = FileName.find("\\", 0);
      size_t commentPos = FileName.find("\\*", 0);

      if (singleQPos != std::string::npos || whateverSlashPos != std::string::npos || commentPos != std::string::npos)
      {
        std::cout << "19.2 : " << "illegal characters in inclusion directive : " << std::endl;
        std::cout << HashLoc.printToString(SM) << "\n" << std::endl;
      }
    }

    size_t whateverSlashPos = FileName.find("\\", 0);
    size_t theotherSlashPos = FileName.find("/", 0);

    if (whateverSlashPos != std::string::npos || theotherSlashPos != std::string::npos)
    {
      std::cout << "19.3 : " << "Include directive contains file address, not just name : " << std::endl;
      std::cout << HashLoc.printToString(SM) << "\n" << std::endl;
    }

  }

  virtual void MacroUndefined(const Token &MacroNameTok, const MacroDefinition &MD)
  {
    SourceLocation SL = MacroNameTok.getLocation();

    std::cout << "19.6 : " << "Use of #undef is illegal : " << std::endl;
    std::cout << SL.printToString(SM) << "\n" << std::endl;
  }

  virtual void MacroDefined(const Token &MacroNameTok, const MacroDirective *MD)
  {
    const MacroInfo* MI = MD->getMacroInfo();

    if (MI->isFunctionLike())
    {
      SourceLocation SL = MacroNameTok.getLocation();

      std::cout << "19.7 : " << "Function-like macro used : " << std::endl;
      std::cout << SL.printToString(SM) << "\n" << std::endl;
    }
  }

  virtual void MacroExpands(const Token &MacroNameTok, const MacroDefinition &MD, SourceRange Range, const MacroArgs *Args)
  {
    DefMacroDirective* DMD = MD.getLocalDirective();

    if (!DMD->isDefined())
    {
      std::cout << "19.11 : " << "Use of undefined macro : " << std::endl;
      std::cout << Range.getBegin().printToString(SM) << "\n" << std::endl;
    }
  }

private:
  const SourceManager &SM;
};
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
class MyASTConsumer : public ASTConsumer {

public:
  MyASTConsumer(Rewriter &R) : HandlerForCmpless(R), HandlerWhileCmpless(R), HandlerElseCmpless(R), HandlerIfCmpless(R), \
    HandlerForIfElse(R), HandlerForSwitchBrkLess(R), HandlerForSwitchDftLEss(R), HandlerForMCSwitch151(R), HandlerForMCSwitch155(R), \
    HandlerForMCFunction161(R), HandlerForFunction162(R), HandlerForFunction164(R), HandlerForFunction166(R), HandlerForFunction168(R), \
    HandlerForFunction169(R), HandlerForPA171(R), HandlerForSU184(R), HandlerForType6465(R), HandlerForDCDF81(R), HandlerForDCDF82(R), \
    HandlerForInit91(R), HandlerForInit92(R), HandlerForInit93(R), HandlerForExpr123(R), HandlerForExpr124(R), HandlerForExpr125(R), \
    HandlerForExpr126(R), HandlerForExpr127(R), HandlerForExpr128(R), HandlerForExpr129(R), HandlerForExpr1210(R), HandlerForExpr1213(R), \
    HandlerForCSE131(R), HandlerForCSE132(R), HandlerForCSE1332(R), HandlerForCSE134(R), HandlerForCSE136(R), HandlerForCF144(R), \
    HandlerForCF145(R), HandlerForCF146(R), HandlerForCF147(R), HandlerForCF148(R), HandlerForSwitch154(R), HandlerForPTC111(R), \
    HandlerForCSE137(R), HandlerForDCDF810(R), HandlerForFunction165(R), HandlerForFunction1652(R), HandlerForPointer171(R), \
    HandlerForPointer1723(R), HandlerForPointer174(R) {

    /*forstmts whithout a compound statement.*/
    Matcher.addMatcher(forStmt(unless(hasDescendant(compoundStmt()))).bind("mcfor"), &HandlerForCmpless);

    /*whilestmts without a compound statement.*/
    Matcher.addMatcher(whileStmt(unless(hasDescendant(compoundStmt()))).bind("mcwhile"), &HandlerWhileCmpless);

    /*else blocks that dont have a compound statemnt.*/
    Matcher.addMatcher(ifStmt(allOf(hasElse(unless(ifStmt())), hasElse(unless(compoundStmt())))).bind("mcelse"), &HandlerElseCmpless);

    /*if blocks that dont have a compound statement.*/
    Matcher.addMatcher(ifStmt(unless(hasDescendant(compoundStmt()))).bind("mcif"), &HandlerIfCmpless);

    /*if-elseif statements that are missing the else block.*/
    Matcher.addMatcher(ifStmt(allOf(hasElse(ifStmt()), unless(hasAncestor(ifStmt())), unless(hasDescendant(ifStmt(hasElse(unless(ifStmt()))))))).bind("mcifelse"), &HandlerForIfElse);

    Matcher.addMatcher(switchStmt(hasDescendant(compoundStmt(hasDescendant(switchCase(unless(hasDescendant(breakStmt()))))))).bind("mcswitchbrk"), &HandlerForSwitchBrkLess);

    Matcher.addMatcher(switchStmt(unless(hasDescendant(defaultStmt()))).bind("mcswitchdft"), &HandlerForSwitchDftLEss);

    Matcher.addMatcher(switchStmt(forEachDescendant(caseStmt(hasAncestor(compoundStmt().bind("mccmp151"))).bind("mccase151"))), &HandlerForMCSwitch151);

    Matcher.addMatcher(switchStmt(unless(hasDescendant(caseStmt()))).bind("mcswitch155"), &HandlerForMCSwitch155);

    Matcher.addMatcher(functionDecl().bind("mcfunction161"), &HandlerForMCFunction161);

    Matcher.addMatcher(functionDecl(forEachDescendant(callExpr().bind("mc162callexpr"))).bind("mc162funcdec"), &HandlerForFunction162);

    Matcher.addMatcher(functionDecl().bind("mcfunc164"), &HandlerForFunction164);

    Matcher.addMatcher(callExpr().bind("mcfunc166"), &HandlerForFunction166);

    Matcher.addMatcher(functionDecl(forEachDescendant(returnStmt().bind("mcfunc168"))), &HandlerForFunction168);

    Matcher.addMatcher(implicitCastExpr(unless(hasAncestor(callExpr()))).bind("mcfunc169"), &HandlerForFunction169);

    Matcher.addMatcher(varDecl().bind("mcpa171"), &HandlerForPA171);

    Matcher.addMatcher(recordDecl(isUnion()).bind("mcsu184"), &HandlerForSU184);

    Matcher.addMatcher(fieldDecl(isBitField()).bind("mctype6465"), &HandlerForType6465);

    Matcher.addMatcher(functionDecl().bind("mcdcdf81"), &HandlerForDCDF81);

    Matcher.addMatcher(varDecl().bind("mcdcdf82"), &HandlerForDCDF82);

    Matcher.addMatcher(varDecl().bind("mcinit91"), &HandlerForInit91);

    Matcher.addMatcher(initListExpr(hasAncestor(varDecl().bind("mcinit92daddy"))).bind("mcinit92"), &HandlerForInit92);

    Matcher.addMatcher(enumConstantDecl(anyOf(allOf(hasDescendant(integerLiteral().bind("mcinit93kiddy")), \
                                        hasAncestor(enumDecl().bind("mcinit93daddy"))), hasAncestor(enumDecl().bind("mcinit93daddy")))).bind("mcinit93"), &HandlerForInit93);

    Matcher.addMatcher(unaryExprOrTypeTraitExpr(hasDescendant(expr().bind("mcexpr123kiddy"))).bind("mcexpr123"), &HandlerForExpr123);

    Matcher.addMatcher(binaryOperator(allOf(eachOf(hasOperatorName("||"), hasOperatorName("&&")), hasRHS(expr().bind("mcexpr124")))), &HandlerForExpr124);

    Matcher.addMatcher(binaryOperator(allOf(eachOf(hasOperatorName("||"), hasOperatorName("&&")), \
                                            eachOf(hasRHS(allOf(expr().bind("lrhs"), unless(anyOf(implicitCastExpr() , declRefExpr(), callExpr(), floatLiteral(), integerLiteral(), stringLiteral()))))\
                                                , hasLHS(allOf(expr().bind("lrhs"), unless(anyOf(implicitCastExpr(), declRefExpr(), callExpr(), floatLiteral(), integerLiteral(), stringLiteral())))))))\
                       , &HandlerForExpr125);
    Matcher.addMatcher(binaryOperator(allOf(eachOf(hasOperatorName("||"), hasOperatorName("&&")), \
                                            eachOf(hasLHS(expr().bind("mcexpr126rl")), hasRHS(expr().bind("mcexpr126rl"))))), &HandlerForExpr126);

    Matcher.addMatcher(binaryOperator(allOf(eachOf(hasOperatorName("<<"), hasOperatorName(">>"), hasOperatorName("~"), hasOperatorName("<<="), \
                                            hasOperatorName(">>="), hasOperatorName("&"), hasOperatorName("&="), hasOperatorName("^"), hasOperatorName("^=")\
                                            , hasOperatorName("|"), hasOperatorName("|=")), eachOf(hasLHS(expr().bind("mcexpr127rl")), hasRHS(expr().bind("mcexpr127rl"))))), &HandlerForExpr127);
    Matcher.addMatcher(binaryOperator(allOf(eachOf(hasOperatorName(">>"), hasOperatorName(">>="), hasOperatorName("<<="), hasOperatorName("<<")), \
                                            hasLHS(expr().bind("mcexpr128lhs")) , hasRHS(expr().bind("mcexpr128rhs")))), &HandlerForExpr128);
    Matcher.addMatcher(unaryOperator(allOf(hasOperatorName("-"), hasUnaryOperand(expr().bind("mcexpr129")))), &HandlerForExpr129);

    Matcher.addMatcher(binaryOperator(allOf(hasOperatorName(","), hasLHS(expr().bind("mcexpr1210")))), &HandlerForExpr1210);

    Matcher.addMatcher(unaryOperator(allOf(eachOf(hasOperatorName("++"), hasOperatorName("--")), anyOf(hasAncestor(binaryOperator()), hasDescendant(binaryOperator())))).bind("mcexpr1213"), &HandlerForExpr1213);

    Matcher.addMatcher(binaryOperator(allOf(hasOperatorName("="), eachOf(hasLHS(expr().bind("cse131rlhs")), hasRHS(expr().bind("cse131rlhs"))))), &HandlerForCSE131);

    Matcher.addMatcher(ifStmt(hasCondition(expr(unless(hasDescendant(binaryOperator(anyOf(hasOperatorName("<")\
                                           , hasOperatorName(">"), hasOperatorName("=="), hasOperatorName("<="), hasOperatorName(">=")))))).bind("mccse132"))), &HandlerForCSE132);
    Matcher.addMatcher(binaryOperator(allOf(anyOf(hasOperatorName("<"), hasOperatorName(">"), hasOperatorName("<="), hasOperatorName(">="), hasOperatorName("==")), \
                                            eachOf(hasLHS(expr().bind("mccse1332rl")), hasRHS(expr().bind("mccse1332rl"))))).bind("mccse1332daddy"), &HandlerForCSE1332);
    Matcher.addMatcher(forStmt().bind("mccse134"), &HandlerForCSE134);

    Matcher.addMatcher(forStmt(forEachDescendant(stmt(eachOf(unaryOperator(allOf(anyOf(hasOperatorName("++"), hasOperatorName("--")), hasUnaryOperand(declRefExpr().bind("mccse136kiddo")))), \
                               binaryOperator(allOf(hasOperatorName("="), hasLHS(declRefExpr().bind("mccse136kiddo")))))))).bind("mccse136daddy"), &HandlerForCSE136);

    Matcher.addMatcher(gotoStmt().bind("mccf144"), &HandlerForCF144);

    Matcher.addMatcher(continueStmt().bind("mccf145"), &HandlerForCF145);

    Matcher.addMatcher(breakStmt(hasAncestor(stmt(anyOf(forStmt().bind("mccffofo"), doStmt().bind("mccfdodo"), whileStmt().bind("mccfwuwu"))))), &HandlerForCF146);

    Matcher.addMatcher(returnStmt(hasAncestor(functionDecl().bind("mccf147"))), &HandlerForCF147);

    Matcher.addMatcher(forStmt(unless(has(compoundStmt()))).bind("mccf148for"), &HandlerForCF148);

    Matcher.addMatcher(whileStmt(unless(has(compoundStmt()))).bind("mccf148while"), &HandlerForCF148);

    Matcher.addMatcher(doStmt(unless(has(compoundStmt()))).bind("mccf148do"), &HandlerForCF148);

    Matcher.addMatcher(switchStmt(unless(has(compoundStmt()))).bind("mccf148switch"), &HandlerForCF148);

    Matcher.addMatcher(switchStmt(hasCondition(expr().bind("mcswitch154"))).bind("mcswitch154daddy"), &HandlerForSwitch154);

    Matcher.addMatcher(declRefExpr().bind("mcptc111"), &HandlerForPTC111);

    Matcher.addMatcher(expr().bind("mccse137"), &HandlerForCSE137);

    Matcher.addMatcher(callExpr(hasAncestor(functionDecl().bind("mcdcdf810daddy"))).bind("mcdcdf810"), &HandlerForDCDF810);

    Matcher.addMatcher(functionDecl(allOf(returns(anything()), unless(returns(asString("void"))), hasBody(compoundStmt()) , unless(hasDescendant(returnStmt())))).bind("mcfunction165"), &HandlerForFunction165);

    Matcher.addMatcher(functionDecl(allOf(parameterCountIs(0), hasBody(compoundStmt()))).bind("mcfunction1652"), &HandlerForFunction1652);

    Matcher.addMatcher(declRefExpr(allOf(to(varDecl().bind("loco")), unless(hasParent(castExpr(hasCastKind(clang::CK_ArrayToPointerDecay)))), hasAncestor(stmt(eachOf(binaryOperator(hasOperatorName("+")).bind("bino"), \
                                         binaryOperator(hasOperatorName("-")).bind("bino"), unaryOperator(hasOperatorName("++")).bind("uno"), \
                                         unaryOperator(hasOperatorName("--")).bind("uno"), binaryOperator(hasOperatorName("/")).bind("bino"), \
                                         binaryOperator(hasOperatorName("*")).bind("bino"), binaryOperator(hasOperatorName("<")).bind("bino"), \
                                         binaryOperator(hasOperatorName("<=")).bind("bino"), binaryOperator(hasOperatorName(">")).bind("bino"), \
                                         binaryOperator(hasOperatorName(">=")).bind("bino")))))).bind("mcpointer171"), &HandlerForPointer171);

    /*start of 17.3 matchers*/
    Matcher.addMatcher(binaryOperator(allOf(hasOperatorName("<="), hasRHS(expr(anyOf(hasDescendant(declRefExpr(hasType(pointerType())).bind("mcpointer1723rhs")), \
                                            has(declRefExpr(hasType(pointerType())).bind("mcpointer1723rhs"))))), \
                                            hasLHS(expr(anyOf(hasDescendant(declRefExpr(hasType(pointerType())).bind("mcpointer1723lhs")), \
                                                has(declRefExpr(hasType(pointerType())).bind("mcpointer1723lhs"))))))).bind("mcpointer1723daddy"), &HandlerForPointer1723);

    Matcher.addMatcher(binaryOperator(allOf(hasOperatorName("<"), hasRHS(expr(anyOf(hasDescendant(declRefExpr(hasType(pointerType())).bind("mcpointer1723rhs")), \
                                            has(declRefExpr(hasType(pointerType())).bind("mcpointer1723rhs"))))), \
                                            hasLHS(expr(anyOf(hasDescendant(declRefExpr(hasType(pointerType())).bind("mcpointer1723lhs")), \
                                                has(declRefExpr(hasType(pointerType())).bind("mcpointer1723lhs"))))))).bind("mcpointer1723daddy"), &HandlerForPointer1723);

    Matcher.addMatcher(binaryOperator(allOf(hasOperatorName(">="), hasRHS(expr(anyOf(hasDescendant(declRefExpr(hasType(pointerType())).bind("mcpointer1723rhs")), \
                                            has(declRefExpr(hasType(pointerType())).bind("mcpointer1723rhs"))))), \
                                            hasLHS(expr(anyOf(hasDescendant(declRefExpr(hasType(pointerType())).bind("mcpointer1723lhs")), \
                                                has(declRefExpr(hasType(pointerType())).bind("mcpointer1723lhs"))))))).bind("mcpointer1723daddy"), &HandlerForPointer1723);

    Matcher.addMatcher(binaryOperator(allOf(hasOperatorName(">"), hasRHS(expr(anyOf(hasDescendant(declRefExpr(hasType(pointerType())).bind("mcpointer1723rhs")), \
                                            has(declRefExpr(hasType(pointerType())).bind("mcpointer1723rhs"))))), \
                                            hasLHS(expr(anyOf(hasDescendant(declRefExpr(hasType(pointerType())).bind("mcpointer1723lhs")), \
                                                has(declRefExpr(hasType(pointerType())).bind("mcpointer1723lhs"))))))).bind("mcpointer1723daddy"), &HandlerForPointer1723);

    Matcher.addMatcher(binaryOperator(allOf(hasOperatorName("-"), hasRHS(expr(anyOf(hasDescendant(declRefExpr(hasType(pointerType())).bind("mcpointer1723rhs")), \
                                            has(declRefExpr(hasType(pointerType())).bind("mcpointer1723rhs"))))), \
                                            hasLHS(expr(anyOf(hasDescendant(declRefExpr(hasType(pointerType())).bind("mcpointer1723lhs")), \
                                                has(declRefExpr(hasType(pointerType())).bind("mcpointer1723lhs"))))))).bind("mcpointer1723daddy"), &HandlerForPointer1723);

    Matcher.addMatcher(binaryOperator(allOf(hasOperatorName("-="), hasRHS(expr(anyOf(hasDescendant(declRefExpr(hasType(pointerType())).bind("mcpointer1723rhs")), \
                                            has(declRefExpr(hasType(pointerType())).bind("mcpointer1723rhs"))))), \
                                            hasLHS(expr(anyOf(hasDescendant(declRefExpr(hasType(pointerType())).bind("mcpointer1723lhs")), \
                                                has(declRefExpr(hasType(pointerType())).bind("mcpointer1723lhs"))))))).bind("mcpointer1723daddy"), &HandlerForPointer1723);
    /*end of 17.3 matchers*/

    /*start of 17.4 matchers*/
    Matcher.addMatcher(castExpr(allOf(hasCastKind(CK_ArrayToPointerDecay), unless(hasParent(arraySubscriptExpr())))).bind("mcpointer174"), &HandlerForPointer174);

    Matcher.addMatcher(declRefExpr(allOf(hasAncestor(expr(anyOf(binaryOperator(hasOperatorName("-=")), \
                                         unaryOperator(hasOperatorName("++")), unaryOperator(hasOperatorName("--")), \
                                         binaryOperator(hasOperatorName("+")), binaryOperator(hasOperatorName("+=")), \
                                         binaryOperator(hasOperatorName("-"))))), to(varDecl(hasType(pointerType()))))).bind("mcpointer1742"), &HandlerForPointer174);
    /*end of 17.4 matchers*/
  }

  void HandleTranslationUnit(ASTContext &Context) override {
    Matcher.matchAST(Context);
  }

private:
  MCForCmpless HandlerForCmpless;
  MCWhileCmpless HandlerWhileCmpless;
  MCElseCmpless HandlerElseCmpless;
  MCIfCmpless HandlerIfCmpless;
  IfElseMissingFixer HandlerForIfElse;
  MCSwitchBrkless HandlerForSwitchBrkLess;
  MCSwitchDftLess HandlerForSwitchDftLEss;
  MCSwitch151 HandlerForMCSwitch151;
  MCSwitch155 HandlerForMCSwitch155;
  MCFunction161 HandlerForMCFunction161;
  MCFunction162 HandlerForFunction162;
  MCFunction164 HandlerForFunction164;
  MCFunction166 HandlerForFunction166;
  MCFunction168 HandlerForFunction168;
  MCFunction169 HandlerForFunction169;
  MCPA171 HandlerForPA171;
  MCSU184 HandlerForSU184;
  MCTypes6465 HandlerForType6465;
  MCDCDF81 HandlerForDCDF81;
  MCDCDF82 HandlerForDCDF82;
  MCInit91 HandlerForInit91;
  MCInit92 HandlerForInit92;
  MCInit93 HandlerForInit93;
  MCExpr123 HandlerForExpr123;
  MCExpr124 HandlerForExpr124;
  MCExpr125 HandlerForExpr125;
  MCExpr126 HandlerForExpr126;
  MCExpr127 HandlerForExpr127;
  MCExpr128 HandlerForExpr128;
  MCExpr129 HandlerForExpr129;
  MCExpr1210 HandlerForExpr1210;
  MCExpr1213 HandlerForExpr1213;
  MCCSE131 HandlerForCSE131;
  MCCSE132 HandlerForCSE132;
  MCCSE1332 HandlerForCSE1332;
  MCCSE134 HandlerForCSE134;
  MCCSE136 HandlerForCSE136;
  MCCF144 HandlerForCF144;
  MCCF145 HandlerForCF145;
  MCCF146 HandlerForCF146;
  MCCF147 HandlerForCF147;
  MCCF148 HandlerForCF148;
  MCSwitch154 HandlerForSwitch154;
  MCPTC111 HandlerForPTC111;
  MCCSE137 HandlerForCSE137;
  MCDCDF810 HandlerForDCDF810;
  MCFunction165 HandlerForFunction165;
  MCFunction1652 HandlerForFunction1652;
  MCPointer171 HandlerForPointer171;
  MCPointer1723 HandlerForPointer1723;
  MCPointer174 HandlerForPointer174;
  MatchFinder Matcher;
};
/**********************************************************************************************************************/
/**********************************************************************************************************************/
class MyFrontendAction : public ASTFrontendAction
{
public:
  MyFrontendAction() {}

  std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI, StringRef file) override
  {
    CI.getPreprocessor().addPPCallbacks(llvm::make_unique<PPInclusion>(&CI.getSourceManager()));

    TheRewriter.setSourceMgr(CI.getSourceManager(), CI.getLangOpts());
    return llvm::make_unique<MyASTConsumer>(TheRewriter);
  }

private:
  Rewriter TheRewriter;
};
/**********************************************************************************************************************/
/*Main*/
int main(int argc, const char **argv)
{
  CommonOptionsParser op(argc, argv, MatcherSampleCategory);
  ClangTool Tool(op.getCompilations(), op.getSourcePathList());

  XMLDocOut.XMLCreateReport();

  int RunResult = Tool.run(newFrontendActionFactory<MyFrontendAction>().get());

  XMLDocOut.SaveReport();

  return RunResult;
}
/*last line intentionally left blank.*/
