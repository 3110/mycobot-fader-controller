#include "m5stack/PbHub.h"

const uint8_t PbHub::HUB_ADDRS[] = {0x40, 0x50, 0x60, 0x70, 0x80, 0xA0};

PbHub::PbHub(uint8_t inputPin) {
    pinMode(inputPin, INPUT);
}

PbHub::~PbHub(void) {
}

void PbHub::begin(void) {
    Wire.begin();
}

uint16_t PbHub::analogRead(Channels ch) {
    uint8_t low = 0;
    uint8_t high = 0;

    Wire.beginTransmission(I2C_ADDR);
    Wire.write(HUB_ADDRS[static_cast<size_t>(ch)] | 0x06);
    Wire.endTransmission();

    Wire.requestFrom(I2C_ADDR, ANALOG_READ_DATA_LEN);
    while (Wire.available()) {
        low = Wire.read();
        high = Wire.read();
    }
    return (high << 8) | low;
}
