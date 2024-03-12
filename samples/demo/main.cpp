#include <iostream>
#include "application.h"
#include "color.h"

class Demo : public TSR::Application
{
public:
    Demo() : Application("Tiny Software Renderer", 640, 400) {}

protected:
    void OnInitialize() override 
    {
        DrawLine(0, 0, 640, 400, TSR::Color::Red);
        SubmitTexture();
    }

    void OnRender() override {}
    void OnShutdown() override {}

private:
    void DrawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, TSR::Color color)
    {
        bool steep = false;
        if(std::abs(x1 - x2) < std::abs(y1 - y2))
        {
            std::swap(x1, y1);
            std::swap(x2, y2);
            steep = true;
        }
        if(x1 > x2)
        {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }

        const int32_t dx = x2 - x1;
        const int32_t dy = y2 - y1;
        const int32_t deltaError = std::abs(dy) * 2;
        int32_t error = 0.0f;
        int32_t y = y1;

        for(int32_t x = x1; x <= x2; ++x)
        {
            if(steep)
            {
                SetPixel(y, x, color);
            }
            else
            {
                SetPixel(x, y, color);
            }

            error += deltaError;
            if(error > dx)
            {
                y += (y2 > y1) ? 1 : -1;
                error -= dx * 2;
            }
        }
    }
};

int main()
{
    try
    {
        Demo demo {};
        demo.Run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}