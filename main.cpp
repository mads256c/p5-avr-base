#include "avr-core/Pins.hpp"
#include "avr-core/Serial.hpp"
#include "avr-core/Util.hpp"
#include "avr-core/Servo.hpp"

#include <util/delay.h>
#include <avr/power.h>


int main()
{
  Pins::PinMode(0, true);
  Pins::PinMode(1, true);

  Serial::Begin(115200);

  Pins::PinMode(9, true);
  Pins::PinMode(10, true);

  Servo::Begin();

  const uint8_t c = 1;

  uint16_t i = Servo::OCR1A_MAX;
  bool down = true;
	
  while(true)
	{
    if (i <= Servo::OCR1A_MIN) down = false;
    if (i >= Servo::OCR1A_MAX) down = true;


		if (down)
    {
      i -= c;
    }

    else
    {
      i += c;
    }

    Servo::SetPosition(i);

    _delay_ms(1);
	}

  return 0;
}