@echo off
set /p id="Enter program ID: "

mkdir .\out\%id%\

.\shaderc.exe -f .\src\vs_%id%.sc -o .\out\%id%\vs_%id%.gl --type v --platform windows -p 440 --varyingdef .\src\varying_%id%.def.sc
.\shaderc.exe -f .\src\fs_%id%.sc -o .\out\%id%\fs_%id%.gl --type f --platform windows -p 440 --varyingdef .\src\varying_%id%.def.sc

echo "Compiled GL shaders for %id%."
pause
cls

.\shaderc.exe -f .\src\vs_%id%.sc -o .\out\%id%\vs_%id%.gl.h --type v --platform windows -p 440 --varyingdef .\src\varying_%id%.def.sc --bin2c
.\shaderc.exe -f .\src\fs_%id%.sc -o .\out\%id%\fs_%id%.gl.h --type f --platform windows -p 440 --varyingdef .\src\varying_%id%.def.sc --bin2c

echo "Compiled GL.h shaders for %id%."
pause
cls

.\shaderc.exe -f .\src\vs_%id%.sc -o .\out\%id%\vs_%id%.spv --type v --platform windows -p spirv --varyingdef .\src\varying_%id%.def.sc
.\shaderc.exe -f .\src\fs_%id%.sc -o .\out\%id%\fs_%id%.spv --type f --platform windows -p spirv --varyingdef .\src\varying_%id%.def.sc

echo "Compiled SPIRV shaders for %id%."
pause
cls

.\shaderc.exe -f .\src\vs_%id%.sc -o .\out\%id%\vs_%id%.dx --type v --platform windows -p s_5_0 --varyingdef .\src\varying_%id%.def.sc
.\shaderc.exe -f .\src\fs_%id%.sc -o .\out\%id%\fs_%id%.dx --type f --platform windows -p s_5_0 --varyingdef .\src\varying_%id%.def.sc

echo "Compiled DX shaders for %id%."
pause

:exit