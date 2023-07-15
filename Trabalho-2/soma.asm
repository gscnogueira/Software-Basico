section .text

global sum

extern input_number_32_bits
extern output_message
extern message6
extern message7
extern message8
extern message10
extern size_message6
extern size_message7
extern size_message8
extern size_message10
extern new_line
extern size_new_line
extern print_number_32_bits
extern overflow_treatment

sum:
	enter 4,0
	push message6
	push size_message6
	call output_message
	push new_line
	push size_new_line
	call output_message
	call input_number_32_bits
	mov dword [ebp-4], eax
	push message7
	push size_message7
	call output_message
	push new_line
	push size_new_line
	call output_message
	call input_number_32_bits	
	add dword eax, [ebp-4]
	jo overflow_treatment
	mov dword [ebp-4], eax 
	push message8
	push size_message8
	call output_message
	push new_line
	push size_new_line
	call output_message
	mov dword eax, [ebp-4]
	push eax
	call print_number_32_bits
	push message10
	push size_message10
	call output_message
	push new_line
	push size_new_line
	call output_message
Loop_enter_sum:

	; fazer alguma coisa para digitar o enter utilizando o input message :[

end_sum:
	leave
	ret