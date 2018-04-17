cmake_minimum_required(VERSION 3.4)
project(EquationSolver)

set(CMAKE_CXX_STANDARD 11)



#example setting of boost directory
set(Boost_INCLUDE_DIR /usr/local/Cellar/boost@1.55/1.55.0_1/include)
set(Boost_LIBRARY_DIR /usr/local/Cellar/boost@1.55/1.55.0_1/lib)

find_package(Boost)

if(Boost_FOUND)
    message("Boost incl dirs: ${Boost_INCLUDE_DIRS}")
    message("Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message("Boost_VERSION: ${Boost_VERSION}")
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(EquationSolver main.cpp compute.cpp split.cpp header.h )
    target_link_libraries(EquationSolver ${Boost_LIBRARIES})

else()
    message([WARNING]"Set boost directory in cmake before execution if boost is not found at /usr/local/include")

endif()
