// This file is part of the FidelityFX Super Resolution 3.0 Unreal Engine Plugin.
// 
// Copyright (c) 2023 Advanced Micro Devices, Inc. All rights reserved.
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.


#ifndef FFX_FRAMEINTERPOLATION_RECONSTRUCT_PREVIOUS_DEPTH_H
#define FFX_FRAMEINTERPOLATION_RECONSTRUCT_PREVIOUS_DEPTH_H

void ReconstructPrevDepth(FfxInt32x2 iPxPos, FfxUInt32 depthTarget, FfxFloat32 fDepth, FfxFloat32x2 fMotionVector, FfxInt32x2 iPxDepthSize)
{
    const FfxFloat32x2 fUv = (iPxPos + FfxFloat32(0.5)) / iPxDepthSize;

    // Project current depth into previous frame locations.
    // Push to all pixels having some contribution if reprojection is using bilinear logic.
    BilinearSamplingData bilinearInfo = GetBilinearSamplingData(fUv + fMotionVector, RenderSize());
    for (FfxInt32 iSampleIndex = 0; iSampleIndex < 4; iSampleIndex++)
    {
        const FfxInt32x2 iOffset = bilinearInfo.iOffsets[iSampleIndex];
        const FfxInt32x2 iSamplePos = bilinearInfo.iBasePos + iOffset;
        const FfxFloat32 fSampleWeight = bilinearInfo.fWeights[iSampleIndex];

        if (fSampleWeight > fReconstructedDepthBilinearWeightThreshold)
        {
            if (IsOnScreen(iSamplePos, RenderSize()))
            {
                if (depthTarget != 0) {
                    UpdateReconstructedDepthInterpolatedFrame(iSamplePos, fDepth);
                }
            }
        }
    }
}

void reconstructPreviousDepth(FfxInt32x2 iPxPos)
{
    FfxFloat32x2 fMotionVector = LoadDilatedMotionVector(iPxPos);
    FfxFloat32   fDilatedDepth = LoadDilatedDepth(iPxPos);

    ReconstructPrevDepth(iPxPos, 1, fDilatedDepth, fMotionVector * 0.5f, RenderSize());
}

#endif // FFX_FRAMEINTERPOLATION_RECONSTRUCT_PREVIOUS_DEPTH_H
