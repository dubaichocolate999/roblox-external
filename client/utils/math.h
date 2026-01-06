#pragma once

// math utils...
#include <cmath>
#include <random>
#include "vector.h"

#define M_PI   3.14159265358979323846264338327950288

namespace math {

    // sometimes it's a trng.
    static std::mt19937& get_random() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }

    static double getPI() {
        // returns PI.
        return M_PI;
    }

    // rounds the number to the closest it can.
    static double round(double value, int precision) {
        int scale = std::pow(10, precision);
        return std::round(value * scale) / scale;
    }

    // interpolates between 2 values.
    static double interpolate(double value, double newValue, double interpolation) {
        return (value + (newValue - value) * interpolation);
    }

    // tries to get a random number between x and y.
    static double random(double min, double max) {
        static std::mt19937& gen = get_random();
        std::uniform_real_distribution<double> dist(min, max);
        return dist(gen);
    }

    static vector_3 subtract_vectors(vector_3 first, vector_3 second) {
        return { first.x - second.x, first.y - second.y, first.z - second.z };
    }

    static float distance(const vector_3& a, const vector_3& b) {
        float dx = a.x - b.x;
        float dy = a.y - b.y;
        float dz = a.z - b.z;
        return sqrtf(dx * dx + dy * dy + dz * dz);
    }

    inline float lerp(float delta, float start, float end) {
        return start + delta * (end - start);
    }

    inline vector_3 lerp_vec3(float delta, const vector_3& start, const vector_3& end) {
        return {
            lerp(delta, start.x, end.x),
            lerp(delta, start.y, end.y),
            lerp(delta, start.z, end.z)
        };
    }
}