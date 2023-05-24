CC=g++
FLAGS= -std=c++17 -Wall
BINARY=montador

# essa é um build rule (): Dependências que a regra precisa para executar
# if you need to build this : all of this things have to be created
all: $(BINARY)

$(BINARY): src/main.cpp
	$(CC) -o $(BINARY) $(FLAGS) src/main.cpp

run: $(BINARY)
	./montador exemplos/bin.asm

