# Gazebo ROS Text-to-Speech (TTS) Plugin

> **Add natural speech output to your Gazebo robots using ROS 2.**

The **Gazebo ROS Text-to-Speech (TTS) Plugin** enables robots in **Gazebo Classic** to speak messages published from ROS 2 topics using offline Text-to-Speech (TTS) engines such as **eSpeak**, **Festival**, and **Piper**.

Designed for **Human-Robot Interaction (HRI)**, **Vision-Language-Action (VLA)** research, service robots, embodied AI, and educational robotics, this plugin allows developers to simulate complete human-robot conversations before deploying to real hardware.

---

# Why This Plugin?

Recent Vision-Language-Action (VLA) models such as **RT-2 (Google DeepMind)** and **OpenVLA (Stanford)** enable robots to perceive the environment and execute actions directly from visual observations and natural language instructions.

More recently, Vision-Language-Action-Speech (VLAS) systems have extended this capability by incorporating **speech as an input modality**, allowing humans to communicate naturally with robots.

However, one important capability has remained largely missing in simulation:

> **Robot speech output.**

Until now, developers could simulate perception, reasoning, navigation, manipulation, and planning—but not what the robot says back to the user.

This plugin fills that gap.

It gives simulated robots a natural voice, enabling developers to build, test, and demonstrate complete Human-Robot Interaction (HRI) pipelines entirely inside Gazebo before deploying to physical robots.

> **You build the robot intelligence.  
> This plugin gives your robot a voice.**

---

# Features

- ROS 2 native plugin for Gazebo Classic
- Offline Text-to-Speech support (No Internet required)
- Supports multiple TTS engines
  - eSpeak
  - Festival
  - Piper
- Configurable speech rate and voice
- Lightweight and easy to integrate
- Works in simulation and on real robots
- Compatible with Human-Robot Interaction pipelines
- Suitable for Vision-Language-Action (VLA) systems

---

# Architecture

```
                ROS2 Node
                    │
                    ▼
          /robot/speak (String)
                    │
                    ▼
      Gazebo ROS TTS Plugin (.so)
                    │
        ┌───────────┼────────────┐
        ▼           ▼            ▼
     eSpeak      Festival      Piper
                    │
                    ▼
           Robot Speech Output
```

---

# Tested Platforms

| Operating System | ROS 2 | Gazebo | Status |
|------------------|--------|---------|--------|
| Ubuntu 22.04 | Humble | Gazebo Classic | ✅ Tested |
| Ubuntu 22.04 (WSL2) | Humble | Gazebo Classic | ✅ Tested |

---

# Planned Support

| Platform | Status |
|----------|--------|
| Gazebo Harmonic | 🚧 Coming Soon |
| ROS2 Iron | 🚧 Coming Soon |
| ROS2 Jazzy | 🚧 Coming Soon |
| Ubuntu 24.04 | 🚧 Coming Soon |

---

# Requirements

```bash
sudo apt update

sudo apt install ros-humble-gazebo-ros-pkgs
sudo apt install espeak
```

Optional engines:

```bash
sudo apt install festival
```

```bash
pip install piper-tts
```

---

# Installation

Clone the repository into your ROS 2 workspace.

```bash
cd ~/ros2_ws/src

git clone https://github.com/Rahulcva/gazebo_ros_tts_plugin.git
```

Build the package.

```bash
cd ~/ros2_ws

colcon build --symlink-install

source install/setup.bash
```

---

# Quick Start

Launch the demo world.

```bash
ros2 launch tts_demo demo.launch.py
```

Open another terminal.

```bash
source install/setup.bash
```

Publish a speech message.

```bash
ros2 topic pub --once /robot/speak std_msgs/msg/String \
'{data: "Hello. I am ready."}'
```

The robot will immediately speak the published sentence.

---

# Integrating With Your Robot

Add the following plugin block inside your robot's **SDF** model.

```xml
<plugin
    name="gazebo_ros_tts"
    filename="libgazebo_ros_tts.so">

    <topic>/robot/speak</topic>

    <tts_engine>espeak</tts_engine>

    <voice>en</voice>

    <rate>150</rate>

</plugin>
```

---

# Plugin Parameters

| Parameter | Default | Description |
|------------|----------|-------------|
| `topic` | `/robot/speak` | ROS2 topic used for speech messages |
| `tts_engine` | `espeak` | TTS engine |
| `voice` | `en` | Voice or language code |
| `rate` | `150` | Speaking speed (words per minute) |

---

# Supported Languages

