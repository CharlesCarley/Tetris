# Tetris

A Tetris clone written with OpenGL and C++.

![SS01](Resources/Main01.png)
![SS02](Resources/Main02.png)
![SS02](Resources/Main03.png)



## Controls

| Key              | Description                                      |
|:-----------------|:-------------------------------------------------|
| Enter            | Accept/Next state                                |
| Escape/Backspace | Back/Previous state                              |
| Q                | Resets the board.                                |
| R                | Swaps the current with next piece. (Score - 200) |
| Space            | Rotates the current piece.                       |
| Left             | Moves left                                       |
| Right            | Moves right                                      |
| Up               | Moves up, but subtracts one from  the score.     |
| Down             | Drops the current piece.                         |
| Number pad (-)   | Increments the level.                            |

## Online Version

The online version can be found [here](https://CharlesCarley.github.io/Tetris/index.html).

## Sub-modules

The files [gitupdate.py](gitupdate.py) or [gitupdate.bat](gitupdate.bat) help automate initial cloning and with keeping the modules up to date.

Once this project has been cloned. The following command will initialize external modules.

```txt
python gitupdate.py 
...
gitupdate.bat 
```

_*Sub-modules in this project*_

| Name                                                      | Description                                              |
|-----------------------------------------------------------|----------------------------------------------------------|
| [Utils](https://github.com/CharlesCarley/Utils)           | Provides common all around functionality.                |
| [Math](https://github.com/CharlesCarley/Math)             | Math support.                                            |
| [Window](https://github.com/CharlesCarley/Window)         | Window support.                                          |
| [Image](https://github.com/CharlesCarley/Image)           | Image I/O.                                               |
| [Graphics](https://github.com/CharlesCarley/Graphics)     | 2D Rendering context.                                    |
| [Thread](https://github.com/CharlesCarley/Threads)        | Thread support.                                          |
| [Json](https://github.com/CharlesCarley/Json)             | Json  support.                                           |
| [FreeImage](https://github.com/CharlesCarley/FreeImage)   | Support library for Image.                               |
| [FreeType](https://github.com/CharlesCarley/FreeType)     | Support library for font I/O.                            |
| [SDL](https://github.com/CharlesCarley/SDL)               | Optional Backend for the window library.                 |
| [Data2Array](https://github.com/CharlesCarley/Data2Array) | Compile time tool to pack resources into the executable. |

## Building

Building with CMake and Make

```sh
mkdir build
cd build
cmake ..

make
```

Optional defines.

| Option                     | Description                                                    | Default |
|:---------------------------|:---------------------------------------------------------------|:-------:|
| Tetris_COPY_BIN            | Copy binary to the bin directory.                              |   ON    |
| Tetris_BACKEND_OPENGL      | Build the OpenGL backend.                                      |   ON    |
| Tetris_USE_SDL             | Build with SDL.                                                |   OFF   |
| Tetris_NO_PALETTE          | Disable builtin palette.                                       |   ON    |
| Tetris_OP_CHECKS           | Extra checks on function parameters                            |   ON    |
| Tetris_EXTRA_BUILTIN_FONTS | Include extra [fonts](https://fonts.google.com/) in the build. |   OFF   |

## References

The initial starter tutorial that was used can be found [here](https://javilop.com/gamedev/tetris-tutorial-in-c-platform-independent-focused-in-game-logic-for-beginners/)
