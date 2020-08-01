add_library(MAPKEP SHARED dllMain.cpp)

target_include_directories(MAPKEP PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_directories(MAPKEP PRIVATE ${CMAKE_SOURCE_DIR}/lib/Release)
target_link_libraries(MAPKEP dllInj.lib)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	target_compile_features(MAPKEP PUBLIC cxx_std_20)
endif()