#pragma once
#define STB_IMAGE_IMPLEMENTATION

#include <GL/glew.h>
#include <fstream>
#include <string>

// File stuff
std::string read_file(const std::string& filepath);

// Textures
GLuint LoadTexture(const std::string& path);
GLuint Texture(const std::string& path);