section .text

global _div

extern get_op1
extern get_op2
extern show_result_msg
extern input_number_32_bits
extern print_number_32_bits
extern overflow_treatment

_div:    

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
