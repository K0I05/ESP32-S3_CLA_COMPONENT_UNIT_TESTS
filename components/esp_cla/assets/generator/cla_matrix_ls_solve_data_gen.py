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
from sympy.matrices.dense import zeros
from sympy.printing.str import StrPrinter
from sympy.abc import x 

filename = "../data/cla_matrix_ls_solve_data.h"

num_tests = 10
min_M_cols = 1
min_M_rows = 1
max_M_cols = 15
max_M_rows = 15
min_val = 1
max_val = 100

a_rows = ""
a_cols = ""
a_mats = ""

b_rows = ""
b_cols = ""
b_mats = ""

x_rows = ""
x_cols = ""
x_mats = ""

fs = open(filename, "w")

fs.write("/*                  MIT License (MIT)                       */")
fs.write("\n")
fs.write("/*           AUTO GENERATED CODE - DO NOT MODIFY            */")
fs.write("\n")
fs.write("/* Copyright (c) 2025 Eric Gionet (gionet.c.eric@gmail.com) */")
fs.write("\n")
fs.write("\n")
fs.write("#ifndef __CLA_MATRIX_LS_SOLVE_TEST_DATA_H__\n")
fs.write("#define __CLA_MATRIX_LS_SOLVE_TEST_DATA_H__\n")
fs.write("\n")
fs.write("#include <stdint.h>\n")
fs.write("\n")
fs.write("#ifdef __cplusplus\n")
fs.write('extern "C" {\n')
fs.write("#endif\n")
fs.write("\n")
fs.write("\nstatic const uint8_t cla_matrix_ls_solve_cases = {};\n".format(num_tests))
fs.write("\n")
for i in range(num_tests):
    print("Creating test case: ", i)
    t_case = i
    M_dim = randrange(min_M_cols, max_M_cols)
    M = randMatrix(M_dim, M_dim, min=min_val, max=max_val, percent=100)            
    B = randMatrix(M_dim, 1, min=min_val, max=max_val, percent=100)            
    x = M.LUsolve(B).applyfunc(N)
    
    a_rows += " cla_matrix_ls_solve_a_{}_rows,".format(t_case)
    a_cols += " cla_matrix_ls_solve_a_{}_cols,".format(t_case)
    a_mats += " &cla_matrix_ls_solve_a_{}_matrix[0][0],".format(t_case)
    
    fs.write("\nstatic const uint16_t cla_matrix_ls_solve_a_{}_rows = {};\n".format(t_case, M_dim))
    fs.write("\nstatic const uint16_t cla_matrix_ls_solve_a_{}_cols = {};\n".format(t_case, M_dim))
    fs.write("\nstatic const double cla_matrix_ls_solve_a_{}_matrix[{}][{}] = ".format(t_case, M_dim, M_dim))
    fs.write("{\n")
    fs.write(M.table(StrPrinter(), rowstart="\t{", rowend="},", colsep=","))
    fs.write("};\n")
    
    b_rows += " cla_matrix_ls_solve_b_{}_rows,".format(t_case)
    b_cols += " cla_matrix_ls_solve_b_{}_cols,".format(t_case)
    b_mats += " &cla_matrix_ls_solve_b_{}_matrix[0][0],".format(t_case)
    
    fs.write("\nstatic const uint16_t cla_matrix_ls_solve_b_{}_rows = {};\n".format(t_case, M_dim))
    fs.write("\nstatic const uint16_t cla_matrix_ls_solve_b_{}_cols = {};\n".format(t_case, 1))
    fs.write("\nstatic const double cla_matrix_ls_solve_b_{}_matrix[{}][{}] = ".format(t_case, M_dim, 1))
    fs.write("{\n")
    fs.write(B.table(StrPrinter(), rowstart="\t{", rowend="},", colsep=","))           
    fs.write("};\n")
    
    x_rows += " cla_matrix_ls_solve_x_{}_rows,".format(t_case)
    x_cols += " cla_matrix_ls_solve_x_{}_cols,".format(t_case)
    x_mats += " &cla_matrix_ls_solve_x_{}_matrix[0][0],".format(t_case)
    
    fs.write("\nstatic const uint16_t cla_matrix_ls_solve_x_{}_rows = {};\n".format(t_case, M_dim))
    fs.write("\nstatic const uint16_t cla_matrix_ls_solve_x_{}_cols = {};\n".format(t_case, 1))
    fs.write("\nstatic const double cla_matrix_ls_solve_x_{}_matrix[{}][{}] = ".format(t_case, M_dim, 1))
    fs.write("{\n")
    fs.write(x.table(StrPrinter(), rowstart="\t{", rowend="},", colsep=","))
    fs.write("};\n")

fs.write("\nstatic const uint16_t cla_matrix_ls_solve_a_rows[{}] = {{{}}};\n".format(num_tests, a_rows))
fs.write("\nstatic const uint16_t cla_matrix_ls_solve_a_cols[{}] = {{{}}};\n".format(num_tests, a_cols))
fs.write("\nstatic const double *cla_matrix_ls_solve_a_mats[{}] = {{{}}};\n".format(num_tests, a_mats))

fs.write("\nstatic const uint16_t cla_matrix_ls_solve_b_rows[{}] = {{{}}};\n".format(num_tests, b_rows))
fs.write("\nstatic const uint16_t cla_matrix_ls_solve_b_cols[{}] = {{{}}};\n".format(num_tests, b_cols))
fs.write("\nstatic const double *cla_matrix_ls_solve_b_mats[{}] = {{{}}};\n".format(num_tests, b_mats))

fs.write("\nstatic const uint16_t cla_matrix_ls_solve_x_rows[{}] = {{{}}};\n".format(num_tests, x_rows))
fs.write("\nstatic const uint16_t cla_matrix_ls_solve_x_cols[{}] = {{{}}};\n".format(num_tests, x_cols))
fs.write("\nstatic const double *cla_matrix_ls_solve_x_mats[{}] = {{{}}};\n".format(num_tests, x_mats))

fs.write("\n")
fs.write("#ifdef __cplusplus\n")
fs.write("}\n")
fs.write("#endif\n")
fs.write("\n")
fs.write("#endif  // __CLA_MATRIX_LS_SOLVE_TEST_DATA_H__\n")
fs.close()