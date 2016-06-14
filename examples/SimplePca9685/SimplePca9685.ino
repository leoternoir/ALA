#include <AlaLed.h>

AlaLed alaLed;

byte pins[] = { 0, 3, 6, 9 };

void setup()
{
  alaLed.initTLC5940(4, pins);
  alaLed.setAnimation(ALA_GLOW, 2000);
}

void loop()
{
  alaLed.runAnimation();
}

