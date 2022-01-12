set(srcs
    "CimaAttiny85.cpp"
)

include_directories(${AVR_INCLUDE_DIRS})

enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

#component_compile_definitions(CORE_DEBUG_LEVEL=4) #copatotuje

# Boost
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()


# set(LINKER_SCRIPT "../AZ3166.ld") # TODO tohle bude potřeba
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${LINKER_SCRIPT}")

add_executable (CimaAttiny85 CimaAttiny85.cpp)

add_custom_target(strip ALL     ${AVRSTRIP} "CimaAttiny85" DEPENDS CimaAttiny85)
add_custom_target(hex   ALL     ${OBJCOPY} -R .eeprom -O ihex "CimaAttiny85" "CimaAttiny85.hex" DEPENDS strip)

# set_target_properties(CimaAttiny85 PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})
