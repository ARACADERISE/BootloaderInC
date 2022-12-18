ENTRY(main)
SECTIONS
{
    . = 0x8500;
    .text : AT(0x8500)
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

    .sig : AT(0x8D00) {SHORT(0x0);}
}