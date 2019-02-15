#include "..//zv_private.h"
#include "zv_meas.h"


int zv_meas_genRect(void * mr, double x, double y, double width, double height, int filterSize)
{
    if (NULL == mr)
    {
        return ZV_ST_NULL_P5;
    }
    ZvRectMeas * p = (ZvRectMeas*)mr;
    p->type = ZV_MEAS_RECT;
    p->x = x;
    p->y = y;
    p->w = width;
    p->h = height;
    p->filterSize = filterSize;
    return ZV_ST_OK;
}

int zv_meas_genRect2(void *mr, double cx, double cy, double size1, double size2,
    double angle, int filterSize, int interp)
{
    ZV_CHK_NULL1(mr);
    if (ZV_INTERP_MAX <= interp)
    {
        return ZV_ERR_FA_RANGE_7;
    }

    ZvRect2Meas *p = (ZvRect2Meas*)mr;
    p->type = ZV_MEAS_RECT2;
    p->cx = cx;
    p->cy = cy;
    p->w = size1;
    p->h = size2;
    p->angle = angle;
    p->filterSize = filterSize;
    p->interp = ZV_ADP_INTERP(interp);
    return ZV_ST_OK;
}

int zv_meas_genArc(void *mr, double cx, double cy, double r, double angleStart, double angleEnd, double rAnnulus, int filterSize, int interp)
{
    if (NULL == mr)
    {
        return ZV_ST_NULL_P7;
    }
    if (ZV_INTERP_MAX <= interp)
    {
        return ZV_ST_OUT_RANGE_P9;
    }

    ZvArcMeas *p = (ZvArcMeas*)mr;
    p->type = ZV_MEAS_ARC;
    p->cx = cx;
    p->cy = cy;
    p->r = r;
    p->aStart = angleStart;
    p->aEnd = angleEnd;
    p->annulusR = rAnnulus;
    p->filterSize = filterSize;
    p->interp = ZV_ADP_INTERP(interp);
    return ZV_ST_OK;
}

// 区域的灰度分布
// 即：从白到黑 和 从黑到白的 灰度值变换情况
int zv_meas_projection(ZvImage _img, ZvMatrix proj, void *mr)
{
    ZV_CHK_NULL2(_img, proj);

    bool isRows = true;
    cv::Mat img = ZV_ADP_IMG_GETM(_img);

    if(img.channels() != 1)
        cvtColor(img, img, cv::COLOR_BGR2GRAY);    // 注意 img 的数据格式，本代码它的格式为 CV_8U 类型数据；

    double *grayVal;
    // 按照 行 来统计灰度的分布情况, 否则按照 列来进行统计
    if (isRows)
    {
        // x 轴表示 图像的行数， y 轴表示 每一行的灰度值得均值
        cv::Mat grayMat(img.rows, 2, CV_64FC1);
        grayVal = new double[img.rows];
        for (int i = 0; i < img.rows; i++)
        {
            grayVal[i] = 0.0;
            for (int j = 0; j < img.cols; j++)
            {
                grayVal[i] += (int)img.at<uchar>(i, j);   // 求第 i 列的所有灰度值之和
            }

            grayVal[i] /= img.cols;

            grayMat.at<double>(i, 0) = (double)i;
            grayMat.at<double>(i, 1) = (double)grayVal[i];
        }

        ZV_ADP_MAT_SETM(proj, grayMat);
    }
    else
    {
        // x 轴表示 图像的列数， y 轴表示 每一列的灰度值得均值
        cv::Mat grayMat(img.cols, 2, CV_64FC1);
        grayVal = new double[img.cols];
        for (int i = 0; i < img.cols; i++)
        {
            grayVal[i] = 0.0;
            for (int j = 0; j < img.rows; j++)
            {
                grayVal[i] += (int)img.at<uchar>(j, i);   // 求第 i 列的所有灰度值之和
            }
            grayVal[i] /= img.rows;

            grayMat.at<double>(i, 0) = (double)i;
            grayMat.at<double>(i, 1) = (double)grayVal[i];
        }
        ZV_ADP_MAT_SETM(proj, grayMat);
    }

    return ZV_ST_OK;
}

