/**
    @brief Header file of ability cv function definition.

    @file ab_cv_api.h

    @note Nothing.
*/

#ifndef _AB_CV_API_H_
#define _AB_CV_API_H_

/********************************************************************
    INCLUDE FILES
*********************************************************************/
#include "ab_cv_types.h"

/* Note: reterun error code reference CAMERA_CV_API_RESULT_ET */

extern int32_t ab_cv_interface_init(void);
#define camera_cv_api_init() ab_cv_interface_init()
    
extern int32_t ab_cv_interface_deinit(void);
#define camera_cv_api_deinit() ab_cv_interface_deinit()

extern int32_t ab_cv_api_response_memory_free(void** ppv_mem_ptr);
#define camera_cv_api_mem_free(ppv_mem_ptr) ab_cv_api_response_memory_free(ppv_mem_ptr)

#if CAMERA_CV_ALGORITHM_API_ENABLE
/********************* Algorithm API *********************/
// camera_cv_api_warp_affine
extern int32_t ab_cv_api_warp_affine(IN CAMERA_CV_API_MAT_ST* ps_src, OUT CAMERA_CV_API_MAT_ST* ps_dst, IN CAMERA_CV_API_MAT_ST* ps_transform, IN CAMERA_CV_API_SIZE_ST* ps_dsize);
#define camera_cv_api_warp_affine(src, dst, transform, dsize) \
    ab_cv_api_warp_affine(src, dst, transform, dsize)

// camera_cv_api_resize
extern int32_t ab_cv_api_resize(IN CAMERA_CV_API_MAT_ST* ps_src, OUT CAMERA_CV_API_MAT_ST* ps_dst, IN CAMERA_CV_API_SIZE_ST* ps_dsize);
#define camera_cv_api_resize(src, dst, dsize) \
    ab_cv_api_resize(src, dst, dsize)

extern int32_t ab_cv_api_warp_perspective(IN CAMERA_CV_API_MAT_ST* ps_src, OUT CAMERA_CV_API_MAT_ST* ps_dst, IN CAMERA_CV_API_MAT_ST* ps_transform, IN CAMERA_CV_API_SIZE_ST* ps_dsize);
#define camera_cv_api_warp_perspective(src, dst, transform, dsize) \
    ab_cv_api_warp_perspective(src, dst, transform, dsize)

// camera_cv_api_fast_create
extern CAMERA_CV_API_FEATURE_2D_ST* ab_cv_api_fast_create(IN int i_threshold, IN int i_non_max_suppression);
#define camera_cv_api_fast_create(threshold, non_max_suppression) \
    ab_cv_api_fast_create(threshold, non_max_suppression)

extern CAMERA_CV_API_FEATURE_2D_ST* ab_cv_api_gftt_create(IN int i_max_corners, IN double d_quality_level, IN double d_min_distance, IN double d_k);
#define camera_cv_api_gftt_create(max_corners, quality_level, min_distance, k) \
    ab_cv_api_gftt_create(max_corners, quality_level, min_distance, k)

extern CAMERA_CV_API_FEATURE_2D_ST* ab_cv_api_orb_create(IN int i_n_features, IN int i_score_type, IN int i_fast_threshold);
#define camera_cv_api_orb_create(n_features, score_type, fast_threshold) \
    ab_cv_api_orb_create(n_features, score_type, fast_threshold)

extern int32_t ab_cv_api_feature_destroy(IN OUT CAMERA_CV_API_FEATURE_2D_ST** pps_instance);
#define camera_cv_api_feature_destroy(instance) \
    ab_cv_api_feature_destroy(instance)

extern int32_t ab_cv_api_feature_detect(IN CAMERA_CV_API_FEATURE_2D_ST* ps_instance, IN CAMERA_CV_API_MAT_ST* ps_image, OUT CAMERA_CV_API_KEY_POINT_VECTOR_ST* ps_keypoints);
#define camera_cv_api_feature_detect(instance, image, keypoints) \
    ab_cv_api_feature_detect(instance, image, keypoints)

