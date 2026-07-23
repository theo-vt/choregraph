
#ifndef THERMAL_PRINTER_H_
#define THERMAL_PRINTER_H_

#include "SoftwareSerial.h"
#include "CommCodes.hpp"

struct ControlParameters {
    // From the datasheet:
    // The more max heating dots, the more peak current will cost when
    // printing, the faster printing speed. The max heating dots is 8*(n1+1)
    // Meaning:
    // The number of dots that can be activated at a time
    uint16_t max_heating_dots; // defaults to 7 = 64 dots

    // The more heating time, the more density, but the slower printing
    // speed. If heating time is too short, blank page may occur.
    uint16_t heating_time_us; // defaults to 800

    // The more heating interval, the clearer, but the slower printing speed.
    uint16_t heating_interval_us; // defaults to 20
};

struct StartRasterImage {
    enum class RasterImageMode {
        Normal,
        DoubleWidth,
        DoubleHeight,
        Quadruple
    };
    RasterImageMode mode;
    uint16_t horizontal_dots;
    uint16_t vertical_dots;
};
struct RasterImageRow {
    uint8_t* data;
};

struct RasterImageMode {
    uint16_t row_bytes;
    uint16_t remaining_rows;
};

class ThermalPrinter {
public:
    enum class PrinterMode {
        Normal,
        RasterImage,
    };
private:
    SoftwareSerial serial;

    PrinterMode mode {PrinterMode::Normal};
    RasterImageMode raster_image_mode;
    uint16_t width_dots { 0 };
    uint16_t length_dots { 0 };
    uint16_t row_printing_time_us { 0 };

public:
    ThermalPrinter(int rx_pin, int tx_pin, uint16_t width_dots, uint16_t length_dots);

    uint16_t get_row_printing_time_us() const { return row_printing_time_us; }

    ErrCode write(ControlParameters ctrl);

    // Print will start when the last row (as defined in StartRasterImage)
    // is sent with a RasterImageRow
    // track progress on upload with raster_image_remaining_rows()
    ErrCode write(StartRasterImage params);
    ErrCode write(RasterImageRow row);

    // This will return even when not in raster image mode
    // beware
    int raster_image_remaining_rows() const;

private:
    void setMode(RasterImageMode raster_mode);
};

#endif