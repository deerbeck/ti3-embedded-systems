#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <string.h>

#include "ti_bmp.h"


// test if convolution is applied correctly
static void v3_aufg3_conv2Dpositive(void** state)
{
    // source image
    uint8_t srcdata[48] = {180, 185, 190, 195, 200, 205, 210, 215, 220, 225, 230, 235,
                           120, 125, 130, 135, 140, 145, 150, 155, 160, 165, 170, 175,
                           60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115,
                           0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55};
    // expected destination image
    uint8_t dstdata[48] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                           0, 91, 96, 101, 106, 111, 116, 121, 126, 131, 136, 0,
                           0, 31, 36, 41, 46, 51, 56, 61, 66, 71, 76, 0,
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    // kernel in use
    float values[9] = {0.8, -0.7, 0.6,
                      -0.5, 0.4, 0.3,
                       0.2, -0.1, 0.0};
    // container for destination image
    uint8_t data[48];
    memset(data, 0, 48);

    // construct source image
    Image src;
    src.width = 12;
    src.height = 4;
    src.datasize = src.width * src.height;
    src.data = srcdata;

    // construct destination image
    Image dst;
    dst.width = src.width;
    dst.height = src.height;
    dst.datasize = src.datasize;
    dst.data = data;

    // construct kernel
    Kernel krnl;
    memcpy(krnl.values, values, sizeof(float)*9);

    // call convolution
    conv2D(&src, &dst, &krnl);

    // check assertions
    for(int i = 0; i < 48; i++)
    {
        assert_int_equal(dst.data[i], dstdata[i]);
    }
}

// test if convolution is applied correctly
static void v3_aufg3_conv2Dborder(void** state)
{
    // source image
    uint8_t srcdata[48] = {180, 185, 190, 195, 200, 205, 210, 215, 220, 225, 230, 235,
                           120, 125, 130, 135, 140, 145, 150, 155, 160, 165, 170, 175,
                           60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115,
                           0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55};
    // expected destination image
    uint8_t dstdata[48] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                           0, 91, 96, 101, 106, 111, 116, 121, 126, 131, 136, 0,
                           0, 31, 36, 41, 46, 51, 56, 61, 66, 71, 76, 0,
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    // kernel in use
    float values[9] = {0.8, -0.7, 0.6,
                      -0.5, 0.4, 0.3,
                       0.2, -0.1, 0.0};
    // container for destination image
    uint8_t data[48];
    memset(data, 1, 48);

    // construct source image
    Image src;
    src.width = 12;
    src.height = 4;
    src.datasize = src.width * src.height;
    src.data = srcdata;

    // construct destination image
    Image dst;
    dst.width = src.width;
    dst.height = src.height;
    dst.datasize = src.datasize;
    dst.data = data;

    // construct kernel
    Kernel krnl;
    memcpy(krnl.values, values, sizeof(float)*9);

    // call convolution
    conv2D(&src, &dst, &krnl);

    // check assertions
    for(int i = 0; i < 48; i++)
    {
        assert_int_equal(dst.data[i], dstdata[i]);
    }
}


int main()
{
    const struct CMUnitTest versuch03[] =
    {
        cmocka_unit_test(v3_aufg3_conv2Dpositive),
        cmocka_unit_test(v3_aufg3_conv2Dborder)
    };

    cmocka_run_group_tests(versuch03, NULL, NULL);

    return 0;
}
