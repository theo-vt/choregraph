
#ifndef CIRCULAR_BUFFER_HPP_
#define CIRCULAR_BUFFER_HPP_

#include <Config.hpp>

#include <inttypes.h>

class CircularBuffer {
public:
    uint8_t data[config::comm::buffer_len];
    uint16_t start_index {0};
    uint16_t length {0};

public:
    uint16_t available() const;

    // Add data to the buffer
    // returns true if the copy was successfull
    bool push_bytes(uint8_t* src, uint16_t len);

    // Copy from the data buffer to a dst buffer
    // Return true if the copy was successfull
    bool consume_bytes(uint8_t* dst, uint16_t len);

    template<typename T>
    bool consume(T& dst)
    {
        union data_T {
            uint8_t u8_data[sizeof(T)];
            T tmp;
        };
        data_T dT;
        if (!consume_bytes(dT.u8_data, sizeof(T))) {
            return false;
        }
        dst = dT.tmp;
    }
};

#endif