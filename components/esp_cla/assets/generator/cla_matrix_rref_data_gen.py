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
from sympy.printing.str import StrPrinter

filename = "../data/cla_matrix_rref_data.h"

num_tests = 10
min_M_cols = 1
min_M_rows = 1
max_M_cols = 15
max_M_rows = 15
min_val = 0
max_val = 15
percent_min = 90
percent_max = 100

a_rows = ""
a_cols = ""
a_mats = ""

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
fs.write("#ifndef __CLA_MATRIX_RREF_TEST_DATA_H__\n")
fs.write("#define __CLA_MATRIX_RREF_TEST_DATA_H__\n")
fs.write("\n")
fs.write("#include <stdint.h>\n")
fs.write("\n")
fs.write("#ifdef __cplusplus\n")
fs.write('extern "C" {\n')
fs.write("#endif\n")
fs.write("\n")
fs.write("\nstatic const uint8_t cla_matrix_rref_cases = {};\n".format(num_tests))
fs.write("\n")

for i in range(num_tests):
    print("Creating test case: ", i + 1)
    M_rows = randrange(min_M_rows, max_M_rows)
    M_cols = randrange(min_M_cols, max_M_cols)
    M = randMatrix(M_rows, M_cols, min=0, max=10, percent=randrange(percent_min, percent_max))
    MRREF = M.rref()[0].applyfunc(N)
    
    a_rows += "{}, ".format(M_rows)
    a_cols += "{}, ".format(M_cols)
    a_mats += "\n{{{}}}, ".format(M.table(StrPrinter(), rowstart="\t{", rowend="},", colsep=","))
    
    x_rows += "{}, ".format(M_rows)
    x_cols += "{}, ".format(M_cols)
    x_mats += "\n{{{}}}, ".format(MRREF.table(StrPrinter(), rowstart="\t{", rowend="},", colsep=","))

fs.write("\nstatic const uint16_t cla_matrix_rref_a_rows[{}] = {{".format(num_tests))
fs.write("{}}};\n".format(a_rows))
fs.write("\nstatic const uint16_t cla_matrix_rref_a_cols[{}] = {{".format(num_tests))
fs.write("{}}};\n".format(a_cols))
fs.write("\nstatic const double cla_matrix_rref_a_mats[{}][{}][{}] = {{".format(num_tests, max_M_rows, max_M_cols))
fs.write("{}}};\n".format(a_mats))

fs.write("\n")

fs.write("\nstatic const uint16_t cla_matrix_rref_x_rows[{}] = {{".format(num_tests))
fs.write("{}}};\n".format(x_rows))
fs.write("\nstatic const uint16_t cla_matrix_rref_x_cols[{}] = {{".format(num_tests))
fs.write("{}}};\n".format(x_cols))
fs.write("\nstatic const double cla_matrix_rref_x_mats[{}][{}][{}] = {{".format(num_tests, max_M_rows, max_M_cols))
fs.write("{}}};\n".format(x_mats))

fs.write("\n")
fs.write("#ifdef __cplusplus\n")
fs.write("}\n")
fs.write("#endif\n")
fs.write("\n")
fs.write("#endif  // __CLA_MATRIX_RREF_TEST_DATA_H__\n")
fs.close() 