# Traverse subdirectories for translation units
file(GLOB_RECURSE project_sources *.cpp core/*.cpp graphics/*.cpp ui/*.cpp)
add_executable(${CMAKE_PROJECT_NAME} ${project_sources})

# GLFW - Lightweight multi-platform windowing, context & event polling.
find_package(glfw3 CONFIG REQUIRED)

# Disable all side GLFW builds
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glfw)

# OpenGL loader (no dealing with function pointers manually).
find_package(glbinding CONFIG REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glbinding::glbinding glbinding::glbinding-aux)

# GLM - Math library for graphics applications (OpenGL).
find_package(glm CONFIG REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glm::glm)

# Dear ImGui - Minimal immediate mode GUI
find_package(imgui CONFIG REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE imgui::imgui)

# File dialogs
# find_package(tinyfiledialogs CONFIG REQUIRED)
# target_link_libraries(minity PRIVATE tinyfiledialogs::tinyfiledialogs)

# include_directories(core/)
# include_directories(graphics/)
# include_directories(ui/)
