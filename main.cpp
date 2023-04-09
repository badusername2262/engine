#include "src/Graphics/window.h"
#include "src/Graphics/shader.h"
#include "src/Utils/camera.h"

#include "src/Buffers/buffer.h"
#include "src/Buffers/indexbuffer.h"
#include "src/Buffers/vertexarray.h"
#include "src/Renderers/renderer.h"

#include <SFML/Audio.hpp>

using namespace Graphics;

int main() 
{
    //creating the window
    Window window("title", 960, 540);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    //creation of shaders and projection matrix
    Shader shader("../resources/Shaders/VertShader", "../resources/Shaders/FragShader");
    shader.bind();
	Camera ortho = Camera::Orthographic(0, 16, 0, 9, 0, 1);
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", Camera::translation(glm::vec3(8, 4.5, 0)));
    
    GLuint smile = Utils::LoadTexture("../resources/textures/smile.png");
    GLuint smile2 = Utils::LoadTexture("../resources/textures/ahhh.jpg");
    
    auto loc = shader.getUniformLocation("u_Textures");
    int samplers[31] = {1, 0};
    shader.setUnuform1iV(loc, 31, samplers);

    GLuint QuaidVA;
    GLuint QuaidVB;
    GLuint QuaidIB;

    glCreateVertexArrays(1, &QuaidVA);
    glBindVertexArray(QuaidVA);

    glCreateBuffers(1, &QuaidVB);
    glBindBuffer(GL_ARRAY_BUFFER, QuaidVB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 1000, nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexArrayAttrib(QuaidVB, 0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, m_Position));

    glEnableVertexArrayAttrib(QuaidVB, 1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, m_Colour));

    glEnableVertexArrayAttrib(QuaidVB, 2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, m_TexCoords));

    glEnableVertexArrayAttrib(QuaidVB, 3);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, m_TexID));

    uint32_t indices[] = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        8, 9, 10, 10, 11, 8
    };

    glCreateBuffers(1, &QuaidIB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, QuaidIB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    //Sound
    sf::Music music;
    if(!music.openFromFile("C:/engine/resources/wav/Royalty Free Music Background Music Chill No Copyright Music Free To Use _ Unisho Reason - Z8phyR (320 kbps).wav"))
        std::cout << "ERROR" << std::endl;
    music.setVolume(0);
    music.setLoop(true);
    music.play();

    //values for imgui
	bool show_demo_window = true;

    static float f = 0.0f;
    static int counter = 0;

    //values for the fixed update
    static double limitFPS = 1.0 / 60.0;
    double lastTime = glfwGetTime(), timer = lastTime;
    double deltaTime = 0, nowTime = 0;
    int frames = 0 , updates = 0;

    double x, y;
    int volume = 0;
    glm::vec2 QuadPosition = { -5.5, -2.5 };

    while (!window.Closed())
    {
        window.Clear();

        //stuff to calculate delta time for the fixed update
        nowTime = glfwGetTime();
        deltaTime += (nowTime - lastTime) / limitFPS;
        lastTime = nowTime;

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

        auto q0 = CreatQuad(QuadPosition, glm::vec2(3.0f, 5.0f), 0.0f);
        auto q1 = CreatQuad(glm::vec2(0.5f, 0.5f), glm::vec2(2.0f, 2.0f), 1.0f);

        Vertex verticies[2 * 4];
        memcpy(verticies, q0.data(), q0.size() * sizeof(Vertex));
        memcpy(verticies + 4, q1.data(), q1.size() * sizeof(Vertex));

        glBindBuffer(GL_ARRAY_BUFFER, QuaidVB);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verticies), verticies);

        glBindVertexArray(QuaidVA);
        glBindTextureUnit(0, smile);
        glBindTextureUnit(1, smile2);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);

        //fixed update
        while (deltaTime >= 1.0){
            updates++;
            deltaTime--;
            music.setVolume(volume);
        }
        //rendering to the screen
		ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        window.Update();

        //debug stuff for fixed update
        frames++;
        if (glfwGetTime() - timer > 1.0) {
            timer ++;
            std::cout << "FPS: " << frames << " Updates:" << updates << std::endl;
            updates = 0, frames = 0;
        }    
    }
    //when the application closes it deletes all instances of its self to free up computer resources
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}