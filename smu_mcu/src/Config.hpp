// File automaticaly generated, any edit will be overwritten on the next build

#ifndef CONFIG_HPP_
#define CONFIG_HPP_

namespace config {

namespace rail {

constexpr float pulley_diam_mm = 10.2;
constexpr int microstep = 1;
constexpr int steps_per_rotation = 200;

} // !rail

namespace head {

constexpr int rx_pin = 8;
constexpr int tx_pin = 9;
constexpr int density_dot_mm = 8;
constexpr int band_width_dots = 384;
constexpr int band_length_mm = 227;
constexpr int dots_bloc = 64;
constexpr int firing_delay_us = 20;
constexpr int firing_duration_us = 10;

} // !head

} // !config 



#endif