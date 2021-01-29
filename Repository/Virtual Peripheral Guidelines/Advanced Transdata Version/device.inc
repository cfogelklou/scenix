;-------------------------------------------------------------------------------------------------------------------------------
;Pre-Defined Symbols
;-------------------------------------------------------------------------------------------------------------------------------
;
;******** DEVICE Directive Symbols
;
;	- used to establish device parameters
;	- multiple DEVICE statements allowed to accomodate parameters
;
;    Example:	DEVICE	DRT960MS, OSCHS3, BOR42
;		DEVICE	CARRYX, PROTECT
;
;DEVICE DRT18MS			; Device reset timer waits 18ms			(default: DRT18MS)
;DEVICE DRT960MS		; Device reset timer waits 960ms
;DEVICE DRT60MS			; Device reset timer waits 60ms
;DEVICE DRT60US			; Device reset timer waits 60us
;
;DEVICE OSCHS3			; External crystal/resonator - high-speed level 3	(default: OSCHS3)
;DEVICE OSCHS2			; External crystal/resonator - high-speed level 2
;DEVICE OSCHS1			; External crystal/resonator - high-speed level 1
;DEVICE OSCXT2			; External crystal/resonator - standard level 2
;DEVICE OSCXT1			; External crystal/resonator - standard level 1
;DEVICE OSCLP2			; External crystal/resonator - low-power level 2
;DEVICE OSCLP1			; External crystal/resonator - low-power level 1
;DEVICE OSCRC			; External RC network
;DEVICE OSC4MHZ			; Internal 4MHz oscillator
;DEVICE OSC1MHZ			; Internal 1MHz oscillator
;DEVICE OSC128KHZ		; Internal 128KHz oscillator
;DEVICE OSC32KHZ		; Internal 32KHz oscillator

;DEVICE DRIVEOFF		; OSC2 output drive off (use for clock/osc packs)	(default: on)
;DEVICE FEEDBACKOFF		; OSC feedback resistor off (for clock/osc packs)	(default: on)
;DEVICE XTLBUFD			; Same as DRIVEOFF
;DEVICE IFBD			; Same as FEEDBACKOFF

;DEVICE BOR42			; Brownout reset at VDD < 4.2V			(default: Brownout off)
;DEVICE BOR26			; Brownout reset at VDD < 2.6V
;DEVICE BOR22			; Brownout reset at VDD < 2.2V

;DEVICE CARRYX			; ADD/SUB uses Carry flag				(default: ADD/SUB ignores Carry flag)
;DEVICE SYNC			; Input Syncing enabled - 2-clock delay on inputs	(default: Input Syncing disabled)
;DEVICE SLEEPCLOCK		; Clock is enabled during sleep - fast wakeup	(default: Clock is disabled during sleep)
;DEVICE WATCHDOG		; Watchdog Timer enabled				(default: Watchdog Timer disabled)
;DEVICE PROTECT			; Code Protect enabled				(default: Code Protect disabled)
