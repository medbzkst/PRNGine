
#include <stdint.h>
#include <stdio.h>
#include <adf.h>
#include "aie_api/aie.hpp"
#include "aie_api/aie_adf.hpp"
#include "kernels.hpp"
#include "../../../../common/aie/routines.hpp"

const uint32 pktType = 0;

/**
 * @brief Generates pseudo-random numbers using the XORWOW algorithm.
 *
 * This function implements the XORWOW (XOR shift with Weyl sequence) algorithm to generate
 * a sequence of pseudo-random numbers. The algorithm uses a state vector of 5 elements
 * and a counter to produce the random numbers.
 *
 * @param states Pointer to the input stream of initial state values. The input stream should
 *               provide at least 21 integers (5 vectors of 4 integers each plus 1 integer for length)
 *               to initialize the state and the length.
 * @param result Pointer to the output stream where the generated random numbers will be written.
 *               The function will write a number of random numbers equal to the length read from the input stream.
 *
 * The function reads the initial state values and the length from the input stream, then iteratively updates
 * the state and generates random numbers, which are written to the output stream.
 */
void xorwow(input_stream<int32> * restrict states, output_stream<int32> * restrict result)
{
    int len = readincr(states);

    aie::vector<int32, 4> s[5];

    s[0] = readincr_v<4>(states);
    s[1] = readincr_v<4>(states);
    s[2] = readincr_v<4>(states);
    s[3] = readincr_v<4>(states);
    s[4] = readincr_v<4>(states);
    int32 cnt = 0;

    aie::vector<int32, 4> s_tmp;
    aie::vector<int32, 4> value;

    const int bound = (len % 4 == 0) ? len / 4 : ((len / 4) + 1);
    writeincr(result, bound);
    for (int b = 0; b < bound; b++)
        chess_prepare_for_pipelining
        {
            cnt += 362437;
            value = s[4];
            value = aie::bit_xor(value, aie::downshift(value, 2));
            value = aie::bit_xor(value, aie::upshift(value, 1));
            value = aie::bit_xor(value, aie::bit_xor(s[0], aie::upshift(s[0], 4)));
            value = aie::add(cnt, value);
            writeincr(result, value);

            s[4] = s[3];
            s[3] = s[2];
            s[2] = s[1];
            s[1] = s[0];

            s[0] = value;
        }
}