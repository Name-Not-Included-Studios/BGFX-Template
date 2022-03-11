.\shaderc.exe -f .\src\vs_cubes.sc -o .\out\vs_cubes.gl --type v --platform windows -p 440 --varyingdef .\src\varying.def.sc
.\shaderc.exe -f .\src\fs_cubes.sc -o .\out\fs_cubes.gl --type f --platform windows -p 440 --varyingdef .\src\varying.def.sc

pause
cls

.\shaderc.exe -f .\src\vs_cubes.sc -o .\out\vs_cubes.gl.h --type v --platform windows -p 440 --varyingdef .\src\varying.def.sc --bin2c
.\shaderc.exe -f .\src\fs_cubes.sc -o .\out\fs_cubes.gl.h --type f --platform windows -p 440 --varyingdef .\src\varying.def.sc --bin2c

pause
cls

.\shaderc.exe -f .\src\vs_cubes.sc -o .\out\vs_cubes.spv --type v --platform windows -p spirv --varyingdef .\src\varying.def.sc
.\shaderc.exe -f .\src\fs_cubes.sc -o .\out\fs_cubes.spv --type f --platform windows -p spirv --varyingdef .\src\varying.def.sc

pause
cls

.\shaderc.exe -f .\src\vs_cubes.sc -o .\out\vs_cubes.dx --type v --platform windows -p s_3_0 --varyingdef .\src\varying.def.sc
.\shaderc.exe -f .\src\fs_cubes.sc -o .\out\fs_cubes.dx --type f --platform windows -p s_3_0 --varyingdef .\src\varying.def.sc

pause