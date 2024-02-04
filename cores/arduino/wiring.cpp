/*
  wiring.c - Partial implementation of the Wiring API for the ATmega8.
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2005-2006 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
*/

#include "wiring_private.h"

#include <mcu_interface.h>

inline uint16_t clockCyclesPerMicrosecond(){
  return MCUI::time::clockCyclesPerMicrosecond();
}

inline unsigned long clockCyclesToMicroseconds(unsigned long cycles){
  return MCUI::time::clockCyclesToMicroseconds(cycles);
}

inline unsigned long microsecondsToClockCycles(unsigned long microseconds){
  return MCUI::time::microsecondsToClockCycles(microseconds);
}

unsigned long millis() {
  return MCUI::time::millis();
}

unsigned long micros() {
  return MCUI::time::microseconds();
}

void delay(unsigned long ms) {
  MCUI::time::delay(ms);
}

void delayMicroseconds(unsigned int us) {
  MCUI::time::delay_microseconds(us);
}

void init() {
  MCUI::time::init();
}

void setup_timers(void)  __attribute__((weak));
