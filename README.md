# GraphicsTemplate

A sub-module template repository.

Its purpose is to define the initial project structure for sub-modules. A sub-module should be able to stand on its own, or included in larger projects as a component piece.

If the module itself requires extra dependencies then they should be included into the module as sub-modules. The `${PROJECT}_ExternalTarget` variable is used to determine whether or not to compile dependencies locally or have them resolved later in the larger project.

if `${PROJECT}_ExternalTarget` is false then the module should be built as a standalone project.

Dependencies should adhere to the same naming strategy to keep everything consistent. Sub-modules should define the same include and library variables relative to the `${PROJECT}_ExternalTarget` variable.

For example:

```cmake
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

## CMakeLists.txt - in larger project


set(Utils_ExternalTarget  TRUE)
set(Utils_TargetName      UtilsAlias)
set(Utils_TargetGroup     VisualStudioFolderName)
set(Utils_INCLUDE         some/path/to/utils/module)
set(Utils_LIBRARY         ${Utils_TargetName})
subdirs(Utils)

## CMakeLists.txt - In Utils


if (Utils_ExternalTarget)
    # Copy of the larger project's settings

    set(TargetFolders ${Utils_TargetFolders})
    set(TargetName    ${Utils_TargetName})
    set(TargetGroup   ${Utils_TargetGroup})
else()
    # Settings for the standalone project

    set(TargetFolders FALSE)
    set(TargetName    Utils)
    set(Utils_INCLUDE internal/path/to/utils/module)
    set(Utils_LIBRARY ${TargetName})
endif()


## When building the library 

add_library(${TargetName} ... )
if (TargetFolders)
    set_target_properties(
        ${TargetName} 
        PROPERTIES FOLDER "${TargetGroup}"
    )
endif()


## When linking against the module

include_directories(${Utils_INCLUDE})

add_executable(HelloWorld main.cpp)

target_link_libraries(HelloWorld  ${Utils_LIBRARY})
```

## Sub-modules

The files [gitupdate.py](gitupdate.py) or [gitupdate.bat](gitupdate.bat) help automate initial cloning and with keeping the modules up to date.

Once this project has been cloned. The following command will initialize external modules.

```txt
python gitupdate.py 
...
gitupdate.bat 
```

**Sub-modules in this template**

| Name       | Description                                              |
|------------|----------------------------------------------------------|
| Utils      | Provides common all around functionality.                |
| Math       | Math support.                                            |
| Window     | Window support.                                          |
| Image      | Image I/O.                                               |
| Graphics   | 2D Rendering context.                                    |
| FreeImage  | Support library for Image.                               |
| FreeType   | Support library for font I/O.                            |
| SDL        | Optional Backend for the window library.                 |
| Data2Array | Compile time tool to pack resources into the executable. |

## Building

Building with CMake and Make

```sh
mkdir build
cd build
cmake ..

make
```

Optional defines.

| Option                               | Description                                                    | Default |
|:-------------------------------------|:---------------------------------------------------------------|:-------:|
| GraphicsTemplate_COPY_BIN            | Copy binary to the bin directory.                              |   ON    |
| GraphicsTemplate_BACKEND_OPENGL      | Build the OpenGL backend.                                      |   ON    |
| GraphicsTemplate_USE_SDL             | Build with SDL.                                                |   OFF   |
| GraphicsTemplate_NO_PALETTE          | Disable builtin palette.                                       |   OFF   |
| GraphicsTemplate_OP_CHECKS           | Extra checks on function parameters                            |   ON    |
| GraphicsTemplate_EXTRA_BUILTIN_FONTS | Include extra [fonts](https://fonts.google.com/) in the build. |   OFF   |
