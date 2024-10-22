;giri1.asm

.model small
.data
  a db 00H
  b db 01H
  c1 db 06H
  d db 06 dup (?)
.code
  mov ax,@data
  mov ds,ax
  mov si,offset a
  mov al,[si]
  mov si,offset b
  mov bl,[si]
  mov si,offset c1
  mov cx,[si]
  mov si,offset d
L1: 
    add al, bl       
    mov [si], al     
    mov al, bl       
    mov bl, [si]     
    inc si           
    loop L1          
    mov cx, 06h      
    mov si, offset d 
L2: 
    mov al, [si]    
    cmp al, 0Ah      
    jb  convert_to_ascii  
    add al, 37h      
    jmp print_char
convert_to_ascii: 
    add al, 30h      
print_char: 
    mov dl, al     
    mov ah, 02h     
    int 21h          
    inc si          
    loop L2          
    mov ah, 4ch     
    int 21h
end
