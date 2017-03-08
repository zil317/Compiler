/*
  CSE 109
  Zihan Liu
  zil317
  Program Description: Make a Lexical analyzer
  Program #4
*/
#include <iostream>
#include <string>
#include <cstdlib>
#include "token.h"

Token::Token(int tokentype, string stringobject, int linenum, int charpos){
  ttype = tokentype;
  lexeme = stringobject;
  line = linenum;
  pos = charpos;
}

Token::Token(){
  Token(0,"",0,0);
}

Token::~Token(){}

int Token::getttype(){
  return ttype;
}

string Token::getlexeme(){
  return lexeme;
}
int Token::getline(){
  return line;
}
int Token::getpos(){
  return pos;
}


