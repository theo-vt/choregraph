
#ifndef SMU_HPP_
#define SMU_HPP_

#include "CommCodes.hpp"
#include "ThermalPrinter.h"

class SMU {
private:
    ThermalPrinter thermalPrinter;
    States state;
    uint16_t rail_steps_velocity; // steps/s

public:
    SMU();

    ErrCode handle_controller_input(uint8_t* bytes, uint16_t len);
};

#endif