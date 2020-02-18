cmake_minimum_required(VERSION 3.1)
project(cerulean-player)

file(GLOB SRC
    "src/*.cpp"
)

find_library(LIB_FMOD fmodL)
find_package(Boost 1.40 COMPONENTS filesystem REQUIRED)

include_directories(src)
add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} ncurses ${LIB_FMOD} Boost::filesystem)