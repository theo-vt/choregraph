
#include <Arduino.h>

#include "SMU.hpp"

#include "Config.hpp"

SMU::SMU()
    : thermalPrinter(config::head::rx_pin, config::head::tx_pin, config::head::band_width_dots, config::head::band_length_mm * config::head::density_dot_mm)
{
    if (thermalPrinter.write(
        ControlParameters {
            .max_heating_dots=config::head::dots_bloc,
            .heating_time_us=config::head::firing_duration_us, 
            .heating_interval_us=config::head::firing_delay_us }) 
            != ErrCode::ok) {
        state = States::error;
    }

    float mm_per_step = config::rail::pulley_diam_mm * PI / static_cast<float>(config::rail::microstep*config::rail::steps_per_rotation);
    float mm_per_row = 1.0 / static_cast<float>(config::head::density_dot_mm);
    float steps_per_row = mm_per_row / mm_per_step;

    rail_steps_velocity = steps_per_row * 1e6 / thermalPrinter.get_row_printing_time_us();
}

ErrCode SMU::handle_controller_input(uint8_t* bytes, uint16_t len)
{

}