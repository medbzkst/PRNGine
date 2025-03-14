#include <ap_int.h>
#include <hls_stream.h>
#include <ap_axi_sdata.h>

extern "C"
{
    void pl_s2mm_40x(ap_int<32> *mem0,
                     ap_int<32> *mem1,
                     ap_int<32> *mem2,
                     ap_int<32> *mem3,
                     ap_int<32> *mem4,
                     ap_int<32> *mem5,
                     ap_int<32> *mem6,
                     ap_int<32> *mem7,
                     ap_int<32> *mem8,
                     ap_int<32> *mem9,
                     ap_int<32> *mem10,
                     ap_int<32> *mem11,
                     ap_int<32> *mem12,
                     ap_int<32> *mem13,
                     ap_int<32> *mem14,
                     ap_int<32> *mem15,
                     ap_int<32> *mem16,
                     ap_int<32> *mem17,
                     ap_int<32> *mem18,
                     ap_int<32> *mem19,
                     ap_int<32> *mem20,
                     ap_int<32> *mem21,
                     ap_int<32> *mem22,
                     ap_int<32> *mem23,
                     ap_int<32> *mem24,
                     ap_int<32> *mem25,
                     ap_int<32> *mem26,
                     ap_int<32> *mem27,
                     ap_int<32> *mem28,
                     ap_int<32> *mem29,
                     ap_int<32> *mem30,
                     ap_int<32> *mem31,
                     ap_int<32> *mem32,
                     ap_int<32> *mem33,
                     ap_int<32> *mem34,
                     ap_int<32> *mem35,
                     ap_int<32> *mem36,
                     ap_int<32> *mem37,
                     ap_int<32> *mem38,
                     ap_int<32> *mem39,
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

    s2mm_loop_0:
        for (int i = 0; i < size0; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s0.read();
            mem0[i] = x.data;
        }

    s2mm_loop_1:
        for (int i = 0; i < size1; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s1.read();
            mem1[i] = x.data;
        }

    s2mm_loop_2:
        for (int i = 0; i < size2; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s2.read();
            mem2[i] = x.data;
        }

    s2mm_loop_3:
        for (int i = 0; i < size3; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s3.read();
            mem3[i] = x.data;
        }

    s2mm_loop_4:
        for (int i = 0; i < size4; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s4.read();
            mem4[i] = x.data;
        }

    s2mm_loop_5:
        for (int i = 0; i < size5; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s5.read();
            mem5[i] = x.data;
        }

    s2mm_loop_6:
        for (int i = 0; i < size6; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s6.read();
            mem6[i] = x.data;
        }

    s2mm_loop_7:
        for (int i = 0; i < size7; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s7.read();
            mem7[i] = x.data;
        }

    s2mm_loop_8:
        for (int i = 0; i < size8; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s8.read();
            mem8[i] = x.data;
        }

    s2mm_loop_9:
        for (int i = 0; i < size9; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s9.read();
            mem9[i] = x.data;
        }
    s2mm_loop_10:
        for (int i = 0; i < size10; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s10.read();
            mem10[i] = x.data;
        }

    s2mm_loop_11:
        for (int i = 0; i < size11; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s11.read();
            mem11[i] = x.data;
        }

    s2mm_loop_12:
        for (int i = 0; i < size12; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s12.read();
            mem12[i] = x.data;
        }

    s2mm_loop_13:
        for (int i = 0; i < size13; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s13.read();
            mem13[i] = x.data;
        }

    s2mm_loop_14:
        for (int i = 0; i < size14; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s14.read();
            mem14[i] = x.data;
        }

    s2mm_loop_15:
        for (int i = 0; i < size15; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s15.read();
            mem15[i] = x.data;
        }

    s2mm_loop_16:
        for (int i = 0; i < size16; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s16.read();
            mem16[i] = x.data;
        }

    s2mm_loop_17:
        for (int i = 0; i < size17; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s17.read();
            mem17[i] = x.data;
        }

    s2mm_loop_18:
        for (int i = 0; i < size18; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s18.read();
            mem18[i] = x.data;
        }

    s2mm_loop_19:
        for (int i = 0; i < size19; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s19.read();
            mem19[i] = x.data;
        }

    s2mm_loop_20:
        for (int i = 0; i < size20; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s20.read();
            mem20[i] = x.data;
        }

    s2mm_loop_21:
        for (int i = 0; i < size21; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s21.read();
            mem21[i] = x.data;
        }

    s2mm_loop_22:
        for (int i = 0; i < size22; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s22.read();
            mem22[i] = x.data;
        }

    s2mm_loop_23:
        for (int i = 0; i < size23; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s23.read();
            mem23[i] = x.data;
        }

    s2mm_loop_24:
        for (int i = 0; i < size24; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s24.read();
            mem24[i] = x.data;
        }

    s2mm_loop_25:
        for (int i = 0; i < size25; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s25.read();
            mem25[i] = x.data;
        }

    s2mm_loop_26:
        for (int i = 0; i < size26; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s26.read();
            mem26[i] = x.data;
        }

    s2mm_loop_27:
        for (int i = 0; i < size27; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s27.read();
            mem27[i] = x.data;
        }

    s2mm_loop_28:
        for (int i = 0; i < size28; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s28.read();
            mem28[i] = x.data;
        }

    s2mm_loop_29:
        for (int i = 0; i < size29; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s29.read();
            mem29[i] = x.data;
        }

    s2mm_loop_30:
        for (int i = 0; i < size30; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s30.read();
            mem30[i] = x.data;
        }

    s2mm_loop_31:
        for (int i = 0; i < size31; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s31.read();
            mem31[i] = x.data;
        }

    s2mm_loop_32:
        for (int i = 0; i < size32; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s32.read();
            mem32[i] = x.data;
        }

    s2mm_loop_33:
        for (int i = 0; i < size33; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s33.read();
            mem33[i] = x.data;
        }

    s2mm_loop_34:
        for (int i = 0; i < size34; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s34.read();
            mem34[i] = x.data;
        }

    s2mm_loop_35:
        for (int i = 0; i < size35; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s35.read();
            mem35[i] = x.data;
        }

    s2mm_loop_36:
        for (int i = 0; i < size36; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s36.read();
            mem36[i] = x.data;
        }

    s2mm_loop_37:
        for (int i = 0; i < size37; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s37.read();
            mem37[i] = x.data;
        }

    s2mm_loop_38:
        for (int i = 0; i < size38; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s38.read();
            mem38[i] = x.data;
        }

    s2mm_loop_39:
        for (int i = 0; i < size39; i++)
        {
            ap_axiu<32, 0, 0, 0> x = s39.read();
            mem39[i] = x.data;
        }
    }
}