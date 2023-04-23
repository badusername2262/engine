#include "src/Graphics/window.h"
#include "src/Graphics/shader.h"
#include "src/Utils/camera.h"

#include "src/Renderers/quads.h"
#include "src/Utils/collition.h"

#include <SFML/Audio.hpp>

using namespace Graphics;

DeltaTime deltatime;

int main() 
{
    //creating the window
    Window window("title", 960, 540);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    //creation of shaders and projection matrix
    Shader shader("../resources/Shaders/VertShader", "../resources/Shaders/FragShader");
    shader.bind();
	Camera ortho = Camera::Orthographic(0, 960, 540, 0, 0, 1);
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", Camera::translation(glm::vec3(480, 270, 0)));
    
    AABB player1;
    AABB player2;

    GLuint smile = Utils::LoadTexture("../resources/textures/smile.png");
    GLuint smile2 = Utils::LoadTexture("../resources/textures/ahhh.jpg");
    
    auto loc = shader.getUniformLocation("u_Textures");
    int samplers[31] = {0, 1};
    shader.setUnuform1iV(loc, 31, samplers);

    GLuint QuaidVA;
    GLuint QuaidVB;
    GLuint QuaidIB;

    glBindVertexArray(QuaidVA);
    glBindTextureUnit(1, smile);
    glBindTextureUnit(0, smile2);

    glCreateVertexArrays(1, &QuaidVA);
    glBindVertexArray(QuaidVA);

    glCreateBuffers(1, &QuaidVB);
    glBindBuffer(GL_ARRAY_BUFFER, QuaidVB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 1000, nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexArrayAttrib(QuaidVB, 0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, m_Position));

    glEnableVertexArrayAttrib(QuaidVB, 2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, m_TexCoords));

    glEnableVertexArrayAttrib(QuaidVB, 3);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, m_TexID));

    uint32_t indices[] = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4
    };

    glCreateBuffers(1, &QuaidIB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, QuaidIB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    //Sound
    sf::Music music;
    if(!music.openFromFile("../resources/wav/Epic Battle [Epic Music] by MokkaMusic _ Rome Battle-HQ.wav"))
        std::cout << "ERROR" << std::endl;
    music.setVolume(0);
    music.setLoop(true);
    music.play();

    //values for imgui
	bool show_demo_window = true;

    static float f = 0.0f;
    static int counter = 0;

    double x, y;
    int volume = 0;
    glm::vec2 QuadPosition = { -5.5, -2.5 };

    while (window.Closed())
    {
        window.Clear();
        deltatime.update();

        //begining the on screen gui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        window.getmouseposition(x, y);

        //ImGui box which makes the inner window
        ImGui::Begin("FPS Checker.");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Text("mouse X:%f, mouse Y:%f", (float)(x * 960.0f / 960.0f), (float)(540.0f - y * 540.0f / 540.0f));
        ImGui::SliderInt("Volume", &volume, 0, 100);
        ImGui::DragFloat2("Quad Position", (float*)&QuadPosition, 0.1f);
        ImGui::End();

        if (window.isKeyPressed(GLFW_KEY_UP))
        {
            QuadPosition.y = QuadPosition.y - 200 * deltatime.deltaTime;
        }
        
        if (window.isKeyPressed(GLFW_KEY_DOWN))
        {
            QuadPosition.y = QuadPosition.y + 200 * deltatime.deltaTime;
        }
        
        if (window.isKeyPressed(GLFW_KEY_RIGHT))
        {
            QuadPosition.x = QuadPosition.x + 200 * deltatime.deltaTime;
        }

        if (window.isKeyPressed(GLFW_KEY_LEFT))
        {
            QuadPosition.x = QuadPosition.x - 200 * deltatime.deltaTime;
        }

        auto q0 = CreatQuad(QuadPosition, glm::vec2(100.0f, 100.0f), 0.0f);
        player1.minX = QuadPosition.x;
        player1.maxX = QuadPosition.x + 100.0f;
        player1.minY = QuadPosition.y;
        player1.maxY = QuadPosition.y + 100;

        auto q1 = CreatQuad(glm::vec2(0.5f, 0.5f), glm::vec2(100.0f, 100.0f), 1.0f);
        player2.minX = 0.5f;
        player2.maxX = 0.5f + 100.0f;
        player2.minY = 0.5f;
        player2.maxY = 0.5f + 100;

        CollisionSide side = checkAABBCollision(player1, player2);

        switch (side) {
            case Top:
            
            break;
        case Bottom:
            
            break;
        case Left:
            
            break;
        case Right:
            
            break;
        case None:
            
            break;
        }

        Vertex verticies[2 * 4];
        memcpy(verticies, q0.data(), q0.size() * sizeof(Vertex));
        memcpy(verticies + 4, q1.data(), q1.size() * sizeof(Vertex));

        glBindBuffer(GL_ARRAY_BUFFER, QuaidVB);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verticies), verticies);


        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);

        music.setVolume(volume);
        
        //rendering to the screen
		ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        window.Update();
    }
    //when the application closes it deletes all instances of its self to free up computer resources
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}