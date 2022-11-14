.686
include C:\masm32\include\io.asm

.data
    x  dw 5 dup(?)
    N  dw  ?
.code
LStart:
    print "N="
    inint N

    mov ecx, 0
    mov cx, N
    mov ebx,    0
L0: inint16 x[ebx],    6
    add ebx,    2
    loop    L0
    newline
    
    mov ecx, 0
    mov cx, N
    mov ebx,    0
    dec cx
L_BEG:
    push cx
    mov edi, 0
    mov esi, 2
L_BODY0:
    mov ax, x[edi]
    cmp ax, x[esi]
    JL L_BODY1
    push    x[esi]
    push    x[edi]
    pop    x[esi]
    pop    x[edi]
L_BODY1:
    add edi, 2
    add esi, 2
    loop L_BODY0
    pop cx
    add ebx, 2
    loop L_BEG
    
    mov ecx, 0
    mov cx, N
    mov ebx,    0
L1: outint16 x[ebx],    6
    add ebx,    2
    loop    L1
    newline
    
LExit:
	newline
	inkey "Press any key to exit."
    exit
end LStart