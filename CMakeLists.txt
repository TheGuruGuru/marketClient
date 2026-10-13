cmake_minimum_required(VERSION 4.0)
project(marketClient)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenSSL REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})

set(CMAKE_CXX_STANDARD 20)

file(GLOB sources *.cpp data/*.cpp gui/*.cpp)

add_executable(${PROJECT_NAME} ${sources}
)

set(IMGUI_DIR /home/m-a-d/Programmieren/libs/imGUI/imgui/imgui)
include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends)

add_library(ImGui STATIC IMPORTED)
set_target_properties(ImGui PROPERTIES
    IMPORTED_LOCATION "${IMGUI_DIR}/libImGui.a"
)

target_include_directories(${PROJECT_NAME} PUBLIC ${jsoncpp_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR} ${GLFW_INClUDE_DIRS} ${GLEW_INCLUDE_DIRS} "/home/m-a-d/Programmieren/libs/cpp-httplib")

target_link_libraries(${PROJECT_NAME} glfw  OpenGL::GL GLEW::GLEW ImGui OpenSSL::SSL ${JSONCPP_LIBRARIES})
