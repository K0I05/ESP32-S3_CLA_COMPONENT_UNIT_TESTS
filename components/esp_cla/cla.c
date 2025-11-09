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
 * @file cla.c
 *
 * ESP-IDF compact linear algebra (cla) library
 * 
 * https://github.com/nomemory/neat-matrix-library/blob/main/nml.c
 * 
 * 
 * Copyright (c) 2025 Eric Gionet (gionet.c.eric@gmail.com)
 *
 * MIT Licensed as described in the file LICENSE
 */
#include <math.h>
#include <float.h>
#include "include/cla.h"

/*
 * macro definitions
*/
#define ESP_ARG_CHECK(VAL) do { if (!(VAL)) return ESP_ERR_INVALID_ARG; } while (0)


/*
* static constant declarations
*/
static const char *TAG = "cla";



esp_err_t cla_matrix_multiply_vector(const cla_matrix_ptr_t m, const cla_vector_ptr_t v, cla_vector_ptr_t *const v_product) {
    ESP_ARG_CHECK(m && v);
    ESP_RETURN_ON_FALSE( (m->num_rows == v->num_cmps), ESP_ERR_INVALID_ARG, TAG, "Invalid matrix and vector dimensions, number of rows in matrix must match number of components in vector" );
    ESP_RETURN_ON_ERROR( cla_vector_create(m->num_rows, v_product), TAG, "Unable to create vector instance, matrix-vector multiplication failed" );
    for(uint16_t i = 0; i < m->num_rows; i++) {
        (*v_product)->data[i] = 0.0;
        for(uint16_t j = 0; j < m->num_cols; j++) {
            (*v_product)->data[i] += m->data[i][j] * v->data[j];
        }
    }
    return ESP_OK;
}

esp_err_t cla_matrix_to_vector(const cla_matrix_ptr_t m, cla_vector_ptr_t *const v) {
    ESP_ARG_CHECK(m);
    ESP_RETURN_ON_FALSE( (m->num_cols == 1 && m->num_rows > 0), ESP_ERR_INVALID_ARG, TAG, "Invalid matrix dimensions, matrix must be n x 1 to convert to vector" );
    ESP_RETURN_ON_ERROR( cla_vector_create(m->num_rows, v), TAG, "Unable to create vector instance, matrix to vector conversion failed" );
    for(uint16_t i = 0; i < m->num_rows; i++) {
        (*v)->data[i] = m->data[i][0];
    }
    return ESP_OK;
}

esp_err_t cla_vector_to_matrix(const cla_vector_ptr_t v, cla_matrix_ptr_t *const m) {
    ESP_ARG_CHECK(v);
    ESP_RETURN_ON_FALSE( (v->num_cmps > 0), ESP_ERR_INVALID_ARG, TAG, "Invalid vector dimensions, number of components must be greater than 0 to convert to matrix" );
    ESP_RETURN_ON_ERROR( cla_matrix_create(v->num_cmps, 1, m), TAG, "Unable to create matrix instance, vector to matrix conversion failed" );
    for(uint16_t i = 0; i < v->num_cmps; i++) {
        (*m)->data[i][0] = v->data[i];
    }
    return ESP_OK;
}

float cla_get_heading(const float x_axis, const float y_axis) {
    float heading;
    /* honeywell application note AN-203 */
    if(y_axis > 0.0f) { 
        heading = 90.0f - (atanf(x_axis/y_axis) * 180.0f / M_PI);
    } else if(y_axis < 0.0f) {
        heading = 270.0f - (atanf(x_axis/y_axis) * 180.0f / M_PI);
    } else {
        if(x_axis < 0.0f) { 
            heading = 180.0f;
        } else if(x_axis > 0.0f) { 
            heading = 0.0f;
        } else {
            heading = 0.0f;
        }
    }
    /* convert to heading to a 0..360 degree range */
    if (heading < 0.0f) {
        heading += 360.0f;
    } else if (heading > 360.0f) {
        heading -= 360.0f;
    }
    return heading;
}

