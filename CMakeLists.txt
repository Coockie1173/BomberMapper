cmake_minimum_required(VERSION 3.16)
project(Bombermapper C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Enable FetchContent for dependencies
include(FetchContent)

# Make FetchContent verbose
set(FETCHCONTENT_QUIET OFF)

# Set static linking flags for MinGW cross-compilation
if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")
endif()

# Set high optimization flags
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_C_COMPILER_ID MATCHES "Clang")
    # For GCC/Clang
    set(CMAKE_C_FLAGS_RELEASE "-O3 -march=native -funroll-loops")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -funroll-loops")
elseif(MSVC)
    # For MSVC (Windows)
    set(CMAKE_C_FLAGS_RELEASE "/O2 /arch:AVX2")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2 /arch:AVX2")
endif()

# Fetch GLFW (force static build)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG latest
    GIT_PROGRESS TRUE
)
set(GLFW_BUILD_SHARED_LIBS OFF)  # Force static build
FetchContent_MakeAvailable(glfw)

# Fetch CGLM (header-only, no linking required)
FetchContent_Declare(
    cglm
    GIT_REPOSITORY https://github.com/recp/cglm.git
    GIT_TAG v0.9.2 # Use latest stable version
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(cglm)


# Add all source files from src directory
file(GLOB_RECURSE SRC_FILES src/*.c)

set(GLAD_SRC src/glad.c)

# Create executable
add_executable(${PROJECT_NAME} ${SRC_FILES} ${GLAD_SRC})

# Include dependencies
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${cglm_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include  # Include GLAD headers
)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Link dependencies statically
target_link_libraries(${PROJECT_NAME} 
    glfw
    OpenGL::GL
    OpenGL::GLU
)
