#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <string.h>
#include "ti_bmp.h"



// test for square image of size 100x100 with background color 111
static void v1_aufg2_genBackgroundImageEven(void** state)
{
    uint32_t height = 100;
    uint32_t width = 100;
    uint8_t backgroundColor = 111;

    uint8_t* image = genBackgroundImage(width, height, backgroundColor);

    assert_non_null(image);

    for(int i = 0; i < width*height; i++)
    {
        assert_int_equal(image[i], backgroundColor);
    }

    free(image);
}

// test for square image of size 101x101 with background color 111
static void v1_aufg2_genBackgroundImageUneven(void** state)
{
    uint32_t height = 101;
    uint32_t width = 101;
    uint8_t backgroundColor = 111;

    uint8_t* image = genBackgroundImage(width, height, backgroundColor);

    assert_non_null(image);

    for(int i = 0; i < width*height; i++)
    {
        assert_int_equal(image[i], backgroundColor);
    }

    free(image);
}

// test for non-square image of size 150x100 with background color 222
static void v1_aufg2_genBackgroundImageNonSquare(void** state)
{
    uint32_t height = 100;
    uint32_t width = 150;
    uint8_t backgroundColor = 222;

    uint8_t* image = genBackgroundImage(width, height, backgroundColor);

    assert_non_null(image);

    for(int i = 0; i < width*height; i++)
    {
        assert_int_equal(image[i], backgroundColor);
    }

    free(image);
}

// test for non-square image of size 2048x1024 with background color 73
static void v1_aufg2_genBackgroundImageBig(void** state)
{
    uint32_t height = 1024;
    uint32_t width = 2048;
    uint8_t backgroundColor = 73;

    uint8_t* image = genBackgroundImage(width, height, backgroundColor);

    assert_non_null(image);

    for(int i = 0; i < width*height; i++)
    {
        assert_int_equal(image[i], backgroundColor);
    }

    free(image);
}

// test for 5 concentric circles of color 10 in squared image (100x100)
static void v1_aufg3_drawCirclesSimple(void** state)
{
    uint8_t backgroundColor = 111;
    uint8_t circleColor = 10;
    uint32_t height = 100;
    uint32_t width = 100;
    uint32_t datasize = width*height;

    uint8_t image[datasize];
    memset(image, backgroundColor, datasize);

    drawCircles(image, width, height, 5, 1000, circleColor);

    assert_non_null(image);

    int histogram[256] = {0};
    for(int i = 0; i < datasize; i++)
    {
        histogram[image[i]]++;
    }

    assert_int_not_equal(histogram[backgroundColor], 0);
    assert_int_not_equal(histogram[circleColor], 0);
}

// test for consideration of circlePoints parameter
static void v1_aufg3_drawCirclesCirclePoints(void** state)
{
    uint8_t backgroundColor = 111;
    uint8_t circleColor = 10;
    uint32_t height = 100;
    uint32_t width = 100;
    uint32_t datasize = width*height;

    uint8_t image[datasize];
    memset(image, backgroundColor, datasize);
    drawCircles(image, width, height, 5, 5, circleColor);

    assert_non_null(image);

    int histogram5[256] = {0};
    for(int i = 0; i < datasize; i++)
    {
        histogram5[image[i]]++;
    }

    memset(image, backgroundColor, datasize);
    drawCircles(image, width, height, 5, 5000, circleColor);

    assert_non_null(image);

    int histogram5000[256] = {0};
    for(int i = 0; i < datasize; i++)
    {
        histogram5000[image[i]]++;
    }

    assert_int_not_equal(histogram5[backgroundColor], histogram5000[backgroundColor]);
    assert_int_not_equal(histogram5[circleColor], histogram5000[circleColor]);
}


int main()
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(v1_aufg2_genBackgroundImageEven),
        cmocka_unit_test(v1_aufg2_genBackgroundImageUneven),
        cmocka_unit_test(v1_aufg2_genBackgroundImageNonSquare),
        cmocka_unit_test(v1_aufg2_genBackgroundImageBig),
        cmocka_unit_test(v1_aufg3_drawCirclesSimple),
        cmocka_unit_test(v1_aufg3_drawCirclesCirclePoints)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
