CC=g++

BINARY=montador

INCDIR=./includes # diretórios que contem arquivos .hpp

CODEDIRS= ./src

FLAGS= -std=c++17 -Wall -I$(INCDIR) -g

# O Makefile é composto pela seguinte estrutura
# <build rule> : <dependencias necessarias para a build rule ser executada>
#	comando a ser executado

$(BINARY): main.o preprocessor.o scanner.o parser.o
	$(CC) -o $@ $^

main.o: src/main.cpp
	$(CC) $(FLAGS) -c src/main.cpp

preprocessor.o: src/preprocessor.cpp
	$(CC)  $(FLAGS) -c src/preprocessor.cpp

scanner.o: src/scanner.cpp
	$(CC)  $(FLAGS) -c src/scanner.cpp

parser.o: src/parser.cpp
	$(CC)  $(FLAGS) -c src/parser.cpp

run: $(BINARY)
	./montador bin
