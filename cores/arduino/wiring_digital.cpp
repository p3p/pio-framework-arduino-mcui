/*
  wiring_digital.c - digital input and output functions
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

  Modified 28 September 2010 by Mark Sproul
*/

#define ARDUINO_MAIN
#include "wiring_private.h"
#include "pins_arduino.h"

#include "interface/pinmapping.h"

void pinMode(pin_size_t pin, PinMode mode) {
  if (!LPC4078::pin_is_valid(pin)) return;
  LPC4078::pin_enable_function(pin, LPC4078::Function::GPIO);
  if(mode == OUTPUT) {
    LPC4078::gpio_set_output(pin);
    LPC4078::pin_set_mode(pin, LPC4078::PinMode::INACTIVE);
  } else {
    LPC4078::gpio_set_input(pin);
    if(mode == INPUT_PULLUP) LPC4078::pin_set_mode(pin, LPC4078::PinMode::PULLUP);
    else if(mode == INPUT_PULLDOWN) LPC4078::pin_set_mode(pin, LPC4078::PinMode::PULLDOWN);
    else LPC4078::pin_set_mode(pin, LPC4078::PinMode::INACTIVE);
  }
}

void digitalWrite(pin_size_t pin, PinStatus val) {
  if (!LPC4078::pin_is_valid(pin)) return;

  LPC4078::gpio_set(pin, val);
  // Set pin mode on every write (Arduino version does this)
  LPC4078::pin_enable_function(pin, LPC4078::Function::GPIO);
  LPC4078::gpio_set_output(pin);

}

PinStatus digitalRead(pin_size_t pin) {
  if (!LPC4078::pin_is_valid(pin)) return PinStatus::LOW;
  return LPC4078::gpio_get(pin) ? PinStatus::HIGH : PinStatus::LOW;
}
