/*
 * register_types.cpp
 * 
 * GDExtension entry point and class registration.
 * This file is compiled when building as a GDExtension.
 */

// Note: GDEXTENSION_BUILD is defined via SConstruct, no need to define it here

#include "register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>

// Include all game classes
#include "../../game_src/game_classes.h"

using namespace godot;

void initialize_mygame_extension(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
    
    // Register all game classes
    ClassDB::register_class<LogoFlasher>();
    
    // Add more class registrations here:
    // ClassDB::register_class<Player>();
    // ClassDB::register_class<Enemy>();
}

void uninitialize_mygame_extension(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
    
    // Cleanup if needed
}

extern "C" {
    // GDExtension entry point
    GDExtensionBool GDE_EXPORT mygame_library_init(
        GDExtensionInterfaceGetProcAddress p_get_proc_address,
        GDExtensionClassLibraryPtr p_library,
        GDExtensionInitialization *r_initialization
    ) {
        GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
        
        init_obj.register_initializer(initialize_mygame_extension);
        init_obj.register_terminator(uninitialize_mygame_extension);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);
        
        return init_obj.init();
    }
}
