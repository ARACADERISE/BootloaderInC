org 0x7E00
use16

mov ah, 0x0E
mov al, 'H'
int 0x10

jmp $

times 1536 - ($ - $$) db 0x0 
