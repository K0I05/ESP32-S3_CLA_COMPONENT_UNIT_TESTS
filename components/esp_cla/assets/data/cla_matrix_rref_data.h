/*                  MIT License (MIT)                       */
/*           AUTO GENERATED CODE - DO NOT MODIFY            */
/* Copyright (c) 2025 Eric Gionet (gionet.c.eric@gmail.com) */

#ifndef __CLA_MATRIX_RREF_TEST_DATA_H__
#define __CLA_MATRIX_RREF_TEST_DATA_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


static const uint8_t cla_matrix_rref_cases = 10;


static const uint16_t cla_matrix_rref_a_0_rows = 11;

static const uint16_t cla_matrix_rref_a_0_cols = 9;

static const double cla_matrix_rref_a_0_matrix[11][9] = {
	{ 7, 4, 5,1,10,7,5,5,5},
	{10, 5, 1,7, 2,7,7,4,0},
	{ 8, 8, 1,3, 6,0,5,6,4},
	{ 0, 5, 4,5, 0,9,7,4,3},
	{ 8, 3,10,1, 6,9,3,5,3},
	{10,10, 4,3, 9,1,7,0,5},
	{ 7, 7, 3,5, 0,8,7,1,8},
	{ 9, 2, 8,1, 6,6,1,7,3},
	{ 0, 0, 7,0, 0,4,1,7,4},
	{ 1, 1, 4,4, 0,0,9,3,2},
	{ 0, 2, 1,5, 4,0,9,8,0},};

static const uint16_t cla_matrix_rref_x_0_rows = 11;

static const uint16_t cla_matrix_rref_x_0_cols = 9;

static const double cla_matrix_rref_x_0_matrix[11][9] = {
	{1.00000000000000,               0,               0,               0,               0,               0,               0,               0,               0},
	{               0,1.00000000000000,               0,               0,               0,               0,               0,               0,               0},
	{               0,               0,1.00000000000000,               0,               0,               0,               0,               0,               0},
	{               0,               0,               0,1.00000000000000,               0,               0,               0,               0,               0},
	{               0,               0,               0,               0,1.00000000000000,               0,               0,               0,               0},
	{               0,               0,               0,               0,               0,1.00000000000000,               0,               0,               0},
	{               0,               0,               0,               0,               0,               0,1.00000000000000,               0,               0},
	{               0,               0,               0,               0,               0,               0,               0,1.00000000000000,               0},
	{               0,               0,               0,               0,               0,               0,               0,               0,1.00000000000000},
	{               0,               0,               0,               0,               0,               0,               0,               0,               0},
	{               0,               0,               0,               0,               0,               0,               0,               0,               0},};

static const uint16_t cla_matrix_rref_a_1_rows = 6;

static const uint16_t cla_matrix_rref_a_1_cols = 4;

static const double cla_matrix_rref_a_1_matrix[6][4] = {
	{10,5,5,5},
	{ 5,0,7,1},
	{ 6,3,1,8},
	{ 4,3,1,7},
	{ 5,7,4,4},
	{ 5,5,7,9},};

static const uint16_t cla_matrix_rref_x_1_rows = 6;

static const uint16_t cla_matrix_rref_x_1_cols = 4;

static const double cla_matrix_rref_x_1_matrix[6][4] = {
	{1.00000000000000,               0,               0,               0},
	{               0,1.00000000000000,               0,               0},
	{               0,               0,1.00000000000000,               0},
	{               0,               0,               0,1.00000000000000},
	{               0,               0,               0,               0},
	{               0,               0,               0,               0},};

static const uint16_t cla_matrix_rref_a_2_rows = 6;

static const uint16_t cla_matrix_rref_a_2_cols = 14;

static const double cla_matrix_rref_a_2_matrix[6][14] = {
	{ 1,6, 6,6,2,10, 6,6,5, 2,9,6,2,1},
	{ 3,7, 0,0,9, 1, 6,9,1, 6,9,1,5,7},
	{ 7,1, 6,1,5, 9,10,0,1, 9,4,5,0,1},
	{10,3, 6,9,2, 4, 2,5,2, 1,7,0,0,5},
	{ 1,7,10,2,6, 9,10,9,1,10,3,2,8,9},
	{10,9, 1,7,4, 8, 3,4,7, 8,1,2,0,0},};

static const uint16_t cla_matrix_rref_x_2_rows = 6;

static const uint16_t cla_matrix_rref_x_2_cols = 14;

