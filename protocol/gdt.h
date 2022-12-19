#ifndef protocol_gdt
#define protocol_gdt

/* Constants for `init_bootloader` function. */
/* Helps with configuring certain aspects of the protocol such as what type of GDT. */
#define gdt_bit32_bit16         0x3216
#define gdt_bit32_only          0x32

/* Enum of different types of GDT. */
enum GDT_TYPE {
    clean_gdt           =   0x0,
    bit32_bit16_gdt     =   0x1,
    bit32_only_gdt      =   0x2,
};

/* Video mode? */
enum VID_MODE
{
    B8000               =   0x3,          // Default
    VESA_VID_MODE       =   0x4,
};

/* Constants for above enums. */
#define DEFAULT_ALL                 clean_gdt | B8000
#define CLEAN_GDT_DEF_VID_MODE      clean_gdt | B8000
#define CLEAN_GDT_VESA_VID_MODE     clean_gdt | VESA_VID_MODE
#define BIT32_BIT16_DEF_VID_MODE    bit32_bit16_gdt | B8000
#define BIT32_BIT16_VESA_VID_MODE   bit32_bit16_gdt | VESA_VID_MODE
#define BIT32_ONLY_DEF_VID_MODE     bit32_only_gdt | B8000
#define BIT32_ONLY_VESA_VID_MODE    bit32_only_gdt | VESA_VID_MODE

/* Descriptiong of GDT. */
/* This will be overwritten(by default) if you inititalize the bootloader with anything but `clean_gdt`. */
typedef struct gdt_desc
{
    uint16      size;
    uint32      address;
} packed _gdt_desc;

/* Setting up the description of the GDT. */
#define setup_gdt_desc(gdtDesc, gdt)     \
    gdtDesc->size = (uint16)sizeof(*gdt);\
    gdtDesc->address = (uint32)gdt;

#ifdef bit32_bit16_GDT

    /* If the GDT has 16-bit segments, we want to make sure we know this. */
    #define has_rmode_access

    typedef struct GDT
    {
        /* 32-bit: null descriptor. */
        long long           null_desc;

        /* 32-bit: code segment. */
        int16          code32_limit;          // 0xFFFFF for full 32-bit range
        int16          code32_base;
        int8           code32_base2;
        int8           code32_access;         // access (present, ring 0, code segment, executable, direction 0, readable)
        int8           code32_gran;           // granularity (4k pages, 32-bit pmode) + limit (bits 16-19)
        int8           code32_base_high;

        /* 32-bit: data segment. */
        int16          data32_limit;         // 0xFFFFF for full 32-bit range
        int16          data32_base;
        int8           data32_base2;
        int8           data32_access;        // access (present, ring 0, code segment, executable, direction 0, readable)
        int8           data32_gran;          // granularity (4k pages, 32-bit pmode) + limit (bits 16-19)
        int8           data32_base_high;

        /* 16-bit: code segment. */
        int16          code16_limit;         // should be 0xFFFFF(same as 32-bit code/data segments)
        int16          code16_base;
        int8           code16_base2;
        int8           code16_access;       // access (present, ring 0, code segment, executable, direction 0, readable)
        int8           code16_gran;         // granularity (4k pages, 32-bit pmode) + limit (bits 16-19)
        int8           cod16_base_high;

        /* 16-bit: data segment. */
        int16          data16_limit;         // should be 0xFFFFF(same as 32-bit code/data segments)
        int16          data16_base;
        int8           data16_base2;
        int8           data16_access;       // access (present, ring 0, code segment, executable, direction 0, readable)
        int8           data16_gran;         // granularity (4k pages, 32-bit pmode) + limit (bits 16-19)
        int8           data16_base_high;
    } packed _GDT;

#else
    /* 32-bit only GDT. */
    typedef struct GDT
    {
        /* 32-bit: null descriptor. */
        uint8           null_desc[64];

        /* 32-bit: code segment. */
        uint16          code32_limit;          // 0xFFFFF for full 32-bit range
        uint16          code32_base;
        uint8           code32_base2;
        uint8           code32_access;         // access (present, ring 0, code segment, executable, direction 0, readable)
        uint8           code32_gran;           // granularity (4k pages, 32-bit pmode) + limit (bits 16-19)
        uint8           code32_base_high;

        /* 32-bit: data segment. */
        uint16          data32_limit;         // 0xFFFFF for full 32-bit range
        uint16          data32_base;
        uint8           data32_base2;
        uint8           data32_access;        // access (present, ring 0, code segment, executable, direction 0, readable)
        uint8           data32_gran;          // granularity (4k pages, 32-bit pmode) + limit (bits 16-19)
        uint8           data32_base_high;
    } packed _GDT;
#endif

#ifdef default_gdt

    #ifdef has_rmode_access
        /* Setup 32-bit/16-bit GDT. */
        _GDT gdt = (_GDT) {
            .null_desc          = {0},

            /* 32-bit code segment. */
            .code32_limit       = 0xFFFF,
            .code32_base        = 0x0,
            .code32_base2       = 0x0,
            .code32_access      = 0b10011010,
            .code32_gran        = 0b11001111,
            .code32_base_high   = 0x0, 

            /* 32-bit data segment. */
            .data32_limit       = 0xFFFF,
            .data32_base        = 0x0,
            .data32_base2       = 0x0,
            .data32_access      = 0b10010010,
            .data32_gran        = 0b11001111,
            .data32_base_high   = 0x0,

            /* 16-bit code segment. */
            .code16_limit       = 0xFFFF,
            .code16_base        = 0x0,
            .code16_base2       = 0x0,
            .code16_access      = 0b10011010,
            .code16_gran        = 0b00001111,
            .cod16_base_high    = 0x0,

            /* 16-bit data segment. */
            .data16_limit       = 0xFFFF,
            .data16_base        = 0x0,
            .data16_base2       = 0x0,
            .data16_access      = 0b10010010,
            .data16_gran        = 0b00001111,
            .data16_base_high   = 0x0
        };

    #else
        /* Setup 32-bit GDT. */
        _GDT gdt = (_GDT) {
            .null_desc          = {0},

            /* 32-bit code segment. */
            .code32_limit       = 0xFFFF,
            .code32_base        = 0x0,
            .code32_base2       = 0x0,
            .code32_access      = 0b10011010,
            .code32_gran        = 0b11001111,
            .code32_base_high   = 0x0, 

            /* 32-bit data segment. */
            .data32_limit       = 0xFFFF,
            .data32_base        = 0x0,
            .data32_base2       = 0x0,
            .data32_access      = 0b10010010,
            .data32_gran        = 0b11001111,
            .data32_base_high   = 0x0
        };

    #endif

    _gdt_desc *gdtDesc = (_gdt_desc *) 0xAA00;

#endif

#endif