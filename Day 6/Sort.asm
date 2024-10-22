;giri2.asm

.model small
.stack 100h
.data
 list db 2h, 9h, 8h, 5h, 3h

.code
main proc
    mov ax, @data
    mov ds, ax

    mov cl, 05h
l1:
    mov ch, 05h
    mov si, offset list
l2:
    mov al, [si]      
    inc si
    cmp al, [si]        
    jc skip        
    xchg al, [si]    
    dec si      
    xchg al, [si]
    inc si
skip:            
    dec ch            
    jnz l2            
    dec cl            
    jnz l1            

    mov cx, 05h
    mov si, offset list
l3:
    mov al, [si]          
    add al, 30h
    mov dl,al          
    mov ah, 02h          
    int 21h              
    inc si                
    loop l3              
    mov ax, 4C00h
    int 21h
main endp
end main
