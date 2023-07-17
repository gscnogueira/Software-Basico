;Procedimento para compilar
;nasm -f elf -o hello.o hello.asm
;ld -o hello hello.o
;ld -m elf_i386 -s -o hello hello.o
;./hello

; coisas uteis a se saber :
; syscall 3 e 4 retornam a quantidade de bytes lidos e escritos em eax

section .data

message1 db "Bem-vindo. Digite seu nome:",0
size_message1 equ $-message1

message2 db "Hola, ",0
size_message2 equ $-message2

message3 db ", bem-vindo ao programa de CALC IA-32.",0
size_message3 equ $-message3

message4 db "Vai trabalhar com 16 ou 32 bits (digite 0 para 16, e 1 para 32):",0
size_message4 equ $-message4

message5 db "ESCOLHA UMA OPÇÃO:",0
size_message5 equ $-message5

message6 db "DIGITE UM NUMERO:",0
size_message6 equ $-message6

message7 db "DIGITE OUTRO NUMERO:",0
size_message7 equ $-message7

message8 db "O RESULTADO E:",0
size_message8 equ $-message8

message9 db "OCORREU OVERFLOW",0
size_message9 equ $-message9

message10 db "DIGITE ENTER PARA CONTINUAR",0
size_message10 equ $-message10

option1 db "- 1: SOMA",0
size_option1 equ $-option1

option2 db "- 2: SUBTRACAO",0
size_option2 equ $-option2

option3 db "- 3: MULTIPLICACAO",0
size_option3 equ $-option3

option4 db "- 4: DIVISAO",0
size_option4 equ $-option4

option5 db "- 5: EXPONENCIACAO",0
size_option5 equ $-option5

option6 db "- 6: MOD",0
size_option6 equ $-option6

option7 db "- 7: SAIR",0
size_option7 equ $-option7

new_line db 0dh,0ah
size_new_line equ $-new_line

section .bss

size_name_user equ 250
name_user resb size_name_user

size_response_precision equ 2
response_precision resb size_response_precision

size_response_menu_option equ 2
response_menu_option resb size_response_menu_option

section .text

global _start
global print_number_32_bits
global print_number_16_bits
global overflow_treatment

global get_op1
global get_op2
global show_result_msg

extern sum_16
extern sum_32
extern sub_16
extern sub_32
extern _mul
extern _div
extern _exp
extern _mod

_start:
	call setup_calculator
Loop_calculator:
	call select_operation
	call execute_operation
	jmp	Loop_calculator
	
setup_calculator:
	push message1
	push size_message1	
	call output_message
	push new_line
	push size_new_line
	call output_message
	push name_user
	push size_name_user
	call input_message 
	push message2
	push size_message2	
	call output_message
	push name_user
	push size_name_user	
	call output_message
	push message3
	push size_message3	
	call output_message
	push new_line
	push size_new_line
	call output_message
	push message4
	push size_message4	
	call output_message
	push new_line
	push size_new_line
	call output_message
	push response_precision
	push size_response_precision
	call input_message 	
	ret

output_message:
	enter 0,0
	mov dword eax, 4
	mov dword ebx, 1
	mov	dword ecx, [ebp+12]
	mov dword edx, [ebp+8]
	int 080h
	leave
	ret 8

input_message:
	enter 0,0
	mov dword eax, 3
	mov dword ebx, 0
	mov dword ecx, [ebp+12]
	mov dword edx, [ebp+8]
	int 080h
	mov byte [ecx + eax-1], 0 ; retira a quebra de linha lida pelo input
	leave 
	ret 8

; recolhe um número de 32 bits do terminal em ascii e transforma para decimal
; e retorna em eax o número em decimal
input_number_32_bits:
	enter 6,0				; aloca uma dword e dois byte para variaveis locais
	mov dword [ebp-4], 0	; limpa possiveis valores que estavam na pilha
	mov byte [ebp-6], 0		; setamos a flag de número negativo como zero no começo
	lea ecx, [ebp-5]		; passa o endereço de memoria da variavel local 
	mov edx, 1				; seta o tamanho do buffer como 1
read_loop:
	mov eax, 3				; chama o serviço de leitura
	mov ebx, 0				; especifica o descritor do arquivo como sendo o stdin
	int 080h					; chama a interrupção
	cmp byte [ebp-5], 10	; compara o byte em ebp-5 com newline
	je 	end_read_loop		; se for new line sai da leitura 
	cmp byte [ebp-5], 45	; verifica se tem o caracter ascii -
	jne jump_flag_neg_input	; se não tiver pula a parte onde setamos a flag de número negativo
	mov	byte [ebp-6], 1		; setamos a flag de número negativo
	jmp read_loop			; pulamos para read_loop para ler o proximo caracter
