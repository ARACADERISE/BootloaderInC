global save_gdt_and_load
use16
save_gdt_and_load:

    ; Do we need to load a already-working gdt into memory?
    mov eax, [g_GDT_status]
    cmp eax, 0
    je .load_new_gdt

    ; Is there already a GDT in memory that the user put there?
    cmp eax, 1
    je .set_it

    ; If for some reason the gdt status is neither 1 or 0, error
    jmp .gdt_error
.load_new_gdt:
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
.set_it:
.do_it:

    jmp load_gdt

sum db "Error loading the GDT :(", 0x0