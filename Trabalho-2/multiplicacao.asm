section .text

global _mul

extern get_op1
extern get_op2
extern show_result_msg
extern input_number_32_bits
extern print_number_32_bits
extern overflow_treatment

_mul:   

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
