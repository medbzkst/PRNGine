#include <stdint.h>
#include <stdio.h>
#include <adf.h>
#include "aie_api/aie.hpp"
#include "aie_api/aie_adf.hpp"
#include "kernels.hpp"
#include "../../../../common/aie/routines.hpp"

void subsequent(input_stream<int32> *restrict input_unif_rdn, output_stream<float> *restrict output_state)
{

    const int32 bound = readincr(input_unif_rdn);
    for (auto i = 0; i < bound; i++)
        chess_prepare_for_pipelining
        {

            // Your code here
            // The input is a stream of 32-bit integers representing uniform random numbers
            // The output should be a stream of 32-bit floats representing the compute values of your sebsequent function
            // The loop bound is given by the first value of the input stream and should be kept as is to ensure correct functionality
        }
}