extern int32_t ab_cv_api_feature_detect_and_compute(IN CAMERA_CV_API_FEATURE_2D_ST* ps_instance, IN CAMERA_CV_API_MAT_ST* ps_image, OUT CAMERA_CV_API_KEY_POINT_VECTOR_ST* ps_keypoints, OUT CAMERA_CV_API_MAT_ST* ps_descriptors);
#define camera_cv_api_feature_detect_and_compute(instance, image, keypoints, descriptors) \
    ab_cv_api_feature_detect_and_compute(instance, image, keypoints, descriptors)

extern int32_t ab_cv_api_bf_matcher_match(IN CAMERA_CV_API_MAT_ST* ps_query_descritor, IN CAMERA_CV_API_MAT_ST* ps_train_descritor, OUT CAMERA_CV_API_MATCH_VECTOR_ST* ps_matches);
#define camera_cv_api_bf_matcher_match(query_descritor, train_descritor, matches) \
    ab_cv_api_bf_matcher_match(query_descritor, train_descritor, matches)

extern int32_t ab_cv_api_bf_matcher_radius_match(IN CAMERA_CV_API_MAT_ST* ps_query_descritor, IN CAMERA_CV_API_MAT_ST* ps_train_descritor, OUT CAMERA_CV_API_MATCH_VECTOR_ST* ps_matches, IN int i_max_distance, IN float f_ratio);
#define camera_cv_api_bf_matcher_radius_match(query_descritor, train_descritor, matches, max_distance, ratio) \
    ab_cv_api_bf_matcher_radius_match(query_descritor, train_descritor, matches, max_distance, ratio)

extern int32_t ab_cv_api_calc_optical_flow_pyr_lk(IN CAMERA_CV_API_MAT_ST* ps_prev_image, IN CAMERA_CV_API_MAT_ST* ps_next_image, IN CAMERA_CV_API_KEY_POINT_VECTOR_ST* ps_prev_pts, OUT CAMERA_CV_API_KEY_POINT_VECTOR_ST* ps_next_pts, OUT uint8_t** ppuc_status, IN CAMERA_CV_API_SIZE_ST* ps_win_size, IN int i_max_level);
#define camera_cv_api_calc_optical_flow_pyr_lk(prev_image, next_image, prev_pts, next_pts, status, win_size, max_level) \
    ab_cv_api_calc_optical_flow_pyr_lk(prev_image, next_image, prev_pts, next_pts, status, win_size, max_level)

//camera_cv_api_pyr_down    -TBD
//camera_cv_api_pyr_up      -TBD
//camera_cv_api_laplacian   -TBD
//camera_cv_api_canny       -TBD
#endif

#if CAMERA_CV_FEATURE_API_ENABLE
/********************* Feature API *********************/

//camera_cv_api_corner_min_eigen_val    -TBD
//camera_cv_api_corner_harris           -TBD
#endif

#if CAMERA_CV_FORMAT_API_ENABLE
/********************* Format API *********************/
//camera_cv_api_cvt_color   -TBD
extern int32_t ab_cv_api_cvt_color(IN CAMERA_CV_API_MAT_ST* ps_src, OUT CAMERA_CV_API_MAT_ST* ps_dst, IN CAMERA_CV_API_CONVERT_CODE_ET e_code);
#define camera_cv_api_cvt_color(src, dst, code) \
    ab_cv_api_cvt_color(src, dst, code)

//camera_cv_api_merge
// CAMERA_CV_API_MERGE_MAX_COUNT 4
extern int32_t ab_cv_api_merge(IN CAMERA_CV_API_MAT_ST* ps_src, IN size_t count, OUT CAMERA_CV_API_MAT_ST* ps_dst);
#define camera_cv_api_merge(src, count, dst) \
    ab_cv_api_merge(src, count, dst)

//camera_cv_api_split
// CAMERA_CV_API_SPLIT_MAX_COUNT   4
extern int32_t ab_cv_api_split(IN CAMERA_CV_API_MAT_ST* ps_src, OUT CAMERA_CV_API_MAT_ST* ps_dst);
#define camera_cv_api_split(src, dst) \
    ab_cv_api_split(src, dst)

