.686
include C:\masm32\include\io.asm

.data
    A  dw ?
    A2 dw ?
    A_div_2 dw ?
    Col dw ?
.code
LStart:
    print "A="
    inint A
    print "B="
    inint A2
    MOV Col, 0
check_beg: 
    MOV AX, A
    SHR AX, 1
    MOV A_div_2, AX
    SHL AX, 1
    CMP AX, A
    JE check_fin
    CMP A, 1
    JE check_true
    MOV CX, 3 
check_mid:
    CMP CX, A_div_2
    JGE check_true
    MOV AX, A
    MOV DX, 0
    DIV CX
    CMP DX, 0
    JE check_fin
    ADD CX, 2
    JMP check_mid
check_true:
    outint16 A, 6
    ADD Col, 1
check_fin:
    ADD A, 1
    MOV AX, A
    CMP AX, A2
    JLE check_beg
	newline
	print "Простых Col="
    outint Col
LExit:
	newline
	inkey "Press any key to exit."
    exit
end LStart