static const double cla_matrix_rref_x_2_matrix[6][14] = {
	{1.00000000000000,               0,               0,               0,               0,               0, -0.156255104248059,-0.538620120338856,-0.0384192612801123, 0.989859928397056, -1.63829918729335,-0.584672025851223,-0.137882018479033, 0.0193575158811091},
	{               0,1.00000000000000,               0,               0,               0,               0, -0.436654350254054, 0.425441558842875,  0.257028963434822,  1.13942267367687, -2.19529680788604,-0.917850852216292, 0.762615493958777,  0.549687233751385},
	{               0,               0,1.00000000000000,               0,               0,               0,  0.192687847364773, 0.387790417919277, -0.492034062164775, 0.603446829737735,-0.976236828280955,-0.670913401051530, 0.734896943852168,   1.10922318310842},
	{               0,               0,               0,1.00000000000000,               0,               0,-0.0788162117540072, 0.763348298436831,  0.324332198810738, -1.73802239909591,  3.04870059639690, 0.770292283039108,-0.401563610518834,-0.0678153156135913},
	{               0,               0,               0,               0,1.00000000000000,               0,  0.990460298330883, 0.901119954795676, -0.128885298441245,-0.573141391533901,  3.19823244028306, 0.912434279357428,0.0589907604832978,  0.448944275958274},
	{               0,               0,               0,               0,               0,1.00000000000000,  0.611203079544602,-0.472310144044639,  0.476022725767789, 0.212734022875860, 0.497883254534779, 0.967063528850865,-0.455579246624023, -0.946381667527491},};

static const uint16_t cla_matrix_rref_a_3_rows = 13;

static const uint16_t cla_matrix_rref_a_3_cols = 7;

static const double cla_matrix_rref_a_3_matrix[13][7] = {
	{ 5, 5, 7, 7, 2, 0, 6},
	{ 4, 7, 1,10, 1, 0, 0},
	{ 4, 3, 0, 4, 0, 5,10},
	{ 6,10, 2, 0, 5, 6, 8},
	{ 3, 9, 0, 5, 9, 3, 4},
	{ 0, 9, 4, 8, 2, 8, 9},
	{ 7, 0, 3, 2, 3, 3, 3},
	{ 1, 5, 0, 4, 8,10, 2},
	{10, 8,10, 3,10, 2, 0},
	{ 0, 7, 0, 6, 3, 1, 5},
	{ 5, 6,10, 5, 6, 1, 3},
	{ 5, 3, 1, 4, 0, 0, 9},
	{ 9, 8, 1, 4, 2, 2, 2},};

static const uint16_t cla_matrix_rref_x_3_rows = 13;

static const uint16_t cla_matrix_rref_x_3_cols = 7;

static const double cla_matrix_rref_x_3_matrix[13][7] = {
	{1.00000000000000,               0,               0,               0,               0,               0,               0},
	{               0,1.00000000000000,               0,               0,               0,               0,               0},
	{               0,               0,1.00000000000000,               0,               0,               0,               0},
	{               0,               0,               0,1.00000000000000,               0,               0,               0},
	{               0,               0,               0,               0,1.00000000000000,               0,               0},
	{               0,               0,               0,               0,               0,1.00000000000000,               0},
	{               0,               0,               0,               0,               0,               0,1.00000000000000},
	{               0,               0,               0,               0,               0,               0,               0},
	{               0,               0,               0,               0,               0,               0,               0},
	{               0,               0,               0,               0,               0,               0,               0},
	{               0,               0,               0,               0,               0,               0,               0},
	{               0,               0,               0,               0,               0,               0,               0},
	{               0,               0,               0,               0,               0,               0,               0},};

static const uint16_t cla_matrix_rref_a_4_rows = 4;

static const uint16_t cla_matrix_rref_a_4_cols = 3;

static const double cla_matrix_rref_a_4_matrix[4][3] = {
	{ 6,4,4},
	{10,7,3},
	{ 0,5,6},
	{ 0,2,6},};

static const uint16_t cla_matrix_rref_x_4_rows = 4;

static const uint16_t cla_matrix_rref_x_4_cols = 3;

static const double cla_matrix_rref_x_4_matrix[4][3] = {
	{1.00000000000000,               0,               0},
	{               0,1.00000000000000,               0},
	{               0,               0,1.00000000000000},
	{               0,               0,               0},};

static const uint16_t cla_matrix_rref_a_5_rows = 3;

static const uint16_t cla_matrix_rref_a_5_cols = 5;

static const double cla_matrix_rref_a_5_matrix[3][5] = {
	{ 2,8,4,10, 8},
	{ 0,0,6, 5,10},
	{10,3,0,10, 0},};

static const uint16_t cla_matrix_rref_x_5_rows = 3;

static const uint16_t cla_matrix_rref_x_5_cols = 5;

