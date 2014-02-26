cmake_minimum_required (VERSION 2.6)

project (B2D)

set(SRC src)
set(BIN bin)

set(CMAKE_CURRENT_SOURCE_DIR .)

list(APPEND CMAKE_MODULE_PATH "cmake-modules/")
include(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC GIT_SHA1)

set(CMAKE_CXX_FLAGS "-g -Wall")

configure_file (
  "${SRC}/gitdefs.h.in"
  "${BIN}/gitdefs.h"
)


include_directories(
        "${BIN}/"
)
add_definitions("-DGIT_SHA1=${GIT_SHA1}")
add_executable(B2D ${SRC}/main.cpp)
target_link_libraries(B2D box2d SDL SDL_gfx SDL_ttf)
