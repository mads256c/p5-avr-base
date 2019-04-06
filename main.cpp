#include "avr-core/Pins.hpp"
#include "avr-core/Serial.hpp"

#include <util/delay.h>

int main()
{
  Pins::PinMode(0, true);
  Pins::PinMode(1, true);

  Serial::Begin(115200);

  for (int16_t i = -32768; i < 32767; i++)
  {
    Serial::TransmitInt16(i);
    Serial::Transmit('\r');
    Serial::Transmit('\n');

    _delay_ms(1000);
  }

  while (true)
  {
  }

  return 0;
}