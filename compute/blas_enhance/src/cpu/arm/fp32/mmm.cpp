// Copyright (C) 2019. Huawei Technologies Co., Ltd. All rights reserved.

// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "cpu/arm/fp32/blas_fp32.h"
#include "blas_enhance.h"

void matrix_matrix_multiply_tmp_bytes_fp32(
    U32 matrixC_N, U32 matrixC_M, U32 matrixA_K, DataFormat bdf, U32 *bytes)
{
    matrix_matrix_multiply_transform_rhs_bytes_fp32(matrixC_N, matrixA_K, bdf, bytes, nullptr);

    *bytes += matrixC_M * matrixA_K * bytesOf(DT_F32);
    *bytes += 32;
}

void matrix_matrix_multiply_transform_rhs_bytes_fp32(
    U32 matrixC_N, U32 matrixA_K, DataFormat bdf, U32 *bytes, U32 *rhsBytes)
{
    U32 matrix = 0;
    U32 pad = 0;
    if (matrix_matrix_multiply_rhs_format(DT_F32) != bdf) {
        matrix = matrixC_N * matrixA_K * bytesOf(DT_F32);
        pad = matrix + 32;
    }
    if (rhsBytes != nullptr) {
        *rhsBytes = matrix;
    }
    if (bytes != nullptr) {
        *bytes = pad;
    }
}
