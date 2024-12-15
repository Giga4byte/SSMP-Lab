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

;alternate code
; giri6.asm

.model small
.stack 100h
.data
    msg db 'MASM Display$'
.code
    mov ax, @data 
    mov ds, ax
    lea si, msg  
access:
    mov dl, [si] 
    cmp dl, '$'
    jz exiting    
    mov ah, 09h
    int 21h     
    inc si   
    jmp access           
exiting:
    mov ah, 4Ch 
    int 21h 
end
