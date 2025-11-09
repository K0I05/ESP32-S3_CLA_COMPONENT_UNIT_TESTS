# Compact Linear Algebra (CLA) Component Unit Tests

[![K0I05](https://img.shields.io/badge/K0I05-a9a9a9?logo=data:image/svg%2bxml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHdpZHRoPSIxODgiIGhlaWdodD0iMTg3Ij48cGF0aCBmaWxsPSIjNDU0QjU0IiBkPSJNMTU1LjU1NSAyMS45M2MxOS4yNzMgMTUuOTggMjkuNDcyIDM5LjM0NSAzMi4xNjggNjMuNzg5IDEuOTM3IDIyLjkxOC00LjU1MyA0Ni42Ni0xOC44NDggNjQuNzgxQTUwOS40NzggNTA5LjQ3OCAwIDAgMSAxNjUgMTU1bC0xLjQ4NCAxLjg4M2MtMTMuMTk2IDE2LjUzMS0zNS41NTUgMjcuMjE1LTU2LjMzOSAyOS45MDItMjguMzEyIDIuOC01Mi4yNTUtNC43MzctNzQuNzMyLTIxLjcxNUMxMy4xNzIgMTQ5LjA5IDIuOTczIDEyNS43MjUuMjc3IDEwMS4yODEtMS42NiA3OC4zNjMgNC44MyA1NC42MjEgMTkuMTI1IDM2LjVBNTA5LjQ3OCA1MDkuNDc4IDAgMCAxIDIzIDMybDEuNDg0LTEuODgzQzM3LjY4IDEzLjU4NiA2MC4wNCAyLjkwMiA4MC44MjMuMjE1YzI4LjMxMi0yLjggNTIuMjU1IDQuNzM3IDc0LjczMiAyMS43MTVaIi8+PHBhdGggZmlsbD0iI0ZERkRGRCIgZD0iTTExOS44NjcgNDUuMjdDMTI4LjkzMiA1Mi4yNiAxMzMuODIgNjMgMTM2IDc0Yy42MyA0Ljk3Mi44NDIgOS45NTMuOTUzIDE0Ljk2LjA0NCAxLjkxMS4xMjIgMy44MjIuMjAzIDUuNzMxLjM0IDEyLjIxLjM0IDEyLjIxLTMuMTU2IDE3LjMwOWE5NS42MDQgOTUuNjA0IDAgMCAxLTQuMTg4IDMuNjI1Yy00LjUgMy43MTctNi45NzQgNy42ODgtOS43MTcgMTIuODAzQzEwNi45NCAxNTIuNzkyIDEwNi45NCAxNTIuNzkyIDk3IDE1N2MtMy40MjMuNTkyLTUuODAxLjY4NS04Ljg3OS0xLjA3NC05LjgyNi03Ljg4LTE2LjAzNi0xOS41OS0yMS44NTgtMzAuNTEyLTIuNTM0LTQuNTc1LTUuMDA2LTcuMjEtOS40NjYtMTAuMDItMy43MTQtMi44ODItNS40NS02Ljk4Ni02Ljc5Ny0xMS4zOTQtLjU1LTQuODg5LS41NjEtOS4zMTYgMS0xNCAuMDkzLTEuNzYzLjE4Mi0zLjUyNy4yMzktNS4yOTIuNDkxLTEzLjg4NCAzLjg2Ni0yNy4wNTcgMTQuMTU2LTM3LjAyOCAxNy4yMTgtMTQuMzM2IDM1Ljg1OC0xNS4wNjYgNTQuNDcyLTIuNDFaIi8+PHBhdGggZmlsbD0iI0M2RDVFMCIgZD0iTTEwOSAzOWMxMS43MDMgNS4yNTUgMTkuMjA2IDEzLjE4NiAyNC4yOTMgMjUuMDA0IDIuODU3IDguMjQgMy40NyAxNi4zMTYgMy42NiAyNC45NTYuMDQ0IDEuOTExLjEyMiAzLjgyMi4yMDMgNS43MzEuMzQgMTIuMjEuMzQgMTIuMjEtMy4xNTYgMTcuMzA5YTk1LjYwNCA5NS42MDQgMCAwIDEtNC4xODggMy42MjVjLTQuNSAzLjcxNy02Ljk3NCA3LjY4OC05LjcxNyAxMi44MDNDMTA2LjgwNCAxNTMuMDQxIDEwNi44MDQgMTUzLjA0MSA5NyAxNTdjLTIuMzMyLjA3OC00LjY2OC4wOS03IDBsMi4xMjUtMS44NzVjNS40My01LjQ0NSA4Ljc0NC0xMi41NzcgMTEuNzU0LTE5LjU1OWEzNDkuNzc1IDM0OS43NzUgMCAwIDEgNC40OTYtOS44NzlsMS42NDgtMy41NWMyLjI0LTMuNTU1IDQuNDEtNC45OTYgNy45NzctNy4xMzcgMi4zMjMtMi42MSAyLjMyMy0yLjYxIDQtNWwtMyAxYy0yLjY4LjE0OC01LjMxOS4yMy04IC4yNWwtMi4xOTUuMDYzYy01LjI4Ny4wMzktNS4yODcuMDM5LTcuNzc4LTEuNjUzLTEuNjY2LTIuNjkyLTEuNDUzLTQuNTYtMS4wMjctNy42NiAyLjM5NS00LjM2MiA0LjkyNC04LjA0IDkuODI4LTkuNTcgMi4zNjQtLjQ2OCA0LjUxNC0uNTI4IDYuOTIyLS40OTNsMi40MjIuMDI4TDEyMSA5MmwtMS0yYTkyLjc1OCA5Mi43NTggMCAwIDEtLjM2LTQuNTg2QzExOC42IDY5LjYzMiAxMTYuNTE3IDU2LjA5NCAxMDQgNDVjLTUuOTA0LTQuNjY0LTExLjYtNi4wODgtMTktNyA3LjU5NC00LjI2NCAxNi4yMjMtMS44MSAyNCAxWiIvPjxwYXRoIGZpbGw9IiM0OTUwNTgiIGQ9Ik03NyA5MmM0LjYxMyAxLjY3MSA3LjI2IDMuOTQ1IDEwLjA2MyA3LjkzOCAxLjA3OCAzLjUyMy45NzYgNS41NDYtLjA2MyA5LjA2Mi0yLjk4NCAyLjk4NC02LjI1NiAyLjM2OC0xMC4yNSAyLjM3NWwtMi4yNzcuMDc0Yy01LjI5OC4wMjgtOC4yNTQtLjk4My0xMi40NzMtNC40NDktMi44MjYtMy41OTctMi40MTYtNy42MzQtMi0xMiA0LjUwMi00LjcyOCAxMC45OS0zLjc2IDE3LTNaIi8+PHBhdGggZmlsbD0iIzQ4NEY1NyIgZD0ibTExOCA5MS43NSAzLjEyNS0uMDc4YzMuMjU0LjM3MSA0LjU5NyAxLjAwMiA2Ljg3NSAzLjMyOC42MzkgNC4yMzEuMjkgNi40NDItMS42ODggMTAuMjUtMy40MjggNC4wNzgtNS44MjcgNS41OTgtMTEuMTk1IDYuMTQ4LTEuNDE0LjAwOC0yLjgyOCAwLTQuMjQyLS4wMjNsLTIuMTY4LjAzNWMtMi45OTgtLjAxNy01LjE1Ny0uMDMzLTcuNjcyLTEuNzU4LTEuNjgxLTIuNjg0LTEuNDYtNC41NTItMS4wMzUtNy42NTIgMi4zNzUtNC4zMjUgNC44OTQtOC4wMDkgOS43NS05LjU1OSAyLjc3Ny0uNTQ0IDUuNDItLjY0OSA4LjI1LS42OTFaIi8+PHBhdGggZmlsbD0iIzUyNTg2MCIgZD0iTTg2IDEzNGgxNmwxIDRjLTIgMi0yIDItNS4xODggMi4yNjZMOTQgMTQwLjI1bC0zLjgxMy4wMTZDODcgMTQwIDg3IDE0MCA4NSAxMzhsMS00WiIvPjwvc3ZnPg==)](https://github.com/K0I05)
[![License: MIT](https://cdn.prod.website-files.com/5e0f1144930a8bc8aace526c/65dd9eb5aaca434fac4f1c34_License-MIT-blue.svg)](/LICENSE)
[![Language](https://img.shields.io/badge/Language-C-navy.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Framework](https://img.shields.io/badge/Framework-ESP_IDF-red.svg)](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/index.html)
[![Edited with VS Code](https://badgen.net/badge/icon/VS%20Code?icon=visualstudio&label=edited%20with)](https://code.visualstudio.com/)
[![Build with PlatformIO](https://img.shields.io/badge/build%20with-PlatformIO-orange?logo=data%3Aimage%2Fsvg%2Bxml%3Bbase64%2CPHN2ZyB3aWR0aD0iMjUwMCIgaGVpZ2h0PSIyNTAwIiB2aWV3Qm94PSIwIDAgMjU2IDI1NiIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIiBwcmVzZXJ2ZUFzcGVjdFJhdGlvPSJ4TWlkWU1pZCI+PHBhdGggZD0iTTEyOCAwQzkzLjgxIDAgNjEuNjY2IDEzLjMxNCAzNy40OSAzNy40OSAxMy4zMTQgNjEuNjY2IDAgOTMuODEgMCAxMjhjMCAzNC4xOSAxMy4zMTQgNjYuMzM0IDM3LjQ5IDkwLjUxQzYxLjY2NiAyNDIuNjg2IDkzLjgxIDI1NiAxMjggMjU2YzM0LjE5IDAgNjYuMzM0LTEzLjMxNCA5MC41MS0zNy40OUMyNDIuNjg2IDE5NC4zMzQgMjU2IDE2Mi4xOSAyNTYgMTI4YzAtMzQuMTktMTMuMzE0LTY2LjMzNC0zNy40OS05MC41MUMxOTQuMzM0IDEzLjMxNCAxNjIuMTkgMCAxMjggMCIgZmlsbD0iI0ZGN0YwMCIvPjxwYXRoIGQ9Ik0yNDkuMzg2IDEyOGMwIDY3LjA0LTU0LjM0NyAxMjEuMzg2LTEyMS4zODYgMTIxLjM4NkM2MC45NiAyNDkuMzg2IDYuNjEzIDE5NS4wNCA2LjYxMyAxMjggNi42MTMgNjAuOTYgNjAuOTYgNi42MTQgMTI4IDYuNjE0YzY3LjA0IDAgMTIxLjM4NiA1NC4zNDYgMTIxLjM4NiAxMjEuMzg2IiBmaWxsPSIjRkZGIi8+PHBhdGggZD0iTTE2MC44NjkgNzQuMDYybDUuMTQ1LTE4LjUzN2M1LjI2NC0uNDcgOS4zOTItNC44ODYgOS4zOTItMTAuMjczIDAtNS43LTQuNjItMTAuMzItMTAuMzItMTAuMzJzLTEwLjMyIDQuNjItMTAuMzIgMTAuMzJjMCAzLjc1NSAyLjAxMyA3LjAzIDUuMDEgOC44MzdsLTUuMDUgMTguMTk1Yy0xNC40MzctMy42Ny0yNi42MjUtMy4zOS0yNi42MjUtMy4zOWwtMi4yNTggMS4wMXYxNDAuODcybDIuMjU4Ljc1M2MxMy42MTQgMCA3My4xNzctNDEuMTMzIDczLjMyMy04NS4yNyAwLTMxLjYyNC0yMS4wMjMtNDUuODI1LTQwLjU1NS01Mi4xOTd6TTE0Ni41MyAxNjQuOGMtMTEuNjE3LTE4LjU1Ny02LjcwNi02MS43NTEgMjMuNjQzLTY3LjkyNSA4LjMyLTEuMzMzIDE4LjUwOSA0LjEzNCAyMS41MSAxNi4yNzkgNy41ODIgMjUuNzY2LTM3LjAxNSA2MS44NDUtNDUuMTUzIDUxLjY0NnptMTguMjE2LTM5Ljc1MmE5LjM5OSA5LjM5OSAwIDAgMC05LjM5OSA5LjM5OSA5LjM5OSA5LjM5OSAwIDAgMCA5LjQgOS4zOTkgOS4zOTkgOS4zOTkgMCAwIDAgOS4zOTgtOS40IDkuMzk5IDkuMzk5IDAgMCAwLTkuMzk5LTkuMzk4em0yLjgxIDguNjcyYTIuMzc0IDIuMzc0IDAgMSAxIDAtNC43NDkgMi4zNzQgMi4zNzQgMCAwIDEgMCA0Ljc0OXoiIGZpbGw9IiNFNTcyMDAiLz48cGF0aCBkPSJNMTAxLjM3MSA3Mi43MDlsLTUuMDIzLTE4LjkwMWMyLjg3NC0xLjgzMiA0Ljc4Ni01LjA0IDQuNzg2LTguNzAxIDAtNS43LTQuNjItMTAuMzItMTAuMzItMTAuMzItNS42OTkgMC0xMC4zMTkgNC42Mi0xMC4zMTkgMTAuMzIgMCA1LjY4MiA0LjU5MiAxMC4yODkgMTAuMjY3IDEwLjMxN0w5NS44IDc0LjM3OGMtMTkuNjA5IDYuNTEtNDAuODg1IDIwLjc0Mi00MC44ODUgNTEuODguNDM2IDQ1LjAxIDU5LjU3MiA4NS4yNjcgNzMuMTg2IDg1LjI2N1Y2OC44OTJzLTEyLjI1Mi0uMDYyLTI2LjcyOSAzLjgxN3ptMTAuMzk1IDkyLjA5Yy04LjEzOCAxMC4yLTUyLjczNS0yNS44OC00NS4xNTQtNTEuNjQ1IDMuMDAyLTEyLjE0NSAxMy4xOS0xNy42MTIgMjEuNTExLTE2LjI4IDMwLjM1IDYuMTc1IDM1LjI2IDQ5LjM2OSAyMy42NDMgNjcuOTI2em0tMTguODItMzkuNDZhOS4zOTkgOS4zOTkgMCAwIDAtOS4zOTkgOS4zOTggOS4zOTkgOS4zOTkgMCAwIDAgOS40IDkuNCA5LjM5OSA5LjM5OSAwIDAgMCA5LjM5OC05LjQgOS4zOTkgOS4zOTkgMCAwIDAtOS4zOTktOS4zOTl6bS0yLjgxIDguNjcxYTIuMzc0IDIuMzc0IDAgMSAxIDAtNC43NDggMi4zNzQgMi4zNzQgMCAwIDEgMCA0Ljc0OHoiIGZpbGw9IiNGRjdGMDAiLz48L3N2Zz4=)](https://platformio.org/)
[![PlatformIO CI](https://github.com/K0I05/ESP32-S3_CLA_COMPONENT_UNIT_TESTS/actions/workflows/pio_build.yml/badge.svg)](https://github.com/K0I05/ESP32-S3_CLA_COMPONENT_UNIT_TESTS/actions/workflows/pio_build.yml)
[![Maintenance](https://img.shields.io/badge/Maintained%3F-yes-green.svg)](https://github.com/K0I05/ESP32-S3_CLA_COMPONENT_UNIT_TESTS/graphs/commit-activity)

This repository is a collection of examples and unit tests for the compact linear algebra (CLA) component that is optimized and compatible with the ESP32 espressif IoT development framework (esp-idf).  The development environment is under Visual Studio Code with the PlatformIO (6.1.18) and ESP-IDF (v5.5.1) extensions.  The CLA test cases, matrix features and functionality was inspired by the [Neat Matrix Library (NML)](https://github.com/nomemory/neat-matrix-library) written in standard C.  There is an official digital signal processing library ([ESP-DSP](https://github.com/espressif/esp-dsp)) by expressif system.  However, the codebase is a mixure of C/C++ which was a key driver behind developing the CLA component in C.

The CLA component currently supports the following features and functionality:

* Matrix Operations (row swaps, column swaps, multiplication, addition, etc.)
  * Transpose
  * Determinant
  * DOT Product
  * LUP Decomposition
  * LUP Inverse
  * LUP Determinant
  * Solving Linear Systems of Equations
  * QR Decomposition
* Vector Operations (multiplication, addition, etc.)
  * DOT Product
  * CROSS Product
* Common Matrix & Vector Operations
  * Convert Vector to Matrix
  * Convert Matrix to Vector
  * Multiply Matrix by Vector
  * Ellipsoid Coefficients

```text
ESP32-S3_CLA_COMPONENT_UNIT_TESTS
├── assets
|   ├── data
|   |   └── cla_matrix_ls_solve_bck_data.h
|   |   └── ...
|   |   └── cla_matrix_lup_solve_data.h
|   └── generator
|       └── cla_matrix_ls_solve_bck_data_gen.py
|       └── ...
|       └── cls_matrix_lup_determinant_data_gen.py
├── components
│   └── esp_cla
├── include
├── src
│   └── CMakeLists.txt
│   └── main.c
├── test
|   ├── test_cla_matrix_ls_solve_bck
|   |   └── test_cla_matrix_ls_solve_bck.c
|   ├── test_cla_matrix_ls_solve_fwd
|   |   └── test_cla_matrix_ls_solve_fwd.c
│   └── test_cla_matrix_ls_solve
|       └── test_cla_matrix_ls_solve.c
└── CMakeLists.txt
└── LICENSE
└── platformio.ini
└── README.md
└── sdkconfig
└── sdkconfig.esp32s3box
```

## Data Generators

The data generators included with the CLA component are written in `python` and generate a C header file with datasets for 10 test cases by default.  The generated header file is stored in the `assets\data` folder by default, data in the datasets is generated randomly, and updated every time the data generator is executed.

The following data generators have been implemented to date:

* `cla_ellipsoid_fitting_data_gen.py`: Generates data to validate ellipsoid fitting calculations and algorithms.
* `cla_matrix_ls_solve_bck_data_gen.py`: Generates data to validate upper triangular system of equations calculations and algorithms.
* `cla_matrix_ls_solve_data_gen.py`: Generates data to validate system of equations calculations and algorithms.
* `cla_matrix_ls_solve_fwd_data_gen.py`: Generates data to validate lower triangular system of equations calculations and algorithms.
* `cls_matrix_lup_inverse_data_gen.py`: Generates data to validate LUP inverse calculations and algorithms.
* `cls_matrix_lup_solve_data_gen.py`: Generates data to validate LUP solve calculations and algorithms.
* `cls_matrix_lup_determinant_data_gen.py`: Generates data to validate LUP determinant calculations and algorithms.
* `cls_matrix_qr_solve_data_gen.py`: Generates data to validate QR solve calculations and algorithms.
* `cla_matrix_qr_decomposition_data_gen.py`: Generates data to validate QR decomposition calculations and algorithms.

The generated data stored in the header file use a common nomenclature for variables as shown in the following example (`cla_matrix_ls_solve_data_gen.py`):

```c
static const uint8_t cla_matrix_ls_solve_cases = 10;


static const uint16_t cla_matrix_ls_solve_a_rows[10] = {4, 7, 5, 8, 8, 14, 5, 3, 6, 5, };

static const uint16_t cla_matrix_ls_solve_a_cols[10] = {4, 7, 5, 8, 8, 14, 5, 3, 6, 5, };

static const double cla_matrix_ls_solve_a_mats[10][15][15] = {
{ {89,72,67, 1},
 {63,24,39,76},
 {83,99,81,23},
 {75,54,62,94},}, 
{ {54,21,56,65,92, 1,94},
 {49,53,32,10,87,11,85},
 {54,63,22,75,15,66,68},
 {39,30,31,88,13,34,14},
 {69,79,74,43,29, 9,88},
 {54,54,88,20,11,96,18},
 {94,74,42,59, 7,76,99},}, 
{ {16, 3,63,55,27},
 {87,92,91,77,82},
 { 6,76,60,63,83},
 {88,74,94,23, 6},
 {68, 4,97,22,17},}, 
{ { 88, 2,18,90,13,29,92,56},
 { 88,72,10,34, 3,72,19,47},
 { 73,83,83, 6, 5,43,16,87},
 { 64,51,70,90,31,65,22,44},
 { 58,79,29,31, 1,61,53,57},
 { 60,82,22,69, 7,42,79,63},
 {100,71,32,11, 1,90,68,54},
 { 65,95,78,72,32,88,93,12},}, 
{ {27,50,84,92,15,79,99, 30},
 {46,25,24,50,29,65,65,  7},
 { 5, 5,21,11,83,22,13,100},
 {52,34,59,17,12,15,55, 11},
 {23,98,35,96, 3,17,42, 46},
 {52,15,64,60,16,47,92,  6},
 {89,30, 4,24,57,36,36, 49},
 {84,36,82,99,41,26,94, 16},}, 
{ {100,40,  1,57,29,83, 18,67, 9,13,60,76,74,69},
 { 48,51, 55,63,20,19, 64,88,32,13,82,62,15,31},
 { 26,98, 15,22,52,78, 68,93,61,20,78,70,26,58},
 { 17,27, 13,45,83,96, 55,78,52, 4,85,47,76,32},
 {  6,57, 60,44,76,88, 36,16,75,69,86,79,26,92},
 { 47,76,100,89,59,35, 82,27, 4,67,79,87,35,28},
 { 25,98, 76,84,20,37, 27,59,62,65,64,54,75,71},
 { 61,24, 65,35,82,60, 16,31,79,61, 1,50,11,46},
 { 47,25, 36,38,92,23, 85,28, 6,85,13,28,92,84},
 { 35,19, 52,61,55,45,100,35,36,15,79,16,68,19},
 { 40,45, 29,34,13,13, 21,92,15,10,50,52,50,33},
 { 63,25, 15,75,71,26, 63,65,62,75,82,42,34, 5},
 { 34,63, 53, 9,92,64,  2,69,85,48, 2,44,79,19},
 { 79,41, 89,77,52, 4,  8,52, 4,20, 1,21,14,42},}, 
{ {75,46,34,59, 7},
 {52,60,85,84,39},
 {58,59,61,85,47},
 {33, 3,71,13,88},
 {80,40,20,61,56},}, 
{ { 9,63,98},
 {76,12,11},
 {61,33,25},}, 
{ {31,38,41,90,84,40},
 {68,12,56,82,25,44},
 {65,65,51,20,48,36},
 {82, 3,19, 3,83,69},
 { 4,42,86,23,44, 7},
 {35,13,82,46,48,27},}, 
{ {37,35,87,90,80},
 {53,98,90,19,63},
 {64, 2,73,58,83},
 { 2,85,80,12,68},
 {80,43,58,57,86},}, };
```

Copyright (c) 2025 Eric Gionet (<gionet.c.eric@gmail.com>)
