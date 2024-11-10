cmake_minimum_required(VERSION 3.13) # declare the minimum required CMake version

   project(server VERSION 1.0 LANGUAGES CXX) # project name, version and language
   project(client VERSION 1.0 LANGUAGES CXX) # project name, version and language
   
   set(CMAKE_CXX_STANDARD 23) # C++ standart

   get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY) # Check if the directory is subproject

   # SFML
   set(SFML_DIR "/usr/include/SFML") # path to SFML (dpkg -L libsfml-dev)
   find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED) # <optional> - let CMake automatically find the SFML

   # doctest
   find_package(doctest REQUIRED)
   
   option(SWALLOW_TESTING "Enable module testing" ON)
   option(SWALLOW_COVERAGE "Enable code coverage" OFF)

   add_executable(
    server
    server.cpp
   )

   add_executable(
    client
    client.cpp
   )

   target_include_directories(server PRIVATE include)
   target_link_libraries(server sfml-network sfml-graphics sfml-window sfml-system)

   target_include_directories(client PRIVATE include)
   target_link_libraries(client sfml-network sfml-graphics sfml-window sfml-system)