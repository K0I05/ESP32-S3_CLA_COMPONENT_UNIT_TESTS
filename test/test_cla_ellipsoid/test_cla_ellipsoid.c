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
#include <stdio.h>
//#include <unity.h>

#include <limits.h>
#include "unity.h"


#include <esp_err.h>
#include <esp_check.h>

// cla component
#include <cla.h>

// cla matrix test data
#include <cla_ellipsoid_fitting_data.h>
#include <cla_ellipsoid_calibration_data.h>

#define CLA_TEST_TOLERANCE_SMALL_NUMBER   (0.05)
#define CLA_TEST_TOLERANCE_BIG_NUMBER     (1e-5)

// C:\Users\lavco\.platformio\penv\Scripts\platformio.exe test -vvv --environment esp32s3box

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void test_function_cla_solve_ellipsoid_coefficients(void) {
    for (uint8_t k = 0; k < cla_ellipsoid_fitting_cases; k++) {
        cla_vector_samples_t calib_data;
        cla_ellipsoid_coeffs_t computed_coeffs = NULL;
        cla_ellipsoid_coeffs_t expected_coeffs = NULL;

        // Create and populate calibration data
        for (int i = 0; i < CLA_CAL_SAMPLE_SIZE; i++) {
            cla_vector_create(3, &calib_data[i]);
            calib_data[i]->data[0] = cla_ellipsoid_fitting_samples[k][i][0];
            calib_data[i]->data[1] = cla_ellipsoid_fitting_samples[k][i][1];
            calib_data[i]->data[2] = cla_ellipsoid_fitting_samples[k][i][2];
        }

        // Create and populate expected coefficients vector
        cla_vector_create(CLA_ELLIPSOID_COEFF_SIZE, &expected_coeffs);
        for (int i = 0; i < CLA_ELLIPSOID_COEFF_SIZE; i++) {
            expected_coeffs->data[i] = cla_ellipsoid_fitting_coeffs[k][i];
        }
        
        // Solve for ellipsoid coefficients
        cla_solve_ellipsoid_coefficients(calib_data, &computed_coeffs);

        bool is_equal = false;
        cla_vector_is_equal(computed_coeffs, expected_coeffs, CLA_TEST_TOLERANCE_SMALL_NUMBER, &is_equal);

        // Cleanup
        for (int i = 0; i < CLA_CAL_SAMPLE_SIZE; i++) {
            cla_vector_delete(calib_data[i]);
        }
        cla_vector_delete(computed_coeffs);
        cla_vector_delete(expected_coeffs);

        TEST_ASSERT_TRUE(is_equal);
    }
}

void test_function_cla_calibration_parameters(void) {
    for (uint8_t k = 0; k < cla_ellipsoid_calibration_cases; k++) {
        cla_vector_samples_t calib_data;
        cla_ellipsoid_coeffs_t computed_coeffs = NULL;
        cla_vector_ptr_t computed_hard_iron = NULL;
        cla_matrix_ptr_t computed_soft_iron = NULL;
        cla_vector_ptr_t expected_hard_iron = NULL;
        cla_matrix_ptr_t expected_soft_iron = NULL;

        // Create and populate calibration data
        for (int i = 0; i < cla_ellipsoid_calibration_samples; i++) {
            cla_vector_create(3, &calib_data[i]);
            calib_data[i]->data[0] = cla_ellipsoid_calibration_a_samples[k][i][0];
            calib_data[i]->data[1] = cla_ellipsoid_calibration_a_samples[k][i][1];
            calib_data[i]->data[2] = cla_ellipsoid_calibration_a_samples[k][i][2];
        }

        // Create and populate expected hard-iron vector
        cla_vector_create(3, &expected_hard_iron);
        for (int i = 0; i < expected_hard_iron->num_cmps; i++) {
            expected_hard_iron->data[i] = cla_ellipsoid_calibration_hard_iron_x_offsets[k][i];
        }

        // Create and populate expected soft-iron matrix
        cla_matrix_create(3, 3, &expected_soft_iron);
        for (int i = 0; i < expected_soft_iron->num_rows; i++) {
            for (int j = 0; j < expected_soft_iron->num_cols; j++) {
                expected_soft_iron->data[i][j] = cla_ellipsoid_calibration_soft_iron_x_distortions[k][i][j];
            }
        }
        
        // Solve for ellipsoid coefficients
        cla_solve_ellipsoid_coefficients(calib_data, &computed_coeffs);

        // Derive calibration parameters (hard and soft iron)
        cla_get_calibration_parameters(computed_coeffs, &computed_hard_iron, &computed_soft_iron);

        bool is_hard_iron_equal = false;
        cla_vector_is_equal(computed_hard_iron, expected_hard_iron, CLA_TEST_TOLERANCE_SMALL_NUMBER, &is_hard_iron_equal);

        bool is_soft_iron_equal = false;
        cla_matrix_is_equal(computed_soft_iron, expected_soft_iron, CLA_TEST_TOLERANCE_SMALL_NUMBER, &is_soft_iron_equal);

        // Cleanup
        for (int i = 0; i < CLA_CAL_SAMPLE_SIZE; i++) {
            cla_vector_delete(calib_data[i]);
        }
        cla_vector_delete(computed_coeffs);
        cla_vector_delete(computed_hard_iron);
        cla_matrix_delete(computed_soft_iron);
        cla_vector_delete(expected_hard_iron);
        cla_matrix_delete(expected_soft_iron);

        TEST_ASSERT_TRUE(is_hard_iron_equal);
        TEST_ASSERT_TRUE(is_soft_iron_equal);
    }
}

void app_main() {
  UNITY_BEGIN();

  RUN_TEST(test_function_cla_solve_ellipsoid_coefficients);
  RUN_TEST(test_function_cla_calibration_parameters);

  UNITY_END();
}