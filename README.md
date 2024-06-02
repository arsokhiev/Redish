# Redish
An analogue of Redis written using the Winsock API

![alt text](https://github.com/arsokhiev/Redish/blob/master/Redish.jpg)

## Installation
### Clone repository
```
git clone --recursive https://github.com/arsokhiev/Redish.git
cd Redish
```
### CMake
Go to the Server folder
```
cd Server
```
Create build folder and open it
```
mkdir build
cd build
```
Build in command line with cmake
```
cmake -G "Visual Studio 17 2022" ..
cmake --build . --config Release
```
Repeat the same in the Client directory
```
cd ../../Client
mkdir build
cd build
cmake -G "Visual Studio 17 2022" ..
cmake --build . --config Release
```
Or use the batch file "compile_win" :-)

## Usage
Again we need to change the directory, but this time to the executable file
```
cd../../Server/build/Release
```
To start the server, run the program passing 2 arguments (ip address is default - 127.0.0.1)
1. Port number
2. Maximum number of connected clients
```
RedishServer 8080 5
```
Congratulations! Server is running
##
By going to the same client folder you will see RedishClient.
Run it by passing the port number
```
RedishClient 8080
```
