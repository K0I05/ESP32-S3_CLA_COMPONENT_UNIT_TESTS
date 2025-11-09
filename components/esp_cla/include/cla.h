/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2025 Eric Gionet (gionet.c.eric@gmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file cla.h
 * @defgroup 
 * @{
 *
 * ESP-IDF compact linear algebra (cla) library
 *
 * Copyright (c) 2025 Eric Gionet (gionet.c.eric@gmail.com)
 *
 * MIT Licensed as described in the file LICENSE
 */
#ifndef __CLA_H__
#define __CLA_H__

/**
 * dependency includes
 */

#include <stdint.h>
#include <stdbool.h>
#include <esp_err.h>

#include "matrix.h"
#include "vector.h"


#ifdef __cplusplus
extern "C" {
#endif

/**
 * public constant definitions
 */
#define CLA_3X3_MATRIX_SIZE                UINT8_C(3)
#define CLA_9X9_MATRIX_SIZE                UINT8_C(9)
#define CLA_ELLIPSOID_COEFF_SIZE           UINT8_C(9)
#define CLA_CAL_SAMPLE_SIZE                UINT8_C(250)

/**
 * public macro definitions
 */


/**
 * public enumerator, union, and structure definitions
 */
typedef cla_vector_ptr_t cla_ellipsoid_coeffs_t;

typedef cla_vector_ptr_t cla_vector_samples_t[CLA_CAL_SAMPLE_SIZE];

/**
 * public function & subroutine prototype definitions
 */

/**
 * @brief Multiplies a matrix by a vector.
 * 
 * @param m Matrix to multiply.
 * @param v Vector to multiply.
 * @param v_product Vector product of matrix and vector. 
 * @return esp_err_t ESP_OK on success.
 */
esp_err_t cla_matrix_multiply_vector(const cla_matrix_ptr_t m, const cla_vector_ptr_t v, cla_vector_ptr_t *const v_product);

 /**
  * @brief Converts n-1 dimensional matrix to n dimensional vector.
  * 
  * @param m Matrix to convert.
  * @param v Vector result of the conversion.
  * @return esp_err_t ESP_OK on success.
  */
esp_err_t cla_matrix_to_vector(const cla_matrix_ptr_t m, cla_vector_ptr_t *const v);

/**
 * @brief Converts n dimensional vector to n-1 dimensional matrix.
 * 
 * @param v Vector to convert.
 * @param m Matrix result of the conversion.
 * @return esp_err_t ESP_OK on success.
 */
esp_err_t cla_vector_to_matrix(const cla_vector_ptr_t v, cla_matrix_ptr_t *const m);

/**
 * @brief Calculates heading in degrees from magnetic x and y components.
 * 
 * @param x_axis X axis magnetic component.
 * @param y_axis Y axis magnetic component.
 * @return float Heading in degrees.
 */
float cla_get_heading(const float x_axis, const float y_axis);

/**
 * @brief Calculates heading from true north in degrees from magnetic x and y components and magnetic declination.
 * 
 * @param x_axis X axis magnetic component.
 * @param y_axis Y axis magnetic component.
 * @param declination Magnetic declination in degrees (+east / -west).
 * @return float Heading from true north in degrees.
 */
float cla_get_true_heading(const float x_axis, const float y_axis, const float declination);

/**
 * @brief Calculates the magnitude of the earth's magnetic field from its x, y, and z components.
 * 
 * @param x_axis Magnetic field x component.
 * @param y_axis Magnetic field y component.
 * @param z_axis Magnetic field z component.
 * @return float Magnitude of the earth's magnetic field.
 */
float cla_get_earth_field(const float x_axis, const float y_axis, const float z_axis);

/**
 * @brief Checks if two double-precision floating-point values are approximately equal within a given tolerance.
 * 
 * @param val1 The first value.
 * @param val2 The second value.
 * @param tolerance The tolerance for comparison. It's used for both absolute and relative error checks.
 * @return bool True when values are equal to each other, otherwise, false.
 */
bool cla_is_value_equal(const double val1, const double val2, const double tolerance);

/**
 * @brief Calculates ellipsoid coefficients from calibration sample data.
 * 
 * @param v_calib_data Calibration sample data array.
 * @param v_ellip_coeffs Ellipsoid coefficients vector (9x1).
 * @return esp_err_t ESP_OK on success.
 */
esp_err_t cla_solve_ellipsoid_coefficients(const cla_vector_samples_t v_calib_data, cla_ellipsoid_coeffs_t *const v_ellip_coeffs);

/**
 * @brief Derives calibration parameters from ellipsoid coefficients.
 *
 * @param v_ellip_coeffs Input vector of 9 ellipsoid coefficients.
 * @param v_offset       Output hard-iron offset vector (3x1).
 * @param m_w            Output soft-iron correction matrix (3x3).
 * @return esp_err_t ESP_OK on success.
 */
esp_err_t cla_get_calibration_parameters(const cla_vector_ptr_t v_ellip_coeffs, cla_vector_ptr_t *const v_offset, cla_matrix_ptr_t *const m_w);

/**
 * @brief Applies calibration to raw vector sensor data.
 *
 * @param v_raw_data Input raw sensor data vector (3x1).
 * @param v_offset   Hard-iron offset vector (3x1).
 * @param m_w        Soft-iron correction matrix (3x3).
 * @param v_cal_data Output calibrated data vector (3x1).
 * @return esp_err_t ESP_OK on success.
 */
esp_err_t cla_apply_calibration(const cla_vector_ptr_t v_raw_data, const cla_vector_ptr_t v_offset, const cla_matrix_ptr_t m_w, cla_vector_ptr_t *const v_cal_data);



#ifdef __cplusplus
}
#endif

/**@}*/

#endif  // __CLA_H__
