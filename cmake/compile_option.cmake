


if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_compile_definitions(_GLIBCXX_DEBUG)
endif ()

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
    message(STATUS "Using GCC")
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
            -Wno-undef

    )
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
    message(STATUS "Using Clang")
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
            -Wno-undef

    )
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    #add_compile_options(/W4 /WX /permissive- /fp:strict /analyze /we4244 /we4018 /wd4018 /wd4365)
    add_compile_options("/W0")

endif ()

