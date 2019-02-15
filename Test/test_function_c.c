#include "test_function.h"
#include "test_frame.h"


//≤‚ ‘∫Ø ˝Demo
TEST_FUNC(testCBase)
{
    TEST_TRACE("Version:%s\n", ZV_VERSION);
    TEST_CHK_TRUE(0 == g_zv_errLastError);
    TEST_RTN_PASS;
}

TEST_FUNC(zv_fileReadImage_c)
{
    char *fileName = TEST_DATA_PATH "1-RGBA.jpg";
    ZvImage img = test_frm_getImgDst(true);
    TEST_CORE_RUN(zv_fileReadImage(img, fileName, ZV_READ_RAW));
    TEST_TRACE("ReadImage:%s\n", fileName);

    TEST_CHK_TRUE(642 == zv_imgWidth(img));
    TEST_CHK_TRUE(484 == zv_imgHeight(img));

    TEST_RTN_PASS;
}

int testRegisterC()
{
    REG_FUNCTION(TEST_TEST, "∞Ê±æ¥Ú”°", testCBase);
    REG_FUNCTION(TEST_FILE, "∂¡»°ÕºœÒ", zv_fileReadImage_c);
    return 0;
}
