#include "window.h"

namespace Graphics
{

    bool Window::Keys[MAX_KEYS];
    bool Window::mouseButtons[MAX_BUTTONS];
    double Window::mx;
    double Window::my;

    void window_resize(GLFWwindow*, int width, int height);
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

    Window::Window(const char* title, int width, int height)
      : title(title), width(width), height(height)
    {
        if (!Init())
            glfwTerminate();

        for (int i = 0; i < MAX_KEYS; i++)
        {
            Keys[i] = false;
        }

        for (int i = 0; i < MAX_BUTTONS; i++)
        {
            mouseButtons[i] = false;
        }
    }

    Window::~Window()
    {
        glfwTerminate();
    }

    static void glfw_error_callback(int error, const char* description)
    {
        fprintf(stderr, "Glfw Error %d: %s\n", error, description);
    }

    bool Window::Init()
    {
        glfwSetErrorCallback(glfw_error_callback);

        const char* glsl_version = "#version 450";

        if (!glfwInit())
        {
            std::cout << "failed to initialize glfw!" << std::endl;
            return false;
        }

        glfwWindowHint(GLFW_RESIZABLE, false);
        window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (!window)
        {
            std::cout << "Failed to create window!" << std::endl;
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);
        glfwSetWindowUserPointer(window, this);
        glfwSetWindowSizeCallback(window, window_resize);
        glfwSetKeyCallback(window, key_callback);
        glfwSetMouseButtonCallback(window, mouse_button_callback);
        glfwSetCursorPosCallback(window, cursor_position_callback);

        glewExperimental = GL_TRUE;
        GLenum err = glewInit();
        if (err != GLEW_OK)
        {
            std::cout << "glewInit failed, aborting." << std::endl;
            glfwTerminate();
            return false;
        }

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        return true;
    }

    bool Window::isKeyPressed(unsigned int keycode)
    {
        assert(keycode < MAX_KEYS);
        return Keys[keycode];
    }

    bool Window::isMouseButtonPressed(unsigned int button)
    {

        if (button >= MAX_BUTTONS)
            return false;

        return mouseButtons[button];
    }

    void Window::getmouseposition(double& x, double& y)
    {
    	x = mx;
    	y = my;
    }

    void Window::Clear() const
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    bool Window::Closed() const
    {
        return glfwWindowShouldClose(window) == 1;
    }

    void Window::Update()
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    void window_resize(GLFWwindow*, int width, int height)
    {
        assert(width > 0 && height > 0);
        glViewport(0, 0, width, height);
    }

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        Window* win = (Window*) glfwGetWindowUserPointer(window);
        win->Keys[key] = action != GLFW_RELEASE;
    }

    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
    	Window* win = (Window*) glfwGetWindowUserPointer(window);
        win->mouseButtons[button] = action != GLFW_RELEASE;
    }

    void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
    {
    	Window* win = (Window*) glfwGetWindowUserPointer(window);
    	win->mx = xpos;
    	win->my = ypos;
    }
};
