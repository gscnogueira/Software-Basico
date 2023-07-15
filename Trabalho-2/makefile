BINARY = calculadora
NASM = nasm
LINKER = ld
NASM_FLAGS = -f elf
LINKER_FLAGS = -m elf_i386
ASMFILES=$(wildcard *.asm)
OBJFILES=$(patsubst %.asm,%.o,$(ASMFILES))

all:$(BINARY)

$(BINARY):$(OBJFILES)
	$(LINKER) $(LINKER_FLAGS) -o $@ $^

%.o:%.asm
	$(NASM) $(NASM_FLAGS) -o $@ $^