jump_flag_neg_input:
	shl dword [ebp-4], 1   	; multiplica por 2
	mov dword eax, [ebp-4] 	; coloca em eax o valor multiplicado por 2
	shl dword [ebp-4], 2   	; multiplica por 4 -> total 8
	add dword [ebp-4], eax 	; adiciona o multiplicado por 2 -> total 10
	mov	byte bl, [ebp-5]	; move o byte lido para o registrador bl
	sub byte bl, 030h		; transforma o ascii para decimal
	add dword [ebp-4], ebx	; adiciona a double word em ebp-4
	jmp read_loop			; volta para pegar o proximo caracter
end_read_loop:
	mov eax, [ebp-4] 		; retorna o número calculado em decimal
	cmp byte [ebp-6], 1		; verifica se a flag de número negativo foi setada
	jne jmp_convert_neg		; se não pula as instruções para tornar o número negativo
	sub eax, 1				; subtrai um do número positivo
	xor eax, 0FFFFFFFFh		; inverte todos os 32 bits
jmp_convert_neg:
	leave 					; desaloca espaço para as variaveis locais
	ret 					; retorna para a função que chamou

input_number_16_bits:
	enter 4,0				
	mov word [ebp-2], 0		
	mov byte [ebp-4], 0		
	lea ecx, [ebp-3]		
	mov edx, 1				
read_loop2:
	mov eax, 3				
	mov ebx, 0				
	int 080h				
	cmp byte [ebp-3], 10	
	je 	end_read_loop2		
	cmp byte [ebp-3], 45	
	jne jump_flag_neg_input2
	mov	byte [ebp-4], 1		
	jmp read_loop2			
jump_flag_neg_input2:
	shl word [ebp-2], 1   	
	mov word ax, [ebp-2] 	
	shl word [ebp-2], 2   	
	add word [ebp-2], ax 	
	mov	byte bl, [ebp-3]	
	sub byte bl, 030h		
	add word [ebp-2], bx	
	jmp read_loop2			
end_read_loop2:
	mov ax, [ebp-2] 		
	cmp byte [ebp-4], 1		
	jne jmp_convert_neg2	
	sub ax, 1				
	xor ax, 0FFFFh			
jmp_convert_neg2:
	leave
	ret

print_number_16_bits:
	enter 1,0
	mov ax, [ebp+8]
	mov cx, ax
	and cx, 08000h
	cmp cx,0
	mov byte [ebp-1],0		
	je jump_flag_neg_print2	
	xor ax, 0FFFFh
	add ax, 1
	mov byte [ebp-1],1
jump_flag_neg_print2:
	mov bx, 10
	xor ecx, ecx
Loop_transform_to_ascii2:
	xor edx, edx
	div bx
	add dx, 030h
	dec ecx
	dec	esp
	mov byte [ebp-1+ecx], dl
	cmp ax, 0
	je	end_transform_to_ascii2
	jmp Loop_transform_to_ascii2
end_transform_to_ascii2:
	mov	esi, ecx
	cmp byte [ebp-1], 0
	je Loop_print_number_16_bits
	mov byte [ebp-1], 45
	mov eax, 4
	mov ebx, 1
	lea	ecx, [ebp-1]
	mov edx, 1
	int 080h
Loop_print_number_16_bits:
	mov eax, 4
	mov ebx, 1
	lea	ecx, [ebp-1+esi]
	mov edx, 1
	int 080h
	inc esi
	inc esp
	cmp esi, 0 
	jne Loop_print_number_16_bits
	push new_line
	push size_new_line
	call output_message
	leave
	ret 2

; Converte um número decimal de 32 bits em caracteres 
; e imprime no terminal seguida da impressão de uma linha
print_number_32_bits:
	enter 1,0				; reserva espaço na pilha para guardar a flag de número negativo
	mov eax, [ebp+8]		; move o primeiro argumento da função para eax
	mov ecx, eax			; move eax para ecx para fazer a operação de and com o ultimo bit do número
	and ecx, 080000000h		; faz o and com a mascara para pegar o ultimo bit do número
	cmp ecx,0				; se não for igual a zero é um número negativo e precisamos processar ele para imprimir no formato
	mov byte [ebp-1],0		
	je jump_flag_neg_print	
	xor eax, 0FFFFFFFFh
	add eax, 1
	mov byte [ebp-1],1
