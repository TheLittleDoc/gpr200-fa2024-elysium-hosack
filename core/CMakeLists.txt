file(
 GLOB_RECURSE CORE_INC CONFIGURE_DEPENDS
 RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
 *.h *.hpp
)

file(
 GLOB_RECURSE CORE_SRC CONFIGURE_DEPENDS
 RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
 *.c *.cpp
)

set(CORE_INC_DIR
 ${CMAKE_CURRENT_SOURCE_DIR}
 CACHE PATH "CORE INCLUDE SOURCE PATH"
)

add_library(core STATIC ${CORE_SRC} ${CORE_INC}
        serinity/Shader.cpp
        serinity/Shader.h
        ew/external/glad.h
        ew/external/glad.cpp
        serinity/Texture2D.cpp
        serinity/Texture2D.h
)

target_link_libraries(core PUBLIC glfw glm)




install (TARGETS core DESTINATION lib)
install (FILES ${CORE_INC} DESTINATION include/core)

