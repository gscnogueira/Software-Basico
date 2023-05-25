
SECTION TEXT ;comentario papi
INPUT OLD_DATA ;comentario papi
LOAD OLD_DATA ;comentario papi
L1: DIV DOIS ;comentario papi
STORE NEW_DATA ;comentario papi
MUL DOIS ;comentario papi
STORE TMP_DATA ;comentario papi
LOAD OLD_DATA ;comentario papi
SUB TMP_DATA ;comentario papi
STORE TMP_DATA ;comentario papi
OUTPUT TMP_DATA ;comentario papi
COPY NEW_DATA , OLD_DATA ;comentario papi
LOAD OLD_DATA ;comentario papi
JMPP L1 ;comentario papi
STOP ;comentario papi
SECTION DATA ;comentario papi
DOIS: CONST 2 ;comentario papi
OLD_DATA: SPACE ;comentario papi
NEW_DATA: SPACE ;comentario papi
TMP_DATA: SPACE ;comentario papi
