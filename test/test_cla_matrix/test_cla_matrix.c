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
#include <unity.h>

#include <esp_err.h>
#include <esp_check.h>

// cla component
#include <cla.h>

// cla matrix test data
#include <cla_matrix_qr_decomposition_data.h>
#include <cla_matrix_ref_data.h>
#include <cla_matrix_rref_data.h>

#define CLA_TEST_TOLERANCE_SMALL_NUMBER   (0.0001)
#define CLA_TEST_TOLERANCE_BIG_NUMBER     (1e-5)

// C:\Users\lavco\.platformio\penv\Scripts\platformio.exe test -vvv --environment esp32s3box

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void test_function_cla_matrix_qr_decomposition(void) {
  // iterate through all test cases
  for(uint16_t k = 0; k < cla_matrix_qr_decomposition_cases; k++) {
    cla_matrix_ptr_t a = NULL;
    cla_matrix_qr_ptr_t a_qr = NULL;
    cla_matrix_ptr_t qr_dot = NULL;

    // create matrix A instances and populate with test data
    cla_matrix_create(cla_matrix_qr_decomposition_rows[k], cla_matrix_qr_decomposition_cols[k], &a);
    for(uint16_t i = 0; i < a->num_rows; i++) {
      for(uint16_t j = 0; j < a->num_cols; j++) {
        a->data[i][j] = cla_matrix_qr_decomposition_mats[k][i][j];
      }
    }

    // perform QR decomposition on matrix A
    cla_matrix_qr_get_decomposition(a, &a_qr);

    // compute matrix dot product from Q and R matrices
    cla_matrix_multiply(a_qr->q, a_qr->r, &qr_dot);

    bool is_equal = false;
    cla_matrix_is_equal(a, qr_dot, CLA_TEST_TOLERANCE_SMALL_NUMBER, &is_equal);

    // free matrices
    cla_matrix_delete(a);
    cla_matrix_delete(qr_dot);
    cla_matrix_qr_delete(a_qr);

    TEST_ASSERT_TRUE(is_equal);
  }
}

void test_function_cla_matrix_ref(void) {
  // iterate through all test cases
  for(uint8_t k = 0; k < cla_matrix_rref_cases; k++) {
    cla_matrix_ptr_t a = NULL;
    cla_matrix_ptr_t x_computed_ref = NULL;
    cla_matrix_ptr_t x_expected_ref = NULL;

    // create matrix A instances and populate with test data
    cla_matrix_create(cla_matrix_rref_a_rows[k], cla_matrix_rref_a_cols[k], &a);
    for(uint16_t i = 0; i < a->num_rows; i++) {
      for(uint16_t j = 0; j < a->num_cols; j++) {
        a->data[i][j] = cla_matrix_rref_a_mats[k][i][j];
      }
    }

    // create expected matrix X instances and populate with test data
    cla_matrix_create(cla_matrix_rref_x_rows[k], cla_matrix_rref_x_cols[k], &x_expected_ref);
    for(uint16_t i = 0; i < x_expected_ref->num_rows; i++) {
      for(uint16_t j = 0; j < x_expected_ref->num_cols; j++) {
        x_expected_ref->data[i][j] = cla_matrix_rref_x_mats[k][i][j];
      }
    }

    cla_matrix_get_row_echelon_form(a, &x_computed_ref);

    bool is_equal = false;
    // The expected data is in RREF, so we must convert the computed REF to RREF before comparing.
    cla_matrix_ptr_t x_computed_rref = NULL;
    cla_matrix_get_reduced_row_echelon_form(x_computed_ref, &x_computed_rref);
    cla_matrix_is_equal(x_computed_rref, x_expected_ref, CLA_TEST_TOLERANCE_SMALL_NUMBER, &is_equal);

    // free matrices
    cla_matrix_delete(a);
    cla_matrix_delete(x_computed_ref);
    cla_matrix_delete(x_expected_ref);
    cla_matrix_delete(x_computed_rref);

    TEST_ASSERT_TRUE(is_equal);
  }
}

void test_function_cla_matrix_rref(void) {
  // iterate through all test cases
  for(uint8_t k = 0; k < cla_matrix_rref_cases; k++) {
    cla_matrix_ptr_t a = NULL;
    cla_matrix_ptr_t x_computed_rref = NULL;
    cla_matrix_ptr_t x_expected_rref = NULL;

    // create matrix A instances and populate with test data
    cla_matrix_create(cla_matrix_rref_a_rows[k], cla_matrix_rref_a_cols[k], &a);
    for(uint16_t i = 0; i < a->num_rows; i++) {
      for(uint16_t j = 0; j < a->num_cols; j++) {
        a->data[i][j] = cla_matrix_rref_a_mats[k][i][j];
      }
    }

    // create expected matrix X instances and populate with test data
    cla_matrix_create(cla_matrix_rref_x_rows[k], cla_matrix_rref_x_cols[k], &x_expected_rref);
    for(uint16_t i = 0; i < x_expected_rref->num_rows; i++) {
      for(uint16_t j = 0; j < x_expected_rref->num_cols; j++) {
        x_expected_rref->data[i][j] = cla_matrix_rref_x_mats[k][i][j];
      }
    }

    cla_matrix_get_reduced_row_echelon_form(a, &x_computed_rref);

    bool is_equal = false;
    cla_matrix_is_equal(x_computed_rref, x_expected_rref, CLA_TEST_TOLERANCE_SMALL_NUMBER, &is_equal);

    // free matrices
    cla_matrix_delete(a);
    cla_matrix_delete(x_computed_rref);
    cla_matrix_delete(x_expected_rref);

    TEST_ASSERT_TRUE(is_equal);
  }
}

void app_main() {
  UNITY_BEGIN();

  RUN_TEST(test_function_cla_matrix_qr_decomposition);
  RUN_TEST(test_function_cla_matrix_ref);
  RUN_TEST(test_function_cla_matrix_rref);

  UNITY_END();
}
