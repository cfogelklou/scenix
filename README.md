# Scenix Semiconductor / Ubiciom

Scenix Semiconductor was founded in 1996 and subsequently renamed Ubicom before being bought by Qualcomm (so, it survived the .com crash.)

The founder and former CEO of Scenix Semiconductor was tragically murdered on a trip to China not long after a new CEO was named to grow the company from startup stage to enterprise.

## Archived Virtual Peripherals and Datasheets

Very little information is available today about the company, so this is my contribution: An archive of Virtual Peripherals which have been collecting dust.

## What was a Virtual Peripheral?

The Scenix/Ubicom processors were fast (for the time) RISC processors with 100% deterministic interrupt latencies and execution times. This determinism meant that actions such as pin toggles/pin samples could be exactly timed to the clock cycle - enabling many "virtual peripherals" to run in a periodic, clock-driven Interrupt Service Routine (ISR).  Motor Control, UARTs, ADCs, DACs, I2S, SPI, etc could be run "in parallel" by VP state machines running in the processor.  Typically, the ISR was run at a multiple of a standard baud rate, allowing for PC communications via terminal while also driving "period independent" peripherals such as I2C, SPI, ADC, etc.

## What could you do with Virtual Peripherals?

### Twin-Turntable MP3 Player + Mixer

My [Linked-In profile](https://se.linkedin.com/in/chris-fogelklou-a174139b) refers to a Twin-Turntable MP3 mixer project. The code for the motor control, LED drivers, Opto-Electronics, and PC communications were developed by me in a single overnight coding session using a Scenix SX28 - a task which would be nearly impossible on a "typical" uController as just looking up the datasheets, register addresses, etc for each SoC peripheral would take hours if not days.

### DTMF Robot on an SX-28

We also demonstrated a DTMF-Detecting robot at a CES show.  The tank-treaded robot performed PWM motor control and DTMF detection simultaneously, and you could call it up and control it from your mobile phone using the touch-tone dials on your phone. This is especially impressive when considering the Scenix Semiconductor had NO A/D or D/A converters, and the A/D conversion was done completely via delta-sigma ADC using one digital input and one digital output of the microcontroller, and a few external resistors and capacitors.

### V.23 Modem on an SX-28

Another example was a V.23 modem. Yes, V.23 is an ancient technology, but the A/D and D/A for the modem was 100% bit-banged in VP's of an SX-28. The target customer was, for example, vending machine companies who wanted a cheap way for their vending machines to dial a central server and let the server know that they were low on Cheetos.

### Many more examples are available in the [application_notes](application_notes) subdirectory

The repository folder contains source code and pdf files, and the application_notes directory contains PDFs previously published by Scenix/Ubicom.
