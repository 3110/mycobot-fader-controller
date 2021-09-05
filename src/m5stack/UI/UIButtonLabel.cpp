#include "m5stack/UI/UIButtonLabel.h"

UIButtonLabel::UIButtonLabel(coord_t x) : x(x) {
}

UIButtonLabel::~UIButtonLabel(void) {
}

void UIButtonLabel::setLabel(const char *label) {
    snprintf(this->label, sizeof(this->label), "%s",
             label == nullptr ? "" : label);
}

void UIButtonLabel::draw(TFT_eSprite &sprite) {
    sprite.createSprite(WIDTH, HEIGHT);
    sprite.fillSprite(BG_COLOR);
    sprite.setTextColor(TEXT_COLOR);
    sprite.setTextDatum(TEXT_DATUM);
    sprite.drawString(this->label, WIDTH / 2, HEIGHT / 2, FONT);
    sprite.pushSprite(getX(), getY());
    sprite.deleteSprite();
}

void UIButtonLabel::clear(TFT_eSprite &sprite) {
    sprite.createSprite(WIDTH, HEIGHT);
    sprite.fillSprite(BG_COLOR);
    sprite.pushSprite(getX(), getY());
    sprite.deleteSprite();
}
