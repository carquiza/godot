@echo off
REM ============================================================================
REM setup_module.bat
REM 
REM Sets up the game as an engine module for deployment builds.
REM This creates a junction (symlink) in the Godot modules folder.
REM ============================================================================

setlocal

echo.
echo ============================================
echo Setting up MyGame as Engine Module
echo ============================================
echo.

set "GODOT_PATH=%~dp0..\.."
set "MODULE_SRC=%~dp0..\game_module"
set "MODULE_DST=%GODOT_PATH%\modules\mygame"

REM Resolve absolute paths
for %%i in ("%MODULE_SRC%") do set "MODULE_SRC=%%~fi"
for %%i in ("%MODULE_DST%") do set "MODULE_DST=%%~fi"
for %%i in ("%GODOT_PATH%") do set "GODOT_PATH=%%~fi"

echo Godot path: %GODOT_PATH%
echo Module source: %MODULE_SRC%
echo Module destination: %MODULE_DST%
echo.

REM Check if Godot modules folder exists
if not exist "%GODOT_PATH%\modules" (
    echo ERROR: Godot modules folder not found at %GODOT_PATH%\modules
    echo Make sure this template is placed inside the Godot source directory.
    pause
    exit /b 1
)

REM Remove existing link/folder if present
if exist "%MODULE_DST%" (
    echo Removing existing module link...
    rmdir "%MODULE_DST%" 2>nul
    if exist "%MODULE_DST%" (
        echo WARNING: Could not remove existing folder. It may not be a junction.
        echo Please manually remove: %MODULE_DST%
        pause
        exit /b 1
    )
)

REM We need to copy instead of junction because the module needs game_src inside it
REM Create the module directory
echo Creating module directory...
mkdir "%MODULE_DST%"

REM Copy module files
echo Copying module files...
copy /Y "%MODULE_SRC%\*.cpp" "%MODULE_DST%\"
copy /Y "%MODULE_SRC%\*.h" "%MODULE_DST%\"
copy /Y "%MODULE_SRC%\*.py" "%MODULE_DST%\"
copy /Y "%MODULE_SRC%\SCsub" "%MODULE_DST%\"

REM Copy game_src folder
echo Copying game source files...
xcopy /E /I /Y "%~dp0..\game_src" "%MODULE_DST%\game_src\"

REM Create doc_classes folder
if not exist "%MODULE_DST%\doc_classes" mkdir "%MODULE_DST%\doc_classes"

echo.
echo ============================================
echo Module setup complete!
echo ============================================
echo.
echo The module has been copied to: %MODULE_DST%
echo.
echo To build Godot with your game module:
echo   cd %GODOT_PATH%
echo   scons platform=windows target=editor
echo.
echo For export templates:
echo   scons platform=windows target=template_release
echo   scons platform=web target=template_release
echo.
echo NOTE: After modifying game_src, run this script again
echo       to update the module copy, or use sync_module.bat
echo.

pause
