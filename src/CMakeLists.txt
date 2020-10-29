add_executable(main main.c)

find_package(Threads REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)

add_library(count count.c)
target_include_directories(count PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(main PUBLIC count)

add_definitions(-Wall -Werror -Wpedantic)


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
