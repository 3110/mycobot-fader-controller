#include "mycobot/MyCobotDefinition.h"

const MyCobotJoint MyCobotJoint::J1(MyCobotJoint::Number::J1, "J1", -165, 165);
const MyCobotJoint MyCobotJoint::J2(MyCobotJoint::Number::J2, "J2", -155, 155);
const MyCobotJoint MyCobotJoint::J3(MyCobotJoint::Number::J3, "J3", -165, 165);
const MyCobotJoint MyCobotJoint::J4(MyCobotJoint::Number::J4, "J4", -165, 165);
const MyCobotJoint MyCobotJoint::J5(MyCobotJoint::Number::J5, "J5", -165, 165);
const MyCobotJoint MyCobotJoint::J6(MyCobotJoint::Number::J6, "J6", -175, 175);
const MyCobotJoint MyCobotJoint::UNKNOWN(MyCobotJoint::Number::UNKNOWN, "??",
                                         -1, -1);

MyCobotJoint::MyCobotJoint(MyCobotJoint::Number number, const char* name,
                           int16_t min, int16_t max)
    : number(number), name{0}, min(min), max(max) {
    snprintf(this->name, sizeof(this->name), "%s", name);
}

MyCobotJoint::~MyCobotJoint(void) {
}

const MyCobotJoint MyCobotJoint::get(Number number) {
    switch (number) {
        case Number::J1:
            return J1;
        case Number::J2:
            return J2;
        case Number::J3:
            return J3;
        case Number::J4:
            return J4;
        case Number::J5:
            return J5;
        case Number::J6:
            return J6;
        default:
            return UNKNOWN;
    }
}

const char* MyCobotJoint::getName(void) const {
    return this->name;
}
