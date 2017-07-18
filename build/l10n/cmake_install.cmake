# Install script for directory: /home/francois/workspace/uoyabause/yabause/yabause/l10n

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/yabause/yts" TYPE FILE RENAME "ar.yts" FILES "/home/francois/workspace/uoyabause/yabause/yabause/l10n/yabause_ar.yts")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/yabause/yts" TYPE FILE RENAME "de.yts" FILES "/home/francois/workspace/uoyabause/yabause/yabause/l10n/yabause_de.yts")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/yabause/yts" TYPE FILE RENAME "es.yts" FILES "/home/francois/workspace/uoyabause/yabause/yabause/l10n/yabause_es.yts")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/yabause/yts" TYPE FILE RENAME "fr.yts" FILES "/home/francois/workspace/uoyabause/yabause/yabause/l10n/yabause_fr.yts")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/yabause/yts" TYPE FILE RENAME "it.yts" FILES "/home/francois/workspace/uoyabause/yabause/yabause/l10n/yabause_it.yts")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/yabause/yts" TYPE FILE RENAME "lt.yts" FILES "/home/francois/workspace/uoyabause/yabause/yabause/l10n/yabause_lt.yts")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/yabause/yts" TYPE FILE RENAME "nl.yts" FILES "/home/francois/workspace/uoyabause/yabause/yabause/l10n/yabause_nl.yts")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/yabause/yts" TYPE FILE RENAME "pt.yts" FILES "/home/francois/workspace/uoyabause/yabause/yabause/l10n/yabause_pt.yts")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/yabause/yts" TYPE FILE RENAME "pt_BR.yts" FILES "/home/francois/workspace/uoyabause/yabause/yabause/l10n/yabause_pt_BR.yts")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/yabause/yts" TYPE FILE RENAME "ru.yts" FILES "/home/francois/workspace/uoyabause/yabause/yabause/l10n/yabause_ru.yts")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/yabause/yts" TYPE FILE RENAME "sv.yts" FILES "/home/francois/workspace/uoyabause/yabause/yabause/l10n/yabause_sv.yts")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/yabause/yts" TYPE FILE RENAME "zh_CN.yts" FILES "/home/francois/workspace/uoyabause/yabause/yabause/l10n/yabause_zh_CN.yts")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/yabause/yts" TYPE FILE RENAME "zh_TW.yts" FILES "/home/francois/workspace/uoyabause/yabause/yabause/l10n/yabause_zh_TW.yts")
endif()

