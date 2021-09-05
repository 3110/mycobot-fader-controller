#ifndef _UI_BUTTON_H
#define _UI_BUTTON_H

#include "UI.h"

class UIButtonLabel : public UIParts {
public:
    static const coord_t BUTTON_A_XPOS = 25;
    static const coord_t BUTTON_B_XPOS = 120;
    static const coord_t BUTTON_C_XPOS = 215;

    UIButtonLabel(coord_t x);
    virtual ~UIButtonLabel(void);

    inline coord_t getX(void) const {
        return this->x;
    }

    inline coord_t getY(void) const {
        return Y_POS;
    }

    inline const char *getLabel(void) const {
        return this->label;
    }

    void setLabel(const char *label);

    virtual void draw(TFT_eSprite &sprite);
    virtual void clear(TFT_eSprite &sprite);

private:
    static const size_t MAX_LABEL_LENGTH = 5;
    static const font_t FONT = 4;  // 24px ASCII
    static const coord_t Y_POS = 212;
    static const length_t WIDTH = 16 * MAX_LABEL_LENGTH;
    static const length_t HEIGHT = 26;
    static const color_t TEXT_COLOR = TFT_WHITE;
    static const color_t BG_COLOR = TFT_BLACK;
    static const text_datum_t TEXT_DATUM = MC_DATUM;

    char label[MAX_LABEL_LENGTH + 1] = {'\0'};
    coord_t x;
};

#endif