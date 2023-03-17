#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.hpp>
#include <imgui/imgui_impl_glfw.hpp>
#include <imgui/imgui_impl_opengl3.hpp>

#include <iostream>

namespace Graphics {

#define MAX_KEYS    1024
#define MAX_BUTTONS 32

    class Window
    {
    private:
        friend struct GLFWwindow;
        const char* title;
        int width, height;
        GLFWwindow* window;
        bool  closed;
    
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

}
