#include <MycobotBasic.h>
#include <ParameterList.h>

#include "UI/FaderControllerUITask.h"
#include "m5stack/PbHub.h"

const char TITLE[] = "Fader Controller";
const char VERSION[] = "v0.0.1";

const uint32_t LONG_PRESS_THRETHOLD_MSEC_FOR_CLEAR = 3000;

const uint8_t INPUT_PIN = 36;
const size_t NUMBER_OF_FADERS = 6;
const BaseType_t UI_CORE = 1;

MycobotBasic myCobot;
PbHub hub(INPUT_PIN);
FaderControllerUITask uiTask(&M5.Lcd, TITLE, VERSION, UIFader::Origin::CENTER);
bool isBtnALongPressed = false;

void setup(void) {
    myCobot.setup();
    myCobot.powerOn();
    hub.begin();
    uiTask.begin(UI_CORE);
}

void loop(void) {
    M5.update();
    PbHub::Channels ch;
    switch (uiTask.getState()) {
        case State::STOP:
            if (M5.BtnA.pressedFor(LONG_PRESS_THRETHOLD_MSEC_FOR_CLEAR)) {
                isBtnALongPressed = true;
                uiTask.clearCalibrations();
            }
            if (M5.BtnA.wasReleased()) {
                if (isBtnALongPressed) {
                    isBtnALongPressed = false;
                } else {
                    uiTask.setState(State::CALIBRATION_MIN);
                }
                delay(100);
            }
            if (M5.BtnB.wasReleased()) {
                uiTask.setState(State::START);
            }
            if (M5.BtnC.wasReleased()) {
                myCobot.setFreeMove();
            }
            break;
        case State::START:
            if (M5.BtnB.wasReleased()) {
                uiTask.setState(State::STOP);
            }
            break;
        case State::CALIBRATION_MIN:
            if (M5.BtnA.wasReleased()) {
                for (uint8_t i = 0; i < PbHub::MAX_CHANNELS; ++i) {
                    ch = static_cast<PbHub::Channels>(i);
                    uiTask.setAnalogMinValue(ch, hub.analogRead(ch));
                }
                uiTask.setState(State::CALIBRATION_MIDDLE);
            }
            break;
        case State::CALIBRATION_MIDDLE:
            if (M5.BtnA.wasReleased()) {
                for (uint8_t i = 0; i < PbHub::MAX_CHANNELS; ++i) {
                    ch = static_cast<PbHub::Channels>(i);
                    uiTask.setAnalogMiddleValue(ch, hub.analogRead(ch));
                }
                uiTask.setState(State::CALIBRATION_MAX);
            }
            break;
        case State::CALIBRATION_MAX:
            if (M5.BtnA.wasReleased()) {
                for (uint8_t i = 0; i < PbHub::MAX_CHANNELS; ++i) {
                    ch = static_cast<PbHub::Channels>(i);
                    uiTask.setAnalogMaxValue(ch, hub.analogRead(ch));
                }
                uiTask.saveCalibrations();
                uiTask.setState(State::STOP);
            }
            break;
    }

    for (uint8_t i = 0; i < PbHub::MAX_CHANNELS; ++i) {
        ch = static_cast<PbHub::Channels>(i);
        uiTask.setAnalogValue(ch, hub.analogRead(ch));
        if (uiTask.getState() == State::START) {
            myCobot.WriteAngle(i + 1, uiTask.getAngle(ch), uiTask.getSpeed(ch));
        }
    }
    delay(100);
}