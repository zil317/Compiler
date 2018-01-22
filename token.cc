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
  llexeme = stringobject;
  lline = linenum;
  ppos = charpos;
}

Token::Token(){
  Token(0,"",0,0);
}

Token::~Token(){}

int Token::type(){
  return ttype;
}

string Token::lexeme(){
  return llexeme;
}
int Token::line(){
  return lline;
}
int Token::pos(){
  return ppos;
}


