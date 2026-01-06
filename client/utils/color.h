#pragma once

struct Color {
    union {
        struct { float r, g, b, a; };
        float rgba[4];
    };

    Color() : r(0), g(0), b(0), a(255) {}
    Color(float r, float g, float b, float a = 255) : r(r), g(g), b(b), a(a) {}
};