extern int32_t ab_cv_api_sub_img_cvt_color(IN CAMERA_CV_API_MAT_ST* ps_src, OUT CAMERA_CV_API_MAT_ST* ps_dst, IN CAMERA_CV_API_CONVERT_CODE_ET* pe_codes, IN CAMERA_CV_API_ROI_ST* ps_rois, IN size_t count);
#define camera_cv_api_sub_img_cvt_color(src, dst, code, roi, count) \
    ab_cv_api_sub_img_cvt_color(src, dst, code, roi, count)

//camera_cv_api_convert_to
extern int32_t ab_cv_api_convert_to(IN CAMERA_CV_API_MAT_ST* ps_src, OUT CAMERA_CV_API_MAT_ST* ps_dst, IN CAMERA_CV_API_BIT_DEPTH_ET i_type, IN float f_alpha);
#define camera_cv_api_convert_to(src, dst, type, alpha) \
    ab_cv_api_convert_to(src, dst, type, alpha)

//camera_cv_api_vconcat
extern int32_t ab_cv_api_vconcat(IN CAMERA_CV_API_MAT_ST* ps_src1, IN CAMERA_CV_API_MAT_ST* ps_src2, OUT CAMERA_CV_API_MAT_ST* ps_dst);
#define camera_cv_api_vconcat(src1, src2, dst) \
    ab_cv_api_vconcat(src1, src2, dst)

//camera_cv_api_hconcat
extern int32_t ab_cv_api_hconcat(IN CAMERA_CV_API_MAT_ST* ps_src1, IN CAMERA_CV_API_MAT_ST* ps_src2, OUT CAMERA_CV_API_MAT_ST* ps_dst);
#define camera_cv_api_hconcat(src1, src2, dst) \
    ab_cv_api_hconcat(src1, src2, dst)

//camera_cv_api_sub_img_cvt_color_and_resize
extern int32_t ab_cv_api_sub_img_cvt_color_and_resize(IN CAMERA_CV_API_MAT_ST* ps_src, OUT CAMERA_CV_API_MAT_ST* ps_dst, IN CAMERA_CV_API_CONVERT_CODE_ET* pe_code, IN CAMERA_CV_API_ROI_ST* ps_roi, IN CAMERA_CV_API_SIZE_ST* ps_dsize, size_t count);
#define camera_cv_api_sub_img_cvt_color_and_resize(src, dst, code, roi, dsize, count) \
    ab_cv_api_sub_img_cvt_color_and_resize(src, dst, code, roi, dsize, count)

extern int32_t ab_cv_api_sub_img_cvt_jpeg_and_resize(IN CAMERA_CV_API_MAT_ST* ps_src, OUT CAMERA_CV_API_JPEG_RESULT_ST *ps_dst, IN CAMERA_CV_API_CONVERT_JPEG_CODE_ET e_code, IN CAMERA_CV_API_JPEG_QUALITY_ET e_quality, IN CAMERA_CV_API_ROI_ST* ps_roi, IN CAMERA_CV_API_SIZE_ST* ps_dsize, IN size_t count);
#define camera_cv_api_sub_img_cvt_jpeg_and_resize(src, dst, code, quality, roi, dsize, count) \
    ab_cv_api_sub_img_cvt_jpeg_and_resize(src, dst, code, quality, roi, dsize, count)

#endif

#if CAMERA_CV_IMAGE_API_ENABLE
/********************* Image API *********************/
//camera_cv_api_min_max_idx -TBD
//camera_cv_api_integral    -TBD

//camera_cv_api_median_blur
extern int32_t ab_cv_api_median_blur(IN CAMERA_CV_API_MAT_ST* ps_src, OUT CAMERA_CV_API_MAT_ST* ps_dst, IN int i_ksize, IN int i_padding);
#define camera_cv_api_median_blur(src, dst, ksize, padding) \
    ab_cv_api_median_blur(src, dst, ksize, padding)
    
//camera_cv_api_blur        -TBD

