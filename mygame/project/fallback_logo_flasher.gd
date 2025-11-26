extends Node2D
## GDScript fallback for LogoFlasher
## This demonstrates the same functionality as the C++ class
## Use this to test the project before building the C++ extension

@export var flash_interval: float = 0.3
@export var max_flashes: int = 10
@export var flash_color_a: Color = Color.WHITE
@export var flash_color_b: Color = Color(0.2, 0.6, 1.0, 1.0)

var logo_sprite: Sprite2D
var flash_timer: float = 0.0
var flash_count: int = 0
var is_flashing: bool = true
var use_color_a: bool = true

func _ready():
	print("===========================================")
	print("LogoFlasher: GDScript Fallback Running")
	print("Build the C++ extension for the real deal!")
	print("===========================================")
	
	# Create sprite
	logo_sprite = Sprite2D.new()
	add_child(logo_sprite)
	
	# Load texture
	var texture = load("res://icon.svg")
	if texture:
		logo_sprite.texture = texture
		print("LogoFlasher: Logo texture loaded!")
	else:
		push_error("LogoFlasher: Failed to load icon.svg")
	
	# Scale up
	logo_sprite.scale = Vector2(2.0, 2.0)
	
	start_flashing()

func _process(delta):
	if not is_flashing or not logo_sprite:
		return
	
	flash_timer += delta
	
	if flash_timer >= flash_interval:
		flash_timer = 0.0
		flash_count += 1
		
		use_color_a = not use_color_a
		logo_sprite.modulate = flash_color_a if use_color_a else flash_color_b
		
		var scale_factor = 2.0 if use_color_a else 2.3
		logo_sprite.scale = Vector2(scale_factor, scale_factor)
		
		if flash_count >= max_flashes:
			stop_flashing()
			print("LogoFlasher: Flash sequence complete!")

func start_flashing():
	is_flashing = true
	flash_timer = 0.0
	flash_count = 0
	use_color_a = true
	
	if logo_sprite:
		logo_sprite.modulate = flash_color_a
		logo_sprite.visible = true
	
	print("LogoFlasher: Starting flash sequence...")

func stop_flashing():
	is_flashing = false
	
	if logo_sprite:
		logo_sprite.modulate = flash_color_a
		logo_sprite.scale = Vector2(2.0, 2.0)

func is_currently_flashing() -> bool:
	return is_flashing

func get_build_mode() -> String:
	return "GDScript Fallback Mode"
