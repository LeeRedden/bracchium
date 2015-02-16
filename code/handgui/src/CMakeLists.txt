cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project( HandGUI )


set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_BUILD_TYPE Debug)



# QT Includes
find_package(Qt4 REQUIRED)
SET(CMAKEQT_LIBS ${QT_QTCORE_LIBRARY}
                 ${QT_QTGUI_LIBRARY}
                 ${QT_QTSVG_LIBRARY}
                 ${QT_QTNETWORK_LIBRARY}
                 ${QT_INCLUDE_DIRS}
                 ${QT_QTXML_LIBRARY}) # Add here any other QT module or other library
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})


# set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# set the default path for builtlibraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)



#Put here CPPs
SET(CMAKEQT_SRCS
    main.cpp
    CMakeQt.cpp
    ServoDriver.cpp
    PhidgetUtilities.cpp
    RoyCalibration.cpp
    RoyDriver.cpp
    MotionPaths.cpp
)

SET(CMAKEQT_HDRS
    CMakeQt.h
    ServoDriver.hpp
    PhidgetUtilities.hpp
    RoyCalibration.hpp
    RoyDriver.hpp
    MotionPaths.hpp
    SignLanguage.hpp
)

#Put here QRC files to be Rcc-ed
SET(CMAKEQT_RCC
    resources.qrc
)

SET(QT_USE_QTGUI TRUE)

#include paths for vlmc
INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_BINARY_DIR}
#  ${CMAKE_CURRENT_BINARY_DIR}/src
#  .
)

#Put here UI files
SET(CMAKEQT_UIS
    CMakeQt.ui
)

QT4_WRAP_UI(CMAKEQT_UIS_H ${CMAKEQT_UIS})
QT4_ADD_RESOURCES(CMAKEQT_RCC_SRCS ${CMAKEQT_RCC})
QT4_WRAP_CPP(CMAKEQT_MOC_SRCS ${CMAKEQT_HDRS})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")

set_source_files_properties(main.cpp PROPERTIES COMPILE_FLAGS -std=gnu++0x)
ADD_EXECUTABLE(cmakeqt ${CMAKEQT_SRCS} ${CMAKEQT_MOC_SRCS} ${CMAKEQT_UIS_H} ${CMAKEQT_RCC_SRCS} ${QT_INCLUDE_DIRS} ${CMAKEQT_HDRS} )
TARGET_LINK_LIBRARIES(cmakeqt ${CMAKEQT_LIBS} phidget21 )

