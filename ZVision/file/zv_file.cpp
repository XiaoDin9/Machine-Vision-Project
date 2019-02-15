#include "zv_private.h"
#include "zv_file.h"

//_flags“¿¥Œ∂‘”¶OpenCV  -1/0/1/2/4
int zv_file_readImage(ZvImage _img, char *_filename, int _flags)
{
    ZV_CHK_NULL2(_img, _filename);
    if (ZV_READ_TYPE_MAX <= (uint)_flags)
    {
        return ZV_ERR_FA_RANGE_3;
    }

    //if (ZV_READ_EXCOLOR != _flags)
    //{
    _flags -= 1;
    //}
    cv::Mat img = cv::imread(_filename, _flags);
    if (0 == img.size().area())
    {
        return ZV_ERR_F_OPEN_FAIL;
    }
    if (3 == img.channels())
    {
        cvtColor(img, img, cv::COLOR_BGR2RGB);
    }
    if (4 == img.channels())
    {
        cvtColor(img, img, cv::COLOR_BGRA2RGBA);
    }
   
    ZV_ADP_IMG_SETM(_img, img);

    return ZV_ST_OK;
}

int zv_file_writeImage(ZvImage _img, char *_filename, int param)
{
    ZV_CHK_NULL2(_img, _filename);

    vector<int> vecParams;
    if (0 < param && param <= 100)
    {
        vecParams.push_back(cv::IMWRITE_JPEG_QUALITY);
        vecParams.push_back(param);
        vecParams.push_back(cv::IMWRITE_PNG_COMPRESSION);
        vecParams.push_back(10 - (param + 9) / 10);
        vecParams.push_back(cv::IMWRITE_WEBP_QUALITY);
        vecParams.push_back(param);
    }

    cv::Mat img = ZV_ADP_IMG_GETM(_img), tmp;
    if (3 == img.channels())
    {
        cvtColor(img, tmp, cv::COLOR_RGB2BGR);
    }
    else if (4 == img.channels())
    {
        cvtColor(img, tmp, cv::COLOR_RGBA2BGRA);
    }
    else
    {
        tmp = img;
    }

    if (cv::imwrite(_filename, tmp, vecParams))
    {
        return ZV_ST_OK;
    }

    return ZV_ERR_F_SAVE_FAIL;
}

int zv_file_readMatrix(ZvMatrix _mat, char *_filename, char *_nodeName, int _flags)
{
    ZV_CHK_NULL3(_mat, _filename, _nodeName);

    cv::FileStorage fs(_filename, cv::FileStorage::READ);
    if (!fs.isOpened())
    {
        return ZV_ERR_F_OPEN_FAIL;
    }

    bool isFind = false;
    cv::Mat m;
    cv::FileNode &node = fs[_nodeName];
    if (!node.empty())
    {
        node >> m;
        isFind = true;
    }
    fs.release();
    ZV_ADP_IMG_SETM(_mat, m);

    return isFind ? ZV_ST_OK : ZV_WARN_NODE_NOT_EXIST;
}

int zv_file_writeMatrix(ZvMatrix _mat, char *_filename, char *_nodeName, int _flags)
{
    ZV_CHK_NULL3(_mat, _filename, _nodeName);

    cv::FileStorage fs;
    vector<cv::Mat> matList;
    vector<cv::String> nodeList;
    if (1 == _flags)
    {
        fs.open(_filename, cv::FileStorage::READ);
        if (!fs.isOpened())
        {
            return ZV_ERR_F_OPEN_FAIL;
        }
        cv::FileNode node = fs.root();
        bool isFind = false;
        for (cv::FileNodeIterator it = node.begin(); it != node.end(); it++)
        {
            cv::Mat mat;
            nodeList.push_back((*it).name());
            if (_nodeName == (*it).name())
            {
                matList.push_back(ZV_ADP_IMG_GETM(_mat));
                isFind = true;
            }
            else
            {
                (*it) >> mat;
                matList.push_back(mat);
            }
        }
        fs.release();
        if (!isFind)
        {
            nodeList.push_back(_nodeName);
            matList.push_back(ZV_ADP_IMG_GETM(_mat));
            fs.open(_filename, cv::FileStorage::WRITE);
        }
        else
        {
            fs.open(_filename, cv::FileStorage::WRITE);
        }
    }
    else if (0 == _flags)
    {
        fs.open(_filename, cv::FileStorage::WRITE);
        nodeList.push_back(_nodeName);
        matList.push_back(ZV_ADP_IMG_GETM(_mat));
    }

    if (!fs.isOpened())
    {
        return ZV_ERR_F_OPEN_FAIL;
    }

    for (int i = 0; i < matList.size(); i++)
    {
        fs << nodeList[i] << matList[i];
    }
    fs.release();
    return ZV_ST_OK;
}