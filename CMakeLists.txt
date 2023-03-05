cmake_minimum_required(VERSION 3.25)
project(MemoryError C)

set(CMAKE_C_STANDARD 17)

# Include OpenGL headers
include_directories(${OPENGL_INCLUDE_DIR} )

# Add executable target
add_executable(MemoryError
        #        matrix.c
        #        hightestLoad.c
        #        CUDA.c
        #        Memory.c
        #        KillerWithThreads.c
        Application.c)