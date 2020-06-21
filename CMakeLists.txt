cmake_minimum_required(VERSION 2.8)
project(Dither)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(OpenCV REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories( 
	${OpenCV_INCLUDE_DIRS} 
	${SDL2_INCLUDE_DIRS} 
	${SDL2_IMAGE_INCLUDE_DIRS}
)

add_executable(Dither main.cpp dither.cpp)
target_link_libraries(Dither
       	${OpenCV_LIBS}
	${SDL2_LIBRARIES}
       	${SDL2_IMAGE_LIBRARIES}       
)
