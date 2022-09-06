cmake_minimum_required(VERSION 3.1)
project(cerulean-player)

set(InstallPath "/usr/local/bin")
message(STATUS "Install path is set to ${InstallPath}")

file(GLOB_RECURSE SRC
    "src/*.cpp"
)

find_library(LIB_FMOD fmodL)
find_package(Boost 1.40 COMPONENTS filesystem REQUIRED)
find_package(PkgConfig)

pkg_search_module(TAGLIB REQUIRED taglib)

include_directories(src ${TAGLIB_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} ncurses ${LIB_FMOD} Boost::filesystem ${TAGLIB_LIBRARIES})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${PROJECT_NAME} DESTINATION ${InstallPath} CONFIGURATIONS ${CMAKE_CONFIGURATION_TYPES})