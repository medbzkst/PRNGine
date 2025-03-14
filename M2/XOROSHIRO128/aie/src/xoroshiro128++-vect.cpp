
#include <stdint.h>
#include <stdio.h>
#include <adf.h>
#include "aie_api/aie.hpp"
#include "aie_api/aie_adf.hpp"
#include "kernels.hpp"
#include "../../../../common/aie/routines.hpp"

const uint32 pktType = 0;

/**
 * @brief Generates pseudo-random numbers using the XOROSHIRO128++ algorithm.
 *
 * This function implements the XOROSHIRO128++ algorithm to generate a sequence of pseudo-random numbers.
 * The algorithm uses a state vector of 2 elements, each containing 4 integers, to produce the random numbers.
 *
 * @param states Pointer to the input stream of initial state values. The input stream should
 *               provide at least 9 integers (2 vectors of 4 integers each plus 1 integer for length)
 *               to initialize the state and the length.
 * @param result Pointer to the output stream where the generated random numbers will be written.
 *               The function will write a number of random numbers equal to the length read from the input stream.
 *
 * The function reads the initial state values and the length from the input stream, then iteratively updates
 * the state and generates random numbers, which are written to the output stream.
 */
void xoroshiro128ppmvect(input_stream<int32> *restrict states, output_stream<int32> *restrict result)
{
    int len = readincr(states);

    aie::vector<int32, 4> s[2];

    s[0] = readincr_v<4>(states);
    s[1] = readincr_v<4>(states);

    aie::vector<int32, 4> s_tmp;
    aie::vector<int32, 4> value;

    const int bound = (len % 4 == 0) ? len / 4 : ((len / 4) + 1);
    writeincr(result, bound);
    for (int b = 0; b < bound; b++)
        chess_prepare_for_pipelining
        {
            value = aie::add(rotl_every64_in128<17>(aie::add(s[0], s[1])), s[0]);
            writeincr(result, value);
            s_tmp = aie::bit_xor(s[0], s[1]);
            s[0] = aie::bit_xor(aie::bit_xor(rotl_every64_in128<49>(s[0]), s_tmp), shl_every64_in128<21>(s_tmp));
            s[1] = rotl_every64_in128<28>(s_tmp);
        }
}