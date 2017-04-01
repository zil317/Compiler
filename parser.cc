/*
CSE 109
Zihan Liu
zil317
Program Description: Implement the parser and tree generator for Microc
Program #5
*/
#include "parser.h"
#include <cstring>

const string Parser::ops[] ={"ADD", "SUB","MULT","DIV","ISEQ","ISNE","ISLE","ISGE","ADD","OR","LOADL","LOADV","STORE","JUMP","JUMPF","CALL","RET","PRINTF","LABLE","SEQ"};




Parser::Parser(Lexer& lexerx, ostream& outx): lexer(lexerx), out(outx), lindex(1), tindex(1) {
  token = lexer.nextToken();
}

Parser::~Parser() {
}

void Parser::error(string message) {
  cerr << message << " Found " << token->lexeme() << " at line " << token->line() << " position " << token->pos() << endl;
  exit(1);
}

void Parser::check(int tokenType, string message) {
  if (token->type() != tokenType)
    error(message);
}

//<factor> ::= LPAREN <expression> RPAREN | INTLIT | IDENT | 
Parser::TreeNode* Parser::factor() {
  TreeNode* node = NULL;
  int tokenType = token->type();
  switch(tokenType){
  case Token::LPAREN:
    token=lexer.nextToken();
    node = expression();
    check(Token::RPAREN,"Expected a )");
    break;
  case Token::INTLIT:
    token=lexer.nextToken();
    node = new TreeNode(LOADL,token->lexeme());
    break;
  case Token::IDENT:
    token = lexer.nextToken();
    node = new TreeNode(LOADV,token->lexeme());
    break;
  default:
    error("Expecting integer, literal, variable or (");
  }
  token = lexer.nextToken();
  return node;
}

//<term> ::= <factor> { TIMES <factor> | DIVIDE <factor> }
Parser::TreeNode* Parser::term() {
  TreeNode* root = factor();
  TreeNode* newfactorNode;
  int tokenType = token->type();
  while(tokenType == Token::TIMES || tokenType == Token::DIVIDE){
    token = lexer.nextToken();
    newfactorNode = factor();
    switch(tokenType){
    case Token::TIMES:
      root = new TreeNode(MULT, root,newfactorNode);
      break;
    case Token::DIVIDE:
      root = new TreeNode(DIV, root, newfactorNode);
      break;  
    }
    tokenType = token->type();
  }
  return root;
}

//<expression> ::= <term> { PLUS <term> | MINUS <term> }
Parser::TreeNode* Parser::expression() {
  TreeNode* root = term();
  TreeNode* newtermNode;
  int tokenType = token->type();
  while(tokenType == Token::PLUS || tokenType == Token::MINUS){
    token = lexer.nextToken();
    newtermNode = term(); 
    switch(tokenType){
    case Token::PLUS:
      root = new TreeNode(ADD,root,newtermNode);
      break;
    case Token::MINUS:
      root = new TreeNode(SUB,root,newtermNode);
      break;
    }
    tokenType = token->type();
  }
  return root;
}

/*<relationalexpression> ::= <expression> [ EQ <expression> | LT
<expression> | LE <expression> | GT <expression> | GE <expression> |
NE <expression> ]*/

Parser::TreeNode* Parser::relationalExpression() {
  TreeNode* root = expression();
  int tokenType = token->type();
  if(tokenType == Token::EQ){
    token = lexer.nextToken();
    TreeNode* rightNode = expression();
    return new TreeNode(ISEQ,root, rightNode);
  }
  if(tokenType == Token::LT){
    token = lexer.nextToken();
    TreeNode* rightNode = expression();
    return new TreeNode(ISLT,root,rightNode);
  }
  else if(tokenType == Token::LE){
    token = lexer.nextToken();
    TreeNode* rightNode = expression();
    return new TreeNode(ISLE,root,rightNode);
  }
  else if(tokenType == Token::GT){
    token = lexer.nextToken();
    TreeNode* rightNode = expression();
    return new TreeNode(ISGT,root,rightNode);
  }
  else if(tokenType == Token::GE){
    token = lexer.nextToken();
    TreeNode* rightNode = expression();
    return new TreeNode(ISGE,root,rightNode);
  }
  else if(tokenType == Token::NE){
    token = lexer.nextToken();
    TreeNode* rightNode = expression();
    return new TreeNode(ISNE,root,rightNode);
  }
  else{
    error("Relational expression is not found");
  }
  return root;  
}

//<logicalexpression> ::= <relationalexpression> { AND
//<relationalexpression> | OR <relationalexpression>

Parser::TreeNode* Parser::logicalExpression() {
  TreeNode* root = relationalExpression();
  TreeNode* relationalexpressionNode;
  int tokenType = token->type();
  while(tokenType == Token::AND || tokenType == Token::OR){
    token = lexer.nextToken();
    relationalexpressionNode = relationalExpression();
    switch(tokenType){
    case Token::AND:
      root = new TreeNode(AND,root,relationalexpressionNode);
      break;
    case Token::OR:
      root = new TreeNode(OR,root,relationalexpressionNode);
      break;
    }
  }
  return root;
}

