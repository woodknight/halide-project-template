#include "Halide.h"

namespace
{
using namespace Halide;

class HalideGaussianBlurGenerator : public Halide::Generator<HalideGaussianBlurGenerator>
{
public:
    Input<Buffer<uint8_t>>  input{"input", 2};
    Output<Buffer<uint8_t>> output{"output", 2};

    void generate()
    {
        Var x("x"), y("y");
        Func clamped = BoundaryConditions::repeat_edge(input);

        Func blur_x;
        blur_x(x, y) = (
            clamped(x - 2, y) 
            + clamped(x - 1, y) * 4
            + clamped(x, y) * 6
            + clamped(x + 1, y) * 4
            + clamped(x + 2, y)) / 16;

        output(x, y) = (
            blur_x(x - 2, y) 
            + blur_x(x - 1, y) * 4
            + blur_x(x, y) * 6
            + blur_x(x + 1, y) * 4
            + blur_x(x + 2, y)) / 16;

        // estimates
        input.set_estimates({{0, 640}, {0, 480}});
        output.set_estimates({{0, 640}, {0, 480}});
    }
};

}

HALIDE_REGISTER_GENERATOR(HalideGaussianBlurGenerator, halide_gaussian_blur)