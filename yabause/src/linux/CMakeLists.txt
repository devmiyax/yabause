project(yabause-linux)

yab_port_start()

include(FindSDL2 OPTIONAL)
find_package(OpenGLES)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

if (NOT OPENGLES2_FOUND)
	return()
endif (NOT OPENGLES2_FOUND)


if (SDL2_FOUND)
		add_definitions(-DHAVE_LIBSDL2=1)
		set(PORT_INCLUDE_DIRS ${PORT_INCLUDE_DIRS} ${SDL2_INCLUDE_DIR})
		set(PORT_LIBRARIES ${PORT_LIBRARIES} ${SDL2_LIBRARY})
endif (SDL2_FOUND)

set(PORT_INCLUDE_DIRS ${PORT_INCLUDE_DIRS} ${OPENGLES_INCLUDE_DIR} )
set(PORT_LIBRARIES ${PORT_LIBRARIES} ${OPENGLES2_LIBRARIES} )

if (GLFW_FOUND)
set(PORT_INCLUDE_DIRS ${GLFW_INCLUDE_DIRS})
set(PORT_LIBRARIES ${GLFW_LIBRARIES})
set(yabause_linux_SOURCES ${yabause_linux_SOURCES}
	platform/glfw/platform.c
)
set(yabause_linux_HEADERS ${yabause_linux_HEADERS}
	platform/glfw/platform.h
)
include_directories(platform/glfw)
endif (GLFW_FOUND)



set(yabause_linux_SOURCES ${yabause_linux_SOURCES}
	main.c
)

add_executable(yabause-linux ${yabause_linux_SOURCES} ${yabause_linux_HEADERS} )
target_link_libraries(yabause-linux yabause ${YABAUSE_LIBRARIES} ${PORT_LIBRARIES})

yab_port_success(yabause-linux)

install(TARGETS yabause-linux DESTINATION "bin")
install(FILES "doc/yabause.1" DESTINATION "${YAB_MAN_DIR}/man1" RENAME "${YAB_PORT_NAME}.1")
install(FILES "yabause.png" DESTINATION "share/pixmaps")
