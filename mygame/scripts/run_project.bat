@echo off
REM run_project.bat
REM Runs the Godot project with the GDExtension

setlocal

REM Check for custom Godot path first (built from source)
set GODOT_BUILT=D:\Source\godot\bin\godot.windows.editor.x86_64.exe

REM Common install locations for Godot 4
set GODOT_STEAM=C:\Program Files (x86)\Steam\steamapps\common\Godot Engine\godot.windows.editor.x86_64.exe
set GODOT_STANDARD=C:\Program Files\Godot\Godot_v4.3-stable_win64.exe
set GODOT_SCOOP=%USERPROFILE%\scoop\apps\godot\current\godot.exe

REM Project path
set PROJECT_PATH=%~dp0..\project

if exist "%GODOT_BUILT%" (
    echo Using Godot built from source...
    "%GODOT_BUILT%" --path "%PROJECT_PATH%"
    goto :end
)

if exist "%GODOT_STEAM%" (
    echo Using Godot from Steam...
    "%GODOT_STEAM%" --path "%PROJECT_PATH%"
    goto :end
)

if exist "%GODOT_STANDARD%" (
    echo Using standard Godot installation...
    "%GODOT_STANDARD%" --path "%PROJECT_PATH%"
    goto :end
)

if exist "%GODOT_SCOOP%" (
    echo Using Godot from Scoop...
    "%GODOT_SCOOP%" --path "%PROJECT_PATH%"
    goto :end
)

REM Try to find godot in PATH
where godot >nul 2>nul
if %ERRORLEVEL% EQU 0 (
    echo Using Godot from PATH...
    godot --path "%PROJECT_PATH%"
    goto :end
)

echo.
echo ERROR: Could not find Godot Editor!
echo.
echo Please either:
echo   1. Build Godot from source: cd D:\Source\godot ^&^& scons platform=windows target=editor
echo   2. Install Godot 4.x and add it to your PATH
echo   3. Edit this script to point to your Godot installation
echo.
pause

:end
endlocal
