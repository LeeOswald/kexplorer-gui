
set(SOURCES
    main.cpp
)

set(RESOURCES
    kexplorer.qrc
)


qt6_add_resources(RESOURCE_SOURCES ${RESOURCES})
#qt6_wrap_ui(UI_SOURCES ${UIS})

if(KX_WINDOWS EQUAL 1)
    set(WINDOWS_RESOURCE_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/kexplorer.rc")
    set(IMAGE_SUBSYSTEM WIN32)
    set(CMAKE_EXE_LINKER_FLAGS /MANIFEST:NO)
endif()    
    
add_executable(${KX_APP} ${IMAGE_SUBSYSTEM} ${SOURCES} ${RESOURCE_SOURCES} ${UI_SOURCES} ${WINDOWS_RESOURCE_SCRIPT})

target_compile_features(${KX_APP} PUBLIC ${KX_CXX_FEATURES})

# Qt6Widgets_LIBRARIES variable also includes QtGui and QtCore
target_link_libraries (${KX_APP} PRIVATE ${Qt6Widgets_LIBRARIES} Boost::program_options ${PLATFORM_LIBRARIES} ${KES_SRVLIB})



