#include "UI/UIFader.h"

UIFader::UIFader(PbHub::Channels ch, Origin origin)
    : ch(ch),
      origin(origin),
      analogMinValue(ANALOG_MIN_VALUE),
      analogMiddleValue(ANALOG_MIDDLE_VALUE),
      analogMaxValue(ANALOG_MAX_VALUE),
      minValue(ANALOG_MIN_VALUE),
      maxValue(ANALOG_MAX_VALUE),
      label{0},
      analogValue(),
      rangeMinKey{0},
      rangeMidKey{0},
      rangeMaxKey{0} {
    snprintf(rangeMinKey, sizeof(rangeMinKey), "J%dMIN",
             static_cast<uint16_t>(ch));
    snprintf(rangeMidKey, sizeof(rangeMinKey), "J%dMID",
             static_cast<uint16_t>(ch));
    snprintf(rangeMaxKey, sizeof(rangeMinKey), "J%dMAX",
             static_cast<uint16_t>(ch));
}

UIFader::~UIFader(void) {
}

void UIFader::draw(TFT_eSprite &sprite) {
    int16_t v = getAnalogValue();
    int16_t w =
        map(v, ANALOG_MIN_VALUE, ANALOG_MAX_VALUE, 0, FADER_AXIS_WIDTH - 1);
    if (w > FADER_AXIS_WIDTH - 1) {
        w = FADER_AXIS_WIDTH - 1;
    }
    if (w < 0) {
        w = 0;
    }

    sprite.createSprite(FADER_WIDTH, FADER_HEIGHT);
    sprite.fillSprite(BG_COLOR);

    drawAxis(sprite);

    switch (this->origin) {
        case Origin::LEFT:
            sprite.fillCircle(FADER_AXIS_X_POS + w, FADER_AXIS_Y_POS,
                              FADER_POINT_R, FADER_POINT_COLOR);
            sprite.fillRect(FADER_AXIS_X_POS,
                            FADER_AXIS_Y_POS - FADER_AXIS_HEIGHT / 2,
                            FADER_AXIS_X_POS + w, FADER_AXIS_HEIGHT,
                            FADER_AXIS_VALUE_COLOR);
            break;
        case Origin::CENTER:
            sprite.fillCircle(FADER_AXIS_X_POS + w, FADER_AXIS_Y_POS,
                              FADER_POINT_R, FADER_POINT_COLOR);
            if (v >= ANALOG_MIDDLE_VALUE) {
                sprite.fillRect(FADER_AXIS_X_POS + FADER_AXIS_WIDTH / 2,
                                FADER_AXIS_Y_POS - FADER_AXIS_HEIGHT / 2,
                                w - FADER_AXIS_WIDTH / 2, FADER_AXIS_HEIGHT,
                                FADER_AXIS_VALUE_COLOR);
            } else {
                sprite.fillRect(FADER_AXIS_X_POS + w,
                                FADER_AXIS_Y_POS - FADER_AXIS_HEIGHT / 2,
                                FADER_AXIS_WIDTH / 2 - w, FADER_AXIS_HEIGHT,
                                FADER_AXIS_VALUE_COLOR);
            }
            break;
        case Origin::RIGHT:
            sprite.fillCircle(FADER_AXIS_X_POS + FADER_AXIS_WIDTH - w,
                              FADER_AXIS_Y_POS, FADER_POINT_R,
                              FADER_POINT_COLOR);
            sprite.fillRect(FADER_AXIS_X_POS + FADER_AXIS_WIDTH - w,
                            FADER_AXIS_Y_POS - FADER_AXIS_HEIGHT / 2, w,
                            FADER_AXIS_HEIGHT, FADER_AXIS_VALUE_COLOR);
            break;
        default:
            break;
    }

    drawValue(sprite, getValue());

    sprite.pushSprite(FADER_X_POS, getY());
    sprite.deleteSprite();
}

void UIFader::clear(TFT_eSprite &sprite) {
    sprite.createSprite(FADER_WIDTH, FADER_HEIGHT);
    sprite.fillSprite(BG_COLOR);
    sprite.deleteSprite();
}

int16_t UIFader::getValue(void) const {
    int16_t v = getAnalogValue();
    return map(v, ANALOG_MIN_VALUE, ANALOG_MAX_VALUE, this->minValue,
               this->maxValue);
}

UIFader *UIFader::setMinValue(int16_t v) {
    this->minValue = v;
    return this;
}

UIFader *UIFader::setMaxValue(int16_t v) {
    this->maxValue = v;
    return this;
}

