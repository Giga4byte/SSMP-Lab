;giri4.asm

.model small
.data
    msg1 db 'Hello, World$'
.code
    mov ax, @data
    mov ds, ax
    lea dx, msg1
    mov ah, 09h
    int 21h
end
