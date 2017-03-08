#include "token.h"
#include "Lexer.h"
#include <iostream>
#include <fstream>

using namespace std;

void processFile(istream& in) {
  Lexer lexer(in);
  Token* tok;
  
  tok = lexer.nextToken();
  printf(" Type     Lexeme    Line #    Pos\n");
  while (tok->getttype() != Token::ENDOFFILE) {
    printf("%5d     %-10s %5d  %5d\n", tok->getttype(), tok->getlexeme().c_str(), tok->getline(), tok->getpos());
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
