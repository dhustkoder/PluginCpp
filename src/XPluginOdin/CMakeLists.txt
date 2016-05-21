project(XPluginOdin)
file(GLOB SRC ./*.cpp)
file(GLOB HEADERS ./*.h)
add_library(${PROJECT_NAME} SHARED ${HEADERS} ${SRC})

