ENTRY(main)
SECTIONS
{
    . = 0x7E00;
    symbol = .;
    .text : AT(0x7E00)
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

    .sig : AT(0x8400) {SHORT(0x0);}
}