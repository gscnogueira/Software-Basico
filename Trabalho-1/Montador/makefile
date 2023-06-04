CC=g++

BINARY=montador

INCDIR=./includes # diretórios que contem arquivos .hpp

CODEDIRS= ./src

FLAGS= -std=c++17 -Wall -I$(INCDIR) -g

# O Makefile é composto pela seguinte estrutura
# <build rule> : <dependencias necessarias para a build rule ser executada>
#	comando a ser executado

$(BINARY): main.o preprocessor.o scanner.o parser.o lexererror.o sintaxerror.o
	$(CC) -o $@ $^

main.o: src/main.cpp
	$(CC) $(FLAGS) -c src/main.cpp

preprocessor.o: src/preprocessor.cpp
	$(CC)  $(FLAGS) -c src/preprocessor.cpp

scanner.o: src/scanner.cpp
	$(CC)  $(FLAGS) -c src/scanner.cpp

parser.o: src/parser.cpp
	$(CC)  $(FLAGS) -c src/parser.cpp

lexererror.o: src/lexererror.cpp
	$(CC) $(FLAGS) -c src/lexererror.cpp

sintaxerror.o: src/sintaxerror.cpp
	$(CC) $(FLAGS) -c src/sintaxerror.cpp

run: $(BINARY)
	./montador bin
