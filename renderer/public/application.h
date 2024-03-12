#ifndef TSR_APPLICATION_H
#define TSR_APPLICATION_H

#include <string>
#include <cstdint>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer.h"

namespace TSR
{
    class Application
    {
    public:
        Application(const std::string& title, int32_t width, int32_t height);
        virtual ~Application() = default;
        void Run();

    protected:
        virtual void OnInitialize() = 0;
        virtual void OnRender() = 0;
        virtual void OnShutdown() = 0;

        void SetPixel(int32_t x, int32_t y, Color color);
        void SubmitTexture();

    private:
        void Initilalize();
        void Render();
        void Shutdown();

    private:
        std::string m_title;
        int32_t m_width;
        int32_t m_height;

        bool m_isRunning;

        GLFWwindow* m_window {nullptr};
        std::unique_ptr<Renderer> m_renderer;
    };
}

#endif // !TSR_APPLICATION_H