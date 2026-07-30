
#include <Arduino.h>

#include "SMU.hpp"

#include "Config.hpp"

SMU::SMU(FastAccelStepperEngine& stepper_engine)
    : thermal_printer(config::head::rx_pin, config::head::tx_pin, config::head::band_width_dots, config::head::band_length_mm * config::head::density_dot_mm)
{
    // Initialize thermal printer
    if (thermal_printer.write(
        ControlParameters {
            .max_heating_dots=config::head::dots_bloc,
            .heating_time_us=config::head::firing_duration_us, 
            .heating_interval_us=config::head::firing_delay_us }) 
            != ErrCode::ok) {
        state = States::error;
    }

    // Register steppers & initialize steppers
    rail_stepper = stepper_engine.stepperConnectToPin(config::rail::stepper_step_pin);
    if (!rail_stepper) {
        state = States::error;
        error = ErrCode::motor_initialization_error;
        return;
    }
    rail_stepper->setDirectionPin(config::rail::stepper_dir_pin);
    rail_stepper->setAutoEnable(false); // No rail enable pin

    roll_stepper = stepper_engine.stepperConnectToPin(config::roll::stepper_step_pin);
    if (!roll_stepper) {
        state = States::error;
        error = ErrCode::motor_initialization_error;
        return;
    }
    roll_stepper->setDirectionPin(config::roll::stepper_dir_pin);
    roll_stepper->setAutoEnable(false); // No roll enable pin

    // Set steppers parameters
    float mm_per_step = config::rail::pulley_diam_mm * PI / static_cast<float>(config::rail::microstep*config::rail::steps_per_rotation);
    float mm_per_row = 1.0 / static_cast<float>(config::head::density_dot_mm);
    float steps_per_row = mm_per_row / mm_per_step;

    rail_steps_velocity = steps_per_row * 1e6 / thermal_printer.get_row_printing_time_us();
    
    rail_stepper->setSpeedInHz(rail_steps_velocity);
}

ErrCode SMU::handle_controller_input(uint8_t* bytes, uint16_t len)
{
    return ErrCode::ok;
}