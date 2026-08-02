
#include <unity.h>

#include <CircularBuffer.hpp>

#include <string.h>
#include <stdio.h>

void test_push_overflow()
{
    CircularBuffer buffer;
    uint8_t blanks[config::comm::buffer_len+1];
    memset(blanks, 0, config::comm::buffer_len+1);
    
    TEST_ASSERT_FALSE(buffer.push_bytes(blanks, config::comm::buffer_len+1));
    TEST_ASSERT_TRUE(buffer.push_bytes(blanks, config::comm::buffer_len-1));
}
void test_consume_over_boundary()
{
    constexpr int n_data = 20; // Must be even
    constexpr int n_blanks = config::comm::buffer_len-n_data/2;
    
    CircularBuffer buffer;
    
    uint8_t blanks[n_blanks];
    for (int i = 0; i < n_blanks; ++i) {
        blanks[i] = i;
    }

    uint8_t src[n_data];
    for (int i = 0; i < n_data; ++i) {
        src[i] = i+128;
    }

    TEST_ASSERT_TRUE(buffer.push_bytes(blanks, n_blanks));

    TEST_ASSERT_TRUE(buffer.consume_bytes(blanks, n_data/2));

    TEST_ASSERT_TRUE(buffer.push_bytes(src, n_data));

    TEST_ASSERT_TRUE(buffer.consume_bytes(blanks, n_blanks-n_data/2));

    uint8_t dst[n_data];
    TEST_ASSERT_TRUE(buffer.consume_bytes(dst, n_data));

    for (int i = 0; i < n_data; ++i) {
        TEST_ASSERT_EQUAL(dst[i], src[i]);
    }
}


int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_push_overflow);
    RUN_TEST(test_consume_over_boundary);
    UNITY_END();

    return 0;
}
