
extern void enter_rmode();
extern void test_this();
extern void enter_pmode();
extern void load_gdt();

extern unsigned short *memsetw(unsigned short *dest, unsigned short val, unsigned int count){
	unsigned short* dstPtr = (unsigned short *)dest;

    for (; count != 0; count--) *dstPtr++ = val;
	
	return dest;
}

static inline unsigned char vga_entry_color(int fg, int bg) 
{
	return fg | bg << 4;
}
 
static inline unsigned short vga_entry(unsigned char uc, unsigned char color) 
{
	return (unsigned short) uc | (unsigned short) color << 8;
}

unsigned char get_text_attribute(unsigned char foreground, unsigned char background){
	/*
     * fg = 1001 1100
     * bg = 1100 1011
     *
     * bg << 4   = 1100 1011 0000
     * fg & 0x0F = 10011100 &
     *             00001111
     *                 1100
     * 
     * 1100 1011 0000 |
     *           1100 = 1100 1011 1100
     * */
    return (background << 4) | (foreground & 0x0F);
}

enum scheme {
    scheme_normal = 0x000,      // 0x0 = black, 0xF = White
    scheme_one = 0x100,         // 0x1 = black, 0xE = white
    scheme_two = 0x200,         // 0x2 = black, 0xD = white
    scheme_three = 0x300,       // 0x3 = black, 0xC = white
    scheme_four = 0x400,        // 0x4 = black, 0xB = white
    scheme_five = 0x500,        // 0x5 = black, 0xA = white
    scheme_six = 0x600,         // 0x6 = black, 0x9 = white
    scheme_seven = 0x700,       // 0x7 = black, 0x8 = white
    scheme_eight = 0x800,       // 0x8 = black, 0x7 = white
    scheme_nine = 0x900,        // 0x9 = black, 0x6 = white
    scheme_A = 0xA00,           // 0xA = black, 0x5 = white
    scheme_B = 0xB00,           // 0xB = black, 0x4 = white
    scheme_C = 0xC00,           // 0xC = black, 0x3 = white
    scheme_D = 0xD00,           // 0xD = black, 0x2 = white
    scheme_E = 0xE00,           // 0xE = black, 0x1 = white
    scheme_F = 0xF00,           // 0xF = black, 0x0 = white
    scheme_F_ultra = 0xF000
};

/* TODO: We are going to need to have a API for colors. */
/* We can do a lot of things with this. */
/* Lets come up with different color schemes. The way this works is by
 * manipulating the bit operators upon the return of the function.*/
 /* We will have to outline the schemes very well and do a lot of color testing :D */
extern unsigned short get_text_value(unsigned char character, unsigned char foreground, unsigned char background, enum scheme s){
	/* Example:
     * character = 'S' =   01010011
     * foreground = 0x3A = 00111010
     * background = 0xD8 = 11011000
     *
     * get_text_attribute:
     *  fg & 0x0f = 00111010 &
     *              00001111 = 1010
     *  bg << 4 = 1101 1000 0000
     *  1101 1000 0000 or
     *  0000 0000 1010   = 1101 1000 1010
     *
     *                0101 0011 or
     *      1101 1000 1010 << 8      =                 0101 0011 or
     *                                  1101 1000 1010 0000 0000    = 1101 1000 1010 0101 0011 = 0xD8A53
     * 1101 1000 1010 0101 0011 ^
     *           1111 0000 0000 = 1101 1000 0101 0101 0011
     * */

     /* TODO:
      * 1. Make `init_bit32` function that takes in the color of screen the user wants, as well as other ideals if needed
      * 2. Store the initial background color(of the screen) so functions(such as this one) can just fill out the background with whatever
      *    the user set the background to be via `init_bit32`.
      * 3. Create color schemes and test out the colors. Possible checks(such as the one below) that makes sure we get the correct
      *    color value? */

    if(s == scheme_F_ultra)
        background++;

    unsigned short text_attr = get_text_attribute(foreground, background) << 8;

    return character | (text_attr ^ s);
}

void __attribute__((section("__start"))) kmain()
{

    unsigned short *vid_mem = (unsigned short *)0xB8000;

    unsigned short bc = get_text_value(' ', 0xAA, 0xC7, scheme_normal); // D8 was last one
    
    for(int i = 0; i < 50; i++)
        memsetw((unsigned short *)vid_mem + (i * 80), bc, 80);

    //enter_rmode();

    //for(int i = 0; i < 50; i++)
    //    memsetw((unsigned short *)vid_mem + (i * 80), bc, 80);
    //unsigned int b = ('S' | ((0x32 << 4) | (0x32 & 0x0F)) << 8);
    vid_mem[0] = get_text_value('S', 0xF, 0xC6, scheme_F_ultra);//0xC7053;//'S' | ((0xD8<<4) | (0x00&0x0F))<<8;//get_text_value('S', 0x3A, 0xD8);
    //vid_mem[1] = 0x00D8;
    //vid_mem[2] = get_text_value('E', 0xAA, 0xD8);
    //vid_mem[2] = get_text_value('X', 0xAA, 0xD8);
    /*vid_mem[5] = vga_entry_color(8,15);
    vid_mem[6] = 'E';//vga_entry('E', vga_entry_color(8,15));
    vid_mem[7] = vga_entry_color(8,15);
    vid_mem[8] = 'X';//vga_entry('X', vga_entry_color(8,15));
    vid_mem[9] = vga_entry_color(8,15);*/

    while(1);
}