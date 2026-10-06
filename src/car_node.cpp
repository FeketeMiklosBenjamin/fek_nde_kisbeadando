#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int32.hpp"

using namespace std::chrono_literals;

class CarNode : public rclcpp::Node
{
public:
    CarNode()
        : Node("car_node"),
          traffic_light_state_("GREEN"),
          traffic_light_id_(0),
          position_(0.0),
          speed_(10.0),
          distance_to_light_(traffic_lights_distance_),
          car_state_("HALAD")
    {
        subscriber_ = this->create_subscription<std_msgs::msg::Int32>(
            "/traffic_light",
            10,
            std::bind(&CarNode::trafficLightCallback, this, std::placeholders::_1));

        timer_ = this->create_wall_timer(
            2s,
            std::bind(&CarNode::updateCar, this));
    }

private:
    void trafficLightCallback(const std_msgs::msg::Int32::SharedPtr message)
    {
        traffic_light_id_ = message->data;
        traffic_light_state_ = (traffic_light_id_ == 0) ? "GREEN" : (traffic_light_id_ == 2) ? "RED" : "YELLOW";

        // RCLCPP_INFO(
        //     this->get_logger(),
        //     "Traffic light: %s",
        //     traffic_light_state.c_str());
    }

    void updateCar()
    {
        distance_to_light_ = traffic_lights_distance_ - position_;
        
        if (distance_to_light_ == 0.0 && traffic_light_id_ == 2){
            speed_ = 0.0;
            car_state_ = "MEGÁLL";
            position_ = 0.0;
        }
        else if(distance_to_light_ == 0.0 && traffic_light_id_ != 2) {
            speed_ = speed_ + 5.0;
            car_state_ = "GYORSÍT";
            position_ = 0.0;
        }
        else if (speed_ * 2.0 > distance_to_light_){
            if(speed_ != 0.0){
                speed_ = speed_ - 5.0;
            }
            car_state_ = "LASSÍT";
        }
        else if (speed_ == max_speed_){
            car_state_ = "HALAD";
        }
        else if (speed_ < max_speed_){
            speed_ = speed_ + 5.0;
            car_state_ = "GYORSÍT";
        }
        
        RCLCPP_INFO(
            this->get_logger(),
            "State: %s | Speed: %.1f m/s | Distance left to next light: %.1f m | Light: %s",
            car_state_.c_str(),
            speed_,
            distance_to_light_,
            traffic_light_state_.c_str());
        
        position_ += 10.0;
        distance_to_light_ = traffic_lights_distance_ - position_;
    }

    static constexpr double traffic_lights_distance_ = 100.0; // A lámpák közötti távolság m-ben
    static constexpr double max_speed_ = 20.0; // Az autó maximális sebessége m/s-ban
    std::string traffic_light_state_;
    int traffic_light_id_; // 0: GREEN, 1: GREEN-YELLOW, 2: RED, 3: RED-YELLOW
    double position_; // Az autó megtett uta (pozíciója) az utolsó lámpától mérve
    double speed_; // Az autó sebessége m/s-ban
    double distance_to_light_; // Az autó és a következő lámpa távolsága
    std::string car_state_; // HALAD, LASSÍT, MEGÁLL, GYORSÍT

    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscriber_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<CarNode>();

    rclcpp::spin(node);

    rclcpp::shutdown();

    return 0;
}