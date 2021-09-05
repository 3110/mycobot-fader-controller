#ifndef MYCOBOT_DEFINITION_
#define MYCOBOT_DEFINITION_

#include <ParameterList.h>

typedef struct {
    int16_t min;
    int16_t max;
} JointRange;

class MyCobotJoint {
public:
    enum class Number {
        J1 = 0,
        J2,
        J3,
        J4,
        J5,
        J6,
        UNKNOWN,
    };

    static const size_t MAX_NAME_LEN = 2;
    static const MyCobotJoint get(Number number);

    static const MyCobotJoint J1;
    static const MyCobotJoint J2;
    static const MyCobotJoint J3;
    static const MyCobotJoint J4;
    static const MyCobotJoint J5;
    static const MyCobotJoint J6;
    static const MyCobotJoint UNKNOWN;

    ~MyCobotJoint(void);

    const char* getName(void) const;

    inline int16_t getMin(void) const {
        return this->min;
    }

    inline int16_t getMax(void) const {
        return this->max;
    }

protected:
    MyCobotJoint(Number number, const char* name, int16_t min, int16_t max);

public:
    Number number;
    char name[MAX_NAME_LEN + 1];
    int16_t min;
    int16_t max;
};

#endif