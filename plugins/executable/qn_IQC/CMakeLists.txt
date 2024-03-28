# qn_IQC

set(TARGET_NAME qn_IQC)
set(FOLDER_NAME plugins)

set(Header_Files
	../include/plugincorehelper.h
	../include/pluginbussiness.h
	../include/basenode.h
	createprocessnode.h
	robothans.h
	ui_robothans.h
	CTCPClient_Rob.h
	structInfo.h
	modbus-rtu.h
	
)

set(Source_Files
	main.cpp
	CTCPClient_Rob.cpp
	createprocessnode.cpp
	robothans.cpp
	../include/pluginbussiness.cpp
	../../../include/jsoncpp/jsoncpp.cpp
)



set(plugincore_DIR "../../../3rd/plugincore")
set(plugincore_INCLUDE_DIR ${plugincore_DIR}/include)
set(plugincore_LIB_DIR ${plugincore_DIR}/lib)
set(QUICKEDITOR_PATH "C:/Users/pc/Desktop/bin")

link_directories(../../../lib)
link_libraries(Qt5::Core Qt5::Widgets Qt5::Qml Qt5::Quick Qt5::QuickWidgets Qt5::RemoteObjects modbus.lib modbus.dll)

if(QUICKEDITOR_PATH)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${QUICKEDITOR_PATH}/plugins/executable/qn_IQC)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO})
endif()

link_directories(${plugincore_LIB_DIR})

#list(APPEND CMAKE_MODULE_PATH ${CONAN_CMAKE_MODULE_PATH_RELEASE} ${CONAN_CMAKE_MODULE_PATH_DEBUG})
include_directories(${CONAN_INCLUDE_DIRS_RELEASE} ${CONAN_INCLUDE_DIRS_DEBUG})

add_executable(${TARGET_NAME} ${Source_Files} ${Header_Files})  #编译为可执行文件

target_include_directories(${TARGET_NAME} PRIVATE ${Qt5Quick_PRIVATE_INCLUDE_DIRS})

#if(MSVC)
#    set_target_properties(${TARGET_NAME} PROPERTIES 
#        COMPILE_FLAGS "/MP"
#		FOLDER ${FOLDER_NAME}
#        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
#        VS_DEBUGGER_ENVIRONMENT "QML2_IMPORT_PATH=${RenderKit_DIR}/import;${_qt_bin_dir}/../qml\n\
#PATH=${_qt_bin_dir};${RenderKit_DIR}/bin;${RenderKit_DIR}/plugin;${OSG_BIN_DIR};OSG_FILE_PATH=$ENV{OSG_FILE_PATH}\n\
#QT_QPA_PLATFORM_PLUGIN_PATH=${_qt_bin_dir}/../plugins/platforms"
#        VS_DEBUGGER_WORKING_DIRECTORY "${DEMO_DEPLOY_PATH}"
#    )
#endif()


set_property(TARGET ${TARGET_NAME} PROPERTY AUTOMOC ON)

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/bin/plugins/executable/${TARGET_NAME}"
        #COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_NAME}.conf ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/${TARGET_NAME}.conf
		)

#链接plugincore库
target_link_libraries(${TARGET_NAME} plugincore Qt5::Core Qt5::QuickWidgets Qt5::Qml Qt5::Quick Qt5::Widgets 
	#OpenThreads.lib
	#CONAN_PKG::spdlog
)

#输出目录
set(DEMO_DEPLOY_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO})
# file(MAKE_DIRECTORY ${DEMO_DEPLOY_PATH})

add_custom_target(deploy_RenderKit
    #COMMAND ${DEPLOYQT_EXECUTABLE} "$<TARGET_FILE:${TARGET_NAME}>"
    #    --$<LOWER_CASE:$<CONFIG>> --qmldir ${CMAKE_SOURCE_DIR}
    #    --dir "${DEMO_DEPLOY_PATH}"
	#怎么拉RenderKit的依赖库？
    #COMMAND ${DEPLOYQT_EXECUTABLE} "$<TARGET_FILE:pluginrenderkit>"
    #    --$<LOWER_CASE:$<CONFIG>> --qmldir "$<TARGET_PROPERTY:pluginrenderkit,SOURCE_DIR>"
    #    --dir "${DEMO_DEPLOY_PATH}"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${DEMO_DEPLOY_PATH}/Sn3D/RenderKit"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${Sn3DRenderKit_IMPORT_PATH}"
        "${DEMO_DEPLOY_PATH}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${Sn3DRenderKit_BIN_PATH}"
        "${DEMO_DEPLOY_PATH}"
    #COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:${TARGET_NAME}>"
    #    "${DEMO_DEPLOY_PATH}"
    #COMMAND ${CMAKE_COMMAND} -E copy_directory "${DEPLOY_PATH}/plugin"		#Cuda用
    #    "${DEMO_DEPLOY_PATH}"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${OSG_BIN_DIR}"
        "${DEMO_DEPLOY_PATH}"
    DEPENDS ${TARGET_NAME}
)

set_target_properties(deploy_RenderKit PROPERTIES FOLDER "examples/helpers")

#release调试
if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /DEBUG")
	set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /DEBUG")
	target_compile_options(${TARGET_NAME} PRIVATE /Od /Ob0)
endif()
