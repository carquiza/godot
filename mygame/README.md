# MyGame C++ Template for Godot

A template for developing Godot games in C++ with **dual-mode compilation**:
- **GDExtension Mode** - For fast development iteration (hot reload, no engine rebuild)
- **Engine Module Mode** - For deployment (Web, iOS, optimal performance)

## Directory Structure

```
mygame/
├── game_src/                    # Shared C++ game code
│   ├── game_config.h            # Build mode detection &amp; unified includes
│   ├── game_classes.h           # Master include for all classes
│   └── classes/
│       └── logo_flasher.cpp/h   # Example class
│
├── gdextension/                 # GDExtension build (development)
│   ├── godot-cpp/               # Git submodule (run setup_godot_cpp.bat)
│   ├── src/
│   │   └── register_types.cpp/h # GDExtension entry point
│   └── SConstruct
│
├── game_module/                 # Engine module build (deployment)
│   ├── register_types.cpp/h     # Module entry point
│   ├── config.py
│   └── SCsub
│
├── project/                     # Godot project
│   ├── project.godot
│   ├── main.tscn
│   ├── icon.svg
│   └── bin/
│       └── mygame.gdextension
│
└── scripts/                     # Build helper scripts
    ├── setup_godot_cpp.bat      # Initialize godot-cpp
    ├── build_extension.bat      # Build GDExtension
    ├── setup_module.bat         # Setup engine module
    ├── sync_module.bat          # Sync changes to module
    ├── build_godot_editor.bat   # Build custom editor
    └── build_export_templates.bat # Build export templates
```

## Quick Start

### Prerequisites

1. **Python 3.6+** with SCons installed: `pip install scons`
2. **Visual Studio 2019/2022** with C++ workload (Windows)
3. **Git** for cloning godot-cpp

### Development Mode (GDExtension)

1. **Initialize godot-cpp:**
   ```batch
   scripts\setup_godot_cpp.bat
   ```

2. **Build the extension:**
   ```batch
   scripts\build_extension.bat
   ```

3. **Open the project:**
   - Launch Godot
   - Open `mygame/project/project.godot`
   - Run the main scene

### Deployment Mode (Engine Module)

For Web, iOS, or optimized builds:

1. **Setup the module:**
   ```batch
   scripts\setup_module.bat
   ```

2. **Build a custom editor (optional, for testing):**
   ```batch
   scripts\build_godot_editor.bat
   ```

3. **Build export templates:**
   ```batch
   scripts\build_export_templates.bat
   ```

## Adding New Classes

1. **Create the class files** in `game_src/classes/`:
   ```cpp
   // game_src/classes/my_class.h
   #pragma once
   #include "../game_config.h"
   
   class MyClass : public Node {
       GDCLASS(MyClass, Node);
   protected:
       static void _bind_methods();
   public:
       // Your methods and properties
   };
   ```

2. **Add to game_classes.h:**
   ```cpp
   #include "classes/my_class.h"
   ```

3. **Register in both entry points:**
   
   **gdextension/src/register_types.cpp:**
   ```cpp
   ClassDB::register_class&lt;MyClass&gt;();
   ```
   
   **game_module/register_types.cpp:**
   ```cpp
   GDREGISTER_CLASS(MyClass);
   ```

4. **Update config.py** (for documentation):
   ```python
   def get_doc_classes():
       return ["LogoFlasher", "MyClass"]
   ```

## How It Works

The key is `game_config.h` which detects the build mode:

```cpp
#if defined(GDEXTENSION_BUILD)
    // Use godot-cpp includes
    #include &lt;godot_cpp/classes/node.hpp&gt;
    using namespace godot;
#else
    // Use engine includes
    #include "scene/main/node.h"
#endif
```

Game code in `game_src/` includes `game_config.h` first, then works identically in both modes.


## Development Workflow

### Daily Development
1. Write/modify code in `game_src/`
2. Run `build_extension.bat`
3. Test in Godot (hot reload supported!)

### Before Release
1. Run `setup_module.bat` (or `sync_module.bat` if already setup)
2. Build export templates with `build_export_templates.bat`
3. Export from Godot using custom templates

### After Code Changes
- **For GDExtension:** Just run `build_extension.bat`
- **For Module:** Run `sync_module.bat` then rebuild Godot

## Tips

- **Hot Reload:** GDExtension supports hot reload in Godot 4.2+
- **Debugging:** Debug builds have full symbol information
- **Performance:** Module builds are slightly faster than GDExtension
- **File Size:** Module builds produce smaller exports

## Troubleshooting

### "LogoFlasher class not found"
- Make sure you've built the extension: `build_extension.bat`
- Check that the .dll was copied to `project/bin/windows/`

### Build errors in godot-cpp
- Ensure you're using the correct godot-cpp branch (4.3)
- Try cleaning and rebuilding: `scons -c` then `scons ...`

### Web export not working
- Web doesn't support GDExtension
- You must use module mode: `setup_module.bat` + `build_export_templates.bat`

## License

This template is provided under the MIT License.
