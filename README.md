# HMC5883L – Mbed Magnetometer Driver

A simple, clean, and minimal driver for the HMC5883L (GY-273) 3-axis magnetometer.

## Features
- Initialize the sensor (config registers A, B, Mode)
- Read raw X, Y, Z values
- Compute heading in XY plane
- Simple blocking I2C implementation (no threads, no callbacks)

## Usage

```cpp
#include "mbed.h"
#include "HMC5883L.h"

DigitalOut myled(LED1);
Serial pc(USBTX, USBRX); // tx, rx
I2C i2c(p9, p10);   // Adjust for your board

int16_t m[3];

int main() {
    pc.baud(9600);

    pc.printf("Starting HMC5883L...\r\n");
    HMC5883L compass(i2c);
    if (!compass.init()) {
        pc.printf("Init failed!\r\n");
        return 0;
    }

  while(1) {

      if (compass.readRaw(m)) {
            pc.printf("X=%d  Y=%d  Z=%d  Heading=%.2f deg\r\n",
                m[0], m[2], m[1],
                compass.headingXY() * 180.0 / 3.14159
            );
        }
    myled = !myled;
    wait(0.2);
  }
}
