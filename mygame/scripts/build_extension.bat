@echo off
REM ============================================================================
REM build_extension.bat
REM 
REM Builds the game as a GDExtension for fast development iteration.
REM ============================================================================

setlocal

echo.
echo ============================================
echo Building MyGame GDExtension (Development)
echo ============================================
echo.

REM Navigate to gdextension directory
cd /d "%~dp0\..\gdextension"

REM Check if godot-cpp exists
if not exist "godot-cpp" (
    echo ERROR: godot-cpp not found!
    echo.
    echo Please run setup_godot_cpp.bat first to initialize the submodule.
    echo.
    pause
    exit /b 1
)

REM Build for Windows debug by default
echo Building for Windows (debug)...
scons platform=windows target=template_debug -j%NUMBER_OF_PROCESSORS%

if %ERRORLEVEL% neq 0 (
    echo.
    echo ERROR: Build failed!
    pause
    exit /b 1
)

REM Copy to project bin directory
echo.
echo Copying binaries to project...

if not exist "..\project\bin\windows" mkdir "..\project\bin\windows"
copy /Y "bin\windows\*.*" "..\project\bin\windows\"

echo.
echo ============================================
echo Build complete!
echo ============================================
echo.
echo You can now run the project in Godot.
echo.

pause
