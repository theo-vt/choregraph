// File automaticaly generated, any edit will be overwritten on the next build

#ifndef COMMCODES_HPP_
#define COMMCODES_HPP_

#include <stdint.h>

enum class OpCode : uint8_t {
  status_firmware_version=0,
  stop=1,
  enable=2,
  roll_advance_mm=3,
  send_band=4,
  last=5,
};
constexpr int opcode_lengths[6] = {
  0,
  0,
  0,
  4,
  4,
  0,
};


enum class ErrCode : uint8_t {
  firmware_version=0,
  ok=1,
  unknown_error=2,
  motor_done=3,
  command_not_handled=4,
  index_error=5,
  empty_buffer=6,
  motor_initialization_error=7,
  homing_error=8,
  last=9,
};

enum class States : uint8_t {
  error=0,
  iddle=1,
  stencil_advance=2,
  receiving_band_data=3,
  printing_band=4,
  home_rail=5,
  last=6,
};

#endif