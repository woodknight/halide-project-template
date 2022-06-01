#include <iostream>

#include "gaussian_blur/halide_gaussian_blur_wrapper.h"
#include "utils/timer.h"

int main()
{
    

    int w = 640;
    int h = 480;
    
    uint8_t* input = new uint8_t[w * h];
    uint8_t* output = new uint8_t[w * h];

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            *(input + y * w + x) = uint8_t(float(rand()) / float(RAND_MAX) * 255);
        }
    }

    Timer timer;
    float best_time = 1e9;
    for(int i = 0; i < 1000; i++) {
        timer.reset();
        halide_gaussian_blur_wrapper(input, output, w, h);
        float time = timer.elapsedUs();
        if (time < best_time) {
            best_time = time;
        }
    }

    std::cout << "Time: " << best_time << " us" << std::endl;

    return 0;
}