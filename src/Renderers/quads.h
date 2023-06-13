#include <glm/glm.hpp>

#include <array>
#include <string>

struct Vertex {
glm::vec2 m_Position;
glm::vec4 m_Colour;
glm::vec2 m_UV;
};

static std::array<Vertex, 4> CreatQuad(glm::vec2 Position, glm::vec2 Size, glm::vec2 UV)
{

    Vertex v0;
    v0.m_Position = { Position.x, Position.y };
    v0.m_UV = { ((UV.x * 512) / 1024), ((UV.y * 512) / 512)};

    Vertex v1;
    v1.m_Position = { Position.x + Size.x, Position.y };
    v1.m_UV = { ((UV.x +1) * 512) / 1024, ((UV.y * 512) / 512)};

    Vertex v2;
    v2.m_Position = { Position.x + Size.x, Position.y + Size.y };
    v2.m_UV = { ((UV.x + 1) * 512) / 1024, ((UV.y + 1) * 512) / 512};

    Vertex v3;
    v3.m_Position = { Position.x, Position.y + Size.y };
    v3.m_UV = { ((UV.x * 512) / 1024), ((UV.y + 1) * 512) / 512};

    return { v0, v1, v2, v3 };
};

static std::array<Vertex, 4> CreatQuad(glm::vec2 Position, glm::vec2 Size, glm::vec4 Colour)
{

    Vertex v0;
    v0.m_Position = { Position.x, Position.y };
    v0.m_Colour = Colour;

    Vertex v1;
    v1.m_Position = { Position.x + Size.x, Position.y };
    v1.m_Colour = Colour;

    Vertex v2;
    v2.m_Position = { Position.x + Size.x, Position.y + Size.y };
    v2.m_Colour = Colour;

    Vertex v3;
    v3.m_Position = { Position.x, Position.y + Size.y };
    v3.m_Colour = Colour;

    return { v0, v1, v2, v3 };
};