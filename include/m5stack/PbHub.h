#ifndef _PBHUB_H_
#define _PBHUB_H_

#include <Wire.h>
class PbHub {
public:
    enum class Channels {
        CH0,
        CH1,
        CH2,
        CH3,
        CH4,
        CH5,
    };
    static const uint8_t MAX_CHANNELS = 6;
    static const uint8_t I2C_ADDR = 0x61;
    static const uint8_t ANALOG_READ_DATA_LEN = 2;

    PbHub(uint8_t inputPin);
    virtual ~PbHub(void);

    virtual void begin(void);
    virtual uint16_t analogRead(Channels ch);

private:
    static const uint8_t HUB_ADDRS[MAX_CHANNELS];
};

#endif