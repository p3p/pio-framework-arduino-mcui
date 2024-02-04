#include <stdbool.h>

#include "pins_arduino.h"
#include "api/Common.h"

static volatile bool lib_exists = false;

#define FORCE_INLINE __attribute__((always_inline)) inline

void setup_timers() {
}

FORCE_INLINE bool isDoubleBondedActive(uint8_t pin) {
  (void)pin;
  return false;
}

void initVariant() {
  lib_exists = true;
}
