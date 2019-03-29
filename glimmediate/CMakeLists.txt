cmake_minimum_required(VERSION 3.1)

project(GLImmediate)

if(NOT EMSCRIPTEN)
  find_package(OpenGL REQUIRED)
  find_package(glfw3 REQUIRED)
endif()

foreach(_tst tst1)
  add_executable(${_tst} ${_tst}.cpp)
    set_target_properties(${_tst} PROPERTIES
      CXX_STANDARD 11
      CXX_STANDARD_REQUIRED TRUE)
  if(EMSCRIPTEN)
    set_target_properties(${_tst} PROPERTIES
      SUFFIX .html)
    set(_emflags "-s LEGACY_GL_EMULATION=1")
    string(APPEND _emflags " -s USE_GLFW=3")
    set_property(TARGET ${_tst} APPEND PROPERTY 
      COMPILE_FLAGS ${_emflags})
    set_property(TARGET ${_tst} APPEND PROPERTY 
      LINK_FLAGS ${_emflags})
  else()
    target_link_libraries(${_tst} PRIVATE
      OpenGL::GL glfw)
  endif()
endforeach()

# vim: sw=2 ts=2 et:
