#pragma once

#include <adf.h>
#include "kernels.hpp"

#define COLS 40
#define ROWS 8
#define CU_PER_COL 4
#define ROWS_PER_CU 2

using namespace adf;

class graph_overlay : public graph
{
private:
    kernel krnl_rand[COLS][CU_PER_COL];
    kernel krnl_icdf[COLS][CU_PER_COL];

public:
    input_plio in_seeds[COLS][CU_PER_COL];
    output_plio out_rand[COLS][CU_PER_COL];

    graph_overlay()
    {
    input_streams:
    {
        for (int c = 0; c < COLS; c++)
            for (int r = 0; r < CU_PER_COL; r++)
            {
                in_seeds[c][r] = input_plio::create("in_seeds" + std::to_string(c) + "_" + std::to_string(r), adf::plio_32_bits, "../../data/in_seeds.txt");
            }
    }
    output_streams:
    {
        for (int c = 0; c < COLS; c++)
            for (int r = 0; r < CU_PER_COL; r++)
            {
                out_rand[c][r] = output_plio::create("out_rand" + std::to_string(c) + "_" + std::to_string(r), adf::plio_32_bits, "./data/out_rand" + std::to_string(c) + "_" + std::to_string(r) + ".txt");
            }
    }
    main_loop:
    {
        for (int col = 0; col < COLS; col++)
        {
            for (unsigned cu = 0; cu < CU_PER_COL; cu++)
            {
                    const unsigned row_of_rand = ROWS_PER_CU * cu + 0;
                    const unsigned row_of_icdf = ROWS_PER_CU * cu + 1;
                    /****************************************************** Boilerplate starts ******************************************************/
                    // Creating the kernels
                    krnl_rand[col][cu] = kernel::create(xorwow);
                    krnl_icdf[col][cu] = kernel::create(inverseCumulativeNormal);
                    // Sourcing the kernels
                    source(krnl_rand[col][cu]) = "xorwow.cpp";
                    source(krnl_icdf[col][cu]) = "gaussian_icdf.cpp";
                    // Specifying the location of the kernels
                    location<kernel>(krnl_rand[col][cu]) = tile(((int)(50-COLS)/2) + col, row_of_rand);
                    location<stack>(krnl_rand[col][cu]) = location<kernel>(krnl_rand[col][cu]);

                    location<kernel>(krnl_icdf[col][cu]) = tile(((int)(50-COLS)/2) + col, row_of_icdf);
                    location<stack>(krnl_icdf[col][cu]) = location<kernel>(krnl_icdf[col][cu]);
                    // Specifying the runtime
                    runtime<ratio>(krnl_rand[col][cu]) = 1;
                    runtime<ratio>(krnl_icdf[col][cu]) = 1;
                    /******************************************************* Boilerplate ends *******************************************************/
                    /******************************************** Internal and exteral connections start ********************************************/
                    // Connecting IOs of the CU graph
                    connect<stream>(in_seeds[col][cu].out[0], krnl_rand[col][cu].in[0]);
                    connect<stream>(krnl_rand[col][cu].out[0], krnl_icdf[col][cu].in[0]);
                    connect<stream>(krnl_icdf[col][cu].out[0], out_rand[col][cu].in[0]);
                    /********************************************* Internal and exteral connections end *********************************************/
                
            }
        }
    }
    };
};
