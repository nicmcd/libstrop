cmake_minimum_required(VERSION 3.20)
project(libstrop)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FindPkgConfig)

# libprim
pkg_check_modules(libprim REQUIRED IMPORTED_TARGET libprim)
  get_target_property(
  LIBPRIM_INC
  PkgConfig::libprim
  INTERFACE_INCLUDE_DIRECTORIES
)

add_library(
  strop
  SHARED
  ${PROJECT_SOURCE_DIR}/src/strop/strop.cc
  ${PROJECT_SOURCE_DIR}/src/strop/strop.h
  ${PROJECT_SOURCE_DIR}/src/strop/strop.tcc
  )

set_target_properties(
  strop
  PROPERTIES
  LINKER_LANGUAGE
  CXX
  POSITION_INDEPENDENT_CODE
  ON
  )

target_include_directories(
  strop
  PUBLIC
  ${PROJECT_SOURCE_DIR}/src
  ${LIBPRIM_INC}
  )

target_link_libraries(
  strop
  PkgConfig::libprim
  )

include(GNUInstallDirs)

install(
  FILES
  ${PROJECT_SOURCE_DIR}/src/strop/strop.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/strop/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/src/strop/strop.tcc
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/strop/
  )

install(
  TARGETS
  strop
  )

configure_file(
  ${PROJECT_SOURCE_DIR}/libstrop.pc.in
  ${CMAKE_CURRENT_BINARY_DIR}/libstrop.pc
  @ONLY
  )
install(
  FILES
  ${CMAKE_CURRENT_BINARY_DIR}/libstrop.pc
  DESTINATION
  ${CMAKE_INSTALL_LIBDIR}/pkgconfig/
  )
