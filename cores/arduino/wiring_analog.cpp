/*
  wiring_analog.c - analog input and output
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

#include "wiring_private.h"

#include <mcu_interface.h>

void analogReference(pin_size_t mode) {

}

int analogRead(pin_size_t pin) {
  if (!MCUI::pin_is_valid(pin) || !MCUI::pin_has_adc(pin)) return 0;

  if (!MCUI::pin_adc_enabled(pin)) {
    MCUI::pin_enable_adc(pin);
    MCUI::adc_hardware.select(MCUI::pin_get_adc_channel(pin));
    while(!MCUI::adc_hardware.done(MCUI::pin_get_adc_channel(pin)));
  }

  int8_t bs = 16 - analogReadResolution();
  uint32_t reading = MCUI::ADC<2,5>::read(pin);
  return bs > 0 ? reading >> bs : reading << abs(bs);
  return 0;
}

void analogWrite(pin_size_t pin, int pwm_value) {
  if (!MCUI::pin_is_valid(pin)) return;

  MCUI::util::limit(pwm_value, 0, 255);
  if (MCUI::pwm_attach_pin(pin)) {
    MCUI::pwm_write_ratio(pin, (uint8_t)pwm_value);  // map 1-254 onto PWM range
  } else {
    digitalWrite(pin, pwm_value);  // treat as a digital pin if out of channels
  }
}

uint8_t analog_read_resolution = 10;
void analogReadResolution(uint8_t resolution) {
  analog_read_resolution = resolution > 32 ? 32 : resolution;
}

uint8_t analogReadResolution() {
  return analog_read_resolution;
}
