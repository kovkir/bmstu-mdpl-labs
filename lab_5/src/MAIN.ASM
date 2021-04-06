STACKSEG SEGMENT PARA STACK 'STACK'
    DB 100 DUP(0)
STACKSEG ENDS

DATASEG SEGMENT PARA 'DATA'
    RMSG DB 'Enter matrix rows: $'
    CMSG DB 'Enter matrix columns: $'
    MMSG DB 'Enter matrix:$'
    RESMSG DB 'Reversed matrix:$'
    DECR DW 0
    STEP DW 0
    ROWS DB 0
    COLS DB 0
    COLSDIVTWO DB ?
    MATRIX DB 9 * 9 DUP(0)
DATASEG ENDS

CODESEG SEGMENT PARA 'CODE'
    ASSUME CS:CODESEG, DS:DATASEG, SS:STACKSEG

INSYMB:
    MOV AH, 1
    INT 21H
    RET

OUTSYMB:
    MOV AH, 2
    INT 21H
    RET

NEWLINE:
    MOV AH, 2
    MOV DL, 13
    INT 21H
    MOV DL, 10
    INT 21H
    RET

PRINTSPACE:
    MOV AH, 2
    MOV DL, ' '
    INT 21H
    RET

; Move to the next line
MOVENL:
    MOV AX, 9
    SUB AL, COLS
    ADD BX, AX
    RET

MAIN:
    MOV AX, DATASEG
    MOV DS, AX

    MOV AH, 9
    MOV DX, OFFSET RMSG
    INT 21H

    CALL INSYMB
    MOV ROWS, AL
    SUB ROWS, '0'
    CALL NEWLINE

    MOV AH, 9
    MOV DX, OFFSET CMSG
    INT 21H

    CALL INSYMB
    MOV COLS, AL
    SUB COLS, '0'
    CALL NEWLINE

    MOV AH, 9
    MOV DX, OFFSET MMSG
    INT 21H
    CALL NEWLINE

    ; Input matrix
    MOV BX, 0 ; Array index.
    MOV CL, ROWS 
    INMAT:
        MOV CL, COLS
        INROW:
            CALL INSYMB
            MOV MATRIX[BX], AL
            INC BX 
            CALL PRINTSPACE
            LOOP INROW

        CALL NEWLINE
        CALL MOVENL 
        MOV CL, ROWS 
        MOV SI, DECR 
        SUB CX, SI 
        INC DECR
        LOOP INMAT
     
    CALL NEWLINE ; Start next row output from new line.

    ; Find half of columns to iterate over it.
    MOV AH, 0
    MOV AL, COLS 
    MOV BL, 2
    DIV BL

    ; If matrix is one-columned, then make it 1.
    CMP AL, 0
    JNE CODE
    ADD AL, 1
    CODE:
    MOV COLSDIVTWO, AL

    MOV DECR, 0

    ; Swap Matrix columns.
    MOV BX, 0
    MOV CL, ROWS
    EXCHANGE:
        MOV CL, COLSDIVTWO
        MOV DI, 1
        COLEXCHANGE:
            MOV AL, MATRIX[BX] 
            
            MOV SI, BX
            MOV DL, COLS
            MOV DH, 0
            ADD SI, DX
            SUB SI, DI
            
            MOV DL, MATRIX[SI] 
           
            MOV MATRIX[SI], AL
            MOV MATRIX[BX], DL
            ADD DI, 2 
            INC BX 
            LOOP COLEXCHANGE

        CALL MOVENL
        ADD BL, COLSDIVTWO 
        TEST COLS, 1 ; If columns is odd.
        JP EVENN ; Jump when it is even.
        INC BX 
        EVENN:
        MOV CL, ROWS
        MOV SI, DECR 
        SUB CX, SI 
        INC DECR
        LOOP EXCHANGE

    MOV AH, 9
    MOV DX, OFFSET RESMSG
    INT 21H
    CALL NEWLINE

    MOV DECR, 0

    ; Output matrix
    MOV BX, 0
    MOV CL, ROWS
    OUTMAT:
        MOV CL, COLS
        OUTROW:
            MOV DL, MATRIX[BX]
            CALL OUTSYMB
            INC BX 
            CALL PRINTSPACE
            LOOP OUTROW

        CALL NEWLINE
        CALL MOVENL
        MOV CL, ROWS
        MOV SI, DECR
        SUB CX, SI
        INC DECR
        LOOP OUTMAT

    MOV AX, 4C00H
    INT 21H
CODESEG ENDS
END MAIN
