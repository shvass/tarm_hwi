

from launch_ros.substitutions import FindPackageShare
from launch import LaunchDescription
from launch.actions import *
from launch_ros.actions import *
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import PathJoinSubstitution, Command
from launch_ros.parameter_descriptions import ParameterValue
from launch.actions import TimerAction




def generate_launch_description():
    
    share = FindPackageShare(package="tarm_hwi")
    
    system = IncludeLaunchDescription(PathJoinSubstitution([share, "launch", "system.py"]))
    
    
        
    rqt_gui = Node(
        package="rqt_joint_trajectory_controller",
        executable="rqt_joint_trajectory_controller"
    )
    
    rviz = Node(
        package="rviz2",
        executable="rviz2",
        arguments=["-d", PathJoinSubstitution([share, "config", "config.rviz"])]
    )
    
    return LaunchDescription([
        system,
        rqt_gui,
        rviz
    ])
    