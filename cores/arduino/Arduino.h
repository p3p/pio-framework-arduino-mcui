/*
  Arduino.h - Main include file for the Arduino SDK
  Copyright (c) 2005-2013 Arduino Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef Arduino_h
#define Arduino_h

#include "api/ArduinoAPI.h"

#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#ifdef __cplusplus
extern "C"{
#endif

#define VCC_3V3 1

#define interrupts() MCUCore::nvic_interrupts_enable()
#define noInterrupts() MCUCore::nvic_interrupts_disable()

#ifndef _NOP
#define _NOP() MCUCore::NOP()
#endif

uint16_t clockCyclesPerMicrosecondComp(uint32_t clk);
uint16_t clockCyclesPerMicrosecond();
unsigned long clockCyclesToMicroseconds(unsigned long cycles);
unsigned long microsecondsToClockCycles(unsigned long microseconds);

#define NOT_A_PIN 255
#define NOT_A_PORT 255
#define NOT_AN_INTERRUPT 255
#define NUM_TOTAL_PORTS 6
#define NOT_ON_TIMER 0

void setup_timers();

#define digitalPinToPort(pin) ( (pin < MCUI_PIN_COUNT) ? digital_pin_to_port[pin] : NOT_A_PIN )
#define digitalPinToBitPosition(pin) ( (pin < MCUI_PIN_COUNT) ? digital_pin_to_bit_position[pin] : NOT_A_PIN )
#define digitalPinToBitMask(pin) ( (pin < MCUI_PIN_COUNT) ? digital_pin_to_bit_mask[pin] : NOT_A_PIN )
#define digitalPinToTimer(pin) ( (pin < MCUI_PIN_COUNT) ? digital_pin_to_timer[pin] : NOT_ON_TIMER )
#define analogPinToBitPosition(pin) ( (digitalPinToAnalogInput(pin) != NOT_A_PIN) ? digital_pin_to_bit_position[pin + ANALOG_INPUT_OFFSET] : NOT_A_PIN )
#define analogPinToBitMask(pin) ( (digitalPinToAnalogInput(pin) != NOT_A_PIN) ? digital_pin_to_bit_mask[pin + ANALOG_INPUT_OFFSET] : NOT_A_PIN )

#define portToPortStruct(port) ( (port < MCUI_PORT_COUNT) ? ((PORT_t *)&PORTA + port) : NULL)
#define digitalPinToPortStruct(pin) ( (pin < MCUI_PIN_COUNT) ? ((PORT_t *)&PORTA + digitalPinToPort(pin)) : NULL)
#define getPINnCTRLregister(port, bit_pos) ( ((port != NULL) && (bit_pos < NOT_A_PIN)) ? ((volatile uint8_t *)&(port->PIN0CTRL) + bit_pos) : NULL )
#define digitalPinToInterrupt(P) (P)

#define portOutputRegister(P) ( (volatile uint8_t *)( &portToPortStruct(P)->OUT ) )
#define portInputRegister(P) ( (volatile uint8_t *)( &portToPortStruct(P)->IN ) )
#define portModeRegister(P) ( (volatile uint8_t *)( &portToPortStruct(P)->DIR ) )

// Extended API (DUE etc.)

char *dtostrf(double val, signed char width, unsigned char prec, char *sout);

#ifdef __cplusplus
} // extern "C"

void analogReadResolution(uint8_t resolution);
uint8_t analogReadResolution();

#endif

#ifdef __cplusplus
#include "UART.h"
//#include "USBCore.h"
//#include "CDC.h"
//#include "MSC.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#include "pins_arduino.h"
#ifdef __cplusplus
} // extern "C"
#endif

#endif
