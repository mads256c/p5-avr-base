#include "avr-core/Pins.hpp"
#include "avr-core/Serial.hpp"

#include <util/delay.h>

int main()
{
  Pins::PinMode(0, true);
  Pins::PinMode(1, true);

  Serial::Begin(9600);

  for (uint8_t i = 0; i < 0xFF; i++)
  {
    Serial::TransmitUint8(i, 16);
    Serial::TransmitString("\r\n");
  }

  Serial::TransmitUint8(255, 16);
    Serial::TransmitString("\r\n");

  while (true)
  {
  }

  return 0;
}