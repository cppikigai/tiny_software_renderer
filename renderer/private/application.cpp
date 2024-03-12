#include "application.h"
#include <iostream>

namespace TSR
{
    Application::Application(const std::string& title, int32_t width, int32_t height)
    : m_title(title)
    , m_width(width)
    , m_height(height)
    , m_isRunning(false)
    {}

    void Application::Run()
    {
        Initilalize();

        while(m_isRunning)
        {
            Render();
        }

        Shutdown();
    }

    void Application::Initilalize()
    {
        if(!glfwInit())
        {
            std::cerr << "Failed to initialize glfw" << std::endl;
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
        if(!m_window)
        {
            std::cerr << "Failed to create glfw window" << std::endl;
            return;
        }

        glfwMakeContextCurrent(m_window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize glad" << std::endl;
            return;
        }

        glViewport(0, 0, m_width, m_height);

        OnInitialize();

        m_isRunning = true;
    }

    void Application::Render()
    {
        glfwPollEvents();
        if (glfwWindowShouldClose(m_window))
        {
            m_isRunning = false;
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        OnRender();

        glfwSwapBuffers(m_window);
    }

    void Application::Shutdown()
    {
        OnShutdown();

        glfwTerminate();
        m_isRunning = false;
    }
}