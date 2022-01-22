SET TOOLCHAIN_DIR=e:\SW\TINY85
SET PATH=%TOOLCHAIN_DIR%\avr-gcc-11.1.0-x64-windows\bin;^
%TOOLCHAIN_DIR%\avr-gcc-11.1.0-x64-windows\avr\bin;^
%TOOLCHAIN_DIR%\micronucleus-cli-master-882e7b4a;^
e:\SW\cmake-3.15.6-win64-x64\bin;^
e:\SW\ninja-win;%PATH%

SET CXX=avr-g++

SET AVR_INCLUDE_DIRS=e:\SW\TINY85\avr-gcc-11.1.0-x64-windows\avr\include 

code .