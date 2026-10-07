#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

using namespace std::chrono_literals;

class TrafficLightNode : public rclcpp::Node
{
public:
    TrafficLightNode()
        : Node("traffic_light_node"), current_state_id_(0)
    {
        publisher_ = this->create_publisher<std_msgs::msg::Int32>(
            "/traffic_light", 10);

        state_time_ = 0;
        timer_ = this->create_wall_timer(
            2s,
            std::bind(&TrafficLightNode::changeLight, this));

        publishState();
    }

private:
    void changeLight()
    {
        if (state_time_ == GREEN_DURATION_ && current_state_id_ == 0)
        {
            current_state_id_ = 1;
            state_time_ = 0;
        }
        else if (state_time_ == YELLOW_DURATION_ && current_state_id_ == 1)
        {
            current_state_id_ = 2;
            state_time_ = 0;
        }
        else if (state_time_ == RED_DURATION_ && current_state_id_ == 2)
        {
            current_state_id_ = 3;
            state_time_ = 0;
        }
        else if (state_time_ == YELLOW_DURATION_ && current_state_id_ == 3)
        {
            current_state_id_ = 0;
            state_time_ = 0;
        }

        state_time_++;

        publishState();
    }

    void publishState()
    {
        std_msgs::msg::Int32 message;
        message.data = current_state_id_;
        std::string state_str;
        // state_str = (current_state_id_ == 0) ? "GREEN" : (current_state_id_ == 2) ? "RED" : "YELLOW";

        publisher_->publish(message);

        // RCLCPP_INFO(
        //     this->get_logger(),
        //     "Traffic light: %s",
        //     state_str.c_str());
    }
    int current_state_id_; // 0: GREEN, 1: GREEN-YELLOW, 2: RED, 3: RED-YELLOW
    static constexpr int RED_DURATION_ = 4;
    static constexpr int YELLOW_DURATION_ = 2;
    static constexpr int GREEN_DURATION_ = 8;
    int state_time_;

    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;
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