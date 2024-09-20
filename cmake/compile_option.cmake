

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_compile_definitions(_GLIBCXX_DEBUG)
endif ()
# Add strict compiler flags
add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Werror
        -Wstrict-aliasing
        -Wformat=2
        -Wshadow
        -Wconversion
        #-Wsign-conversion
        -Wstrict-overflow=5
        -Wundef
        #-Wno-unused
        -Wno-sign-compare
        -Wno-sign-conversion

)