global save_gdt_and_load
use16
save_gdt_and_load:
    push ebp
    mov ebp, esp

    mov eax, [ebp + 8]
    mov [g_GDT32_16_desc_addr], eax

    mov eax, [ebp + 12]
    mov [g_GDT32_16_address], eax

    pop ebp

    mov eax, [g_GDT32_16_desc_addr]
    mov [g_GDTDesc], eax

    mov ax, [g_GDTDesc.size]

    cmp ax, 0
    je .gdt_error

    mov ax, [g_GDTDesc.addr]
    cmp ax, 0
    je .gdt_error

    jmp .do_it
.gdt_error:
    mov si, sum
    call print
.hl:
    jmp .hl
.do_it:
    mov eax, [def_GDTDesc]
    mov [g_GDT32_16_desc_addr], eax

    mov eax, [g_GDT32_16]
    mov [g_GDT32_16_address], eax

    jmp load_gdt

sum db "GDT error :(", 0x0