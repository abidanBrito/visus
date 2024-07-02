# Traverse subdirectories for translation units
file(GLOB_RECURSE project_sources *.cpp)
add_executable(${CMAKE_PROJECT_NAME} ${project_sources})

# WinAPI components (runtime libraries)
#	user32.dll - Windowing, user interface primitives, input, messaging, etc.
# target_link_libraries(${CMAKE_PROJECT_NAME} user32)

# GLAD - OpenGL loader (no working with function pointers manually).
# https://stackoverflow.com/a/56842079/2394163
#target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glad ${CMAKE_DL_LIBS})

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

# Dear ImGui - Minimal immediate mode GUI
# find_package(imgui CONFIG REQUIRED)
# target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE imgui::imgui)

# File dialogs
# find_package(tinyfiledialogs CONFIG REQUIRED)
# target_link_libraries(minity PRIVATE tinyfiledialogs::tinyfiledialogs)
