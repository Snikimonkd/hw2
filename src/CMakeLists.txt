add_executable(main main.c)

FIND_PACKAGE(OpenMP REQUIRED)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_library(count count.c)
target_include_directories(count PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(main PUBLIC count)



option(USE_MULTI "use multithreading lib" OFF)

if(USE_MULTI)
    add_library(multithreding_count SHARED multithreding_count.c)
    target_include_directories(multithreding_count PUBLIC "${PROJECT_SOURCE_DIR}/include")
    target_link_libraries(main PUBLIC multithreding_count Threads::Threads)
else()
    add_library(linear_count STATIC linear_count.c)
    target_include_directories(linear_count PUBLIC "${PROJECT_SOURCE_DIR}/include")
    target_link_libraries(main PUBLIC linear_count)
endif()
