# Playdate VS Code Template (Mac)
Build and run projects in the Playdate simulator with a key shortcut.

## Requirements
- [VS Code](https://code.visualstudio.com)
- [C/C++ Extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
- [CMake Extension](https://marketplace.visualstudio.com/items?itemName=twxs.cmake)
- [Playdate SDK](https://play.date/dev/)
- CMake (`brew install cmake`)
- cmocka (`brew install cmocka`) - for testing


## Get Started
**This is a template repo.**  
You can generate your own separate repositories from this template with the same directory structure, branches, and files. Click "Use this template" to create your own repo.

1. Clone or download the repo.
2. In VS Code, choose Run > Run Without Debugging to launch the project in the Playdate simulator.
3. Assign a keyboard shortcut to the Run Without Debugging option to build and run with a keypress.

## Output
Build files get output to `HelloWorld.pdx`. There are some additional build files, like CMake logs, in the `build` directory.

## Creating Your Own Project
1. Do a global project replace for "HelloWorld" and "hello_world", replacing it with your own program name.
2. Modify or add the appropriate information in `Source/pdxinfo`.
3. Write the app code.

## Automatic Test and Build
1. Install watchman (`brew install watchman`)
2. `make watch`

## Writing and Running Tests
1. Write tests under `lib/__tests__`- watcher will automatically run them when files change.
2. `make test` to compile and run only tests.