cmake_minimum_required(VERSION 2.7)
project(StockComplexNetworks)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/CMakeModules")

SET(CXX11_FLAGS -std=gnu++11)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX11_FLAGS}")

SET(INCLUDES ${PROJECT_SOURCE_DIR}/include include/config.h src/PropertyMatrix.cpp include/PropertyMatrix.h)
INCLUDE_DIRECTORIES(${INCLUDES})

FILE(GLOB_RECURSE SOURCES "src/*.cpp")
ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCES} ${INCLUDES})

add_custom_target("${PROJECT_NAME}_SUCCESSFUL" ALL
        DEPENDS ${PROJECT_NAME}
        COMMAND ${CMAKE_COMMAND} -E echo ""
        COMMAND ${CMAKE_COMMAND} -E echo "====================="
        COMMAND ${CMAKE_COMMAND} -E echo "  Compile complete!  "
        COMMAND ${CMAKE_COMMAND} -E echo "====================="
        COMMAND ${CMAKE_COMMAND} -E echo "${CMAKE_CURRENT_BINARY_DIR}"
        )

target_link_libraries(${PROJECT_NAME})