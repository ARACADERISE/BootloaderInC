
asm(".code16gcc\n");

extern unsigned char symbol[];

extern void print_str();
extern void load_gdt();
extern void enter_rmode();
extern void enter_pmode();
extern void do_something(int a);
extern void print();

void __attribute__((section("__start"))) main()
{
    print_str("hey");
    print_str("bye");

    //do_something(0x10);

    load_gdt();

    while(1);
}