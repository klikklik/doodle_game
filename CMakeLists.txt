cmake_minimum_required(VERSION 3.22)
project(sfmlgame)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(sfmlgame ${SRC_FILES})

if (WIN32)
    set(SFML_DIR "C:\\SFML\\lib\\cmake\\SFML")
    set(SFML_STATIC_LIBRARIES TRUE)
endif (WIN32)

find_package(SFML REQUIRED system window graphics)
target_link_libraries(sfmlgame sfml-system sfml-window sfml-graphics) #added

target_include_directories(sfmlgame PUBLIC ${PROJECT_SOURCE_DIR}/include)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

target_link_options(sfmlgame PRIVATE -mwindows)


