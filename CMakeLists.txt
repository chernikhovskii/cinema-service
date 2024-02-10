cmake_minimum_required(VERSION 3.18)

set(PROJECT_VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(
  cinema_service
  LANGUAGES C CXX
  VERSION ${PROJECT_VERSION}
  DESCRIPTION "Implementation of a backend service in C++ which is used by some other services for booking online movie tickets. ")


add_executable(
  ${PROJECT_NAME}
  main.cc
  src/Cinema.cc
  src/Service.cc
  src/Movie.cc
  src/Client.cc
 )


# find_package(PkgConfig REQUIRED)

# pkg_check_modules(AVFORMAT libavformat)
# include_directories(${AVFORMAT_INCLUDE_DIRS})
# link_directories(${AVFORMAT_LIBRARY_DIRS})
# add_definitions(${AVFORMAT_CFLAGS})

target_link_libraries(
  ${PROJECT_NAME}
  -lpthread 
)

install(TARGETS ${PROJECT_NAME} DESTINATION sbin)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wunused -Wextra)
