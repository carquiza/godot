/*
 * game_config.h
 * 
 * Build mode detection and unified includes for dual-mode compilation.
 * This file detects whether we're building as a GDExtension or as an engine module
 * and provides the appropriate includes and macros for each mode.
 */

#pragma once

// ============================================================================
// BUILD MODE DETECTION
// ============================================================================

#if defined(GDEXTENSION_BUILD)
    // Building as GDExtension (development mode)
    #define GAME_GDEXTENSION 1
    #define GAME_MODULE 0
    
    // GDExtension includes from godot-cpp
    #include <godot_cpp/godot.hpp>
    #include <godot_cpp/core/class_db.hpp>
    #include <godot_cpp/core/binder_common.hpp>
    
    // Core types
    #include <godot_cpp/variant/variant.hpp>
    #include <godot_cpp/variant/string.hpp>
    #include <godot_cpp/variant/vector2.hpp>
    #include <godot_cpp/variant/vector3.hpp>
    #include <godot_cpp/variant/color.hpp>
    
    // Base classes
    #include <godot_cpp/classes/ref_counted.hpp>
    #include <godot_cpp/classes/resource.hpp>
    #include <godot_cpp/classes/node.hpp>
    #include <godot_cpp/classes/node2d.hpp>
    #include <godot_cpp/classes/node3d.hpp>
    #include <godot_cpp/classes/control.hpp>
    #include <godot_cpp/classes/canvas_item.hpp>
    
    // Commonly used classes
    #include <godot_cpp/classes/sprite2d.hpp>
    #include <godot_cpp/classes/texture2d.hpp>
    #include <godot_cpp/classes/engine.hpp>
    #include <godot_cpp/classes/resource_loader.hpp>
    #include <godot_cpp/classes/scene_tree.hpp>
    #include <godot_cpp/classes/window.hpp>
    
    using namespace godot;
    
#else
    // Building as Engine Module (deployment mode)
    #define GAME_GDEXTENSION 0
    #define GAME_MODULE 1
    
    // Engine includes
    #include "core/object/ref_counted.h"
    #include "core/object/class_db.h"
    #include "core/io/resource_loader.h"
    #include "core/string/ustring.h"
    #include "core/math/vector2.h"
    #include "core/math/vector3.h"
    #include "core/math/color.h"
    #include "core/variant/variant.h"
    
    // Scene classes
    #include "scene/main/node.h"
    #include "scene/2d/node_2d.h"
    #include "scene/3d/node_3d.h"
    #include "scene/gui/control.h"
    #include "scene/main/canvas_item.h"
    #include "scene/2d/sprite_2d.h"
    #include "scene/resources/texture.h"
    #include "scene/main/scene_tree.h"
    #include "scene/main/window.h"
    #include "core/config/engine.h"
    
#endif

// ============================================================================
// UNIFIED MACROS
// ============================================================================

// These macros provide a unified interface for common operations that differ
// between GDExtension and module builds.

#if GAME_GDEXTENSION
    // GDExtension uses ClassDB::register_class
    #define GAME_REGISTER_CLASS(m_class) ClassDB::register_class<m_class>()
    #define GAME_REGISTER_ABSTRACT_CLASS(m_class) ClassDB::register_abstract_class<m_class>()
#else
    // Module uses GDREGISTER macros
    #define GAME_REGISTER_CLASS(m_class) GDREGISTER_CLASS(m_class)
    #define GAME_REGISTER_ABSTRACT_CLASS(m_class) GDREGISTER_ABSTRACT_CLASS(m_class)
#endif

// ============================================================================
// HELPER MACROS
// ============================================================================

// Print macro that works in both modes
#if GAME_GDEXTENSION
    #include <godot_cpp/variant/utility_functions.hpp>
    #define GAME_PRINT(...) UtilityFunctions::print(__VA_ARGS__)
    #define GAME_PRINT_ERR(...) UtilityFunctions::printerr(__VA_ARGS__)
#else
    #include "core/string/print_string.h"
    #define GAME_PRINT(...) print_line(__VA_ARGS__)
    #define GAME_PRINT_ERR(...) print_error(__VA_ARGS__)
#endif
