# 🤖🔊 gazebo_ros_tts_plugin

> **Gazebo mein robot ko bolwao!**  
> ROS topic pe text bhejo — robot speaker se bolta hai.

---

## Kya Hai Yeh?

Yeh world ka **pehla dedicated Gazebo TTS plugin** hai.  
Pehle search kiya — koi nahi tha, toh banaya! 🚀

| Feature | Detail |
|---------|--------|
| **Gazebo Classic** | ROS1 Noetic support |
| **Gazebo Harmonic** | ROS2 Humble support |
| **TTS Engines** | espeak, festival, piper |
| **Interface** | Simple ROS topic `/robot/speak` |
| **Language** | Hindi + English + 100+ languages (espeak) |

---

## Quick Start

### Install

```bash
git clone https://github.com/yourusername/gazebo_ros_tts_plugin
cd gazebo_ros_tts_plugin
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

**Made with ❤️ — Kyunki koi aur nahi tha jo banata!**
