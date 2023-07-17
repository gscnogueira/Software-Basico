section .text

global sub_16
global sub_32

extern get_op1
extern get_op2
extern show_result_msg
extern print_number_32_bits
extern print_number_16_bits
extern overflow_treatment

sub_16: 
    enter 2,0

    call get_op1
    mov word [ebp-2], ax

    call get_op2
    sub word [ebp-2], ax

    jo overflow_treatment

    call show_result_msg

    mov word ax, [ebp-2]
    push ax
    call print_number_16_bits

    leave
    ret

sub_32:    
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

    
