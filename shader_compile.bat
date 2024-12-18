@echo off
setlocal

set "SCRIPT_DIR=%~dp0"

for %%i in ("%SCRIPT_DIR%shaders\*.vert") do (
    glslc "%%i" -o "%%i.spv"
)

for %%i in ("%SCRIPT_DIR%shaders\*.frag") do (
    glslc "%%i" -o "%%i.spv"
)

echo Shader compilation complete.
pause
