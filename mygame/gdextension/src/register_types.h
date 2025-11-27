/*
 * register_types.h
 * 
 * GDExtension registration header.
 */

#pragma once

#include <godot_cpp/core/class_db.hpp>

void initialize_mygame_extension(godot::ModuleInitializationLevel p_level);
void uninitialize_mygame_extension(godot::ModuleInitializationLevel p_level);
