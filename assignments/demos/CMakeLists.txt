file(
 GLOB_RECURSE demos_INC CONFIGURE_DEPENDS
 RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
 *.h *.hpp
)

file(
 GLOB_RECURSE demos_SRC CONFIGURE_DEPENDS
 RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
 *.c *.cpp
)
#Copies this demos's asset folder to bin when it is built
add_custom_target(copyAssetsDemos ALL COMMAND ${CMAKE_COMMAND} -E copy_directory
${CMAKE_CURRENT_SOURCE_DIR}/assets/
${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/)

install(FILES ${demos_INC} DESTINATION include/demos)
add_executable(demos ${demos_SRC} ${demos_INC})
target_link_libraries(demos PUBLIC core IMGUI glm)
target_include_directories(demos PUBLIC ${CORE_INC_DIR} ${stb_INCLUDE_DIR})

#Trigger asset copy when demos is built
add_dependencies(demos copyAssetsA4)