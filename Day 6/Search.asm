.model small
.data
    msg db "HELLO WORLD$"
    msg1 db "character present$"
    msg2 db "character not present$"
    msg3 db 10,13,'$'
    ins db "check letter: $"
.code
    mov ax, @data
    mov ds, ax
    lea si, msg
    
    lea dx, ins
    mov ah, 09h
    int 21h
    mov ah, 01h
    int 21h
    lea dx, msg3
    mov ah, 09h
    int 21h
    
    mov bl, '$'
    
    up: cmp bl, [si]
        jz exit
        cmp al, [si]
        jz print
        inc si
        jmp up
    
    print: lea dx, msg1
           mov ah, 09h
           int 21h
           mov ah, 4ch
           int 21h
    
    exit: lea dx, msg2
          mov ah, 09h
          int 21h
          mov ah, 4ch
          int 21h
end
