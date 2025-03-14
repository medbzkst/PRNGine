
#pragma once
#include <adf.h>
#include "aie_api/aie_adf.hpp"
#include "aie_api/aie.hpp"

#define STATES 2
#define vSTATES_T int32
#define vSIZE 4

void xoroshiro128ppmvect(input_window<int32> * restrict states, output_pktstream * restrict result);