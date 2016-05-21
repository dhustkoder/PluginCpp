project(PluginCpp)
file(GLOB SRC ./LoadPlugin.cpp)
file(GLOB HEADERS ./XPlugin.h)
add_executable(${PROJECT_NAME} ${HEADERS} ${SRC})
target_link_libraries( ${PROJECT_NAME} -ldl )


add_subdirectory(XPluginIfrit)
add_subdirectory(XPluginOdin)
