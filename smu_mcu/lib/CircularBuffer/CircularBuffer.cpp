
#include "CircularBuffer.hpp"
#include "stdio.h"

uint16_t CircularBuffer::available() const
{
    return length;
}

bool CircularBuffer::push_bytes(uint8_t* src, uint16_t len)
{
    if (config::comm::buffer_len - length < len) {
        return false;
    }

    if (start_index + length + len < config::comm::buffer_len) {
        for (uint16_t i = 0; i < len; ++i) {
            data[start_index+length+i] = src[i];
        }
        length += len;
        return true;
    }

    uint16_t fhi = 0;
    uint16_t end_index = start_index + length;
    if (end_index > config::comm::buffer_len) {
        end_index -= config::comm::buffer_len;
    }
    for (fhi = 0; end_index + fhi < config::comm::buffer_len; ++fhi) {
        data[end_index+fhi] = src[fhi];
    }
    for (uint16_t i = 0; i < len-fhi; ++i) {
        data[i] = src[i+fhi];
    }
    length += len;
    return true;
}

bool CircularBuffer::consume_bytes(uint8_t* dst, uint16_t len)
{
    if (available() < len) {
        return false;
    }

    // Typical case
    if (config::comm::buffer_len - start_index > len) {
        for (uint16_t i = 0; i < len; ++i) {
            dst[i] = data[start_index+i];
        }
        start_index += len;
        length -= len;
        return true;
    }

    // Here we need to go over the end of the linear buffer
    uint16_t fhi = 0;
    for (fhi = 0; start_index + fhi < config::comm::buffer_len; ++fhi) {
        dst[fhi] = data[start_index+fhi];
    }
    for (uint16_t i = 0; i < len-fhi; ++i) {
        dst[fhi+i] = data[i];
    }
    start_index = len-fhi;
    length -= len;
    return true;
}
