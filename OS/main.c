
asm(".code16gcc\n");

/* macros to make our lives easier :D */
#define bit32_bit16_GDT
#define default_gdt

#include "../protocol/boot_header.h"
#include "../protocol/gdt.h"

extern unsigned char symbol[];

//extern void load_gdt();
extern void init_bootloader(int8 setting);
extern void enter_rmode();
extern void enter_pmode();
extern void do_something(int a);
extern void print();

void __attribute__((section("__start"))) main()
{
    init_bootloader(DEFAULT_ALL);
    //print_str("Second Stage :D\n\0");

    setup_gdt_desc_and_load();

    while(1);
}