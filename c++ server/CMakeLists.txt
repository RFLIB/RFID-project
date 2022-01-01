cmake_minimum_required(VERSION 3.14)
project(RFIDProject)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

add_executable(RFIDProject main.cpp SerialPort.h SerialPort.cpp RFIDObject.h BooksDataBase.h Book.h sqlite3.h sqlite3ext.h sqlite3.c)