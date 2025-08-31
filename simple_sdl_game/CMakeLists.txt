cmake_minimum_required(VERSION 3.28)
project(simple C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(MAIN_SOURCES main.c)

if (EMSCRIPTEN)
  message("Using Emscripten for a web build")
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
  set(USE_SDL3_SUBMODULES ON)
else()
  set(USE_SDL3_SUBMODULES OFF)
endif()
message("USE_SDL3_SUBMODULES is set to ${USE_SDL3_SUBMODULES}")


if (USE_SDL3_SUBMODULES)
  add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

  set(SDLTTF_VENDORED ON)
  add_subdirectory(vendored/SDL_ttf EXCLUDE_FROM_ALL)

  add_subdirectory(vendored/SDL_image EXCLUDE_FROM_ALL)
else()
  find_package(SDL3_ttf REQUIRED)
  if(SDL3_ttf_FOUND)
    message(STATUS "SDL3_ttf found at: ${SDL3_ttf_DIR}")
  endif()
  find_package(SDL3_image REQUIRED)
  if (SDL3_image_FOUND)
    message(STATUS "SDL3_image found at: ${SDL3_image_DIR}")
  endif()
  find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
  if (SDL3_FOUND)
    message(STATUS "SDL3 found at: ${SDL3_DIR}")
  endif()
endif()

add_subdirectory(lib)
add_executable(simple ${MAIN_SOURCES})

target_link_libraries(simple PUBLIC lib m PRIVATE SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf SDL3::SDL3)

if (EMSCRIPTEN)
  set(CMAKE_EXE_LINKER_FLAGS "-sALLOW_MEMORY_GROWTH=1 -sMAXIMUM_MEMORY=4GB")
  add_link_options(${CMAKE_EXE_LINKER_FLAGS})
  target_link_libraries(simple PRIVATE
     "--preload-file \"${CMAKE_CURRENT_LIST_DIR}/images@/images/\""
     "--preload-file \"${CMAKE_CURRENT_LIST_DIR}/fonts@/fonts/\""
  )
else()
  add_custom_command(
      TARGET simple POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/images ${CMAKE_BINARY_DIR}/images
  )
  add_custom_command(
      TARGET simple POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/fonts ${CMAKE_BINARY_DIR}/fonts
  )
endif()
