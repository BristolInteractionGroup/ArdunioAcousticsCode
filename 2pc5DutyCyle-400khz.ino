#include <avr/io.h>
#include <util/delay.h>

// sketch which outputs a 2.5% duty cycle squarewave on pin3

int main(void)
{
  pinMode(3, OUTPUT); // output pin for OCR2B, this is Arduino pin number

  // In the next line of code, we:
  // 1. Set the compare output mode to clear OC2A and OC2B on compare match.
  //    To achieve this, we set bits COM2A1 and COM2B1 to high.
  // 2. Set the waveform generation mode to fast PWM (mode 3 in datasheet).
  //    To achieve this, we set bits WGM21 and WGM20 to high.
  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);

  // In the next line of code, we:
  // 1. Set the waveform generation mode to fast PWM mode 7 —reset counter on
  //    OCR2A value instead of the default 255. To achieve this, we set bit
  //    WGM22 to high.
  // 2. Set the prescaler divisor to 1, so that our counter will be fed with
  //    the clock's full frequency (16MHz). To achieve this, we set CS20 to
  //    high (and keep CS21 and CS22 to low by not setting them).
  TCCR2B = _BV(WGM22) | _BV(CS20);

  // OCR2A holds the top value of our counter, so it acts as a divisor to the
  // clock. When our counter reaches this, it resets. Counting starts from 0.
  // Thus 39 equals to 40 divs.
  OCR2A = 39;
  // This is the duty cycle. Think of it as the last value of the counter our
  // output will remain high for. Can't be greater than OCR2A.A
  // value of 0 means a duty cycle of 1/40 = 2.5% in this case. -- NB arduino counts from 0
  OCR2B = 0;
}
