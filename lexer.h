/*
  CSE 109
  Zihan Liu
  zil317
  Program Description: Make a Lexical analyzer
  Program #4
*/

#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>
#include "token.h"
using namespace std;

class Lexer{

 private:
  int pos;
  int line;
  char ch;
  istream& stream;

 public:
  Lexer(istream& in);

  //destructor
  ~Lexer();
  
  Token* nextToken();
  char nextChar();
};

#endif
