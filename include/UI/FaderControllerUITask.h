#ifndef FADER_UI_TASK_H_
#define FADER_UI_TASK_H_

#include <Preferences.h>

#include "UI/UIFader.h"
#include "m5stack/PbHub.h"
#include "m5stack/UI/UITask.h"
#include "mycobot/MyCobotDefinition.h"

enum class State {
    STOP,
    START,
    CALIBRATION_MIN,
    CALIBRATION_MIDDLE,
    CALIBRATION_MAX,
};

class FaderControllerUITask : public UITask {
public:
    static const size_t MAX_PREF_NAMESPACE_LEN = 15;
    static const char PREF_NAMESPACE[MAX_PREF_NAMESPACE_LEN + 1];

    FaderControllerUITask(TFT_eSPI *tft, const char *name, const char *version,
                          UIFader::Origin origin = UIFader::Origin::LEFT);
    virtual ~FaderControllerUITask(void);

    virtual void begin(BaseType_t core);
    virtual void update(void);

    virtual State getState(void) const;
    virtual void setState(State state);

    virtual bool saveCalibrations(void);
    virtual bool loadCalibrations(void);
    virtual bool clearCalibrations(void);

    virtual uint8_t getSpeed(PbHub::Channels ch) const;
    virtual int16_t getAngle(PbHub::Channels ch) const;

    virtual FaderControllerUITask *setAnalogValue(PbHub::Channels ch,
                                                  int32_t value);
    virtual FaderControllerUITask *setAnalogMinValue(PbHub::Channels ch,
                                                     int32_t value);
    virtual FaderControllerUITask *setAnalogMiddleValue(PbHub::Channels ch,
                                                        int32_t value);
    virtual FaderControllerUITask *setAnalogMaxValue(PbHub::Channels ch,
                                                     int32_t value);

private:
    State state;
    UIFader *faders[PbHub::MAX_CHANNELS];
    Preferences prefs;
    bool isCalibrated;
};

#endif