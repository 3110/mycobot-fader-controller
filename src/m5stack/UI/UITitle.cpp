#include "m5stack/UI/UITitle.h"

UITitle::UITitle(const char *name, const char *version) : name{0}, version{0} {
    this->setTitle(name)->setVersion(version);
}

UITitle::~UITitle(void) {
}

UITitle *UITitle::setTitle(const char *name) {
    snprintf(this->name, sizeof(this->name), "%s", name == nullptr ? "" : name);
    return this;
}

UITitle *UITitle::setVersion(const char *version) {
    snprintf(this->version, sizeof(this->version), "%s",
             version == nullptr ? "" : version);
    return this;
}

void UITitle::draw(TFT_eSprite &sprite) {
    sprite.setColorDepth(8);
    sprite.createSprite(TITLE_WIDTH, TITLE_HEIGHT);
    sprite.fillSprite(TITLE_BG_COLOR);

    sprite.setTextColor(VERSION_TEXT_COLOR);
    sprite.setTextDatum(VERSION_DATUM);
    sprite.drawString(this->version, VERSION_X_POS, VERSION_Y_POS,
                      VERSION_FONT);

    sprite.setTextColor(NAME_TEXT_COLOR);
    sprite.setTextDatum(NAME_DATUM);
    sprite.drawString(this->name, NAME_X_POS, NAME_Y_POS, NAME_FONT);

    sprite.pushSprite(TITLE_X_POS, TITLE_Y_POS);
    sprite.deleteSprite();
}

void UITitle::clear(TFT_eSprite &sprite) {
    sprite.setColorDepth(8);
    sprite.createSprite(TITLE_WIDTH, TITLE_HEIGHT);
    sprite.fillSprite(TITLE_BG_COLOR);
    sprite.pushSprite(TITLE_X_POS, TITLE_Y_POS);
    sprite.deleteSprite();
}
