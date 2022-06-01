#include <iostream>

#include "HalideBuffer.h"
#include "halide_gaussian_blur.h"

#include "utils/timer.h"

using namespace Halide::Runtime;

int main()
{
    halide_set_num_threads(1);

    int w = 640;
    int h = 480;
    
    Buffer<uint8_t> input(w, h);
    Buffer<uint8_t> output(w, h);

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            input(x, y) = uint8_t(float(rand()) / float(RAND_MAX) * 255);
        }
    }

    Timer timer;
    float best_time = 1e9;
    for(int i = 0; i < 1000; i++) {
        timer.reset();
        halide_gaussian_blur(input, output);        
        float time = timer.elapsedMs();
        if (time < best_time) {
            best_time = time;
        }
    }

    std::cout << "Time: " << best_time << " ms" << std::endl;

    return 0;
}