//camera_cv_box_filter
extern int32_t ab_cv_api_box_filter(IN CAMERA_CV_API_MAT_ST* ps_src, OUT CAMERA_CV_API_MAT_ST* ps_dst, IN CAMERA_CV_API_SIZE_ST* ps_ksize, IN int i_padding);
#define camera_cv_api_box_filter(src, dst, ksize, padding) \
    ab_cv_api_box_filter(src, dst, ksize, padding)

//camera_cv_api_filter_2d - TBD
    
//camera_cv_api_dilate
extern int32_t ab_cv_api_dilate(IN CAMERA_CV_API_MAT_ST* ps_src, OUT CAMERA_CV_API_MAT_ST* ps_dst, IN CAMERA_CV_API_MAT_ST* ps_kernel, IN int i_padding);
#define camera_cv_api_dilate(src, dst, kernel, padding) \
    ab_cv_api_dilate(src, dst, kernel, padding)
    
//camera_cv_api_erode
extern int32_t ab_cv_api_erode(IN CAMERA_CV_API_MAT_ST* ps_src, OUT CAMERA_CV_API_MAT_ST* ps_dst, IN CAMERA_CV_API_MAT_ST* ps_kernel, IN int i_padding);
#define camera_cv_api_erode(src, dst, kernel, padding) \
    ab_cv_api_erode(src, dst, kernel, padding)
    
//camera_cv_api_sobel
extern int32_t ab_cv_api_sobel(IN CAMERA_CV_API_MAT_ST* ps_src, OUT CAMERA_CV_API_MAT_ST* ps_dst, IN int i_ddepth, IN int i_dx, IN int i_dy, IN int i_padding);
#define camera_cv_api_sobel(src, dst, ddepth, dx, dy, padding) \
    ab_cv_api_sobel(src, dst, ddepth, dx, dy, padding)
#endif

#if CAMERA_CV_MATH_API_ENABLE
/********************* Math API *********************/
//camera_cv_api_abs
extern int32_t ab_cv_api_abs(IN CAMERA_CV_API_MAT_ST* ps_src, OUT CAMERA_CV_API_MAT_ST* ps_dst, IN int i_dtype);
#define camera_cv_api_abs(src, dst, type) \
    ab_cv_api_abs(src, dst, type)
    
//camera_cv_api_abs_diff
extern int32_t ab_cv_api_abs_diff(IN CAMERA_CV_API_MAT_ST* ps_src1, IN CAMERA_CV_API_MAT_ST* ps_src2, OUT CAMERA_CV_API_MAT_ST* ps_dst, IN int i_dtype);
#define camera_cv_api_abs_diff(src1, src2, dst, type) \
    ab_cv_api_abs_diff(src1, src2, dst, type)
    
//camera_cv_api_add
extern int32_t ab_cv_api_add(IN CAMERA_CV_API_MAT_ST* ps_src1, IN CAMERA_CV_API_MAT_ST* ps_src2, OUT CAMERA_CV_API_MAT_ST* ps_dst, IN int i_dtype);
#define camera_cv_api_add(src1, src2, dst, type) \
    ab_cv_api_add(src1, src2, dst, type)
    
//camera_cv_api_add_weighted
extern int32_t ab_cv_api_add_weighted(IN CAMERA_CV_API_MAT_ST* ps_src, IN float f_alpha, IN CAMERA_CV_API_MAT_ST* ps_src2, IN float f_beta, IN float f_gamma, OUT CAMERA_CV_API_MAT_ST* ps_dst, IN int i_dtype);
#define camera_cv_api_add_weighted(src, alpha, src2, beta, gamma, dst, type) \
    ab_cv_api_add_weighted(src, alpha, src2, beta, gamma, dst, type)
    
//camera_cv_api_bitwise_and
extern int32_t ab_cv_api_bitwise_and(IN CAMERA_CV_API_MAT_ST* ps_src1, IN CAMERA_CV_API_MAT_ST* ps_src2, OUT CAMERA_CV_API_MAT_ST* ps_dst);
#define camera_cv_api_bitwise_and(src1, src2, dst) \
    ab_cv_api_bitwise_and(src1, src2, dst)
    
