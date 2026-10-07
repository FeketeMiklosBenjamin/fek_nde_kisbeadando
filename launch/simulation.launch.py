from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='fek_nde_kisbeadando',
            executable='traffic_light_node',
            name='traffic_light_node',
        ),
        Node(
            package='fek_nde_kisbeadando',
            executable='car_node',
            name='car_node',
            output='screen'
        ),
        

    ])