cmake_minimum_required(VERSION 3.25)

project(edgeDetector)

find_package(OpenCV REQUIRED)

file(GLOB SOURCE_FILES CONFIGURE_DEPENDS "src/*.cpp" "include/*.h" "include/*.hpp")

add_executable(edgeDetectorApp  ${SOURCE_FILES})

target_link_libraries(edgeDetectorApp ${OpenCV_LIBS})