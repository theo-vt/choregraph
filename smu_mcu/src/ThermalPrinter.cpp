
#include "ThermalPrinter.h"
#include <Arduino.h>

constexpr uint8_t GS = 0x1D;
constexpr uint8_t ESC = 0x1B;

ThermalPrinter::ThermalPrinter(int rx_pin, int tx_pin, uint16_t width_dots, uint16_t length_dots)
    : serial(rx_pin, tx_pin)
    , width_dots(width_dots)
    , length_dots(length_dots)
{

}

ErrCode ThermalPrinter::write(ControlParameters ctrl)
{
    uint8_t n1 = (ctrl.max_heating_dots / 8) - 1;
    uint8_t n2 = ctrl.heating_time_us / 10;
    uint8_t n3 = ctrl.heating_interval_us / 10;

    serial.write(ESC);
    serial.write(0x37);
    serial.write(n1);
    serial.write(n2);
    serial.write(n3);

    uint16_t num_firing_events = ceil(static_cast<float>(width_dots) / static_cast<float>(ctrl.max_heating_dots)); 
    row_printing_time_us = num_firing_events * ctrl.heating_time_us  + (num_firing_events-1) * ctrl.heating_interval_us;

    return ErrCode::ok;
}
ErrCode ThermalPrinter::write(StartRasterImage params)
{
    if (params.horizontal_dots > width_dots) {
        return ErrCode::index_error;
    }
    if (params.vertical_dots > length_dots) {
        return ErrCode::index_error;
    }

    uint8_t m;
    switch (params.mode) {
    case StartRasterImage::RasterImageMode::Normal:
        m = 0x30;
        break;
    case StartRasterImage::RasterImageMode::DoubleWidth:
        m = 0x31;
        break;
    case StartRasterImage::RasterImageMode::DoubleHeight:
        m = 0x32;
        break;
    case StartRasterImage::RasterImageMode::Quadruple:
        m = 0x33;
        break;
    }

    uint8_t xL = params.horizontal_dots % 256;
    uint8_t xH = params.horizontal_dots / 256;

    uint8_t yL = params.vertical_dots % 256;
    uint8_t yH = params.vertical_dots / 256;
    
    serial.write(GS);
    serial.write(0x76);
    serial.write(0x30);
    serial.write(m);
    serial.write(xL);
    serial.write(xH);
    serial.write(yL);
    serial.write(yH);

    setMode(RasterImageMode {
        .row_bytes=params.horizontal_dots,
        .remaining_rows=params.vertical_dots,
    });

    return ErrCode::ok;
}
ErrCode ThermalPrinter::write(RasterImageRow row)
{
    if (mode != PrinterMode::RasterImage || raster_image_mode.remaining_rows == 0) {
        return ErrCode::command_not_handled;
    }
    serial.write(row.data, raster_image_mode.row_bytes);
    raster_image_mode.remaining_rows--;
    
    return ErrCode::ok;
}
void ThermalPrinter::setMode(RasterImageMode raster_mode)
{
    mode = PrinterMode::RasterImage;
    raster_image_mode = raster_mode;
}