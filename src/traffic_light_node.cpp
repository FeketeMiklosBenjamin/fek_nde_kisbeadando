#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class TrafficLightNode : public rclcpp::Node
{
public:
    TrafficLightNode()
        : Node("traffic_light_node"), current_state_("RED")
    {
        publisher_ = this->create_publisher<std_msgs::msg::String>(
            "/traffic_light", 10);

        timer_ = this->create_wall_timer(
            5s,
            std::bind(&TrafficLightNode::changeLight, this));

        publishState();
    }

private:
    void changeLight()
    {
        if (current_state_ == "RED")
        {
            current_state_ = "GREEN";
        }
        else
        {
            current_state_ = "RED";
        }

        publishState();
    }

    void publishState()
    {
        std_msgs::msg::String message;
        message.data = current_state_;

        publisher_->publish(message);

        RCLCPP_INFO(
            this->get_logger(),
            "Traffic light: %s",
            current_state_.c_str());
    }

    std::string current_state_;

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<TrafficLightNode>();

    rclcpp::spin(node);

    rclcpp::shutdown();

    return 0;
}