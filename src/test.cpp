#include <iostream>

#include "halide_benchmark.h"
#include "HalideBuffer.h"
#include "halide_gaussian_blur.h"

using namespace Halide::Runtime;
using namespace Halide::Tools;

int main()
{
    halide_set_num_threads(1);
    
    Buffer<uint8_t> input(640, 480);
    Buffer<uint8_t> output(640, 480);

    float t = benchmark(10000, 1, [&](){
        halide_gaussian_blur(input, output);
    });

    std::cout << "Time: " << t * 1000 << " ms" << std::endl;

    return 0;
}