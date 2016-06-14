#include "ExtPca9685.h"

uint8_t Pca9685::readData(uint8_t add, uint8_t reg, uint8_t* data)
{
  Wire.beginTransmission(add);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(add, (uint8_t)1);
  if (Wire.available()==1) {
    *data = Wire.read();
  }
  return 0;
}

uint8_t Pca9685::writeData(uint8_t add, uint8_t reg, uint8_t data)
{
  Wire.beginTransmission(add);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
  return 0;
}

// uint8_t Pca9685::initChip()
// {
//   // Check Chip ID
//   uint8_t data = -1;
//   readData(AT42QT2120_ADDR, 0x00, &data);
//   if (data != 0x3E) {
//     return -1;
//   }
//   writeData(AT42QT2120_ADDR, 0x0E, 0xC0);  // enable wheel mode
//   writeData(AT42QT2120_ADDR, 0x06, 0X01);  // calibrate
//   delay(300); // wait for calibration to be done (approximate)
//   return 0;
// }

void Pca9685::init()
{
  // Wire.begin();

  writeData(PCA9685_ADDR, PCA9685_MODE1, PCA9685_MODE1_CONFIG);
  writeData(PCA9685_ADDR, PCA9685_MODE2, PCA9685_MODE2_CONFIG);
}

/**
 * LED FUNCTIONS
 */

void Pca9685::setLedOff(uint8_t ledNum)
{
  if (11 < ledNum) {
    return;
  }
  uint16_t base_add = 0x06 + 4 * ledNum;
  writeData(PCA9685_ADDR, base_add    , 0x00);
  writeData(PCA9685_ADDR, base_add + 1, 0x00);
  writeData(PCA9685_ADDR, base_add + 2, 0x00);
  writeData(PCA9685_ADDR, base_add + 3, 0x10);
}

void Pca9685::setLedOn(uint8_t ledNum)
{
  if (11 < ledNum) {
    return;
  }
  uint16_t base_add = 0x06 + 4 * ledNum;
  writeData(PCA9685_ADDR, base_add    , 0x00);
  writeData(PCA9685_ADDR, base_add + 1, 0x10);
  writeData(PCA9685_ADDR, base_add + 2, 0x00);
  writeData(PCA9685_ADDR, base_add + 3, 0x00);
}

void Pca9685::setLedAmount(uint8_t ledNum, int16_t amount)
{
  if (4095 < amount || 11 < ledNum) {
    return;
  }
  if (amount <= 0) {
    setLedOff(ledNum);
  } else if (amount >= 4095) {
    setLedOn(ledNum);
  } else {
    uint16_t led_on = 0;
    uint16_t led_off = amount;
    uint8_t b1 = led_on & 0xFF;
    uint8_t b2 = (led_on >> 8) & 0xFF;
    uint8_t b3 = led_off & 0xFF;
    uint8_t b4 = (led_off >> 8) & 0xFF;
    int base_add = 0x06 + 4 * ledNum;
    writeData(PCA9685_ADDR, base_add    , b1);
    writeData(PCA9685_ADDR, base_add + 1, b2);
    writeData(PCA9685_ADDR, base_add + 2, b3);
    writeData(PCA9685_ADDR, base_add + 3, b4);
  }
}

Pca9685 Pca;