// 检测点
int zv_meas_pos(ZvImage img, ZvMatrix pts, void *mr, int thresh, int type, int select)
{
    ZV_CHK_NULL2(img, pts);

    cv::Mat src(ZV_ADP_IMG_GETM(img).rows, ZV_ADP_IMG_GETM(img).cols, CV_64FC1, ZV_ADP_IMG_GETM(img).data);
    //zv_meas_projection(img, &src, mr);

    // 把灰度分布的 像素值 存放到 points 中去
    vector<cv::Point> points;
    for (int i = 0; i < src.rows; i++)
        points.push_back(cv::Point((int)src.at<double>(i, 0), (int)src.at<double>(i, 1)));

    vector<double> garyYval;
    for (int i = 0; i < points.size(); i++)
        garyYval.push_back(points[i].y);

    // 1. 对灰度值轮廓线 进行高斯平滑滤波处理
    cv::Mat Guassian(garyYval);
    cv::GaussianBlur(Guassian, Guassian, cv::Size(5, 5), 1.1, 0);

    vector<cv::Point> GuassianPoint;
    for (int i = 0; i < garyYval.size(); i++)
        GuassianPoint.push_back(cv::Point(points[i].x, (int)Guassian.at<double>(i, 0)));

    // 3. 对灰度轮廓求一阶前向差分运算
    vector<cv::Point> GradPoint;
    for (int i = 0; i < points.size(); i++)
    {
        if (i == points.size() - 1)
            GradPoint.push_back(cv::Point(points[i].x, 0));
        else
            GradPoint.push_back(cv::Point(points[i].x, GuassianPoint[i].y - GuassianPoint[i + 1].y));
    }

    // 包含有错误的出现
    int n = 0;
    double xLoc[50], yVal[50];
    for (int i = 0; i < GradPoint.size(); i++)
    {
        // 4. 根据阈值筛选 符合要求的边界点
        if (abs(GradPoint[i].y) >= thresh)
            if (abs(GradPoint[i].y) > abs(GradPoint[i - 1].y) && abs(GradPoint[i + 1].y) <= abs(GradPoint[i].y))   // 满足这个条件说明是 图像的边缘点
            {
                // 记下 x 的位置, 和位置出的像素值
                xLoc[n] = GradPoint[i].x;
                yVal[n] = GradPoint[i].y;
                n++;
            }
    }

    cv::Mat edgeMat(n, 2, CV_64FC1);
    for (int i = 0; i < n; i++)
    {
        edgeMat.at<double>(i, 0) = (double)xLoc[i];
        edgeMat.at<double>(i, 1) = (double)yVal[i];
    }

    ZV_ADP_MAT_SETM(pts, edgeMat);
    return ZV_ST_OK;
}

// 检测间距
int zv_meas_pairs(ZvImage img, ZvMatrix pairs, void *mr, int thresh, int type, int select)
{
    ZV_CHK_NULL2(img, pairs);
    cv::Mat mat(ZV_ADP_IMG_GETM(img).rows, ZV_ADP_IMG_GETM(img).cols, CV_64FC1, ZV_ADP_IMG_GETM(img).data);

    int m = 0, num1, num2, num3;
    double distGray[50];
    for (int i = 0; i < mat.rows; i++)
    {
        if (i == 0)
        {
            num1 = 0;
            num2 = (int)mat.at<double>(i, 1);     // error
            num3 = (int)mat.at<double>(i + 1, 1);
        }
        else if (i == mat.rows - 1)
        {
            num3 = 0;
            num1 = (int)mat.at<double>(i - 1, 1);
            num2 = (int)mat.at<double>(i, 1);
        }
        else
        {
            num1 = (int)mat.at<double>(i - 1, 1);
            num2 = (int)mat.at<double>(i, 1);
            num3 = (int)mat.at<double>(i + 1, 1);
        }


        if (type == 0 && num1 < num2 && num2 > num3)    // 黑色的区域的宽度
        {
            distGray[m] = (double)mat.at<double>(i + 1, 0) - (double)mat.at<double>(i, 0); 
            m++;
        }
        if (type == 1 && num2 < 0 && num1 > num2 && num2 < num3)   // 求白色区域的间距 (白到黑）
        {
            distGray[m] = (double)mat.at<double>(i + 1, 0) - (double)mat.at<double>(i, 0);
            m++;
        }
    }

    cv::Mat matD(m, 1, CV_64FC1);
    for (int i = 0; i < m; i++)
        matD.at<double>(i, 0) = (double)distGray[i];

    ZV_ADP_MAT_SETM(pairs, matD);
    return ZV_ST_OK;
}

int zv_meas_lines(ZvImage img, ZvMatrix lines, void *mr, int thresh, int type, int select, int subNum, int subWidth)
{
    //TODO
    return ZV_ST_OK;
}

int zv_meas_circle(ZvImage img, ZvMatrix circles, void *mr, int thresh, int type, int select, int subNum, int subWidth)
{
    //TODO
    return ZV_ST_OK;
}


