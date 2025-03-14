
#pragma once
#include <adf.h>
#include "aie_api/aie_adf.hpp"
#include "aie_api/aie.hpp"

#define STATES 5
#define vSTATES_T int32
#define vSIZE 4

void xorwow(input_stream<int32> * restrict states, output_stream<int32> * restrict result);
void inverseCumulativeNormal(input_stream<int32> *restrict input_unif_rdn, output_stream<float> *restrict output_state);