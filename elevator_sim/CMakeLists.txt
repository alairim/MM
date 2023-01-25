cmake_minimum_required(VERSION 3.5)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

project(elevator_sim LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)
add_subdirectory(simulation)

add_executable(elevator_sim
    main.c
    ext_work.h
    multiword_types.h
    rt_logging.h
    rt_zcfcn.c
    rt_zcfcn.h
    rtmodel.h
    rtw_continuous.h
    rtw_solver.h
    rtwtypes.h
    sim_ele_data.c
    sim_ele_private.h
    sim_ele_types.h
    sim_ele.c
    sim_ele.h
    solver_zc.h
    tmwtypes.h
    zero_crossing_types.h
    simulation/elevator.h
    # ADD YOUR EXTRA SOURCE FILES HERE
)
target_link_libraries(elevator_sim LINK_PUBLIC Simulation m)
