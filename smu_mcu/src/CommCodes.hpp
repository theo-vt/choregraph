// File automaticaly generated, any edit will be overwritten on the next build

#ifndef BOP_COMMCODES_HPP
#define BOP_COMMCODES_HPP

#include <stdint.h>

enum class OpCode : uint8_t {
  status_firmware_version=0,
  stop=1,
  enable=2,
  roll_advance_mm=3,
  rail_start_draw=4,
  rail_dots=5,
};

enum class ErrCode : uint8_t {
  firmware_version=0,
  ok=1,
  motor_done=2,
  command_not_handled=3,
  index_error=4,
  empty_buffer=5,
  unknown_error=6,
};

enum class States : uint8_t {
  error=0,
  iddle=1,
  stencil_advance=2,
  receiving_band_data=3,
  printing_band=4,
};

#endif