static const double cla_matrix_rref_x_5_matrix[3][5] = {
	{1.00000000000000,               0,               0,0.810810810810811,-0.0540540540540541},
	{               0,1.00000000000000,               0,0.630630630630631,  0.180180180180180},
	{               0,               0,1.00000000000000,0.833333333333333,   1.66666666666667},};

static const uint16_t cla_matrix_rref_a_6_rows = 10;

static const uint16_t cla_matrix_rref_a_6_cols = 6;

static const double cla_matrix_rref_a_6_matrix[10][6] = {
	{4,10, 8,7, 0, 8},
	{3, 3, 2,1, 5,10},
	{3, 5, 7,6,10, 2},
	{5, 3,10,9, 0, 3},
	{0, 9, 8,8, 0, 9},
	{9, 7, 2,6, 6, 0},
	{2, 7, 0,7, 8, 7},
	{3, 1, 6,1, 2, 6},
	{4, 7, 3,1,10, 2},
	{2, 8, 4,0, 8, 2},};

static const uint16_t cla_matrix_rref_x_6_rows = 10;

static const uint16_t cla_matrix_rref_x_6_cols = 6;

static const double cla_matrix_rref_x_6_matrix[10][6] = {
	{1.00000000000000,               0,               0,               0,               0,               0},
	{               0,1.00000000000000,               0,               0,               0,               0},
	{               0,               0,1.00000000000000,               0,               0,               0},
	{               0,               0,               0,1.00000000000000,               0,               0},
	{               0,               0,               0,               0,1.00000000000000,               0},
	{               0,               0,               0,               0,               0,1.00000000000000},
	{               0,               0,               0,               0,               0,               0},
	{               0,               0,               0,               0,               0,               0},
	{               0,               0,               0,               0,               0,               0},
	{               0,               0,               0,               0,               0,               0},};

static const uint16_t cla_matrix_rref_a_7_rows = 10;

static const uint16_t cla_matrix_rref_a_7_cols = 4;

static const double cla_matrix_rref_a_7_matrix[10][4] = {
	{1, 0, 0,3},
	{6, 8,10,2},
	{2, 6, 3,2},
	{3, 4, 5,1},
	{0,10, 9,1},
	{6, 1, 0,7},
	{1, 3, 2,6},
	{8, 8, 7,3},
	{9, 0, 4,1},
	{2, 5, 7,6},};

static const uint16_t cla_matrix_rref_x_7_rows = 10;

static const uint16_t cla_matrix_rref_x_7_cols = 4;

static const double cla_matrix_rref_x_7_matrix[10][4] = {
	{1.00000000000000,               0,               0,               0},
	{               0,1.00000000000000,               0,               0},
	{               0,               0,1.00000000000000,               0},
	{               0,               0,               0,1.00000000000000},
	{               0,               0,               0,               0},
	{               0,               0,               0,               0},
	{               0,               0,               0,               0},
	{               0,               0,               0,               0},
	{               0,               0,               0,               0},
	{               0,               0,               0,               0},};

static const uint16_t cla_matrix_rref_a_8_rows = 7;

static const uint16_t cla_matrix_rref_a_8_cols = 11;

static const double cla_matrix_rref_a_8_matrix[7][11] = {
	{10,8,8,0,0,9,5,2,4,8,4},
	{ 7,5,0,9,5,4,4,3,3,4,9},
	{ 1,9,1,6,0,7,7,1,8,1,8},
	{10,2,8,0,9,2,9,3,0,8,3},
	{ 2,2,3,1,2,4,7,1,4,5,5},
	{ 9,0,2,3,9,4,9,7,7,0,0},
	{ 6,2,7,9,0,4,2,7,4,4,5},};

static const uint16_t cla_matrix_rref_x_8_rows = 7;

static const uint16_t cla_matrix_rref_x_8_cols = 11;

static const double cla_matrix_rref_x_8_matrix[7][11] = {
	{1.00000000000000,               0,               0,               0,               0,               0,               0, -14.5104042412193, -16.2367793240557, 32.7821073558648, 27.3348575215374},
	{               0,1.00000000000000,               0,               0,               0,               0,               0, -1.47294013695604, -1.31941683233930, 2.03379721669980, 2.06008394079965},
	{               0,               0,1.00000000000000,               0,               0,               0,               0,  8.24581400485973,  8.60165672630881,-17.3721669980119,-15.0505191075768},
	{               0,               0,               0,1.00000000000000,               0,               0,               0,-0.605301524188204,-0.874155069582505, 2.23419483101392, 2.47190192180252},
	{               0,               0,               0,               0,1.00000000000000,               0,               0,  20.7167218908770,  22.4809807819748,-45.8795228628231,-38.6747073116854},
	{               0,               0,               0,               0,               0,1.00000000000000,               0,  18.9172520432958,  21.1783962889331,-41.0429423459245,-34.6318975038657},
	{               0,               0,               0,               0,               0,               0,1.00000000000000, -15.4668433841396, -16.4991385023194, 34.4544731610338, 29.2523967307268},};

