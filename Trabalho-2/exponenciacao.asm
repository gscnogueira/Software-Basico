section .text

global _exp

extern get_op1
extern get_op2
extern show_result_msg
extern input_number_32_bits
extern print_number_32_bits
extern overflow_treatment

_exp:    

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
