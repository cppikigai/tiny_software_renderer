#include "renderer.h"
#include <iostream>

namespace TSR
{
    Renderer::Renderer(int32_t width, int32_t height)
    : m_width(width)
    , m_height(height)
    , m_ready(false)
    , m_textureID(0)
    , m_shaderProgram(0)
    {
        m_pixels.resize(m_width * m_height * 3, 0);
    }

    Renderer::~Renderer()
    {
        Shutdown();
    }

    void Renderer::SetPixel(int32_t x, int32_t y, Color color)
    {
        m_ready = false;
        if (x >= 0 && x < m_width && y >= 0 && y < m_height)
        {
            int index = (y * m_width + x) * 3;
            m_pixels[index] = color.r;
            m_pixels[index + 1] = color.g;
            m_pixels[index + 2] = color.b;
        }
    }

    void Renderer::UpdateTexture()
    {
        glBindTexture(GL_TEXTURE_2D, m_textureID);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, GL_RGB, GL_UNSIGNED_BYTE, m_pixels.data());
        m_ready = true;
    }

    void Renderer::Render()
    {
        if (!IsReady())
        {
            std::cerr << "Renderer is not ready. Call Initialize before rendering." << std::endl;
            return;
        }

        glUseProgram(m_shaderProgram);
        glBindTexture(GL_TEXTURE_2D, m_textureID);

        // Render quad
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void Renderer::Initialize()
    {
        // Load shaders
        std::string vertexShaderSource = R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec2 aTexCoord;
            out vec2 TexCoord;
            void main()
            {
                gl_Position = vec4(aPos, 1.0);
                TexCoord = aTexCoord;
            }
        )";

        std::string fragmentShaderSource = R"(
            #version 330 core
            out vec4 FragColor;
            in vec2 TexCoord;
            uniform sampler2D textureSampler;

            void main()
            {
                FragColor = texture(textureSampler, TexCoord);
            }
        )";

        GLuint vertexShader, fragmentShader;
        GLint success;
        GLchar infoLog[512];

        // Vertex Shader
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const GLchar* vShaderCode = vertexShaderSource.c_str();
        glShaderSource(vertexShader, 1, &vShaderCode, NULL);
        glCompileShader(vertexShader);
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cerr << "Vertex shader compilation failed: " << infoLog << std::endl;
        }

        // Fragment Shader
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        const GLchar* fShaderCode = fragmentShaderSource.c_str();
        glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
        glCompileShader(fragmentShader);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cerr << "Fragment shader compilation failed: " << infoLog << std::endl;
        }

        // Shader Program
        m_shaderProgram = glCreateProgram();
        glAttachShader(m_shaderProgram, vertexShader);
        glAttachShader(m_shaderProgram, fragmentShader);
        glLinkProgram(m_shaderProgram);
        glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
            std::cerr << "Shader program linking failed: " << infoLog << std::endl;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        // Setup quad VAO
        GLfloat vertices[] = 
        {
            // Positions        // Texture Coords
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
            1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 0.0f, 1.0f, 0.0f
        };

        GLuint indices[] =
        {
            0, 1, 2,
            1, 3, 2
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // Create and bind the texture
        glGenTextures(1, &m_textureID);
        glBindTexture(GL_TEXTURE_2D, m_textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_pixels.data());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        m_ready = true;
    }

    void Renderer::Shutdown()
    {
        glDeleteTextures(1, &m_textureID);
        glDeleteProgram(m_shaderProgram);
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        m_ready = false;
    }

    bool Renderer::IsReady() const
    {
        return m_ready;
    }
}