; Stack segment.
SSEG SEGMENT PARA STACK 'STACK'
    DB 100 DUP(0)
SSEG ENDS

; Buffer segment.
DSEG1 SEGMENT PARA 'DATA'
    DB 100
    DB 0
    DB 100 DUP(0)
DSEG1 ENDS

; Result data segment.
DSEG2 SEGMENT PARA 'DATA'
    DB 2 DUP(0)
DSEG2 ENDS

; Main code segment.
CSEG SEGMENT PARA 'CODE'
    ASSUME CS:CSEG, DS:DSEG1, ES:DSEG2, SS:SSEG
MAIN:
    ; DATASEG1 preparation.
    MOV AX, DSEG1
    MOV DS, AX

    ; Echoed input.
    MOV AH, 0AH
    MOV DX, 0
    INT 21H
    
    ; Sum of 2nd and 5th digits from input.
    MOV DH, DS:3
    SUB DH, '0'
    ADD DH, DS:6
    MOV ES:1, DH
    
    ; Output of found sum.
    MOV AH, 2
    MOV DL, 13
    INT 21H
    MOV DL, 10
    INT 21H
    MOV DL, ES:1
    INT 21H
    
    ; Program termination.
    MOV AH, 4CH
    INT 21H
CSEG ENDS
END MAIN
