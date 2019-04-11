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
  Pins::PinMode(2, true);
  Pins::PinMode(9, true);

  Pins::DigitalWrite(2, true);
  
  Servo::Begin();


  while(true)
  {
    Servo::SetPosition(Servo::OCR1A_MIN);
    _delay_ms(1000);
    Servo::SetPosition(Servo::OCR1A_MAX);
    _delay_ms(1000);
  }
  return 0;
}