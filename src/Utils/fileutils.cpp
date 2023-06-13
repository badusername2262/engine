#include "fileutils.h"

#include <stb_image/stb_image.h>
#include "iostream"

std::string read_file(const std::string& filepath) {
	return {
	std::istreambuf_iterator<char>(std::ifstream(filepath).rdbuf()),
	std::istreambuf_iterator<char>()
	};
}

GLuint LoadTexture(const std::string& path) {
    int w, h, bits;

    auto* pixels = stbi_load(path.c_str(), &w, &h, &bits, STBI_rgb_alpha);
    GLuint textureID;
    glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(pixels);

    return textureID;
}

GLuint Texture(const std::string& path) {
    int m_Width, m_Height, m_Bits;

    auto* m_Data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_Bits, STBI_rgb_alpha);

    std::cout << m_Width << std::endl;

    stbi_image_free(m_Data);

    return 0;
}