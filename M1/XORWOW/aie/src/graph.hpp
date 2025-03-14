#pragma once

#include <adf.h>
#include "kernels.hpp"

#define COLS 40
#define ROWS 8
#define PACKETS_PER_COL 4
#define ROWS_PER_PACKET 2

using namespace adf;

class graph_overlay : public graph
{
private:
    kernel krnl[COLS][ROWS];

public:
    input_plio in_seeds[COLS][PACKETS_PER_COL];
    output_plio out_rand[COLS][PACKETS_PER_COL];

    pktsplit<ROWS_PER_PACKET> pkt_in_seeds[COLS][PACKETS_PER_COL];
    pktmerge<ROWS_PER_PACKET> pkt_out_rand[COLS][PACKETS_PER_COL];
    graph_overlay()
    {
    input_streams:
    {
        for (int c = 0; c < COLS; c++)
            for (int r = 0; r < PACKETS_PER_COL; r++)
            {
                in_seeds[c][r] = input_plio::create("in_seeds" + std::to_string(c) + "_" + std::to_string(r), adf::plio_32_bits, "../../data/in_seeds.txt");
            }
    }
    output_streams:
    {
        for (int c = 0; c < COLS; c++)
            for (int r = 0; r < PACKETS_PER_COL; r++)
            {
                out_rand[c][r] = output_plio::create("out_rand" + std::to_string(c) + "_" + std::to_string(r), adf::plio_32_bits, "./data/out_rand.txt" + std::to_string(c) + "_" + std::to_string(r));
            }
    }
    main_loop:
    {
        for (int col = 0; col < COLS; col++)
        {
            for (unsigned subcol_sec = 0; subcol_sec < PACKETS_PER_COL; subcol_sec++)
            {
                pkt_in_seeds[col][subcol_sec] = pktsplit<ROWS_PER_PACKET>::create();

                pkt_out_rand[col][subcol_sec] = pktmerge<ROWS_PER_PACKET>::create();

                for (unsigned row = 0; row < ROWS_PER_PACKET; row++)
                {
                    const unsigned r = ROWS_PER_PACKET * subcol_sec + row;
                    /****************************************************** Boilerplate starts ******************************************************/
                    // Creating the kernels
                    krnl[col][r] = kernel::create(xorwow);
                    // Sourcing the kernels
                    source(krnl[col][r]) = "xorwow.cpp";
                    location<kernel>(krnl[col][r]) = tile(((int)(50-COLS)/2) + col, r);
                    location<stack>(krnl[col][r]) = location<kernel>(krnl[col][r]);
                    location<buffer>(krnl[col][r].in[0]) = location<kernel>(krnl[col][r]);
                    // Specifying the runtime
                    runtime<ratio>(krnl[col][r]) = 1;
                    /******************************************************* Boilerplate ends *******************************************************/
                    /******************************************** Internal and exteral connections start ********************************************/
                    // Connecting IOs of the CU graph
                    connect<pktstream, window<STATES * vSIZE * sizeof(vSTATES_T)>>(pkt_in_seeds[col][subcol_sec].out[row], krnl[col][r].in[0]);
                    connect<pktstream,                                  pktstream>(krnl[col][r].out[0], pkt_out_rand[col][subcol_sec].in[row]);
                    /********************************************* Internal and exteral connections end *********************************************/
                }
            }
        }
    }
    unpacking_seeds: 
    {
        for (int c = 0; c < COLS; c++)
            for (int r = 0; r < PACKETS_PER_COL; r++)
            {
                connect<pktstream>(in_seeds[c][r].out[0], pkt_in_seeds[c][r].in[0]);
            }
    }
    packing_output:
    {
        for (int c = 0; c < COLS; c++)
            for (int r = 0; r < PACKETS_PER_COL; r++)
            {
                connect<pktstream>(pkt_out_rand[c][r].out[0], out_rand[c][r].in[0]);
            }
    }
    };
};
