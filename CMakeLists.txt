cmake_minimum_required(VERSION 2.8.9)
project(SolarusQuestCreator)
# Active l'appel automatique à moc si nécéssaire
set(CMAKE_AUTOMOC ON)
# Dependances
find_package(Qt5Core)
find_package(Lua51 REQUIRED)
# Sources
file(
  GLOB_RECURSE
  source_files
  src/*.cpp
  include/*.h
)
# Resources
file(
  GLOB_RECURSE
  resource_files
  resource/*.qrc
)
# Dossiers des headers
include_directories(
  include/
  ${LUA_INCLUDE_DIR}
)
# Resources Qt5
qt5_add_resources(
  source_files
  ${resource_files}
)
# Exécutable
add_executable(
  ${PROJECT_NAME}
  ${source_files}
)
# Modules Qt5
qt5_use_modules(
  ${PROJECT_NAME}
  Widgets
)
# Bibliothèques
target_link_libraries(
  ${PROJECT_NAME}
  ${LUA_LIBRARY}
)
