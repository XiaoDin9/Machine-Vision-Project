/*************************************************************
该文件为自动生成文件，如果修改请注意备份，重新生成将被覆盖
////由zv_module_gen.py生成，需要zv_module_templ.py模块内的
////固定字符串定义和zv_module.h文件内的函数声明，声明需要符
////合特定格式
*************************************************************/

#ifndef ZV_TASK_H
#define ZV_TASK_H

#ifdef __cplusplus
extern "C"
{
#endif


typedef void(*ZvTaskFun)(void *);

int zv_task_init(bool isBlocking);
int zv_task_registerRun(ZvTaskFun fun, void *param, int paramSize);

void zv_task_cam_scan(void *param);
void zv_task_cam_getInfo(void *param);
void zv_task_cam_open(void *param);
void zv_task_cam_status(void *param);
void zv_task_cam_close(void *param);
void zv_task_cam_payloadSize(void *param);
void zv_task_cam_grab(void *param);
void zv_task_cam_getROI(void *param);
void zv_task_cam_setROI(void *param);
void zv_task_cam_getExposure(void *param);
void zv_task_cam_setExposure(void *param);
void zv_task_cam_startGrabbing(void *param);
void zv_task_cam_isGrabbing(void *param);
void zv_task_cam_retrieve(void *param);
void zv_task_cam_reset(void *param);
void zv_task_cam_getParam(void *param);
void zv_task_cam_setParam(void *param);
void zv_task_file_readImage(void *param);
void zv_task_file_writeImage(void *param);
void zv_task_file_readMatrix(void *param);
void zv_task_file_writeMatrix(void *param);
void zv_task_img_genConst(void *param);
void zv_task_img_genData(void *param);
void zv_task_img_getData(void *param);
void zv_task_img_setData(void *param);
void zv_task_img_getSub(void *param);
void zv_task_img_setSub(void *param);
void zv_task_img_convert(void *param);
void zv_task_img_copy(void *param);
void zv_task_img_split2(void *param);
void zv_task_img_split3(void *param);
void zv_task_img_split4(void *param);
void zv_task_img_merge2(void *param);
void zv_task_img_merge3(void *param);
void zv_task_img_merge4(void *param);
void zv_task_mat_genConst(void *param);
void zv_task_mat_genEye(void *param);
void zv_task_mat_genData(void *param);
void zv_task_mat_getRow(void *param);
void zv_task_mat_setRow(void *param);
void zv_task_mat_getCol(void *param);
void zv_task_mat_setCol(void *param);
void zv_task_mat_getData(void *param);
void zv_task_mat_setData(void *param);
void zv_task_mat_getSub(void *param);
void zv_task_mat_setSub(void *param);
void zv_task_mat_copy(void *param);
void zv_task_cont_getPointsAll(void *param);
void zv_task_cont_gen(void *param);
void zv_task_cont_toMatrix(void *param);
void zv_task_cont_fromMatrix(void *param);
void zv_task_cont_area(void *param);
void zv_task_cont_length(void *param);
void zv_task_cont_center(void *param);
void zv_task_cont_isConvex(void *param);
void zv_task_cont_convexity(void *param);
void zv_task_cont_circularity(void *param);
void zv_task_cont_compactness(void *param);
void zv_task_cont_smallestRect(void *param);
void zv_task_cont_smallestRect2(void *param);
void zv_task_cont_smallestCircle(void *param);
void zv_task_cont_ellipticAxis(void *param);
void zv_task_cont_convexHullIdx(void *param);
void zv_task_cont_approxPoly(void *param);
void zv_task_cont_sort(void *param);
void zv_task_cont_filter(void *param);
void zv_task_cont_moments(void *param);
void zv_task_cont_huMoments(void *param);
void zv_task_cont_affine(void *param);
void zv_task_cont_perspective(void *param);
void zv_task_arith_abs(void *param);
void zv_task_arith_absDiff(void *param);
void zv_task_arith_add(void *param);
void zv_task_arith_sub(void *param);
void zv_task_arith_mul(void *param);
void zv_task_arith_div(void *param);
void zv_task_arith_scale(void *param);
void zv_task_arith_addWeighted(void *param);
void zv_task_arith_sin(void *param);
void zv_task_arith_cos(void *param);
void zv_task_arith_tan(void *param);
void zv_task_arith_asin(void *param);
void zv_task_arith_acos(void *param);
void zv_task_arith_atan(void *param);
void zv_task_arith_atan2(void *param);
void zv_task_arith_exp(void *param);
void zv_task_arith_log(void *param);
void zv_task_arith_pow(void *param);
void zv_task_arith_sqrt(void *param);
void zv_task_arith_compare(void *param);
void zv_task_arith_max(void *param);
void zv_task_arith_min(void *param);
void zv_task_arith_maxS(void *param);
void zv_task_arith_minS(void *param);
void zv_task_arith_magnitude(void *param);
void zv_task_arith_phase(void *param);
void zv_task_arith_integral(void *param);
void zv_task_arith_integral2(void *param);
void zv_task_arith_and(void *param);
void zv_task_arith_or(void *param);
void zv_task_arith_not(void *param);
void zv_task_arith_xor(void *param);
void zv_task_arith_transpose(void *param);
void zv_task_arith_invert(void *param);
void zv_task_arith_norm(void *param);
void zv_task_arith_matrixMult(void *param);
void zv_task_arith_eigen(void *param);
void zv_task_arith_zeroCount(void *param);
void zv_task_arith_sum(void *param);
void zv_task_arith_statRow(void *param);
void zv_task_arith_statCol(void *param);
void zv_task_arith_mean(void *param);
void zv_task_arith_meanSdev(void *param);
void zv_task_arith_minMaxLoc(void *param);
void zv_task_arith_hist(void *param);
void zv_task_ip_mirror(void *param);
void zv_task_ip_rotate(void *param);
void zv_task_ip_zoom(void *param);
void zv_task_ip_resize(void *param);
void zv_task_ip_affine(void *param);
void zv_task_ip_perspective(void *param);
void zv_task_ip_moments(void *param);
void zv_task_ip_rgbToGray(void *param);
void zv_task_ip_grayToRgb(void *param);
void zv_task_ip_colorToRgb(void *param);
void zv_task_ip_rgbToColor(void *param);
void zv_task_ip_bayerToRgb(void *param);
void zv_task_ip_medianBlur(void *param);
void zv_task_ip_meanBlur(void *param);
void zv_task_ip_gaussBlur(void *param);
void zv_task_ip_bilateralFilter(void *param);
void zv_task_ip_sobel(void *param);
void zv_task_ip_scharr(void *param);
void zv_task_ip_laplace(void *param);
void zv_task_ip_canny(void *param);
void zv_task_ip_equalizeHist(void *param);
void zv_task_ip_dilate(void *param);
void zv_task_ip_erode(void *param);
void zv_task_ip_opening(void *param);
void zv_task_ip_closing(void *param);
void zv_task_ip_morphSe(void *param);
void zv_task_ip_morph(void *param);
void zv_task_ip_label(void *param);
void zv_task_ip_threshold(void *param);
void zv_task_ip_adpThreshold(void *param);
void zv_task_ip_autoThreshold(void *param);
void zv_task_match_fastTempl(void *param);
void zv_task_match_bestTempl(void *param);
void zv_task_match_multiTempl(void *param);
void zv_task_match_nccCreate(void *param);
void zv_task_match_nccFind(void *param);
void zv_task_meas_projection(void *param);
void zv_task_meas_pos(void *param);
void zv_task_meas_pairs(void *param);
void zv_task_meas_line(void *param);
void zv_task_meas_circle(void *param);
void zv_task_feat_houghLine(void *param);
void zv_task_feat_houghCircle(void *param);
void zv_task_tk_getRigid(void *param);
void zv_task_tk_getRigidVector(void *param);
void zv_task_tk_getSimilarity(void *param);
void zv_task_tk_getAffine(void *param);
void zv_task_tk_estimateSimilarity(void *param);
void zv_task_tk_estimateAffine(void *param);
void zv_task_tk_affineTrans(void *param);
void zv_task_tk_getProjective(void *param);
void zv_task_tk_projectiveTrans2d(void *param);
void zv_task_tk_projectiveTrans3d(void *param);
void zv_task_tk_distanceContP(void *param);
void zv_task_tk_fitLine2D(void *param);
void zv_task_tk_fitEllipse(void *param);
void zv_task_tk_intersectRect2(void *param);
void zv_task_tk_fitLineEx(void *param);
void zv_task_tk_fitEllipseEx(void *param);
void zv_task_tk_fitPolyn(void *param);
void zv_task_dra_line(void *param);
void zv_task_dra_rect(void *param);
void zv_task_dra_rect2(void *param);
void zv_task_dra_circle(void *param);
void zv_task_dra_ellipse(void *param);
void zv_task_dra_ellipseArc(void *param);
void zv_task_dra_arrow(void *param);
void zv_task_dra_polygon(void *param);
void zv_task_dra_contour(void *param);
void zv_task_dra_marker(void *param);
void zv_task_dra_text(void *param);
void zv_task_dra_mask(void *param);
void zv_task_dra_measurer(void *param);

#ifdef __cplusplus
}
#endif

#endif
