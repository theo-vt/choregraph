
#ifndef THERMAL_PRINTER_H_
#define THERMAL_PRINTER_H_

#include "SoftwareSerial.h"
#include "CommCodes.hpp"

struct ControlParameters {
    // The more max heating dots, the more peak current will cost when
    // printing, the faster printing speed. The max heating dots is 8*(n1+1)
    uint16_t max_heating_dots; // defaults to 64

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

    PrinterMode mode;
    RasterImageMode rasterImageMode;
    int width_dots;
    int height_dots;

public:
    ThermalPrinter(int rx_pin, int tx_pin, int width_dots, int height_dots);

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