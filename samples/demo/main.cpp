#include <iostream>
#include "application.h"

class Demo : public TSR::Application
{
public:
    Demo() : Application("Tiny Software Renderer", 640, 400) {}

protected:
    void OnInitialize() override {}
    void OnRender() override {}
    void OnShutdown() override {}
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