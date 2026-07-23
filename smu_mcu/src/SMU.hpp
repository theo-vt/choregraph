
#ifndef SMU_HPP_
#define SMU_HPP_

#include "CommCodes.hpp"
#include "ThermalPrinter.h"

class SMU {
private:
    ThermalPrinter thermalPrinter;
    States state;

public:
    SMU();

    ErrCode handle_controller_input(uint8_t* bytes, uint16_t len);
};

#endif