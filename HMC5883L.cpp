#include "HMC5883L.h"

HMC5883L::HMC5883L(I2C &i2c) : _i2c(i2c) {
}

bool HMC5883L::writeReg(char reg, char value) {
    char data[2] = { reg, value };
    return (_i2c.write(ADDRESS, data, 2) == 0);
}

bool HMC5883L::readRegs(char reg, char *buffer, int len) {
    if (_i2c.write(ADDRESS, &reg, 1, true) != 0)
        return false;
    return (_i2c.read(ADDRESS, buffer, len, false) == 0);
}

bool HMC5883L::init() {
    // Config A: 8 samples, 15 Hz
    if (!writeReg(0x00, 0x70)) return false;
    // Config B: gain = 1.3 Ga
    if (!writeReg(0x01, 0x20)) return false;
    // Mode: continuous
    if (!writeReg(0x02, 0x00)) return false;

    return true;
}

bool HMC5883L::readRaw(int16_t out[3]) {
    char data[6];

    if (!readRegs(0x03, data, 6))
        return false;

    // Sensor outputs X Z Y
    out[0] = (data[0] << 8) | data[1];
    out[2] = (data[4] << 8) | data[5];
    out[1] = (data[2] << 8) | data[3];

    return true;
}

float HMC5883L::headingXY() {
    int16_t raw[3];
    if (!readRaw(raw)) return 0.0f;

    float heading = atan2f((float)raw[2], (float)raw[0]);
    if (heading < 0) heading += 2 * 3.1415;

    return heading;
}
