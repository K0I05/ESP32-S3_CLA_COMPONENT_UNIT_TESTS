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
#include <cla_matrix_ls_solve_fwd_data.h>
#include <cla_matrix_ls_solve_bck_data.h>
#include <cla_matrix_ls_solve_data.h>

#define CLA_TEST_TOLERANCE_SMALL_NUMBER   (0.0001)
#define CLA_TEST_TOLERANCE_BIG_NUMBER     (1e-5)

// C:\Users\lavco\.platformio\penv\Scripts\platformio.exe test -vvv --environment esp32s3box

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void test_function_cla_matrix_ls_solve_fwd(void) {
  // iterate through all test cases
  for(uint8_t k = 0; k < cla_matrix_ls_solve_fwd_cases; k++) {
    cla_matrix_ptr_t a = NULL;
    cla_matrix_ptr_t b = NULL;
    cla_matrix_ptr_t x_expected = NULL;
    cla_matrix_ptr_t x_computed = NULL;

    // create matrix A instances and populate with test data
    cla_matrix_create(cla_matrix_ls_solve_fwd_a_rows[k], cla_matrix_ls_solve_fwd_a_cols[k], &a);
    for(uint16_t i = 0; i < a->num_rows; i++) {
      for(uint16_t j = 0; j < a->num_cols; j++) {
        a->data[i][j] = cla_matrix_ls_solve_fwd_a_mats[k][i][j];
      }
    }

    // create matrix B instances and populate with test data
    cla_matrix_create(cla_matrix_ls_solve_fwd_b_rows[k], cla_matrix_ls_solve_fwd_b_cols[k], &b);
    for(uint16_t i = 0; i < b->num_rows; i++) {
      for(uint16_t j = 0; j < b->num_cols; j++) {
        b->data[i][j] = cla_matrix_ls_solve_fwd_b_mats[k][i][j];
      }
    }

    // create expected matrix X instances and populate with test data
    cla_matrix_create(cla_matrix_ls_solve_fwd_x_rows[k], cla_matrix_ls_solve_fwd_x_cols[k], &x_expected);
    for(uint16_t i = 0; i < x_expected->num_rows; i++) {
      for(uint16_t j = 0; j < x_expected->num_cols; j++) {
        x_expected->data[i][j] = cla_matrix_ls_solve_fwd_x_mats[k][i][j];
      }
    }

    // compute matrix X using linear system solve forward function
    cla_matrix_ls_solve_fwd(a, b, &x_computed);

    bool is_equal = false;
    cla_matrix_is_equal(x_computed, x_expected, CLA_TEST_TOLERANCE_SMALL_NUMBER, &is_equal);

    // free matrices
    cla_matrix_delete(a);
    cla_matrix_delete(b);
    cla_matrix_delete(x_computed);
    cla_matrix_delete(x_expected);

    TEST_ASSERT_TRUE(is_equal);
  }
}

