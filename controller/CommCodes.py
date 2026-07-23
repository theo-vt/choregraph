from enum import IntEnum

class OpCode (IntEnum):
  status_firmware_version = 0

  stop = 1
  enable = 2  # when a stop command has been issued an enable command must be issued to allow for other commands to be executed

  roll_advance_mm = 3
  
  rail_start_draw = 4
  rail_dots = 5

class ErrCode (IntEnum):
  firmware_version = 0
  ok = 1
  motor_done = 2
  command_not_handled = 3
  index_error = 4
  empty_buffer = 5
  unknown_error = 6

class States (IntEnum):
  error = 0
  iddle = 1
  stencil_advance = 2
  receiving_band_data = 3
  printing_band = 4
