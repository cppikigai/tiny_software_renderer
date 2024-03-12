#ifndef TSR_RENDERER_H
#define TSR_RENDERER_H

#include <vector>
#include <cstdint>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "color.h"

namespace TSR
{
    class Renderer
    {
    public:
        Renderer(int32_t width, int32_t height);
        ~Renderer();

        void SetPixel(int32_t x, int32_t y, Color color);
        void UpdateTexture();
        void Render();
        void Initialize();
        void Shutdown();
        bool IsReady() const;

    private:
        int32_t m_width;
        int32_t m_height;
        bool m_ready;
        std::vector<uint8_t> m_pixels;
        uint32_t m_textureID;
        uint32_t m_shaderProgram;
        uint32_t VAO;
        uint32_t VBO;
        uint32_t EBO;
    };
}

#endif // !TSR_RENDERER_H