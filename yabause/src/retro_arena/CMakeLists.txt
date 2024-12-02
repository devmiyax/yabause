project(yabause-retro-arena)

yab_port_start()

find_package(SDL2 COMPONENTS sdl)
find_package(SDL2 REQUIRED)
find_package(OpenGLES)
find_package(PkgConfig REQUIRED)

find_package(Boost REQUIRED COMPONENTS system filesystem date_time locale)

#if (NOT OPENGLES2_FOUND)
#	return()
#endif (NOT OPENGLES2_FOUND)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(pugixml)
add_subdirectory(nanogui-sdl)

#include( ../glfw/external_zlib.cmake )
include( ${CMAKE_SOURCE_DIR}/CMake/Packages/external_libpng.cmake )

set( CD_INSTALL_DIR  ${CMAKE_CURRENT_BINARY_DIR})

#ExternalProject_Add( libcharsetdetect
#     PREFIX ${CMAKE_CURRENT_BINARY_DIR}/libcharsetdetect#
#	 CMAKE_ARGS     -DCMAKE_INSTALL_PREFIX=${CD_INSTALL_DIR
#     GIT_REPOSITORY https://github.com/batterseapower/libcharsetdetect.git
#)
#ExternalProject_Get_Property(libcharsetdetect SOURCE_DIR)
#set( libcharsetdetect_dir ${SOURCE_DIR} )

set( sqlite3_source_path ${CMAKE_CURRENT_BINARY_DIR}/external/sqlite3/src/external_sqlite3/ )
set( sqlite3_cmake_file_path ${sqlite3_source_path}/CMakeLists.txt )

ExternalProject_Add( external_sqlite3
  PREFIX            ${CMAKE_CURRENT_BINARY_DIR}/external/sqlite3
  INSTALL_DIR       ${CMAKE_CURRENT_BINARY_DIR}
  # http://www.sqlite.org/download.html
  URL               https://www.sqlite.org/2022/sqlite-amalgamation-3400000.zip
##  URL_HASH          SHA1=cee1d63a9ae8d8f5948c12682c5d746b72363aaf
  PATCH_COMMAND
    COMMAND echo cmake_minimum_required( VERSION 3.2 ) > ${sqlite3_cmake_file_path}
    COMMAND echo project( sqlite3_project ) >> ${sqlite3_cmake_file_path}
    COMMAND echo find_package( Threads ) >> ${sqlite3_cmake_file_path}
    COMMAND echo add_library( sqlite3 sqlite3.c ) >> ${sqlite3_cmake_file_path}
    COMMAND echo install( TARGETS sqlite3 DESTINATION lib ) >> ${sqlite3_cmake_file_path}
    COMMAND echo install( FILES sqlite3.h DESTINATION include ) >> ${sqlite3_cmake_file_path}
  CMAKE_ARGS        -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}
                    -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
                    -DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
                    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
)

#------------------------------------------------------------------------------
# nlohmann/json
#  * sets EXTERNAL_JSON_INCLUDE_DIR 

ExternalProject_Add(
     Json
     PREFIX ${CMAKE_CURRENT_BINARY_DIR}/Json
     GIT_REPOSITORY https://github.com/nlohmann/json.git
     # For shallow git clone (without downloading whole history)
     #GIT_SHALLOW 1
     # For point at certain tag
     GIT_TAG v3.2.0
     #disables auto update on every build
     UPDATE_DISCONNECTED 1
     #disable following
     CONFIGURE_COMMAND "" BUILD_COMMAND "" INSTALL_DIR "" INSTALL_COMMAND ""
     )
 # Update json target
 add_custom_target(external-Json-update
     COMMENT "Updated Nlohmann/Json"
     WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Json/src/Json
     COMMAND ${GIT_EXECUTABLE} pull
     DEPENDS Json)
