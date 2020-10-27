add_executable(main main.c)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_library(count count.c)
target_include_directories(count PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(main PRIVATE count)


option(USE_MULTI "use multithreading lib" OFF)

if(USE_MULTI)
    add_library(multithreding_count multithreding_count.c)
    target_include_directories(multithreding_count PUBLIC "${PROJECT_SOURCE_DIR}/include")
    target_link_libraries(main PRIVATE multithreding_count Threads::Threads)
else()
    add_library(linear_count linear_count.c)
    target_include_directories(linear_count PUBLIC "${PROJECT_SOURCE_DIR}/include")
    target_link_libraries(main PRIVATE linear_count)
endif()
