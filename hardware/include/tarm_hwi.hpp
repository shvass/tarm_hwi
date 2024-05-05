

#ifndef TARM_HWI_HPP
#define TARM_HWI_HPP

#include <hardware_interface/system_interface.hpp>
#include "visibility_control.h"

#include <memory>
#include <string>
#include <vector>

#include "hardware_interface/handle.hpp"
#include "hardware_interface/hardware_info.hpp"
#include "hardware_interface/system_interface.hpp"
#include "hardware_interface/types/hardware_interface_return_values.hpp"
#include "rclcpp/macros.hpp"
#include "rclcpp_lifecycle/node_interfaces/lifecycle_node_interface.hpp"
#include "rclcpp_lifecycle/state.hpp"

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/imu.hpp>

#define NODE_NAME "tarm_control"
#define TOPIC_NAME "command"

namespace tarm
{

class tarm_hwi : public hardware_interface::SystemInterface, public rclcpp::Node
{
    public:

    TARM_PUBLIC tarm_hwi();


    TARM_PUBLIC
    hardware_interface::CallbackReturn on_init(
        const hardware_interface::HardwareInfo & info) override;

    TARM_PUBLIC
    hardware_interface::CallbackReturn on_configure(
        const rclcpp_lifecycle::State & previous_state) override;

    TARM_PUBLIC
    std::vector<hardware_interface::StateInterface> export_state_interfaces() override;

    TARM_PUBLIC
    std::vector<hardware_interface::CommandInterface> export_command_interfaces() override;

    TARM_PUBLIC
    hardware_interface::CallbackReturn on_activate(
        const rclcpp_lifecycle::State & previous_state) override;

    TARM_PUBLIC
    hardware_interface::CallbackReturn on_deactivate(
        const rclcpp_lifecycle::State & previous_state) override;

    TARM_PUBLIC
    hardware_interface::return_type read(
        const rclcpp::Time & time, const rclcpp::Duration & period) override;

    TARM_PUBLIC
    hardware_interface::return_type write(
        const rclcpp::Time & time, const rclcpp::Duration & period) override;


    public:

    rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr publisher_;

    std::vector<double> joint_position_command_;
    std::vector<double> joint_velocities_command_;
    std::vector<double> joint_position_;
    std::vector<double> joint_velocities_;

    std::unordered_map<std::string, std::vector<std::string>> joint_interfaces = {
        {"position", {}}, {"velocity", {}}};
    };

};




#endif //  TARM_HWI_HPP
