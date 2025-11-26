@echo off
REM ============================================================================
REM build_godot_editor.bat
REM 
REM Builds a custom Godot editor with the game module integrated.
REM ============================================================================

setlocal

echo.
echo ============================================
echo Building Custom Godot Editor with MyGame
echo ============================================
echo.

set "GODOT_PATH=%~dp0..\.."
for %%i in ("%GODOT_PATH%") do set "GODOT_PATH=%%~fi"

REM Check if module is set up
if not exist "%GODOT_PATH%\modules\mygame" (
    echo Module not found. Running setup_module.bat first...
    call "%~dp0setup_module.bat"
)

cd /d "%GODOT_PATH%"

echo.
echo Building Godot editor...
echo.

scons platform=windows target=editor -j%NUMBER_OF_PROCESSORS%

if %ERRORLEVEL% neq 0 (
    echo.
    echo ERROR: Build failed!
    pause
    exit /b 1
)

echo.
echo ============================================
echo Build complete!
echo ============================================
echo.
echo The custom editor is at: %GODOT_PATH%\bin\godot.windows.editor.x86_64.exe
echo.

pause
