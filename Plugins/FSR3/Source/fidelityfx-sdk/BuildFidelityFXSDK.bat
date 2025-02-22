@echo off
setlocal enabledelayedexpansion

echo ===============================================================
echo.
echo  FidelityFX Build System
echo.
echo ===============================================================

echo Checking pre-requisites... 

:: Check if cmake is installed
cmake --version > nul 2>&1
if %errorlevel% NEQ 0 (
    echo Cannot find path to CMake. Is CMake installed? Exiting...
    exit /b -1
) else (
    echo CMake Ready.
)

:: Check if VULKAN_SDK is installed but don't bail out
if "%VULKAN_SDK%"=="" (
    echo Vulkan SDK is not installed -Environment variable VULKAN_SDK is not defined- : Please install the latest Vulkan SDK from LunarG.
) else (
    echo    Vulkan SDK - Ready : %VULKAN_SDK%
)

echo.
echo Building FidelityFX SDK (Standalone)
echo.

:: Check directories exist and create if not
if not exist build\ (
	mkdir build 
)
cd build
cmake -A x64 .. -DFFX_API_CUSTOM=OFF -DFFX_FSR=ON -DFFX_FSR3=ON -DFFX_AUTO_COMPILE_SHADERS=1 %*
cmake --build ./ --config Debug --parallel 4 -- /p:CL_MPcount=16
cmake --build ./ --config Release --parallel 4 -- /p:CL_MPcount=16
cmake --build ./ --config RelWithDebInfo --parallel 4 -- /p:CL_MPcount=16

cd..
