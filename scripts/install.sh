#!/bin/bash
# ═══════════════════════════════════════════════
# gazebo_ros_tts_plugin — Install Script
# Dono versions (Classic + Harmonic) setup karta hai
# ═══════════════════════════════════════════════

set -e  # Koi bhi error pe rok jao

BOLD="\e[1m"
GREEN="\e[32m"
YELLOW="\e[33m"
RED="\e[31m"
RESET="\e[0m"

log()  { echo -e "${GREEN}[✓]${RESET} $1"; }
warn() { echo -e "${YELLOW}[!]${RESET} $1"; }
err()  { echo -e "${RED}[✗]${RESET} $1"; exit 1; }

echo -e "${BOLD}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${RESET}"
echo -e "${BOLD}  gazebo_ros_tts_plugin — Installer     ${RESET}"
echo -e "${BOLD}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${RESET}"

# ── TTS Engine install ─────────────────────────
echo ""
echo -e "${BOLD}[Step 1] TTS engines install karo${RESET}"

sudo apt-get update -qq

# espeak (basic, offline)
if ! command -v espeak &>/dev/null; then
  sudo apt-get install -y espeak
  log "espeak installed"
else
  log "espeak already installed"
fi

# festival (better voice)
if ! command -v festival &>/dev/null; then
  sudo apt-get install -y festival festvox-us-slt-hts
  log "festival installed"
else
  log "festival already installed"
fi

# audio playback
sudo apt-get install -y alsa-utils
log "alsa-utils installed"

# piper (optional, best quality)
echo ""
read -p "Piper TTS install karein? (best quality, ~500MB) [y/N]: " install_piper
if [[ "$install_piper" =~ ^[Yy]$ ]]; then
  pip install piper-tts 2>/dev/null || warn "Piper install failed. Manual: pip install piper-tts"
  log "piper-tts installed"
fi

# ── Detect ROS version ─────────────────────────
echo ""
echo -e "${BOLD}[Step 2] ROS version detect karo${RESET}"

if [ -f /opt/ros/humble/setup.bash ]; then
  ROS_VERSION="humble"
  ROS_TYPE="ros2"
  log "ROS2 Humble found"
elif [ -f /opt/ros/noetic/setup.bash ]; then
  ROS_VERSION="noetic"
  ROS_TYPE="ros1"
  log "ROS1 Noetic found"
else
  err "Koi ROS version nahi mila! ROS install karo pehle."
fi

# ── Build ──────────────────────────────────────
echo ""
echo -e "${BOLD}[Step 3] Plugin build karo${RESET}"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PLUGIN_ROOT="$(dirname "$SCRIPT_DIR")"

if [ "$ROS_TYPE" = "ros2" ]; then
  # ── ROS2 Humble + Gazebo Harmonic ─────────
  source /opt/ros/humble/setup.bash

  mkdir -p ~/ros2_ws/src
  cp -r "$PLUGIN_ROOT/harmonic" ~/ros2_ws/src/gz_ros_tts

  cd ~/ros2_ws
  colcon build --packages-select gz_ros_tts --symlink-install
  source ~/ros2_ws/install/setup.bash

  log "Harmonic plugin build complete!"

  echo ""
  echo -e "${BOLD}━━━━ Usage (ROS2 Humble + Gazebo Harmonic) ━━━━${RESET}"
  echo "  source ~/ros2_ws/install/setup.bash"
  echo "  ros2 launch gz_ros_tts demo.launch.py"
  echo ""
  echo "  # Robot ko bolwao:"
  echo "  ros2 topic pub --once /robot/speak std_msgs/msg/String '{data: \"Hello World\"}'"

else
  # ── ROS1 Noetic + Gazebo Classic ──────────
  source /opt/ros/noetic/setup.bash

  mkdir -p ~/catkin_ws/src
  cp -r "$PLUGIN_ROOT/classic" ~/catkin_ws/src/gazebo_ros_tts

  cd ~/catkin_ws
  catkin_make --pkg gazebo_ros_tts
  source ~/catkin_ws/devel/setup.bash

  log "Classic plugin build complete!"

  echo ""
  echo -e "${BOLD}━━━━ Usage (ROS1 Noetic + Gazebo Classic) ━━━━${RESET}"
  echo "  source ~/catkin_ws/devel/setup.bash"
  echo "  roslaunch gazebo_ros_tts demo.launch"
  echo ""
  echo "  # Robot ko bolwao:"
  echo "  rostopic pub -1 /robot/speak std_msgs/String 'data: Hello World'"
fi

echo ""
log "Installation complete! 🤖🔊"