jump_flag_neg_print:
	mov ebx, 10
	xor ecx, ecx
Loop_transform_to_ascii:
	xor edx, edx
	div ebx
	add edx, 030h
	dec ecx
	dec	esp
	mov byte [ebp-1+ecx], dl
	cmp eax, 0
	je	end_transform_to_ascii
	jmp Loop_transform_to_ascii
end_transform_to_ascii:
	mov	esi, ecx
	cmp byte [ebp-1], 0
	je Loop_print_number_32_bits
	mov byte [ebp-1], 45
	mov eax, 4
	mov ebx, 1
	lea	ecx, [ebp-1]
	mov edx, 1
	int 080h
Loop_print_number_32_bits:
	mov eax, 4
	mov ebx, 1
	lea	ecx, [ebp-1+esi]
	mov edx, 1
	int 080h
	inc esi
	inc esp
	cmp esi, 0 
	jne Loop_print_number_32_bits
	push new_line
	push size_new_line
	call output_message
	leave
	ret 4
	
select_operation:
	push message5
	push size_message5	
	call output_message
	push new_line
	push size_new_line
	call output_message
	push option1
	push size_option1
	call output_message
	push new_line
	push size_new_line
	call output_message
	push option2
	push size_option2
	call output_message
	push new_line
	push size_new_line
	call output_message
	push option3
	push size_option3
	call output_message
	push new_line
	push size_new_line
	call output_message
	push option4
	push size_option4
	call output_message
	push new_line
	push size_new_line
	call output_message
	push option5
	push size_option5
	call output_message
	push new_line
	push size_new_line
	call output_message
	push option6
	push size_option6
	call output_message
	push new_line
	push size_new_line
	call output_message
	push option7
	push size_option7
	call output_message
	push new_line
	push size_new_line
	call output_message
	push response_menu_option
	push size_response_menu_option
	call input_message 	
	ret

execute_operation:

	mov eax, [response_menu_option]
	sub eax, 30h
	cmp byte al, 1
	jne jmp_sub

	mov eax, [response_precision]
	sub eax, 30h
	cmp byte al,0
	jne jmp_sum_32

	call sum_16
	jmp end_operation

jmp_sum_32:
	call sum_32
	jmp end_operation

jmp_sub:
	cmp al, 2
	jne jmp_mul

	mov eax, [response_precision]
	sub eax, 30h
	cmp byte al,0
	jne jmp_sub_32

    call sub_16
    jmp end_operation

jmp_sub_32:
	call sub_32
	jmp end_operation
	
jmp_mul:
	cmp al, 3
	jne jmp_div
    call _mul
	jmp end_operation

jmp_div:
	cmp al, 4
	jne jmp_exp
	call _div
	jmp end_operation

jmp_exp:
	cmp al, 5
	jne jmp_mod
    call _exp
	jmp end_operation

jmp_mod:
	cmp al, 6
	jne jmp_sair
    call _mod
	jmp end_operation

jmp_sair:
	jmp terminate_program

terminate_program:
	mov eax, 1
	mov ebx, 0
	int 80h

end_operation:
	push message10
	push size_message10
	call output_message
	push new_line
	push size_new_line
	call output_message
	push name_user
	push size_name_user
	call input_message 
	ret

overflow_treatment:
	push message9
	push size_message9
	call output_message
	push new_line
	push size_new_line
	call output_message
	jmp terminate_program

get_op1:    
    push message6
    push size_message6
    call output_message

    push new_line
    push size_new_line
    call output_message
	mov eax, [response_precision]
	sub eax, 30h
	cmp byte al,0
    jne jmp_op1_input_16_bits
	call input_number_16_bits
	jmp end_op1
jmp_op1_input_16_bits:
	call input_number_32_bits
end_op1:
    ret

get_op2:    
    push message7
    push size_message7
    call output_message

    push new_line
    push size_new_line
    call output_message
	mov eax, [response_precision]
	sub eax, 30h
	cmp byte al,0
    jne jmp_op2_input_16_bits
	call input_number_16_bits
	jmp end_op2
jmp_op2_input_16_bits:
	call input_number_32_bits
end_op2:
    ret

show_result_msg:    
    push message8
    push size_message8
    call output_message

    push new_line
    push size_new_line
    call output_message

    ret


