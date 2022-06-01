#include "Halide.h"

namespace
{
using namespace Halide;
using namespace Halide::ConciseCasts;

class HalideGaussianBlurGenerator : public Halide::Generator<HalideGaussianBlurGenerator>
{
public:
    Input<Buffer<uint8_t>>  input{"input", 2};
    Output<Buffer<uint8_t>> blur_y{"output", 2};

    void generate()
    {
        Var x("x"), y("y");
        Func clamped = BoundaryConditions::repeat_edge(input);
        
        Func clamped_f;
        clamped_f(x, y) = cast<uint16_t>(clamped(x, y));

        Func blur_x;
        blur_x(x, y) = (
              clamped_f(x - 2, y) 
            + clamped_f(x - 1, y) * 4
            + clamped_f(x,     y) * 6
            + clamped_f(x + 1, y) * 4
            + clamped_f(x + 2, y)) / 16;

        blur_y(x, y) = u8_sat((
              blur_x(x, y - 2) 
            + blur_x(x, y - 1) * 4
            + blur_x(x, y    ) * 6
            + blur_x(x, y + 1) * 4
            + blur_x(x, y + 2)) / 16);

        // estimates
        input.set_estimates({{0, 640}, {0, 480}});
        blur_y.set_estimates({{0, 640}, {0, 480}});

        if(!auto_schedule)
        {
            Var xi, yi;
            const auto vec = natural_vector_size<uint16_t>();
            blur_y.compute_root().vectorize(x, vec);
            blur_x.store_at(blur_y, y).compute_at(blur_y, x).vectorize(x, vec);
        }
    }
};

}

HALIDE_REGISTER_GENERATOR(HalideGaussianBlurGenerator, halide_gaussian_blur)