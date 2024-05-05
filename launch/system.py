

# launch file common to both deployment and testing environment


from launch_ros.substitutions import FindPackageShare
from launch import LaunchDescription
from launch.actions import *
from launch_ros.actions import *
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import PathJoinSubstitution, Command
from launch_ros.parameter_descriptions import ParameterValue
from launch.actions import TimerAction




def generate_launch_description():
    
    share = FindPackageShare("tarm_hwi")
    tarmShare = FindPackageShare("tarm")


    urdfPath = PathJoinSubstitution([share, "descriptions", "tarm.urdf.xacro"])
    
    # robot state publisher
    robot_state_pub = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        parameters=[{
            'robot_description': ParameterValue(Command(['xacro ', urdfPath]), value_type=str)
    }]
    )
    
    # start joint state broadcaster controller
    joint_state_broad = Node(
        package="controller_manager",
        executable="spawner",
        arguments=[
            "joint_state_broadcaster",
        ]
    )
    
    joint_traject = Node(
        package="controller_manager",
        executable="spawner",
        arguments=[
            "joint_traject",
        ]
    )
    
    # run control manager with its parameters
    robot_controller_param = PathJoinSubstitution([tarmShare ,"config", "tarm_controller.yaml"])

    cm = Node(
        package="controller_manager",
        executable="ros2_control_node",
        parameters=[robot_controller_param],
        output="both",
        remappings=[
            ("~/robot_description", "/robot_description"),
        ],
    )
    
    
    return LaunchDescription([
        robot_state_pub,
        cm,
        joint_state_broad,
        joint_traject,
    ]
    )