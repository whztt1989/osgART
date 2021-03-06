set(lib_name "osgART")

#osgart_folder()

include_directories(${CMAKE_SOURCE_DIR}/include)

set(lib_srcs
	Foundation.cpp
    	Object.cpp
    	Event.cpp	
	BaseCallback.cpp
	PluginManager.cpp
	Video.cpp
	VideoCallback.cpp
	VideoConfiguration.cpp
	VideoStream.cpp
#	VideoStreamCallback.cpp
	VideoGeode.cpp
	VideoPlane.cpp
	VideoLayer.cpp
	VideoUtils.cpp
	Tracker.cpp
	TrackerCallback.cpp
	TrackerConfiguration.cpp
	CameraConfiguration.cpp
	TrackerTrainingSupport.cpp
	TrackerUtils.cpp
	Target.cpp
	TargetCallback.cpp
	VisualTracker.cpp
	GPSInertialTracker.cpp
	TransformFilterCallback.cpp
	Sensor.cpp
#	SensorCallback.cpp
	SensorConfiguration.cpp
	SensorData.cpp
	Mapper.cpp
#	MapperpCallback.cpp
	MapperConfiguration.cpp
	MapData.cpp
	Scene.cpp
	Utils.cpp
)


set(OSGART_BINARY_DIR ${CMAKE_BINARY_DIR})
set(OSGART_SOURCE_DIR ${CMAKE_SOURCE_DIR})

configure_file(CoreConfiguration.cmake.hpp
	${CMAKE_BINARY_DIR}/include/osgART/CoreConfiguration
	)

set(lib_hdrs
	${CMAKE_BINARY_DIR}/include/osgART/CoreConfiguration
	${CMAKE_SOURCE_DIR}/include/osgART/Foundation
	${CMAKE_SOURCE_DIR}/include/osgART/Object
	${CMAKE_SOURCE_DIR}/include/osgART/Event
	${CMAKE_SOURCE_DIR}/include/osgART/Field
	${CMAKE_SOURCE_DIR}/include/osgART/Export
	${CMAKE_SOURCE_DIR}/include/osgART/BaseCallback
	${CMAKE_SOURCE_DIR}/include/osgART/PluginManager
	${CMAKE_SOURCE_DIR}/include/osgART/ExportPlugin
	${CMAKE_SOURCE_DIR}/include/osgART/Video
	${CMAKE_SOURCE_DIR}/include/osgART/VideoConfiguration
	${CMAKE_SOURCE_DIR}/include/osgART/VideoCallback	
	${CMAKE_SOURCE_DIR}/include/osgART/VideoStream
#	${CMAKE_SOURCE_DIR}/include/osgART/VideoStreamCallback
	${CMAKE_SOURCE_DIR}/include/osgART/VideoGeode
	${CMAKE_SOURCE_DIR}/include/osgART/VideoPlane
	${CMAKE_SOURCE_DIR}/include/osgART/VideoLayer
	${CMAKE_SOURCE_DIR}/include/osgART/VideoUtils
	${CMAKE_SOURCE_DIR}/include/osgART/Tracker
	${CMAKE_SOURCE_DIR}/include/osgART/TrackerConfiguration
	${CMAKE_SOURCE_DIR}/include/osgART/CameraConfiguration
	${CMAKE_SOURCE_DIR}/include/osgART/TrackerCallback
	${CMAKE_SOURCE_DIR}/include/osgART/TrackerTrainingSupport
	${CMAKE_SOURCE_DIR}/include/osgART/VisualTracker
	${CMAKE_SOURCE_DIR}/include/osgART/GPSInertialTracker	
	${CMAKE_SOURCE_DIR}/include/osgART/Target
	${CMAKE_SOURCE_DIR}/include/osgART/TargetCallback
	${CMAKE_SOURCE_DIR}/include/osgART/TransformFilterCallback
	${CMAKE_SOURCE_DIR}/include/osgART/TrackerUtils	
	${CMAKE_SOURCE_DIR}/include/osgART/Sensor
#	${CMAKE_SOURCE_DIR}/include/osgART/SensorCallback
	${CMAKE_SOURCE_DIR}/include/osgART/SensorConfiguration
	${CMAKE_SOURCE_DIR}/include/osgART/SensorData
	${CMAKE_SOURCE_DIR}/include/osgART/Mapper
#	${CMAKE_SOURCE_DIR}/include/osgART/MapperCallback
	${CMAKE_SOURCE_DIR}/include/osgART/MapperConfiguration
	${CMAKE_SOURCE_DIR}/include/osgART/MapData
	${CMAKE_SOURCE_DIR}/include/osgART/GeometryUtils
	${CMAKE_SOURCE_DIR}/include/osgART/Scene
	${CMAKE_SOURCE_DIR}/include/osgART/Utils
	)



