"""
config.py

Module configuration for the Godot build system.
"""

def can_build(env, platform):
    """Return True to enable this module for all platforms."""
    return True


def configure(env):
    """Configure the environment for this module."""
    pass


def get_doc_classes():
    """Return list of classes that have documentation."""
    return [
        "LogoFlasher",
        # Add more documented classes here:
        # "Player",
        # "Enemy",
    ]


def get_doc_path():
    """Return path to documentation files."""
    return "doc_classes"
