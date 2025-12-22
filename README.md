# Foundational AI & Robotics Curriculum

![banner](https://github.com/user-attachments/assets/4a51153a-68d3-4b67-9416-397c375b4d02)

![ROS 2](https://img.shields.io/badge/ROS2-Humble%20%7C%20Jazzy-22314E?style=for-the-badge&logo=ros&logoColor=white)
![Gazebo](https://img.shields.io/badge/Gazebo-Harmonic-FF6D00?style=for-the-badge&logo=gazebo&logoColor=white)
![FreeRTOS](https://img.shields.io/badge/FreeRTOS-RealTime-blue?style=for-the-badge&logo=freertos&logoColor=white)
![PyTorch](https://img.shields.io/badge/PyTorch-2.0+-EE4C2C?style=for-the-badge&logo=pytorch&logoColor=white)

> *"A brain without a body is a hallucination."*

Welcome! This repository is an open-source engineering log designed to teach the full stack of **Industrial AI**: from the mathematical foundations of Machine Learning to the deployment of intelligent agents on physical robots.

My mission is to bridge the gap between pure ML theory (inspired by *Aurélien Géron*) and practical robotics control (inspired by *Peter Corke*).

---

## 📚 Pillar 1: Machine Learning Foundations ("The Brain")

Before we can build intelligent robots, we must master the algorithms that drive them. These modules focus on the mathematical and theoretical underpinnings of AI.

| # | Topic | 🔗 Notebook & Cheatsheet | 🔗 Original LinkedIn Post |
| :--- | :--- | :--- | :--- |
| **01** | **The ML Project Roadmap: Regression** | [`1-Machine-learning/01-ML-Cheatsheet-Roadmap-Regression/`](./1-Machine-learning/01-ML-Cheatsheet-Roadmap-Regression/) | [`View linkedIn post`](https://www.linkedin.com/posts/christiantsoungui_ml-cheat-sheet-1-activity-7398373282556571648-KqYl?utm_source=share&utm_medium=member_desktop&rcm=ACoAACIGZ5gBH4kEhyxvC7B6oPUFpa6SuDySW00) |
| **02** | **The ML Project Roadmap: Classification** | [`/1-Machine-Learning/02-ML-Cheatsheet-Roadmap-Classification/`](./1-Machine-Learning/02-ML-Cheatsheet-Roadmap-Classification/) | [`View linkedIn post`](https://www.linkedin.com/posts/christiantsoungui_cheat-sheet-ml-roadmap-classification-activity-7403025733821935616-bhq-?utm_source=social_share_send&utm_medium=member_desktop_web&rcm=ACoAACIGZ5gBH4kEhyxvC7B6oPUFpa6SuDySW00) | 
| **03** | **Deep Dive: Mastering Linear Regression** | [`/1-Machine-Learning/03-ML-Cheatsheet-DeepDive-MasteringRegression/`](./1-Machine-Learning/03-ML-Cheatsheet-DeepDive-MasteringRegression/) | `(Coming Soon)` |

---

## 🤖 Pillar 2: The AYILI Robotics Project ("The Body")

This section documents the **Sim-to-Real** engineering process of building the **AYILI Mark 1**—an Industrial AI mobile robot.

We apply the theory from Pillar 1 to real-world hardware. For example, *Linear Regression* (ML Module 03) is used here to calibrate the robot's motor controllers.

### The Hardware Platform: AYILI Mark 1
*   **Design Philosophy:** **DfAM (Design for Additive Manufacturing).** A 3D-printed Monocoque (Unibody) chassis with internal structural ribbing, mimicking industrial AGVs.
*   **Embedded Architecture:** **FreeRTOS on ESP32.** We reject the standard Arduino loop in favor of real-time multitasking (Core 1 for Control, Core 0 for Comms).
*   **Core Specs:** Raspberry Pi 5, 12V DC Gearmotors (Hall Encoders), Lidar, and 3S Li-Ion Power.

### The Engineering Roadmap
The curriculum follows a "Seasons" format, moving from basic control to advanced autonomy.

#### Season 1: The Mobile Base
*Goal: Build a robot that moves precisely and perceives its environment.*

| # | Phase | The Engineering Challenge | Tech Stack |
| :--- | :--- | :--- | :--- |
| **04** | **Mechatronics** | **Design for AI.** Designing the Monocoque chassis in Fusion 360 and managing the Power Budget. | *Fusion 360, FDM Printing* |
| **05** | **Control** | **Hardware Calibration.** Using Linear Regression to map PWM signals to RPM. Implementing the PID loop in **FreeRTOS**. | *C++, ESP32, Micro-ROS* |
| **06** | **Perception** | **The Safety Stop.** Training a CNN on the Edge to classify "Floor" vs. "Obstacle" in real-time. | *PyTorch, TensorFlow Lite* |
| **07** | **Vision** | **Object Tracking.** Implementing Visual Servoing (PID) to track dynamic objects with YOLOv8. | *YOLO, OpenCV* |
| **08** | **Kinematics** | **State Estimation.** Using RNNs (Recurrent Neural Networks) to correct odometry drift. | *ROS 2 TF2, RNNs* |
| **09** | **Intelligence** | **Voice Control (VLA).** A Vision-Language-Action pipeline using local LLMs to parse voice commands. | *Llama 3, Whisper* |
| **10** | **Autonomy** | **Sim-to-Real (RL).** Training a PPO Agent in Gazebo to navigate complex spaces without a map. | *Gazebo, Stable Baselines3* |

---

## 🛠️ How to Use This Repository

### Prerequisites
-   **For ML (Pillar 1):** Python 3.8+, Jupyter Notebook.
-   **For Robotics (Pillar 2):** Ubuntu 22.04/24.04, ROS 2 (Humble/Jazzy), Gazebo Harmonic.

### Installation

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/christianTsounguiObama/Foundational-AI-Robotics-Curriculum.git
    cd Foundational-AI-Robotics-Curriculum
    ```

2.  **Navigate to a project folder:**
    Each numbered folder is a self-contained project.
    ```bash
    cd 1-Machine-learning/01-ML-Cheatsheet-Roadmap-Regression
    ```

3.  **Set up the Environment:**
    *   *For ML Projects:* Create a standard Python venv and install `requirements.txt`.
    *   *For Robotics Projects:* Source your ROS 2 workspace (detailed instructions provided inside each robotics folder).

---

## 👨‍💻 About the Author

My name is **Dr. Christian Tsoungui Obama**. I am an **Industrial AI Engineer** with a background in mathematical modeling and electromechanical engineering.

I am passionate about empowering the next generation of engineers—especially within the African tech ecosystem—by making complex, industrial-grade concepts accessible and practical.

## 🤝 Let's Connect

If you find this content valuable, let's connect!

-   **LinkedIn:** [linkedin.com/in/christiantsoungui](https://www.linkedin.com/in/christiantsoungui/)
-   **Twitter:** [@TsounguiChris](https://twitter.com/TsounguiChris)

If you support this mission, please give the repo a ⭐!

## 📄 License

The work presented in this repository is for educational purposes. The code is released under the [Apache 2.0 License](LICENSE).
