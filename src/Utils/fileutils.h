#pragma once
#define STB_IMAGE_IMPLEMENTATION

#include <stb_image/stb_image.h>
#include <fstream>
#include <string>


struct Utils {

	static std::string read_file(const std::string& filepath) {
		return {
		std::istreambuf_iterator<char>(std::ifstream(filepath).rdbuf()),
		std::istreambuf_iterator<char>()
		};
	}

	static GLuint LoadTexture(const std::string& path) {
		int w, h, bits;

		stbi_set_flip_vertically_on_load(1);
		auto* pixels = stbi_load(path.c_str(), &w, &h, &bits, STBI_rgb);
		GLuint textureID;
		glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

		stbi_image_free(pixels);

		return textureID;
	}
};
