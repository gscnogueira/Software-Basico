MOD_A:	BEGIN
EXTERN:	R
EXTERN:	MOD_B
	PUBLIC A
	PUBLIC B
	PUBLIC L1


SECTION DATA
A:	SPACE
B:	SPACE

SECTION TEXT
	INPUT	A
	INPUT	B
	JMP	MOD_B
L1:	OUTPUT	R + 1
	STOP

	END
	
	
	