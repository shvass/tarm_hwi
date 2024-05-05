
CMAKE_MINIMUM_REQUIRED(VERSION 3.8)

project(tarm_hwi)

set(DEPENDENCIES
    hardware_interface
    rclcpp
    pluginlib
    rclcpp_lifecycle
)

# dependencies
find_package(ament_cmake REQUIRED)

foreach(Dependency IN ITEMS ${DEPENDENCIES})
  find_package(${Dependency} REQUIRED)
endforeach()


add_library(
    tarm_hwi
    SHARED
    hardware/hwi.cpp
)


target_compile_features(tarm_hwi PUBLIC cxx_std_17)
target_include_directories(tarm_hwi PUBLIC
$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/hardware/include>
$<INSTALL_INTERFACE:include/tarm_hwi>
)

ament_target_dependencies(tarm_hwi PUBLIC ament_cmake ${DEPENDENCIES})


# Export hardware plugins
pluginlib_export_plugin_description_file(hardware_interface tarm_hwi.xml)


install( DIRECTORY
    launch
    descriptions
    config

    DESTINATION share/${PROJECT_NAME}
)

install(TARGETS tarm_hwi
  EXPORT tarm_hwi
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)


ament_package()