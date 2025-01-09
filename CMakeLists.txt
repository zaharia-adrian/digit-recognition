# CMakeList.txt : CMake project for digit-recognition, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("digit-recognition")

# Add source to this project's executable.
add_executable (digit-recognition "src/digit-recognition.cpp" "src/digit-recognition.h" "src/grid/Grid.cpp" "src/ui/Button.cpp" "src/managers/FileManager.cpp" "src/nn/NN.cpp")


if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_link_libraries(digit-recognition 
		${CMAKE_SOURCE_DIR}/lib/sfml-graphics-d.lib
		${CMAKE_SOURCE_DIR}/lib/sfml-audio-d.lib
		${CMAKE_SOURCE_DIR}/lib/sfml-network-d.lib
		${CMAKE_SOURCE_DIR}/lib/sfml-system-d.lib
		${CMAKE_SOURCE_DIR}/lib/sfml-window-d.lib)
else()
	target_link_libraries(digit-recognition
		${CMAKE_SOURCE_DIR}/lib/sfml-graphics.lib
		${CMAKE_SOURCE_DIR}/lib/sfml-audio.lib
		${CMAKE_SOURCE_DIR}/lib/sfml-network.lib
		${CMAKE_SOURCE_DIR}/lib/sfml-system.lib
		${CMAKE_SOURCE_DIR}/lib/sfml-window.lib)
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET digit-recognition PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
