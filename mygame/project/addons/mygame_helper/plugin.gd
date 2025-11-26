@tool
extends EditorPlugin

# This plugin helps verify the C++ extension is loaded correctly

func _enter_tree():
	print("MyGame C++ Template - Editor Plugin Loaded")
	
	# Check if LogoFlasher class exists
	if ClassDB.class_exists("LogoFlasher"):
		print("✓ LogoFlasher class found - C++ extension is working!")
	else:
		push_warning("LogoFlasher class not found - C++ extension may not be built")
		push_warning("Run scripts/build_extension.bat to build the extension")


func _exit_tree():
	pass
