cd Server
mkdir build
cd build
cmake -G "Visual Studio 17 2022" ..
cmake --build . --config Release

cd ../../Client
mkdir build
cd build
cmake -G "Visual Studio 17 2022" ..
cmake --build . --config Release