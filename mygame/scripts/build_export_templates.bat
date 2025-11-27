@echo off
REM ============================================================================
REM build_export_templates.bat
REM 
REM Builds export templates with the game module for deployment.
REM ============================================================================

setlocal

echo.
echo ============================================
echo Building Export Templates with MyGame
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

:menu
echo.
echo Select platform to build:
echo   1. Windows (release)
echo   2. Windows (debug)
echo   3. Web/HTML5 (release)
echo   4. Web/HTML5 (debug)
echo   5. Linux (release)
echo   6. All desktop platforms (release)
echo   7. Exit
echo.

set /p choice="Enter choice (1-7): "

if "%choice%"=="1" goto windows_release
if "%choice%"=="2" goto windows_debug
if "%choice%"=="3" goto web_release
if "%choice%"=="4" goto web_debug
if "%choice%"=="5" goto linux_release
if "%choice%"=="6" goto all_desktop
if "%choice%"=="7" goto end

echo Invalid choice!
goto menu

:windows_release
echo Building Windows release template...
scons platform=windows target=template_release -j%NUMBER_OF_PROCESSORS%
goto done

:windows_debug
echo Building Windows debug template...
scons platform=windows target=template_debug -j%NUMBER_OF_PROCESSORS%
goto done

:web_release
echo Building Web release template...
echo NOTE: This requires Emscripten to be installed and configured.
scons platform=web target=template_release -j%NUMBER_OF_PROCESSORS%
goto done

:web_debug
echo Building Web debug template...
echo NOTE: This requires Emscripten to be installed and configured.
scons platform=web target=template_debug -j%NUMBER_OF_PROCESSORS%
goto done

:linux_release
echo Building Linux release template...
echo NOTE: Cross-compilation from Windows requires additional setup.
scons platform=linux target=template_release -j%NUMBER_OF_PROCESSORS%
goto done

:all_desktop
echo Building all desktop release templates...
echo.
echo Windows...
scons platform=windows target=template_release -j%NUMBER_OF_PROCESSORS%
echo.
echo Linux...
scons platform=linux target=template_release -j%NUMBER_OF_PROCESSORS%
goto done

:done
if %ERRORLEVEL% neq 0 (
    echo.
    echo ERROR: Build failed!
) else (
    echo.
    echo ============================================
    echo Build complete!
    echo ============================================
    echo.
    echo Templates are in: %GODOT_PATH%\bin\
    echo.
    echo To use these templates:
    echo 1. Open Godot Editor
    echo 2. Go to Editor -^> Manage Export Templates
    echo 3. Point to the custom templates in the bin folder
)

pause
goto menu

:end
echo Goodbye!
