## format handler CmakeLists.txt

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32 -std=c++11 -D__cdecl=\"\" -D__stdcall=\"\"")

include_directories($ENV{RIVER_SDK_DIR}/include
	)

include_directories("../include")
include_directories("../../river")

add_library(format.handler STATIC
    BinFormat.cpp
    TextFormat.cpp
    BinFormatConcolic.cpp
    )

install (TARGETS format.handler DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
