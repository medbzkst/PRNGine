#include <ap_int.h>
#include <hls_stream.h>
#include <ap_axi_sdata.h>

extern "C"
{

    void pl_mm2s_40x(ap_uint<32> *mem0,
                     ap_uint<32> *mem1,
                     ap_uint<32> *mem2,
                     ap_uint<32> *mem3,
                     ap_uint<32> *mem4,
                     ap_uint<32> *mem5,
                     ap_uint<32> *mem6,
                     ap_uint<32> *mem7,
                     ap_uint<32> *mem8,
                     ap_uint<32> *mem9,
                     ap_uint<32> *mem10,
                     ap_uint<32> *mem11,
                     ap_uint<32> *mem12,
                     ap_uint<32> *mem13,
                     ap_uint<32> *mem14,
                     ap_uint<32> *mem15,
                     ap_uint<32> *mem16,
                     ap_uint<32> *mem17,
                     ap_uint<32> *mem18,
                     ap_uint<32> *mem19,
                     ap_uint<32> *mem20,
                     ap_uint<32> *mem21,
                     ap_uint<32> *mem22,
                     ap_uint<32> *mem23,
                     ap_uint<32> *mem24,
                     ap_uint<32> *mem25,
                     ap_uint<32> *mem26,
                     ap_uint<32> *mem27,
                     ap_uint<32> *mem28,
                     ap_uint<32> *mem29,
                     ap_uint<32> *mem30,
                     ap_uint<32> *mem31,
                     ap_uint<32> *mem32,
                     ap_uint<32> *mem33,
                     ap_uint<32> *mem34,
                     ap_uint<32> *mem35,
                     ap_uint<32> *mem36,
                     ap_uint<32> *mem37,
                     ap_uint<32> *mem38,
                     ap_uint<32> *mem39,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s0,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s1,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s2,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s3,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s4,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s5,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s6,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s7,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s8,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s9,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s10,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s11,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s12,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s13,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s14,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s15,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s16,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s17,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s18,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s19,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s20,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s21,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s22,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s23,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s24,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s25,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s26,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s27,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s28,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s29,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s30,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s31,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s32,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s33,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s34,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s35,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s36,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s37,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s38,
                     hls::stream<ap_axiu<32, 0, 0, 0>> &s39,
                     int size0,
                     int size1,
                     int size2,
                     int size3,
                     int size4,
                     int size5,
                     int size6,
                     int size7,
                     int size8,
                     int size9,
                     int size10,
                     int size11,
                     int size12,
                     int size13,
                     int size14,
                     int size15,
                     int size16,
                     int size17,
                     int size18,
                     int size19,
                     int size20,
                     int size21,
                     int size22,
                     int size23,
                     int size24,
                     int size25,
                     int size26,
                     int size27,
                     int size28,
                     int size29,
                     int size30,
                     int size31,
                     int size32,
                     int size33,
                     int size34,
                     int size35,
                     int size36,
                     int size37,
                     int size38,
                     int size39)
    {
    mm2s_loop_0:
        for (int i = 0; i < size0; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem0[i];
            x.keep = -1;
            x.last = (i == size0 - 1);
            s0.write(x);
        }

    mm2s_loop_1:
        for (int i = 0; i < size1; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem1[i];
            x.keep = -1;
            x.last = (i == size1 - 1);
            s1.write(x);
        }

    mm2s_loop_2:
        for (int i = 0; i < size2; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem2[i];
            x.keep = -1;
            x.last = (i == size2 - 1);
            s2.write(x);
        }

    mm2s_loop_3:
        for (int i = 0; i < size3; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem3[i];
            x.keep = -1;
            x.last = (i == size3 - 1);
            s3.write(x);
        }

    mm2s_loop_4:
        for (int i = 0; i < size4; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem4[i];
            x.keep = -1;
            x.last = (i == size4 - 1);
            s4.write(x);
        }

    mm2s_loop_5:
        for (int i = 0; i < size5; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem5[i];
            x.keep = -1;
            x.last = (i == size5 - 1);
            s5.write(x);
        }

    mm2s_loop_6:
        for (int i = 0; i < size6; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem6[i];
            x.keep = -1;
            x.last = (i == size6 - 1);
            s6.write(x);
        }

    mm2s_loop_7:
        for (int i = 0; i < size7; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem7[i];
            x.keep = -1;
            x.last = (i == size7 - 1);
            s7.write(x);
        }

    mm2s_loop_8:
        for (int i = 0; i < size8; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem8[i];
            x.keep = -1;
            x.last = (i == size8 - 1);
            s8.write(x);
        }

    mm2s_loop_9:
        for (int i = 0; i < size9; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem9[i];
            x.keep = -1;
            x.last = (i == size9 - 1);
            s9.write(x);
        }

    mm2s_loop_10:
        for (int i = 0; i < size10; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem10[i];
            x.keep = -1;
            x.last = (i == size10 - 1);
            s10.write(x);
        }

    mm2s_loop_11:
        for (int i = 0; i < size11; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem11[i];
            x.keep = -1;
            x.last = (i == size11 - 1);
            s11.write(x);
        }

    mm2s_loop_12:
        for (int i = 0; i < size12; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem12[i];
            x.keep = -1;
            x.last = (i == size12 - 1);
            s12.write(x);
        }

    mm2s_loop_13:
        for (int i = 0; i < size13; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem13[i];
            x.keep = -1;
            x.last = (i == size13 - 1);
            s13.write(x);
        }

    mm2s_loop_14:
        for (int i = 0; i < size14; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem14[i];
            x.keep = -1;
            x.last = (i == size14 - 1);
            s14.write(x);
        }

    mm2s_loop_15:
        for (int i = 0; i < size15; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem15[i];
            x.keep = -1;
            x.last = (i == size15 - 1);
            s15.write(x);
        }

    mm2s_loop_16:
        for (int i = 0; i < size16; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem16[i];
            x.keep = -1;
            x.last = (i == size16 - 1);
            s16.write(x);
        }

    mm2s_loop_17:
        for (int i = 0; i < size17; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem17[i];
            x.keep = -1;
            x.last = (i == size17 - 1);
            s17.write(x);
        }

    mm2s_loop_18:
        for (int i = 0; i < size18; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem18[i];
            x.keep = -1;
            x.last = (i == size18 - 1);
            s18.write(x);
        }

    mm2s_loop_19:
        for (int i = 0; i < size19; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem19[i];
            x.keep = -1;
            x.last = (i == size19 - 1);
            s19.write(x);
        }

    mm2s_loop_20:
        for (int i = 0; i < size20; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem20[i];
            x.keep = -1;
            x.last = (i == size20 - 1);
            s20.write(x);
        }

    mm2s_loop_21:
        for (int i = 0; i < size21; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem21[i];
            x.keep = -1;
            x.last = (i == size21 - 1);
            s21.write(x);
        }

    mm2s_loop_22:
        for (int i = 0; i < size22; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem22[i];
            x.keep = -1;
            x.last = (i == size22 - 1);
            s22.write(x);
        }

    mm2s_loop_23:
        for (int i = 0; i < size23; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem23[i];
            x.keep = -1;
            x.last = (i == size23 - 1);
            s23.write(x);
        }

    mm2s_loop_24:
        for (int i = 0; i < size24; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem24[i];
            x.keep = -1;
            x.last = (i == size24 - 1);
            s24.write(x);
        }

    mm2s_loop_25:
        for (int i = 0; i < size25; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem25[i];
            x.keep = -1;
            x.last = (i == size25 - 1);
            s25.write(x);
        }

    mm2s_loop_26:
        for (int i = 0; i < size26; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem26[i];
            x.keep = -1;
            x.last = (i == size26 - 1);
            s26.write(x);
        }

    mm2s_loop_27:
        for (int i = 0; i < size27; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem27[i];
            x.keep = -1;
            x.last = (i == size27 - 1);
            s27.write(x);
        }

    mm2s_loop_28:
        for (int i = 0; i < size28; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem28[i];
            x.keep = -1;
            x.last = (i == size28 - 1);
            s28.write(x);
        }

    mm2s_loop_29:
        for (int i = 0; i < size29; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem29[i];
            x.keep = -1;
            x.last = (i == size29 - 1);
            s29.write(x);
        }

    mm2s_loop_30:
        for (int i = 0; i < size30; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem30[i];
            x.keep = -1;
            x.last = (i == size30 - 1);
            s30.write(x);
        }

    mm2s_loop_31:
        for (int i = 0; i < size31; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem31[i];
            x.keep = -1;
            x.last = (i == size31 - 1);
            s31.write(x);
        }

    mm2s_loop_32:
        for (int i = 0; i < size32; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem32[i];
            x.keep = -1;
            x.last = (i == size32 - 1);
            s32.write(x);
        }

    mm2s_loop_33:
        for (int i = 0; i < size33; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem33[i];
            x.keep = -1;
            x.last = (i == size33 - 1);
            s33.write(x);
        }

    mm2s_loop_34:
        for (int i = 0; i < size34; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem34[i];
            x.keep = -1;
            x.last = (i == size34 - 1);
            s34.write(x);
        }

    mm2s_loop_35:
        for (int i = 0; i < size35; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem35[i];
            x.keep = -1;
            x.last = (i == size35 - 1);
            s35.write(x);
        }

    mm2s_loop_36:
        for (int i = 0; i < size36; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem36[i];
            x.keep = -1;
            x.last = (i == size36 - 1);
            s36.write(x);
        }

    mm2s_loop_37:
        for (int i = 0; i < size37; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem37[i];
            x.keep = -1;
            x.last = (i == size37 - 1);
            s37.write(x);
        }

    mm2s_loop_38:
        for (int i = 0; i < size38; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem38[i];
            x.keep = -1;
            x.last = (i == size38 - 1);
            s38.write(x);
        }

    mm2s_loop_39:
        for (int i = 0; i < size39; i++)
        {
            ap_axiu<32, 0, 0, 0> x;
            x.data = mem39[i];
            x.keep = -1;
            x.last = (i == size39 - 1);
            s39.write(x);
        }
    }
}