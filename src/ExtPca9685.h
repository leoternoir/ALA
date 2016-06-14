#ifndef PCA9685_H
#define PCA9685_H

#include "Arduino.h"
#include "Wire.h"

#define PCA9685_ADDR 0x42
/* Register Addresses */
#define PCA9685_MODE1 0x00
#define PCA9685_MODE2 0x01
#define PCA9685_LED0_ON_L 0x06
#define PCA9685_ALL_LED_ON_L 0xFA

/* Configuration values */
#define PCA9685_MAX_LEDS 12
#define PCA9685_MODE1_CONFIG 0xA0
#define PCA9685_MODE2_CONFIG 0x10

#define AT42QT2120_ADDR 0x1C
#define GPIO_PIN 2

class Pca9685
{
  public:
    void init();
    // uint8_t initChip();

    void setLedOff(uint8_t ledNum);
    void setLedOn(uint8_t ledNum);
    void setLedAmount(uint8_t ledNum, int16_t amount);

  private:
    uint8_t readData(uint8_t add, uint8_t reg, uint8_t* data);
    uint8_t writeData(uint8_t add, uint8_t reg, uint8_t data);
};

extern Pca9685 Pca;

#endif

