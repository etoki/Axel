/************************************************************
 * File: include/drawable.h
 * Description: Drawable objects.
 ************************************************************/

#ifndef _DRAWABLE_H_
#define _DRAWABLE_H_



#include <rgb8.h>

enum Drawable_constants {
    MAX_HEIGHT_SIZE = 16,
    MAX_WIDTH_SIZE = 16,
};


struct Drawable_bitmap {
    int32_t height;
    int32_t width;
    RGB8 color;
    uint32_t const* data;
};
typedef struct Drawable_bitmap Drawable_bitmap;


struct Drawable_multi_bitmap {
    int32_t height;
    int32_t width;
    int32_t size;
    RGB8 color;
    uint32_t const* data[];
};
typedef struct Drawable_multi_bitmap Drawable_multi_bitmap;



#endif
