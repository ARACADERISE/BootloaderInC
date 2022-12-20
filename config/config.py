import yaml
import os
import sys

if os.path.isfile('boot.yaml'):
    REQUIRED = [
        'kernel_binary',
        'kernel_addr',
        'second_stage_binary',
        'second_stage_addr'
    ]

    file = open('boot.yaml', 'r')
    data = yaml.safe_load(file)
    file.close()

    for i in REQUIRED:
        if not i in data:
            print(f'Error: Expected `{i}` in `boot.yaml`.')
            sys.exit(1)

    file = open(data['kernel_binary'], 'rb')
    kernel_binary_data = file.read();
    file.close()

    file = open(data['second_stage_binary'], 'rb')
    second_stage_binary_data = file.read()
    file.close()

    ss_addr = data['second_stage_addr']
    ss_size = int(len(second_stage_binary_data)/512)
    if ss_size * 512 < len(second_stage_binary_data):
        ss_size += 1

    kern_addr = data['kernel_addr']
    kern_size = int(len(kernel_binary_data)/512)
    if kern_size * 512 < len(kernel_binary_data):
        kern_size += 1
    
    boot = f"""org 0x7C00
use16

xor ax, ax
mov es, ax
mov ds, ax

cli
mov bp, 0x7C00
mov sp, bp
mov ss, ax
sti

mov ax, {hex(ss_addr)}
mov es, ax
xor bx, bx

mov ah, 0x02
mov al, {hex(ss_size)}
mov ch, 0x00
mov cl, 0x02
mov dh, 0x00
mov dl, 0x80
int 0x13
jc failed

mov ax, {hex(kern_addr)}
mov es, ax
xor bx, bx

mov ah, 0x02
mov al, {hex(kern_size)}
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
    """

    file = open("boot/boot.asm", "w")
    file.write(boot)
    file.close()