static const uint16_t cla_matrix_rref_a_9_rows = 2;

static const uint16_t cla_matrix_rref_a_9_cols = 8;

static const double cla_matrix_rref_a_9_matrix[2][8] = {
	{ 3,2, 5,10,4,5,7,3},
	{10,0,10, 1,1,0,1,0},};

static const uint16_t cla_matrix_rref_x_9_rows = 2;

static const uint16_t cla_matrix_rref_x_9_cols = 8;

static const double cla_matrix_rref_x_9_matrix[2][8] = {
	{1.00000000000000,               0,1.00000000000000,0.100000000000000,0.100000000000000,               0,0.100000000000000,               0},
	{               0,1.00000000000000,1.00000000000000, 4.85000000000000, 1.85000000000000,2.50000000000000, 3.35000000000000,1.50000000000000},};

static const uint16_t cla_matrix_rref_a_rows[10] = { cla_matrix_rref_a_0_rows, cla_matrix_rref_a_1_rows, cla_matrix_rref_a_2_rows, cla_matrix_rref_a_3_rows, cla_matrix_rref_a_4_rows, cla_matrix_rref_a_5_rows, cla_matrix_rref_a_6_rows, cla_matrix_rref_a_7_rows, cla_matrix_rref_a_8_rows, cla_matrix_rref_a_9_rows,};

static const uint16_t cla_matrix_rref_a_cols[10] = { cla_matrix_rref_a_0_cols, cla_matrix_rref_a_1_cols, cla_matrix_rref_a_2_cols, cla_matrix_rref_a_3_cols, cla_matrix_rref_a_4_cols, cla_matrix_rref_a_5_cols, cla_matrix_rref_a_6_cols, cla_matrix_rref_a_7_cols, cla_matrix_rref_a_8_cols, cla_matrix_rref_a_9_cols,};

static const double *cla_matrix_rref_a_mats[10]  = { &cla_matrix_rref_a_0_matrix[0][0], &cla_matrix_rref_a_1_matrix[0][0], &cla_matrix_rref_a_2_matrix[0][0], &cla_matrix_rref_a_3_matrix[0][0], &cla_matrix_rref_a_4_matrix[0][0], &cla_matrix_rref_a_5_matrix[0][0], &cla_matrix_rref_a_6_matrix[0][0], &cla_matrix_rref_a_7_matrix[0][0], &cla_matrix_rref_a_8_matrix[0][0], &cla_matrix_rref_a_9_matrix[0][0],};

static const uint16_t cla_matrix_rref_x_rows[10] = { cla_matrix_rref_x_0_rows, cla_matrix_rref_x_1_rows, cla_matrix_rref_x_2_rows, cla_matrix_rref_x_3_rows, cla_matrix_rref_x_4_rows, cla_matrix_rref_x_5_rows, cla_matrix_rref_x_6_rows, cla_matrix_rref_x_7_rows, cla_matrix_rref_x_8_rows, cla_matrix_rref_x_9_rows,};

static const uint16_t cla_matrix_rref_x_cols[10] = { cla_matrix_rref_x_0_cols, cla_matrix_rref_x_1_cols, cla_matrix_rref_x_2_cols, cla_matrix_rref_x_3_cols, cla_matrix_rref_x_4_cols, cla_matrix_rref_x_5_cols, cla_matrix_rref_x_6_cols, cla_matrix_rref_x_7_cols, cla_matrix_rref_x_8_cols, cla_matrix_rref_x_9_cols,};

static const double *cla_matrix_rref_x_mats[10]  = { &cla_matrix_rref_x_0_matrix[0][0], &cla_matrix_rref_x_1_matrix[0][0], &cla_matrix_rref_x_2_matrix[0][0], &cla_matrix_rref_x_3_matrix[0][0], &cla_matrix_rref_x_4_matrix[0][0], &cla_matrix_rref_x_5_matrix[0][0], &cla_matrix_rref_x_6_matrix[0][0], &cla_matrix_rref_x_7_matrix[0][0], &cla_matrix_rref_x_8_matrix[0][0], &cla_matrix_rref_x_9_matrix[0][0],};

#ifdef __cplusplus
}
#endif

#endif  // __CLA_MATRIX_RREF_TEST_DATA_H__
