.model small
.stack 100h
.data
  a dw 1234h
  b dw 5678h
.code
  mov ax, @data
  mov ds, ax
  mov si, offset a
  mov bx, [si]
  mov di, offset b
  mov ax, [di]
  add ax, bx
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
// masm - addition
