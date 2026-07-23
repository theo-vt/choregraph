
#include "SMU.hpp"

#include "Config.hpp"

SMU::SMU()
    : thermalPrinter(rx_pin, tx_pin, band_width_dots, band_length_dots)
{

}

ErrCode SMU::handle_controller_input(uint8_t* bytes, uint16_t len)
{

}