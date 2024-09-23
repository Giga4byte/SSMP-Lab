.model small
.stack 100h
.data
a dw FF30h
b dw 0030h
.code
mov ax, @data
mov ds, ax
mov si, offset b
mov bx, [si]
mov si, offset a
mov ax, [si]
sub bx
mov cx, 0000h
mov bx, 000Ah
L: mov dx, 0000h
div bx
push dx
inc cx
cmp ax, 0000h
jnz L
D: pop dx
add dl, 30h
mov ah, 02h
int 21h
dec cl
jnz D
mov ah, 4ch
int 21h
end
