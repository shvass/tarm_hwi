

#include "tarm_hwi.hpp"

#include "hardware_interface/types/hardware_interface_type_values.hpp"
#include "rclcpp/rclcpp.hpp"
#include "pluginlib/class_list_macros.hpp"

tarm::tarm_hwi::tarm_hwi() : Node(NODE_NAME){};

hardware_interface::CallbackReturn tarm::tarm_hwi::on_init(const hardware_interface::HardwareInfo &info)
{

    if (hardware_interface::SystemInterface::on_init(info) != CallbackReturn::SUCCESS)
    {
        return CallbackReturn::ERROR;
    }

    // robot has 6 joints and 2 interfaces
    joint_position_.assign(6, 0);
    joint_velocities_.assign(6, 0);
    joint_position_command_.assign(6, 0);
    joint_velocities_command_.assign(6, 0);

    for (const auto & joint : info_.joints)
    {
        for (const auto & interface : joint.state_interfaces)
        {
        joint_interfaces[interface.name].push_back(joint.name);
        }
    }

    return CallbackReturn::SUCCESS;
    rclcpp::Logger log = rclcpp::get_logger("tarm_hwi");

    RCLCPP_INFO(log, "hardware interface initialized");
    return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::CallbackReturn tarm::tarm_hwi::on_configure(const rclcpp_lifecycle::State &previous_state)
{
    publisher_ = this->create_publisher<sensor_msgs::msg::Imu>(TOPIC_NAME, 10);

    return hardware_interface::CallbackReturn::SUCCESS;
}

std::vector<hardware_interface::StateInterface> tarm::tarm_hwi::export_state_interfaces()
{   
    std::vector<hardware_interface::StateInterface> state_interfaces;

    int ind = 0;
    for (const auto & joint_name : joint_interfaces["position"])
    {
    state_interfaces.emplace_back(joint_name, "position", &joint_position_[ind++]);
    }

    ind = 0;
    for (const auto & joint_name : joint_interfaces["velocity"])
    {
    state_interfaces.emplace_back(joint_name, "velocity", &joint_velocities_[ind++]);
    }

    return state_interfaces;
}

std::vector<hardware_interface::CommandInterface> tarm::tarm_hwi::export_command_interfaces()
{
    std::vector<hardware_interface::CommandInterface> command_interfaces;

    int ind = 0;
    for (const auto & joint_name : joint_interfaces["position"])
    {
        command_interfaces.emplace_back(joint_name, "position", &joint_position_command_[ind++]);
    }

    ind = 0;
    for (const auto & joint_name : joint_interfaces["velocity"])
    {
        command_interfaces.emplace_back(joint_name, "velocity", &joint_velocities_command_[ind++]);
    }

    return command_interfaces;
}

hardware_interface::CallbackReturn tarm::tarm_hwi::on_activate(const rclcpp_lifecycle::State &previous_state)
{
    return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::CallbackReturn tarm::tarm_hwi::on_deactivate(const rclcpp_lifecycle::State &previous_state)
{
    return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::return_type tarm::tarm_hwi::read(const rclcpp::Time &time, const rclcpp::Duration &period)
{
    // rclcpp::Logger log = rclcpp::get_logger("tarm_hw");    
    // RCLCPP_INFO(log, "read called");
    return hardware_interface::return_type::OK;
}

hardware_interface::return_type tarm::tarm_hwi::write(const rclcpp::Time &time, const rclcpp::Duration &period)
{   
    auto message = sensor_msgs::msg::Imu();

    // auto& arr = message.angular_velocity_covariance;

    auto& arr = message.angular_velocity_covariance;

    for(int i = 0; i <=5; i++) joint_position_[i] = arr[i] = joint_position_command_[i];

    publisher_.get()->publish(message);

    rclcpp::Logger log = rclcpp::get_logger("tarm_hw");    
    
    RCLCPP_INFO(log, "got commands %f %f %f %f %f %f", 
        joint_position_command_[0],
        joint_position_command_[1],
        joint_position_command_[2],
        joint_position_command_[3],
        joint_position_command_[4],
        joint_position_command_[5]
    );


    // RCLCPP_INFO(log, "write called");
    return hardware_interface::return_type::OK;
}

PLUGINLIB_EXPORT_CLASS(tarm::tarm_hwi, hardware_interface::SystemInterface)
