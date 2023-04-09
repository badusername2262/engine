#include "../Graphics/shader.h"
#include "../../include/glm/glm.hpp"

#include <array>
#include <string>

struct Vertex {
glm::vec3 m_Position;
glm::vec4 m_Colour;
glm::vec2 m_TexCoords;
float m_TexID;
};

static std::array<Vertex, 4> CreatQuad(glm::vec2 Position, glm::vec2 Size, float TextureID)
{

    Vertex v0;
    v0.m_Position = { Position.x, Position.y, 0.0f };
    v0.m_Colour = { 0.18f, 0.6f, 0.96f, 1.0f };
    v0.m_TexCoords = { 0.0f, 0.0f };
    v0.m_TexID = TextureID;

    Vertex v1;
    v1.m_Position = { Position.x + Size.x, Position.y, 0.0f };
    v1.m_Colour = { 0.18f, 0.6f, 0.96f, 1.0f };
    v1.m_TexCoords = { 1.0f, 0.0f };
    v1.m_TexID = TextureID;

    Vertex v2;
    v2.m_Position = { Position.x + Size.x, Position.y + Size.y, 0.0f };
    v2.m_Colour = { 0.18f, 0.6f, 0.96f, 1.0f };
    v2.m_TexCoords = { 1.0f, 1.0f };
    v2.m_TexID = TextureID;

    Vertex v3;
    v3.m_Position = { Position.x, Position.y + Size.y, 0.0f };
    v3.m_Colour = { 0.18f, 0.6f, 0.96f, 1.0f };
    v3.m_TexCoords = { 0.0f, 1.0f };
    v3.m_TexID = TextureID;

    return { v0, v1, v2, v3 };
};