//camera_cv_api_bitwise_not
extern int32_t ab_cv_api_bitwise_not(IN CAMERA_CV_API_MAT_ST* ps_src, OUT CAMERA_CV_API_MAT_ST* ps_dst);
#define camera_cv_api_bitwise_not(src, dst) \
    ab_cv_api_bitwise_not(src, dst)

//camera_cv_api_bitwise_or
extern int32_t ab_cv_api_bitwise_or(IN CAMERA_CV_API_MAT_ST* ps_src1, IN CAMERA_CV_API_MAT_ST* ps_src2, OUT CAMERA_CV_API_MAT_ST* ps_dst);
#define camera_cv_api_bitwise_or(src1, src2, dst) \
    ab_cv_api_bitwise_or(src1, src2, dst)

//camera_cv_api_bitwise_xor
extern int32_t ab_cv_api_bitwise_xor(IN CAMERA_CV_API_MAT_ST* ps_src1, IN CAMERA_CV_API_MAT_ST* ps_src2, OUT CAMERA_CV_API_MAT_ST* ps_dst);
#define camera_cv_api_bitwise_xor(src1, src2, dst) \
    ab_cv_api_bitwise_xor(src1, src2, dst)
    
//camera_cv_api_count_non_zero
extern int32_t ab_cv_api_count_non_zero(IN CAMERA_CV_API_MAT_ST* ps_src, OUT int* i_count);
#define camera_cv_api_count_non_zero(src, count) \
    ab_cv_api_count_non_zero(src, count)
    
//camera_cv_api_dct     -TBD

//camera_cv_api_exp
extern int32_t ab_cv_api_exp(IN CAMERA_CV_API_MAT_ST* ps_src, OUT CAMERA_CV_API_MAT_ST* ps_dst);
#define camera_cv_api_exp(src, dst) \
    ab_cv_api_exp(src, dst)
    
//camera_cv_api_mean_std_dev
extern int32_t ab_cv_api_mean_std_dev(IN CAMERA_CV_API_MAT_ST* ps_src, OUT CAMERA_CV_API_MAT_ST* ps_mean, OUT CAMERA_CV_API_MAT_ST* ps_std_dev);
#define camera_cv_api_mean_std_dev(src, mean, std_dev) \
    ab_cv_api_mean_std_dev(src, mean, std_dev)
    
//camera_cv_api_lut
extern int32_t ab_cv_api_lut(IN CAMERA_CV_API_MAT_ST* ps_src, IN CAMERA_CV_API_MAT_ST* ps_lut, OUT CAMERA_CV_API_MAT_ST* ps_dst);
#define camera_cv_api_lut(src, lut, dst) \
    ab_cv_api_lut(src, lut, dst)
    
//camera_cv_api_magnitude
extern int32_t ab_cv_api_magnitude(IN CAMERA_CV_API_MAT_ST* ps_x, IN CAMERA_CV_API_MAT_ST* ps_y, OUT CAMERA_CV_API_MAT_ST* ps_magnitude, IN int i_dtype);
#define camera_cv_api_magnitude(x, y, magnitude, type) \
    ab_cv_api_magnitude(x, y, magnitude, type)
    
//camera_cv_api_max
extern int32_t ab_cv_api_max(IN CAMERA_CV_API_MAT_ST* ps_src1, IN CAMERA_CV_API_MAT_ST* ps_src2, OUT CAMERA_CV_API_MAT_ST* ps_dst);
#define camera_cv_api_max(src1, src2, dst) \
    ab_cv_api_max(src1, src2, dst)
    
//camera_cv_api_min
extern int32_t ab_cv_api_min(IN CAMERA_CV_API_MAT_ST* ps_src1, IN CAMERA_CV_API_MAT_ST* ps_src2, OUT CAMERA_CV_API_MAT_ST* ps_dst);
#define camera_cv_api_min(src1, src2, dst) \
    ab_cv_api_min(src1, src2, dst)
    
//camera_cv_api_min_max_loc
extern int32_t ab_cv_api_min_max_loc(IN CAMERA_CV_API_MAT_ST* ps_src, OUT float* pf_min_val, OUT float* pf_max_val, OUT CAMERA_CV_API_MAT_ST* ps_min_loc, OUT CAMERA_CV_API_MAT_ST* ps_max_loc);
#define camera_cv_api_min_max_loc(src, min_val, max_val, min_loc, max_loc) \
    ab_cv_api_min_max_loc(src, min_val, max_val, min_loc, max_loc)
    
