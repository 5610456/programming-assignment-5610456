

cmake_minimum_required(VERSION 3.5)

# Use environment variable for cross-compilation
set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})

# Project def
project(BoidsBuild VERSION 0.1 LANGUAGES CXX)

# Target executable
set(TargetName Boids)

# Enable Qt
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt packages
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets OpenGLWidgets)

# Find NGL library
find_package(NGL CONFIG REQUIRED)

# Set UI search
set(CMAKE_AUTOUIC_SEARCH_PATHS ${PROJECT_SOURCE_DIR}/ui)

# Add executable and specify initial source files
add_executable(${TargetName}
        src/main.cpp
        include/boid.h
        src/boid.cpp
        src/Flock.cpp
)

# Add all source files as private sources
target_sources(${TargetName} PRIVATE
        src/main.cpp
        src/MainWindow.cpp
        src/NGLScene.cpp
        src/Flock.cpp
        src/NGLSceneMouseControls.cpp
        include/MainWindow.h
        include/Flock.h
        include/NGLScene.h
        include/WindowParams.h
        ui/MainWindow.ui
        shaders/BoidFragment.glsl
        shaders/BoidVertex.glsl
)

# Include project headers directory
target_include_directories(${TargetName} PRIVATE include)

# Link Qt libraries
target_link_libraries(${TargetName} PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::OpenGLWidgets
)

# Link NGL library
target_link_libraries(${TargetName} PRIVATE NGL)

# Custom target to copy shaders folder to the build output directory
add_custom_target(${TargetName}CopyShaders ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders
        $<TARGET_FILE_DIR:${TargetName}>/shaders
)
