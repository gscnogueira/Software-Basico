CC=g++
BINARY=ligador
INCDIR=./includes
CODEDIR=./src
OBJDIR=./obj
DEBUG=false
CFILES=$(wildcard $(CODEDIR)/*.cpp)
OBJFILES=$(patsubst $(CODEDIR)/%.cpp,$(OBJDIR)/%.o,$(CFILES))
FLAGS= -std=c++17 -Wall -I$(INCDIR)

$(shell mkdir -p $(OBJDIR))

ifeq ($(DEBUG),true) 
	FLAGS += -g
endif

all: $(BINARY)

$(BINARY):$(OBJFILES)
	$(CC) $(FLAGS) -o $@ $^

obj/%.o:$(CODEDIR)/%.cpp
	$(CC) $(FLAGS) -c $^ -o $@

run:$(BINARY)
	./ligador exemplos/ex1 exemplos/ex2

clear:
	rm $(OBJFILES)