//camera_cv_api_multiply
extern int32_t ab_cv_api_multiply(IN CAMERA_CV_API_MAT_ST* ps_src1, IN CAMERA_CV_API_MAT_ST* ps_src2, OUT CAMERA_CV_API_MAT_ST* ps_dst, IN float f_scale, IN int i_dtype);
#define camera_cv_api_multiply(src1, src2, dst, scale, type) \
    ab_cv_api_multiply(src1, src2, dst, scale, type)
    
//camera_cv_api_mul - TBD

//camera_cv_api_phase
extern int32_t ab_cv_api_phase(IN CAMERA_CV_API_MAT_ST* ps_x, IN CAMERA_CV_API_MAT_ST* ps_y, OUT CAMERA_CV_API_MAT_ST* ps_angle);
#define camera_cv_api_phase(x, y, angle) \
    ab_cv_api_phase(x, y, angle)
    
//camera_cv_api_scale_add
extern int32_t ab_cv_api_scale_add(IN CAMERA_CV_API_MAT_ST* ps_src1, IN float f_alpha, IN CAMERA_CV_API_MAT_ST* ps_src2, OUT CAMERA_CV_API_MAT_ST* ps_dst, IN int i_dtype);
#define camera_cv_api_scale_add(src1, alpha, src2, dst, type) \
    ab_cv_api_scale_add(src1, alpha, src2, dst, type)
    
//camera_cv_api_sort
extern int32_t ab_cv_api_sort(IN CAMERA_CV_API_MAT_ST* ps_src, OUT CAMERA_CV_API_MAT_ST* ps_dst, IN int i_flags);
#define camera_cv_api_sort(src, dst, flags) \
    ab_cv_api_sort(src, dst, flags)
    
//camera_cv_api_subtract
extern int32_t ab_cv_api_subtract(IN CAMERA_CV_API_MAT_ST* ps_src1, IN CAMERA_CV_API_MAT_ST* ps_src2, OUT CAMERA_CV_API_MAT_ST* ps_dst, IN int i_dtype);
#define camera_cv_api_subtract(src1, src2, dst, type) \
    ab_cv_api_subtract(src1, src2, dst, type)
    
//camera_cv_api_sum
extern int32_t ab_cv_api_sum(IN CAMERA_CV_API_MAT_ST* ps_src, OUT float* pf_sum);
#define camera_cv_api_sum(src, sum) \
    ab_cv_api_sum(src, sum)
    
//camera_cv_api_accumulate
extern int32_t ab_cv_api_accumulate(IN CAMERA_CV_API_MAT_ST* ps_src1, IN CAMERA_CV_API_MAT_ST* ps_src2, OUT CAMERA_CV_API_MAT_ST* ps_dst);
#define camera_cv_api_accumulate(src1, src2, dst) \
    ab_cv_api_accumulate(src1, src2, dst)
    
//camera_cv_api_accumulate_square
extern int32_t ab_cv_api_accumulate_square(IN CAMERA_CV_API_MAT_ST* ps_src1, IN CAMERA_CV_API_MAT_ST* ps_src2, OUT CAMERA_CV_API_MAT_ST* ps_dst);
#define camera_cv_api_accumulate_square(src1, src2, dst) \
    ab_cv_api_accumulate_square(src1, src2, dst)
    
//camera_cv_api_accumulate_weighted
extern int32_t ab_cv_api_accumulate_weighted(IN CAMERA_CV_API_MAT_ST* ps_src1, IN CAMERA_CV_API_MAT_ST* ps_src2, OUT CAMERA_CV_API_MAT_ST* ps_dst, IN float f_alpha);
#define camera_cv_api_accumulate_weighted(src1, src2, dst, alpha) \
    ab_cv_api_accumulate_weighted(src1, src2, dst, alpha)
#endif

#endif  /* _AB_CV_API_H_ */
