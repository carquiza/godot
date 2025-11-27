@echo off
REM ============================================================================
REM sync_module.bat
REM 
REM Syncs the game source files to the engine module after changes.
REM Run this after modifying files in game_src.
REM ============================================================================

setlocal

echo.
echo ============================================
echo Syncing game source to engine module
echo ============================================
echo.

set "GODOT_PATH=%~dp0..\.."
set "MODULE_DST=%GODOT_PATH%\modules\mygame"

for %%i in ("%MODULE_DST%") do set "MODULE_DST=%%~fi"

if not exist "%MODULE_DST%" (
    echo ERROR: Module not found at %MODULE_DST%
    echo Please run setup_module.bat first.
    pause
    exit /b 1
)

echo Syncing game_src...
xcopy /E /Y "%~dp0..\game_src\*" "%MODULE_DST%\game_src\"

echo Syncing module files...
copy /Y "%~dp0..\game_module\*.cpp" "%MODULE_DST%\"
copy /Y "%~dp0..\game_module\*.h" "%MODULE_DST%\"

echo.
echo ============================================
echo Sync complete!
echo ============================================
echo.
echo Remember to rebuild Godot after syncing:
echo   scons platform=windows target=editor
echo.

pause
