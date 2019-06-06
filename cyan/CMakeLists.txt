SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++17")
file(GLOB sources *.h *.c *.cxx *.cpp *.hxx)
add_executable(cyantest ${sources})
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")