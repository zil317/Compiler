/*
  CSE 109
  Zihan Liu
  zil317
  Program Description: Implement the parser and tree generator for
  Microc
  Program #5
*/
#include "token.h"
#include "lexer.h"
#include "parser.h"
#include <iostream>
#include <fstream>

using namespace std;

void processFile(istream& in) {
  Lexer lexer(in);
  Token token;
  Parser parser(lexer, cout);
  Parser::TreeNode* program = parser.block();
   cout << Parser::TreeNode::toString(program) << endl;
 
}

int main(int argc, char **argv) {
  ifstream in;
  
  if (argc > 1) {
      in.open(argv[1]);
      processFile(in);
      in.close();
  } else {
    processFile(cin);
  }
  return 0;
  
}
