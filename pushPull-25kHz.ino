#include <avr/sleep.h>
#include <avr/power.h>

// this sketch sets the analogue ports to output a push-pull driving signal using an arduino and L298N H-bridge motor driver
// the sketch uses individual clock cycles to generate square waves - 2 are needed (on and off) for each wave period

byte pattern = 0b10101010; // consecutive ports will have an opposite signal for push-pull for push config use 0b11111111

void setup()
{
 DDRC = 0b11111111; // set pins A0 to A7 as outputs (port C is the analogue pins) ----- 
 DDRD = 0b11111100; // set digital pins D2 to D7 as outputs, (port D is the digital pins)
 PORTC = 0b00000000; // output low signal to all A pins 
 PORTD = 0b00001100; // set D2 (ENB) & D3(ENA) high to enable the outputs of the h-bridge - can also use these pins for PWM for software voltage control.
 
  // initialize timer1
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  OCR1A = 319;              // ***** CHANGE THIS ONE TO CHANGE FREQUENCY f_out = [(16 MHZ / 2X FREQUENCY) - 1] as the arduino clock is 16MHz ******
  // 25 kHz = 319 
  // 40 kHz = 199 
  // 57.97 kHz = 137
  // 307.7 kHz = 25
  
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS10);    // 1 prescaler, no prescaling
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  interrupts();             // enable all interrupts

  // disable ADC
  ADCSRA = 0;  
  
  // turn off everything we can
  power_adc_disable();
  power_spi_disable();
  power_twi_disable();
  power_timer0_disable();
  power_usart0_disable();
  while(true); //avoid entering into the loop
}

ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
  PORTC = pattern;      //output portCV into ports 0 to 7
  pattern = ~pattern;   // invert the pattern for the next cycle - this line also uses clock cycles so will stop very fast frequencies
}

void loop(){
// we're not using the arduino loop as its slower and we want to use the low level programming above  
}
