#
# The MIT License (MIT)
#
# Copyright (c) 2025 Eric Gionet (gionet.c.eric@gmail.com)
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
#!/usr/bin/env python
from random import randrange
from sympy import Matrix, pprint, randMatrix, N, eye
from sympy.printing.str import StrPrinter
from sympy.abc import x 

filename = "../data/cla_matrix_qr_decomposition_data.h"

num_tests = 10
min_M_cols = 1
min_M_rows = 1
max_M_cols = 25
max_M_rows = 25
min_val = 0
max_val = 100

a_rows = ""
a_cols = ""
a_mats = ""

fs = open(filename, "w")

fs.write("/*                  MIT License (MIT)                       */")
fs.write("\n")
fs.write("/*           AUTO GENERATED CODE - DO NOT MODIFY            */")
fs.write("\n")
fs.write("/* Copyright (c) 2025 Eric Gionet (gionet.c.eric@gmail.com) */")
fs.write("\n")
fs.write("\n")
fs.write("#ifndef __CLA_MATRIX_QR_DECOMPOSITION_TEST_DATA_H__\n")
fs.write("#define __CLA_MATRIX_QR_DECOMPOSITION_TEST_DATA_H__\n")
fs.write("\n")
fs.write("#include <stdint.h>\n")
fs.write("\n")
fs.write("#ifdef __cplusplus\n")
fs.write('extern "C" {\n')
fs.write("#endif\n")
fs.write("\n")
fs.write("\nstatic const uint8_t cla_matrix_qr_decomposition_cases = {};\n".format(num_tests))
fs.write("\n")

for i in range(num_tests):
    print("Creating test case: ", i)
    t_case = i
    M_dim = randrange(min_M_cols, max_M_cols)
    M = randMatrix(M_dim, M_dim, min=min_val, max=max_val, percent=100)
    
    a_rows += " cla_matrix_qr_decomposition_a_{}_rows,".format(t_case)
    a_cols += " cla_matrix_qr_decomposition_a_{}_cols,".format(t_case)
    a_mats += " &cla_matrix_qr_decomposition_a_{}_matrix[0][0],".format(t_case)
    
    fs.write("\nstatic const uint16_t cla_matrix_qr_decomposition_a_{}_rows = {};\n".format(t_case, M_dim))
    fs.write("\nstatic const uint16_t cla_matrix_qr_decomposition_a_{}_cols = {};\n".format(t_case, M_dim))
    fs.write("\nstatic const double cla_matrix_qr_decomposition_a_{}_matrix[{}][{}] = ".format(t_case, M_dim, M_dim))
    fs.write("{\n")
    fs.write(M.table(StrPrinter(), rowstart="\t{", rowend="},", colsep=","))
    fs.write("};\n")

fs.write("\nstatic const uint16_t cla_matrix_qr_decomposition_a_rows[{}] = {{{}}};\n".format(num_tests, a_rows))
fs.write("\nstatic const uint16_t cla_matrix_qr_decomposition_a_cols[{}] = {{{}}};\n".format(num_tests, a_cols))
fs.write("\nstatic const double *cla_matrix_qr_decomposition_a_mats[{}]  = {{{}}};\n".format(num_tests, a_mats))


fs.write("\n")
fs.write("#ifdef __cplusplus\n")
fs.write("}\n")
fs.write("#endif\n")
fs.write("\n")
fs.write("#endif  // __CLA_MATRIX_QR_DECOMPOSITION_TEST_DATA_H__\n")
fs.close() 