//<statement> ::= <assignstatement> | <whilestatement> | <ifstatement> | <returnstatement>
Parser::TreeNode* Parser::statement() {
  TreeNode* statementNode;
  int tokenType = token->type();
  if(tokenType == Token::ASSIGN){
    statementNode = assignStatement();
  }else if(tokenType == Token::WHILE){
    statementNode = whileStatement();
  }else if(tokenType == Token::IF){
    statementNode = ifStatement();
  }else{
    error("statement is not found");
  }
  return statementNode;
}

//<block> ::= LBRACE { <statement> } RBRACE 
Parser::TreeNode* Parser::block(){
  check(Token::LBRACE,"( is expected");
  token = lexer.nextToken();
  
  TreeNode* root = statement();
  TreeNode* node = NULL; 
  int tokenType = token->type();
  while(tokenType==Token::ASSIGN||tokenType==Token::IF||tokenType==Token::WHILE){
    node = statement();
    root = new TreeNode(SEQ,root,node);
  }
  check(Token::RBRACE,") is expected");
  token = lexer.nextToken();
  
  return root;
}

//<ifstatement> ::= IF LPAREN <logicalexpression> RPAREN <block> [ELSE
//<block>]
Parser::TreeNode* Parser::ifStatement(){

  token=lexer.nextToken();
  //check for LPAREN
  //call nextToken
  //call logical statement - generate a tree node - save the tree node
  //check for RPAREN
  //call for nextToken
  //call the function
  //call block statement - save the tree node
  //look to see if the current token is else
  //call next token and call block-end with two or three pointers 

  TreeNode* root = NULL;
  TreeNode* logic= NULL;
  TreeNode* thenBlock = NULL;
  TreeNode* elseBlock = NULL;
  string firstLabel = NULL;
  string secondLabel = NULL;
  TreeNode* jumpfNode = new TreeNode(JUMPF,firstLabel);
  TreeNode* jumpNode = new TreeNode(JUMP,secondLabel);
  TreeNode* firstLabelNode = new TreeNode(LABEL,firstLabel);
  TreeNode* secondLabelNode = new TreeNode(LABEL,secondLabel);

  check(Token::LPAREN,"( is expected");
  token = lexer.nextToken();
  logic = logicalExpression();
  check(Token::RPAREN, ") is expected");
  token = lexer.nextToken();
  thenBlock = block();

  if(token->type()==Token::ELSE){
    token = lexer.nextToken();
    elseBlock = block();
    root = logicalExpression();
    root = new TreeNode(SEQ,root,jumpfNode);
    root = new TreeNode(SEQ, root, thenBlock);
    root = new TreeNode(SEQ, root, jumpNode);
    root = new TreeNode(SEQ, root, firstLabelNode);
    root = new TreeNode(SEQ, root, elseBlock);
    root = new TreeNode(SEQ, root, secondLabelNode);
  }

  else{
    root = logicalExpression();
    root = new TreeNode(SEQ,root, jumpfNode);
    root = new TreeNode(SEQ, root, thenBlock);
    root = new TreeNode(SEQ, root, firstLabelNode);
  }
  return root;
}
    
    
    

    
    /*  TreeNode* root = logicalExpression();
  root = new TreeNode(SEQ,root,jumpfNode);
  root = new TreeNode(SEQ, root, thenBlock);
  root = new TreeNode(SEQ, root, jumpNode);
  root = new TreeNode(SEQ, root, firstLabelNode);
  root = new TreeNode(SEQ, root, elseBlock);
  root = new TreeNode(SEQ, root, secondLabelNode);
    */


//<whilestatement> ::= WHILE LPAREN <logicalexpression> RPAREN <block>
Parser::TreeNode* Parser::whileStatement(){
  TreeNode* logic = NULL;
  TreeNode* blockNode = NULL;
  check(Token::WHILE,"WHILE is expected");
  token = lexer.nextToken();
  check(Token::LPAREN,"( is expected");
  logic = logicalExpression();
  check(Token::RPAREN,") is expected");
  token = lexer.nextToken();
  blockNode = block();

  string firstLabel = NULL;
  string secondLabel = NULL;
  TreeNode* jumpfNode = new TreeNode(JUMPF,secondLabel);
  TreeNode* jumpNode = new TreeNode(JUMP,firstLabel);
  TreeNode* root = new TreeNode(LABEL,firstLabel);
  TreeNode* secondLabelNode = new TreeNode(LABEL,secondLabel);
  // TreeNode* root = firstLabelNode;

  root = new TreeNode(SEQ,root,logic);
  root = new TreeNode(SEQ,root, jumpfNode);
  root = new TreeNode(SEQ,root, blockNode);
  root = new TreeNode(SEQ,root, jumpNode);
  root = new TreeNode(SEQ, root, secondLabelNode);
  return root;
}

//<assignstatement> ::= IDENT ASSIGN <logicalexpression> SEMICOLON
Parser::TreeNode* Parser::assignStatement(){
  TreeNode* expressionNode = NULL;
  TreeNode* root = NULL;
  check(Token::IDENT,"IDENT is expected");
  string s  = token->lexeme();
  token = lexer.nextToken();
  check(Token::ASSIGN,"ASSIGN is expected");
  TreeNode* store = new TreeNode(STOREV, s);
  token = lexer.nextToken();
  expressionNode = expression();
  root = new TreeNode(SEQ,expressionNode,store);
  check(Token::SEMICOLON, "SEMICOLON is expected");
  token = lexer.nextToken();
  return root;
}



  
 
 
 
   
   
   
   
   
