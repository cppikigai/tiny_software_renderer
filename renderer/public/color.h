#ifndef TSR_COLOR_H
#define TSR_COLOR_H

#include <cstdint>

namespace TSR
{
    #pragma pack(push, 1)
    struct Color
    {
        uint8_t r {};
        uint8_t g {};
        uint8_t b {};

        Color() = default;
        Color(uint8_t red, uint8_t green, uint8_t blue)
        : r(red)
        , g(green)
        , b(blue) {}

        static const Color Black;
        static const Color White;
        static const Color Red;
        static const Color Green;
        static const Color Blue;
        static const Color Yellow;
        static const Color Cyan;
        static const Color Magenta;

        bool operator==(const Color& other) const;
        bool operator!=(const Color& other) const;
    };
    #pragma pack(pop)
}

#endif // !TSR_COLOR_H
