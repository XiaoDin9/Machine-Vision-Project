#ifndef ZV_FILE_H
#define ZV_FILE_H


#ifdef __cplusplus
extern "C"{
#endif

int zv_file_readImage(ZvImage img, char *fileName, int type);
int zv_file_writeImage(ZvImage img, char *fileName, int param);
int zv_file_readMatrix(ZvMatrix mat, char *fileName, char *nodeName, int type);
int zv_file_writeMatrix(ZvMatrix mat, char *fileName, char *nodeName, int type);

#ifdef __cplusplus
}
#endif

#endif
