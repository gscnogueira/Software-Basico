section .text

global _sub

extern get_op1
extern get_op2
extern show_result_msg
extern input_number_32_bits
extern print_number_32_bits
extern overflow_treatment

_sub:    
    enter 4,0

    call get_op1
    mov dword [ebp-4], eax

    call get_op2
    sub dword [ebp-4], eax

    jo overflow_treatment

    call show_result_msg

    mov dword eax, [ebp-4]
    push eax
    call print_number_32_bits
   
    leave
    ret

    
