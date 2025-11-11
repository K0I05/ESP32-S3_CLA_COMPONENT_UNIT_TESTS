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
#include <cla_matrix_lup_determinant_data.h>
#include <cla_matrix_lup_inverse_data.h>
#include <cla_matrix_lup_solve_data.h>

#define CLA_TEST_TOLERANCE_SMALL_NUMBER   (0.05)
#define CLA_TEST_TOLERANCE_BIG_NUMBER     (1e-5)

// C:\Users\lavco\.platformio\penv\Scripts\platformio.exe test -vvv --environment esp32s3box

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void test_function_cla_matrix_lup_determinant(void) {
  // iterate through all test cases
  for(uint16_t k = 0; k < cla_matrix_lup_determinant_cases; k++) {
    cla_matrix_ptr_t a = NULL;
    cla_matrix_lup_ptr_t a_lup = NULL;
    double x_computed = NAN;

    // create matrix A instances and populate with test data
    cla_matrix_create(cla_matrix_lup_determinant_rows[k], cla_matrix_lup_determinant_cols[k], &a);
    for(uint16_t i = 0; i < a->num_rows; i++) {
      for(uint16_t j = 0; j < a->num_cols; j++) {
        a->data[i][j] = cla_matrix_lup_determinant_mats[k][i][j];
      }
    }

    // get expected determinant value
    const double x_expected = cla_matrix_lup_determinant_vals[k];

    // perform LUP decomposition on matrix A
    cla_matrix_lup_solve(a, &a_lup);

    // compute determinant from LUP decomposition
    cla_matrix_lup_get_determinant(a_lup, &x_computed);

    // Using a larger tolerance for determinant due to large numbers
    bool is_equal = cla_is_value_equal(x_computed, x_expected, CLA_TEST_TOLERANCE_BIG_NUMBER);

    // free matrices
    cla_matrix_delete(a);
    cla_matrix_lup_delete(a_lup);

    TEST_ASSERT_TRUE(is_equal);
  }
}

void test_function_cla_matrix_lup_inverse(void) {
  // iterate through all test cases
  for(uint8_t k = 0; k < cla_matrix_lup_inverse_cases; k++) {
    cla_matrix_ptr_t a = NULL;
    cla_matrix_lup_ptr_t a_lup = NULL;
    cla_matrix_ptr_t x_inv_computed = NULL;
    cla_matrix_ptr_t x_inv_expected = NULL;
    cla_matrix_ptr_t a_dot_inv_computed = NULL;
    cla_matrix_ptr_t eye = NULL;

    // create matrix A instances and populate with test data
    cla_matrix_create(cla_matrix_lup_inverse_a_rows[k], cla_matrix_lup_inverse_a_cols[k], &a);
    for(uint16_t i = 0; i < a->num_rows; i++) {
      for(uint16_t j = 0; j < a->num_cols; j++) {
        a->data[i][j] = cla_matrix_lup_inverse_a_mats[k][i][j];
      }
    }

    // perform LUP decomposition on matrix A
    cla_matrix_lup_solve(a, &a_lup);

    // compute matrix X inverse using LUP decomposition
    cla_matrix_lup_get_inverse(a_lup, &x_inv_computed);

    // compute matrix A dot product from X inverse matrix
    cla_matrix_get_dot_product(a, x_inv_computed, &a_dot_inv_computed);

    // create identity matrix
    cla_matrix_create_identity(a->num_rows, &eye);

    // create expected matrix X instances and populate with test data
    cla_matrix_create(cla_matrix_lup_inverse_x_rows[k], cla_matrix_lup_inverse_x_cols[k], &x_inv_expected);
    for(uint16_t i = 0; i < x_inv_expected->num_rows; i++) {
      for(uint16_t j = 0; j < x_inv_expected->num_cols; j++) {
        x_inv_expected->data[i][j] = cla_matrix_lup_inverse_x_mats[k][i][j];
      }
    }

    bool is_equal = false;
    cla_matrix_is_equal(x_inv_computed, x_inv_expected, CLA_TEST_TOLERANCE_SMALL_NUMBER, &is_equal);

    // free matrices
    cla_matrix_delete(a);
    cla_matrix_lup_delete(a_lup);
    cla_matrix_delete(x_inv_computed);
    cla_matrix_delete(x_inv_expected);
    cla_matrix_delete(a_dot_inv_computed);
    cla_matrix_delete(eye);

    TEST_ASSERT_TRUE(is_equal);
  }
}

void test_function_cla_matrix_lup_solve(void) {
  // iterate through all test cases
  for(uint8_t k = 0; k < cla_matrix_lup_solve_cases; k++) {
    cla_matrix_ptr_t input = NULL;
    cla_matrix_lup_ptr_t input_lup = NULL;
    cla_matrix_ptr_t p_dot_input = NULL;
    cla_matrix_ptr_t l_dot_u = NULL;

    // create matrix input instances and populate with test data
    cla_matrix_create(cla_matrix_lup_solve_rows[k], cla_matrix_lup_solve_cols[k], &input);
    for(uint16_t i = 0; i < input->num_rows; i++) {
      for(uint16_t j = 0; j < input->num_cols; j++) {
        input->data[i][j] = cla_matrix_lup_solve_mats[k][i][j];
      }
    }

    // perform LUP decomposition on input matrix
    cla_matrix_lup_solve(input, &input_lup);

    // compute P dot product from input matrix
    cla_matrix_get_dot_product(input_lup->p, input, &p_dot_input);

    // compute L dot product from U matrix
    cla_matrix_get_dot_product(input_lup->l, input_lup->u, &l_dot_u);

    bool is_equal = false;
    cla_matrix_is_equal(p_dot_input, l_dot_u, CLA_TEST_TOLERANCE_SMALL_NUMBER, &is_equal);

    // free matrices
    cla_matrix_delete(input);
    cla_matrix_lup_delete(input_lup);
    cla_matrix_delete(p_dot_input);
    cla_matrix_delete(l_dot_u);

    TEST_ASSERT_TRUE(is_equal);
  }
}

void app_main() {
  UNITY_BEGIN();

  RUN_TEST(test_function_cla_matrix_lup_determinant);
  RUN_TEST(test_function_cla_matrix_lup_inverse);
  RUN_TEST(test_function_cla_matrix_lup_solve);

  UNITY_END();
}