#include "src/Graphics/window.h"
#include "src/Graphics/shader.h"
#include "src/Utils/camera.h"

#include "src/Buffers/buffer.h"
#include "src/Buffers/indexbuffer.h"
#include "src/Buffers/vertexarray.h"

#include "include/SFML/Audio.hpp"

using namespace Graphics;

int main() 
{
    //creating the window
    Window window("title", 960, 540);
    glClearColor(0.2, 0.3, 0.8, 1.0);

    //creation of shaders and projection matrix
    Shader shader("../resources/Shaders/VertShader", "../resources/Shaders/FragShader");
    shader.bind();
	Camera ortho = Camera::Orthographic(0, 960, 0, 540, 0, 100);
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", Camera::translation(glm::vec3(0, 0, 0)));

    //this is to tell the computer to draw a bright circle that fades to black
	shader.setUniform2f("light_pos", glm::vec2(4.0f, 5.0f));
	shader.setUniform4f("colour", glm::vec4(0.2f, 0.3f, 0.8f, 1.0f));

    sf::SoundBuffer buffer;

    if(!buffer.loadFromFile("C:/Users/GSCrohdea/Desktop/2d_engine/resources/mp3/test.wav"))
    {
        std::cout << "ERROR" << std::endl;
    }

    sf::Sound Sound;
	Sound.setBuffer(buffer);
	Sound.setLoop(true);
	Sound.play();

    //values for imgui
	bool show_demo_window = true;

    static float f = 0.0f;
    static int counter = 0;

    //values for the fixed update
    static double limitFPS = 1.0 / 60.0;
    double lastTime = glfwGetTime(), timer = lastTime;
    double deltaTime = 0, nowTime = 0;
    int frames = 0 , updates = 0;

    //for mouse positioning
    double x, y;

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
        
        //foe the bright light
        shader.setUniform2f("light_pos", glm::vec2((float)(x * 960.0f / 960.0f), (float)(540.0f - y * 540.0f / 540.0f)));

        //ImGui box which makes the inner window
        ImGui::Begin("FPS Checker.");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Text("mouse X:%f, mouse Y:%f", (float)(x * 960.0f / 960.0f), (float)(540.0f - y * 540.0f / 540.0f));
        ImGui::End();

        //fixed update
        while (deltaTime >= 1.0){
            updates++;
            deltaTime--;
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