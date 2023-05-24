CC=g++

BINARY=montador

INCDIR=./includes # diretórios que contem arquivos .hpp

CODEDIRS= ./src

FLAGS= -std=c++17 -Wall -I$(INCDIR)

# O Makefile é composto pela seguinte estrutura
# <build rule> : <dependencias necessarias para a build rule ser executada>
#	comando a ser executado

$(BINARY): main.o preprocessor.o
	$(CC) -o $@ $^

main.o: src/main.cpp
	$(CC) $(FLAGS) -c src/main.cpp

preprocessor.o: src/preprocessor.cpp
	$(CC)  $(FLAGS) -c src/preprocessor.cpp

run: $(BINARY)
	./montador exemplos/bin.asm

