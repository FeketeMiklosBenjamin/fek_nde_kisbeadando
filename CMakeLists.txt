cmake_minimum_required(VERSION 3.8)
project(fek_nde_kisbeadando)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

set(ament_dependencies
  rclcpp
  std_msgs
)

add_executable(traffic_light_node src/traffic_light_node.cpp)
ament_target_dependencies(traffic_light_node ${ament_dependencies})

add_executable(car_node src/car_node.cpp)
ament_target_dependencies(car_node ${ament_dependencies})

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

install(TARGETS
  traffic_light_node
  car_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()