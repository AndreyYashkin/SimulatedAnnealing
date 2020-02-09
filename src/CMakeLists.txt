set(SOURCE_LIB
    CoolingSchedule.cpp
    SimulatedAnnealing.cpp
    )

set(HEADER_LIB_PUBLIC
    CoolingSchedule.h
    SimulatedAnnealing.h
    )
    
set(HEADER_LIB_PRIVATE # headers that shall not be seen by lib users
   )

add_library(SimulatedAnnealing STATIC ${HEADER_LIB_PUBLIC} ${HEADER_LIB_PRIVATE} ${SOURCE_LIB})    
       

OPTION(BUILD_EXAMPLES "Build examples that are not required P-median" OFF)
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
