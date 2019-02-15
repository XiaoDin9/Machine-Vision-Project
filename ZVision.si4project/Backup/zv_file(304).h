#ifndef ZV_FILE_H
#define ZV_FILE_H


#ifdef __cplusplus
extern "C"{
#endif

int zvReadImage(ZvImage img, char *filename, int type);
int zvWriteImage(ZvImage img, char *filename, int *params, int num);
int zvReadMatrix(ZvMatrix mat, char *filename, char *_nodeName, int type);
int zvWriteMatrix(ZvMatrix mat, char *filename, char *_nodeName, int type);


#ifdef __cplusplus
}
#endif

#endif