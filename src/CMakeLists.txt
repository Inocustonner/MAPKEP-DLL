add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_library(MAPKEP SHARED dllMain.cpp)

target_include_directories(MAPKEP PRIVATE ${CMAKE_SOURCE_DIR}/include)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	target_compile_features(MAPKEP PUBLIC cxx_std_20)
endif()