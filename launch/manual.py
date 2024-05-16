

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
    
    systemLaunch = IncludeLaunchDescription(PathJoinSubstitution([share, "launch", "system.py"]))
    controllerLaunch = IncludeLaunchDescription(PathJoinSubstitution([share, "launch", "controller.py"]))
    
    return LaunchDescription([
        systemLaunch,
        controllerLaunch
    ])
