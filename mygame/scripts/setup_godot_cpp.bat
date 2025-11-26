@echo off
REM ============================================================================
REM setup_godot_cpp.bat
REM 
REM Initializes the godot-cpp submodule for GDExtension development.
REM ============================================================================

setlocal

echo.
echo ============================================
echo Setting up godot-cpp for GDExtension
echo ============================================
echo.

cd /d "%~dp0\..\gdextension"

REM Check if already exists
if exist "godot-cpp\.git" (
    echo godot-cpp already exists. Updating...
    cd godot-cpp
    git pull
    git submodule update --init --recursive
) else (
    echo Cloning godot-cpp...
    git clone --recurse-submodules -b 4.3 https://github.com/godotengine/godot-cpp.git
)

if %ERRORLEVEL% neq 0 (
    echo.
    echo ERROR: Failed to setup godot-cpp!
    pause
    exit /b 1
)

echo.
echo ============================================
echo Building godot-cpp bindings...
echo ============================================
echo.

cd /d "%~dp0\..\gdextension\godot-cpp"
scons platform=windows target=template_debug -j%NUMBER_OF_PROCESSORS%

if %ERRORLEVEL% neq 0 (
    echo.
    echo ERROR: Failed to build godot-cpp!
    pause
    exit /b 1
)

echo.
echo ============================================
echo godot-cpp setup complete!
echo ============================================
echo.
echo You can now run build_extension.bat to build your game.
echo.

pause
