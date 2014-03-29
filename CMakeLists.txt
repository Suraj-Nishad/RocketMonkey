cmake_minimum_required (VERSION 2.6)

project (B2D)

set(SRC src)
set(BIN bin)

set(SDL2_CONFIG "sdl2-config" CACHE STRING "Path to sdl-config script")
EXEC_PROGRAM(${SDL2_CONFIG} ARGS "--libs" OUTPUT_VARIABLE SDL2_LIBS)
EXEC_PROGRAM(${SDL2_CONFIG} ARGS "--cflags" OUTPUT_VARIABLE SDL2_CFLAGS)

set(SDL2_LIBS "-lSDL2_image ${SDL2_LIBS}")

list(APPEND CMAKE_MODULE_PATH "cmake-modules/")
include(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC GIT_SHA1)

set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11 ${SDL2_CFLAGS}")

configure_file (
  "${SRC}/gitdefs.h.in"
  "${BIN}/gitdefs.h"
)

include_directories(
        "/usr/include/"
        "/opt/Box2d/include/"
        "${BIN}/"
)
link_directories(/opt/Box2d/lib)

add_executable(B2D ${SRC}/main.cpp 
                   ${SRC}/CEvent.cpp ${SRC}/CEvent.h
                   ${SRC}/CApp.cpp ${SRC}/CApp.h
                   ${SRC}/sprite.cpp ${SRC}/sprite.h
                   ${SRC}/spritefile.cpp ${SRC}/spritefile.h
                   ${SRC}/block.cpp ${SRC}/block.h
                   ${SRC}/wall.cpp ${SRC}/wall.h
                   ${SRC}/game_object.cpp ${SRC}/game_object.h
                   ${SRC}/player.cpp ${SRC}/player.h
                   ${SRC}/camera.cpp ${SRC}/camera.h
                   )

target_link_libraries(B2D Box2D ${SDL2_LIBS} jsoncpp)
