//===-- HelloWorld.cpp - Example Transformations --------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "llvm/Transforms/Utils/HelloWorld.h"
#include "llvm/IR/CFG.h"
#include <vector>

using namespace llvm;

PreservedAnalyses HelloWorldPass::run(Function &F,
                                      FunctionAnalysisManager &AM) {

  errs() << "*************************************\n";
  long unsigned int basicBlockCount = 0;
  long unsigned int maxBasicBlockSize = 0;
  long unsigned int successorCount = 0;
  long unsigned int predecessorCount = 0;
  long unsigned int maxPredecessorCount = 0;
  long unsigned int maxSuccessorCount = 0;
  const char *maxSuccessorBlockName = "";
  const char *maxPredecessorBlockName = "";
  const char *maxBlockSizeName = "";

  std::vector<llvm::StringRef> bbWithMoreThanTwoPredeccors;
  std::vector<llvm::StringRef> bbWithMoreThanTwoSuccessors;

  errs() << "Function name " << F.getName() << "\n";

  for (BasicBlock &BB : F) {
    successorCount = 0;
    predecessorCount = 0;
    basicBlockCount += 1;

    if (BB.size() > maxBasicBlockSize) {
      maxBasicBlockSize = BB.size();
      maxBlockSizeName = BB.getName().data();
    }

    errs() << "--------------------------------------------\n";

    errs() << "Basic block ( name = " << BB.getName() << ") has " << BB.size()
           << " instructions "
           << "\n";
    errs() << "List of predeccors"
           << "\n";

    for (BasicBlock *pred : predecessors(&BB)) {
      predecessorCount += 1;
      errs() << "Pred -> " << pred->getName() << "\n";
    }

    if (predecessorCount > 2)
      bbWithMoreThanTwoPredeccors.push_back(BB.getName());

    errs() << "List of Successors"
           << "\n";
    for (BasicBlock *succ : successors(&BB)) {
      successorCount += 1;
      errs() << "Successor -> " << succ->getName() << "\n";
    }

    if (successorCount > 2)
      bbWithMoreThanTwoSuccessors.push_back(BB.getName());

    if (successorCount > maxSuccessorCount) {
      maxSuccessorCount = successorCount;
      maxSuccessorBlockName = BB.getName().data();
    }

    if (predecessorCount > maxPredecessorCount) {
      maxPredecessorCount = predecessorCount;
      maxPredecessorBlockName = BB.getName().data();
    }
    errs() << "--------------------------------------------\n";
  }

  errs() << "Number of Basic blocks in Function " << F.getName()
         << " is = " << basicBlockCount << "\n";

  errs() << "Max block = " << maxBlockSizeName << " with size "
         << maxBasicBlockSize << "\n";

  errs() << "BB with more than 2 predecessors \n";

  for (auto i = bbWithMoreThanTwoPredeccors.begin();
       i != bbWithMoreThanTwoPredeccors.end(); ++i) {
    errs() << *i << "\n";
  }

  errs() << "BB with more than 2 sucessors \n";

  for (auto i = bbWithMoreThanTwoSuccessors.begin();
       i != bbWithMoreThanTwoSuccessors.end(); ++i) {
    errs() << *i << "\n";
  }

  errs() << "BB with max predecessors " << maxPredecessorBlockName
         << maxPredecessorCount << "\n";
  errs() << "BB with max sucessors " << maxSuccessorBlockName
         << maxSuccessorCount << "\n";

  errs() << "*************************************\n";
  return PreservedAnalyses::all();
}
