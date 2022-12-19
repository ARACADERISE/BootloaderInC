use16
global print_str

print_str:
    push ebp
    mov ebp, esp

    mov si, [ebp + 8]

    pop ebp
	mov ah, 0x0e
.print:
	mov al, [si]
	cmp al, 0x0
	je .end_print
	int 0x10
	
	add si, 1

	jmp .print

.end_print:
    mov ah, 0x0E
    mov al, 0xD
    int 0x10
	ret

global print

print:
	mov ah, 0x0e
.print:
	mov al, [si]
	cmp al, 0x0
	je .end_print
	int 0x10
	
	add si, 1

	jmp .print

.end_print:
    mov dl, 0x0
    mov dh, 0x1
    mov ah, 0x02
    int 0x10

	ret