# we are going to build a lib - tell the preprocessor
add_definitions(-DOSGART_LIBRARY)

source_group("Header Files" FILES ${lib_hdrs})

# create a shared library - always
add_library(${lib_name} SHARED ${lib_srcs} ${lib_hdrs})

# additional libs
set(addon_libs)

#message(STATUS "OSG: ${OPENSCENEGRAPH_VERSION}")

if (WIN32)
	# some target properties
	set_target_properties(${lib_name}
		PROPERTIES
#		PREFIX "osg${OSG_VERSION_SO}-"
		IMPORT_PREFIX ""
#		VERSION ${OSGART_VERSION_MAJOR}
#		SOVERSION ${OSG_VERSION_SO}
	)
else(WIN32)
	# some target properties
#	set_target_properties(${lib_name}
#		PROPERTIES
#		VERSION ${OSGART_VERSION_MAJOR}
#		SOVERSION ${OSG_VERSION_SO}
#	)
endif(WIN32)

# some finiky magic around Apple specifics
if   (APPLE)

	if (OSGART_USE_FRAMEWORKS)
		set_target_properties(${lib_name} PROPERTIES
		  FRAMEWORK TRUE
		  FRAMEWORK_VERSION ${OSGART_VERSION_FULL}
		  BUILD_WITH_INSTALL_RPATH 1
		  INSTALL_NAME_DIR "@executable_path/../Frameworks"
		)
	else(OSGART_USE_FRAMEWORKS)
		# do nothing
	endif(OSGART_USE_FRAMEWORKS)
	set(addon_libs ${CARBON_LIBRARY})
endif(APPLE)

# link external libs
target_link_libraries(${lib_name}
	${OPENSCENEGRAPH_LIBRARIES}
        ${OPENGL_LIBRARIES}
	${addon_libs}
	)


set_target_properties(${lib_name}
	PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
	)

set(OSGART_PLUGINS_PREFIX "osgPlugins-${OPENSCENEGRAPH_VERSION}" CACHE STRING "OpenSceneGraph conform plugins folder" FORCE)

set_source_files_properties(${lib_hdrs}
	PROPERTIES
	HEADER_FILE_ONLY TRUE
	)

set(lib_libinstalldir lib)

if(WIN32)
	set(lib_libinstalldir bin)
elif(APPLE)
	set(lib_libinstalldir ${CMAKE_INSTALL_PREFIX}/lib/)	
endif()

install(TARGETS ${lib_name}
 		RUNTIME DESTINATION bin
 		LIBRARY DESTINATION ${lib_libinstalldir}
 		ARCHIVE DESTINATION ${OSGART_LIB_PREFIX}
 		)

install(FILES ${lib_hdrs}
		DESTINATION include/${lib_name}
		)
 

#
# Install share/
#
install(DIRECTORY ${CMAKE_SOURCE_DIR}/share
	DESTINATION ${CMAKE_INSTALL_PREFIX}
	PATTERN ".svn" EXCLUDE
	)

#
# Optional SDK packaging (default is off)
#
if(WIN32)
	option(OSGART_BUILD_SDK "Build as an SDK which will copy all necessary files into the osgART folder (osg)" OFF)
	if(OSGART_BUILD_SDK)
		install(
			DIRECTORY "${OSG_INCLUDE_DIR}/../"
			DESTINATION "."
		)
	endif()
endif()

