/* Tone.cpp

  A Tone Generator Library

  Written by Brett Hagman

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

#include <mcu_interface.h>
#include "Arduino.h"

#warning Timer 2 is also used for the SoftwareSerial Library
constexpr MCUI::IRQNumber tone_timer_interrupt_number = MCUI::IRQNumber::TIMER2;
auto& tone_timer = MCUI::timer2;

pin_size_t tone_pin = P_NC;
volatile int32_t toggles = 0;
bool initialised_tone_timer = false;

void tone(pin_size_t _pin, unsigned int frequency, unsigned long duration) {
  if ((tone_pin != (pin_size_t)P_NC && tone_pin != _pin) || _pin == (pin_size_t)P_NC || frequency == 0) return;
  MCUCore::nvic_disable_irq(tone_timer_interrupt_number);
  tone_pin = _pin;
  toggles = duration ? 2 * frequency * duration / 1000 : -1;

  if (!initialised_tone_timer) {
    MCUI::register_isr(tone_timer_interrupt_number, [](){
      const uint32_t interrupts = tone_timer.IR;
      tone_timer.IR = interrupts;  // clear all interrupts
      if (toggles != 0) {
        if(toggles > 0) toggles--;
        MCUI::gpio_toggle(tone_pin);
      } else noTone(tone_pin);
    });

    MCUI::util::bit_set(MCUI::system_control.PCONP, 22);     // Power ON Timer 2
    tone_timer.TCR = MCUI::util::bit_value(1);               // Put Timer in reset state
    tone_timer.PR = ((PeripheralClock) / 1000000) - 1;       // Use prescaler to set frequency
    tone_timer.MCR = MCUI::util::bitset_value(0, 1);         // Match on MR0, reset on MR0, interrupts when NVIC enables them
    MCUCore::nvic_set_priority(tone_timer_interrupt_number, MCUCore::nvic_encode_priority(0, 2, 0));
    initialised_tone_timer = true;
  }

  tone_timer.TCR = MCUI::util::bit_value(1);                 // Put Timer in reset state
  tone_timer.MR0 = (1000000 / (2 * frequency)) - 1;          // Match value (period) to set frequency
  tone_timer.TCR = MCUI::util::bit_value(0);                 // Counter Enable

  MCUI::pin_enable_function(_pin, MCUI::Function::GPIO);
  MCUI::gpio_set_output(_pin);
  MCUI::gpio_clear(_pin);

  MCUCore::nvic_enable_irq(tone_timer_interrupt_number);
}

void noTone(pin_size_t _pin) {
  tone_timer.TCR = MCUI::util::bit_value(1);           // Put Timer in reset state
  MCUCore::nvic_disable_irq(tone_timer_interrupt_number);
   MCUI::gpio_clear(_pin);
  tone_pin = P_NC;
}
