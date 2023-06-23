#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <string.h>

#include "ti_bmp.h"


// test if existing file is recognized correctly
static void v2_aufg1_existBMPpositive(void** state)
{
    int32_t ret = existBmp("test/codeblocks1.bmp");
    assert_int_equal(ret, 0);
}

// test if not existing file is recognized correctly
static void v2_aufg1_existBMPnegative(void** state)
{
    int32_t ret = existBmp("test/codeblocks0.bmp");
    assert_int_equal(ret, -1);
}

// test if width of three images is read out correctly
static void v2_aufg2_getBMPWidthpositive(void** state)
{
    int32_t ret = 0;
    
    ret = getBmpWidth("test/codeblocks1.bmp");
    assert_int_equal(ret, 225);
    
    ret = getBmpWidth("test/codeblocks2.bmp");
    assert_int_equal(ret, 111);
    
    ret = getBmpWidth("test/codeblocks3.bmp");
    assert_int_equal(ret, 73);
}

// test if not existing file is recognized correctly
static void v2_aufg2_getBMPWidthnegative(void** state)
{
    int32_t ret = getBmpWidth("test/codeblocks0.bmp");
    assert_int_equal(ret, -1);
}

// test if height of three images is read out correctly
static void v2_aufg2_getBMPHeightpositive(void** state)
{
    int32_t ret = 0;
    
    ret = getBmpHeight("test/codeblocks1.bmp");
    assert_int_equal(ret, 225);
    
    ret = getBmpHeight("test/codeblocks2.bmp");
    assert_int_equal(ret, 141);
    
    ret = getBmpHeight("test/codeblocks3.bmp");
    assert_int_equal(ret, 42);
}

// test if not existing file is recognized correctly
static void v2_aufg2_getBMPHeightnegative(void** state)
{
    int32_t ret = getBmpHeight("test/codeblocks0.bmp");
    assert_int_equal(ret, -1);
}

// test if data size of three images is read out correctly
static void v2_aufg2_getBMPDataSizepositive(void** state)
{
    uint32_t ret = 0;
    
    ret = getBmpDataSize("test/codeblocks1.bmp");
    assert_int_equal(ret, 152100);
    
    ret = getBmpDataSize("test/codeblocks2.bmp");
    assert_int_equal(ret, 47376);
    
    ret = getBmpDataSize("test/codeblocks3.bmp");
    assert_int_equal(ret, 9240);
}

// test if not existing file is recognized correctly
static void v2_aufg2_getBMPDataSizenegative(void** state)
{
    uint32_t ret = getBmpDataSize("test/codeblocks0.bmp");
    uint32_t uintmax = -1;
    assert_int_equal(ret, uintmax);
}

// test if data block of three images is read out correctly
static void v2_aufg3_getBMPDatapositive(void** state)
{
    uint8_t ret = 0;
    
    int datasize1 = 152100;
    uint8_t data1[datasize1];
    ret = getBmpData("test/codeblocks1.bmp", data1);
    assert_int_equal(ret, 0);
    uint8_t data1_ref[datasize1];
    FILE* file1 = fopen("test/codeblocks1.bmp.data", "rb");
    fread(data1_ref, 1, datasize1, file1);
    fclose(file1);
    for(int i = 0; i < datasize1; i++)
    {
        assert_int_equal(data1[i], data1_ref[i]);
    }
    
    
    int datasize2 = 47376;
    uint8_t data2[datasize2];
    ret = getBmpData("test/codeblocks2.bmp", data2);
    assert_int_equal(ret, 0);
    uint8_t data2_ref[datasize2];
    FILE* file2 = fopen("test/codeblocks2.bmp.data", "rb");
    fread(data2_ref, 1, datasize2, file2);
    fclose(file2);
    for(int i = 0; i < datasize2; i++)
    {
        assert_int_equal(data2[i], data2_ref[i]);
    }
    
    
    int datasize3 = 9240;
    uint8_t data3[datasize3];
    ret = getBmpData("test/codeblocks3.bmp", data3);
    assert_int_equal(ret, 0);
    uint8_t data3_ref[datasize3];
    FILE* file3 = fopen("test/codeblocks3.bmp.data", "rb");
    fread(data3_ref, 1, datasize3, file3);
    fclose(file3);
    for(int i = 0; i < datasize3; i++)
    {
        assert_int_equal(data3[i], data3_ref[i]);
    }
}

// test if not existing file is recognized correctly
static void v2_aufg3_getBMPDatanegative(void** state)
{
    uint8_t data = 0;
    uint8_t ret = getBmpData("test/codeblocks0.bmp", &data);
    uint8_t uintmax = -1;
    assert_int_equal(ret, uintmax);
}

// test if conversion of rgb to gray is implemented correctly
static void v2_aufg4_convertRgb2Gray(void** state)
{
    uint8_t rgbImage[9] = {111, 74, 250, 250, 74, 111, 74, 111, 250};
    uint8_t grayImage_ref[3] = {130, 105, 148};
    
    uint8_t* grayImage = convertRgb2Gray(rgbImage, 3);
    for(int i = 0; i < 3; i++)
    {
        assert_int_equal(grayImage[i], grayImage_ref[i]);
    }
}

int main()
{
    const struct CMUnitTest versuch02[] =
    {
        cmocka_unit_test(v2_aufg1_existBMPpositive),
        cmocka_unit_test(v2_aufg1_existBMPnegative),
        cmocka_unit_test(v2_aufg2_getBMPWidthpositive),
        cmocka_unit_test(v2_aufg2_getBMPWidthnegative),
        cmocka_unit_test(v2_aufg2_getBMPHeightpositive),
        cmocka_unit_test(v2_aufg2_getBMPHeightnegative),
        cmocka_unit_test(v2_aufg2_getBMPDataSizepositive),
        cmocka_unit_test(v2_aufg2_getBMPDataSizenegative),
        cmocka_unit_test(v2_aufg3_getBMPDatapositive),
        cmocka_unit_test(v2_aufg3_getBMPDatanegative),
        cmocka_unit_test(v2_aufg4_convertRgb2Gray)
    };

    cmocka_run_group_tests(versuch02, NULL, NULL);
    
    return 0;
}
