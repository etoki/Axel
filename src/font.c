/**
 * @file font.c
 * @brief font data implementation.
 * @author mopp
 * @version 0.1
 * @date 2014-04-11
 */
#include <rgb8.h>
#include <font.h>
#include <drawable.h>
#include <stdint.h>

static uint32_t const s_mplus_font[FONT_SIZE][FONT_HIGHT] = {
        [0x0000] = {
            0x00, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x00,
        },
        [0x0001] = {
            0x00, 0x00, 0x00, 0x00, 0x20, 0x70, 0xF8, 0x70, 0x20, 0x00, 0x00, 0x00, 0x00,
        },
        [0x0002] = {
            0x00, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8,
        },
        [0x0003] = {
            0x00, 0x88, 0x88, 0xF8, 0x88, 0x88, 0x00, 0xF8, 0x20, 0x20, 0x20, 0x20, 0x00,
        },
        [0x0004] = {
            0x00, 0xF8, 0x80, 0xF8, 0x80, 0x80, 0x00, 0xF8, 0x80, 0xF8, 0x80, 0x80, 0x00,
        },
        [0x0005] = {
            0x00, 0xF8, 0x88, 0x80, 0x88, 0xF8, 0x00, 0xF8, 0x88, 0xF8, 0x90, 0x88, 0x00,
        },
        [0x0006] = {
            0x00, 0x80, 0x80, 0x80, 0x80, 0xF8, 0x00, 0xF8, 0x80, 0xF8, 0x80, 0x80, 0x00,
        },
        [0x0007] = {
            0x00, 0x60, 0x90, 0x90, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        [0x0008] = {
            0x00, 0x00, 0x00, 0x20, 0x20, 0xF8, 0x20, 0x20, 0x00, 0x00, 0xF8, 0x00, 0x00,
        },
        [0x0009] = {
            0x00, 0x88, 0xC8, 0xA8, 0x98, 0x88, 0x00, 0x80, 0x80, 0x80, 0x80, 0xF8, 0x00,
        },
        [0x000A] = {
            0x00, 0x88, 0x88, 0x88, 0x90, 0xE0, 0x00, 0xF8, 0x20, 0x20, 0x20, 0x20, 0x00,
        },
        [0x000B] = {
            0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        [0x000C] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x20, 0x20, 0x20, 0x20, 0x20,
        },
        [0x000D] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x20, 0x20, 0x20, 0x20, 0x20,
        },
        [0x000E] = {
            0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        [0x000F] = {
            0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xFC, 0x20, 0x20, 0x20, 0x20, 0x20,
        },
        [0x0010] = {
            0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        [0x0011] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        [0x0012] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        [0x0013] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00,
        },
        [0x0014] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00,
        },
        [0x0015] = {
            0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3C, 0x20, 0x20, 0x20, 0x20, 0x20,
        },
        [0x0016] = {
            0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x20, 0x20, 0x20, 0x20, 0x20,
        },
        [0x0017] = {
            0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        [0x0018] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x20, 0x20, 0x20, 0x20, 0x20,
        },
        [0x0019] = {
            0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
        },
        [0x001A] = {
            0x00, 0x00, 0x10, 0x20, 0x40, 0x80, 0x40, 0x20, 0x10, 0x00, 0xF8, 0x00, 0x00,
        },
        [0x001B] = {
            0x00, 0x00, 0x40, 0x20, 0x10, 0x08, 0x10, 0x20, 0x40, 0x00, 0xF8, 0x00, 0x00,
        },
        [0x001C] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x50, 0x50, 0x50, 0x90, 0x90, 0x00, 0x00,
        },
        [0x001D] = {
            0x00, 0x00, 0x00, 0x10, 0x10, 0xF8, 0x20, 0xF8, 0x40, 0x40, 0x00, 0x00, 0x00,
        },
        [0x001E] = {
            0x00, 0x00, 0x30, 0x48, 0x40, 0x40, 0xF0, 0x40, 0x40, 0x60, 0x98, 0x00, 0x00,
        },
        [0x001F] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x70, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        [0x0020] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        [0x0021] = {
            0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x20, 0x00, 0x00,
        },
        [0x0022] = {
            0x00, 0x50, 0x50, 0x50, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        [0x0023] = {
            0x00, 0x00, 0x50, 0x50, 0xF8, 0x50, 0x50, 0x50, 0xF8, 0x50, 0x50, 0x00, 0x00,
        },
        [0x0024] = {
            0x00, 0x00, 0x20, 0x78, 0xA0, 0xA0, 0x70, 0x28, 0x28, 0xF0, 0x20, 0x00, 0x00,
        },
        [0x0025] = {
            0x00, 0x00, 0x40, 0xA0, 0x48, 0x10, 0x20, 0x40, 0x90, 0x28, 0x10, 0x00, 0x00,
        },
        [0x0026] = {
            0x00, 0x00, 0x60, 0x90, 0x90, 0x60, 0x48, 0xA8, 0x90, 0x90, 0x68, 0x00, 0x00,
        },
        [0x0027] = {
            0x00, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        [0x0028] = {
            0x00, 0x10, 0x20, 0x20, 0x40, 0x40, 0x40, 0x40, 0x40, 0x20, 0x20, 0x10, 0x00,
        },
        [0x0029] = {
            0x00, 0x40, 0x20, 0x20, 0x10, 0x10, 0x10, 0x10, 0x10, 0x20, 0x20, 0x40, 0x00,
        },
        [0x002A] = {
            0x00, 0x00, 0x00, 0x20, 0xA8, 0x70, 0x20, 0x70, 0xA8, 0x20, 0x00, 0x00, 0x00,
        },
        [0x002B] = {
            0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0xF8, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00,
        },
        [0x002C] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x70, 0x20, 0x40, 0x00,
        },
        [0x002D] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        [0x002E] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x70, 0x20, 0x00, 0x00,
        },
        [0x002F] = {
            0x00, 0x00, 0x08, 0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x40, 0x80, 0x80, 0x00,
        },
        [0x0030] = {
            0x00, 0x00, 0x70, 0x88, 0x88, 0x98, 0xA8, 0xC8, 0x88, 0x88, 0x70, 0x00, 0x00,
        },
        [0x0031] = {
            0x00, 0x00, 0x20, 0x60, 0xA0, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00,
        },
        [0x0032] = {
            0x00, 0x00, 0x70, 0x88, 0x88, 0x08, 0x10, 0x20, 0x40, 0x80, 0xF8, 0x00, 0x00,
        },
        [0x0033] = {
            0x00, 0x00, 0xF8, 0x08, 0x10, 0x20, 0x70, 0x08, 0x08, 0x88, 0x70, 0x00, 0x00,
        },
        [0x0034] = {
            0x00, 0x00, 0x30, 0x30, 0x50, 0x50, 0x90, 0x90, 0xF8, 0x10, 0x10, 0x00, 0x00,
        },
        [0x0035] = {
            0x00, 0x00, 0xF8, 0x80, 0x80, 0xF0, 0x08, 0x08, 0x88, 0x88, 0x70, 0x00, 0x00,
        },
        [0x0036] = {
            0x00, 0x00, 0x30, 0x40, 0x80, 0xF0, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00,
        },
        [0x0037] = {
            0x00, 0x00, 0xF8, 0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x40, 0x40, 0x00, 0x00,
        },
        [0x0038] = {
            0x00, 0x00, 0x70, 0x88, 0x88, 0x50, 0x20, 0x50, 0x88, 0x88, 0x70, 0x00, 0x00,
        },
        [0x0039] = {
            0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0x88, 0x78, 0x08, 0x10, 0x60, 0x00, 0x00,
        },
        [0x003A] = {
            0x00, 0x00, 0x00, 0x00, 0x20, 0x70, 0x20, 0x00, 0x20, 0x70, 0x20, 0x00, 0x00,
        },
        [0x003B] = {
            0x00, 0x00, 0x00, 0x00, 0x20, 0x70, 0x20, 0x00, 0x20, 0x70, 0x20, 0x40, 0x00,
        },
        [0x003C] = {
            0x00, 0x00, 0x08, 0x10, 0x20, 0x40, 0x80, 0x40, 0x20, 0x10, 0x08, 0x00, 0x00,
        },
        [0x003D] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        [0x003E] = {
            0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00,
        },
        [0x003F] = {
            0x00, 0x00, 0x70, 0x88, 0x88, 0x08, 0x10, 0x20, 0x20, 0x00, 0x20, 0x00, 0x00,
        },
        [0x0040] = {
            0x00, 0x00, 0x70, 0x88, 0xB8, 0xA8, 0xA8, 0xA8, 0xB8, 0x80, 0x70, 0x00, 0x00,
        },
        [0x0041] = {
            0x00, 0x00, 0x20, 0x20, 0x50, 0x50, 0x50, 0xF8, 0x88, 0x88, 0x88, 0x00, 0x00,
        },
        [0x0042] = {
            0x00, 0x00, 0xF0, 0x88, 0x88, 0x88, 0xF0, 0x88, 0x88, 0x88, 0xF0, 0x00, 0x00,
        },
        [0x0043] = {
            0x00, 0x00, 0x70, 0x88, 0x80, 0x80, 0x80, 0x80, 0x80, 0x88, 0x70, 0x00, 0x00,
        },
        [0x0044] = {
            0x00, 0x00, 0xE0, 0x90, 0x88, 0x88, 0x88, 0x88, 0x88, 0x90, 0xE0, 0x00, 0x00,
        },
        [0x0045] = {
            0x00, 0x00, 0xF8, 0x80, 0x80, 0x80, 0xF0, 0x80, 0x80, 0x80, 0xF8, 0x00, 0x00,
        },
        [0x0046] = {
            0x00, 0x00, 0xF8, 0x80, 0x80, 0x80, 0xF0, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00,
        },
        [0x0047] = {
            0x00, 0x00, 0x70, 0x88, 0x80, 0x80, 0xB8, 0x88, 0x88, 0x88, 0x78, 0x00, 0x00,
        },
        [0x0048] = {
            0x00, 0x00, 0x88, 0x88, 0x88, 0x88, 0xF8, 0x88, 0x88, 0x88, 0x88, 0x00, 0x00,
        },
        [0x0049] = {
            0x00, 0x00, 0x70, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00, 0x00,
        },
        [0x004A] = {
            0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00,
        },
        [0x004B] = {
            0x00, 0x00, 0x88, 0x90, 0xA0, 0xC0, 0xC0, 0xA0, 0x90, 0x88, 0x88, 0x00, 0x00,
        },
        [0x004C] = {
            0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xF8, 0x00, 0x00,
        },
        [0x004D] = {
            0x00, 0x00, 0x88, 0xD8, 0xA8, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x00, 0x00,
        },
        [0x004E] = {
            0x00, 0x00, 0x88, 0xC8, 0xA8, 0x98, 0x88, 0x88, 0x88, 0x88, 0x88, 0x00, 0x00,
        },
        [0x004F] = {
            0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00,
        },
        [0x0050] = {
            0x00, 0x00, 0xF0, 0x88, 0x88, 0x88, 0xF0, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00,
        },
        [0x0051] = {
            0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x10, 0x0C,
        },
        [0x0052] = {
            0x00, 0x00, 0xF0, 0x88, 0x88, 0x88, 0xF0, 0xA0, 0x90, 0x88, 0x88, 0x00, 0x00,
        },
        [0x0053] = {
            0x00, 0x00, 0x70, 0x88, 0x80, 0x80, 0x70, 0x08, 0x08, 0x88, 0x70, 0x00, 0x00,
        },
        [0x0054] = {
            0x00, 0x00, 0xF8, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00,
        },
        [0x0055] = {
            0x00, 0x00, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00,
        },
        [0x0056] = {
            0x00, 0x00, 0x88, 0x88, 0x88, 0x88, 0x50, 0x50, 0x50, 0x20, 0x20, 0x00, 0x00,
        },
        [0x0057] = {
            0x00, 0x00, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0x50, 0x50, 0x50, 0x00, 0x00,
        },
        [0x0058] = {
            0x00, 0x00, 0x88, 0x88, 0x50, 0x50, 0x20, 0x50, 0x50, 0x88, 0x88, 0x00, 0x00,
        },
        [0x0059] = {
            0x00, 0x00, 0x88, 0x88, 0x50, 0x50, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00,
        },
        [0x005A] = {
            0x00, 0x00, 0xF8, 0x08, 0x10, 0x10, 0x20, 0x40, 0x40, 0x80, 0xF8, 0x00, 0x00,
        },
        [0x005B] = {
            0x00, 0x70, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x70, 0x00,
        },
        [0x005C] = {
            0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0x20, 0x20, 0x10, 0x10, 0x08, 0x08, 0x00,
        },
        [0x005D] = {
            0x00, 0x70, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x70, 0x00,
        },
        [0x005E] = {
            0x00, 0x20, 0x50, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        [0x005F] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00,
        },
        [0x0060] = {
            0x00, 0x40, 0x40, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        [0x0061] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x08, 0x78, 0x88, 0x88, 0x78, 0x00, 0x00,
        },
        [0x0062] = {
            0x00, 0x00, 0x80, 0x80, 0x80, 0xF0, 0x88, 0x88, 0x88, 0x88, 0xF0, 0x00, 0x00,
        },
        [0x0063] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x88, 0x80, 0x80, 0x88, 0x70, 0x00, 0x00,
        },
        [0x0064] = {
            0x00, 0x00, 0x08, 0x08, 0x08, 0x78, 0x88, 0x88, 0x88, 0x88, 0x78, 0x00, 0x00,
        },
        [0x0065] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x88, 0xF8, 0x80, 0x88, 0x70, 0x00, 0x00,
        },
        [0x0066] = {
            0x00, 0x00, 0x18, 0x20, 0x20, 0x20, 0xF8, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00,
        },
        [0x0067] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x88, 0x88, 0x88, 0x78, 0x08, 0x88, 0x70,
        },
        [0x0068] = {
            0x00, 0x00, 0x80, 0x80, 0x80, 0xB0, 0xC8, 0x88, 0x88, 0x88, 0x88, 0x00, 0x00,
        },
        [0x0069] = {
            0x00, 0x20, 0x00, 0x00, 0x00, 0x60, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00, 0x00,
        },
        [0x006A] = {
            0x00, 0x10, 0x00, 0x00, 0x00, 0x30, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0xE0,
        },
        [0x006B] = {
            0x00, 0x00, 0x80, 0x80, 0x80, 0x90, 0xA0, 0xC0, 0xA0, 0x90, 0x88, 0x00, 0x00,
        },
        [0x006C] = {
            0x00, 0x00, 0x60, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x30, 0x00, 0x00,
        },
        [0x006D] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0x00, 0x00,
        },
        [0x006E] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0xB0, 0xC8, 0x88, 0x88, 0x88, 0x88, 0x00, 0x00,
        },
        [0x006F] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00,
        },
        [0x0070] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x88, 0x88, 0x88, 0xF0, 0x80, 0x80, 0x80,
        },
        [0x0071] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x88, 0x88, 0x88, 0x78, 0x08, 0x08, 0x08,
        },
        [0x0072] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0xB0, 0xC8, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00,
        },
        [0x0073] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x88, 0x70, 0x08, 0x88, 0x70, 0x00, 0x00,
        },
        [0x0074] = {
            0x00, 0x00, 0x40, 0x40, 0x40, 0xF0, 0x40, 0x40, 0x40, 0x48, 0x30, 0x00, 0x00,
        },
        [0x0075] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x88, 0x88, 0x88, 0x98, 0x68, 0x00, 0x00,
        },
        [0x0076] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x88, 0x50, 0x50, 0x20, 0x20, 0x00, 0x00,
        },
        [0x0077] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0xA8, 0xA8, 0xA8, 0xA8, 0x50, 0x50, 0x00, 0x00,
        },
        [0x0078] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x50, 0x20, 0x20, 0x50, 0x88, 0x00, 0x00,
        },
        [0x0079] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x88, 0x88, 0x88, 0x78, 0x08, 0x88, 0x70,
        },
        [0x007A] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x10, 0x20, 0x40, 0x80, 0xF8, 0x00, 0x00,
        },
        [0x007B] = {
            0x00, 0x18, 0x20, 0x20, 0x20, 0x20, 0xC0, 0x20, 0x20, 0x20, 0x20, 0x18, 0x00,
        },
        [0x007C] = {
            0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00,
        },
        [0x007D] = {
            0x00, 0xC0, 0x20, 0x20, 0x20, 0x20, 0x18, 0x20, 0x20, 0x20, 0x20, 0xC0, 0x00,
        },
        [0x007E] = {
            0x00, 0x00, 0x68, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        [0x007F] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        [0x0080] = {
            0x00, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8,
        },
        [0x0081] = {
            0x00, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8,
        },
        [0x0082] = {
            0x00, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8,
        },
        [0x0083] = {
            0x00, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8,
        },
        [0x0084] = {
            0x00, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8,
        },
        [0x0085] = {
            0x00, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8,
        },
        [0x0086] = {
            0x00, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8,
        },
        [0x0087] = {
            0x00, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8,
        },
        [0x0088] = {
            0x00, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8,
        },
        [0x0089] = {
            0x00, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8,
        },
        [0x008A] = {
            0x00, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8,
        },
        [0x008B] = {
            0x00, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8,
        },
        [0x008C] = {
            0x00, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8,
        },
        [0x008D] = {
            0x00, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8,
        },
        [0x008E] = {
            0x00, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8,
        },
        [0x008F] = {
            0x00, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8,
        },
        [0x0090] = {
            0x00, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8,
        },
        [0x0091] = {
            0x00, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8,
        },
        [0x0092] = {
            0x00, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8,
        },
        [0x0093] = {
            0x00, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8,
        },
        [0x0094] = {
            0x00, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8,
        },
        [0x0095] = {
            0x00, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8,
        },
        [0x0096] = {
            0x00, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8,
        },
        [0x0097] = {
            0x00, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8,
        },
        [0x0098] = {
            0x00, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8,
        },
        [0x0099] = {
            0x00, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8,
        },
        [0x009A] = {
            0x00, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8,
        },
        [0x009B] = {
            0x00, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8,
        },
        [0x009C] = {
            0x00, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8,
        },
        [0x009D] = {
            0x00, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8,
        },
        [0x009E] = {
            0x00, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8,
        },
        [0x009F] = {
            0x00, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8, 0x54, 0xA8,
        },
        [0x00A0] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        [0x00A1] = {
            0x00, 0x00, 0x20, 0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00,
        },
        [0x00A2] = {
            0x00, 0x00, 0x20, 0x20, 0x70, 0xA8, 0xA0, 0xA0, 0xA0, 0x78, 0x20, 0x00, 0x00,
        },
        [0x00A3] = {
            0x00, 0x00, 0x30, 0x48, 0x40, 0x40, 0xF0, 0x40, 0x40, 0x60, 0x98, 0x00, 0x00,
        },
        [0x00A4] = {
            0x00, 0x00, 0x00, 0x00, 0x88, 0x70, 0x50, 0x50, 0x70, 0x88, 0x00, 0x00, 0x00,
        },
        [0x00A5] = {
            0x00, 0x00, 0x88, 0x88, 0x50, 0x50, 0xF8, 0x20, 0xF8, 0x20, 0x20, 0x00, 0x00,
        },
        [0x00A6] = {
            0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00,
        },
        [0x00A7] = {
            0x00, 0x60, 0x90, 0x80, 0x40, 0xA0, 0x90, 0x50, 0x20, 0x10, 0x90, 0x60, 0x00,
        },
        [0x00A8] = {
            0x00, 0x00, 0xD8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        [0x00A9] = {
            0x00, 0x00, 0xF8, 0x88, 0x70, 0x40, 0x40, 0x40, 0x70, 0x88, 0xF8, 0x00, 0x00,
        },
        [0x00AA] = {
            0x00, 0x00, 0x70, 0x08, 0x78, 0x88, 0x78, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00,
        },
        [0x00AB] = {
            0x00, 0x00, 0x08, 0x10, 0x28, 0x50, 0xA0, 0x50, 0x28, 0x10, 0x08, 0x00, 0x00,
        },
        [0x00AC] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00,
        },
        [0x00AD] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        [0x00AE] = {
            0x00, 0x00, 0xF8, 0x88, 0x70, 0x50, 0x60, 0x50, 0x50, 0x88, 0xF8, 0x00, 0x00,
        },
        [0x00AF] = {
            0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        [0x00B0] = {
            0x00, 0x60, 0x90, 0x90, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        [0x00B1] = {
            0x00, 0x00, 0x00, 0x20, 0x20, 0xF8, 0x20, 0x20, 0x00, 0x00, 0xF8, 0x00, 0x00,
        },
        [0x00B2] = {
            0x00, 0x60, 0x90, 0x10, 0x20, 0x40, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        [0x00B3] = {
            0x00, 0xF0, 0x10, 0x60, 0x10, 0x90, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        [0x00B4] = {
            0x00, 0x10, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        [0x00B5] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x88, 0x88, 0x88, 0x98, 0xE8, 0x80, 0x80,
        },
        [0x00B6] = {
            0x00, 0x00, 0x78, 0xE8, 0xE8, 0xE8, 0xE8, 0x68, 0x28, 0x28, 0x28, 0x00, 0x00,
        },
        [0x00B7] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x70, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        [0x00B8] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x20, 0x40,
        },
        [0x00B9] = {
            0x00, 0x20, 0x60, 0xA0, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        [0x00BA] = {
            0x00, 0x60, 0x90, 0x90, 0x90, 0x60, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        [0x00BB] = {
            0x00, 0x00, 0x80, 0x40, 0xA0, 0x50, 0x28, 0x50, 0xA0, 0x40, 0x80, 0x00, 0x00,
        },
        [0x00BC] = {
            0x00, 0x00, 0x40, 0xC0, 0x40, 0x40, 0x50, 0x30, 0x50, 0x78, 0x10, 0x00, 0x00,
        },
        [0x00BD] = {
            0x00, 0x00, 0x40, 0xC0, 0x40, 0x40, 0x50, 0x28, 0x08, 0x10, 0x38, 0x00, 0x00,
        },
        [0x00BE] = {
            0x00, 0x00, 0xE0, 0x20, 0x40, 0x20, 0xD0, 0x30, 0x50, 0x78, 0x10, 0x00, 0x00,
        },
        [0x00BF] = {
            0x00, 0x00, 0x20, 0x00, 0x20, 0x20, 0x40, 0x80, 0x88, 0x88, 0x70, 0x00, 0x00,
        },
        [0x00C0] = {
            0x00, 0x20, 0x10, 0x00, 0x20, 0x20, 0x50, 0x50, 0xF8, 0x88, 0x88, 0x00, 0x00,
        },
        [0x00C1] = {
            0x00, 0x10, 0x20, 0x00, 0x20, 0x20, 0x50, 0x50, 0xF8, 0x88, 0x88, 0x00, 0x00,
        },
        [0x00C2] = {
            0x00, 0x30, 0x48, 0x00, 0x20, 0x20, 0x50, 0x50, 0xF8, 0x88, 0x88, 0x00, 0x00,
        },
        [0x00C3] = {
            0x00, 0x68, 0xB0, 0x00, 0x20, 0x20, 0x50, 0x50, 0xF8, 0x88, 0x88, 0x00, 0x00,
        },
        [0x00C4] = {
            0x00, 0x50, 0x50, 0x00, 0x20, 0x20, 0x50, 0x50, 0xF8, 0x88, 0x88, 0x00, 0x00,
        },
        [0x00C5] = {
            0x00, 0x30, 0x48, 0x48, 0x30, 0x20, 0x50, 0x50, 0xF8, 0x88, 0x88, 0x00, 0x00,
        },
        [0x00C6] = {
            0x00, 0x00, 0xF8, 0xA0, 0xA0, 0xA0, 0xF8, 0xA0, 0xA0, 0xA0, 0xB8, 0x00, 0x00,
        },
        [0x00C7] = {
            0x00, 0x00, 0x70, 0x88, 0x80, 0x80, 0x80, 0x80, 0x80, 0x88, 0x70, 0x20, 0x40,
        },
        [0x00C8] = {
            0x00, 0x20, 0x10, 0x00, 0xF8, 0x80, 0x80, 0xF0, 0x80, 0x80, 0xF8, 0x00, 0x00,
        },
        [0x00C9] = {
            0x00, 0x10, 0x20, 0x00, 0xF8, 0x80, 0x80, 0xF0, 0x80, 0x80, 0xF8, 0x00, 0x00,
        },
        [0x00CA] = {
            0x00, 0x30, 0x48, 0x00, 0xF8, 0x80, 0x80, 0xF0, 0x80, 0x80, 0xF8, 0x00, 0x00,
        },
        [0x00CB] = {
            0x00, 0x50, 0x50, 0x00, 0xF8, 0x80, 0x80, 0xF0, 0x80, 0x80, 0xF8, 0x00, 0x00,
        },
        [0x00CC] = {
            0x00, 0x20, 0x10, 0x00, 0x70, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00, 0x00,
        },
        [0x00CD] = {
            0x00, 0x10, 0x20, 0x00, 0x70, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00, 0x00,
        },
        [0x00CE] = {
            0x00, 0x30, 0x48, 0x00, 0x70, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00, 0x00,
        },
        [0x00CF] = {
            0x00, 0x50, 0x50, 0x00, 0x70, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00, 0x00,
        },
        [0x00D0] = {
            0x00, 0x00, 0xF0, 0x48, 0x48, 0x48, 0xE8, 0x48, 0x48, 0x48, 0xF0, 0x00, 0x00,
        },
        [0x00D1] = {
            0x00, 0x68, 0xB0, 0x00, 0x88, 0xC8, 0xA8, 0x98, 0x88, 0x88, 0x88, 0x00, 0x00,
        },
        [0x00D2] = {
            0x00, 0x20, 0x10, 0x00, 0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00,
        },
        [0x00D3] = {
            0x00, 0x10, 0x20, 0x00, 0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00,
        },
        [0x00D4] = {
            0x00, 0x30, 0x48, 0x00, 0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00,
        },
        [0x00D5] = {
            0x00, 0x68, 0xB0, 0x00, 0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00,
        },
        [0x00D6] = {
            0x00, 0x50, 0x50, 0x00, 0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00,
        },
        [0x00D7] = {
            0x00, 0x00, 0x00, 0x00, 0x88, 0x50, 0x20, 0x50, 0x88, 0x00, 0x00, 0x00, 0x00,
        },
        [0x00D8] = {
            0x00, 0x08, 0x70, 0x98, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xC8, 0x70, 0x80, 0x00,
        },
        [0x00D9] = {
            0x00, 0x20, 0x10, 0x00, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00,
        },
        [0x00DA] = {
            0x00, 0x10, 0x20, 0x00, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00,
        },
        [0x00DB] = {
            0x00, 0x30, 0x48, 0x00, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00,
        },
        [0x00DC] = {
            0x00, 0x50, 0x50, 0x00, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00,
        },
        [0x00DD] = {
            0x00, 0x10, 0x20, 0x00, 0x88, 0x88, 0x50, 0x50, 0x20, 0x20, 0x20, 0x00, 0x00,
        },
        [0x00DE] = {
            0x00, 0x80, 0x80, 0xF0, 0x88, 0x88, 0x88, 0xF0, 0x80, 0x80, 0x80, 0x00, 0x00,
        },
        [0x00DF] = {
            0x00, 0x00, 0x00, 0x70, 0x88, 0x88, 0xF0, 0x88, 0x88, 0x88, 0xF0, 0x80, 0x80,
        },
        [0x00E0] = {
            0x00, 0x20, 0x10, 0x00, 0x00, 0x70, 0x08, 0x78, 0x88, 0x88, 0x78, 0x00, 0x00,
        },
        [0x00E1] = {
            0x00, 0x10, 0x20, 0x00, 0x00, 0x70, 0x08, 0x78, 0x88, 0x88, 0x78, 0x00, 0x00,
        },
        [0x00E2] = {
            0x00, 0x30, 0x48, 0x00, 0x00, 0x70, 0x08, 0x78, 0x88, 0x88, 0x78, 0x00, 0x00,
        },
        [0x00E3] = {
            0x00, 0x68, 0xB0, 0x00, 0x00, 0x70, 0x08, 0x78, 0x88, 0x88, 0x78, 0x00, 0x00,
        },
        [0x00E4] = {
            0x00, 0x50, 0x50, 0x00, 0x00, 0x70, 0x08, 0x78, 0x88, 0x88, 0x78, 0x00, 0x00,
        },
        [0x00E5] = {
            0x00, 0x30, 0x48, 0x30, 0x00, 0x70, 0x08, 0x78, 0x88, 0x88, 0x78, 0x00, 0x00,
        },
        [0x00E6] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x28, 0xF8, 0xA0, 0xA0, 0xF8, 0x00, 0x00,
        },
        [0x00E7] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x88, 0x80, 0x80, 0x88, 0x70, 0x20, 0x40,
        },
        [0x00E8] = {
            0x00, 0x20, 0x10, 0x00, 0x00, 0x70, 0x88, 0xF8, 0x80, 0x88, 0x70, 0x00, 0x00,
        },
        [0x00E9] = {
            0x00, 0x10, 0x20, 0x00, 0x00, 0x70, 0x88, 0xF8, 0x80, 0x88, 0x70, 0x00, 0x00,
        },
        [0x00EA] = {
            0x00, 0x30, 0x48, 0x00, 0x00, 0x70, 0x88, 0xF8, 0x80, 0x88, 0x70, 0x00, 0x00,
        },
        [0x00EB] = {
            0x00, 0x50, 0x50, 0x00, 0x00, 0x70, 0x88, 0xF8, 0x80, 0x88, 0x70, 0x00, 0x00,
        },
        [0x00EC] = {
            0x00, 0x20, 0x10, 0x00, 0x00, 0x60, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00, 0x00,
        },
        [0x00ED] = {
            0x00, 0x10, 0x20, 0x00, 0x00, 0x60, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00, 0x00,
        },
        [0x00EE] = {
            0x00, 0x30, 0x48, 0x00, 0x00, 0x60, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00, 0x00,
        },
        [0x00EF] = {
            0x00, 0x50, 0x50, 0x00, 0x00, 0x60, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00, 0x00,
        },
        [0x00F0] = {
            0x00, 0x40, 0x38, 0xE0, 0x10, 0x70, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00,
        },
        [0x00F1] = {
            0x00, 0x68, 0xB0, 0x00, 0x00, 0xB0, 0xC8, 0x88, 0x88, 0x88, 0x88, 0x00, 0x00,
        },
        [0x00F2] = {
            0x00, 0x20, 0x10, 0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00,
        },
        [0x00F3] = {
            0x00, 0x10, 0x20, 0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00,
        },
        [0x00F4] = {
            0x00, 0x30, 0x48, 0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00,
        },
        [0x00F5] = {
            0x00, 0x68, 0xB0, 0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00,
        },
        [0x00F6] = {
            0x00, 0x50, 0x50, 0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00,
        },
        [0x00F7] = {
            0x00, 0x00, 0x00, 0x20, 0x20, 0x00, 0xF8, 0x00, 0x20, 0x20, 0x00, 0x00, 0x00,
        },
        [0x00F8] = {
            0x00, 0x00, 0x00, 0x00, 0x08, 0x70, 0x98, 0xA8, 0xA8, 0xC8, 0x70, 0x80, 0x00,
        },
        [0x00F9] = {
            0x00, 0x20, 0x10, 0x00, 0x00, 0x88, 0x88, 0x88, 0x88, 0x98, 0x68, 0x00, 0x00,
        },
        [0x00FA] = {
            0x00, 0x10, 0x20, 0x00, 0x00, 0x88, 0x88, 0x88, 0x88, 0x98, 0x68, 0x00, 0x00,
        },
        [0x00FB] = {
            0x00, 0x30, 0x48, 0x00, 0x00, 0x88, 0x88, 0x88, 0x88, 0x98, 0x68, 0x00, 0x00,
        },
        [0x00FC] = {
            0x00, 0x50, 0x50, 0x00, 0x00, 0x88, 0x88, 0x88, 0x88, 0x98, 0x68, 0x00, 0x00,
        },
        [0x00FD] = {
            0x00, 0x10, 0x20, 0x00, 0x00, 0x88, 0x88, 0x88, 0x88, 0x78, 0x08, 0x88, 0x70,
        },
        [0x00FE] = {
            0x00, 0x00, 0x00, 0x80, 0x80, 0xF0, 0x88, 0x88, 0x88, 0xF0, 0x80, 0x80, 0x80,
        },
        [0x00FF] = {
            0x00, 0x50, 0x50, 0x00, 0x00, 0x88, 0x88, 0x88, 0x88, 0x78, 0x08, 0x88, 0x70,
        },
};


Drawable_multi_bitmap const mplus_fonts = {
    .height = FONT_HIGHT,
    .width = FONT_WIDTH,
    .size = FONT_SIZE,
    .color = {},
    .data  = {
        s_mplus_font[0x0000],
        s_mplus_font[0x0001],
        s_mplus_font[0x0002],
        s_mplus_font[0x0003],
        s_mplus_font[0x0004],
        s_mplus_font[0x0005],
        s_mplus_font[0x0006],
        s_mplus_font[0x0007],
        s_mplus_font[0x0008],
        s_mplus_font[0x0009],
        s_mplus_font[0x000A],
        s_mplus_font[0x000B],
        s_mplus_font[0x000C],
        s_mplus_font[0x000D],
        s_mplus_font[0x000E],
        s_mplus_font[0x000F],
        s_mplus_font[0x0010],
        s_mplus_font[0x0011],
        s_mplus_font[0x0012],
        s_mplus_font[0x0013],
        s_mplus_font[0x0014],
        s_mplus_font[0x0015],
        s_mplus_font[0x0016],
        s_mplus_font[0x0017],
        s_mplus_font[0x0018],
        s_mplus_font[0x0019],
        s_mplus_font[0x001A],
        s_mplus_font[0x001B],
        s_mplus_font[0x001C],
        s_mplus_font[0x001D],
        s_mplus_font[0x001E],
        s_mplus_font[0x001F],
        s_mplus_font[0x0020],
        s_mplus_font[0x0021],
        s_mplus_font[0x0022],
        s_mplus_font[0x0023],
        s_mplus_font[0x0024],
        s_mplus_font[0x0025],
        s_mplus_font[0x0026],
        s_mplus_font[0x0027],
        s_mplus_font[0x0028],
        s_mplus_font[0x0029],
        s_mplus_font[0x002A],
        s_mplus_font[0x002B],
        s_mplus_font[0x002C],
        s_mplus_font[0x002D],
        s_mplus_font[0x002E],
        s_mplus_font[0x002F],
        s_mplus_font[0x0030],
        s_mplus_font[0x0031],
        s_mplus_font[0x0032],
        s_mplus_font[0x0033],
        s_mplus_font[0x0034],
        s_mplus_font[0x0035],
        s_mplus_font[0x0036],
        s_mplus_font[0x0037],
        s_mplus_font[0x0038],
        s_mplus_font[0x0039],
        s_mplus_font[0x003A],
        s_mplus_font[0x003B],
        s_mplus_font[0x003C],
        s_mplus_font[0x003D],
        s_mplus_font[0x003E],
        s_mplus_font[0x003F],
        s_mplus_font[0x0040],
        s_mplus_font[0x0041],
        s_mplus_font[0x0042],
        s_mplus_font[0x0043],
        s_mplus_font[0x0044],
        s_mplus_font[0x0045],
        s_mplus_font[0x0046],
        s_mplus_font[0x0047],
        s_mplus_font[0x0048],
        s_mplus_font[0x0049],
        s_mplus_font[0x004A],
        s_mplus_font[0x004B],
        s_mplus_font[0x004C],
        s_mplus_font[0x004D],
        s_mplus_font[0x004E],
        s_mplus_font[0x004F],
        s_mplus_font[0x0050],
        s_mplus_font[0x0051],
        s_mplus_font[0x0052],
        s_mplus_font[0x0053],
        s_mplus_font[0x0054],
        s_mplus_font[0x0055],
        s_mplus_font[0x0056],
        s_mplus_font[0x0057],
        s_mplus_font[0x0058],
        s_mplus_font[0x0059],
        s_mplus_font[0x005A],
        s_mplus_font[0x005B],
        s_mplus_font[0x005C],
        s_mplus_font[0x005D],
        s_mplus_font[0x005E],
        s_mplus_font[0x005F],
        s_mplus_font[0x0060],
        s_mplus_font[0x0061],
        s_mplus_font[0x0062],
        s_mplus_font[0x0063],
        s_mplus_font[0x0064],
        s_mplus_font[0x0065],
        s_mplus_font[0x0066],
        s_mplus_font[0x0067],
        s_mplus_font[0x0068],
        s_mplus_font[0x0069],
        s_mplus_font[0x006A],
        s_mplus_font[0x006B],
        s_mplus_font[0x006C],
        s_mplus_font[0x006D],
        s_mplus_font[0x006E],
        s_mplus_font[0x006F],
        s_mplus_font[0x0070],
        s_mplus_font[0x0071],
        s_mplus_font[0x0072],
        s_mplus_font[0x0073],
        s_mplus_font[0x0074],
        s_mplus_font[0x0075],
        s_mplus_font[0x0076],
        s_mplus_font[0x0077],
        s_mplus_font[0x0078],
        s_mplus_font[0x0079],
        s_mplus_font[0x007A],
        s_mplus_font[0x007B],
        s_mplus_font[0x007C],
        s_mplus_font[0x007D],
        s_mplus_font[0x007E],
        s_mplus_font[0x007F],
        s_mplus_font[0x0080],
        s_mplus_font[0x0081],
        s_mplus_font[0x0082],
        s_mplus_font[0x0083],
        s_mplus_font[0x0084],
        s_mplus_font[0x0085],
        s_mplus_font[0x0086],
        s_mplus_font[0x0087],
        s_mplus_font[0x0088],
        s_mplus_font[0x0089],
        s_mplus_font[0x008A],
        s_mplus_font[0x008B],
        s_mplus_font[0x008C],
        s_mplus_font[0x008D],
        s_mplus_font[0x008E],
        s_mplus_font[0x008F],
        s_mplus_font[0x0090],
        s_mplus_font[0x0091],
        s_mplus_font[0x0092],
        s_mplus_font[0x0093],
        s_mplus_font[0x0094],
        s_mplus_font[0x0095],
        s_mplus_font[0x0096],
        s_mplus_font[0x0097],
        s_mplus_font[0x0098],
        s_mplus_font[0x0099],
        s_mplus_font[0x009A],
        s_mplus_font[0x009B],
        s_mplus_font[0x009C],
        s_mplus_font[0x009D],
        s_mplus_font[0x009E],
        s_mplus_font[0x009F],
        s_mplus_font[0x00A0],
        s_mplus_font[0x00A1],
        s_mplus_font[0x00A2],
        s_mplus_font[0x00A3],
        s_mplus_font[0x00A4],
        s_mplus_font[0x00A5],
        s_mplus_font[0x00A6],
        s_mplus_font[0x00A7],
        s_mplus_font[0x00A8],
        s_mplus_font[0x00A9],
        s_mplus_font[0x00AA],
        s_mplus_font[0x00AB],
        s_mplus_font[0x00AC],
        s_mplus_font[0x00AD],
        s_mplus_font[0x00AE],
        s_mplus_font[0x00AF],
        s_mplus_font[0x00B0],
        s_mplus_font[0x00B1],
        s_mplus_font[0x00B2],
        s_mplus_font[0x00B3],
        s_mplus_font[0x00B4],
        s_mplus_font[0x00B5],
        s_mplus_font[0x00B6],
        s_mplus_font[0x00B7],
        s_mplus_font[0x00B8],
        s_mplus_font[0x00B9],
        s_mplus_font[0x00BA],
        s_mplus_font[0x00BB],
        s_mplus_font[0x00BC],
        s_mplus_font[0x00BD],
        s_mplus_font[0x00BE],
        s_mplus_font[0x00BF],
        s_mplus_font[0x00C0],
        s_mplus_font[0x00C1],
        s_mplus_font[0x00C2],
        s_mplus_font[0x00C3],
        s_mplus_font[0x00C4],
        s_mplus_font[0x00C5],
        s_mplus_font[0x00C6],
        s_mplus_font[0x00C7],
        s_mplus_font[0x00C8],
        s_mplus_font[0x00C9],
        s_mplus_font[0x00CA],
        s_mplus_font[0x00CB],
        s_mplus_font[0x00CC],
        s_mplus_font[0x00CD],
        s_mplus_font[0x00CE],
        s_mplus_font[0x00CF],
        s_mplus_font[0x00D0],
        s_mplus_font[0x00D1],
        s_mplus_font[0x00D2],
        s_mplus_font[0x00D3],
        s_mplus_font[0x00D4],
        s_mplus_font[0x00D5],
        s_mplus_font[0x00D6],
        s_mplus_font[0x00D7],
        s_mplus_font[0x00D8],
        s_mplus_font[0x00D9],
        s_mplus_font[0x00DA],
        s_mplus_font[0x00DB],
        s_mplus_font[0x00DC],
        s_mplus_font[0x00DD],
        s_mplus_font[0x00DE],
        s_mplus_font[0x00DF],
        s_mplus_font[0x00E0],
        s_mplus_font[0x00E1],
        s_mplus_font[0x00E2],
        s_mplus_font[0x00E3],
        s_mplus_font[0x00E4],
        s_mplus_font[0x00E5],
        s_mplus_font[0x00E6],
        s_mplus_font[0x00E7],
        s_mplus_font[0x00E8],
        s_mplus_font[0x00E9],
        s_mplus_font[0x00EA],
        s_mplus_font[0x00EB],
        s_mplus_font[0x00EC],
        s_mplus_font[0x00ED],
        s_mplus_font[0x00EE],
        s_mplus_font[0x00EF],
        s_mplus_font[0x00F0],
        s_mplus_font[0x00F1],
        s_mplus_font[0x00F2],
        s_mplus_font[0x00F3],
        s_mplus_font[0x00F4],
        s_mplus_font[0x00F5],
        s_mplus_font[0x00F6],
        s_mplus_font[0x00F7],
        s_mplus_font[0x00F8],
        s_mplus_font[0x00F9],
        s_mplus_font[0x00FA],
        s_mplus_font[0x00FB],
        s_mplus_font[0x00FC],
        s_mplus_font[0x00FD],
        s_mplus_font[0x00FE],
        s_mplus_font[0x00FF],
    }
};