int16_t UIFader::getAnalogValue(void) const {
    int16_t v = this->analogValue.get();
    if (v >= this->analogMiddleValue) {
        return map(v, this->analogMiddleValue, this->analogMaxValue,
                   ANALOG_MIDDLE_VALUE, ANALOG_MAX_VALUE);
    } else {
        return map(v, this->analogMinValue, this->analogMiddleValue - 1,
                   ANALOG_MIN_VALUE, ANALOG_MIDDLE_VALUE - 1);
    }
}

UIFader *UIFader::setAnalogValue(int16_t v) {
    this->analogValue.update(v);
    return this;
}

UIFader *UIFader::setAnalogMinValue(int16_t v) {
    this->analogMinValue = v;
    return this;
}

UIFader *UIFader::setAnalogMiddleValue(int16_t v) {
    this->analogMiddleValue = v;
    return this;
}

UIFader *UIFader::setAnalogMaxValue(int16_t v) {
    this->analogMaxValue = v;
    return this;
}

UIFader *UIFader::setLabel(const char *label) {
    snprintf(this->label, sizeof(this->label), "%s", label);
    return this;
}

bool UIFader::loadRange(Preferences &prefs) {
    if (!prefs.isKey(rangeMinKey)) {
        return false;
    }
    if (!prefs.isKey(rangeMidKey)) {
        return false;
    }
    if (!prefs.isKey(rangeMaxKey)) {
        return false;
    }
    setAnalogMinValue(prefs.getShort(rangeMinKey));
    setAnalogMiddleValue(prefs.getShort(rangeMidKey));
    setAnalogMaxValue(prefs.getShort(rangeMaxKey));
    return true;
}

bool UIFader::saveRange(Preferences &prefs) {
    if (prefs.putShort(this->rangeMinKey, this->analogMinValue) != 2) {
        return false;
    }
    if (prefs.putShort(this->rangeMidKey, this->analogMiddleValue) != 2) {
        prefs.remove(this->rangeMidKey);
        return false;
    }
    if (prefs.putShort(this->rangeMaxKey, this->analogMaxValue) != 2) {
        prefs.remove(this->rangeMinKey);
        prefs.remove(this->rangeMidKey);
        return false;
    }
    return true;
}

bool UIFader::clearRange(Preferences &prefs) {
    bool result = true;
    if (prefs.remove(this->rangeMinKey) == false) {
        result = false;
    }
    if (prefs.remove(this->rangeMidKey) == false) {
        result = false;
    }
    if (prefs.remove(this->rangeMaxKey) == false) {
        result = false;
    }
    return result;
}

void UIFader::drawAxis(TFT_eSprite &sprite) {
    sprite.fillRect(FADER_AXIS_X_POS, FADER_AXIS_Y_POS - FADER_AXIS_HEIGHT / 2,
                    FADER_AXIS_WIDTH, FADER_AXIS_HEIGHT, FADER_AXIS_COLOR);
    sprite.drawLine(
        FADER_AXIS_X_POS, FADER_AXIS_Y_POS - FADER_AXIS_SCALE_HEIGHT / 2,
        FADER_AXIS_X_POS, FADER_AXIS_Y_POS + FADER_AXIS_SCALE_HEIGHT / 2,
        FADER_AXIS_COLOR);
    sprite.drawLine(FADER_AXIS_X_POS + FADER_AXIS_WIDTH / 2,
                    FADER_AXIS_Y_POS - FADER_AXIS_SCALE_HEIGHT / 2,
                    FADER_AXIS_X_POS + FADER_AXIS_WIDTH / 2,
                    FADER_AXIS_Y_POS + FADER_AXIS_SCALE_HEIGHT / 2,
                    FADER_AXIS_COLOR);
    sprite.drawLine(FADER_AXIS_X_POS + FADER_AXIS_WIDTH,
                    FADER_AXIS_Y_POS - FADER_AXIS_SCALE_HEIGHT / 2,
                    FADER_AXIS_X_POS + FADER_AXIS_WIDTH,
                    FADER_AXIS_Y_POS + FADER_AXIS_SCALE_HEIGHT / 2,
                    FADER_AXIS_COLOR);
}

void UIFader::drawValue(TFT_eSprite &sprite, int16_t v) {
    char valStr[10] = {0};  // "J1: -135"
    snprintf(valStr, sizeof(valStr), "%2s: %-4d ", this->label, v);

    sprite.setTextDatum(FADER_AXIS_VALUE_DATUM);
    sprite.drawString(valStr, FADER_AXIS_VALUE_X_POS, FADER_AXIS_VALUE_Y_POS,
                      FADER_AXIS_VALUE_FONT);
}

void UIFader::drawSlider(TFT_eSprite &sprite) {
}
