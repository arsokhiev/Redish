# Redish
An analogue of Redis written using the Winsock API 
<br/>The application's task is to implement a simple key-value store, interacting via a tcp connection.

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

## Run it!
### Server
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
### Client
By going to the same client folder you will see RedishClient.
<br/>Run it by passing the port number
```
RedishClient 8080
```
Congratulations! Client connected to server

## Usage
Supported commands:<br/>
<br/>PUT <key> <value> - remembers the value for the key
<br/>GET <key> - gets the value for key
<br/>DEL <key> - deletes the value by key
<br/>COUNT - number of keys
##
Example script:
```
PUT name Vasya
OK
PUT name Masha
OK Vasya // returns the previous value
GET name
OK Masha // current Masha value
GET age
NE // no key
PUT age 20
OK
GET age
OK 20
COUNT
OK 2 // 2 keys
DEL age
OK 20
DEL name
OK Masha
COUNT
OK 0 // no keys
DEL name
NE // error, no key
```
