section .text

global mul_16
global mul_32

extern get_op1
extern get_op2
extern show_result_msg
extern print_number_16_bits
extern print_number_32_bits
extern overflow_treatment

mul_16: 
    enter 2,0
    push dx,

    call get_op1
    mov word [ebp-2], ax

    call get_op2
    imul word [ebp-2]

    xor dx, ax
    test dx, 0x8000
    jnz overflow_treatment

    mov [ebp-2], ax

    call show_result_msg

    mov word ax, [ebp-2]
    push ax
    call print_number_16_bits

    pop ax
    pop dx

    leave
    ret

mul_32:   
    enter 4,0

    call get_op1
    mov dword [ebp-4], eax

    call get_op2
    imul dword [ebp-4]

    jo overflow_treatment

    mov [ebp-4], eax

    call show_result_msg

    mov dword eax, [ebp-4]
    push eax

    call print_number_32_bits

    leave
    ret
