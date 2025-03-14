#include <stdint.h>
#include <stdio.h>
#include <adf.h>
#include "aie_api/aie.hpp"
#include "aie_api/aie_adf.hpp"
#include "kernels.hpp"
#include "../../../../common/aie/routines.hpp"

#define M 122                 // Middle point (custom value for SFMT)
#define SFMT_MSK1 0xdfffffefU // Mask for vectorized AND operation
#define SFMT_MSK2 0xddfecb7fU // Mask for vectorized AND operation
#define SFMT_MSK3 0xbffaffffU // Mask for vectorized AND operation
#define SFMT_MSK4 0xbffffff6U // Mask for vectorized AND operation
#define SHIFT_L 8             // Left shift amount for 128-bit integers
#define SHIFT_R 11            // Right shift amount for 32-bit integers
#define N 156                 // Degree of recursion (19937/128)

alignas(aie::vector_decl_align) static int32 MASK[4] = {static_cast<int32>(SFMT_MSK1), static_cast<int32>(SFMT_MSK2), static_cast<int32>(SFMT_MSK3), static_cast<int32>(SFMT_MSK4)};
const uint32 pktType = 0;

/**
 * @brief Implementation of SIMD-oriented Fast Mersenne Twister (SFMT) for AIE.
 *
 * This file contains the implementation of the SFMT algorithm optimized for AIE using SIMD ops.
 *
 * @details
 * The implementation uses a circular buffer to manage the state array and perform the
 * SFMT recursion. The state array is initialized and updated using SIMD operations to
 * leverage the parallel processing capabilities of AIE.
 *
 * The key parameters and constants used in the implementation are:
 * - M: Middle point for the SFMT algorithm.
 * - SFMT_MSK1, SFMT_MSK2, SFMT_MSK3, SFMT_MSK4: Masks for vectorized AND operations.
 * - SHIFT_L: Left shift amount for 128-bit integers.
 * - SHIFT_R: Right shift amount for 32-bit integers.
 * - N: Degree of recursion (19937/128).
 *
 * The main function `sfmt` performs the following steps:
 * 1. Reads the length of the state array from the input stream.
 * 2. Initializes the state array by reading values from the input stream.
 * 3. Sets up a circular iterator for the state buffer.
 * 4. Loads initial values into cached registers for faster access.
 * 5. Iterates over blocks and performs the SFMT recursion using SIMD operations.
 * 6. Updates the state array and writes the results to the output stream.
 *
 * @note
 * The implementation uses a circular iterator for the state buffer to manage the state
 * array efficiently. However, direct access to the state buffer is used in some cases
 * for better readability and debuggability.
 *
 * @param states Input stream containing the initial state array.
 * @param result Output stream to store the generated pseudorandom numbers.
 */
void sfmt(input_stream<int32> *restrict states, output_stream<int32> *restrict result)
{
    const int32 len = readincr(states);

    alignas(aie::vector_decl_align) int32 s[N * 4];

    for (int i = 0; i < 4 * N; i++)
        s[i] = readincr(states); // _INIT_STATE_BUFF_

    aie::vector<int32, 4> vMASK = *(reinterpret_cast<aie::vector<int32, 4> *>(MASK));

    // HERE IS A VERY VERY VERY IMPORTANT NOTE!!!
    // This circular iterator is used for two reasons:
    // 1 - Initialise the state buffer declared above (lookup comment: _INIT_STATE_BUFF_)
    // 2 - Update its values throughout the iterations (lookup comment: _UPDATE_STATE_BUFF_)
    // However
    // HOWEVER !
    // HOWEVER !!
    // HOWEVER !!
    // HOWEVER !!!
    // HOW !! EV !! ER !!!!!
    // The state buffer, although could be access using this iterator, it's not (lookup comment: _ACCESS_STATE_BUFF_).
    // This is even though the fourth (read) access uses the modulo to mimic what a circular buffer does.
    // The reason is: It's a crazy mess and unreadable and not easily debuggable to use as it initializes r1 and r2 then
    // goes to the i-th iteration then jumps M steps ahead and then gets back for storing. We can do this but this prevents
    // the reusability of this code. SO PLEASE PROCEED WITH CAUTION!!
    auto states_v_c = aie::begin_vector_circular<4, N * 4>(s); // Circular iterator for the state buffer // _INIT_STATE_BUFF_

    aie::vector<int32, 4> r1 = aie::load_v<4>(s + 4 * (N - 2)); // Cached register for faster access // _ACCESS_STATE_BUFF_
    aie::vector<int32, 4> r2 = aie::load_v<4>(s + 4 * (N - 1)); // Cached register for faster access // _ACCESS_STATE_BUFF_

    const int32 bound = (len % 4 == 0) ? len / 4 : ((len / 4) + 1);
    writeincr(result, bound); // Write the loop bound to the output stream for the next stage
    for (int ii = 0; ii < bound; ii++)
        chess_prepare_for_pipelining
        {
            const int i = (ii & 0xFF) >= N ? (ii & 0xFF) - N : (ii & 0xFF); // The trick is used to avoid using modulo.
            // Load two 128-bit vectors from the state array
            aie::vector<int32, 4> v0 = aie::load_v<4>(s + 4 * i);                             // _ACCESS_STATE_BUFF_
            const int ipos = ((i + M) & 0xFF) >= N ? ((i + M) & 0xFF) - N : ((i + M) & 0xFF); // The trick is used to avoid using modulo.
            aie::vector<int32, 4> vM = aie::load_v<4>(s + 4 * ipos);                          // _ACCESS_STATE_BUFF_

            // Perform the SIMD-based recursion

            // We want to compute wA = (w << 8) ^ w but since the shift ops here are per 32-bits we use do more
            aie::vector<int32, 4> A = shl_128bit(v0, SHIFT_L);
            A = aie::bit_xor(A, v0);

            aie::vector<int32, 4> B = aie::downshift(vM, SHIFT_R); // wD = w >> 11 per 32-bits
            B = aie::bit_and(vMASK, B);

            // We want to compute wA = (w >> 8) ^ w but since the shift ops here are per 32-bits we use do more
            aie::vector<int32, 4> C = shr_128bit(r1, SHIFT_L);

            aie::vector<int32, 4> D = aie::upshift(r2, 18); // wD = w << 18 per 32-bits

            // Update r1 and r2 for the next iteration
            r1 = r2;
            r2 = aie::bit_xor(A, aie::bit_xor(B, aie::bit_xor(C, D))); // Final result of SFMT recursion for the next state
            writeincr(result, r2);                                     // Write the result to the output stream

            // Store the result back to the state array
            *states_v_c++ = r2; // This assumed to start from 0 and to circulate the moment it should. If you chnaged anything make sure it's not broken // _UPDATE_STATE_BUFF_
        }
}