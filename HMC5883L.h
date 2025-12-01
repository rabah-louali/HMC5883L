#ifndef HMC5883L_H
#define HMC5883L_H

#include "mbed.h"

class HMC5883L {
public:
    HMC5883L(I2C &i2c);

    bool init();
    bool readRaw(int16_t out[3]);
    float headingXY();

private:
    I2C &_i2c;

    static const int ADDRESS = 0x1E << 1;   // HMC5883L 7-bit address
    bool writeReg(char reg, char value);
    bool readRegs(char reg, char *buffer, int len);
};

#endif
