#include "token.h"
#include "lexer.h"
#include <iostream>
#include <fstream>

using namespace std;

void processFile(istream& in) {
  Lexer lexer(in);
  Token* tok;
  
  tok = lexer.nextToken();
  printf(" Type     Lexeme    Line #    Pos\n");
  while (tok->type() != Token::ENDOFFILE) {
    printf("%5d     %-10s %5d  %5d\n", tok->type(), tok->lexeme().c_str(), tok->line(), tok->pos());
    tok = lexer.nextToken();
  }
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
  
}
