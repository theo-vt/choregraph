
#include "ThermalPrinter.h"

constexpr uint8_t GS = 0x1D;
constexpr uint8_t ESC = 0x1B;

ThermalPrinter::ThermalPrinter(int rx_pin, int tx_pin, int width_dots, int height_dots)
    : serial(rx_pin, tx_pin)
    , width_dots(width_dots)
    , height_dots(height_dots)
{

}

ErrCode ThermalPrinter::write(ControlParameters ctrl)
{
    uint8_t n1 = ctrl.max_heating_dots / 8;
    uint8_t n2 = ctrl.heating_time_us / 10;
    uint8_t n3 = ctrl.heating_interval_us / 10;

    serial.write(ESC);
    serial.write(0x37);
    serial.write(n1);
    serial.write(n2);
    serial.write(n3);

    return ErrCode::ok;
}
ErrCode ThermalPrinter::write(StartRasterImage params)
{
    if (params.horizontal_dots > width_dots) {
        return ErrCode::index_error;
    }
    if (params.vertical_dots > height_dots) {
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
    if (mode != PrinterMode::RasterImage || rasterImageMode.remaining_rows == 0) {
        return ErrCode::command_not_handled;
    }
    serial.write(row.data, rasterImageMode.row_bytes);
    rasterImageMode.remaining_rows--;
    
    return ErrCode::ok;
}
void ThermalPrinter::setMode(RasterImageMode raster_mode)
{
    mode = PrinterMode::RasterImage;
    rasterImageMode = raster_mode;
}