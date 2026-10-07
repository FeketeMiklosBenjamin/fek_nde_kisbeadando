# `fek_nde_kisbeadando` package
ROS 2 C++ package.  [![Static Badge](https://img.shields.io/badge/ROS_2-Humble-34aec5)](https://docs.ros.org/en/humble/)
## Packages and build

It is assumed that the workspace is `~/ros2_ws/`.

### Clone the packages
``` r
cd ~/ros2_ws/src
```
``` r
git clone https://github.com/FeketeMiklosBenjamin/fek_nde_kisbeadando
```

### Build ROS 2 packages
``` r
cd ~/ros2_ws
```
``` r
colcon build --packages-select fek_nde_kisbeadando --symlink-install
```

<details>
<summary> Don't forget to source before ROS commands.</summary>

``` bash
source ~/ros2_ws/install/setup.bash
```
</details>

``` r
ros2 launch fek_nde_kisbeadando simulation.launch.py
```

## Graph

```mermaid
graph LR
    id1([/traffic_light_node]):::red
    id2(/traffic_light):::light
    id3([/car_node]):::red

    id1 --> id2 --> id3

    classDef light fill:#34aec5,stroke:#152742,stroke-width:2px,color:#152742
    classDef dark fill:#152742,stroke:#34aec5,stroke-width:2px,color:#34aec5
    classDef white fill:#ffffff,stroke:#152742,stroke-width:2px,color:#152742
    classDef red fill:#ef4638,stroke:#152742,stroke-width:2px,color:#fff
```