/*
 * logo_flasher.h
 * 
 * A simple Node2D that displays and flashes the Godot logo to demonstrate
 * that the C++ code is working correctly in both GDExtension and module modes.
 */

#pragma once

#include "../game_config.h"

class LogoFlasher : public Node2D {
    GDCLASS(LogoFlasher, Node2D);

private:
    // The sprite that displays the logo
    Sprite2D* logo_sprite = nullptr;
    
    // Flash timing
    double flash_timer = 0.0;
    double flash_interval = 0.5;  // How often to toggle visibility
    int flash_count = 0;
    int max_flashes = 6;  // Number of times to flash (3 on/off cycles)
    bool is_flashing = true;
    
    // Color modulation for effect
    Color flash_color_a = Color(1.0, 1.0, 1.0, 1.0);  // White (normal)
    Color flash_color_b = Color(0.3, 0.5, 1.0, 1.0);  // Blue tint
    bool use_color_a = true;
    
    // Message to display
    String build_mode_message;

protected:
    static void _bind_methods();

public:
    // Property accessors
    void set_flash_interval(double p_interval);
    double get_flash_interval() const;
    
    void set_max_flashes(int p_max);
    int get_max_flashes() const;
    
    void set_flash_color_a(const Color& p_color);
    Color get_flash_color_a() const;
    
    void set_flash_color_b(const Color& p_color);
    Color get_flash_color_b() const;
    
    // Methods
    void start_flashing();
    void stop_flashing();
    bool is_currently_flashing() const;
    String get_build_mode() const;
    
    // Godot virtual methods
    void _ready();
    void _process(double delta);
    
    LogoFlasher();
    ~LogoFlasher();
};
