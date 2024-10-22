.model small
.data
     msg1 db 'Hello$'
     msg2 db 'Giri$'
.code
     mov ax, @data
     mov ds, ax
     lea si, msg1
     lea di, msg2
     mov al, '$'

     up: cmp al, [si]
           jz next
           inc si
           jmp up

    next: cmp al, [di]
             jz exit
             mov bl, [di]
             mov [si], bl
             inc si
             inc di
             jmp next

    exit: mov [si], al
            lea dx, msg1
            mov ah, 09h
            int 21h

    mov ah, 4ch
    int 21h
end
