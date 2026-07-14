cmake_minimum_required(VERSION 3.8)
project(gazebo_ros_tts)

# C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

# Compiler warnings
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# -----------------------------
# Dependencies
# -----------------------------
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

find_package(gazebo REQUIRED)
find_package(gazebo_ros REQUIRED)

find_package(Boost REQUIRED COMPONENTS thread)

include_directories(
  include
  ${GAZEBO_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)

link_directories(${GAZEBO_LIBRARY_DIRS})

# -----------------------------
# Plugin Library
# -----------------------------
add_library(${PROJECT_NAME} SHARED
  src/GazeboRosTts.cc
)

ament_target_dependencies(${PROJECT_NAME}
  rclcpp
  std_msgs
  gazebo_ros
)

target_link_libraries(${PROJECT_NAME}
  ${GAZEBO_LIBRARIES}
  ${Boost_LIBRARIES}
)

# -----------------------------
# Install
# -----------------------------
install(
  TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION lib
)

install(
  DIRECTORY include/
  DESTINATION include
)

install(
  DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

install(
  DIRECTORY sounds
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
