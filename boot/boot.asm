org 0x7C00
use16

xor ax, ax
mov es, ax
mov ds, ax

cli
mov bp, 0x7C00
mov sp, bp
mov ss, ax
sti

mov ax, 0x7e0
mov es, ax
xor bx, bx

mov ah, 0x02
mov al, 0x5
mov ch, 0x00
mov cl, 0x02
mov dh, 0x00
mov dl, 0x80
int 0x13
jc failed

mov ax, 0x850
mov es, ax
xor bx, bx

mov ah, 0x02
mov al, 0x4
mov ch, 0x00
mov cl, 0x06
mov dh, 0x00
mov dl, 0x80
int 0x13
jc failed

jmp word 0x0:0x7E00

jmp $

failed:
	mov ah, 0x0E
	mov al, 'E'
	int 0x10

	cli
.failed_loop:
	jmp .failed_loop

times 510 - ($ - $$) db 0x0
dw 0xAA55
    