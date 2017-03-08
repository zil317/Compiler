/*
  CSE 109
  Zihan Liu
  zil317
  Program Description: Make a Lexical analyzer
  Program #4
*/

#include"token.h"
#include"Lexer.h"

Lexer::Lexer(istream& in):stream(in){
  line =1;
  pos =0;
  ch = nextChar();
}

//desconstructor
Lexer::~Lexer(){}

char Lexer::nextChar(){
  //  cout<<"aaaaaaaaa"<<endl;
  ch = stream.get();
  pos++;
  //  cout<<ch<<endl;

  if(stream.eof()){
    return '$';
  }
  else if(ch =='\n'){
    line++;
    pos=0;
    return ' ';
  }
  else if(ch =='#'){
    ch = stream.get();

    while(!stream.eof() && ch != '\n'){
      ch = stream.get();
    }
    
    if(stream.eof()){
      return '$';
    } else {
      line++;
      pos = 0;
      return ' ';
    }    
  }
  
  return ch;
}

Token* Lexer::nextToken(){
  // cout<<"bbbbbb"<<endl;
  string token ="";
  int tokline;
  int tokpos;
  // bool flag;

  // flag == true;
  
 
  while(isspace(ch)){
    ch = nextChar();
  }
  tokline = line;
  tokpos = pos;

  if(ch=='$'){
    token+=ch;
    return new Token(Token::ENDOFFILE,token,tokline,tokpos);
  }

  //IDENT or Keyword
  else  if(isalpha(ch)){
      token+=ch;
      ch = nextChar();
      while(isdigit(ch)||isalpha(ch)||ch=='_'){
	token+=ch;
	ch=nextChar();
      }

    if(token == "if"){return new Token(Token::IF,token,tokline,tokpos);}
    if(token == "else"){return new Token(Token::ELSE,token,tokline,tokpos);}
    if(token == "while"){return new Token(Token::WHILE,token,tokline,tokpos);}
    if(token == "function"){
      Token* newtoken =  new Token(Token::FUNCTION,token,tokline,tokpos);
      return newtoken;}
    if(token == "var"){return new Token(Token::VAR,token,tokline,tokpos);}
    if(token == "return"){return new Token(Token::RETURN,token,tokline,tokpos);}

    else{
	return new Token(Token::IDENT,token,tokline,tokpos);
    }
  }
  //if the first char is a digit 
  else if(isdigit(ch)){
    token+=ch;
    ch = nextChar();
    while(isdigit(ch)){
      token+=ch;
      ch=nextChar();
    }
    return new Token(Token::INTLIT,token,tokline,tokpos);
  }

  //special character- operator and punctuation
  else if(ch == '+'|| ch == '-'||ch == '*'||ch =='/'||ch=='='||ch=='<'||ch=='<'||ch=='>'||ch=='('||ch==')'||ch=='{'||ch=='}'||ch==','||ch==';'){
    switch(ch){
    case '+': ch=nextChar(); return new Token(Token::PLUS,"+",tokline,tokpos);break;
    case '-': ch=nextChar(); return new Token(Token::MINUS,"-",tokline,tokpos);break;
    case '*': ch=nextChar(); return new Token(Token::TIMES,"*",tokline,tokpos);break;
    case '/': ch=nextChar(); return new Token(Token::DIVIDE,"/",tokline,tokpos);break;
    case '=':
	token+=ch;
	ch=nextChar();
	if(token == "==") {ch=nextChar();return new Token(Token::EQ,"==",tokline,tokpos);}
	else {return new Token(Token::ASSIGN,"=",tokline,tokpos);}
      
    case '!':
	token+=ch;
	ch=nextChar();
	if(token =="!=") {ch=nextChar();return new Token(Token::NE,"!=",tokline,tokpos);}
        else {return new Token(Token::ERROR,token,tokline,tokpos);}
      
    case '<':
	  token+=ch;
	  ch=nextChar();
	  
	  if(token == "<=") {ch=nextChar();return new Token(Token::LE,"<=",tokline,tokpos);} 
	  else {return new Token(Token::LT,"<",tokline,tokpos);}
	
    case '>':
	  token+=ch;
	  ch=nextChar();
	  if(token ==">=") {ch= nextChar(); return new Token(Token::GE,">=",tokline,tokpos);}
	  else {return new Token (Token::GT,">",tokline,tokpos);}

    case '&':
	token+=ch;
	ch=nextChar();
	if(token == "&&") {ch=nextChar(); return new Token(Token::AND,"&&",tokline,tokpos); }
	else {return new Token(Token::ERROR,token,tokline,tokpos);}

    case '|':
        token+=ch;
	ch=nextChar();
	if(token == "||") {ch=nextChar(); return new Token(Token::OR,"&&",tokline,tokpos);} 
	else {return new Token(Token::ERROR,token,tokline,tokpos);}
	  
    case '(':ch=nextChar(); return new Token(Token::LPAREN,"(",tokline,tokpos); break;
    case ')':ch=nextChar(); return new Token(Token::RPAREN,")",tokline,tokpos); break;
    case '{':ch=nextChar(); return new Token(Token::LBRACE,"{",tokline,tokpos); break;
    case '}':ch=nextChar(); return new Token(Token::RBRACE,"}",tokline,tokpos); break;
    case ',':ch=nextChar(); return new Token(Token::COMMA,",",tokline,tokpos); break;
    case ';':ch=nextChar(); return new Token(Token::SEMICOLON,";",tokline,tokpos); break;
      /* case '"':
	token+=ch;
	ch=nextChar();
	while(ch!='"'){
	  token+=ch;
	  ch=nextChar();
	}
	
      if(token == "\"") return Token(Token::STRINGLIT,token,tokline,tokpos);
      else return Token(Token::ERROR,token,tokline,tokpos);break;*/
    }
  }
  else if(ch =='"'){
    token+=ch;
    ch=nextChar();
    
    while(ch!='"'){
      token+=ch;
      ch=nextChar();
    
      if(ch == '"'){
	token +=ch;
	ch = nextChar();
	return new Token(Token::STRINGLIT,token,tokline,tokpos);
      }
    }
  }

  
  return new Token(Token::ERROR,"ERROR",tokline,tokpos);
}
      
      
	
      
    




    
	
    
 



      
 

