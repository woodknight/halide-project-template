#include "halide_gaussian_blur_wrapper.h"
#include "HalideBuffer.h"
#include "halide_gaussian_blur.h"

void halide_gaussian_blur(
    uint8_t* input,
    uint8_t* output,
    int32_t width,
    int32_t height)
{
    halide_set_num_threads(1);
    Halide::Runtime::Buffer<uint8_t> input_buffer(input, width, height);
    Halide::Runtime::Buffer<uint8_t> output_buffer(output, width, height);
    halide_gaussian_blur(input_buffer, output_buffer);    
}