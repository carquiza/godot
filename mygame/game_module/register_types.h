/*
 * register_types.h
 * 
 * Engine module registration header.
 */

#pragma once

#include "modules/register_module_types.h"

void initialize_mygame_module(ModuleInitializationLevel p_level);
void uninitialize_mygame_module(ModuleInitializationLevel p_level);
