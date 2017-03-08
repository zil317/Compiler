OPTS= -g -c -Wall -Werror

lextest: token.o Lexer.o lextest.o
	g++ -o lextest Lexer.o token.o lextest.o

lextest.o: lextest.cc Lexer.h token.h
	g++ $(OPTS) lextest.cc

Lexer.o: Lexer.cc Lexer.h token.h
	g++ $(OPTS) Lexer.cc

Token.o: token.cc token.h
	g++ $(OPTS) token.cc
clean: 
	rm -f *.o lextest *~ 