void test_function_cla_matrix_ls_solve_bck(void) {
  // iterate through all test cases
  for(uint8_t k = 0; k < cla_matrix_ls_solve_bck_cases; k++) {
    cla_matrix_ptr_t a = NULL;
    cla_matrix_ptr_t b = NULL;
    cla_matrix_ptr_t x_expected = NULL;
    cla_matrix_ptr_t x_computed = NULL;

    // create matrix A instances and populate with test data
    cla_matrix_create(cla_matrix_ls_solve_bck_a_rows[k], cla_matrix_ls_solve_bck_a_cols[k], &a);
    for(uint16_t i = 0; i < a->num_rows; i++) {
      for(uint16_t j = 0; j < a->num_cols; j++) {
        a->data[i][j] = cla_matrix_ls_solve_bck_a_mats[k][i][j];
      }
    }

    // create matrix B instances and populate with test data
    cla_matrix_create(cla_matrix_ls_solve_bck_b_rows[k], cla_matrix_ls_solve_bck_b_cols[k], &b);
    for(uint16_t i = 0; i < b->num_rows; i++) {
      for(uint16_t j = 0; j < b->num_cols; j++) {
        b->data[i][j] = cla_matrix_ls_solve_bck_b_mats[k][i][j];
      }
    }

    // create expected matrix X instances and populate with test data
    cla_matrix_create(cla_matrix_ls_solve_bck_x_rows[k], cla_matrix_ls_solve_bck_x_cols[k], &x_expected);
    for(uint16_t i = 0; i < x_expected->num_rows; i++) {
      for(uint16_t j = 0; j < x_expected->num_cols; j++) {
        x_expected->data[i][j] = cla_matrix_ls_solve_bck_x_mats[k][i][j];
      }
    }

    // compute matrix X using linear system solve backward function
    cla_matrix_ls_solve_bck(a, b, &x_computed);

    bool is_equal = false;
    cla_matrix_is_equal(x_computed, x_expected, CLA_TEST_TOLERANCE_SMALL_NUMBER, &is_equal);

    // free matrices
    cla_matrix_delete(a);
    cla_matrix_delete(b);
    cla_matrix_delete(x_computed);
    cla_matrix_delete(x_expected);

    TEST_ASSERT_TRUE(is_equal);
  }
}

void test_function_cla_matrix_ls_solve(void) {
  // iterate through all test cases
  for(uint8_t k = 0; k < cla_matrix_ls_solve_cases; k++) {
    cla_matrix_ptr_t a = NULL;
    cla_matrix_lup_ptr_t a_lup = NULL;
    cla_matrix_ptr_t b = NULL;
    cla_matrix_ptr_t x_expected = NULL;
    cla_matrix_ptr_t x_computed = NULL;

    // create matrix A instances and populate with test data
    cla_matrix_create(cla_matrix_ls_solve_a_rows[k], cla_matrix_ls_solve_a_cols[k], &a);
    for(uint16_t i = 0; i < a->num_rows; i++) {
      for(uint16_t j = 0; j < a->num_cols; j++) {
        a->data[i][j] = cla_matrix_ls_solve_a_mats[k][i][j];
      }
    }

    // perform LUP decomposition on matrix A
    cla_matrix_lup_solve(a, &a_lup);

    // create matrix B instances and populate with test data
    cla_matrix_create(cla_matrix_ls_solve_b_rows[k], cla_matrix_ls_solve_b_cols[k], &b);
    for(uint16_t i = 0; i < b->num_rows; i++) {
      for(uint16_t j = 0; j < b->num_cols; j++) {
        b->data[i][j] = cla_matrix_ls_solve_b_mats[k][i][j];
      }
    }

    // create expected matrix X instances and populate with test data
    cla_matrix_create(cla_matrix_ls_solve_x_rows[k], cla_matrix_ls_solve_x_cols[k], &x_expected);
    for(uint16_t i = 0; i < x_expected->num_rows; i++) {
      for(uint16_t j = 0; j < x_expected->num_cols; j++) {
        x_expected->data[i][j] = cla_matrix_ls_solve_x_mats[k][i][j];
      }
    }

    // compute matrix X using linear system solve function
    cla_matrix_ls_solve(a_lup, b, &x_computed);

    bool is_equal = false;
    cla_matrix_is_equal(x_computed, x_expected, CLA_TEST_TOLERANCE_SMALL_NUMBER, &is_equal);

    // free matrices
    cla_matrix_delete(a);
    cla_matrix_lup_delete(a_lup);
    cla_matrix_delete(b);
    cla_matrix_delete(x_computed);
    cla_matrix_delete(x_expected);

    TEST_ASSERT_TRUE(is_equal);
  }
}

void app_main() {
  UNITY_BEGIN();

  RUN_TEST(test_function_cla_matrix_ls_solve_fwd);
  RUN_TEST(test_function_cla_matrix_ls_solve_bck);
  RUN_TEST(test_function_cla_matrix_ls_solve);

  UNITY_END();
}
