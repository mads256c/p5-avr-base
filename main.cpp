#include "avr-core/Pins.hpp"
#include "avr-core/Serial.hpp"

#include <util/delay.h>

int main()
{
  Pins::PinMode(0, true);
  Pins::PinMode(1, true);

  Serial::Begin(9600);

  while(true)
  {
    const uint8_t c = Serial::Receive();

    Serial::TransmitString("Got: ");
    Serial::Transmit(c);
    Serial::Transmit('\r');
    Serial::Transmit('\n');

    //_delay_ms(1000);
  }

  return 0;
}