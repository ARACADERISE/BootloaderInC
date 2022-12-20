ENTRY(main)
SECTIONS
{
    . = 0x9000;
    .text : AT(0x9000)
    {
        *(__start*);
        *(.text*);
    }

    .data :
    {
        *(.bss*);
        *(.data*);
        *(.rodata*);
        *(COMMON*);
    }

    .sig : AT(0x9800) {SHORT(0x00);}
}