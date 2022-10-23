cmake_minimum_required(VERSION 3.21)
project(Lab6)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab6 main.cpp poly.h)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg

target_link_libraries(Lab6 gtest_main)
add_test(NAME example_test COMMAND Lab6)
