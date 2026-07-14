#include "gazebo_ros_tts/GazeboRosTts.hh"

#include <cstdlib>
#include <thread>
#include <functional>

namespace gazebo
{

GZ_REGISTER_MODEL_PLUGIN(GazeboRosTts)


/////////////////////////////////////////////////
GazeboRosTts::GazeboRosTts()
{
}


/////////////////////////////////////////////////
void GazeboRosTts::Load(
    physics::ModelPtr model,
    sdf::ElementPtr sdf)
{
    model_ = model;


    if (!rclcpp::ok())
    {
        rclcpp::init(0, nullptr);
    }


    node_ = rclcpp::Node::make_shared("gazebo_ros_tts");


    // Default parameters
    topic_ = "/robot/speak";
    engine_ = "espeak";
    voice_ = "en";
    rate_ = 150;


    // Read parameters from SDF
    if (sdf->HasElement("topic"))
    {
        topic_ = sdf->Get<std::string>("topic");
    }


    if (sdf->HasElement("tts_engine"))
    {
        engine_ = sdf->Get<std::string>("tts_engine");
    }


    if (sdf->HasElement("voice"))
    {
        voice_ = sdf->Get<std::string>("voice");
    }


    if (sdf->HasElement("rate"))
    {
        rate_ = sdf->Get<int>("rate");
    }



    // ROS2 subscriber
    speak_sub_ =
        node_->create_subscription<std_msgs::msg::String>(
            topic_,
            10,
            std::bind(
                &GazeboRosTts::OnSpeakMsg,
                this,
                std::placeholders::_1
            )
        );



    executor_.add_node(node_);



    executor_thread_ =
        std::thread(
            [this]()
            {
                executor_.spin();
            }
        );



    RCLCPP_INFO(
        node_->get_logger(),
        "Gazebo ROS TTS loaded. Topic: %s",
        topic_.c_str()
    );
}



/////////////////////////////////////////////////
GazeboRosTts::~GazeboRosTts()
{
    executor_.cancel();


    if (executor_thread_.joinable())
    {
        executor_thread_.join();
    }


    if (rclcpp::ok())
    {
        rclcpp::shutdown();
    }
}



/////////////////////////////////////////////////
void GazeboRosTts::OnSpeakMsg(
    const std_msgs::msg::String::SharedPtr msg)
{
    std::thread(
        &GazeboRosTts::Speak,
        this,
        msg->data
    ).detach();
}



/////////////////////////////////////////////////
void GazeboRosTts::Speak(
    const std::string &text)
{

    std::string safe_text = text;


    size_t pos = 0;

    while (
        (pos = safe_text.find('"', pos))
        != std::string::npos
    )
    {
        safe_text.replace(
            pos,
            1,
            "\\\""
        );

        pos += 2;
    }



    std::string cmd;



    if (engine_ == "espeak")
    {

        cmd =
            "espeak -v " +
            voice_ +
            " -s " +
            std::to_string(rate_) +
            " \"" +
            safe_text +
            "\"";

    }


    else if (engine_ == "festival")
    {

        cmd =
            "echo \"" +
            safe_text +
            "\" | festival --tts";

    }


    else if (engine_ == "piper")
    {

        cmd =
            "echo \"" +
            safe_text +
            "\" | piper --model en_US-lessac-medium "
            "--output-raw | "
            "aplay -r 22050 -f S16_LE -t raw -";

    }


    else
    {

        RCLCPP_WARN(
            node_->get_logger(),
            "Unknown TTS engine: %s",
            engine_.c_str()
        );

        return;

    }



    RCLCPP_INFO(
        node_->get_logger(),
        "Speaking: %s",
        text.c_str()
    );


    system(cmd.c_str());

}


} // namespace gazebo
