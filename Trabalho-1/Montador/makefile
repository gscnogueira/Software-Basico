CC=g++
BINARY=montador
INCDIR=./includes
CODEDIR=./src
OBJDIR=./obj
DEBUG=true
CFILES=$(wildcard $(CODEDIR)/*.cpp)
OBJFILES=$(patsubst $(CODEDIR)/%.cpp,$(OBJDIR)/%.o,$(CFILES))
INCS = $(wildcard $(INCDIR)/*.hpp)
FLAGS= -std=c++17 -Wall -I$(INCDIR)

$(shell mkdir -p $(OBJDIR))

ifeq ($(DEBUG),true)
	FLAGS += -g
endif

all: $(BINARY)

$(BINARY):$(OBJFILES)
	$(CC) $(FLAGS) -o $@ $^

obj/%.o:$(CODEDIR)/%.cpp $(INCS)
	$(CC) $(FLAGS) -c $< -o $@

run: $(BINARY)
	./montador mod1 mod2 mod3 mod4

clear:
	rm $(OBJFILES)

