.model small
.stack 100h
.data
.code
  mov ax, @data
  mov ds, ax
  mov bx, 3333h
  mov ax, 5555h
  sub ax, bx
  mov cx, 0000h
  mov bx, 16
convert:
    xor dx, dx
    div bx
    push dx
    inc cx
    cmp ax, 0
    jnz convert
printloop:
    pop dx
    add dx, '0'
    cmp dx, '9'
    jbe output
    add dx, 7
output:
    mov ah, 02h
    int 21h
    dec cx
    jnz printloop
  mov ah, 4ch
  int 21h
end
