#ifndef UI_FADER_H_
#define UI_FADER_H_

#include <Arduino.h>
#include <Preferences.h>

#include "MovingMean.h"
#include "m5stack/PbHub.h"
#include "m5stack/UI/UI.h"

class UIFader : public UIParts {
public:
    enum class Origin {
        LEFT,
        CENTER,
        RIGHT,
    };
    static const int16_t ANALOG_MIN_VALUE = 0;
#ifdef USE_PBHUB
    static const int16_t ANALOG_MAX_VALUE = 675;
#else
    static const int16_t ANALOG_MAX_VALUE = 4095;
#endif
    static const int16_t ANALOG_MIDDLE_VALUE =
        (ANALOG_MAX_VALUE - ANALOG_MIN_VALUE) / 2;

    UIFader(PbHub::Channels ch, Origin origin = Origin::LEFT);
    virtual ~UIFader(void);

    virtual void draw(TFT_eSprite &sprite);
    virtual void drawValue(TFT_eSprite &sprite, int16_t v);
    virtual void clear(TFT_eSprite &sprite);

    virtual int16_t getValue(void) const;
    virtual UIFader *setMinValue(int16_t v);
    virtual UIFader *setMaxValue(int16_t v);

    virtual int16_t getAnalogValue(void) const;
    virtual UIFader *setAnalogValue(int16_t v);
    virtual UIFader *setAnalogMinValue(int16_t v);
    virtual UIFader *setAnalogMiddleValue(int16_t v);
    virtual UIFader *setAnalogMaxValue(int16_t v);

    virtual UIFader *setLabel(const char *label);

    virtual bool loadRange(Preferences &prefs);
    virtual bool saveRange(Preferences &prefs);
    virtual bool clearRange(Preferences &prefs);

protected:
    inline coord_t getX(void) const {
        return FADER_X_POS;
    }

    inline coord_t getY(void) const {
        return FADER_Y_POS_BASE - static_cast<uint8_t>(this->ch) * FADER_HEIGHT;
    }

    inline length_t toLength(int16_t v) const {
        return map(map(v, this->minValue, this->maxValue, ANALOG_MIN_VALUE,
                       ANALOG_MAX_VALUE),
                   ANALOG_MIN_VALUE, ANALOG_MAX_VALUE, 0, FADER_AXIS_WIDTH);
    }

    virtual void drawAxis(TFT_eSprite &sprite);
    virtual void drawSlider(TFT_eSprite &sprite);

private:
    static const color_t BG_COLOR = TFT_BLACK;
    static const font_t FONT = 2;  // 16px
    static const length_t FADER_WIDTH = 320;
    static const length_t FADER_HEIGHT = 30;  // 28-212 -> 30-210 = 180
    static const coord_t FADER_X_POS = 0;
    static const coord_t FADER_Y_POS_BASE = 210 - FADER_HEIGHT;  // title height

    static const length_t FADER_LEFT_MARGIN = 70;
    static const length_t FADER_RIGHT_MARGIN = 15;
    static const length_t FADER_AXIS_WIDTH =
        FADER_WIDTH - (FADER_LEFT_MARGIN + FADER_RIGHT_MARGIN);
    static const length_t FADER_AXIS_HEIGHT = 3;
    static const length_t FADER_AXIS_X_POS = FADER_LEFT_MARGIN;
    static const length_t FADER_AXIS_Y_POS =
        FADER_HEIGHT / 2 - FADER_AXIS_HEIGHT / 2;
    static const color_t FADER_AXIS_COLOR = TFT_DARKGREY;

    static const length_t FADER_POINT_R = 6;
    static const color_t FADER_POINT_COLOR = TFT_WHITE;

    static const length_t FADER_AXIS_SCALE_HEIGHT = 6;

    static const font_t FADER_AXIS_VALUE_FONT = FONT;
    static const coord_t FADER_AXIS_VALUE_DATUM = ML_DATUM;
    static const coord_t FADER_AXIS_VALUE_X_POS = 5;
    static const coord_t FADER_AXIS_VALUE_Y_POS = FADER_AXIS_Y_POS;
    static const color_t FADER_AXIS_VALUE_COLOR = FADER_POINT_COLOR;

    static const size_t MAX_LABEL_LENGTH = 5;
    static const size_t MAX_PREF_KEY_LENGTH = 5;

    PbHub::Channels ch;
    Origin origin;
    int16_t analogMinValue;
    int16_t analogMiddleValue;
    int16_t analogMaxValue;
    int16_t minValue;
    int16_t maxValue;
    char label[MAX_LABEL_LENGTH + 1];
    MovingMean<int16_t, 5> analogValue;
    char rangeMinKey[MAX_PREF_KEY_LENGTH + 1];
    char rangeMidKey[MAX_PREF_KEY_LENGTH + 1];
    char rangeMaxKey[MAX_PREF_KEY_LENGTH + 1];
};

#endif