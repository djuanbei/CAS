
cmake_policy(SET CMP0135 NEW)         # Use the new behavior globally

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


if (CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))

    target_compile_options(gmock PRIVATE -w)
    target_compile_options(gmock_main PRIVATE -w)
    target_compile_options(gtest PRIVATE -w)
    target_compile_options(gtest_main PRIVATE -w)

else ()
    target_compile_options(gmock PRIVATE "/wd4005"
            "/wd4101"
            "/wd4244"
            "/wd4305"
            "/wd4996")
    target_compile_options(gmock_main PRIVATE "/wd4005"
            "/wd4101"
            "/wd4244"
            "/wd4305"
            "/wd4996")
    target_compile_options(gtest PRIVATE "/wd4005"
            "/wd4101"
            "/wd4244"
            "/wd4305"
            "/wd4996")
    target_compile_options(gtest_main PRIVATE "/wd4005"
            "/wd4101"
            "/wd4244"
            "/wd4305"
            "/wd4996")

endif ()


enable_testing()
include(GoogleTest)


