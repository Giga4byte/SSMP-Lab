.model small
.stack 100h
.data
  a dw 0110h
  b dw 1001h
.code
  mov ax, @data
  mov ds, ax
  mov si, offset a
  mov bx, [si]
  mov di, offset b
  mov ax, [di]
  and ax, bx
  mov cx, 0
  mov bx, 10
  
  test ax, ax 
  jnz convert
  mov dx, 0  
  add dx, 30h   
  mov ah, 02h
  int 21h            
  jmp endProg
convert:
    xor dx, dx
    div bx
    push dx
    inc cx
    cmp ax, 0
    jnz convert
printloop:
    pop dx
    add dx, 30h
    mov ah, 02h
    int 21h
endProg: 
    mov ah, 4ch
    int 21h
end
