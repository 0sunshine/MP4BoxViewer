1. windwos:
	D:\vs2022\VC\Auxiliary\Build\vcvars64.bat
	cmake -G "NMake Makefiles" -B build -S .
	cmake --build build -j
	.\build\MP4BoxViewer.exe

2. windwos vs:
	cmake -G "Visual Studio 17 2022" -B vsbuild -S .