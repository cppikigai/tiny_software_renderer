#include "color.h"

namespace TSR
{
    const Color Color::Black(0, 0, 0);
    const Color Color::White(255, 255, 255);
    const Color Color::Red(255, 0, 0);
    const Color Color::Green(0, 255, 0);
    const Color Color::Blue(0, 0, 255);
    const Color Color::Yellow(255, 255, 0);
    const Color Color::Cyan(0, 255, 255);
    const Color Color::Magenta(255, 0, 255);

    bool Color::operator==(const Color& other) const
    {
        return r == other.r && g == other.g && b == other.b;
    }

    bool Color::operator!=(const Color& other) const
    {
        return !(*this == other);
    }
}