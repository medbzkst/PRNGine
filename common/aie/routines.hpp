#pragma once // This is to avoid multiple inclusion of this file
#include <stdint.h> // This is for the integer types
#include <stdio.h> // This is for the printf function
#include <adf.h> // This is for the ADF functions
#include "aie_api/aie.hpp" // This is for the AIE functions
#include "aie_api/aie_adf.hpp" // This is for the AIE ADF functions

template <typename T, typename... Types>
concept IsOneOf = (std::is_same_v<T, Types> || ...); // This is to check if the type is one of the types in the list

// template <typename T>
// void printBinary(T num) 
// { // This is for debug and can be removed in prod
//     for (int i = sizeof(num) * 8 - 1; i >= 0; --i)
//     {
//         printf("%u", ((num >> i) & 1));
//         if (i % 8 == 0)
//             printf(" ");
//     }
// }

template <typename T, unsigned Elems>
    requires IsOneOf<T, int32, cint32>
__attribute__((always_inline)) auto negative_to_float(const aie::vector<T, Elems> &v, int shift = 0)
{
    aie::vector<T, Elems> u_shift_value = aie::bit_and(0x007FFFFF, (aie::vector<T, Elems>)aie::downshift(v, 9));

    return aie::to_float(u_shift_value, shift - 8);
}

template <typename T, unsigned Elems>
    requires IsOneOf<T, int32, cint32>
__attribute__((always_inline)) auto unsigned_to_float(const aie::vector<T, Elems> &v, int shift = 0)
{
    aie::vector<float, Elems> negative_floatted = negative_to_float(v, shift);

    aie::vector<float, Elems> floatted = aie::to_float(v, shift);

    aie::mask<Elems> msk_lt = aie::lt(v, aie::zeros<int32, 4>());

    return (aie::vector<float, Elems>)aie::select(floatted, negative_floatted, msk_lt);
}

// void testing_unsigned_to_float()
// {

//     alignas(aie::vector_decl_align) int32 values_in_array[4] = {(int32)0x80000000, (int32)0x8FFFFFFF, (int32)-619201654, (int32)0x7FFFFFFF};

//     aie::vector<int32, 4> value = aie::load_v<4>(values_in_array);

//     printf("Unsigned interpretation of %d is: %u\n", (int32)value[0], (int32)value[0]);

//     printBinary<int32>(value[0]);

//     printf(" : is its binary.\n");

//     aie::vector<int32, 4> s_shift_value = aie::downshift(value, 9);

//     printBinary<int32>(s_shift_value[0]);

//     printf(" : is the binary of its shifted version, without masking\n");

//     aie::vector<int32, 4> u_shift_value = aie::bit_and(0x007FFFFF, (aie::vector<int32, 4>)aie::downshift(value, 9));

//     printBinary<int32>(u_shift_value[0]);
//     printf(" : is the shifted version, with masking\n\n");

//     printBinary<int32>(value[3]);
//     printf(" : is the binary of what its unsigned interpretation is %d and Hex is: 0x%x\n", (int32)value[3], (int32)value[3]);

//     aie::vector<float, 4> testing_floatted_test = unsigned_to_float(value, 31);

//     printf("\nTesting what 0 float looks like: %f\n", (float)testing_floatted_test[0]);
//     printf("\nTesting what 1 float looks like: %f\n", (float)testing_floatted_test[1]);
//     printf("\nTesting what 2 float looks like: %f\n", (float)testing_floatted_test[2]);
//     printf("\nTesting what 3 float looks like: %f\n", (float)testing_floatted_test[3]);
// }


alignas(aie::vector_decl_align) int32 F0F0_in_array[4] = {static_cast<int32>(0xFFFFFFFF), static_cast<int32>(0x00000000), static_cast<int32>(0xFFFFFFFF), static_cast<int32>(0x00000000)};

inline aie::vector<int32, 4> swap_low_per64bit_in128(aie::vector<int32, 4> x)
{
    aie::vector<int32, 4> F0F0 = aie::load_v<4>(F0F0_in_array);
    return aie::bit_and(aie::shuffle_down_rotate(x, 1), aie::bit_not(F0F0)); // {0, low0, 0, low1}   for x = {low0, high0, low1, high1}
}

inline aie::vector<int32, 4> swap_high_per64bit_in128(aie::vector<int32, 4> x)
{
    aie::vector<int32, 4> F0F0 = aie::load_v<4>(F0F0_in_array);
    return aie::bit_and(aie::shuffle_up_rotate(x, 1), F0F0); // {high0, 0, high1, 0} for x = {low0, high0, low1, high1}
}

inline aie::vector<int32, 4> swap_high_low_per64bit(aie::vector<int32, 4> x)
{
    return aie::bit_or(swap_high_per64bit_in128(x), swap_low_per64bit_in128(x));
}

template <int k>
inline aie::vector<int32, 4> rotl_every64_in128(aie::vector<int32, 4> x)
{
    aie::vector<int32, 4> v1, v2;
    if (k < 32)
    {
        v1 = aie::upshift(x, k);
        v2 = aie::downshift(x, 32 - k);
    }
    else
    {
        v2 = aie::upshift(x, k - 32); // k - 32 comes from 32 - (64 - k)
        v1 = aie::downshift(x, 64 - k);
    }
    return aie::bit_or(v1, swap_high_low_per64bit(v2));
}

template <int k>
inline aie::vector<int32, 4> shl_every64_in128(aie::vector<int32, 4> x)
{
    aie::vector<int32, 4> v1, v2;

    if (k < 32)
    {
        v1 = aie::upshift(x, k);
        v2 = aie::downshift(x, 32 - k);
    }
    else
    {
        v2 = aie::upshift(x, k - 32);   // k - 32 comes from 32 - (64 - k)
        v1 = aie::broadcast<int, 4>(0); // This is because it is shifted more 32 bits, therfore it becomes all zeros
    }
    return aie::bit_or(v1, swap_low_per64bit_in128(v2));
}

template <int k>
inline aie::vector<int32, 4> shr_every64_in128(aie::vector<int32, 4> x)
{
    aie::vector<int32, 4> v1, v2;

    if (k < 32)
    {
        v1 = aie::downshift(x, k);
        v2 = aie::upshift(x, 32 - k);
    }
    else
    {
        v2 = aie::downshift(x, k - 32); // k - 32 comes from 32 - (64 - k)
        v1 = aie::broadcast<int, 4>(0); // This is because it is shifted more 32 bits, therfore it becomes all zeros
    }
    return aie::bit_or(v1, swap_high_per64bit_in128(v2));
}



inline aie::vector<int32, 4> shl_128bit(aie::vector<int32, 4> v0, int shift)
{
    aie::vector<int32, 4> A = aie::upshift(v0, shift);
    aie::vector<int32, 4> Ap = aie::shuffle_down_fill(v0, aie::zeros<int32, 4>(), 1);
    aie::vector<int32, 4> App = aie::downshift(Ap, (32 - shift));
    A = aie::bit_or(A, App);
    return A;
}

inline aie::vector<int32, 4> shr_128bit(aie::vector<int32, 4> r1, int shift)
{
    aie::vector<int32, 4> C = aie::downshift(r1, shift);
    aie::vector<int32, 4> Cp = aie::shuffle_up_fill(r1, aie::zeros<int32, 4>(), 1);
    aie::vector<int32, 4> Cpp = aie::upshift(Cp, (32 - shift));
    C = aie::bit_or(C, Cpp);
    return C;
}