#include "../Buffers/buffer.h"
#include "../Buffers/indexbuffer.h"
#include "../Buffers/vertexarray.h"
#include "../Graphics/shader.h"
#include "../../include/glm/glm.hpp"

#include <array>
#include <string>

struct Vertex {
glm::vec3 Position;
glm::vec4 Colour;
glm::vec2 TexCoords;
float TexID;
};

static std::array<Vertex, 4> CreatQuad(float x, float y, float TextureID, float size)
{

    Vertex v0;
    v0.Position = { x, y, 0.0f };
    v0.Colour = { 0.18f, 0.6f, 0.96f, 1.0f };
    v0.TexCoords = { 0.0f, 0.0f };
    v0.TexID = TextureID;

    Vertex v1;
    v1.Position = { x + size, y, 0.0f };
    v1.Colour = { 0.18f, 0.6f, 0.96f, 1.0f };
    v1.TexCoords = { 1.0f, 0.0f };
    v1.TexID = TextureID;

    Vertex v2;
    v2.Position = { x + size, y + size, 0.0f };
    v2.Colour = { 0.18f, 0.6f, 0.96f, 1.0f };
    v2.TexCoords = { 1.0f, 1.0f };
    v2.TexID = TextureID;

    Vertex v3;
    v3.Position = { x, y + size, 0.0f };
    v3.Colour = { 0.18f, 0.6f, 0.96f, 1.0f };
    v3.TexCoords = { 0.0f, 1.0f };
    v3.TexID = TextureID;

    return { v0, v1, v2, v3 };
};