section .text

global exp_16
global exp_32

extern get_op1
extern get_op2
extern show_result_msg
extern print_number_32_bits
extern print_number_16_bits
extern overflow_treatment

exp_16: 
    enter 2,0

    push cx
    push dx

    call get_op1
    mov word [ebp-2], ax

    call get_op2

    mov cx, ax

    mov ax, 1

beg_loop16:
    cmp cx, 0
    je end_loop16

    imul word [ebp-2]

    xor dx, ax
    test dx, 0x8000
    jnz overflow_treatment

    dec cx

    jmp beg_loop16

end_loop16:   

    mov [ebp-2], ax

    call show_result_msg

    mov word ax, [ebp-2]
    push ax
    call print_number_16_bits

    pop cx
    pop dx

    leave
    ret


exp_32:    

    enter 4,0

    push ecx

    call get_op1
    mov dword [ebp-4], eax

    call get_op2

    mov ecx, eax

    mov eax, 1

beg_loop:
    cmp ecx, 0
    je end_loop

    imul dword [ebp-4]

    jo overflow_treatment

    dec ecx

    jmp beg_loop

end_loop:   

    mov [ebp-4], eax

    call show_result_msg

    mov dword eax, [ebp-4]
    push eax
    call print_number_32_bits

    pop ecx

    leave
    ret
