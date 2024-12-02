project(YabaSanshiro)

cmake_minimum_required(VERSION 2.8)

#-------------------------------------------------------------------------------
#add local find scripts to CMAKE path
LIST(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/CMake/Utils
    ${CMAKE_CURRENT_SOURCE_DIR}/CMake/Packages
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(YAB_PACKAGE yabause)
set(YAB_VERSION_MAJOR 1)
set(YAB_VERSION_MINOR 16)
set(YAB_VERSION_PATCH 3)
set(YAB_VERSION "${YAB_VERSION_MAJOR}.${YAB_VERSION_MINOR}.${YAB_VERSION_PATCH}")

include(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC GIT_SHA1)
string(SUBSTRING ${GIT_SHA1} 0 6 GIT_SHA1_MINI )

set(CPACK_SOURCE_GENERATOR TGZ)
set(CPACK_PACKAGE_VENDOR "devMiyax")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING.txt")
set(CPACK_PACKAGE_FILE_NAME "yabasanshiro${YAB_TARGET}-${YAB_VERSION}-${GIT_SHA1_MINI}")
set(CPACK_PACKAGE_CONTACT "smiyaxdev@gmail.com" )
set(CPACK_PACKAGE_INSTALL_DIRECTORY "YabaSanshiro")

if (APPLE)
    set(CPACK_GENERATOR DragNDrop)
    set(CPACK_PACKAGE_FILE_NAME yabause-${YAB_VERSION}-mac)
endif ()

if (WIN32)
	set(CMAKE_CXX_STANDARD 17)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
	SET(CPACK_NSIS_INSTALLED_ICON_NAME yabasanshiro.exe)
	set(CPACK_NSIS_MENU_LINKS yabasanshiro.exe;"Yaba Sanshiro")
	set(CPACK_NSIS_URL_INFO_ABOUT "http://www.uoyabause.org")
	set(CPACK_NSIS_COMPRESSOR "/SOLID lzma")
	if(${CMAKE_SIZEOF_VOID_P} EQUAL 8)
		set(CPACK_SYSTEM_NAME "win64")
		set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")
		set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "${CPACK_PACKAGE_NAME}")
	else()
		set(CPACK_WIX_ARCHITECTURE "x86")
	endif ()
	set(CPACK_WIX_VERSION 3)
	set(CPACK_WIX_ARCHITECTURE x64)
	set(CPACK_WIX_UPGRADE_GUID "c0a71dab-2333-406c-9815-634e13221c46" )
	set(CPACK_WIX_PRODUCT_ICON "${CMAKE_CURRENT_SOURCE_DIR}/src/android/app/src/main/res/mipmap-xxxhdpi/ic_launcher_round.png" )
	set(CPACK_WIX_UI_BANNER "${CMAKE_CURRENT_SOURCE_DIR}/res/banner.png")
	set(CPACK_WIX_UI_DIALOG "${CMAKE_CURRENT_SOURCE_DIR}/res/dialog.png")
	set(CPACK_WIX_CULTURES en-US ja-jp pt-BR fr-FR)
	set(CPACK_WIX_PROPERTY_ARPHELPLINK "http://www.uoyabause.org/")
else()
	set(CPACK_PACKAGE_VERSION_MAJOR 2-${YAB_VERSION_MAJOR})
	set(CPACK_PACKAGE_VERSION_MINOR ${YAB_VERSION_MINOR})
	set(CPACK_PACKAGE_VERSION_PATCH ${YAB_VERSION_PATCH})
endif ()

include(CPack)

function(assign_source_group)
    foreach(_source IN ITEMS ${ARGN})
        if (IS_ABSOLUTE "${_source}")
            file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}")
        else()
            set(_source_rel "${_source}")
        endif()
        get_filename_component(_source_path "${_source_rel}" PATH)
        string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
        source_group("${_source_path_msvc}" FILES "${_source}")
    endforeach()
endfunction(assign_source_group)

add_subdirectory(doc)
add_subdirectory(l10n)
add_subdirectory(src)
