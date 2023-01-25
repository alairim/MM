find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Threads REQUIRED)

add_library(Simulation SHARED
  elevator.h
  elevator_output.h
  elevator.cpp
  simulation.h
  simulation.cpp
  mainwindow.cpp
  mainwindow.h
  mainwindow.ui
)
set_target_properties(Simulation PROPERTIES
    AUTOUIC ON
    AUTOMOC ON
    AUTORCC ON
)
target_link_libraries(Simulation PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    Threads::Threads
)