# set include directory
set(EXTERNAL_JSON_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/Json/src/Json/single_include")

set(PORT_INCLUDE_DIRS ${EXTERNAL_JSON_INCLUDE_DIR} ${SDL2_INCLUDE_DIR} ${png_INCLUDE_DIR} ${zlib_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include )
set(PORT_LIBRARIES ${SDL2_LIBRARY} ${OPENGLES2_LIBRARIES} ${png_STATIC_LIBRARIES} ${zlib_STATIC_LIBRARIES} )

message("Nlohmann/json dir =" ${EXTERNAL_JSON_INCLUDE_DIR})

set(yabause_ra_SOURCES
  common.h
	main.cpp
	InputManager.h
	InputManager.cpp
	InputConfig.h
	InputConfig.cpp
	MenuScreen.h
  MenuScreen.cpp
  Preference.h
  Preference.cpp
  EventManager.h
  EventManager.cpp
  GameInfo.h
  GameInfo.cpp
  GameListPanel.h
  GameListPanel.cpp
  ../about.h
  ../about.c
) 

if (YAB_WANT_VULKAN)
set( yabause_ra_SOURCES ${yabause_ra_SOURCES} ../vulkan/Window_sdl.cpp )
endif()


link_directories( ${link_directories} ${LIBCHDR_LIB_DIR} ${CMAKE_CURRENT_BINARY_DIR}/lib )

include_directories( 
  ${PORT_INCLUDE_DIRS} 
  #${libcharsetdetect_dir} 
  ${Boost_INCLUDE_DIR} 
  ${sqlite3_source_path} 
  "nanogui-sdl/include" 
  "nanogui-sdl/ext/eigen" 
  "win/include" )

set(APP_ICON_RESOURCE_WINDOWS application.rc)

add_executable(yabause-retro-arena WIN32 ${yabause_ra_SOURCES} ${APP_ICON_RESOURCE_WINDOWS} ${CMAKE_CURRENT_SOURCE_DIR}/res/utf8.manifest )


# OpenSSL for https
if(WIN32) 

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include )

# 64bit
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	target_link_libraries( yabause-retro-arena ${CMAKE_CURRENT_SOURCE_DIR}/lib/x64/libssl.lib)
	target_link_libraries( yabause-retro-arena ${CMAKE_CURRENT_SOURCE_DIR}/lib/x64/libcrypto.lib)
else()
	target_link_libraries( yabause-retro-arena ${CMAKE_CURRENT_SOURCE_DIR}/lib/x86/libssl-1_1.lib)
	target_link_libraries( yabause-retro-arena ${CMAKE_CURRENT_SOURCE_DIR}/lib/x86/libcrypto-1_1.lib)
endif()

else()
	
  find_package(OpenSSL REQUIRED) 
	if( OpenSSL_FOUND )
		include_directories(${OPENSSL_INCLUDE_DIRS})
		link_directories(${OPENSSL_LIBRARIES})
		message(STATUS "Using OpenSSL ${OPENSSL_VERSION}")
		target_link_libraries(yabause-retro-arena ${OPENSSL_LIBRARIES})
  endif()

endif()


target_link_libraries(yabause-retro-arena yabause  ${Boost_LIBRARIES} pugixml ${YABAUSE_LIBRARIES} ${PORT_LIBRARIES} nanogui ${LIBCHDR_LIBRARIES} Shcore )
target_link_libraries( yabause-retro-arena ${LIBCHDR_LIBRARIES} )
target_link_libraries( yabause-retro-arena ${zlib_STATIC_LIBRARIES} )
target_link_libraries( yabause-retro-arena ${CMAKE_CURRENT_BINARY_DIR}/lib/sqlite3.lib )
if (YAB_WANT_VULKAN)
target_link_libraries( yabause-retro-arena ${GLFW_LIBRARIES} ${LIBVULKAN} ${SHADERC_LIBRARIES} )
endif()
add_dependencies(yabause-retro-arena Json png zlib libchd nanogui external_sqlite3)

#add_dependencies(yabause-retro-arena libcharsetdetect)
#target_include_directories(yabause-retro-arena PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libcharsetdetect/lib)
#target_link_directories(yabause-retro-arena PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libcharsetdetect/lib/.libs)
#target_link_libraries(yabause-retro-arena PRIVATE charsetdetect)


yab_port_success(yabause-retro-arena)


set_target_properties(yabause-retro-arena PROPERTIES OUTPUT_NAME yabasanshiro)

set(YAB_TARGET "-HH"  CACHE STRING "package name" )

if (WIN32)
install(TARGETS yabause-retro-arena DESTINATION ".")
set_property(INSTALL $<TARGET_FILE_NAME:yabause-retro-arena>
  PROPERTY CPACK_START_MENU_SHORTCUTS "Yaba Sanshiro"
)
#install(FILES "default.config" DESTINATION "." )
install(FILES "howtouse.md" DESTINATION "." )
#install(FILES "place_games_here" DESTINATION "./games" )
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/../../COPYING.txt    DESTINATION "." RENAME COPYING.txt)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/boxart.txt    DESTINATION "." )
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/../../EULA.txt    DESTINATION "." RENAME EULA.txt)
get_filename_component(SDL2_BINARY_DIR ${SDL2_LIBRARY} PATH)
install(DIRECTORY ${SDL2_BINARY_DIR}/ DESTINATION "." FILES_MATCHING PATTERN "SDL2.dll")
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/fonts DESTINATION "." )
else ()
install(TARGETS yabause-retro-arena DESTINATION ".")
install(FILES "README.md" DESTINATION "." )
endif ()



