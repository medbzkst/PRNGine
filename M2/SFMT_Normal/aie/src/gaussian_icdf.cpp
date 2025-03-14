#include <stdint.h>
#include <stdio.h>
#include <adf.h>
#include "aie_api/aie.hpp"
#include "aie_api/aie_adf.hpp"
#include "kernels.hpp"
#include "../../../../common/aie/routines.hpp"

#define A_1 -39.696830286653757
#define A_2 220.94609842452050
#define A_3 -275.92851044696869
#define A_4 138.35775186726900
#define A_5 -30.664798066147160
#define A_6 2.5066282774592392
#define B_1 -54.476098798224058
#define B_2 161.58583685804089
#define B_3 -155.69897985988661
#define B_4 66.801311887719720
#define B_5 -13.280681552885721

__attribute__((always_inline)) aie::vector<float, 4> inverseCumulativeNormalKernel(aie::vector<float, 4> input)
{
    aie::vector<float, 4> z = aie::sub(input, (float)0.5);

    aie::vector<float, 4> r = aie::mul(z, z);

    aie::vector<float, 4> res0 = aie::mul((float)A_1, r);
    res0 = aie::add((float)A_2, res0);
    res0 = aie::mul(res0, r);
    res0 = aie::add((float)A_3, res0);
    res0 = aie::mul(res0, r);
    res0 = aie::add((float)A_4, res0);
    res0 = aie::mul(res0, r);
    res0 = aie::add((float)A_5, res0);
    res0 = aie::mul(res0, r);
    res0 = aie::add((float)A_6, res0);
    res0 = aie::mul(res0, z);

    aie::vector<float, 4> res1 = aie::mul((float)B_1, r);
    res1 = aie::add((float)B_2, res1);
    res1 = aie::mul(res1, r);
    res1 = aie::add((float)B_3, res1);
    res1 = aie::mul(res1, r);
    res1 = aie::add((float)B_4, res1);
    res1 = aie::mul(res1, r);
    res1 = aie::add((float)B_5, res1);
    res1 = aie::mul(res1, r);
    res1 = aie::add((float)1.0, res1);
    res1 = aie::inv(res1);

    aie::vector<float, 4> res = aie::mul(res0, res1);
    return res;
}

void inverseCumulativeNormal(input_stream<int32> *restrict input_unif_rdn, output_stream<float> *restrict output_state)
{

    const int32 bound = readincr(input_unif_rdn);
    for (auto i = 0; i < bound; i++)
        chess_prepare_for_pipelining
        {
            aie::vector<int32, 4> uniform_number = readincr_v<4>(input_unif_rdn);
            aie::vector<float, 4> gaussian_number = inverseCumulativeNormalKernel(unsigned_to_float(uniform_number, 31));

            writeincr(output_state, gaussian_number);
        }
}