# CMakeList.txt : CMake project for OpenGLProj, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("OpenGLProj")

# Add source to this project's executable.
add_executable (OpenGLProj "src/main.cpp" "src/config.h" "src/glad.c" "src/shader.h" "src/camera.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OpenGLProj PROPERTY CXX_STANDARD 20)
endif()

target_include_directories (OpenGLProj PRIVATE include)
target_link_directories (OpenGLProj PRIVATE lib) 
target_link_libraries (OpenGLProj glfw3)

set_property(TARGET OpenGLProj PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/src")