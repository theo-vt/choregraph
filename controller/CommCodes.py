from enum import IntEnum

class OpCode (IntEnum):
  status_firmware_version = 0

  stop = 1
  enable = 2  # when a stop command has been issued an enable command must be issued to allow for other commands to be executed

  roll_advance_mm = 3

  send_band = 4

class ErrCode (IntEnum):
  firmware_version = 0
  ok = 1
  unknown_error = 2
  motor_done = 3
  command_not_handled = 4
  index_error = 5
  empty_buffer = 6
  motor_initialization_error = 7
  homing_error = 8

class States (IntEnum):
  error = 0
  iddle = 1
  stencil_advance = 2
  receiving_band_data = 3
  printing_band = 4
  home_rail = 5

def message_bytes_for_opcode(opcode: int):
  if opcode == OpCode.roll_advance_mm:
    return 4

  if opcode == OpCode.send_band:
    return 4 # Actually this is dynamic as the band can be a few kbs but the first 4 bytes tell the mcu that number

  return 0