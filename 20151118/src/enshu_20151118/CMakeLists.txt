cmake_minimum_required(VERSION 2.8.3)
project(enshu_20151118)

find_package(catkin REQUIRED COMPONENTS)
catkin_package()

add_custom_command(OUTPUT ${PROJECT_SOURCE_DIR}/echo-common.c ${PROJECT_SOURCE_DIR}/echo-skels.c ${PROJECT_SOURCE_DIR}/echo-skelimpl.c ${PROJECT_SOURCE_DIR}/echo-stubs.c 
  COMMAND orbit-idl-2 echo.idl --skeleton-impl
  DEPENDS echo.idl
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  )

include(FindPkgConfig)
pkg_check_modules(orbit REQUIRED ORBit-2.0)
pkg_check_modules(orbit_cosname REQUIRED ORBit-CosNaming-2.0)
include_directories(${orbit_INCLUDE_DIRS} ${orbit_cosname_INCLUDE_DIRS})
link_directories(${orbit_LIBRARY_DIRS} ${orbit_cosname_LIBRARY_DIRS})

add_executable(echo-server echo-server.c echo-common.c echo-skels.c examples-toolkit.c)
add_executable(echo-client echo-client.c echo-common.c echo-stubs.c examples-toolkit.c)

target_link_libraries(echo-server ${orbit_LIBRARIES} ${orbit_cosname_LIBRARIES})
target_link_libraries(echo-client ${orbit_LIBRARIES} ${orbit_cosname_LIBRARIES})





