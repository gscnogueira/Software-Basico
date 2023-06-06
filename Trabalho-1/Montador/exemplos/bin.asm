SECTION TEXT
INPUT OLD_DATA           ; old_data = input
LOAD OLD_DATA            ; acc = old_data
L1:DIV DOIS             ; acc = old_data/2
STORE NEW_DATA          ; new_data = acc = old_data/2
MUL DOIS                 ; acc = (old_data/2)*2
STORE TMP_DATA           ; tmp_data = old_data/2*2
LOAD            ; acc = old_data 
SUB TMP_DATA             ; acc= old_data - (old_data/2*2)
STORE TMP_DATA           ; tmp_data = old_data - (old_data/2*2)
OUTPUT TMP_DATA          ; print(tmp_data)
COPY NEW_DATA , OLD_DATA ; old_data = new_data
LOAD OLD_DATA            ; acc = old_data
JMPP L1
STOP
SECTION DATA
DOIS:CONST 0x80
OLD_DATA:SPACE
NEW_DATA:SPACE
TMP_DATA:SPACE