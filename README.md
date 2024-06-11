# Doodle Game recreated

![](https://github.com/klikklik/doodle_game/blob/main/doodlegif.gif)

to hop on and play just
 `git clone https://github.com/klikklik/doodle_game_exe.git`


## Manual build steps using cmake


##### Must Have (dependencies)
- C++ compiler
- cmake
- mingw added to PATH

  
#### Building
- `git clone https://github.com/klikklik/doodle_game.git`
- Create a directory for cmake , e.g. - `mkdir build`
- `cd build`
- `cmake .. -G Ninja` or `cmake ..` (to use the default build system)
- `ninja sfmlgame` or `make sfmlgame` (depending on your selected build system)
  
