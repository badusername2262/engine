#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.hpp>
#include <imgui/imgui_impl_glfw.hpp>
#include <imgui/imgui_impl_opengl3.hpp>

#include <iostream>

namespace Graphics {

    class Window
    {
    private:
        friend struct GLFWwindow;
        const char* title;
        int width, height;
        GLFWwindow* window;
        bool  closed;
    
        static constexpr int MAX_KEYS = GLFW_KEY_LAST + 1;
        static constexpr int MAX_BUTTONS = GLFW_MOUSE_BUTTON_LAST + 1;
        static bool Keys[MAX_KEYS];
        static bool mouseButtons[MAX_BUTTONS];
        static double mx, my;
    public:
        Window(const char* title, int width, int height);
        ~Window();
        void Clear() const;
        bool Closed() const;
        void Update();
    
        inline int getWidth() const { return width; }
        inline int getHeight() const { return height; }

        static bool isKeyPressed(unsigned int keycode);
        static bool isMouseButtonPressed(unsigned int button);
        static void getmouseposition(double& x, double& y);
    private:
        bool Init();
        friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
        friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    };

    struct Clock {
        double lastTime;
        const double frameTime = 1.0 / 60.0;
        double accumulatedTime;
        int updates;

        Clock() : lastTime(glfwGetTime()), accumulatedTime(0.0) {}

        double DeltaTime() {
            double currentTime = glfwGetTime();
            double deltaTime = (currentTime - lastTime) / frameTime;
            lastTime = currentTime;
            accumulatedTime += deltaTime;

            if (accumulatedTime >= frameTime) {
                accumulatedTime -= frameTime;
                deltaTime = frameTime;
            }

            return deltaTime;
        }
    };
}
