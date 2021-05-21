cmake_minimum_required(VERSION 3.19)
project(C__ClearVolume)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH " ")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)

include_directories(images)
include_directories(uis)

configure_file(images/loading.gif images/loading.gif COPYONLY)
add_executable(${PROJECT_NAME} main.cpp mainwindow.cpp mainwindow.h uis/mainWindow.ui functions.cpp functions.h filesizecounter.cpp filesizecounter.h)

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
include(InstallRequiredSystemLibraries)
include(CPack)

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
