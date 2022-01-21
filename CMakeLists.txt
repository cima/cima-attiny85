cmake_minimum_required(VERSION 3.15)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# C++ stuff
# ---------
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Linking and packing
set(CMAKE_CXX_FLAGS "-mmcu=attiny85" ${CMAKE_CXX_FLAGS})
set(OBJCOPY  avr-objcopy)
set(OBJDUMP  avr-objdump)
set(AVRSTRIP avr-strip)

# Definition of target processor
add_compile_definitions(__AVR_ATtiny85__=1)
add_compile_definitions(F_CPU=16500000UL)
add_compile_definitions(__OPTIMIZE__=1)

#cmake_policy(SET CMP0074 NEW) # TODO co to je? Asi to je k boostu.

# Main code
# ---------

project(CIMA-ATTINY85
    VERSION 0.1
    DESCRIPTION "An example of arduinoless ATTINY85 programming"
    LANGUAGES CXX
)

add_subdirectory(src)