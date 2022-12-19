ENTRY(main)
SECTIONS
{
    . = 0x9100;
    .text : AT(0x9100)
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

    .sig : AT(0x8F00) {SHORT(0x0);}
}