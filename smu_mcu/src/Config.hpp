
#ifndef CONFIG_HPP_
#define CONFIG_HPP_

// Physical parameters
constexpr int print_density_dot_mm = 8;
constexpr int band_width_dots = 384;
constexpr int band_length_dots = 227 * print_density_dot_mm;

// Electrical parameters
constexpr int rx_pin = 8;
constexpr int tx_pin = 9;

#endif