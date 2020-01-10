# Ardunio Code to drive transducers
The arduino has 5V logic which can be used to directly power a small ultrasonic transducer with a squarewave. To drive more transducers at high voltages requires either an H-bridge or gate driver. push-pull is based on Marzo tractor beam but changed so voltage positive and negative about 0 V when using an H-bridge.

I've included code to generate the following:
* 25 kHz push pull (successive outputs are out of phase for H-bridge push pull configuration (gives 2*Vcc peak to peak)
* 25 kHz push pull (successive outputs are out of phase for H-bridge push pull configuration (gives 2*Vcc peak to peak)
* 400 kHz squarewave at 2.5% duty cycle - requires a mosfet + gate driver

