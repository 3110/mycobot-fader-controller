#include "UI/FaderControllerUITask.h"

const char FaderControllerUITask::PREF_NAMESPACE[MAX_PREF_NAMESPACE_LEN + 1] =
    "FaderController";

static const char BUTTON_SET[] = "Set";
static const char BUTTON_START[] = "Start";
static const char BUTTON_STOP[] = "Stop";
static const char BUTTON_MIN[] = "Min";
static const char BUTTON_MID[] = "Mid";
static const char BUTTON_MAX[] = "Max";
static const char BUTTON_FREE[] = "Free";
static const char BUTTON_EMPTY[] = "";

FaderControllerUITask::FaderControllerUITask(TFT_eSPI *tft, const char *name,
                                             const char *version,
                                             UIFader::Origin origin)
    : UITask(tft, name, version), state(State::STOP), faders{0}, prefs() {
    MyCobotJoint::Number n;
    PbHub::Channels ch;
    for (int i = 0; i < PbHub::MAX_CHANNELS; ++i) {
        ch = static_cast<PbHub::Channels>(i);
        faders[i] = new UIFader(ch, origin);

        n = static_cast<MyCobotJoint::Number>(i);
        faders[i]->setMinValue(MyCobotJoint::get(n).getMin());
        faders[i]->setMaxValue(MyCobotJoint::get(n).getMax());
    }
}

FaderControllerUITask::~FaderControllerUITask(void) {
    for (int i = 0; i < PbHub::MAX_CHANNELS; ++i) {
        delete faders[i];
        faders[i] = nullptr;
    }
}

void FaderControllerUITask::begin(BaseType_t core) {
    UITask::begin(core);
    MyCobotJoint::Number n;
    for (int i = 0; i < PbHub::MAX_CHANNELS; ++i) {
        n = static_cast<MyCobotJoint::Number>(i);
        faders[i]->setLabel(MyCobotJoint::get(n).getName());
    }
    if (loadCalibrations() == false) {
        this->state = State::CALIBRATION_MIN;
    }
    setState(this->state);
}

void FaderControllerUITask::update(void) {
    UITask::update();
    for (int i = 0; i < PbHub::MAX_CHANNELS; ++i) {
        faders[i]->draw(this->sprite);
    }
}

State FaderControllerUITask::getState(void) const {
    return this->state;
}

void FaderControllerUITask::setState(State state) {
    this->state = state;
    switch (this->state) {
        case State::START:
            setButtonA(BUTTON_EMPTY);
            setButtonB(BUTTON_STOP);
            setButtonC(BUTTON_EMPTY);
            break;
        case State::STOP:
            setButtonA(BUTTON_SET);
            setButtonB(BUTTON_START);
            setButtonC(BUTTON_FREE);
            break;
        case State::CALIBRATION_MIN:
            setButtonA(BUTTON_MIN);
            setButtonB(BUTTON_EMPTY);
            setButtonC(BUTTON_EMPTY);
            break;
        case State::CALIBRATION_MIDDLE:
            setButtonA(BUTTON_MID);
            setButtonB(BUTTON_EMPTY);
            setButtonC(BUTTON_EMPTY);
            break;
        case State::CALIBRATION_MAX:
            setButtonA(BUTTON_MAX);
            setButtonB(BUTTON_EMPTY);
            setButtonC(BUTTON_EMPTY);
            break;
    }
}

bool FaderControllerUITask::saveCalibrations(void) {
    bool result = this->prefs.begin(PREF_NAMESPACE, false);
    if (result == false) {
        return result;
    }
    for (int i = 0; i < PbHub::MAX_CHANNELS; ++i) {
        if (faders[i]->saveRange(this->prefs) == false) {
            result = false;
        }
    }
    this->prefs.end();
    return result;
}

bool FaderControllerUITask::loadCalibrations(void) {
    bool result = this->prefs.begin(PREF_NAMESPACE, false);
    if (result == false) {
        return result;
    }
    for (int i = 0; i < PbHub::MAX_CHANNELS; ++i) {
        if (faders[i]->loadRange(this->prefs) == false) {
            result = false;
        }
    }
    this->prefs.end();
    return result;
}

bool FaderControllerUITask::clearCalibrations(void) {
    bool result = this->prefs.begin(PREF_NAMESPACE, false);
    if (result == false) {
        return result;
    }
    for (int i = 0; i < PbHub::MAX_CHANNELS; ++i) {
        if (faders[i]->clearRange(this->prefs) == false) {
            result = false;
        }
    }
    this->prefs.end();
    return result;
}

uint8_t FaderControllerUITask::getSpeed(PbHub::Channels ch) const {
    return 30;  // TODO:
}

int16_t FaderControllerUITask::getAngle(PbHub::Channels ch) const {
    return faders[static_cast<size_t>(ch)]->getValue();
}

FaderControllerUITask *FaderControllerUITask::setAnalogValue(PbHub::Channels ch,
                                                             int32_t value) {
    faders[static_cast<size_t>(ch)]->setAnalogValue(value);
    return this;
}

FaderControllerUITask *FaderControllerUITask::setAnalogMinValue(
    PbHub::Channels ch, int32_t value) {
    faders[static_cast<size_t>(ch)]->setAnalogMinValue(value);
    return this;
}

FaderControllerUITask *FaderControllerUITask::setAnalogMiddleValue(
    PbHub::Channels ch, int32_t value) {
    faders[static_cast<size_t>(ch)]->setAnalogMiddleValue(value);
    return this;
}

FaderControllerUITask *FaderControllerUITask::setAnalogMaxValue(
    PbHub::Channels ch, int32_t value) {
    faders[static_cast<size_t>(ch)]->setAnalogMaxValue(value);
    return this;
}
