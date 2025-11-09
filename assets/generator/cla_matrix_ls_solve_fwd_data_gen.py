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
from sympy import randMatrix, N
from sympy.matrices.dense import zeros
from sympy.printing.str import StrPrinter
from sympy.abc import x 

filename = "../data/cla_matrix_ls_solve_fwd_data.h"

num_tests = 5
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

fs = open(filename, "w", encoding="utf-8")

fs.write("/*                  MIT License (MIT)                       */")
fs.write("\n")
fs.write("/*           AUTO GENERATED CODE - DO NOT MODIFY            */")
fs.write("\n")
fs.write("/* Copyright (c) 2025 Eric Gionet (gionet.c.eric@gmail.com) */")
fs.write("\n")
fs.write("\n")
fs.write("#ifndef __CLA_MATRIX_LS_SOLVE_FWD_TEST_DATA_H__\n")
fs.write("#define __CLA_MATRIX_LS_SOLVE_FWD_TEST_DATA_H__\n")
fs.write("\n")
fs.write("#include <stdint.h>\n")
fs.write("\n")
fs.write("#ifdef __cplusplus\n")
fs.write('extern "C" {\n')
fs.write("#endif\n")
fs.write("\n")
fs.write("\nstatic const uint8_t cla_matrix_ls_solve_fwd_cases = {};\n".format(num_tests))
fs.write("\n")

for i in range(num_tests):
    print("Creating test case: ", i + 1)
    M_dim = randrange(min_M_cols, max_M_cols)
    M = zeros(M_dim)
    for i in range(M_dim):
        for j in range(i+1):
            M[i, j] = randrange(min_val, max_val)
    B = randMatrix(M_dim, 1, min=min_val, max=max_val, percent=100)            
    x = M.lower_triangular_solve(B).applyfunc(N)
    
    a_rows += "{}, ".format(M_dim)
    a_cols += "{}, ".format(M_dim)
    a_mats += "\n{{{}}}, ".format(M.table(StrPrinter(), rowstart="\t{", rowend="},", colsep=","))
    
    b_rows += "{}, ".format(M_dim)
    b_cols += "{}, ".format(1)
    b_mats += "\n{{{}}}, ".format(B.table(StrPrinter(), rowstart="\t{", rowend="},", colsep=","))
    
    x_rows += "{}, ".format(M_dim)
    x_cols += "{}, ".format(1)
    x_mats += "\n{{{}}}, ".format(x.table(StrPrinter(), rowstart="\t{", rowend="},", colsep=","))
    
fs.write("\nstatic const uint16_t cla_matrix_ls_solve_fwd_a_rows[{}] = {{".format(num_tests))
fs.write("{}}};\n".format(a_rows))
fs.write("\nstatic const uint16_t cla_matrix_ls_solve_fwd_a_cols[{}] = {{".format(num_tests))
fs.write("{}}};\n".format(a_cols))
fs.write("\nstatic const double cla_matrix_ls_solve_fwd_a_mats[{}][{}][{}] = {{".format(num_tests, max_M_rows, max_M_cols))
fs.write("{}}};\n".format(a_mats))

fs.write("\n")

fs.write("\nstatic const uint16_t cla_matrix_ls_solve_fwd_b_rows[{}] = {{".format(num_tests))
fs.write("{}}};\n".format(b_rows))
fs.write("\nstatic const uint16_t cla_matrix_ls_solve_fwd_b_cols[{}] = {{".format(num_tests))
fs.write("{}}};\n".format(b_cols))
fs.write("\nstatic const double cla_matrix_ls_solve_fwd_b_mats[{}][{}][{}] = {{".format(num_tests, max_M_rows, max_M_cols))
fs.write("{}}};\n".format(b_mats))

fs.write("\n")

fs.write("\nstatic const uint16_t cla_matrix_ls_solve_fwd_x_rows[{}] = {{".format(num_tests))
fs.write("{}}};\n".format(x_rows))
fs.write("\nstatic const uint16_t cla_matrix_ls_solve_fwd_x_cols[{}] = {{".format(num_tests))
fs.write("{}}};\n".format(x_cols))
fs.write("\nstatic const double cla_matrix_ls_solve_fwd_x_mats[{}][{}][{}] = {{".format(num_tests, max_M_rows, max_M_cols))
fs.write("{}}};\n".format(x_mats))

fs.write("\n")
fs.write("#ifdef __cplusplus\n")
fs.write("}\n")
fs.write("#endif\n")
fs.write("\n")
fs.write("#endif  // __CLA_MATRIX_LS_SOLVE_FWD_TEST_DATA_H__\n")
fs.close()  