| Language | Voice Code |
|-----------|------------|
| English | `en` |
| Hindi | `hi` |
| French | `fr` |
| German | `de` |
| Spanish | `es` |

Additional language packs supported by the selected TTS engine can also be used.

---

# Supported TTS Engines

| Engine | Quality | Offline | Installation |
|---------|----------|----------|--------------|
| eSpeak | Fast | ✅ | `sudo apt install espeak` |
| Festival | Better | ✅ | `sudo apt install festival` |
| Piper | High Quality | ✅ | `pip install piper-tts` |

For most users, **eSpeak** is recommended because it works immediately without additional configuration.

---

# Example Commands

### Greeting

```bash
ros2 topic pub --once /robot/speak std_msgs/msg/String \
'{data: "Hello. I am ready."}'
```

---

### Obstacle Detection

```bash
ros2 topic pub --once /robot/speak std_msgs/msg/String \
'{data: "Obstacle detected. Stopping."}'
```

---

### Battery Warning

```bash
ros2 topic pub --once /robot/speak std_msgs/msg/String \
'{data: "Battery low. Returning to charging station."}'
```

---

### Navigation Complete

```bash
ros2 topic pub --once /robot/speak std_msgs/msg/String \
'{data: "Destination reached successfully."}'
```

---

### Task Completed

```bash
ros2 topic pub --once /robot/speak std_msgs/msg/String \
'{data: "Task completed successfully."}'
```

---

# WSL2 Audio Support

The plugin has been tested successfully on **Windows Subsystem for Linux (WSL2)**.

Since WSL2 does not directly forward Linux audio to Windows speakers, the repository includes a lightweight audio bridge utility.

Simply run the bridge alongside Gazebo and the plugin will function exactly as it does on native Ubuntu.

No workaround is required on native Linux installations or physical robots.

---

# Applications

This plugin can be integrated into:

- Human-Robot Interaction (HRI)
- Vision-Language-Action (VLA) systems
- Embodied AI
- Mobile Manipulators
- Service Robots
- Warehouse Automation
- Educational Robotics
- AI Robot Assistants
- Research Demonstrations
- ROS2 Simulation Projects

---

# Roadmap

- [x] ROS2 Humble Support
- [x] Gazebo Classic Support
- [x] eSpeak Integration
- [x] Festival Integration
- [x] Piper Integration
- [ ] Gazebo Harmonic Support
- [ ] ROS2 Iron Support
- [ ] ROS2 Jazzy Support
- [ ] SSML Support
- [ ] Emotion-based Speech
- [ ] Multi-language Runtime Switching

---

# Authors

- **Aachal Sharma***  
- **Rahul Gupta***

**\*Equal Contribution:** Aachal Sharma and Rahul Gupta contributed equally to the design, implementation, development, testing, and documentation of this project.

---

# Citation

If you use this project in your research, please consider citing it.

```bibtex
@software{gazebo_ros_tts_plugin,
  title  = {Gazebo ROS Text-to-Speech Plugin},
  author = {Aachal Sharma and Rahul Gupta},
  year   = {2026},
  url    = {https://github.com/Rahulcva/gazebo_ros_tts_plugin}
}
```

---

# License

This project is released under the **MIT License**.

---

# Acknowledgements

This project was developed to bridge an important gap in robot simulation by enabling speech output for ROS 2 robots in Gazebo. It aims to support researchers and developers working in Human-Robot Interaction (HRI), Vision-Language-Action (VLA) systems, embodied AI, and intelligent robotic applications.cd gazebo_ros_tts_plugin
chmod +x scripts/install.sh
./scripts/install.sh
```

Script automatically detect karega:
- **ROS2 Humble** → Gazebo Harmonic plugin build hoga
- **ROS1 Noetic** → Gazebo Classic plugin build hoga

---

## Usage

### Gazebo Harmonic + ROS2 Humble

**1. Launch karo:**
```bash
source ~/ros2_ws/install/setup.bash
ros2 launch gz_ros_tts demo.launch.py
```

**2. Robot ko bolwao:**
```bash
# English
ros2 topic pub --once /robot/speak std_msgs/msg/String \
  '{data: "Hello! I am a talking robot!"}'

# Hindi (espeak ke saath)
ros2 topic pub --once /robot/speak std_msgs/msg/String \
  '{data: "Namaste, main robot hoon"}'
```

**3. Python se trigger karo:**
```python
import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class RobotController(Node):
    def __init__(self):
        super().__init__('controller')
        self.pub = self.create_publisher(String, '/robot/speak', 10)

    def say(self, text):
        msg = String()
        msg.data = text
        self.pub.publish(msg)