float cla_get_true_heading(const float x_axis, const float y_axis, const float declination) {
    float heading;
    /* honeywell application note AN-203 */
    if(y_axis > 0.0f) { 
        heading = 90.0f - (atanf(x_axis/y_axis) * 180.0f / M_PI);
    } else if(y_axis < 0.0f) {
        heading = 270.0f - (atanf(x_axis/y_axis) * 180.0f / M_PI);
    } else {
        if(x_axis < 0.0f) { 
            heading = 180.0f;
        } else if(x_axis > 0.0f) { 
            heading = 0.0f;
        } else {
            heading = 0.0f;
        }
    }
    /* apply magnetic declination (+east | -west) */
    heading += declination;
    /* convert to heading to a 0..360 degree range */
    if (heading < 0.0f) {
        heading += 360.0f;
    } else if (heading > 360.0f) {
        heading -= 360.0f;
    }
    return heading;
}

float cla_get_earth_field(const float x_axis, const float y_axis, const float z_axis) {
    return sqrtf(powf(x_axis, 2) + powf(y_axis, 2) + powf(z_axis, 2));
}

bool cla_is_value_equal(const double val1, const double val2, const double tolerance) {
    const double diff = fabs(val1 - val2);
    return diff <= tolerance || diff < fmax(fabs(val1), fabs(val2)) * tolerance;
}

esp_err_t cla_solve_ellipsoid_coefficients(const cla_vector_samples_t v_calib_data, cla_ellipsoid_coeffs_t *const v_ellip_coeffs) {
    esp_err_t ret = ESP_OK;

    ESP_ARG_CHECK(v_calib_data);

    // ellipsoid fitting algorithm

    // Create the design matrix D (N x 9)
    cla_matrix_ptr_t d_matrix = NULL;
    ESP_GOTO_ON_ERROR(cla_matrix_create(CLA_CAL_SAMPLE_SIZE, CLA_ELLIPSOID_COEFF_SIZE, &d_matrix), cleanup, TAG, "Failed to create design matrix");

    // Create the observation vector O (N x 1)
    cla_matrix_ptr_t o_matrix = NULL;
    ESP_GOTO_ON_ERROR(cla_matrix_create(CLA_CAL_SAMPLE_SIZE, 1, &o_matrix), cleanup, TAG, "Failed to create observation matrix");

    // Populate the D and O matrices
    for(uint16_t i = 0; i < CLA_CAL_SAMPLE_SIZE; i++) {
        const cla_vector_ptr_t sample = v_calib_data[i];
        if (sample == NULL || sample->num_cmps != 3) {
            ret = ESP_ERR_INVALID_ARG;
            goto cleanup;
        }
        const double x = sample->data[0];
        const double y = sample->data[1];
        const double z = sample->data[2];

        // Ax^2 + By^2 + Cz^2 + 2Dxy + 2Exz + 2Fyz + 2Gx + 2Hy + 2Iz = 1
        d_matrix->data[i][0] = x * x;
        d_matrix->data[i][1] = y * y;
        d_matrix->data[i][2] = z * z;
        d_matrix->data[i][3] = x * y;
        d_matrix->data[i][4] = x * z;
        d_matrix->data[i][5] = y * z;
        d_matrix->data[i][6] = x;
        d_matrix->data[i][7] = y;
        d_matrix->data[i][8] = z;

        o_matrix->data[i][0] = 1.0; // J = -1, so -J = 1
    }

    // Solve QR decomposition
    cla_matrix_ptr_t v_matrix = NULL;
    ESP_GOTO_ON_ERROR(cla_matrix_qr_solve(d_matrix, o_matrix, &v_matrix), cleanup, TAG, "Failed to solve with QR decomposition");

    // Convert the resulting matrix to a vector
    ESP_GOTO_ON_ERROR(cla_matrix_to_vector(v_matrix, v_ellip_coeffs), cleanup, TAG, "Failed to convert result matrix to vector");

cleanup:
    cla_matrix_delete(d_matrix);
    cla_matrix_delete(o_matrix);
    cla_matrix_delete(v_matrix);

    if (*v_ellip_coeffs == NULL) ret = ESP_FAIL;

    return ret;
}

