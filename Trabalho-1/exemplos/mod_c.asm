MOD_C:    BEGIN
EXTERN: DATA1
EXTERN: DOIS
EXTERN: DATA2
EXTERN: RET_MOD_C
PUBLIC MOD_C
SECTION TEXT
INPUT DATA1
L2: LOAD DATA1 
OUTPUT DATA1
MUL    DOIS
STORE DATA1
SUB DATA2
JMPN L2

JMP RET_MOD_C

END
