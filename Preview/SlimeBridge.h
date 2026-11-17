#pragma once
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SlimeRenderer SlimeRenderer;

SlimeRenderer *slime_renderer_create(int height, int width,
                                     double density, double speed);
void slime_renderer_destroy(SlimeRenderer *renderer);

// The caller owns the buffer. Each pixel uses four bytes: red, green, blue, alpha.
// Time is in seconds, matching SlimeShader::RainbowWave.
bool slime_renderer_copy_rgba(SlimeRenderer *renderer, double elapsed_seconds,
                              uint8_t *destination, size_t capacity);

#ifdef __cplusplus
}
#endif
