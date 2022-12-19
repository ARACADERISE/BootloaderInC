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
        *(COMMON*);
    }

    .sig : AT(0x8600) {SHORT(0x0);}
}