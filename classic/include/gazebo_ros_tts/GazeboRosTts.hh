#ifndef GAZEBO_ROS_TTS_HH
#define GAZEBO_ROS_TTS_HH

#include <gazebo/common/Plugin.hh>
#include <gazebo/physics/physics.hh>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

#include <thread>
#include <memory>
#include <string>

namespace gazebo
{

class GazeboRosTts : public ModelPlugin
{
public:
  GazeboRosTts();
  virtual ~GazeboRosTts();

  void Load(physics::ModelPtr model, sdf::ElementPtr sdf) override;

private:

  /// ROS2 callback
  void OnSpeakMsg(const std_msgs::msg::String::SharedPtr msg);

  /// Execute TTS
  void Speak(const std::string &text);

  /// ROS2 node
  rclcpp::Node::SharedPtr node_;

  /// ROS2 subscription
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr speak_sub_;

  /// ROS2 executor
  rclcpp::executors::SingleThreadedExecutor executor_;

  /// Executor thread
  std::thread executor_thread_;

  /// Gazebo model
  physics::ModelPtr model_;

  /// Parameters
  std::string topic_  = "/robot/speak";
  std::string engine_ = "espeak";
  std::string voice_  = "en";
  int rate_ = 150;
};

}

#endif
