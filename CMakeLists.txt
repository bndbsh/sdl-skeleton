project(sdl_skeleton)

find_package(OpenGL REQUIRED)

if (UNIX)
	add_definitions(-DUNIX)
endif (UNIX)

include_directories(. ${silver_SOURCE_DIR}/build ${silver_SOURCE_DIR}/src ${silver_SOURCE_DIR}/build/src ${SDL_INCLUDE_DIR})

cmake_policy(SET CMP0003 NEW)

set (SOURCES gfx/sdlwidget skeleton.cc locations.cc)

set (LIBRARIES  ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} SDL2 SDL2_image)

if (UNIX)
	set_source_files_properties(${SOURCES} PROPERTIES COMPILE_FLAGS "-std=c++0x")
endif(UNIX)

add_executable(sdl-skeleton ${SOURCES} gfx/glew.c)
target_link_libraries(sdl-skeleton ${LIBRARIES})
