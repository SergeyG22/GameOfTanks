### GameOfTanks

The program is a simulator of tank battles. It is possible to expand and modify various weapons (in this example, only the groundwork is implemented).

[![CI - Windows](https://github.com/SergeyG22/WorldOfTanks/actions/workflows/windows_builds.yml/badge.svg)](https://github.com/SergeyG22/WorldOfTanks/actions/workflows/windows_builds.yml)<br>
[![CI - linux](https://github.com/SergeyG22/WorldOfTanks/actions/workflows/linux_builds.yml/badge.svg)](https://github.com/SergeyG22/WorldOfTanks/actions/workflows/linux_builds.yml)<br>
[![CI - macOS](https://github.com/SergeyG22/WorldOfTanks/actions/workflows/macos_builds.yml/badge.svg)](https://github.com/SergeyG22/WorldOfTanks/actions/workflows/macos_builds.yml)<br>


### Build from source
CMake 3.13 or higher must be installed
```
git clone https://github.com/SergeyG22/GameOfTanks.git
cd GameOfTanks
mkdir build
cd build
cmake ..
```

### Keyboard control

```
 W - move up
 S - move down
 A - move left
 D - move right
 SPACE - make a shot
```

### How to add resources to an executable file

```
Copy the resources folder at the root of the project directory.
Paste it one directory higher from the executable file.
```

### If Linux requires a dependency type in cmd:

```
sudo apt-get install build-essential pkg-config libx11-dev libxcursor-dev libxinerama-dev libgl1-mesa-dev libglu-dev libasound2-dev libpulse-dev libdbus-1-dev libudev-dev libxi-dev libxrandr-dev yasm xvfb wget unzip libopenal-dev libvorbis-dev libflac-dev
```

### Preview

![hippo](https://github.com/SergeyG22/GameOfTanks/blob/master/docs/images/animation.gif)

