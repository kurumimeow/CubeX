cmake_minimum_required (VERSION 3.20.x)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("CubeX")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source to this project's executable.
add_library (${PROJECT_NAME} SHARED "main.cpp" "player.hpp" "inventory.hpp")

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)

# TODO: Add tests and install targets if needed.
# target_link_libraries(${PROJECT_NAME} PRIVATE imgui)
