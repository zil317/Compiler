/*
  CSE 109
  Zihan Liu
  zil317
  Program Description: Make a Lexical analyzer
  Program #4
*/
#include<iostream>
#include<cstdio>
#include"token.h"
#include"Lexer.h"
#include<string>
#include<cctype>

using namespace std;

Lexer::Lexer(istream& input):stream(input){
  line =1;
  pos =0;
  ch = nextChar();
}

//desconstructor
Lexer::~Lexer(){}

char Lexer::nextChar(){
  ch = stream.get();
  pos++;

  if(stream.eof()){
    return '$';
  }
  else if(ch =='\n'){
    return ' ';
  }
  else if(ch =='#'){
    ch = stream.get();
    if(stream.eof()){
      return '$';
    }
    else{
      while(ch!='#'){
	if(ch =='\n'){
	  line++;
	  pos=0;
	}
	else{
	  pos++;
	}
	ch=stream.get();
      }
      return ' ';
    }
  }
  else return ch;
}

Token Lexer::nextToken(){
  string token ="";
  int tokline;
  int tokpos;
  int count;
  string digit="";
  count = 0;
  
  if(ch == '\n'){
    line++;
    pos++;
    ch = nextChar();
  }
  while(isspace(ch)){
    ch = nextChar();
  }
  tokline = line;
  tokpos = pos;

  //IDENT or Keyword
  if(isalpha(ch)){
    while(ch!=' '&&ch!='\n'&&ch!='$'){
      token+=ch;
      if(isalpha(ch) || isdigit(ch)){
	count++;
      }
      ch= nextChar();
    }
    if(token == "if"){return Token(Token::IF,token,tokline,tokpos);}
    if(token == "else"){return Token(Token::ELSE,token,tokline,tokpos);}
    if(token == "while"){return Token(Token::WHILE,token,tokline,tokpos);}
    if(token == "function"){return Token(Token::FUNCTION,token,tokline,tokpos);}
    if(token == "var"){return Token(Token::VAR,token,tokline,tokpos);}
    if(token == "return"){return Token(Token::RETURN,token,tokline,tokpos);}

    else{
      if(count==0){
	cout<<"0";
	return Token(Token::ERROR,token,tokline,tokpos);
      }
      else{
	return Token(Token::IDENT,token,tokline,tokpos);
      }
    }
  }
  //if the first char is a digit 
  else if(isdigit(ch)){
    if(ch=='0'){
      digit=+ch;
      ch=nextChar();
      if(ch == 'x'){
	digit=+ch;
	ch=nextChar();
	while(ch!=' '&&ch!='\n'&&ch!='$'){
	  token+=ch;
	  if(!isxdigit(ch)){
	    count++;
	  }
	  ch=nextChar();
	}
	digit+=token;
	if(count==0){
	  return Token(Token::INTLIT,digit,tokline,tokpos);
	}
	else{
	  return Token(Token::ERROR,digit,tokline,tokpos);
	}
      }
      else if(ch==' '){
	return Token(Token::INTLIT,digit,tokline,tokpos);
      }
      else{
	while(ch!=' '&&ch!='\n'&&ch!='$'){
	  digit+=ch;
	  ch=nextChar();
	}
	return Token(Token::ERROR,digit,tokline,tokpos);
      }
    }
    else{
      while(ch!=' '&&ch!='\n'&&ch!='$'){
	token+=ch;
	if(!isdigit(ch)){
	  count++;
	}
	ch=nextChar();
      }
      if(count!=0){return Token(Token::ERROR,token,tokline,tokpos);}
      else {return Token(Token::INTLIT,token,tokline,tokpos);}
    }
  }

  //special character- operator and punctuation
  else{
    switch(ch){
    case '+': ch=nextChar(); return Token(Token::PLUS,"+",tokline,tokpos);break;
    case '-': ch=nextChar(); return Token(Token::MINUS,"-",tokline,tokpos);break;
    case '*': ch=nextChar(); return Token(Token::TIMES,"*",tokline,tokpos);break;
    case '/': ch=nextChar(); return Token(Token::DIVIDE,"/",tokline,tokpos);break;
    case '=':
      while(ch!=' '&&ch!='\n'&&ch!='$'){
	token+=ch;
	ch=nextChar();
      }
      if(token == "==")return Token(Token::EQ,"==",tokline,tokpos);
      else if(token == "=") return Token(Token::ASSIGN,"=",tokline,tokpos);
      else return Token(Token::ERROR,token,tokline,tokpos);break;
    case '!':
      while(ch!=' '&&ch!='\n'&&ch!='$'){
	token+=ch;
	ch=nextChar();
      }
      if(token =="!=") return Token(Token::NE,"!=",tokline,tokpos);
      else return Token(Token::ERROR,token,tokline,tokpos);break;
    case '<':
	while(ch!=' '&&ch!='\n'&&ch!='$'){
	  token+=ch;
	  ch=nextChar();
	}
	if(token == "<") return Token(Token::LT,"<",tokline,tokpos); 
	else if (token == "<=") return Token(Token::LE,"<=",tokline,tokpos);
	else return Token(Token::ERROR,token,tokline,tokpos);break;
    case '>':
	while(ch!=' '&&ch!='\n'&&ch!='$'){
	  token+=ch;
	  ch=nextChar();
	}
	if(token == ">") return Token(Token::GT,">",tokline,tokpos); 
	else if(token ==">=") return Token(Token::GE,">=",tokline,tokpos);
	else return Token(Token::ERROR,token,tokline,tokpos);break;
    case '&':
      while(ch!=' '&&ch!='\n'&&ch!='$'){
	token+=ch;
	ch=nextChar();
      }
      if(token == "&&") return Token(Token::AND,"&&",tokline,tokpos); 
      else return Token(Token::ERROR,token,tokline,tokpos);break;

    case '|':
      while(ch!=' '&&ch!='\n'&&ch!='$'){
        token+=ch;
	ch=nextChar();
      }
      if(token == "||") return Token(Token::OR,"&&",tokline,tokpos); 
      else return Token(Token::ERROR,token,tokline,tokpos);break;
	  
    case '(':ch=nextChar(); return Token(Token::LPAREN,token,tokline,tokpos); break;
    case ')':ch=nextChar(); return Token(Token::RPAREN,token,tokline,tokpos); break;
    case '{':ch=nextChar(); return Token(Token::LBRACE,token,tokline,tokpos); break;
    case '}':ch=nextChar(); return Token(Token::RBRACE,token,tokline,tokpos); break;
    case ',':ch=nextChar(); return Token(Token::COMMA,token,tokline,tokpos); break;
    case ';':ch=nextChar(); return Token(Token::SEMICOLON,token,tokline,tokpos); break;
    case '$':return Token(Token::ENDOFFILE,"$",tokline,tokpos); break;
    case '"':
      while(ch!=' '&&ch!='\n'&&ch!='$'){
	token+=ch;
	if(ch == '"'){
	  count++;
	}
	ch=nextChar();
      }
      if(token == "\"") return Token(Token::STRINGLIT,token,tokline,tokpos);
      else return Token(Token::ERROR,token,tokline,tokpos);break;
    }
  }
  while(ch==' '){
    ch =nextChar();
  }
  return Token(Token::ERROR,"ERROR",tokline,tokpos);
}
      
      
	
      
    




    
	
    
 



      
 

