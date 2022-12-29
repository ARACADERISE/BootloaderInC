/* macros to make our lives easier :D */
#define bit32_bit16_GDT
#define default_gdt

#include "../protocol/boot_header.h"

void __attribute__((section("__start"))) main()
{
    init_bootloader(CLEAN_GDT_DEF_VID_MODE);
    //init_bootloader(BIT32_BIT16_DEF_VID_MODE);

    /*
     * TODO: Before we load the GDT, we need to read in X
     *       amount of sectors for the kernel.
     *       This is where the "lazy fs" comes in handy. We
     *       will have the binary for the kernel stored in the "lazy fs",
     *       along with the packet information over it's size so we can read in
     *       the correct amount of sectors.
     * */
    load_kernel();

    while(1);
}