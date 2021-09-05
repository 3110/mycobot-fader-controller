#ifndef _UI_TITLE_H
#define _UI_TITLE_H

#include "UI.h"

class UITitle : public UIParts {
public:
    UITitle(const char *name, const char *version);
    virtual ~UITitle(void);

    virtual UITitle *setTitle(const char *name);
    virtual UITitle *setVersion(const char *version);

    virtual void draw(TFT_eSprite &sprite);
    virtual void clear(TFT_eSprite &sprite);

private:
    static const coord_t TITLE_WIDTH = 320;
    static const coord_t TITLE_HEIGHT = 28;
    static const coord_t TITLE_X_POS = 0;
    static const coord_t TITLE_Y_POS = 0;
    static const color_t TITLE_BG_COLOR = TFT_BLUE;

    static const font_t NAME_FONT = 4;
    static const text_datum_t NAME_DATUM = TC_DATUM;
    static const coord_t NAME_X_POS = TITLE_WIDTH / 2;
    static const coord_t NAME_Y_POS = 2;
    static const color_t NAME_TEXT_COLOR = TFT_WHITE;

    static const font_t VERSION_FONT = 2;
    static const text_datum_t VERSION_DATUM = BR_DATUM;
    static const coord_t VERSION_X_POS = TITLE_WIDTH - 1;
    static const coord_t VERSION_Y_POS = TITLE_HEIGHT - 2;
    static const color_t VERSION_TEXT_COLOR = TFT_WHITE;

    static const size_t NAME_LEN = 19;
    static const size_t VERSION_LEN = 9;  // v00.00.00

    char name[NAME_LEN + 1];
    char version[VERSION_LEN + 1];
};

#endif