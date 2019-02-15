#include "zv_private.h"
#include "zv_core.h"


using namespace cv;
int zv_cont_getPoint(ZvContour contour, int ptId, double * ptX, double *ptY)
{
    ZV_CHK_NULL4(contour, g_zv_adp_notNull, ptX, ptY);
    if (ptId >= (int)contour->size())
    {
        return ZV_ERR_FA_RANGE_2;
    }

    *ptX = (*contour)[ptId].x;
    *ptY = (*contour)[ptId].y;

    return ZV_ST_OK;
}

int zv_cont_getPointsAll(ZvContour cont, double *pts, int *ptsLen)
{
    ZV_CHK_NULL3(cont, pts, ptsLen);

    if (*ptsLen < (int)cont->size()*2)
    {
        return ZV_ERR_G_BUF_SMALL;
    }
    *ptsLen = (int)cont->size() * 2;
    for (int i = 0; i < (int)cont->size(); i++)
    {
        pts[2 * i] = (*cont)[i].x;
        pts[2 * i + 1] = (*cont)[i].y;
    }
    return ZV_ST_OK;
}

int zv_cont_gen(ZvImage img, ZvContList contList, int mode, int appro)
{
    ZV_CHK_NULL2(img, contList);
    if (1 != zv_img_channels(img) || ZV_PIXEL_8U != zv_img_dataType(img))
    {
        return ZV_ERR_I_ONLY_8UC1;
    }
    if (0 != mode && 1 != mode)
    {
        return ZV_ERR_FA_RANGE_3;
    }
    if (0 != appro && 1 != appro)
    {
        return ZV_ERR_FA_RANGE_4;
    }
    
    findContours(ZV_ADP_IMG_GETM(img), contList->cdata, 0 == mode ? noArray() : contList->hierarchy,
        0 == mode ? RETR_EXTERNAL : RETR_TREE, appro + 1);
    contList->_size = (int)contList->cdata.size();
    contList->clist.resize(contList->_size);
    contList->cptr.resize(contList->_size);
    for (int i = 0; i < contList->_size; i++)
    {
        contList->clist[i].cont = &contList->cdata[i];
        contList->clist[i].contId = i;
        contList->cptr[i] = &contList->clist[i];
        contList->clist[i].curId = i;
    }

    return ZV_ST_OK;
}

int zv_cont_toMatrix(ZvContour cont, ZvMatrix mat)
{
    ZV_CHK_NULL2(cont, mat);
    if (0 == zv_cont_pointCount(cont))
    {
        ZV_ADP_MAT_SETM(mat, Mat());
        return ZV_ST_OK;
    }

    Mat tmp((int)cont->size(), 2, CV_32S, &(*cont)[0]);
    Mat m((int)cont->size(), 2, CV_64F);
    tmp.convertTo(m, CV_64F);

    ZV_ADP_MAT_SETM(mat, m);
    return ZV_ST_OK;
}

int zv_cont_fromMatrix(ZvContour cont, ZvMatrix mat)
{
    ZV_CHK_NULL2(cont, mat);
    Mat m = ZV_ADP_MAT_GETM(mat);
    if (2 != m.cols)
    {
        return ZV_ERR_M_SIZE;
    }

    if (0 == m.rows)
    {
        cont->release();
        return ZV_ST_OK;
    }
  
    double * data = m.ptr<double>();
    if (!cont->createContour(m.rows))
    {
        return ZV_ERR_MEM_ALLOC;
    }

    for (int i = 0; i < m.rows; i++)
    {
        (*cont)[i].x = (int)data[2*i];
        (*cont)[i].y = (int)data[2*i+1];
    }
    return ZV_ST_OK;
}
