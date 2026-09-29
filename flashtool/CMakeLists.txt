cmake_minimum_required(VERSION 3.20)
project(AceFlashTool VERSION 1.0.2 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Set this to the Qt installation that matches the selected target platform and architecture.
set(ACEFLASHTOOL_QT_ROOT "" CACHE PATH "Architecture-matched Qt 5 installation")
if(ACEFLASHTOOL_QT_ROOT)
    list(PREPEND CMAKE_PREFIX_PATH "${ACEFLASHTOOL_QT_ROOT}")
endif()

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Network)
if(NOT APPLE)
    find_package(OpenSSL REQUIRED COMPONENTS Crypto)
endif()

add_subdirectory(third_party)

add_executable(AceFlashTool WIN32 MACOSX_BUNDLE
    main.cpp
    core/discovery.cpp
    core/firmware_file.cpp
    core/firmware_packager.cpp
    core/http_server.cpp
    core/mqtt_client.cpp
    targets/ams_target.cpp
    targets/printer_app_target.cpp
    ui/mainwindow.cpp
    ui/discovery_widget.cpp
    ui/flash_widget.cpp
    ui/mainwindow.ui
    ui/discovery_widget.ui
    ui/flash_widget.ui
)

if(APPLE)
    set_target_properties(AceFlashTool PROPERTIES
        OUTPUT_NAME "${PROJECT_NAME}${PROJECT_VERSION}"
        MACOSX_BUNDLE_BUNDLE_NAME "ACE Flash Tool"
        MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION}"
        MACOSX_BUNDLE_GUI_IDENTIFIER "org.anycubic-cfw.AceFlashTool"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION}"
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/macos/Info.plist.in"
    )

    set(ACEFLASHTOOL_CODESIGN_IDENTITY "Apple Development: Ozgun Ayaz (9HRAY44VNW)"
        CACHE STRING "Code-signing identity for AceFlashTool")
    add_custom_command(TARGET AceFlashTool POST_BUILD
        COMMAND codesign --force --sign "${ACEFLASHTOOL_CODESIGN_IDENTITY}"
            --entitlements "${CMAKE_CURRENT_SOURCE_DIR}/macos/AceFlashTool.entitlements"
            --timestamp=none
            "$<TARGET_BUNDLE_DIR:AceFlashTool>"
        COMMENT "Signing ${PROJECT_NAME}${PROJECT_VERSION}.app"
        VERBATIM
    )
endif()

target_include_directories(AceFlashTool PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(AceFlashTool PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Network
    qmqtt
)
if(NOT APPLE)
    target_link_libraries(AceFlashTool PRIVATE OpenSSL::Crypto)
endif()

# Windows OpenSSL runtime DLLs must match the selected target architecture.
set(OPENSSL_SRC "" CACHE PATH "Directory containing target-architecture OpenSSL runtime DLLs")
if(WIN32 AND NOT OPENSSL_SRC)
    set(_windows_arch "${CMAKE_GENERATOR_PLATFORM}")
    if(NOT _windows_arch)
        set(_windows_arch "${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}")
    endif()
    if(NOT _windows_arch)
        set(_windows_arch "${CMAKE_SYSTEM_PROCESSOR}")
    endif()
    if(NOT _windows_arch OR _windows_arch MATCHES "^(x64|x86_64|AMD64)$")
        set(OPENSSL_SRC "E:/Qt/Tools/QtCreator/bin")
    endif()
endif()
if(WIN32 AND OPENSSL_SRC)
    file(GLOB OPENSSL_RUNTIME_DLLS
        "${OPENSSL_SRC}/libssl*.dll"
        "${OPENSSL_SRC}/libcrypto*.dll"
    )
    foreach(SSL_DLL IN LISTS OPENSSL_RUNTIME_DLLS)
        get_filename_component(SSL_DLL_NAME "${SSL_DLL}" NAME)
        add_custom_command(TARGET AceFlashTool POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${SSL_DLL}"
                "$<TARGET_FILE_DIR:AceFlashTool>/${SSL_DLL_NAME}"
            COMMENT "Deploying ${SSL_DLL_NAME}")
    endforeach()
endif()

# Copy Qt DLLs to output directory after build
if(WIN32)
    get_target_property(_qmake Qt5::qmake IMPORTED_LOCATION)
    get_filename_component(_qt_bin "${_qmake}" DIRECTORY)
    find_program(WINDEPLOYQT windeployqt HINTS "${_qt_bin}")
    if(WINDEPLOYQT)
        add_custom_command(TARGET AceFlashTool POST_BUILD
            COMMAND "${WINDEPLOYQT}"
                --no-translations
                --no-opengl-sw
                --no-angle
                $<TARGET_FILE:AceFlashTool>
            COMMENT "Deploying Qt DLLs"
        )
        # Remove files not needed for this app
        add_custom_command(TARGET AceFlashTool POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E remove_directory "$<TARGET_FILE_DIR:AceFlashTool>/imageformats"
            COMMAND ${CMAKE_COMMAND} -E remove_directory "$<TARGET_FILE_DIR:AceFlashTool>/translations"
            COMMAND ${CMAKE_COMMAND} -E remove -f
                "$<TARGET_FILE_DIR:AceFlashTool>/opengl32sw.dll"
                "$<TARGET_FILE_DIR:AceFlashTool>/libGLESv2.dll"
                "$<TARGET_FILE_DIR:AceFlashTool>/libEGL.dll"
                "$<TARGET_FILE_DIR:AceFlashTool>/D3Dcompiler_47.dll"
            COMMENT "Removing unused OpenGL/ANGLE/imageformats/translations"
        )
    endif()
endif()
