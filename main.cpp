#include "avr-core/Pins.hpp"
#include "avr-core/Serial.hpp"

#include <util/delay.h>

int main()
{
  Pins::PinMode(0, true);
  Pins::PinMode(1, true);

  Serial::Begin(115200);

  for (uint16_t i = 0; i < 0xFFFF; i++)
  {
    Serial::TransmitUint16(i, 10);
    Serial::Transmit('\r');
    Serial::Transmit('\n');
  }

  Serial::TransmitUint16(0xFFFF, 10);
    Serial::TransmitString("\r\n");

  while (true)
  {
  }

  return 0;
}