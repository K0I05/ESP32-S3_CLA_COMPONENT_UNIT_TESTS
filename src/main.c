/**
 * @file main.c
 * @brief explain
 *
 * This example takes the parameters 
 *
 * board: (1) ESP32-S3-­WROOM­-1-N16R8 (esp32s3box)
 * 
 * CTRL + SHIFT + P
 * pio run -t menuconfig
 * k & l keys for up or down
 * OR
 * PowerShell prompt: C:\Users\lavco\.platformio\penv\Scripts\platformio.exe run -t menuconfig
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#include <esp_system.h>
#include <esp_timer.h>
#include <esp_event.h>
#include <esp_log.h>
#include <nvs.h>
#include <nvs_flash.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <cla.h>
#include <cla_matrix_ls_solve_fwd_data.h>
#include <cla_matrix_ls_solve_bck_data.h>
#include <cla_matrix_ls_solve_data.h>
#include <cla_matrix_lup_determinant_data.h>
#include <cla_matrix_lup_inverse_data.h>
#include <cla_matrix_lup_solve_data.h>
#include <cla_matrix_qr_decomposition_data.h>
#include <cla_ellipsoid_fitting_data.h>


#define CONFIG_I2C_0_PORT                       I2C_NUM_0
#define CONFIG_I2C_0_SDA_IO                     (gpio_num_t)(45) // blue
#define CONFIG_I2C_0_SCL_IO                     (gpio_num_t)(48) // yellow
//
#define CONFIG_I2C_0_TASK_NAME                  "i2c_0_tsk"
#define CONFIG_I2C_0_TASK_MINIMAL_STACK_SIZE    (1024)
#define CONFIG_I2C_0_TASK_STACK_SIZE            (CONFIG_I2C_0_TASK_MINIMAL_STACK_SIZE * 4)
#define CONFIG_I2C_0_TASK_PRIORITY              (tskIDLE_PRIORITY + 2)
#define CONFIG_I2C_0_TASK_INTERVAL              (10) // sensor sampling task execution interval in seconds

#define CONFIG_APP_TAG                          "CLA [APP]"

#define CLA_TEST_TOLERANCE                      (0.0001f)

// macros
#define CONFIG_I2C_0_MASTER_DEFAULT {                               \
        .clk_source                     = I2C_CLK_SRC_DEFAULT,      \
        .i2c_port                       = CONFIG_I2C_0_PORT,        \
        .scl_io_num                     = CONFIG_I2C_0_SCL_IO,      \
        .sda_io_num                     = CONFIG_I2C_0_SDA_IO,      \
        .glitch_ignore_cnt              = 7,                        \
        .flags.enable_internal_pullup   = true, }



static inline void vTaskDelayMs(const uint ms) {
    const TickType_t xDelay = (ms / portTICK_PERIOD_MS);
    vTaskDelay( xDelay );
}

static inline void vTaskDelaySecUntil(TickType_t *previousWakeTime, const uint sec) {
    const TickType_t xFrequency = ((sec * 1000) / portTICK_PERIOD_MS);
    vTaskDelayUntil( previousWakeTime, xFrequency );  
}

static inline void cla_ls_solve_fwd_test(void) {
    ESP_LOGI(CONFIG_APP_TAG, "Matrix Linear System Solve Forward Test Cases - Begin");
    // iterate through all test cases
    for(uint8_t k = 0; k < cla_matrix_ls_solve_fwd_cases; k++) {
        cla_matrix_ptr_t a = NULL;
        cla_matrix_ptr_t b = NULL;
        cla_matrix_ptr_t x_expected = NULL;
        cla_matrix_ptr_t x_computed = NULL;

        ESP_LOGI(CONFIG_APP_TAG, "Matrix Linear System Solve Forward Test Case: %lu", (uint16_t)k + 1);

        // create matrix A instances and populate with test data
        const uint16_t a_rows = cla_matrix_ls_solve_fwd_a_rows[k];
        const uint16_t a_cols = cla_matrix_ls_solve_fwd_a_cols[k];
        const double  *a_mats = (const double *)cla_matrix_ls_solve_fwd_a_mats[k];
        cla_matrix_create(a_rows, a_cols, &a);
        for(uint16_t i = 0; i < a->num_rows; i++) {
            for(uint16_t j = 0; j < a->num_cols; j++) {
                a->data[i][j] = a_mats[i * a->num_cols + j];
            }
        }

        // create matrix B instances and populate with test data
        const uint16_t b_rows = cla_matrix_ls_solve_fwd_b_rows[k];
        const uint16_t b_cols = cla_matrix_ls_solve_fwd_b_cols[k];
        const double  *b_mats = (const double *)cla_matrix_ls_solve_fwd_b_mats[k];
        cla_matrix_create(b_rows, b_cols, &b);
        for(uint16_t i = 0; i < b->num_rows; i++) {
            for(uint16_t j = 0; j < b->num_cols; j++) {
                b->data[i][j] = b_mats[i * b->num_cols + j];
            }
        }

        // create expected matrix X instances and populate with test data
        const uint16_t x_rows = cla_matrix_ls_solve_fwd_x_rows[k];
        const uint16_t x_cols = cla_matrix_ls_solve_fwd_x_cols[k];
        const double  *x_mats = (const double *)cla_matrix_ls_solve_fwd_x_mats[k];
        cla_matrix_create(x_rows, x_cols, &x_expected);
        for(uint16_t i = 0; i < x_expected->num_rows; i++) {
            for(uint16_t j = 0; j < x_expected->num_cols; j++) {
                x_expected->data[i][j] = x_mats[i * x_expected->num_cols + j];
            }
        }

        // compute matrix X using linear system solve forward function
        cla_matrix_ls_solve_fwd(a, b, &x_computed);

        // print matrices
        ESP_LOGI(CONFIG_APP_TAG, "Matrix A:");
        cla_matrix_print(a);
        ESP_LOGI(CONFIG_APP_TAG, "Matrix B:");
        cla_matrix_print(b);
        ESP_LOGI(CONFIG_APP_TAG, "Expected X:");
        cla_matrix_print(x_expected);
        ESP_LOGI(CONFIG_APP_TAG, "Computed X:");
        cla_matrix_print(x_computed);

        // free matrices
        cla_matrix_delete(a);
        cla_matrix_delete(b);
        cla_matrix_delete(x_computed);
        cla_matrix_delete(x_expected);
    }
    ESP_LOGI(CONFIG_APP_TAG, "Matrix Linear System Solve Forward Test Cases - End");
}

static inline void cla_ls_solve_bck_test(void) {
    ESP_LOGI(CONFIG_APP_TAG, "Matrix Linear System Solve Backward Test Cases - Begin");
    // iterate through all test cases
    for(uint8_t k = 0; k < cla_matrix_ls_solve_bck_cases; k++) {
        cla_matrix_ptr_t a = NULL;
        cla_matrix_ptr_t b = NULL;
        cla_matrix_ptr_t x_expected = NULL;
        cla_matrix_ptr_t x_computed = NULL;

        ESP_LOGI(CONFIG_APP_TAG, "Matrix Linear System Solve Backward Test Case: %lu", (uint16_t)k + 1);

        // create matrix A instances and populate with test data
        const uint16_t a_rows = cla_matrix_ls_solve_bck_a_rows[k];
        const uint16_t a_cols = cla_matrix_ls_solve_bck_a_cols[k];
        const double  *a_mats = (const double *)cla_matrix_ls_solve_bck_a_mats[k];
        cla_matrix_create(a_rows, a_cols, &a);
        for(uint16_t i = 0; i < a->num_rows; i++) {
            for(uint16_t j = 0; j < a->num_cols; j++) {
                a->data[i][j] = a_mats[i * a->num_cols + j];
            }
        }

        // create matrix B instances and populate with test data
        const uint16_t b_rows = cla_matrix_ls_solve_bck_b_rows[k];
        const uint16_t b_cols = cla_matrix_ls_solve_bck_b_cols[k];
        const double  *b_mats = (const double *)cla_matrix_ls_solve_bck_b_mats[k];
        cla_matrix_create(b_rows, b_cols, &b);
        for(uint16_t i = 0; i < b->num_rows; i++) {
            for(uint16_t j = 0; j < b->num_cols; j++) {
                b->data[i][j] = b_mats[i * b->num_cols + j];
            }
        }

        // create expected matrix X instances and populate with test data
        const uint16_t x_rows = cla_matrix_ls_solve_bck_x_rows[k];
        const uint16_t x_cols = cla_matrix_ls_solve_bck_x_cols[k];
        const double  *x_mats = (const double *)cla_matrix_ls_solve_bck_x_mats[k];
        cla_matrix_create(x_rows, x_cols, &x_expected);
        for(uint16_t i = 0; i < x_expected->num_rows; i++) {
            for(uint16_t j = 0; j < x_expected->num_cols; j++) {
                x_expected->data[i][j] = x_mats[i * x_expected->num_cols + j];
            }
        }

        // compute matrix X using linear system solve backward function
        cla_matrix_ls_solve_bck(a, b, &x_computed);

        // print matrices
        ESP_LOGI(CONFIG_APP_TAG, "Matrix A:");
        cla_matrix_print(a);
        ESP_LOGI(CONFIG_APP_TAG, "Matrix B:");
        cla_matrix_print(b);
        ESP_LOGI(CONFIG_APP_TAG, "Expected X:");
        cla_matrix_print(x_expected);
        ESP_LOGI(CONFIG_APP_TAG, "Computed X:");
        cla_matrix_print(x_computed);

        // free matrices
        cla_matrix_delete(a);
        cla_matrix_delete(b);
        cla_matrix_delete(x_computed);
        cla_matrix_delete(x_expected);
    }
    ESP_LOGI(CONFIG_APP_TAG, "Matrix Linear System Solve Backward Test Cases - End");
}

static inline void cla_ls_solve_test(void) {
    ESP_LOGI(CONFIG_APP_TAG, "Matrix Linear System Solve Test Cases - Begin");
    // iterate through all test cases
    for(uint8_t k = 0; k < cla_matrix_ls_solve_cases; k++) {
        cla_matrix_ptr_t a = NULL;
        cla_matrix_lup_ptr_t a_lup = NULL;
        cla_matrix_ptr_t b = NULL;
        cla_matrix_ptr_t x_expected = NULL;
        cla_matrix_ptr_t x_computed = NULL;

        ESP_LOGI(CONFIG_APP_TAG, "Matrix Linear System Solve Test Case: %lu", (uint16_t)k + 1);

        // create matrix A instances and populate with test data
        const uint16_t a_rows = cla_matrix_ls_solve_a_rows[k];
        const uint16_t a_cols = cla_matrix_ls_solve_a_cols[k];
        const double  *a_mats = (const double *)cla_matrix_ls_solve_a_mats[k];
        cla_matrix_create(a_rows, a_cols, &a);
        for(uint16_t i = 0; i < a->num_rows; i++) {
            for(uint16_t j = 0; j < a->num_cols; j++) {
                a->data[i][j] = a_mats[i * a->num_cols + j];
            }
        }

        // perform LUP decomposition on matrix A
        cla_matrix_lup_solve(a, &a_lup);

        // create matrix B instances and populate with test data
        const uint16_t b_rows = cla_matrix_ls_solve_b_rows[k];
        const uint16_t b_cols = cla_matrix_ls_solve_b_cols[k];
        const double  *b_mats = (const double *)cla_matrix_ls_solve_b_mats[k];
        cla_matrix_create(b_rows, b_cols, &b);
        for(uint16_t i = 0; i < b->num_rows; i++) {
            for(uint16_t j = 0; j < b->num_cols; j++) {
                b->data[i][j] = b_mats[i * b->num_cols + j];
            }
        }

        // create expected matrix X instances and populate with test data
        const uint16_t x_rows = cla_matrix_ls_solve_x_rows[k];
        const uint16_t x_cols = cla_matrix_ls_solve_x_cols[k];
        const double  *x_mats = (const double *)cla_matrix_ls_solve_x_mats[k];
        cla_matrix_create(x_rows, x_cols, &x_expected);
        for(uint16_t i = 0; i < x_expected->num_rows; i++) {
            for(uint16_t j = 0; j < x_expected->num_cols; j++) {
                x_expected->data[i][j] = x_mats[i * x_expected->num_cols + j];
            }
        }

        // compute matrix X using linear system solve function
        cla_matrix_ls_solve(a_lup, b, &x_computed);

        // print matrices
        ESP_LOGI(CONFIG_APP_TAG, "Matrix A:");
        cla_matrix_print(a);
        ESP_LOGI(CONFIG_APP_TAG, "Matrix B:");
        cla_matrix_print(b);
        ESP_LOGI(CONFIG_APP_TAG, "Expected X:");
        cla_matrix_print(x_expected);
        ESP_LOGI(CONFIG_APP_TAG, "Computed X:");
        cla_matrix_print(x_computed);

        // free matrices
        cla_matrix_delete(a);
        cla_matrix_lup_delete(a_lup);
        cla_matrix_delete(b);
        cla_matrix_delete(x_computed);
        cla_matrix_delete(x_expected);
    }
    ESP_LOGI(CONFIG_APP_TAG, "Matrix Linear System Solve Test Cases - End");
}

static inline void cla_matrix_lup_solve_test(void) {
    ESP_LOGI(CONFIG_APP_TAG, "Matrix LUP Solve Test Cases - Begin");
    // iterate through all test cases
    for(uint8_t k = 0; k < cla_matrix_lup_solve_cases; k++) {
        cla_matrix_ptr_t input = NULL;
        cla_matrix_lup_ptr_t input_lup = NULL;
        cla_matrix_ptr_t p_dot_input = NULL;
        cla_matrix_ptr_t l_dot_u = NULL;

        ESP_LOGI(CONFIG_APP_TAG, "Matrix LUP Solve Test Case: %lu", (uint16_t)k + 1);

        // create matrix input instances and populate with test data
        const uint16_t rows = cla_matrix_lup_solve_rows[k];
        const uint16_t cols = cla_matrix_lup_solve_cols[k];
        const double  *mats = (const double *)cla_matrix_lup_solve_mats[k];
        cla_matrix_create(rows, cols, &input);
        for(uint16_t i = 0; i < input->num_rows; i++) {
            for(uint16_t j = 0; j < input->num_cols; j++) {
                input->data[i][j] = mats[i * input->num_cols + j];
            }
        }

        // perform LUP decomposition on input matrix
        cla_matrix_lup_solve(input, &input_lup);

        // compute P dot product from input matrix
        cla_matrix_get_dot_product(input_lup->p, input, &p_dot_input);

        // compute L dot product from U matrix
        cla_matrix_get_dot_product(input_lup->l, input_lup->u, &l_dot_u);

        // print matrices
        ESP_LOGI(CONFIG_APP_TAG, "P DOT Input Matrix:");
        cla_matrix_print(p_dot_input);
        ESP_LOGI(CONFIG_APP_TAG, "L DOT U Matrix:");
        cla_matrix_print(l_dot_u);

        // free matrices
        cla_matrix_delete(input);
        cla_matrix_lup_delete(input_lup);
        cla_matrix_delete(p_dot_input);
        cla_matrix_delete(l_dot_u);
    }
    ESP_LOGI(CONFIG_APP_TAG, "Matrix LUP Solve Test Cases - End");
}


static inline void cla_matrix_lup_inverse_test(void) {
    ESP_LOGI(CONFIG_APP_TAG, "Matrix LUP Inverse Test Cases - Begin");
    // iterate through all test cases
    for(uint8_t k = 0; k < cla_matrix_lup_inverse_cases; k++) {
        cla_matrix_ptr_t a = NULL;
        cla_matrix_lup_ptr_t a_lup = NULL;
        cla_matrix_ptr_t x_inv_computed = NULL;
        cla_matrix_ptr_t x_inv_expected = NULL;
        cla_matrix_ptr_t a_dot_inv_computed = NULL;
        cla_matrix_ptr_t eye = NULL;

        ESP_LOGI(CONFIG_APP_TAG, "Matrix LUP Inverse Test Case: %lu", (uint16_t)k + 1);

        // create matrix A instances and populate with test data
        const uint16_t a_rows = cla_matrix_lup_inverse_a_rows[k];
        const uint16_t a_cols = cla_matrix_lup_inverse_a_cols[k];
        const double  *a_mats = (const double *)cla_matrix_lup_inverse_a_mats[k];
        cla_matrix_create(a_rows, a_cols, &a);
        for(uint16_t i = 0; i < a->num_rows; i++) {
            for(uint16_t j = 0; j < a->num_cols; j++) {
                a->data[i][j] = a_mats[i * a->num_cols + j];
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
        const uint16_t x_rows = cla_matrix_lup_inverse_x_rows[k];
        const uint16_t x_cols = cla_matrix_lup_inverse_x_cols[k];
        const double  *x_mats = cla_matrix_lup_inverse_x_mats[k];
        cla_matrix_create(x_rows, x_cols, &x_inv_expected);
        for(uint16_t i = 0; i < x_inv_expected->num_rows; i++) {
            for(uint16_t j = 0; j < x_inv_expected->num_cols; j++) {
                x_inv_expected->data[i][j] = x_mats[i * x_inv_expected->num_cols + j];
            }
        }

        // print matrices
        ESP_LOGI(CONFIG_APP_TAG, "Matrix A:");
        cla_matrix_print(a);
        ESP_LOGI(CONFIG_APP_TAG, "Expected X Inverse:");
        cla_matrix_print(x_inv_expected);
        ESP_LOGI(CONFIG_APP_TAG, "Computed X Inverse:");
        cla_matrix_print(x_inv_computed);

        // free matrices
        cla_matrix_delete(a);
        cla_matrix_lup_delete(a_lup);
        cla_matrix_delete(x_inv_computed);
        cla_matrix_delete(x_inv_expected);
        cla_matrix_delete(a_dot_inv_computed);
        cla_matrix_delete(eye);
    }
    ESP_LOGI(CONFIG_APP_TAG, "Matrix LUP Inverse Test Cases - End");
}


static inline void cla_matrix_lup_determinant_test(void) {
    ESP_LOGI(CONFIG_APP_TAG, "Matrix LUP Determinant Test Cases - Begin");
    // iterate through all test cases
    for(uint16_t k = 0; k < cla_matrix_lup_determinant_cases; k++) {
        cla_matrix_ptr_t a = NULL;
        cla_matrix_lup_ptr_t a_lup = NULL;
        double x_computed = NAN;

        ESP_LOGI(CONFIG_APP_TAG, "Matrix LUP Determinant Test Case: %lu", (uint16_t)k + 1);

        // create matrix A instances and populate with test data
        const uint16_t rows = cla_matrix_lup_determinant_a_rows[k];
        const uint16_t cols = cla_matrix_lup_determinant_a_cols[k];
        const double  *mats = (const double *)cla_matrix_lup_determinant_a_mats[k];
        cla_matrix_create(rows, cols, &a);
        for(uint16_t i = 0; i < a->num_rows; i++) {
            for(uint16_t j = 0; j < a->num_cols; j++) {
                a->data[i][j] = mats[i * a->num_cols + j];
            }
        }

        // get expected determinant value
        const double x_expected = cla_matrix_lup_determinant_x_vals[k];

        // perform LUP decomposition on matrix A
        cla_matrix_lup_solve(a, &a_lup);

        // compute determinant from LUP decomposition
        cla_matrix_lup_get_determinant(a_lup, &x_computed);

        // print matrices
        ESP_LOGI(CONFIG_APP_TAG, "A Matrix:");
        cla_matrix_print(a);
        ESP_LOGI(CONFIG_APP_TAG, "Expected X Determinant:");
        printf("\n%.f\n", x_expected);
        ESP_LOGI(CONFIG_APP_TAG, "Computed X Determinant:");
        printf("\n%.f\n", x_computed);

        // free matrices
        cla_matrix_delete(a);
        cla_matrix_lup_delete(a_lup);
    }
    ESP_LOGI(CONFIG_APP_TAG, "Matrix LUP Determinant Test Cases - End");
}

static inline void cla_matrix_qr_decomposition_test(void) {
    ESP_LOGI(CONFIG_APP_TAG, "Matrix QR Decomposition Test Cases - Begin");
    // iterate through all test cases
    for(uint16_t k = 0; k < cla_matrix_qr_decomposition_cases; k++) {
        cla_matrix_ptr_t a = NULL;
        cla_matrix_qr_ptr_t a_qr = NULL;
        cla_matrix_ptr_t qr_dot = NULL;

        ESP_LOGI(CONFIG_APP_TAG, "Matrix QR Decomposition Test Case: %lu", (uint16_t)k + 1);

        // create matrix A instances and populate with test data
        const uint16_t rows = cla_matrix_qr_decomposition_a_rows[k];
        const uint16_t cols = cla_matrix_qr_decomposition_a_cols[k];
        const double  *mats = (const double *)cla_matrix_qr_decomposition_a_mats[k];
        cla_matrix_create(rows, cols, &a);
        for(uint16_t i = 0; i < a->num_rows; i++) {
            for(uint16_t j = 0; j < a->num_cols; j++) {
                a->data[i][j] = *((mats + i*a->num_cols) + j);
            }
        }

        // perform QR decomposition on matrix A
        cla_matrix_qr_get_decomposition(a, &a_qr);

        // compute matrix dot product from Q and R matrices
        cla_matrix_multiply(a_qr->q, a_qr->r, &qr_dot);

        // print matrices
        ESP_LOGI(CONFIG_APP_TAG, "A Matrix:");
        cla_matrix_print(a);
        ESP_LOGI(CONFIG_APP_TAG, "Q*R Matrix:");
        cla_matrix_print(qr_dot);

        // free matrices
        cla_matrix_delete(a);
        cla_matrix_delete(qr_dot);
        cla_matrix_qr_delete(a_qr);
    }
    ESP_LOGI(CONFIG_APP_TAG, "Matrix QR Decomposition Test Cases - End");
}

static inline void cla_ellipsoid_fitting_test(void) {
    ESP_LOGI(CONFIG_APP_TAG, "Ellipsoid Fitting Test Cases - Begin");

    for (uint8_t k = 0; k < cla_ellipsoid_fitting_cases; k++) {
        cla_vector_samples_t calib_data;
        cla_ellipsoid_coeffs_t computed_coeffs = NULL;
        cla_ellipsoid_coeffs_t expected_coeffs = NULL;

        ESP_LOGI(CONFIG_APP_TAG, "Ellipsoid Fitting Test Case: %u", (uint16_t)k + 1);

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
        esp_err_t err = cla_solve_ellipsoid_coefficients(calib_data, &computed_coeffs);

        if (err == ESP_OK) {
            ESP_LOGI(CONFIG_APP_TAG, "Computed Ellipsoid Coefficients:");
            printf("Computed Coeffs: ");
            for(int i=0; i<computed_coeffs->num_cmps; i++) {
                printf("%.4f ", computed_coeffs->data[i]);
            }
            printf("\n");
            printf("Expected Coeffs: ");
            for(int i=0; i<expected_coeffs->num_cmps; i++) {
                printf("%.4f ", expected_coeffs->data[i]);
            }
            printf("\n");
            //
            //printf("\n");
            //printf("Expected Coeffs Iterator: ");
            //cla_vector_iterator_t it = cla_vector_begin(computed_coeffs);
            //cla_vector_iterator_t last = cla_vector_end(computed_coeffs);
            //for(; !cla_vector_iterator_equals(it, last); cla_vector_iterator_increment(&it)) {
            //    double* value = cla_vector_iterator_get(it);
            //    printf("%.4lf ", *value);
            //}
            //printf("\n");
            //
        } else {
            ESP_LOGE(CONFIG_APP_TAG, "Ellipsoid fitting failed with error: %s", esp_err_to_name(err));
        }

        // Derive calibration parameters (hard and soft iron)
        cla_vector_ptr_t hard_iron = NULL;
        cla_matrix_ptr_t soft_iron = NULL;
        err = cla_get_calibration_parameters(computed_coeffs, &hard_iron, &soft_iron);
        if (err == ESP_OK) {
            ESP_LOGI(CONFIG_APP_TAG, "Hard Iron Parameters:");
            printf("Hard Iron: ");
            for(int i=0; i<hard_iron->num_cmps; i++) {
                printf("%.4f ", hard_iron->data[i]);
            }
            printf("\n");
            ESP_LOGI(CONFIG_APP_TAG, "Soft Iron Parameters:");
            printf("Soft Iron: ");
            for(int i=0; i<soft_iron->num_rows; i++) {
                for(int j=0; j<soft_iron->num_cols; j++) {
                    printf("%.4f ", soft_iron->data[i][j]);
                }
            }
            printf("\n");
        } else {
            ESP_LOGE(CONFIG_APP_TAG, "Calibration parameters retrieval failed with error: %s", esp_err_to_name(err));
        }
        

        // Cleanup
        for (int i = 0; i < CLA_CAL_SAMPLE_SIZE; i++) {
            cla_vector_delete(calib_data[i]);
        }
        cla_vector_delete(computed_coeffs);
        cla_vector_delete(expected_coeffs);
        cla_matrix_delete(soft_iron);
        cla_vector_delete(hard_iron);
    }
    ESP_LOGI(CONFIG_APP_TAG, "Ellipsoid Fitting Test Cases - End");
}

static void i2c_0_task( void *pvParameters ) {
    // initialize the xLastWakeTime variable with the current time.
    TickType_t              xLastWakeTime   = xTaskGetTickCount ();
    //
    //
    //
    //
    // task loop entry point
    for ( ;; ) {
        //ESP_LOGI(CONFIG_APP_TAG, "######################## CLA - START #########################");

        //cla_matrix_qr_decomposition_test();
        //cla_matrix_lup_determinant_test();
        //cla_matrix_lup_inverse_test();
        //cla_matrix_lup_solve_test();
        //cla_ls_solve_fwd_test();
        //cla_ls_solve_bck_test();
        //cla_ls_solve_test();
        cla_ellipsoid_fitting_test();
        //
        //ESP_LOGI(CONFIG_APP_TAG, "######################## CLA - END ###########################");
        //
        //
        // pause the task per defined wait period (interval) in seconds
        vTaskDelaySecUntil( &xLastWakeTime, CONFIG_I2C_0_TASK_INTERVAL );
    }
    //
    // free resources
    vTaskDelete( NULL );                // delete task
}


void app_main( void ) {
    ESP_LOGI(CONFIG_APP_TAG, "Startup..");
    ESP_LOGI(CONFIG_APP_TAG, "Free memory: %lu bytes", esp_get_free_heap_size());
    ESP_LOGI(CONFIG_APP_TAG, "IDF version: %s", esp_get_idf_version());

    esp_log_level_set("*", ESP_LOG_INFO);
    esp_log_level_set(CONFIG_APP_TAG, ESP_LOG_VERBOSE);

    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK( nvs_flash_erase() );
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );
    
    xTaskCreatePinnedToCore( 
        i2c_0_task, 
        CONFIG_I2C_0_TASK_NAME, 
        CONFIG_I2C_0_TASK_STACK_SIZE, 
        NULL, 
        CONFIG_I2C_0_TASK_PRIORITY, 
        NULL, 
        APP_CPU_NUM );
}