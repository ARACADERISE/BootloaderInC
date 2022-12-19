
asm(".code16gcc\n");

/* macros to make our lives easier :D */
#define bit32_bit16_GDT
//#define default_gdt

#include "../protocol/boot_header.h"
#include "../protocol/gdt.h"

extern unsigned char symbol[];

extern void print_str();
//extern void load_gdt();
extern void init_bootloader(int8 setting);
extern void enter_rmode();
extern void save_gdt_and_load(_gdt_desc gdtDesc, _GDT gdt);
extern void enter_pmode();
extern void do_something(int a);
extern void print();

void __attribute__((section("__start"))) main()
{
    init_bootloader(DEFAULT_ALL);
    print_str("Second Stage :D\n\0");

    _GDT *gdt = (_GDT *)0xA500;
    _gdt_desc *gdtDesc = (_gdt_desc *) 0xAA00;

    //gdt->null_desc = 0x0;

    /* 32-bit code segment. */
    //gdt->code32_limit       = 0xFFFF;
    //gdt->code32_base        = 0x0;
    //gdt->code32_base2       = 0x0;
    //gdt->code32_access      = 0b10011010;
    //gdt->code32_gran        = 0b11001111;
    //gdt->code32_base_high   = 0x0; 

    /* 32-bit data segment. */
    //gdt->data32_limit       = 0xFFFF;
    //gdt->data32_base        = 0x0;
    //gdt->data32_base2       = 0x0;
    //gdt->data32_access      = 0b10010010;
    //gdt->data32_gran        = 0b11001111;
    //gdt->data32_base_high   = 0x0;

    /* 16-bit code segment. */
    //gdt->code16_limit       = 0xFFFF;
    //gdt->code16_base        = 0x0;
    //gdt->code16_base2       = 0x0;
    //gdt->code16_access      = 0b10011010;
    //gdt->code16_gran        = 0b00001111;
    //gdt->cod16_base_high    = 0x0;

    /* 16-bit data segment. */
    //gdt->data16_limit       = 0xFFFF;
    //gdt->data16_base        = 0x0;
    //gdt->data16_base2       = 0x0;
    //gdt->data16_access      = 0b10010010;
    //gdt->data16_gran        = 0b00001111;
    //gdt->data16_base_high   = 0x0;

    setup_gdt_desc(gdtDesc, gdt);

    save_gdt_and_load(*gdtDesc, *gdt);

    while(1);
}