section .text

global div_32
global div_16

extern get_op1
extern get_op2
extern show_result_msg
extern input_number_32_bits
extern print_number_32_bits
extern print_number_16_bits
extern overflow_treatment

div_16: 
    enter 2,0
    push dx

    call get_op1
    mov word [ebp-2], ax

    call get_op2
    xchg [ebp-2], ax
    cwd

    idiv word [ebp-2]

    mov word [ebp-2], ax

    call show_result_msg

    push word [ebp-2]
    call print_number_16_bits

    pop dx
    leave
    ret

div_32:    

    enter 4,0
    push edx

    call get_op1
    mov dword [ebp-4], eax

    call get_op2

    xchg [ebp-4], eax
    cdq

    idiv dword [ebp-4]

    mov dword [ebp-4], eax

    call show_result_msg

    push dword [ebp-4]
    call print_number_32_bits

    pop edx
    leave
    ret