// 在src 图像上得到一个 旋转矩形 ROI 的图 
// angle 负数为逆时针旋转
int zv_ip_rect2Measurer(ZvImage src, ZvImage Roi, double x, double y, double width, double height, double angle)
{
    ZV_CHK_NULL2(src, Roi);

    cv::Mat img = ZV_ADP_IMG_GETM(src);   // 图像是 BGR 的格式
    CvBox2D box;
    box.size.width = (float)width;
    box.size.height = (float)height;
    box.angle = (float)angle;           // 负数为逆时针旋转
    box.center.x = (float)x;
    box.center.y = (float)y;

    CvPoint2D32f point[4];
    int i;
    for (i = 0; i < 4; i++)
    {
        point[i].x = 0;
        point[i].y = 0;
    }
    cvBoxPoints(box, point); //计算二维盒子顶点
    CvPoint pt[4];
    for (i = 0; i < 4; i++)
    {
        pt[i].x = (int)point[i].x;
        pt[i].y = (int)point[i].y;
    }

    vector<cv::Point> contour;
    // 旋转矩形的四个顶点
    contour.push_back(pt[0]);
    contour.push_back(pt[1]);
    contour.push_back(pt[2]);
    contour.push_back(pt[3]);

    cv::RotatedRect rect = cv::minAreaRect(contour);//外接矩形

    cv::Point2f vertices[4];
    rect.points(vertices);         //外接矩形的 4 个顶点

    for (int i = 0; i < 4; i++)    //画矩形
        line(img, vertices[i], vertices[(i + 1) % 4], cv::Scalar(255, 0, 0), 1, 8, 0);

    cv::Point2f center = rect.center;//外接矩形中心点坐标
    cv::Mat rot_mat = cv::getRotationMatrix2D(center, rect.angle, 1.0);//求旋转矩阵
    cv::Mat rot_image;
    cv::warpAffine(img, rot_image, rot_mat, img.size());//原图像旋转

    // 得到旋转到 正位置上的矩形框
    cv::Mat roi = rot_image(cv::Rect2f(center.x - (rect.size.width / 2), center.y - (rect.size.height / 2), rect.size.width, rect.size.height));//提取ROI

    ZV_ADP_IMG_SETM(Roi, roi);

    return ZV_ST_OK;
}

// 生成圆环测量区域
int zv_ip_arcMeasurer(ZvImage src, ZvImage Roi, double cX, double cY, double r, double edgeWidth, double aStart, double aEnd, double annulusR, int interp)
{
    ZV_CHK_NULL2(src, Roi);

    cv::Mat image_src = ZV_ADP_IMG_GETM(src);

    cv::Mat ROI(image_src.rows, image_src.cols, image_src.type(), cv::Scalar(0, 0, 0));    // 产生全黑图像
    cv::circle(ROI, cv::Point((int)cX, (int)cY), (int)r + (int)annulusR, cv::Scalar(255, 255, 255), -1, 8, 0);    // 画外圆环， 用白色填充
    cv::circle(ROI, cv::Point((int)cX, (int)cY), (int)r - (int)annulusR, cv::Scalar(0, 0, 0), -1, 8, 0);    // 画内圆环，用黑填充;

    cv::Mat res, Res;
    bitwise_and(image_src, ROI, res);   // 按位与 运算

    cv::Mat rect1(image_src.rows, image_src.cols, image_src.type(), cv::Scalar(0, 0, 0));
    cv::Mat rect2(image_src.rows, image_src.cols, image_src.type(), cv::Scalar(0, 0, 0));
    cv::rectangle(rect1, cv::Rect(cX, cY - r - annulusR, r + annulusR, r + annulusR), cv::Scalar(255, 255, 255), -1, 8, 0);
    cv::rectangle(rect2, cv::Rect(cX, cY - r - annulusR, r + annulusR, r + annulusR), cv::Scalar(255, 255, 255), -1, 8, 0);
   
    // 2. 对矩形进行 逆时针旋转 ：rect1 旋转 aStart 角度， rect2 旋转 aEnd + aStart - 90 角度
    cv::Mat rot1 = cv::getRotationMatrix2D(cv::Point2f((float)cX, (float)cY), aStart, 1);
    cv::Mat rot2 = cv::getRotationMatrix2D(cv::Point2f((float)cX, (float)cY), aEnd + aStart - 90, 1);

    cv::Mat dst1, dst2;
    cv::warpAffine(rect1, dst1, rot1, rect1.size());
    cv::warpAffine(rect1, dst2, rot2, rect1.size());

    cv::Mat A1, A2, A3;
    bitwise_and(res, dst1, A1);
    bitwise_and(res, dst2, A2);
    bitwise_or(A1, A2, A3);

    /*if ((cX - (r + annulusR) - edgeWidth) + (2 * (r + annulusR + edgeWidth)) <= A3.cols && (cY - (r + annulusR) - edgeWidth) + (2 * (r + annulusR + edgeWidth)) <= A3.rows)
    {
    Res = A3(cv::Rect(cX - (r + annulusR) - edgeWidth, cY - (r + annulusR) - edgeWidth, 2 * (r + annulusR + edgeWidth), 2 * (r + annulusR + edgeWidth)));
    ZV_ADP_IMG_SETM(Roi, Res);
    }*/

    ZV_ADP_IMG_SETM(Roi, A3);
    return ZV_ST_OK;
}
