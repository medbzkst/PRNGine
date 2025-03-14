#include <cstring>
#include <fstream>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <iomanip>
#include <string>
#include <cmath>
#include "xrt.h"
#include "experimental/xrt_kernel.h"
#include <type_traits> // C++0x
#include "../aie/src/kernels.hpp"

uint32_t generateHeader(unsigned int pktType, unsigned int ID)
{
    uint32_t header = 0;
    header |= ID & 0x1F;
    header |= (0 & 0x7F) << 5;
    header |= (pktType & 0x7) << 12;
    header |= (0 & 0x1) >> 15;
    header |= (-1 & 0x1F) >> 16; // source row
    header |= (-1 & 0x7F) >> 21; // source column
    header |= (0 & 0x7) >> 28;
    uint32_t xor_result = 0;
    for (int i = 0; i <= 30; ++i)
    {
        xor_result ^= (header >> i) & 1;
    }
    header |= ((xor_result ^ 1) << 31);
    return header;
}

int main(int argc, char **argv)
{

    // Check input arguments
    if (argc < 2 || argc > 3)
    {
        std::cout << "Usage: " << argv[0] << " <XCLBIN File> [RNs = 1000]" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Open the device" << std::endl;
    auto device = xrt::device(0);
    std::string binaryFile = argv[1];
    std::cout << "Load the xclbin " << binaryFile << std::endl;
    auto uuid = device.load_xclbin(binaryFile);

    std::cout << "Get references to compute units" << std::endl;
    /******************************************************* pl_mm2s_40x *******************************************************/
    auto kernel_mm2s_in_seeds_block0 = xrt::kernel(device, uuid, "pl_mm2s_40x:{pl_mm2s_in_seeds_block0}");
    auto kernel_mm2s_in_seeds_block1 = xrt::kernel(device, uuid, "pl_mm2s_40x:{pl_mm2s_in_seeds_block1}");
    auto kernel_mm2s_in_seeds_block2 = xrt::kernel(device, uuid, "pl_mm2s_40x:{pl_mm2s_in_seeds_block2}");
    auto kernel_mm2s_in_seeds_block3 = xrt::kernel(device, uuid, "pl_mm2s_40x:{pl_mm2s_in_seeds_block3}");
    /***************************************************************************************************************************/
    /******************************************************* pl_s2mm_40x *******************************************************/
    auto kernel_out_result_block0 = xrt::kernel(device, uuid, "pl_s2mm_40x:{pl_s2mm_out_result_block0}");
    auto kernel_out_result_block1 = xrt::kernel(device, uuid, "pl_s2mm_40x:{pl_s2mm_out_result_block1}");
    auto kernel_out_result_block2 = xrt::kernel(device, uuid, "pl_s2mm_40x:{pl_s2mm_out_result_block2}");
    auto kernel_out_result_block3 = xrt::kernel(device, uuid, "pl_s2mm_40x:{pl_s2mm_out_result_block3}");
    /***************************************************************************************************************************/
    int size_seeds = STATES * vSIZE;
    long long size_out = argc == 3 ? std::stoi(argv[2]) : 1000;

    std::cout << "Lauching the accelerator for generating " << size_out << " random numbers" << std::endl;

    int *in_seeds_block0[40];
    int *in_seeds_block1[40];
    int *in_seeds_block2[40];
    int *in_seeds_block3[40];

    int *out_result_block0[40];
    int *out_result_block1[40];
    int *out_result_block2[40];
    int *out_result_block3[40];

    std::cout << "Creating host buffers of the following sizes: " << 2 * (size_seeds + 2) * sizeof(int) << " , " << 2 * (size_out + 1) * sizeof(int) << std::endl;

    for (auto cu = 0; cu < 40; cu++)
    {
        in_seeds_block0[cu] = (int *)malloc(2 * (size_seeds + 2) * sizeof(int));
        in_seeds_block1[cu] = (int *)malloc(2 * (size_seeds + 2) * sizeof(int));
        in_seeds_block2[cu] = (int *)malloc(2 * (size_seeds + 2) * sizeof(int));
        in_seeds_block3[cu] = (int *)malloc(2 * (size_seeds + 2) * sizeof(int));

        out_result_block0[cu] = (int *)malloc(2 * (size_out + 1) * sizeof(int));
        out_result_block1[cu] = (int *)malloc(2 * (size_out + 1) * sizeof(int));
        out_result_block2[cu] = (int *)malloc(2 * (size_out + 1) * sizeof(int));
        out_result_block3[cu] = (int *)malloc(2 * (size_out + 1) * sizeof(int));
    }

    std::cout << "Initializing input buffers" << std::endl;

    for (auto cu = 0; cu < 40; cu++)
    {
        for (auto pkt = 0; pkt < 2; pkt++)
        {
            in_seeds_block0[cu][pkt * (size_seeds + 2) + 0] = generateHeader(0, pkt); // Paket header
            in_seeds_block0[cu][pkt * (size_seeds + 2) + 1] = size_out;               // Output length
            in_seeds_block1[cu][pkt * (size_seeds + 2) + 0] = generateHeader(0, pkt); // Paket header
            in_seeds_block1[cu][pkt * (size_seeds + 2) + 1] = size_out;               // Output length
            in_seeds_block2[cu][pkt * (size_seeds + 2) + 0] = generateHeader(0, pkt); // Paket header
            in_seeds_block2[cu][pkt * (size_seeds + 2) + 1] = size_out;               // Output length
            in_seeds_block3[cu][pkt * (size_seeds + 2) + 0] = generateHeader(0, pkt); // Paket header
            in_seeds_block3[cu][pkt * (size_seeds + 2) + 1] = size_out;               // Output length
            for (int i = 0; i < size_seeds; i++)
            {
                in_seeds_block0[cu][pkt * (size_seeds + 2) + 2 + i] = 1234 + cu + pkt * size_seeds + 2 + i; // Seeds
                in_seeds_block1[cu][pkt * (size_seeds + 2) + 2 + i] = 1235 + cu + pkt * size_seeds + 2 + i; // Seeds
                in_seeds_block2[cu][pkt * (size_seeds + 2) + 2 + i] = 1236 + cu + pkt * size_seeds + 2 + i; // Seeds
                in_seeds_block3[cu][pkt * (size_seeds + 2) + 2 + i] = 1237 + cu + pkt * size_seeds + 2 + i; // Seeds
            }
        }
    }

    std::cout << "Creating device buffers" << std::endl;

    /***********************************/
    // The low and high seeds are separated in the input buffer
    // as a hacky way to avoid the need for another pl kernel recompilation
    xrt::bo in_seeds_block0_buff_low[40];
    xrt::bo in_seeds_block1_buff_low[40];
    xrt::bo in_seeds_block2_buff_low[40];
    xrt::bo in_seeds_block3_buff_low[40];

    xrt::bo in_seeds_block0_buff_high[40];
    xrt::bo in_seeds_block1_buff_high[40];
    xrt::bo in_seeds_block2_buff_high[40];
    xrt::bo in_seeds_block3_buff_high[40];
    /***********************************/

    xrt::bo out_result_block0_buff[40];
    xrt::bo out_result_block1_buff[40];
    xrt::bo out_result_block2_buff[40];
    xrt::bo out_result_block3_buff[40];

    for (auto cu = 0; cu < 40; cu++)
    {
        in_seeds_block0_buff_low[cu] = xrt::bo(device, (size_seeds + 2) * sizeof(int), kernel_mm2s_in_seeds_block0.group_id(cu));
        in_seeds_block1_buff_low[cu] = xrt::bo(device, (size_seeds + 2) * sizeof(int), kernel_mm2s_in_seeds_block1.group_id(cu));
        in_seeds_block2_buff_low[cu] = xrt::bo(device, (size_seeds + 2) * sizeof(int), kernel_mm2s_in_seeds_block2.group_id(cu));
        in_seeds_block3_buff_low[cu] = xrt::bo(device, (size_seeds + 2) * sizeof(int), kernel_mm2s_in_seeds_block3.group_id(cu));

        in_seeds_block0_buff_low[cu].write(in_seeds_block0[cu]);
        in_seeds_block0_buff_low[cu].sync(XCL_BO_SYNC_BO_TO_DEVICE);
        in_seeds_block1_buff_low[cu].write(in_seeds_block1[cu]);
        in_seeds_block1_buff_low[cu].sync(XCL_BO_SYNC_BO_TO_DEVICE);
        in_seeds_block2_buff_low[cu].write(in_seeds_block2[cu]);
        in_seeds_block2_buff_low[cu].sync(XCL_BO_SYNC_BO_TO_DEVICE);
        in_seeds_block3_buff_low[cu].write(in_seeds_block3[cu]);
        in_seeds_block3_buff_low[cu].sync(XCL_BO_SYNC_BO_TO_DEVICE);

        in_seeds_block0_buff_high[cu] = xrt::bo(device, (size_seeds + 2) * sizeof(int), kernel_mm2s_in_seeds_block0.group_id(cu));
        in_seeds_block1_buff_high[cu] = xrt::bo(device, (size_seeds + 2) * sizeof(int), kernel_mm2s_in_seeds_block1.group_id(cu));
        in_seeds_block2_buff_high[cu] = xrt::bo(device, (size_seeds + 2) * sizeof(int), kernel_mm2s_in_seeds_block2.group_id(cu));
        in_seeds_block3_buff_high[cu] = xrt::bo(device, (size_seeds + 2) * sizeof(int), kernel_mm2s_in_seeds_block3.group_id(cu));

        in_seeds_block0_buff_high[cu].write(((int *)(in_seeds_block0[cu]) + size_seeds + 2));
        in_seeds_block0_buff_high[cu].sync(XCL_BO_SYNC_BO_TO_DEVICE);
        in_seeds_block1_buff_high[cu].write(((int *)(in_seeds_block1[cu]) + size_seeds + 2));
        in_seeds_block1_buff_high[cu].sync(XCL_BO_SYNC_BO_TO_DEVICE);
        in_seeds_block2_buff_high[cu].write(((int *)(in_seeds_block2[cu]) + size_seeds + 2));
        in_seeds_block2_buff_high[cu].sync(XCL_BO_SYNC_BO_TO_DEVICE);
        in_seeds_block3_buff_high[cu].write(((int *)(in_seeds_block3[cu]) + size_seeds + 2));
        in_seeds_block3_buff_high[cu].sync(XCL_BO_SYNC_BO_TO_DEVICE);

        out_result_block0_buff[cu] = xrt::bo(device, 2 * (size_out + 1) * sizeof(int), kernel_out_result_block0.group_id(cu));
        out_result_block1_buff[cu] = xrt::bo(device, 2 * (size_out + 1) * sizeof(int), kernel_out_result_block1.group_id(cu));
        out_result_block2_buff[cu] = xrt::bo(device, 2 * (size_out + 1) * sizeof(int), kernel_out_result_block2.group_id(cu));
        out_result_block3_buff[cu] = xrt::bo(device, 2 * (size_out + 1) * sizeof(int), kernel_out_result_block3.group_id(cu));
    }

    std::cout << "Creating the runs" << std::endl;
    xrt::run run_kernel_mm2s_in_seeds_block0(kernel_mm2s_in_seeds_block0);
    xrt::run run_kernel_mm2s_in_seeds_block1(kernel_mm2s_in_seeds_block1);
    xrt::run run_kernel_mm2s_in_seeds_block2(kernel_mm2s_in_seeds_block2);
    xrt::run run_kernel_mm2s_in_seeds_block3(kernel_mm2s_in_seeds_block3);

    xrt::run run_kernel_out_result_block0(kernel_out_result_block0);
    xrt::run run_kernel_out_result_block1(kernel_out_result_block1);
    xrt::run run_kernel_out_result_block2(kernel_out_result_block2);
    xrt::run run_kernel_out_result_block3(kernel_out_result_block3);
    /********************** */

    std::cout << "Launching" << std::endl;
    std::chrono::duration<double> fpga_duration = std::chrono::nanoseconds::zero();

    for (auto cu = 0; cu < 40; cu++)
    {
        run_kernel_mm2s_in_seeds_block0.set_arg(cu, in_seeds_block0_buff_low[cu]);
        run_kernel_mm2s_in_seeds_block0.set_arg(80 + cu, (size_seeds + 2));

        run_kernel_mm2s_in_seeds_block1.set_arg(cu, in_seeds_block1_buff_low[cu]);
        run_kernel_mm2s_in_seeds_block1.set_arg(80 + cu, (size_seeds + 2));

        run_kernel_mm2s_in_seeds_block2.set_arg(cu, in_seeds_block2_buff_low[cu]);
        run_kernel_mm2s_in_seeds_block2.set_arg(80 + cu, (size_seeds + 2));

        run_kernel_mm2s_in_seeds_block3.set_arg(cu, in_seeds_block3_buff_low[cu]);
        run_kernel_mm2s_in_seeds_block3.set_arg(80 + cu, (size_seeds + 2));
    }
    auto fpga_begin = std::chrono::high_resolution_clock::now();

    run_kernel_mm2s_in_seeds_block0.start();
    run_kernel_mm2s_in_seeds_block0.wait();
    // std::cout << "run_kernel_mm2s_in_seeds_block0 completed" << std::endl;

    run_kernel_mm2s_in_seeds_block1.start();
    run_kernel_mm2s_in_seeds_block1.wait();
    // std::cout << "run_kernel_mm2s_in_seeds_block1 completed" << std::endl;

    run_kernel_mm2s_in_seeds_block2.start();
    run_kernel_mm2s_in_seeds_block2.wait();
    // std::cout << "run_kernel_mm2s_in_seeds_block2 completed" << std::endl;

    run_kernel_mm2s_in_seeds_block3.start();
    run_kernel_mm2s_in_seeds_block3.wait();
    // std::cout << "run_kernel_mm2s_in_seeds_block3 completed" << std::endl;
    auto fpga_end = std::chrono::high_resolution_clock::now();
    fpga_duration = fpga_end - fpga_begin;

    for (auto cu = 0; cu < 40; cu++)
    {
        run_kernel_mm2s_in_seeds_block0.set_arg(cu, in_seeds_block0_buff_high[cu]);
        run_kernel_mm2s_in_seeds_block0.set_arg(80 + cu, (size_seeds + 2));

        run_kernel_mm2s_in_seeds_block1.set_arg(cu, in_seeds_block0_buff_high[cu]);
        run_kernel_mm2s_in_seeds_block1.set_arg(80 + cu, (size_seeds + 2));

        run_kernel_mm2s_in_seeds_block2.set_arg(cu, in_seeds_block0_buff_high[cu]);
        run_kernel_mm2s_in_seeds_block2.set_arg(80 + cu, (size_seeds + 2));

        run_kernel_mm2s_in_seeds_block3.set_arg(cu, in_seeds_block0_buff_high[cu]);
        run_kernel_mm2s_in_seeds_block3.set_arg(80 + cu, (size_seeds + 2));
    }

    fpga_begin = std::chrono::high_resolution_clock::now();

    run_kernel_mm2s_in_seeds_block0.start();
    run_kernel_mm2s_in_seeds_block0.wait();
    // std::cout << "Relaunching the input run_kernel_mm2s_in_seeds_block0 completed" << std::endl;

    run_kernel_mm2s_in_seeds_block1.start();
    run_kernel_mm2s_in_seeds_block1.wait();
    // std::cout << "Relaunching the input run_kernel_mm2s_in_seeds_block1 completed" << std::endl;

    run_kernel_mm2s_in_seeds_block2.start();
    run_kernel_mm2s_in_seeds_block2.wait();
    // std::cout << "Relaunching the input run_kernel_mm2s_in_seeds_block2 completed" << std::endl;

    run_kernel_mm2s_in_seeds_block3.start();
    run_kernel_mm2s_in_seeds_block3.wait();
    fpga_end = std::chrono::high_resolution_clock::now();
    fpga_duration += fpga_end - fpga_begin;
    // std::cout << "Relaunching the input run_kernel_mm2s_in_seeds_block3 completed" << std::endl;
    for (auto cu = 0; cu < 40; cu++)
    {
        run_kernel_out_result_block0.set_arg(cu, out_result_block0_buff[cu]);
        run_kernel_out_result_block0.set_arg(80 + cu, 2 * (size_out + 1));

        run_kernel_out_result_block1.set_arg(cu, out_result_block1_buff[cu]);
        run_kernel_out_result_block1.set_arg(80 + cu, 2 * (size_out + 1));

        run_kernel_out_result_block2.set_arg(cu, out_result_block2_buff[cu]);
        run_kernel_out_result_block2.set_arg(80 + cu, 2 * (size_out + 1));

        run_kernel_out_result_block3.set_arg(cu, out_result_block3_buff[cu]);
        run_kernel_out_result_block3.set_arg(80 + cu, 2 * (size_out + 1));
    }
    fpga_begin = std::chrono::high_resolution_clock::now();

    run_kernel_out_result_block0.start();
    run_kernel_out_result_block0.wait();
    // std::cout << "run_kernel_out_result_block0 completed" << std::endl;

    run_kernel_out_result_block1.start();
    run_kernel_out_result_block1.wait();
    // std::cout << "run_kernel_out_result_block1 completed" << std::endl;

    run_kernel_out_result_block2.start();
    run_kernel_out_result_block2.wait();
    // std::cout << "run_kernel_out_result_block2 completed" << std::endl;

    run_kernel_out_result_block3.start();
    run_kernel_out_result_block3.wait();
    // std::cout << "run_kernel_out_result_block3 completed" << std::endl;
    
    fpga_end = std::chrono::high_resolution_clock::now();
    fpga_duration += fpga_end - fpga_begin;
    /********************** */

    // Synchronize the output buffer data from the device
    std::cout << "Done! in " << fpga_duration.count() << " s " << std::endl;

    std::cout << "Synchronize the output buffer data from the device" << std::endl;

    for (auto cu = 0; cu < 40; cu++)
    {
        out_result_block0_buff[cu].sync(XCL_BO_SYNC_BO_FROM_DEVICE);
        out_result_block1_buff[cu].sync(XCL_BO_SYNC_BO_FROM_DEVICE);
        out_result_block2_buff[cu].sync(XCL_BO_SYNC_BO_FROM_DEVICE);
        out_result_block3_buff[cu].sync(XCL_BO_SYNC_BO_FROM_DEVICE);
    }

    std::cout << "Reading the data" << std::endl;
    for (auto cu = 0; cu < 40; cu++)
    {
        out_result_block0_buff[cu].read(out_result_block0[cu]);
        out_result_block1_buff[cu].read(out_result_block1[cu]);
        out_result_block2_buff[cu].read(out_result_block2[cu]);
        out_result_block3_buff[cu].read(out_result_block3[cu]);
    }

    std::cout << "Exec time on cold : " << fpga_duration.count() << " s " << std::endl;
    return 0;
}