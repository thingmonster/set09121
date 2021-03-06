cmake_minimum_required(VERSION  3.9)

# Require  modern C++
set(CMAKE_CXX_STANDARD  14)
set(CMAKE_CXX_STANDARD_REQUIRED  ON)

project(Games_Engineering)

####  Setup  Directories  ####

#Main  output  directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")

# Ouput  all  DLLs  from  all  libs  into  main  build  folder
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Add  External  Dependencies  ####
add_subdirectory("lib/sfml")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

####  Practical 1 ####
file(GLOB_RECURSE SOURCES practical_1/*.cpp  practical_1/*.h)
add_executable(PRACTICAL_1 ${SOURCES})
target_include_directories(PRACTICAL_1 PRIVATE ${SFML_INCS})
target_link_libraries(PRACTICAL_1 sfml-graphics)

####  Practical 2 ####
file(GLOB_RECURSE SOURCES practical_2/*.cpp  practical_2/*.h)
add_executable(PRACTICAL_2 ${SOURCES})
target_include_directories(PRACTICAL_2 SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(PRACTICAL_2 sfml-graphics)
set_target_properties(PRACTICAL_2 PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY 
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)

add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND}
	-E copy_directory
	"${PROJECT_SOURCE_DIR}/res"
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res
)
add_dependencies(PRACTICAL_2 copy_resources)


####  Practical 3 ####
file(GLOB_RECURSE SOURCES practical_3/*.cpp  practical_3/*.h)
add_executable(PRACTICAL_3 ${SOURCES})
target_include_directories(PRACTICAL_3 PRIVATE ${SFML_INCS})

target_link_libraries(PRACTICAL_3 lib_tile_level_loader sfml-graphics)

set_target_properties(PRACTICAL_3 PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY 
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)
add_dependencies(PRACTICAL_3 copy_resources)


####  Practical 4 ####
file(GLOB_RECURSE SOURCES practical_4/*.cpp  practical_4/*.h)
add_executable(PRACTICAL_4 ${SOURCES})
target_include_directories(PRACTICAL_4 PRIVATE ${SFML_INCS})

target_link_libraries(PRACTICAL_4 sfml-graphics lib_ecm lib_maths lib_tile_level_loader)

set_target_properties(PRACTICAL_4 PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY 
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)
add_dependencies(PRACTICAL_4 copy_resources)

# Tile Loader Lib
file(GLOB_RECURSE LOAD_TILES lib_tile_level_loader/*.cpp lib_tile_level_loader/*.h)
add_library(lib_tile_level_loader STATIC ${LOAD_TILES})
target_include_directories(lib_tile_level_loader 
	INTERFACE "${CMAKE_SOURCE_DIR}/lib_tile_level_loader/" 
	PRIVATE ${SFML_INCS}
)

target_link_libraries(lib_tile_level_loader lib_maths sfml-graphics)

# math lib
add_library(lib_maths INTERFACE)
target_sources(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths/maths.h")
target_include_directories(lib_maths 
	INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths/" 
	SYSTEM INTERFACE ${SFML_INCS}
)

# ecm lib
file(GLOB_RECURSE SOURCE_FILES lib_ecm/*.cpp lib_ecm/*.h)
add_library(lib_ecm STATIC ${SOURCE_FILES})
target_include_directories(lib_ecm 	INTERFACE "${CMAKE_SOURCE_DIR}/lib_ecm/")

target_link_libraries(lib_ecm PRIVATE lib_maths lib_tile_level_loader)




