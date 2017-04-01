OPTS= -g -c -Wall -Werror

microc: token.o lexer.o parser.o microc.o
	g++ -o microc lexer.o token.o parser.o microc.o

microc.o: microc.cc parser.h token.h lexer.h
	g++ $(OPTS) microc.cc

Lexer.o: Lexer.cc lexer.h token.h
	g++ $(OPTS) lexer.cc

Token.o: token.cc token.h
	g++ $(OPTS) token.cc

parser.o: parser.cc parser.h lexer.h token.h
	g++ $(OPTS) parser.cc

clean: 
	rm -f *.o microc *~ 