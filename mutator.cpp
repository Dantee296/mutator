
/*first line intentionally left blank.*/
/**********************************************************************************************************************/
/*included modules*/
/*project headers*/
#include "mutator_aux.h"
/*standard headers*/
#include <string>
#include <iostream>
#include <cassert>
/*LLVM headers*/
#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Lex/Lexer.h"
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
/*the variable that holds the previously-matched SOC for class StmtTrap.*/
std::string g_linenoold;

static llvm::cl::OptionCategory MatcherSampleCategory("Matcher Sample");
/**********************************************************************************************************************/
/*matcher callback for something.*/
class FunctionHandler : public MatchFinder::MatchCallback {
public:
  FunctionHandler (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::BinaryOperator>("binopeq") != nullptr)
    {
      /*get the matched node.*/
      const BinaryOperator *BinOp = MR.Nodes.getNodeAs<clang::BinaryOperator>("binopeq");

      /*get the sourceloation.*/
      SourceLocation BinOpSL = BinOp->getLocStart();

      BinOpSL = Devi::SourceLocationHasMacro(BinOpSL, Rewrite, "start");
      /*does the sourcelocation include a macro expansion?*/

      /*replace it.*/
#if 0
      Rewrite.ReplaceText(BinOpSL, 2U , "XXX");
#endif
    }
    else
    {
      std::cout << "the macther -binopeq- returned nullptr!" << std::endl;
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class StmtTrapIf : public MatchFinder::MatchCallback {
public:
  StmtTrapIf (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run (const MatchFinder::MatchResult &MR)
  {
    /*just in case*/
    if (MR.Nodes.getNodeAs<clang::IfStmt>("iftrap") != nullptr)
    {
      /*getting the matched ifStmt.*/
      const IfStmt *TrapIf = MR.Nodes.getNodeAs<clang::IfStmt>("iftrap");

      /*getting the condition of the matched ifStmt.*/
      const Expr *IfCond = TrapIf->getCond();

      /*getting the sourcerange of the condition of the trapped ifstmt.*/
      SourceLocation TrapIfCondSL = IfCond->getLocStart();
      TrapIfCondSL = Devi::SourceLocationHasMacro(TrapIfCondSL, Rewrite, "start");
      SourceLocation TrapIfCondSLEnd = IfCond->getLocEnd();
      TrapIfCondSLEnd = Devi::SourceLocationHasMacro(TrapIfCondSLEnd, Rewrite, "end");
      SourceRange TrapIfCondSR;
      TrapIfCondSR.setBegin(TrapIfCondSL);
      TrapIfCondSR.setEnd(TrapIfCondSLEnd);

      /*replacing the condition with the utility trap function.*/
#if 0
      Rewrite.ReplaceText(TrapIfCondSR, "C_Trap_P()");
#endif
    }
    else
    {
      std::cout << "the matcher -iftrap- returned nullptr!" << std::endl;
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class StmtTrap : public MatchFinder::MatchCallback {
public:
  StmtTrap (Rewriter &Rewrite) : Rewrite(Rewrite) {}

  /*if there are more than 2 statements in the traditional sense in one line, the behavior is undefined.*/
  /*for now this class only finds an SOC. later to be used for something useful.*/
  virtual void run (const MatchFinder::MatchResult &MR)
  {
    /*out of paranoia*/
    if (MR.Nodes.getNodeAs<clang::Stmt>("stmttrap") != nullptr)
    {
      const Stmt *StmtTrapMR = MR.Nodes.getNodeAs<clang::Stmt>("stmttrap");

      SourceLocation STSL = StmtTrapMR->getLocStart();
      STSL = Devi::SourceLocationHasMacro(STSL, Rewrite, "start");
      SourceLocation STSLE = StmtTrapMR->getLocEnd();
      STSLE = Devi::SourceLocationHasMacro(STSLE, Rewrite, "end");

      /*just getting the SOC of the matched statement out of its sourcelocation.*/
      /*this only works since we are guaranteed the same and known matching pattern by MatchFinder.*/
      size_t startloc = 0U;
      size_t endloc = 0U;
      std::string lineno;
      startloc = STSL.printToString(*MR.SourceManager).find(":", 0U);
      endloc = STSLE.printToString(*MR.SourceManager).find(":", startloc + 1U);
      lineno = STSL.printToString(*MR.SourceManager).substr(startloc, endloc - startloc);

      /*just prints out the sourcelocations for diagnostics.*/
#if 0
      std::cout << STSL.printToString(*MR.SourceManager) << std::endl;
      std::cout << STSLE.printToString(*MR.SourceManager) << std::endl;
      std::cout << startloc << "---" << endloc << "---" << lineno << std::endl;
#endif

      /*have we matched a new SOC? if yes:*/
      if (lineno != g_linenoold)
      {
        SourceRange SR;
        SR.setBegin(StmtTrapMR->getLocStart());
        SR.setEnd(StmtTrapMR->getLocEnd());

#if 0
        Rewrite.InsertText(StmtTrapMR->getLocStart(), "XXX", "true", "true");
#endif
      }
      else
      {
        /*intentionally left blank.*/
      }

      /*set the string representing the old SOC line number to the one matched now.*/
      g_linenoold = lineno;
    }
    else
    {
      std::cout << "the matcher -stmttrap- returned nullptr!" << std::endl;
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class StmtRet : public MatchFinder::MatchCallback
{
public:
  StmtRet (Rewriter &Rewrite) : Rewrite (Rewrite) {}

  virtual void run (const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::ReturnStmt>("stmtret") != nullptr)
    {
      /*getting the returnstmt.*/
      const ReturnStmt *RetStmtMR = MR.Nodes.getNodeAs<clang::ReturnStmt>("stmtret");

      /*getting the sourcerange of the matched returnstmt.*/
      SourceLocation RSMR = RetStmtMR->getLocStart();
      RSMR = Devi::SourceLocationHasMacro(RSMR, Rewrite, "start");
      SourceLocation RSMRE = RetStmtMR->getLocEnd();
      RSMRE = Devi::SourceLocationHasMacro(RSMRE, Rewrite, "end");
      SourceRange RSMRSR;
      RSMRSR.setBegin(RSMR);
      RSMRSR.setEnd(RSMRE);

#if 0
      Rewrite.ReplaceText(RSMRSR, "C_Trap_P()");
#endif
    }
    else
    {
      std::cout << "matcher -stmtret- returned nullptr." << std::endl;
    }
  }

private:
  Rewriter &Rewrite;

};
/**********************************************************************************************************************/
class ForFixer : public MatchFinder::MatchCallback
{
public:
  ForFixer (Rewriter &Rewrite) : Rewrite (Rewrite) {}

  /*adds curly braces for forstmts that don't have it.*/
  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::ForStmt>("mrfor") != nullptr)
    {
      const ForStmt *MRFor = MR.Nodes.getNodeAs<clang::ForStmt>("mrfor");

      SourceLocation MRForSL = MRFor->getBody()->getLocStart();
      MRForSL = Devi::SourceLocationHasMacro(MRForSL, Rewrite, "start");
      SourceLocation MRForSLE = MRFor->getBody()->getLocEnd();
      MRForSLE = Devi::SourceLocationHasMacro(MRForSLE, Rewrite, "end");

      Rewrite.InsertText(MRForSL, "{\n", "true", "false");
      /*we're getting the endloc with an offset of 2 to accomodate unary operators like '++'.*/
      /*line-terminating semicolons are not included in the matches.*/
      Rewrite.InsertTextAfterToken(MRForSLE.getLocWithOffset(2U), "\n}");
    }
    else
    {
      std::cout << "matcher -mrfor- returned nullptr." << std::endl;
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class WhileFixer : public MatchFinder::MatchCallback
{
public:
  WhileFixer (Rewriter &Rewrite) : Rewrite (Rewrite) {}

  /*adds curly braces for whilestmts that don't have it.*/
  virtual void run (const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::WhileStmt>("mrwhile") != nullptr)
    {
      const WhileStmt *MRWhile = MR.Nodes.getNodeAs<clang::WhileStmt>("mrwhile");

#if 0
      std::cout << MRWhile->getBody()->getLocStart().printToString(*MR.SourceManager) << std::endl;
      std::cout << MRWhile->getBody()->getLocEnd().printToString(*MR.SourceManager) << std::endl;
#endif

      SourceLocation WFSL = MRWhile->getBody()->getLocStart();
      WFSL = Devi::SourceLocationHasMacro(WFSL, Rewrite, "start");
      SourceLocation WFSLE = MRWhile->getBody()->getLocEnd();
      WFSLE = Devi::SourceLocationHasMacro(WFSLE, Rewrite, "end");

      /*we're getting the endloc with an offset of 2 to accomodate unary operators like '++'.*/
      /*line-terminating semicolons are not included in the matches.*/
      Rewrite.InsertText(WFSL, "{\n", "true", "true");
      Rewrite.InsertTextAfterToken(WFSLE.getLocWithOffset(2U), "\n}");
    }
    else
    {
#if 1
      std::cout << "matcher -mrwhile- returned nullptr." << std::endl;
#endif
    }
  }


private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class IfFixer : public MatchFinder::MatchCallback
{
public:
  IfFixer (Rewriter &Rewrite) : Rewrite (Rewrite) {}

  /*adds curly braces to ifstmts that dont have it.*/
  virtual void run(const MatchFinder::MatchResult &MR)
  {
    if (MR.Nodes.getNodeAs<clang::IfStmt>("mrif") != nullptr)
    {
      const IfStmt *MRIf = MR.Nodes.getNodeAs<clang::IfStmt>("mrif");

      SourceLocation FFSL = MRIf->getThen()->getLocStart();
      FFSL = Devi::SourceLocationHasMacro(FFSL, Rewrite, "start");
      SourceLocation FFSLE = MRIf->getThen()->getLocEnd();
      FFSLE = Devi::SourceLocationHasMacro(FFSLE, Rewrite, "end");

      /*we're getting the endloc with an offset of 2 to accomodate unary operators like '++'.*/
      /*line-terminating semicolons are not included in the matches.*/
      Rewrite.InsertText(FFSL, "{\n", "true", "true");
      Rewrite.InsertTextAfterToken(FFSLE.getLocWithOffset(2U), "\n}");
    }
    else
    {
      std::cout << "matcher -- returned nullptr." << std::endl;
    }
  }

private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
class IfElseFixer : public MatchFinder::MatchCallback
{
public:
  IfElseFixer (Rewriter &Rewrite) : Rewrite (Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &MR)
  {
    /*underdev*/
    if (MR.Nodes.getNodeAs<clang::IfStmt>("mrifelse") != nullptr)
    {
      const IfStmt *ElseIf = MR.Nodes.getNodeAs<clang::IfStmt>("mrifelse");

      std::cout << "yolo" << std::endl;

      //Rewrite.InsertText(ElseIf->getThen()->getLocStart(), "{\n", "true", "true");
      Rewrite.InsertTextAfterToken(ElseIf->getLocEnd().getLocWithOffset(2U), "\nelse\n{\n}");
    }
    else
    {
      std::cout << "matcher -mrifelse- returned nullptr." << std::endl;
    }
  }


private:
  Rewriter &Rewrite;
};
/**********************************************************************************************************************/
/**********************************************************************************************************************/
class MyASTConsumer : public ASTConsumer {

public:
  MyASTConsumer(Rewriter &R) : HandlerForFunction(R), HandlerForIfTrap(R), HandlerForStmtTrap(R), HandlerForStmtRet(R), HandlerForFixer(R), HandlerForWhile(R), HandlerForIfFixer(R), HandlerForIfElse(R) {
    Matcher.addMatcher(binaryOperator(hasOperatorName("==")).bind("binopeq"), &HandlerForFunction);

    Matcher.addMatcher(ifStmt(hasCondition(anything())).bind("iftrap"), &HandlerForIfTrap);

    Matcher.addMatcher(stmt().bind("stmttrap") , &HandlerForStmtTrap);

    Matcher.addMatcher(returnStmt().bind("stmtret"), &HandlerForStmtRet);

    Matcher.addMatcher(forStmt(unless(hasDescendant(compoundStmt()))).bind("mrfor"), &HandlerForFixer);

    Matcher.addMatcher(whileStmt(unless(hasDescendant(compoundStmt()))).bind("mrwhile"), &HandlerForWhile);

    Matcher.addMatcher(ifStmt(unless(hasDescendant(compoundStmt()))).bind("mrif"), &HandlerForIfFixer);

    Matcher.addMatcher(ifStmt(allOf(hasElse(anything()), hasDescendant(ifStmt()), unless(hasAncestor(ifStmt())))).bind("mrifelse"), &HandlerForIfElse);
  }

  void HandleTranslationUnit(ASTContext &Context) override {
    Matcher.matchAST(Context);
  }

private:
  FunctionHandler HandlerForFunction;
  StmtTrapIf HandlerForIfTrap;
  StmtTrap HandlerForStmtTrap;
  StmtRet HandlerForStmtRet;
  ForFixer HandlerForFixer;
  WhileFixer HandlerForWhile;
  IfFixer HandlerForIfFixer;
  IfElseFixer HandlerForIfElse;
  MatchFinder Matcher;
};
/**********************************************************************************************************************/
class MyFrontendAction : public ASTFrontendAction {
public:
  MyFrontendAction() {}
  void EndSourceFileAction() override {
    TheRewriter.getEditBuffer(TheRewriter.getSourceMgr().getMainFileID()).write(llvm::outs());
  }

  std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI, StringRef file) override {
    TheRewriter.setSourceMgr(CI.getSourceManager(), CI.getLangOpts());
    return llvm::make_unique<MyASTConsumer>(TheRewriter);
  }

private:
  Rewriter TheRewriter;
};
/**********************************************************************************************************************/
/*Main*/
int main(int argc, const char **argv) {
  CommonOptionsParser op(argc, argv, MatcherSampleCategory);
  ClangTool Tool(op.getCompilations(), op.getSourcePathList());

  return Tool.run(newFrontendActionFactory<MyFrontendAction>().get());
}
/*last line intentionally left blank.*/
