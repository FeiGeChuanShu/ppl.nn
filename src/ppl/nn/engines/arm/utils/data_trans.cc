// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#include "ppl/nn/engines/arm/utils/data_trans.h"
#include <arm_neon.h>
#include <cstring>

void Fp32ToFp16(const float* src, int len, __fp16* dst) {
    const int simd_body = len / 8 * 8;
    if (simd_body > 0) {
        CvtFp32ToFp16(simd_body, src, dst);
    }
    for (int i = simd_body; i < len; ++i) {
        dst[i] = src[i];
    }
}

void Fp16ToFp32(const __fp16* src, int len, float* dst) {
    const int simd_body = len / 8 * 8;
    if (simd_body > 0) {
        CvtFp16ToFp32(simd_body, src, dst);
    }
    for (int i = simd_body; i < len; ++i) {
        dst[i] = src[i];
    }
}
