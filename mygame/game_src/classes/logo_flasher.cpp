/*
 * logo_flasher.cpp
 * 
 * Implementation of the LogoFlasher class.
 */

#include "logo_flasher.h"

void LogoFlasher::_bind_methods() {
    // Bind property accessors
    ClassDB::bind_method(D_METHOD("set_flash_interval", "interval"), &LogoFlasher::set_flash_interval);
    ClassDB::bind_method(D_METHOD("get_flash_interval"), &LogoFlasher::get_flash_interval);
    
    ClassDB::bind_method(D_METHOD("set_max_flashes", "max_flashes"), &LogoFlasher::set_max_flashes);
    ClassDB::bind_method(D_METHOD("get_max_flashes"), &LogoFlasher::get_max_flashes);
    
    ClassDB::bind_method(D_METHOD("set_flash_color_a", "color"), &LogoFlasher::set_flash_color_a);
    ClassDB::bind_method(D_METHOD("get_flash_color_a"), &LogoFlasher::get_flash_color_a);
    
    ClassDB::bind_method(D_METHOD("set_flash_color_b", "color"), &LogoFlasher::set_flash_color_b);
    ClassDB::bind_method(D_METHOD("get_flash_color_b"), &LogoFlasher::get_flash_color_b);
    
    // Bind methods
    ClassDB::bind_method(D_METHOD("start_flashing"), &LogoFlasher::start_flashing);
    ClassDB::bind_method(D_METHOD("stop_flashing"), &LogoFlasher::stop_flashing);
    ClassDB::bind_method(D_METHOD("is_currently_flashing"), &LogoFlasher::is_currently_flashing);
    ClassDB::bind_method(D_METHOD("get_build_mode"), &LogoFlasher::get_build_mode);
    
    // Register properties
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "flash_interval", PROPERTY_HINT_RANGE, "0.1,2.0,0.1"), 
                 "set_flash_interval", "get_flash_interval");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "max_flashes", PROPERTY_HINT_RANGE, "1,20,1"), 
                 "set_max_flashes", "get_max_flashes");
    ADD_PROPERTY(PropertyInfo(Variant::COLOR, "flash_color_a"), 
                 "set_flash_color_a", "get_flash_color_a");
    ADD_PROPERTY(PropertyInfo(Variant::COLOR, "flash_color_b"), 
                 "set_flash_color_b", "get_flash_color_b");
}

LogoFlasher::LogoFlasher() {
    // Determine build mode message
#if GAME_GDEXTENSION
    build_mode_message = "GDExtension Mode (Development)";
#else
    build_mode_message = "Engine Module Mode (Deployment)";
#endif
}

LogoFlasher::~LogoFlasher() {
    // Sprite2D is a child node, Godot handles its cleanup
}

void LogoFlasher::_ready() {
    GAME_PRINT("===========================================");
    GAME_PRINT("LogoFlasher: C++ Code Running Successfully!");
    GAME_PRINT("Build Mode: ", build_mode_message);
    GAME_PRINT("===========================================");
    
    // Create the sprite for the logo
    logo_sprite = memnew(Sprite2D);
    add_child(logo_sprite);
    
    // Load the Godot logo texture
    // In GDExtension, we use ResourceLoader singleton
    // In Module, we can use ResourceLoader directly
#if GAME_GDEXTENSION
    Ref<Texture2D> logo_texture = ResourceLoader::get_singleton()->load("res://icon.svg");
#else
    Ref<Texture2D> logo_texture = ResourceLoader::load("res://icon.svg");
#endif
    
    if (logo_texture.is_valid()) {
        logo_sprite->set_texture(logo_texture);
        GAME_PRINT("LogoFlasher: Logo texture loaded successfully!");
    } else {
        GAME_PRINT_ERR("LogoFlasher: Failed to load icon.svg - make sure it exists in project root!");
    }
    
    // Center the logo on screen
    // Get viewport size
#if GAME_GDEXTENSION
    if (get_tree() && get_tree()->get_root()) {
        Vector2 viewport_size = get_tree()->get_root()->get_visible_rect().size;
        set_position(viewport_size / 2.0);
    }
#else
    if (get_tree() && get_tree()->get_root()) {
        Vector2 viewport_size = get_tree()->get_root()->get_visible_rect().size;
        set_position(viewport_size / 2.0);
    }
#endif
    
    // Scale up the logo a bit
    logo_sprite->set_scale(Vector2(2.0, 2.0));
    
    // Start flashing
    start_flashing();
}

void LogoFlasher::_process(double delta) {
    if (!is_flashing || !logo_sprite) {
        return;
    }
    
    flash_timer += delta;
    
    if (flash_timer >= flash_interval) {
        flash_timer = 0.0;
        flash_count++;
        
        // Toggle color
        use_color_a = !use_color_a;
        logo_sprite->set_modulate(use_color_a ? flash_color_a : flash_color_b);
        
        // Also scale pulse effect
        double scale_factor = use_color_a ? 2.0 : 2.3;
        logo_sprite->set_scale(Vector2(scale_factor, scale_factor));
        
        // Check if we're done flashing
        if (flash_count >= max_flashes) {
            stop_flashing();
            GAME_PRINT("LogoFlasher: Flash sequence complete!");
        }
    }
}

void LogoFlasher::set_flash_interval(double p_interval) {
    flash_interval = p_interval;
}

double LogoFlasher::get_flash_interval() const {
    return flash_interval;
}

void LogoFlasher::set_max_flashes(int p_max) {
    max_flashes = p_max;
}

int LogoFlasher::get_max_flashes() const {
    return max_flashes;
}

void LogoFlasher::set_flash_color_a(const Color& p_color) {
    flash_color_a = p_color;
}

Color LogoFlasher::get_flash_color_a() const {
    return flash_color_a;
}

void LogoFlasher::set_flash_color_b(const Color& p_color) {
    flash_color_b = p_color;
}

Color LogoFlasher::get_flash_color_b() const {
    return flash_color_b;
}

void LogoFlasher::start_flashing() {
    is_flashing = true;
    flash_timer = 0.0;
    flash_count = 0;
    use_color_a = true;
    
    if (logo_sprite) {
        logo_sprite->set_modulate(flash_color_a);
        logo_sprite->set_visible(true);
    }
    
    GAME_PRINT("LogoFlasher: Starting flash sequence...");
}

void LogoFlasher::stop_flashing() {
    is_flashing = false;
    
    if (logo_sprite) {
        logo_sprite->set_modulate(flash_color_a);
        logo_sprite->set_scale(Vector2(2.0, 2.0));
    }
}

bool LogoFlasher::is_currently_flashing() const {
    return is_flashing;
}

String LogoFlasher::get_build_mode() const {
    return build_mode_message;
}
