/*
 * Arduino SoftwareSerial API implementation for LPC176x by gloomyandy
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef SOFTWARESERIAL_H
#define SOFTWARESERIAL_H

#include <Arduino.h>
#include <stdint.h>
#include <Stream.h>
#include <Print.h>

/******************************************************************************
* Definitions
******************************************************************************/

#define _SS_MAX_RX_BUFF 64 // RX buffer size

class SoftwareSerial : public Stream
{
private:
  // per object data
  pin_t _receivePin;
  pin_t _transmitPin;
  uint32_t _speed;

  uint16_t _buffer_overflow:1;
  uint16_t _inverse_logic:1;
  uint16_t _half_duplex:1;
  uint16_t _output_pending:1;

  unsigned char _receive_buffer[_SS_MAX_RX_BUFF];
  volatile uint8_t _receive_buffer_tail;
  volatile uint8_t _receive_buffer_head;

  uint32_t delta_start;

  // static data
  static bool initialised;
  static SoftwareSerial * active_listener;
  static SoftwareSerial * volatile active_out;
  static SoftwareSerial * volatile active_in;
  static int32_t tx_tick_cnt;
  static int32_t rx_tick_cnt;
  static uint32_t tx_buffer;
  static int32_t tx_bit_cnt;
  static uint32_t rx_buffer;
  static int32_t rx_bit_cnt;
  static uint32_t cur_speed;

  // private methods
  void send();
  void recv();
  void setTX();
  void setRX();
  void setSpeed(uint32_t speed);
  void setRXTX(bool input);

public:
  // public methods

  SoftwareSerial(pin_t receivePin, pin_t transmitPin, bool inverse_logic = false);
  ~SoftwareSerial();
  void begin(long speed);
  bool listen();
  void end();
  bool isListening() { return active_listener == this; }
  bool stopListening();
  bool overflow() { bool ret = _buffer_overflow; if (ret) _buffer_overflow = false; return ret; }

  virtual int peek() override;
  virtual size_t write(uint8_t byte) override;
  virtual int read() override;
  virtual int available() override;
  virtual void flush() override;

  operator bool() { return true; }

  using Print::write;

};

#endif // SOFTWARESERIAL_H
