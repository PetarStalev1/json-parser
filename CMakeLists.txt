# CMakeList.txt : CMake project for JSON Parser, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("JSON Parser")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options("/Zc:__cplusplus")
endif()

# --- Библиотеката (същинската логика на parser-а) ---
add_library(JsonParserLib
    src/JsonValue.cpp
    src/Parser.cpp
 "include/json/Parser.h")

target_include_directories(JsonParserLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET JsonParserLib PROPERTY CXX_STANDARD 20)
endif()

# --- Demo/example изпълним файл ---
add_executable(JsonParserApp
    examples/main.cpp
 "include/json/Parser.h")

target_link_libraries(JsonParserApp PRIVATE JsonParserLib)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET JsonParserApp PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.