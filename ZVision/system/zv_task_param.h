/*************************************************************
该文件为自动生成文件，如果修改请注意备份，重新生成将被覆盖
////由zv_module_gen.py生成，需要zv_module_templ.py模块内的
////固定字符串定义和zv_module.h文件内的函数声明，声明需要符
////合特定格式
*************************************************************/

#ifndef ZV_TASK_PARAM_H
#define ZV_TASK_PARAM_H

#ifdef __cplusplus
extern "C"
{
#endif


typedef struct
{
    char *type;
}ZvTPCamScan;

typedef struct
{
    int scanId;
    int prop;
    char *value;
    int maxValLen;
}ZvTPCamGetInfo;

typedef struct
{
    int camId;
    int scanId;
}ZvTPCamOpen;

typedef struct
{
    int camId;
    int *status;
}ZvTPCamStatus;

typedef struct
{
    int camId;
}ZvTPCamClose;

typedef struct
{
    int camId;
    int *size;
}ZvTPCamPayloadSize;

typedef struct
{
    ZvImage img;
    int camId;
}ZvTPCamGrab;

typedef struct
{
    int camId;
    int *camROI;
}ZvTPCamGetROI;

typedef struct
{
    int camId;
    int x;
    int y;
    int width;
    int height;
}ZvTPCamSetROI;

typedef struct
{
    int camId;
    double *time;
}ZvTPCamGetExposure;

typedef struct
{
    int camId;
    double time;
}ZvTPCamSetExposure;

typedef struct
{
    int camId;
    int bufCount;
}ZvTPCamStartGrabbing;

typedef struct
{
    int camId;
    int *isGrabbing;
}ZvTPCamIsGrabbing;

typedef struct
{
    ZvImage img;
    int camId;
    int bufId;
}ZvTPCamRetrieve;

typedef struct
{
    int camId;
}ZvTPCamReset;

typedef struct
{
    int camId;
    char *name;
    char *value;
    int maxValLen;
}ZvTPCamGetParam;

typedef struct
{
    int camId;
    char *name;
    char *value;
}ZvTPCamSetParam;

typedef struct
{
    ZvImage img;
    char *fileName;
    int type;
}ZvTPFileReadImage;

typedef struct
{
    ZvImage img;
    char *fileName;
    int param;
}ZvTPFileWriteImage;

typedef struct
{
    ZvMatrix mat;
    char *fileName;
    char *nodeName;
    int type;
}ZvTPFileReadMatrix;

typedef struct
{
    ZvMatrix mat;
    char *fileName;
    char *nodeName;
    int type;
}ZvTPFileWriteMatrix;

typedef struct
{
    ZvImage img;
    int width;
    int height;
    int type;
    int channel;
    double *element;
}ZvTPImgGenConst;

typedef struct
{
    ZvImage img;
    int width;
    int height;
    int type;
    int channel;
    void *data;
}ZvTPImgGenData;

typedef struct
{
    ZvImage img;
    void *buf;
    int size;
    bool isAlign;
}ZvTPImgGetData;

typedef struct
{
    ZvImage img;
    void *buf;
}ZvTPImgSetData;

typedef struct
{
    ZvImage img;
    ZvImage sub;
    int x;
    int y;
    int width;
    int height;
}ZvTPImgGetSub;

typedef struct
{
    ZvImage img;
    ZvImage sub;
    int x;
    int y;
}ZvTPImgSetSub;

typedef struct
{
    ZvImage src;
    ZvImage dst;
    int dstType;
    double mult;
    double add;
}ZvTPImgConvert;

typedef struct
{
    ZvImage src;
    ZvImage dst;
}ZvTPImgCopy;

typedef struct
{
    ZvImage src;
    ZvImage dst1;
    ZvImage dst2;
}ZvTPImgSplit2;

typedef struct
{
    ZvImage src;
    ZvImage dst1;
    ZvImage dst2;
    ZvImage dst3;
}ZvTPImgSplit3;

typedef struct
{
    ZvImage src;
    ZvImage dst1;
    ZvImage dst2;
    ZvImage dst3;
    ZvImage dst4;
}ZvTPImgSplit4;

typedef struct
{
    ZvImage src1;
    ZvImage src2;
    ZvImage dst;
}ZvTPImgMerge2;

typedef struct
{
    ZvImage src1;
    ZvImage src2;
    ZvImage src3;
    ZvImage dst;
}ZvTPImgMerge3;

typedef struct
{
    ZvImage src1;
    ZvImage src2;
    ZvImage src3;
    ZvImage src4;
    ZvImage dst;
}ZvTPImgMerge4;

typedef struct
{
    ZvMatrix mat;
    int rows;
    int cols;
    double value;
}ZvTPMatGenConst;

typedef struct
{
    ZvMatrix mat;
    int size;
}ZvTPMatGenEye;

typedef struct
{
    ZvMatrix mat;
    int rows;
    int cols;
    double *data;
}ZvTPMatGenData;

typedef struct
{
    ZvMatrix mat;
    int row;
    double *data;
    int bufLen;
}ZvTPMatGetRow;

typedef struct
{
    ZvMatrix mat;
    int row;
    double *data;
}ZvTPMatSetRow;

typedef struct
{
    ZvMatrix mat;
    int col;
    double * data;
    int bufLen;
}ZvTPMatGetCol;

typedef struct
{
    ZvMatrix mat;
    int col;
    double * data;
}ZvTPMatSetCol;

typedef struct
{
    ZvMatrix mat;
    double *data;
    int bufLen;
}ZvTPMatGetData;

typedef struct
{
    ZvMatrix mat;
    double *data;
}ZvTPMatSetData;

typedef struct
{
    ZvMatrix mat;
    ZvMatrix sub;
    int x;
    int y;
    int width;
    int height;
}ZvTPMatGetSub;

typedef struct
{
    ZvMatrix mat;
    ZvMatrix sub;
    int x;
    int y;
}ZvTPMatSetSub;

typedef struct
{
    ZvMatrix src;
    ZvMatrix dst;
}ZvTPMatCopy;

typedef struct
{
    ZvContour cont;
    double *pts;
    int *ptsLen;
}ZvTPContGetPointsAll;

typedef struct
{
    ZvImage img;
    ZvContList contList;
    int mode;
    int appro;
}ZvTPContGen;

typedef struct
{
    ZvContour cont;
    ZvMatrix mat;
}ZvTPContToMatrix;

typedef struct
{
    ZvContour cont;
    ZvMatrix mat;
}ZvTPContFromMatrix;

typedef struct
{
    ZvContour cont;
    bool isOriented;
    double *area;
}ZvTPContArea;

typedef struct
{
    ZvContour cont;
    bool isClosed;
    double *len;
}ZvTPContLength;

typedef struct
{
    ZvContour cont;
    double *center;
}ZvTPContCenter;

typedef struct
{
    ZvContour cont;
    int *isConvex;
}ZvTPContIsConvex;

typedef struct
{
    ZvContour cont;
    double *convexity;
}ZvTPContConvexity;

typedef struct
{
    ZvContour cont;
    double *value;
}ZvTPContCircularity;

typedef struct
{
    ZvContour cont;
    double *value;
}ZvTPContCompactness;

typedef struct
{
    ZvContour cont;
    int *rect;
}ZvTPContSmallestRect;

typedef struct
{
    ZvContour cont;
    double *rect2;
}ZvTPContSmallestRect2;

typedef struct
{
    ZvContour cont;
    double *circle;
}ZvTPContSmallestCircle;

typedef struct
{
    ZvContour cont;
    double *major;
    double * minor;
    double *angle;
}ZvTPContEllipticAxis;

typedef struct
{
    ZvContour cont;
    int *ptIdx;
    int *bufLen;
}ZvTPContConvexHullIdx;

typedef struct
{
    ZvContour cont;
    ZvContour poly;
    double epsilon;
    bool isClosed;
}ZvTPContApproxPoly;

typedef struct
{
    ZvContList contlist;
    int feature;
    bool isInc;
}ZvTPContSort;

typedef struct
{
    ZvContList contlist;
    int feature;
    double min;
    double max;
    bool isInvert;
}ZvTPContFilter;

typedef struct
{
    ZvContour cont;
    int type;
    int orderX;
    int orderY;
    double *m;
}ZvTPContMoments;

typedef struct
{
    ZvContour cont;
    double *hu;
}ZvTPContHuMoments;

typedef struct
{
    ZvContour contSrc;
    ZvContour contDst;
    ZvMatrix mat;
}ZvTPContAffine;

typedef struct
{
    ZvContour contSrc;
    ZvContour contDst;
    ZvMatrix mat;
}ZvTPContPerspective;

typedef struct
{
    ZvObject src;
    ZvObject dst;
}ZvTPArithAbs;

typedef struct
{
    ZvObject src1;
    ZvObject src2;
    ZvObject dst;
    double mult;
}ZvTPArithAbsDiff;

typedef struct
{
    ZvObject src1;
    ZvObject src2;
    ZvObject dst;
    double mult;
    double add;
}ZvTPArithAdd;

typedef struct
{
    ZvObject src1;
    ZvObject src2;
    ZvObject dst;
    double mult;
    double add;
}ZvTPArithSub;

typedef struct
{
    ZvObject src1;
    ZvObject src2;
    ZvObject dst;
    double mult;
    double add;
}ZvTPArithMul;

typedef struct
{
    ZvObject src1;
    ZvObject src2;
    ZvObject dst;
    double mult;
    double add;
}ZvTPArithDiv;

typedef struct
{
    ZvObject src;
    ZvObject dst;
    double mult;
    double add;
}ZvTPArithScale;

typedef struct
{
    ZvObject src1;
    ZvObject src2;
    ZvObject dst;
    double weight1;
    double weight2;
    double add;
}ZvTPArithAddWeighted;

typedef struct
{
    ZvObject src;
    ZvObject dst;
}ZvTPArithSin;

typedef struct
{
    ZvObject src;
    ZvObject dst;
}ZvTPArithCos;

typedef struct
{
    ZvObject src;
    ZvObject dst;
}ZvTPArithTan;

typedef struct
{
    ZvObject src;
    ZvObject dst;
}ZvTPArithAsin;

typedef struct
{
    ZvObject src;
    ZvObject dst;
}ZvTPArithAcos;

typedef struct
{
    ZvObject src;
    ZvObject dst;
}ZvTPArithAtan;

typedef struct
{
    ZvObject y;
    ZvObject x;
    ZvObject dst;
}ZvTPArithAtan2;

typedef struct
{
    ZvObject src;
    ZvObject dst;
    int baseType;
}ZvTPArithExp;

typedef struct
{
    ZvObject src;
    ZvObject dst;
    int baseType;
}ZvTPArithLog;

typedef struct
{
    ZvObject src;
    ZvObject dst;
    double exponent;
}ZvTPArithPow;

typedef struct
{
    ZvObject src;
    ZvObject dst;
}ZvTPArithSqrt;

typedef struct
{
    ZvObject src1;
    ZvObject src2;
    ZvImage dst;
    int op;
}ZvTPArithCompare;

typedef struct
{
    ZvObject src1;
    ZvObject src2;
    ZvObject dst;
}ZvTPArithMax;

typedef struct
{
    ZvObject src1;
    ZvObject src2;
    ZvObject dst;
}ZvTPArithMin;

typedef struct
{
    ZvObject src1;
    ZvObject dst;
    double *scalar;
}ZvTPArithMaxS;

typedef struct
{
    ZvObject src1;
    ZvObject dst;
    double *scalar;
}ZvTPArithMinS;

typedef struct
{
    ZvObject x;
    ZvObject y;
    ZvObject magnitude;
}ZvTPArithMagnitude;

typedef struct
{
    ZvObject x;
    ZvObject y;
    ZvObject radian;
}ZvTPArithPhase;

typedef struct
{
    ZvObject src;
    ZvObject dst;
}ZvTPArithIntegral;

typedef struct
{
    ZvObject src;
    ZvObject dst;
    ZvObject dstSqrt;
}ZvTPArithIntegral2;

typedef struct
{
    ZvImage src1;
    ZvImage src2;
    ZvImage dst;
}ZvTPArithAnd;

typedef struct
{
    ZvImage src1;
    ZvImage src2;
    ZvImage dst;
}ZvTPArithOr;

typedef struct
{
    ZvImage src;
    ZvImage dst;
}ZvTPArithNot;

typedef struct
{
    ZvImage src1;
    ZvImage src2;
    ZvImage dst;
}ZvTPArithXor;

typedef struct
{
    ZvMatrix src;
    ZvMatrix dst;
}ZvTPArithTranspose;

typedef struct
{
    ZvMatrix src;
    ZvMatrix dst;
    int method;
}ZvTPArithInvert;

typedef struct
{
    ZvMatrix mat;
    int normType;
    double *value;
}ZvTPArithNorm;

typedef struct
{
    ZvMatrix mat1;
    ZvMatrix mat2;
    ZvMatrix dst;
}ZvTPArithMatrixMult;

typedef struct
{
    ZvMatrix src;
    ZvMatrix eigenvalues;
    ZvMatrix eigenvectors;
    bool isSymmetric;
}ZvTPArithEigen;

typedef struct
{
    ZvObject src;
    int *cnt;
}ZvTPArithZeroCount;

typedef struct
{
    ZvObject src;
    double * sum;
}ZvTPArithSum;

typedef struct
{
    ZvObject src;
    ZvObject dst;
    int type;
}ZvTPArithStatRow;

typedef struct
{
    ZvObject src;
    ZvObject dst;
    int type;
}ZvTPArithStatCol;

typedef struct
{
    ZvObject src;
    double *mean;
}ZvTPArithMean;

typedef struct
{
    ZvObject src;
    double *mean;
    double *stdDev;
}ZvTPArithMeanSdev;

typedef struct
{
    ZvObject src;
    double *value;
    int *pos;
}ZvTPArithMinMaxLoc;

typedef struct
{
    ZvImage img;
    ZvMatrix hist;
    int size;
    double low;
    double upper;
}ZvTPArithHist;

typedef struct
{
    ZvImage src;
    ZvImage dst;
    int type;
}ZvTPIpMirror;

typedef struct
{
    ZvImage src;
    ZvImage dst;
    double angle;
    int interp;
}ZvTPIpRotate;

typedef struct
{
    ZvImage src;
    ZvImage dst;
    double scaleW;
    double scaleH;
    int interp;
}ZvTPIpZoom;

typedef struct
{
    ZvImage src;
    ZvImage dst;
    int dstW;
    int dstH;
    int interp;
}ZvTPIpResize;

typedef struct
{
    ZvImage src;
    ZvImage dst;
    ZvMatrix mat;
    int dstW;
    int dstH;
    int interp;
    char *border;
}ZvTPIpAffine;

typedef struct
{
    ZvImage src;
    ZvImage dst;
    ZvMatrix mat;
    int dstW;
    int dstH;
    int interp;
    char *border;
}ZvTPIpPerspective;

typedef struct
{
    ZvImage binImg;
    int type;
    int orderX;
    int orderY;
    double *m;
}ZvTPIpMoments;

typedef struct
{
    ZvImage rgb;
    ZvImage gray;
}ZvTPIpRgbToGray;

typedef struct
{
    ZvImage gray;
    ZvImage rgb;
}ZvTPIpGrayToRgb;

typedef struct
{
    ZvImage color;
    ZvImage rgb;
    int colorSpace;
}ZvTPIpColorToRgb;

typedef struct
{
    ZvImage rgb;
    ZvImage color;
    int colorSpace;
}ZvTPIpRgbToColor;

typedef struct
{
    ZvImage bayer;
    ZvImage rgb;
    int bayerType;
}ZvTPIpBayerToRgb;

typedef struct
{
    ZvImage src;
    ZvImage dst;
    int size;
}ZvTPIpMedianBlur;

typedef struct
{
    ZvImage src;
    ZvImage dst;
    int size;
}ZvTPIpMeanBlur;

typedef struct
{
    ZvImage src;
    ZvImage dst;
    int size;
}ZvTPIpGaussBlur;

typedef struct
{
    ZvImage src;
    ZvImage dst;
    double sigmaSpace;
    double sigmaRange;
}ZvTPIpBilateralFilter;

typedef struct
{
    ZvImage src;
    ZvImage dst;
    int dx;
    int dy;
    int size;
}ZvTPIpSobel;

typedef struct
{
    ZvImage src;
    ZvImage dst;
    int dx;
    int dy;
}ZvTPIpScharr;

typedef struct
{
    ZvImage src;
    ZvImage dst;
    int size;
}ZvTPIpLaplace;

typedef struct
{
    ZvImage img;
    ZvImage dst;
    double thresh1;
    double thresh2;
    int size;
}ZvTPIpCanny;

typedef struct
{
    ZvImage src;
    ZvImage dst;
}ZvTPIpEqualizeHist;

typedef struct
{
    ZvImage src;
    ZvImage dst;
    int seWidth;
    int seHeight;
}ZvTPIpDilate;

typedef struct
{
    ZvImage src;
    ZvImage dst;
    int seWidth;
    int seHeight;
}ZvTPIpErode;

typedef struct
{
    ZvImage src;
    ZvImage dst;
    int seWidth;
    int seHeight;
}ZvTPIpOpening;

typedef struct
{
    ZvImage src;
    ZvImage dst;
    int seWidth;
    int seHeight;
}ZvTPIpClosing;

typedef struct
{
    ZvImage kernel;
    int shape;
    int sizeX;
    int sizeY;
    int anchorX;
    int anchorY;
}ZvTPIpMorphSe;

typedef struct
{
    ZvImage src;
    ZvImage dst;
    ZvImage kernel;
    int op;
    int anchorX;
    int anchorY;
    int iter;
    char *border;
}ZvTPIpMorph;

typedef struct
{
    ZvImage src;
    ZvImage label;
    int connectivity;
}ZvTPIpLabel;

typedef struct
{
    ZvImage src;
    ZvImage dst;
    double thresh0;
    double thresh1;
    bool isInv;
}ZvTPIpThreshold;

typedef struct
{
    ZvImage src;
    ZvImage thresh;
    ZvImage dst;
    double offset;
    bool isInv;
}ZvTPIpAdpThreshold;

typedef struct
{
    ZvImage src;
    ZvImage dst;
    double *thresh;
}ZvTPIpAutoThreshold;

typedef struct
{
    ZvImage img;
    ZvImage templ;
    int *pos;
    int method;
}ZvTPMatchFastTempl;

typedef struct
{
    ZvImage img;
    ZvImage templ;
    double minScore;
    double *mRst;
    bool isSubPix;
    int polar;
}ZvTPMatchBestTempl;

typedef struct
{
    ZvImage img;
    ZvImage templ;
    ZvMatrix matches;
    double minScore;
    int nums;
    double minDist;
    bool isSubPix;
    int polar;
}ZvTPMatchMultiTempl;

typedef struct _ZvTPMatchNccCreate
{
    ZvModel mod;
    ZvImage templ;
    double angleStart;
    double angleExt;
    double angleStep;
    int numLevel;
}ZvTPMatchNccCreate;

typedef struct _ZvTPMatchNccFind
{
    ZvModel mod;
    ZvImage img;
    ZvMatrix matchs;
    int NumLevel;
    double minScore;
    double *x;
    double *y;
    double minDist;
    int isSubPix;
}ZvTPMatchNccFind;


typedef struct
{
    ZvImage img;
    ZvMatrix proj;
    void *mr;
}ZvTPMeasProjection;

typedef struct
{
    ZvImage img;
    ZvMatrix pts;
    void *mr;
    int filterSize;
    double thresh;
    int type;
    int select;
}ZvTPMeasPos;

typedef struct
{
    ZvImage img;
    ZvMatrix pairs;
    void *mr;
    int filterSize;
    double thresh;
    int type;
    int select;
}ZvTPMeasPairs;

typedef struct
{
    ZvImage img;
    void *mr;
    double *line;
    ZvMatrix pts;
}ZvTPMeasLine;

typedef struct
{
    ZvImage img;
    void *mr;
    double *circle;
    ZvMatrix pts;
}ZvTPMeasCircle;

typedef struct
{
    ZvImage img;
    ZvMatrix lines;
    double rho;
    double theta;
    int thresh;
    double minLinelen;
    double maxLineGap;
}ZvTPFeatHoughLine;

typedef struct
{
    ZvImage img;
    ZvMatrix circles;
    double minDist;
    double param1;
    double param2;
    double minR;
    double maxR;
}ZvTPFeatHoughCircle;

typedef struct
{
    ZvMatrix mat;
    double *from;
    double *to;
}ZvTPTkGetRigid;

typedef struct
{
    ZvMatrix mat;
    double xFrom;
    double yFrom;
    double angleFrom;
    double xTo;
    double yTo;
    double angleTo;
}ZvTPTkGetRigidVector;

typedef struct
{
    ZvMatrix mat;
    double *from;
    double *to;
}ZvTPTkGetSimilarity;

typedef struct
{
    ZvMatrix mat;
    double *from;
    double *to;
}ZvTPTkGetAffine;

typedef struct
{
    ZvMatrix from;
    ZvMatrix to;
    ZvMatrix mat;
    double thresh;
    double confidence;
    bool * isInliers;
}ZvTPTkEstimateSimilarity;

typedef struct
{
    ZvMatrix from;
    ZvMatrix to;
    ZvMatrix mat;
    double thresh;
    double confidence;
    bool * isInliers;
}ZvTPTkEstimateAffine;

typedef struct
{
    ZvMatrix mat;
    double *from;
    double *to;
    int ptNum;
}ZvTPTkAffineTrans;

typedef struct
{
    ZvMatrix mat;
    double *from;
    double *to;
}ZvTPTkGetProjective;

typedef struct
{
    ZvMatrix mat;
    double *from;
    double *to;
    int num;
}ZvTPTkProjectiveTrans2d;

typedef struct
{
    ZvMatrix mat;
    double *from;
    double *to;
    int num;
}ZvTPTkProjectiveTrans3d;

typedef struct
{
    ZvContour cont;
    double px;
    double py;
    double * dist;
}ZvTPTkDistanceContP;

typedef struct
{
    ZvMatrix pts;
    double *line;
}ZvTPTkFitLine2D;

typedef struct
{
    ZvMatrix pts;
    double *ellipse;
}ZvTPTkFitEllipse;

typedef struct
{
    ZvMatrix pts;
    double R1X;
    double R1Y;
    double R1W;
    double R1H;
    double R1Angle;
    double R2X;
    double R2Y;
    double R2W;
    double R2H;
    double R2Angle;
}ZvTPTkIntersectRect2;

typedef struct
{
    ZvMatrix pts;
    double *line;
    int method;
    double reps;
    double aeps;
}ZvTPTkFitLineEx;

typedef struct
{
    ZvMatrix pts;
    double *ellipse;
    int method;
}ZvTPTkFitEllipseEx;

typedef struct
{
    ZvMatrix pts;
    int order;
    double *param;
}ZvTPTkFitPolyn;

typedef struct
{
    ZvImage img;
    double x1;
    double y1;
    double x2;
    double y2;
    int color;
}ZvTPDraLine;

typedef struct
{
    ZvImage img;
    double x;
    double y;
    double w;
    double h;
    int color;
}ZvTPDraRect;

typedef struct
{
    ZvImage img;
    double cx;
    double cy;
    double width;
    double height;
    double angle;
    int color;
}ZvTPDraRect2;

typedef struct
{
    ZvImage img;
    double cx;
    double cy;
    double r;
    int color;
}ZvTPDraCircle;

typedef struct
{
    ZvImage img;
    double cx;
    double cy;
    double xR;
    double yR;
    double angle;
    int color;
}ZvTPDraEllipse;

typedef struct
{
    ZvImage img;
    double cx;
    double cy;
    double xR;
    double yR;
    double angle;
    double angleStart;
    double angleEnd;
    int color;
}ZvTPDraEllipseArc;

typedef struct
{
    ZvImage img;
    double x1;
    double y1;
    double x2;
    double y2;
    int color;
    int size;
}ZvTPDraArrow;

typedef struct
{
    ZvImage img;
    ZvMatrix pts;
    bool isClosed;
    int color;
}ZvTPDraPolygon;

typedef struct
{
    ZvImage img;
    ZvContour cont;
    int color;
}ZvTPDraContour;

typedef struct
{
    ZvImage img;
    double x;
    double y;
    int type;
    int size;
    int color;
}ZvTPDraMarker;

typedef struct
{
    ZvImage img;
    char * text;
    double x;
    double y;
    double scale;
    int color;
}ZvTPDraText;

typedef struct
{
    ZvImage img;
    ZvImage mask;
}ZvTPDraMask;

typedef struct
{
    ZvImage img;
    void *mr;
    int color;
    int subColor;
}ZvTPDraMeasurer;


#ifdef __cplusplus
}
#endif

#endif
