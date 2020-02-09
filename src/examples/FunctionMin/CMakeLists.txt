project(FunctionMin)

set(SOURCE_FMIN
    main.cpp
    )

set(HEADER_FMIN
    )


add_executable(FunctionMin ${HEADER_FMIN} ${SOURCE_FMIN})

target_include_directories(FunctionMin PUBLIC
                          "${SimulatedAnnealing_BINARY_DIR}"
                          "${SimulatedAnnealing_SOURCE_DIR}/src"
                          )

target_link_libraries(FunctionMin SimulatedAnnealing)

# add the binary tree to the search path for include files
# so that we will be founded by FunctionMin example

