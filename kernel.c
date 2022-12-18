
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
	return (background << 4) | (foreground & 0x0F);
}

extern unsigned short get_text_value(unsigned char character, unsigned char foreground, unsigned char background){
	return character | (get_text_attribute(foreground, background) << 8);
}

void __attribute__((section("__start"))) main()
{

    unsigned char *vid_mem = (unsigned char *)0xB8000;

    unsigned short bc = get_text_value(' ', 0x00, 0xFF);
    
    for(int i = 0; i < 50; i++)
        memsetw((unsigned short *)vid_mem + (i * 80), bc, 80);
    /*for(int i = 0; i < 25; i++)
    {
        for(int x = 0; x < 80; x++)
        {
            vid_mem[i * 80 + x] = vga_entry(' ', 0xFF);
        }
    }*/

    enter_rmode();

    //for(int i = 0; i < 50; i++)
    //    memsetw((unsigned short *)vid_mem + (i * 80), bc, 80);

    vid_mem[4] = 'S';//vga_entry('S', vga_entry_color(8,15));
    vid_mem[5] = vga_entry_color(8,15);
    vid_mem[6] = 'E';//vga_entry('E', vga_entry_color(8,15));
    vid_mem[7] = vga_entry_color(8,15);
    vid_mem[8] = 'X';//vga_entry('X', vga_entry_color(8,15));
    vid_mem[9] = vga_entry_color(8,15);

    while(1);
}