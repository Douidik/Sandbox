file(GLOB_RECURSE SBX_ENGINE_SRC [a-zA-Z0-9]*.hpp [a-zA-Z0-9]*.cpp)

add_library(SandboxEngine STATIC ${SBX_ENGINE_SRC})

target_link_libraries(SandboxEngine PUBLIC ${CONAN_LIBS})
target_include_directories(SandboxEngine PUBLIC ./)
