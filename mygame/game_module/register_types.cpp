/*
 * register_types.cpp
 * 
 * Engine module entry point and class registration.
 * This file is compiled when building as an engine module.
 */

#include "register_types.h"

#include "core/object/class_db.h"

// Include all game classes
// Note: The path here is relative to the godot/modules/mygame directory
// which is where this module will be symlinked/copied
#include "game_src/game_classes.h"

void initialize_mygame_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
    
    // Register all game classes
    GDREGISTER_CLASS(LogoFlasher);
    
    // Add more class registrations here:
    // GDREGISTER_CLASS(Player);
    // GDREGISTER_CLASS(Enemy);
}

void uninitialize_mygame_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
    
    // Cleanup if needed
}
