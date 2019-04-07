#include "avr-core/Pins.hpp"
#include "avr-core/Serial.hpp"
#include "avr-core/Util.hpp"

#include <util/delay.h>
#include <avr/power.h>

int main()
{
  Pins::PinMode(0, true);
  Pins::PinMode(1, true);

  Serial::Begin(115200);

  Serial::TransmitInt<int8_t>(-128);

  while (true)
  {
  }

  return 0;
}