```

---

### Gazebo Classic + ROS1 Noetic

**1. Launch karo:**
```bash
source ~/catkin_ws/devel/setup.bash
roslaunch gazebo_ros_tts demo.launch
```

**2. Robot ko bolwao:**
```bash
rostopic pub -1 /robot/speak std_msgs/String "data: 'Hello from Gazebo Classic!'"
```

---

## URDF/SDF mein Plugin Add Karo

### Gazebo Classic (URDF mein):
```xml
<robot name="my_robot">
  <!-- ... robot links ... -->

  <gazebo>
    <plugin name="gazebo_ros_tts" filename="libgazebo_ros_tts.so">
      <topic>/robot/speak</topic>
      <tts_engine>espeak</tts_engine>   <!-- espeak | festival | piper -->
      <voice>en</voice>                  <!-- en, hi, fr, de ... -->
      <rate>150</rate>                   <!-- words per minute -->
    </plugin>
  </gazebo>
</robot>
```

### Gazebo Harmonic (SDF mein):
```xml
<model name="my_robot">
  <!-- ... robot links ... -->

  <plugin filename="gz-ros-tts-system"
          name="gz_ros_tts::GzRosTts">
    <topic>/robot/speak</topic>
    <tts_engine>espeak</tts_engine>
    <voice>en</voice>
    <rate>150</rate>
  </plugin>
</model>
```

---

## TTS Engines

| Engine | Quality | Internet | Install |
|--------|---------|----------|---------|
| **espeak** | Basic | ❌ Offline | `sudo apt install espeak` |
| **festival** | Medium | ❌ Offline | `sudo apt install festival` |
| **piper** | ⭐ Best | ❌ Offline | `pip install piper-tts` |

### Hindi mein bolwao (espeak):
```bash
# voice = hi se Hindi milti hai
ros2 topic pub --once /robot/speak std_msgs/msg/String \
  '{data: "नमस्ते, मैं रोबोट हूँ"}'
```

URDF/SDF mein:
```xml
<voice>hi</voice>   <!-- Hindi -->
<voice>en</voice>   <!-- English -->
<voice>fr</voice>   <!-- French -->
```

---

## Real Robot Use Cases

```bash
# Obstacle detect hone pe bolwao
ros2 topic pub --once /robot/speak std_msgs/msg/String \
  '{data: "Raasta band hai, ruk raha hoon"}'

# Battery low hone pe
ros2 topic pub --once /robot/speak std_msgs/msg/String \
  '{data: "Battery low hai, charge karo"}'

# Navigation complete hone pe
ros2 topic pub --once /robot/speak std_msgs/msg/String \
  '{data: "Manzil par pahunch gaya"}'
```

---

## Project Structure

```
gazebo_ros_tts_plugin/
├── classic/                    # Gazebo Classic + ROS1 Noetic
│   ├── include/gazebo_ros_tts/
│   │   └── GazeboRosTts.hh    # Plugin header
│   ├── src/
│   │   └── GazeboRosTts.cc    # Plugin implementation
│   ├── launch/
│   │   └── demo.launch        # Demo launch file
│   ├── CMakeLists.txt
│   └── package.xml
│
├── harmonic/                   # Gazebo Harmonic + ROS2 Humble
│   ├── include/gz_ros_tts/
│   │   └── GzRosTts.hh        # Plugin header
│   ├── src/
│   │   └── GzRosTts.cc        # Plugin implementation
│   ├── launch/
│   │   └── demo.launch.py     # Demo launch file
│   ├── worlds/
│   │   └── tts_demo.sdf       # Demo world with robot
│   ├── CMakeLists.txt
│   └── package.xml
│
├── scripts/
│   └── install.sh             # Auto installer
│
└── README.md
```

---

## Contributing

PR welcome! Ideas:
- [ ] Sound file playback support (WAV/MP3)
- [ ] 3D positional audio (OpenAL)
- [ ] Google Cloud TTS integration
- [ ] Emotion-based voice modulation

---

## License

Apache-2.0 — Free to use, modify, distribute.

---
# Demo

<p align="center">
  <a href="https://youtu.be/fZDQTZH6RKk?si=5kX5JXs28x1v6Fax">
    <img src="https://img.youtube.com/vi/fZDQTZH6RKk/maxresdefault.jpg" width="900" alt="Gazebo ROS TTS Plugin Demo"/>
  </a>
</p>

<p align="center">
  <b>🎥 Click the image above to watch the demo video.</b>
</p>

---

---

**Made by - Aachal & Rahul!**
