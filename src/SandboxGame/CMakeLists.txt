file(GLOB_RECURSE SBX_GAME_SRC [a-zA-Z0-9]*.hpp [a-zA-Z0-9]*.cpp)

add_executable(SandboxGame ${SBX_GAME_SRC})
target_link_libraries(SandboxGame PUBLIC ${CONAN_LIBS} SandboxEngine)