esp_err_t cla_get_calibration_parameters(const cla_vector_ptr_t v_ellip_coeffs, cla_vector_ptr_t *const v_offset, cla_matrix_ptr_t *const m_w) {
    esp_err_t ret = ESP_OK;

    // 1. Construct the M matrix and b vector from coefficients
    cla_matrix_ptr_t M = NULL;
    cla_vector_ptr_t b = NULL;
    ESP_RETURN_ON_ERROR( cla_matrix_create(3, 3, &M), TAG, "Unable to create matrix instance, M matrix creation failed" );
    ESP_RETURN_ON_ERROR( cla_vector_create(3, &b), TAG, "Unable to create vector instance, b vector creation failed" );

    M->data[0][0] = v_ellip_coeffs->data[0]; M->data[0][1] = v_ellip_coeffs->data[3]; M->data[0][2] = v_ellip_coeffs->data[4]; // A, D, E
    M->data[1][0] = v_ellip_coeffs->data[3]; M->data[1][1] = v_ellip_coeffs->data[1]; M->data[1][2] = v_ellip_coeffs->data[5]; // D, B, F
    M->data[2][0] = v_ellip_coeffs->data[4]; M->data[2][1] = v_ellip_coeffs->data[5]; M->data[2][2] = v_ellip_coeffs->data[2]; // E, F, C

    b->data[0] = v_ellip_coeffs->data[6]; // G
    b->data[1] = v_ellip_coeffs->data[7]; // H
    b->data[2] = v_ellip_coeffs->data[8]; // I

    // 2. Calculate Hard-Iron offset: offset = -0.5 * M_inv * b
    cla_matrix_lup_ptr_t M_lup = NULL;
    cla_matrix_ptr_t M_inv = NULL;
    cla_vector_ptr_t M_inv_b = NULL;

    ESP_GOTO_ON_ERROR(cla_matrix_lup_solve(M, &M_lup), cleanup, TAG, "LUP decomp failed");
    ESP_GOTO_ON_ERROR(cla_matrix_lup_get_inverse(M_lup, &M_inv), cleanup, TAG, "Matrix inverse failed");
    ESP_GOTO_ON_ERROR(cla_matrix_multiply_vector(M_inv, b, &M_inv_b), cleanup, TAG, "Matrix-vector multiply failed");
    ESP_GOTO_ON_ERROR(cla_vector_scale(M_inv_b, -0.5, v_offset), cleanup, TAG, "Vector scaling failed");

    // 3. Calculate Soft-Iron correction matrix W
    // This step requires a matrix decomposition like Cholesky or Eigenvalue decomposition.
    // that computes W such that W^T * W = M.
    ESP_GOTO_ON_ERROR(cla_matrix_solve_cholesky(M, m_w), cleanup, TAG, "Cholesky decomp failed");


cleanup:
    cla_matrix_delete(M);
    cla_vector_delete(b);
    cla_matrix_lup_delete(M_lup);
    cla_matrix_delete(M_inv);
    cla_vector_delete(M_inv_b);

    return ret;
}

esp_err_t cla_apply_calibration(const cla_vector_ptr_t v_raw_data, const cla_vector_ptr_t v_offset, const cla_matrix_ptr_t m_w, cla_vector_ptr_t *v_cal_data) {
    esp_err_t ret = ESP_OK;
    cla_vector_ptr_t centered_data = NULL;

    // Hard-iron correction: centered_data = raw_data - offset
    ESP_GOTO_ON_ERROR(cla_vector_subtract(v_raw_data, v_offset, &centered_data), cleanup, TAG, "Vector subtract failed");

    // Soft-iron correction: cal_data = W * centered_data
    ESP_GOTO_ON_ERROR(cla_matrix_multiply_vector(m_w, centered_data, v_cal_data), cleanup, TAG, "Matrix-vector multiply failed");

cleanup:
    cla_vector_delete(centered_data);
    return ret;
}