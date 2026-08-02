
#ifndef SMU_HPP_
#define SMU_HPP_

#include "CommCodes.hpp"
#include "ThermalPrinter.h"
#include <FastAccelStepper.h>
#include <FastAccelStepperEngine.h>

#include <CircularBuffer.hpp>

class SMU {
private:
    ThermalPrinter thermal_printer;
    States state {States::iddle};
    ErrCode error {ErrCode::ok};
    uint16_t rail_steps_velocity; // steps/s
    FastAccelStepper* rail_stepper {nullptr};
    FastAccelStepper* roll_stepper {nullptr};
    int steps_per_row {0};

    CircularBuffer buffer;

public:
    SMU(FastAccelStepperEngine& stepper_engine);

    void spin();

    ErrCode handle_controller_input(uint8_t* bytes, uint16_t len);

    void advance_stencil();
    void home_rail();

    void flag_error(ErrCode err);
};

#endif