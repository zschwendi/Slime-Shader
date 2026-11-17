#include "SlimeBridge.h"
#include "Slime_Shader.h"
#include <algorithm>
#include <cmath>

struct SlimeRenderer {
    SlimeShader shader;

    SlimeRenderer(int height, int width, double density, double speed)
        : shader(height, width, density, speed) {}
};

SlimeRenderer *slime_renderer_create(int height, int width,
                                     double density, double speed) {
    if (height < 1 || width < 1 || height > 2048 || width > 2048 ||
        !std::isfinite(density) || !std::isfinite(speed)) {
        return nullptr;
    }
    try {
        return new SlimeRenderer(height, width, density, speed);
    } catch (...) {
        return nullptr;
    }
}

void slime_renderer_destroy(SlimeRenderer *renderer) {
    delete renderer;
}

bool slime_renderer_copy_rgba(SlimeRenderer *renderer, double elapsed_seconds, bool goop,
                              uint8_t *destination, size_t capacity) {
    if (!renderer || !destination || !std::isfinite(elapsed_seconds)) {
        return false;
    }
    const int height = renderer->shader.getHeight();
    const int width = renderer->shader.getWidth();
    const size_t required = static_cast<size_t>(height) * width * 4;
    if (capacity < required) {
        return false;
    }
    try {
        if (goop)
            renderer->shader.RainbowGoop(elapsed_seconds);
        else
            renderer->shader.RainbowWave(elapsed_seconds);
        size_t offset = 0;
        for (int row = 0; row < height; ++row) {
            for (int column = 0; column < width; ++column) {
                for (int channel = 0; channel < 3; ++channel) {
                    const int value = renderer->shader.getChannel(row, column, channel);
                    destination[offset++] = static_cast<uint8_t>(
                        std::max(0, std::min(255, value)));
                }
                destination[offset++] = 255;
            }
        }
        return true;
    } catch (...) {
        return false;
    }
}
