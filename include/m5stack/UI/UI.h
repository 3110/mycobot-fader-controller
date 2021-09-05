#ifndef _UI_H
#define _UI_H

#include <M5Stack.h>

typedef int32_t coord_t;
typedef uint16_t length_t;
typedef uint32_t color_t;
typedef uint8_t font_t;
typedef uint8_t font_size_t;
typedef uint8_t text_datum_t;

class UIParts {
public:
    virtual void draw(TFT_eSprite &sprite) = 0;
    virtual void clear(TFT_eSprite &sprite) = 0;
};

#endif