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

#include "FFXRHIBackendModule.h"
#include "FFXRHIBackend.h"
#include "Interfaces/IPluginManager.h"

IMPLEMENT_MODULE(FFXRHIBackendModule, FFXRHIBackend)

#define LOCTEXT_NAMESPACE "FFXRHIBackend"

static FFXRHIBackend sRHIBackennd;

void FFXRHIBackendModule::StartupModule()
{
	FString PluginFSR3ShaderDir = FPaths::Combine(IPluginManager::Get().FindPlugin(TEXT("FSR3"))->GetBaseDir(), TEXT("Source/fidelityfx-hlsl"));
	AddShaderSourceDirectoryMapping(TEXT("/ThirdParty/FFX"), PluginFSR3ShaderDir);
	FString PluginShaderDir = FPaths::Combine(IPluginManager::Get().FindPlugin(TEXT("FSR3"))->GetBaseDir(), TEXT("Shaders"));
	AddShaderSourceDirectoryMapping(TEXT("/Plugin/FFX"), PluginShaderDir);
}

void FFXRHIBackendModule::ShutdownModule()
{
}

IFFXSharedBackend* FFXRHIBackendModule::GetBackend()
{
	return &sRHIBackennd;
}

#undef LOCTEXT_NAMESPACE