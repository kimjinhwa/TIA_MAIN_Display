/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: --bpp 1 --size 16 --font C:\Users\ServerManager\Documents\SquareLine\assets\arial.ttf -o C:\Users\ServerManager\Documents\SquareLine\assets\ui_font_Font1.c --format lvgl -r 0x20-0x7f --no-compress --no-prefilter
 ******************************************************************************/

#include "../ui.h"

#ifndef UI_FONT_FONT1
#define UI_FONT_FONT1 1
#endif

#if UI_FONT_FONT1

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0x90,

    /* U+0022 "\"" */
    0x99, 0x99,

    /* U+0023 "#" */
    0x11, 0x8, 0x84, 0xdf, 0xf2, 0x21, 0x10, 0x89,
    0xff, 0x64, 0x22, 0x11, 0x8, 0x80,

    /* U+0024 "$" */
    0x10, 0x71, 0xf4, 0xb9, 0x12, 0x3c, 0x1e, 0x16,
    0x26, 0x4c, 0x9d, 0x4f, 0x84, 0x8,

    /* U+0025 "%" */
    0x70, 0x48, 0x88, 0x88, 0x88, 0x90, 0x89, 0x7,
    0x20, 0x2, 0x60, 0x49, 0xc, 0x90, 0x89, 0x18,
    0x91, 0x6,

    /* U+0026 "&" */
    0x1c, 0x8, 0x82, 0x20, 0xc8, 0x1c, 0xe, 0x6,
    0xd3, 0x1e, 0xc7, 0x30, 0xc6, 0x78, 0xf2,

    /* U+0027 "'" */
    0xf0,

    /* U+0028 "(" */
    0x29, 0x29, 0x24, 0x92, 0x24, 0x88,

    /* U+0029 ")" */
    0x99, 0x22, 0x49, 0x24, 0xa5, 0x20,

    /* U+002A "*" */
    0x25, 0x7e, 0xa5, 0x0,

    /* U+002B "+" */
    0x10, 0x10, 0x10, 0xff, 0x10, 0x10, 0x10, 0x10,

    /* U+002C "," */
    0xe0,

    /* U+002D "-" */
    0xf0,

    /* U+002E "." */
    0x80,

    /* U+002F "/" */
    0x11, 0x12, 0x22, 0x24, 0x44, 0xc8,

    /* U+0030 "0" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x83,
    0x5, 0x11, 0xc0,

    /* U+0031 "1" */
    0x13, 0x7d, 0x11, 0x11, 0x11, 0x11,

    /* U+0032 "2" */
    0x3c, 0x8b, 0xa, 0x10, 0x20, 0x83, 0xc, 0x30,
    0xc3, 0x7, 0xf0,

    /* U+0033 "3" */
    0x3c, 0x66, 0x42, 0x2, 0x6, 0x1c, 0x2, 0x1,
    0x1, 0x41, 0x62, 0x3c,

    /* U+0034 "4" */
    0x4, 0xc, 0xc, 0x14, 0x34, 0x24, 0x44, 0xc4,
    0xff, 0x4, 0x4, 0x4,

    /* U+0035 "5" */
    0x7e, 0x81, 0x2, 0xf, 0x98, 0x80, 0x81, 0x3,
    0x87, 0x13, 0xc0,

    /* U+0036 "6" */
    0x3c, 0x8d, 0xc, 0xb, 0x98, 0xa0, 0xc1, 0x83,
    0x5, 0x11, 0xc0,

    /* U+0037 "7" */
    0xfe, 0x8, 0x30, 0x40, 0x82, 0x4, 0x8, 0x20,
    0x40, 0x81, 0x0,

    /* U+0038 "8" */
    0x3c, 0xcd, 0xa, 0x16, 0x67, 0x91, 0xc1, 0x83,
    0x5, 0x11, 0xc0,

    /* U+0039 "9" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x51, 0x9d, 0x3,
    0xb, 0x13, 0xc0,

    /* U+003A ":" */
    0x80, 0x80,

    /* U+003B ";" */
    0x80, 0xe0,

    /* U+003C "<" */
    0x3, 0xe, 0x38, 0xe0, 0xe0, 0x38, 0xe, 0x3,

    /* U+003D "=" */
    0xff, 0x0, 0x0, 0xff,

    /* U+003E ">" */
    0x80, 0xf0, 0x3c, 0x7, 0x7, 0x1c, 0xf0, 0x80,

    /* U+003F "?" */
    0x38, 0x8b, 0x8, 0x10, 0x20, 0x82, 0x8, 0x10,
    0x20, 0x0, 0x80,

    /* U+0040 "@" */
    0x7, 0xc0, 0x60, 0xc2, 0x1, 0x91, 0xda, 0x4c,
    0xc6, 0x23, 0x19, 0x4, 0x64, 0x11, 0x90, 0xc6,
    0x43, 0x28, 0x99, 0x13, 0xb8, 0x60, 0xc, 0xe0,
    0x60, 0xfe, 0x0,

    /* U+0041 "A" */
    0xc, 0x1, 0xc0, 0x68, 0xd, 0x1, 0x30, 0x62,
    0x8, 0x61, 0xfc, 0x60, 0x88, 0x19, 0x3, 0x60,
    0x30,

    /* U+0042 "B" */
    0xfe, 0x83, 0x81, 0x81, 0x83, 0xfe, 0x83, 0x81,
    0x81, 0x81, 0x82, 0xfc,

    /* U+0043 "C" */
    0x1e, 0x18, 0xe4, 0x1a, 0x0, 0x80, 0x20, 0x8,
    0x2, 0x0, 0x80, 0xd0, 0x66, 0x38, 0x78,

    /* U+0044 "D" */
    0xfe, 0x41, 0xa0, 0x50, 0x18, 0xc, 0x6, 0x3,
    0x1, 0x80, 0xc0, 0xa0, 0xdf, 0x80,

    /* U+0045 "E" */
    0xff, 0x80, 0x80, 0x80, 0x80, 0xfe, 0x80, 0x80,
    0x80, 0x80, 0x80, 0xff,

    /* U+0046 "F" */
    0xff, 0x2, 0x4, 0x8, 0x1f, 0xa0, 0x40, 0x81,
    0x2, 0x4, 0x0,

    /* U+0047 "G" */
    0x1f, 0x8, 0x64, 0xe, 0x1, 0x80, 0x20, 0x8,
    0x7e, 0x1, 0x80, 0x50, 0x12, 0xc, 0x7c,

    /* U+0048 "H" */
    0x80, 0xc0, 0x60, 0x30, 0x18, 0xf, 0xfe, 0x3,
    0x1, 0x80, 0xc0, 0x60, 0x30, 0x10,

    /* U+0049 "I" */
    0xff, 0xf0,

    /* U+004A "J" */
    0x4, 0x10, 0x41, 0x4, 0x10, 0x41, 0x6, 0x1c,
    0xde,

    /* U+004B "K" */
    0x83, 0x43, 0x23, 0x13, 0xb, 0x7, 0x83, 0x61,
    0x18, 0x86, 0x43, 0x20, 0xd0, 0x30,

    /* U+004C "L" */
    0x81, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x81,
    0x2, 0x7, 0xf0,

    /* U+004D "M" */
    0xc0, 0x78, 0xf, 0x83, 0xd0, 0x5b, 0xb, 0x63,
    0x64, 0x4c, 0xc9, 0x9b, 0x31, 0x46, 0x38, 0xc2,
    0x10,

    /* U+004E "N" */
    0x80, 0xe0, 0x78, 0x36, 0x1b, 0xc, 0xc6, 0x33,
    0xd, 0x86, 0xc1, 0xe0, 0x70, 0x10,

    /* U+004F "O" */
    0x1f, 0x4, 0x11, 0x1, 0x40, 0x38, 0x3, 0x0,
    0x60, 0xc, 0x1, 0x80, 0x28, 0x8, 0x82, 0xf,
    0x80,

    /* U+0050 "P" */
    0xfe, 0x83, 0x81, 0x81, 0x81, 0x82, 0xfc, 0x80,
    0x80, 0x80, 0x80, 0x80,

    /* U+0051 "Q" */
    0x1f, 0x4, 0x11, 0x1, 0x40, 0x38, 0x3, 0x0,
    0x60, 0xc, 0x1, 0x80, 0x28, 0x68, 0x86, 0xf,
    0xf0, 0x2,

    /* U+0052 "R" */
    0xff, 0x20, 0x68, 0xa, 0x2, 0x81, 0xbf, 0xc8,
    0x62, 0xc, 0x83, 0x20, 0x68, 0x1a, 0x3,

    /* U+0053 "S" */
    0x1e, 0x10, 0x90, 0x68, 0x7, 0x1, 0xf0, 0x3c,
    0x3, 0xc0, 0xa0, 0x58, 0x47, 0xc0,

    /* U+0054 "T" */
    0xff, 0x84, 0x2, 0x1, 0x0, 0x80, 0x40, 0x20,
    0x10, 0x8, 0x4, 0x2, 0x1, 0x0,

    /* U+0055 "U" */
    0x80, 0xc0, 0x60, 0x30, 0x18, 0xc, 0x6, 0x3,
    0x1, 0x80, 0xc0, 0x50, 0x47, 0xc0,

    /* U+0056 "V" */
    0xc0, 0x48, 0x19, 0x83, 0x30, 0x42, 0x18, 0x63,
    0xc, 0x40, 0x98, 0x1a, 0x1, 0x40, 0x38, 0x6,
    0x0,

    /* U+0057 "W" */
    0xc1, 0x86, 0x87, 0xd, 0xa, 0x13, 0x14, 0x26,
    0x6c, 0xc4, 0xc9, 0x89, 0x12, 0x12, 0x24, 0x3c,
    0x78, 0x30, 0x60, 0x60, 0xc0, 0xc1, 0x80,

    /* U+0058 "X" */
    0x60, 0xc4, 0x10, 0xc4, 0xd, 0x80, 0xe0, 0x18,
    0x3, 0x80, 0xd8, 0x13, 0x6, 0x31, 0x83, 0x60,
    0x60,

    /* U+0059 "Y" */
    0xc1, 0x90, 0x66, 0x30, 0x88, 0x36, 0x5, 0x0,
    0x80, 0x20, 0x8, 0x2, 0x0, 0x80, 0x20,

    /* U+005A "Z" */
    0x7f, 0x80, 0xc0, 0xc0, 0xc0, 0x60, 0x60, 0x60,
    0x70, 0x30, 0x30, 0x30, 0x1f, 0xf0,

    /* U+005B "[" */
    0xf2, 0x49, 0x24, 0x92, 0x49, 0x38,

    /* U+005C "\\" */
    0x8c, 0x44, 0x42, 0x22, 0x21, 0x11,

    /* U+005D "]" */
    0xe4, 0x92, 0x49, 0x24, 0x92, 0x78,

    /* U+005E "^" */
    0x10, 0x30, 0xe1, 0x66, 0x48, 0x91, 0x80,

    /* U+005F "_" */
    0xff, 0x80,

    /* U+0060 "`" */
    0xc8,

    /* U+0061 "a" */
    0x3c, 0x8e, 0x8, 0x37, 0xf8, 0x60, 0xc3, 0x7a,

    /* U+0062 "b" */
    0x81, 0x2, 0x5, 0xcc, 0x50, 0x60, 0xc1, 0x83,
    0x7, 0x15, 0xc0,

    /* U+0063 "c" */
    0x38, 0x8a, 0x1c, 0x8, 0x10, 0x21, 0xa2, 0x38,

    /* U+0064 "d" */
    0x2, 0x4, 0x9, 0xd4, 0x70, 0x60, 0xc1, 0x83,
    0x5, 0x19, 0xd0,

    /* U+0065 "e" */
    0x3c, 0x46, 0x82, 0x82, 0xfe, 0x80, 0x82, 0x46,
    0x3c,

    /* U+0066 "f" */
    0x3a, 0x11, 0xe4, 0x21, 0x8, 0x42, 0x10, 0x80,

    /* U+0067 "g" */
    0x3a, 0x8e, 0xc, 0x18, 0x30, 0x60, 0xa3, 0x3a,
    0x7, 0x13, 0xc0,

    /* U+0068 "h" */
    0x81, 0x2, 0x5, 0xec, 0x70, 0x60, 0xc1, 0x83,
    0x6, 0xc, 0x10,

    /* U+0069 "i" */
    0x9f, 0xf0,

    /* U+006A "j" */
    0x20, 0x12, 0x49, 0x24, 0x92, 0x70,

    /* U+006B "k" */
    0x82, 0x8, 0x23, 0x9a, 0xce, 0x3c, 0x92, 0x68,
    0xe3,

    /* U+006C "l" */
    0xff, 0xf0,

    /* U+006D "m" */
    0xb9, 0xd8, 0xc6, 0x10, 0xc2, 0x18, 0x43, 0x8,
    0x61, 0xc, 0x21, 0x84, 0x20,

    /* U+006E "n" */
    0xbd, 0x8e, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x82,

    /* U+006F "o" */
    0x3c, 0x42, 0x81, 0x81, 0x81, 0x81, 0x81, 0x42,
    0x3c,

    /* U+0070 "p" */
    0xb9, 0x8a, 0xc, 0x18, 0x30, 0x60, 0xe2, 0xb9,
    0x2, 0x4, 0x0,

    /* U+0071 "q" */
    0x3a, 0x8e, 0xc, 0x18, 0x30, 0x60, 0xa3, 0x3e,
    0x4, 0x8, 0x10,

    /* U+0072 "r" */
    0xfc, 0x88, 0x88, 0x88, 0x80,

    /* U+0073 "s" */
    0x3c, 0x8d, 0x3, 0x83, 0xc0, 0xf0, 0xa1, 0x3c,

    /* U+0074 "t" */
    0x44, 0x4f, 0x44, 0x44, 0x44, 0x47,

    /* U+0075 "u" */
    0x83, 0x6, 0xc, 0x18, 0x30, 0x60, 0xe3, 0x7a,

    /* U+0076 "v" */
    0xc3, 0x42, 0x62, 0x66, 0x24, 0x34, 0x3c, 0x18,
    0x18,

    /* U+0077 "w" */
    0xc6, 0x38, 0xc5, 0x39, 0xa5, 0x26, 0xb4, 0x52,
    0x8e, 0x71, 0x8c, 0x31, 0x80,

    /* U+0078 "x" */
    0x42, 0x66, 0x3c, 0x18, 0x18, 0x3c, 0x24, 0x66,
    0xc3,

    /* U+0079 "y" */
    0xc3, 0x42, 0x62, 0x66, 0x24, 0x34, 0x1c, 0x18,
    0x18, 0x10, 0x10, 0x60,

    /* U+007A "z" */
    0xfe, 0x8, 0x30, 0xc1, 0x4, 0x18, 0x60, 0xfe,

    /* U+007B "{" */
    0x19, 0x8, 0x42, 0x10, 0x98, 0x61, 0x8, 0x42,
    0x10, 0x60,

    /* U+007C "|" */
    0xff, 0xfe,

    /* U+007D "}" */
    0xc1, 0x8, 0x42, 0x10, 0xc3, 0x31, 0x8, 0x42,
    0x13, 0x0,

    /* U+007E "~" */
    0xf1, 0x8f
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 71, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 71, .box_w = 1, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 91, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 5, .adv_w = 142, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 19, .adv_w = 142, .box_w = 7, .box_h = 16, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 33, .adv_w = 228, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 51, .adv_w = 171, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 66, .adv_w = 49, .box_w = 1, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 67, .adv_w = 85, .box_w = 3, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 73, .adv_w = 85, .box_w = 3, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 79, .adv_w = 100, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 83, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 91, .adv_w = 71, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 92, .adv_w = 85, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 93, .adv_w = 71, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 94, .adv_w = 71, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 100, .adv_w = 142, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 111, .adv_w = 142, .box_w = 4, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 117, .adv_w = 142, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 128, .adv_w = 142, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 140, .adv_w = 142, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 152, .adv_w = 142, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 163, .adv_w = 142, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 174, .adv_w = 142, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 185, .adv_w = 142, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 196, .adv_w = 142, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 207, .adv_w = 71, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 209, .adv_w = 71, .box_w = 1, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 211, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 219, .adv_w = 150, .box_w = 8, .box_h = 4, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 223, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 231, .adv_w = 142, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 242, .adv_w = 260, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 269, .adv_w = 171, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 286, .adv_w = 171, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 298, .adv_w = 185, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 313, .adv_w = 185, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 327, .adv_w = 171, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 339, .adv_w = 156, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 350, .adv_w = 199, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 365, .adv_w = 185, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 379, .adv_w = 71, .box_w = 1, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 381, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 390, .adv_w = 171, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 404, .adv_w = 142, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 415, .adv_w = 213, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 432, .adv_w = 185, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 446, .adv_w = 199, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 463, .adv_w = 171, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 475, .adv_w = 199, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 493, .adv_w = 185, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 508, .adv_w = 171, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 522, .adv_w = 156, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 536, .adv_w = 185, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 550, .adv_w = 171, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 567, .adv_w = 242, .box_w = 15, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 590, .adv_w = 171, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 607, .adv_w = 171, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 622, .adv_w = 156, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 636, .adv_w = 71, .box_w = 3, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 642, .adv_w = 71, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 648, .adv_w = 71, .box_w = 3, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 654, .adv_w = 120, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 661, .adv_w = 142, .box_w = 9, .box_h = 1, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 663, .adv_w = 85, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 10},
    {.bitmap_index = 664, .adv_w = 142, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 672, .adv_w = 142, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 683, .adv_w = 128, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 691, .adv_w = 142, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 702, .adv_w = 142, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 711, .adv_w = 71, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 719, .adv_w = 142, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 730, .adv_w = 142, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 741, .adv_w = 57, .box_w = 1, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 743, .adv_w = 57, .box_w = 3, .box_h = 15, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 749, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 758, .adv_w = 57, .box_w = 1, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 760, .adv_w = 213, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 773, .adv_w = 142, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 781, .adv_w = 142, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 790, .adv_w = 142, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 801, .adv_w = 142, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 812, .adv_w = 85, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 817, .adv_w = 128, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 825, .adv_w = 71, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 831, .adv_w = 142, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 839, .adv_w = 128, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 848, .adv_w = 185, .box_w = 11, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 861, .adv_w = 128, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 870, .adv_w = 128, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 882, .adv_w = 128, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 890, .adv_w = 86, .box_w = 5, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 900, .adv_w = 67, .box_w = 1, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 902, .adv_w = 86, .box_w = 5, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 912, .adv_w = 150, .box_w = 8, .box_h = 2, .ofs_x = 1, .ofs_y = 5}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t ui_font_Font1 = {
#else
lv_font_t ui_font_Font1 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 17,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if UI_FONT_FONT1*/

