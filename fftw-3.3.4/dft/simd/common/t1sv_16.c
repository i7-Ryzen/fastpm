/*
 * Copyright (c) 2003, 2007-14 Matteo Frigo
 * Copyright (c) 2003, 2007-14 Massachusetts Institute of Technology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Tue Mar  4 13:47:52 EST 2014 */

#include "codelet-dft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_twiddle.native -fma -reorder-insns -schedule-for-pipeline -simd -compact -variables 4 -pipeline-latency 8 -n 16 -name t1sv_16 -include ts.h */

/*
 * This function contains 174 FP additions, 100 FP multiplications,
 * (or, 104 additions, 30 multiplications, 70 fused multiply/add),
 * 113 stack variables, 3 constants, and 64 memory accesses
 */
#include "ts.h"

static void t1sv_16(R *ri, R *ii, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DVK(KP923879532, +0.923879532511286756128183189396788286822416626);
     DVK(KP414213562, +0.414213562373095048801688724209698078569671875);
     DVK(KP707106781, +0.707106781186547524400844362104849039284835938);
     {
	  INT m;
	  for (m = mb, W = W + (mb * 30); m < me; m = m + (2 * VL), ri = ri + ((2 * VL) * ms), ii = ii + ((2 * VL) * ms), W = W + ((2 * VL) * 30), MAKE_VOLATILE_STRIDE(32, rs)) {
	       V T2S, T2O, T2B, T2j, T2A, T24, T3J, T3L, T2Q, T2I, T2R, T2L, T2C, T2y, T3D;
	       V T3F;
	       {
		    V T3o, T3z, T1I, T8, T35, T2o, T1s, T2r, T36, T2w, T1F, T2p, T1N, T3k, Tl;
		    V T3A, T2V, T1T, Tz, T1U, T30, T29, T11, T2c, TH, TK, TJ, T31, T2h, T1e;
		    V T2a, T1Z, TI, T1Y, TF;
		    {
			 V Ta, Td, Tg, Tj, T2t, T1y, Tf, T1J, Tb, Tc, T2v, T1E, Ti;
			 {
			      V T1, T3n, T3, T6, T5, T1h, T1k, T1n, T1q, T1m, T3l, T4, T1j, T1p, T2k;
			      V T1i, T2, T1g;
			      T1 = LD(&(ri[0]), ms, &(ri[0]));
			      T3n = LD(&(ii[0]), ms, &(ii[0]));
			      T3 = LD(&(ri[WS(rs, 8)]), ms, &(ri[0]));
			      T6 = LD(&(ii[WS(rs, 8)]), ms, &(ii[0]));
			      T2 = LDW(&(W[TWVL * 14]));
			      T5 = LDW(&(W[TWVL * 15]));
			      T1h = LD(&(ri[WS(rs, 15)]), ms, &(ri[WS(rs, 1)]));
			      T1k = LD(&(ii[WS(rs, 15)]), ms, &(ii[WS(rs, 1)]));
			      T1g = LDW(&(W[TWVL * 28]));
			      T1n = LD(&(ri[WS(rs, 7)]), ms, &(ri[WS(rs, 1)]));
			      T1q = LD(&(ii[WS(rs, 7)]), ms, &(ii[WS(rs, 1)]));
			      T1m = LDW(&(W[TWVL * 12]));
			      T3l = VMUL(T2, T6);
			      T4 = VMUL(T2, T3);
			      T1j = LDW(&(W[TWVL * 29]));
			      T1p = LDW(&(W[TWVL * 13]));
			      T2k = VMUL(T1g, T1k);
			      T1i = VMUL(T1g, T1h);
			      {
				   V T1u, T1x, T1A, T2s, T1v, T1D, T1z, T1w, T1C, T2u, T1B, T9;
				   {
					V T2l, T1l, T1t, T2n, T1r;
					{
					     V T2m, T1o, T3m, T7;
					     T1u = LD(&(ri[WS(rs, 3)]), ms, &(ri[WS(rs, 1)]));
					     T2m = VMUL(T1m, T1q);
					     T1o = VMUL(T1m, T1n);
					     T3m = VFNMS(T5, T3, T3l);
					     T7 = VFMA(T5, T6, T4);
					     T1x = LD(&(ii[WS(rs, 3)]), ms, &(ii[WS(rs, 1)]));
					     T2l = VFNMS(T1j, T1h, T2k);
					     T1l = VFMA(T1j, T1k, T1i);
					     T1t = LDW(&(W[TWVL * 4]));
					     T2n = VFNMS(T1p, T1n, T2m);
					     T1r = VFMA(T1p, T1q, T1o);
					     T3o = VADD(T3m, T3n);
					     T3z = VSUB(T3n, T3m);
					     T1I = VSUB(T1, T7);
					     T8 = VADD(T1, T7);
					}
					T1A = LD(&(ri[WS(rs, 11)]), ms, &(ri[WS(rs, 1)]));
					T2s = VMUL(T1t, T1x);
					T1v = VMUL(T1t, T1u);
					T35 = VADD(T2l, T2n);
					T2o = VSUB(T2l, T2n);
					T1s = VADD(T1l, T1r);
					T2r = VSUB(T1l, T1r);
					T1D = LD(&(ii[WS(rs, 11)]), ms, &(ii[WS(rs, 1)]));
					T1z = LDW(&(W[TWVL * 20]));
				   }
				   T1w = LDW(&(W[TWVL * 5]));
				   T1C = LDW(&(W[TWVL * 21]));
				   Ta = LD(&(ri[WS(rs, 4)]), ms, &(ri[0]));
				   Td = LD(&(ii[WS(rs, 4)]), ms, &(ii[0]));
				   T9 = LDW(&(W[TWVL * 6]));
				   Tg = LD(&(ri[WS(rs, 12)]), ms, &(ri[0]));
				   Tj = LD(&(ii[WS(rs, 12)]), ms, &(ii[0]));
				   T2u = VMUL(T1z, T1D);
				   T1B = VMUL(T1z, T1A);
				   T2t = VFNMS(T1w, T1u, T2s);
				   T1y = VFMA(T1w, T1x, T1v);
				   Tf = LDW(&(W[TWVL * 22]));
				   T1J = VMUL(T9, Td);
				   Tb = VMUL(T9, Ta);
				   Tc = LDW(&(W[TWVL * 7]));
				   T2v = VFNMS(T1C, T1A, T2u);
				   T1E = VFMA(T1C, T1D, T1B);
				   Ti = LDW(&(W[TWVL * 23]));
			      }
			 }
			 {
			      V TW, TZ, TY, T27, TX, T26, TU;
			      {
				   V To, Tr, Tu, Tx, Tq, Tw, T1P, Tp, T1R, Tv;
				   {
					V T1K, Te, T1M, Tk, Tn, Tt, T1L, Th;
					To = LD(&(ri[WS(rs, 2)]), ms, &(ri[0]));
					T1L = VMUL(Tf, Tj);
					Th = VMUL(Tf, Tg);
					Tr = LD(&(ii[WS(rs, 2)]), ms, &(ii[0]));
					T1K = VFNMS(Tc, Ta, T1J);
					Te = VFMA(Tc, Td, Tb);
					T36 = VADD(T2t, T2v);
					T2w = VSUB(T2t, T2v);
					T1F = VADD(T1y, T1E);
					T2p = VSUB(T1y, T1E);
					T1M = VFNMS(Ti, Tg, T1L);
					Tk = VFMA(Ti, Tj, Th);
					Tn = LDW(&(W[TWVL * 2]));
					Tu = LD(&(ri[WS(rs, 10)]), ms, &(ri[0]));
					Tx = LD(&(ii[WS(rs, 10)]), ms, &(ii[0]));
					Tt = LDW(&(W[TWVL * 18]));
					Tq = LDW(&(W[TWVL * 3]));
					Tw = LDW(&(W[TWVL * 19]));
					T1N = VSUB(T1K, T1M);
					T3k = VADD(T1K, T1M);
					Tl = VADD(Te, Tk);
					T3A = VSUB(Te, Tk);
					T1P = VMUL(Tn, Tr);
					Tp = VMUL(Tn, To);
					T1R = VMUL(Tt, Tx);
					Tv = VMUL(Tt, Tu);
				   }
				   {
					V TQ, TT, T1Q, Ts, T1S, Ty, TV, T25, TR, TP, TS;
					TQ = LD(&(ri[WS(rs, 1)]), ms, &(ri[WS(rs, 1)]));
					TT = LD(&(ii[WS(rs, 1)]), ms, &(ii[WS(rs, 1)]));
					TP = LDW(&(W[0]));
					TW = LD(&(ri[WS(rs, 9)]), ms, &(ri[WS(rs, 1)]));
					T1Q = VFNMS(Tq, To, T1P);
					Ts = VFMA(Tq, Tr, Tp);
					T1S = VFNMS(Tw, Tu, T1R);
					Ty = VFMA(Tw, Tx, Tv);
					TZ = LD(&(ii[WS(rs, 9)]), ms, &(ii[WS(rs, 1)]));
					TV = LDW(&(W[TWVL * 16]));
					T25 = VMUL(TP, TT);
					TR = VMUL(TP, TQ);
					TS = LDW(&(W[TWVL * 1]));
					TY = LDW(&(W[TWVL * 17]));
					T2V = VADD(T1Q, T1S);
					T1T = VSUB(T1Q, T1S);
					Tz = VADD(Ts, Ty);
					T1U = VSUB(Ts, Ty);
					T27 = VMUL(TV, TZ);
					TX = VMUL(TV, TW);
					T26 = VFNMS(TS, TQ, T25);
					TU = VFMA(TS, TT, TR);
				   }
			      }
			      {
				   V T19, T1c, T1b, T2f, T1a, T2e, T17;
				   {
					V T13, T16, T12, T28, T10, T18, T15, T2d, T14;
					T13 = LD(&(ri[WS(rs, 5)]), ms, &(ri[WS(rs, 1)]));
					T16 = LD(&(ii[WS(rs, 5)]), ms, &(ii[WS(rs, 1)]));
					T12 = LDW(&(W[TWVL * 8]));
					T19 = LD(&(ri[WS(rs, 13)]), ms, &(ri[WS(rs, 1)]));
					T28 = VFNMS(TY, TW, T27);
					T10 = VFMA(TY, TZ, TX);
					T1c = LD(&(ii[WS(rs, 13)]), ms, &(ii[WS(rs, 1)]));
					T18 = LDW(&(W[TWVL * 24]));
					T15 = LDW(&(W[TWVL * 9]));
					T1b = LDW(&(W[TWVL * 25]));
					T2d = VMUL(T12, T16);
					T14 = VMUL(T12, T13);
					T30 = VADD(T26, T28);
					T29 = VSUB(T26, T28);
					T11 = VADD(TU, T10);
					T2c = VSUB(TU, T10);
					T2f = VMUL(T18, T1c);
					T1a = VMUL(T18, T19);
					T2e = VFNMS(T15, T13, T2d);
					T17 = VFMA(T15, T16, T14);
				   }
				   {
					V TB, TE, TA, T2g, T1d, TG, TD, T1X, TC;
					TB = LD(&(ri[WS(rs, 14)]), ms, &(ri[0]));
					TE = LD(&(ii[WS(rs, 14)]), ms, &(ii[0]));
					TA = LDW(&(W[TWVL * 26]));
					TH = LD(&(ri[WS(rs, 6)]), ms, &(ri[0]));
					T2g = VFNMS(T1b, T19, T2f);
					T1d = VFMA(T1b, T1c, T1a);
					TK = LD(&(ii[WS(rs, 6)]), ms, &(ii[0]));
					TG = LDW(&(W[TWVL * 10]));
					TD = LDW(&(W[TWVL * 27]));
					TJ = LDW(&(W[TWVL * 11]));
					T1X = VMUL(TA, TE);
					TC = VMUL(TA, TB);
					T31 = VADD(T2e, T2g);
					T2h = VSUB(T2e, T2g);
					T1e = VADD(T17, T1d);
					T2a = VSUB(T17, T1d);
					T1Z = VMUL(TG, TK);
					TI = VMUL(TG, TH);
					T1Y = VFNMS(TD, TB, T1X);
					TF = VFMA(TD, TE, TC);
				   }
			      }
			 }
		    }
		    {
			 V T2U, Tm, T3p, T3u, T34, T1G, T1f, T2Z, T20, TL, T32, T3f, T3g, T37;
			 T2U = VSUB(T8, Tl);
			 Tm = VADD(T8, Tl);
			 T3p = VADD(T3k, T3o);
			 T3u = VSUB(T3o, T3k);
			 T34 = VSUB(T1s, T1F);
			 T1G = VADD(T1s, T1F);
			 T1f = VADD(T11, T1e);
			 T2Z = VSUB(T11, T1e);
			 T20 = VFNMS(TJ, TH, T1Z);
			 TL = VFMA(TJ, TK, TI);
			 T32 = VSUB(T30, T31);
			 T3f = VADD(T30, T31);
			 T3g = VADD(T35, T36);
			 T37 = VSUB(T35, T36);
			 {
			      V T3r, T1H, T21, T1W, T3i, T3h, T3j, T2X, TN, T3t, T2W, TM;
			      T3r = VSUB(T1G, T1f);
			      T1H = VADD(T1f, T1G);
			      T21 = VSUB(T1Y, T20);
			      T2W = VADD(T1Y, T20);
			      T1W = VSUB(TF, TL);
			      TM = VADD(TF, TL);
			      T3i = VADD(T3f, T3g);
			      T3h = VSUB(T3f, T3g);
			      T3j = VADD(T2V, T2W);
			      T2X = VSUB(T2V, T2W);
			      TN = VADD(Tz, TM);
			      T3t = VSUB(TM, Tz);
			      {
				   V T2E, T1O, T3B, T3H, T2x, T2q, T2K, T2J, T3C, T23, T3I, T2H;
				   {
					V T2F, T1V, T22, T2G;
					T2E = VADD(T1I, T1N);
					T1O = VSUB(T1I, T1N);
					{
					     V T3b, T33, T3c, T38;
					     T3b = VSUB(T32, T2Z);
					     T33 = VADD(T2Z, T32);
					     T3c = VADD(T34, T37);
					     T38 = VSUB(T34, T37);
					     {
						  V T3a, T2Y, T3s, T3q;
						  T3a = VSUB(T2U, T2X);
						  T2Y = VADD(T2U, T2X);
						  T3s = VSUB(T3p, T3j);
						  T3q = VADD(T3j, T3p);
						  {
						       V T3x, T3v, T3e, TO;
						       T3x = VSUB(T3u, T3t);
						       T3v = VADD(T3t, T3u);
						       T3e = VSUB(Tm, TN);
						       TO = VADD(Tm, TN);
						       {
							    V T3d, T3w, T3y, T39;
							    T3d = VSUB(T3b, T3c);
							    T3w = VADD(T3b, T3c);
							    T3y = VSUB(T38, T33);
							    T39 = VADD(T33, T38);
							    ST(&(ii[WS(rs, 4)]), VADD(T3r, T3s), ms, &(ii[0]));
							    ST(&(ii[WS(rs, 12)]), VSUB(T3s, T3r), ms, &(ii[0]));
							    ST(&(ii[0]), VADD(T3i, T3q), ms, &(ii[0]));
							    ST(&(ii[WS(rs, 8)]), VSUB(T3q, T3i), ms, &(ii[0]));
							    ST(&(ri[WS(rs, 4)]), VADD(T3e, T3h), ms, &(ri[0]));
							    ST(&(ri[WS(rs, 12)]), VSUB(T3e, T3h), ms, &(ri[0]));
							    ST(&(ri[0]), VADD(TO, T1H), ms, &(ri[0]));
							    ST(&(ri[WS(rs, 8)]), VSUB(TO, T1H), ms, &(ri[0]));
							    ST(&(ri[WS(rs, 6)]), VFMA(LDK(KP707106781), T3d, T3a), ms, &(ri[0]));
							    ST(&(ri[WS(rs, 14)]), VFNMS(LDK(KP707106781), T3d, T3a), ms, &(ri[0]));
							    ST(&(ii[WS(rs, 10)]), VFNMS(LDK(KP707106781), T3w, T3v), ms, &(ii[0]));
							    ST(&(ii[WS(rs, 2)]), VFMA(LDK(KP707106781), T3w, T3v), ms, &(ii[0]));
							    ST(&(ii[WS(rs, 14)]), VFNMS(LDK(KP707106781), T3y, T3x), ms, &(ii[0]));
							    ST(&(ii[WS(rs, 6)]), VFMA(LDK(KP707106781), T3y, T3x), ms, &(ii[0]));
							    ST(&(ri[WS(rs, 2)]), VFMA(LDK(KP707106781), T39, T2Y), ms, &(ri[0]));
							    ST(&(ri[WS(rs, 10)]), VFNMS(LDK(KP707106781), T39, T2Y), ms, &(ri[0]));
							    T3B = VSUB(T3z, T3A);
							    T3H = VADD(T3A, T3z);
						       }
						  }
					     }
					}
					T2F = VADD(T1U, T1T);
					T1V = VSUB(T1T, T1U);
					T22 = VADD(T1W, T21);
					T2G = VSUB(T1W, T21);
					{
					     V T2M, T2N, T2b, T2i;
					     T2x = VSUB(T2r, T2w);
					     T2M = VADD(T2r, T2w);
					     T2N = VSUB(T2o, T2p);
					     T2q = VADD(T2o, T2p);
					     T2K = VSUB(T29, T2a);
					     T2b = VADD(T29, T2a);
					     T2i = VSUB(T2c, T2h);
					     T2J = VADD(T2c, T2h);
					     T3C = VADD(T1V, T22);
					     T23 = VSUB(T1V, T22);
					     T2S = VFMA(LDK(KP414213562), T2M, T2N);
					     T2O = VFNMS(LDK(KP414213562), T2N, T2M);
					     T3I = VSUB(T2G, T2F);
					     T2H = VADD(T2F, T2G);
					     T2B = VFNMS(LDK(KP414213562), T2b, T2i);
					     T2j = VFMA(LDK(KP414213562), T2i, T2b);
					}
				   }
				   T2A = VFNMS(LDK(KP707106781), T23, T1O);
				   T24 = VFMA(LDK(KP707106781), T23, T1O);
				   T3J = VFMA(LDK(KP707106781), T3I, T3H);
				   T3L = VFNMS(LDK(KP707106781), T3I, T3H);
				   T2Q = VFNMS(LDK(KP707106781), T2H, T2E);
				   T2I = VFMA(LDK(KP707106781), T2H, T2E);
				   T2R = VFNMS(LDK(KP414213562), T2J, T2K);
				   T2L = VFMA(LDK(KP414213562), T2K, T2J);
				   T2C = VFMA(LDK(KP414213562), T2q, T2x);
				   T2y = VFNMS(LDK(KP414213562), T2x, T2q);
				   T3D = VFMA(LDK(KP707106781), T3C, T3B);
				   T3F = VFNMS(LDK(KP707106781), T3C, T3B);
			      }
			 }
		    }
	       }
	       {
		    V T3E, T2T, T2P, T3G;
		    T3E = VADD(T2R, T2S);
		    T2T = VSUB(T2R, T2S);
		    T2P = VADD(T2L, T2O);
		    T3G = VSUB(T2O, T2L);
		    {
			 V T3K, T2D, T2z, T3M;
			 T3K = VSUB(T2C, T2B);
			 T2D = VADD(T2B, T2C);
			 T2z = VSUB(T2j, T2y);
			 T3M = VADD(T2j, T2y);
			 ST(&(ri[WS(rs, 5)]), VFMA(LDK(KP923879532), T2T, T2Q), ms, &(ri[WS(rs, 1)]));
			 ST(&(ri[WS(rs, 13)]), VFNMS(LDK(KP923879532), T2T, T2Q), ms, &(ri[WS(rs, 1)]));
			 ST(&(ii[WS(rs, 9)]), VFNMS(LDK(KP923879532), T3E, T3D), ms, &(ii[WS(rs, 1)]));
			 ST(&(ii[WS(rs, 1)]), VFMA(LDK(KP923879532), T3E, T3D), ms, &(ii[WS(rs, 1)]));
			 ST(&(ii[WS(rs, 13)]), VFNMS(LDK(KP923879532), T3G, T3F), ms, &(ii[WS(rs, 1)]));
			 ST(&(ii[WS(rs, 5)]), VFMA(LDK(KP923879532), T3G, T3F), ms, &(ii[WS(rs, 1)]));
			 ST(&(ri[WS(rs, 1)]), VFMA(LDK(KP923879532), T2P, T2I), ms, &(ri[WS(rs, 1)]));
			 ST(&(ri[WS(rs, 9)]), VFNMS(LDK(KP923879532), T2P, T2I), ms, &(ri[WS(rs, 1)]));
			 ST(&(ri[WS(rs, 15)]), VFMA(LDK(KP923879532), T2D, T2A), ms, &(ri[WS(rs, 1)]));
			 ST(&(ri[WS(rs, 7)]), VFNMS(LDK(KP923879532), T2D, T2A), ms, &(ri[WS(rs, 1)]));
			 ST(&(ii[WS(rs, 11)]), VFNMS(LDK(KP923879532), T3K, T3J), ms, &(ii[WS(rs, 1)]));
			 ST(&(ii[WS(rs, 3)]), VFMA(LDK(KP923879532), T3K, T3J), ms, &(ii[WS(rs, 1)]));
			 ST(&(ii[WS(rs, 15)]), VFMA(LDK(KP923879532), T3M, T3L), ms, &(ii[WS(rs, 1)]));
			 ST(&(ii[WS(rs, 7)]), VFNMS(LDK(KP923879532), T3M, T3L), ms, &(ii[WS(rs, 1)]));
			 ST(&(ri[WS(rs, 3)]), VFMA(LDK(KP923879532), T2z, T24), ms, &(ri[WS(rs, 1)]));
			 ST(&(ri[WS(rs, 11)]), VFNMS(LDK(KP923879532), T2z, T24), ms, &(ri[WS(rs, 1)]));
		    }
	       }
	  }
     }
     VLEAVE();
}

static const tw_instr twinstr[] = {
     VTW(0, 1),
     VTW(0, 2),
     VTW(0, 3),
     VTW(0, 4),
     VTW(0, 5),
     VTW(0, 6),
     VTW(0, 7),
     VTW(0, 8),
     VTW(0, 9),
     VTW(0, 10),
     VTW(0, 11),
     VTW(0, 12),
     VTW(0, 13),
     VTW(0, 14),
     VTW(0, 15),
     {TW_NEXT, (2 * VL), 0}
};

static const ct_desc desc = { 16, XSIMD_STRING("t1sv_16"), twinstr, &GENUS, {104, 30, 70, 0}, 0, 0, 0 };

void XSIMD(codelet_t1sv_16) (planner *p) {
     X(kdft_dit_register) (p, t1sv_16, &desc);
}
#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_twiddle.native -simd -compact -variables 4 -pipeline-latency 8 -n 16 -name t1sv_16 -include ts.h */

/*
 * This function contains 174 FP additions, 84 FP multiplications,
 * (or, 136 additions, 46 multiplications, 38 fused multiply/add),
 * 52 stack variables, 3 constants, and 64 memory accesses
 */
#include "ts.h"

static void t1sv_16(R *ri, R *ii, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DVK(KP382683432, +0.382683432365089771728459984030398866761344562);
     DVK(KP923879532, +0.923879532511286756128183189396788286822416626);
     DVK(KP707106781, +0.707106781186547524400844362104849039284835938);
     {
	  INT m;
	  for (m = mb, W = W + (mb * 30); m < me; m = m + (2 * VL), ri = ri + ((2 * VL) * ms), ii = ii + ((2 * VL) * ms), W = W + ((2 * VL) * 30), MAKE_VOLATILE_STRIDE(32, rs)) {
	       V T7, T37, T1t, T2U, Ti, T38, T1w, T2R, Tu, T2s, T1C, T2c, TF, T2t, T1H;
	       V T2d, T1f, T1q, T2B, T2C, T2D, T2E, T1Z, T2j, T24, T2k, TS, T13, T2w, T2x;
	       V T2y, T2z, T1O, T2g, T1T, T2h;
	       {
		    V T1, T2T, T6, T2S;
		    T1 = LD(&(ri[0]), ms, &(ri[0]));
		    T2T = LD(&(ii[0]), ms, &(ii[0]));
		    {
			 V T3, T5, T2, T4;
			 T3 = LD(&(ri[WS(rs, 8)]), ms, &(ri[0]));
			 T5 = LD(&(ii[WS(rs, 8)]), ms, &(ii[0]));
			 T2 = LDW(&(W[TWVL * 14]));
			 T4 = LDW(&(W[TWVL * 15]));
			 T6 = VFMA(T2, T3, VMUL(T4, T5));
			 T2S = VFNMS(T4, T3, VMUL(T2, T5));
		    }
		    T7 = VADD(T1, T6);
		    T37 = VSUB(T2T, T2S);
		    T1t = VSUB(T1, T6);
		    T2U = VADD(T2S, T2T);
	       }
	       {
		    V Tc, T1u, Th, T1v;
		    {
			 V T9, Tb, T8, Ta;
			 T9 = LD(&(ri[WS(rs, 4)]), ms, &(ri[0]));
			 Tb = LD(&(ii[WS(rs, 4)]), ms, &(ii[0]));
			 T8 = LDW(&(W[TWVL * 6]));
			 Ta = LDW(&(W[TWVL * 7]));
			 Tc = VFMA(T8, T9, VMUL(Ta, Tb));
			 T1u = VFNMS(Ta, T9, VMUL(T8, Tb));
		    }
		    {
			 V Te, Tg, Td, Tf;
			 Te = LD(&(ri[WS(rs, 12)]), ms, &(ri[0]));
			 Tg = LD(&(ii[WS(rs, 12)]), ms, &(ii[0]));
			 Td = LDW(&(W[TWVL * 22]));
			 Tf = LDW(&(W[TWVL * 23]));
			 Th = VFMA(Td, Te, VMUL(Tf, Tg));
			 T1v = VFNMS(Tf, Te, VMUL(Td, Tg));
		    }
		    Ti = VADD(Tc, Th);
		    T38 = VSUB(Tc, Th);
		    T1w = VSUB(T1u, T1v);
		    T2R = VADD(T1u, T1v);
	       }
	       {
		    V To, T1y, Tt, T1z, T1A, T1B;
		    {
			 V Tl, Tn, Tk, Tm;
			 Tl = LD(&(ri[WS(rs, 2)]), ms, &(ri[0]));
			 Tn = LD(&(ii[WS(rs, 2)]), ms, &(ii[0]));
			 Tk = LDW(&(W[TWVL * 2]));
			 Tm = LDW(&(W[TWVL * 3]));
			 To = VFMA(Tk, Tl, VMUL(Tm, Tn));
			 T1y = VFNMS(Tm, Tl, VMUL(Tk, Tn));
		    }
		    {
			 V Tq, Ts, Tp, Tr;
			 Tq = LD(&(ri[WS(rs, 10)]), ms, &(ri[0]));
			 Ts = LD(&(ii[WS(rs, 10)]), ms, &(ii[0]));
			 Tp = LDW(&(W[TWVL * 18]));
			 Tr = LDW(&(W[TWVL * 19]));
			 Tt = VFMA(Tp, Tq, VMUL(Tr, Ts));
			 T1z = VFNMS(Tr, Tq, VMUL(Tp, Ts));
		    }
		    Tu = VADD(To, Tt);
		    T2s = VADD(T1y, T1z);
		    T1A = VSUB(T1y, T1z);
		    T1B = VSUB(To, Tt);
		    T1C = VSUB(T1A, T1B);
		    T2c = VADD(T1B, T1A);
	       }
	       {
		    V Tz, T1E, TE, T1F, T1D, T1G;
		    {
			 V Tw, Ty, Tv, Tx;
			 Tw = LD(&(ri[WS(rs, 14)]), ms, &(ri[0]));
			 Ty = LD(&(ii[WS(rs, 14)]), ms, &(ii[0]));
			 Tv = LDW(&(W[TWVL * 26]));
			 Tx = LDW(&(W[TWVL * 27]));
			 Tz = VFMA(Tv, Tw, VMUL(Tx, Ty));
			 T1E = VFNMS(Tx, Tw, VMUL(Tv, Ty));
		    }
		    {
			 V TB, TD, TA, TC;
			 TB = LD(&(ri[WS(rs, 6)]), ms, &(ri[0]));
			 TD = LD(&(ii[WS(rs, 6)]), ms, &(ii[0]));
			 TA = LDW(&(W[TWVL * 10]));
			 TC = LDW(&(W[TWVL * 11]));
			 TE = VFMA(TA, TB, VMUL(TC, TD));
			 T1F = VFNMS(TC, TB, VMUL(TA, TD));
		    }
		    TF = VADD(Tz, TE);
		    T2t = VADD(T1E, T1F);
		    T1D = VSUB(Tz, TE);
		    T1G = VSUB(T1E, T1F);
		    T1H = VADD(T1D, T1G);
		    T2d = VSUB(T1D, T1G);
	       }
	       {
		    V T19, T20, T1p, T1X, T1e, T21, T1k, T1W;
		    {
			 V T16, T18, T15, T17;
			 T16 = LD(&(ri[WS(rs, 15)]), ms, &(ri[WS(rs, 1)]));
			 T18 = LD(&(ii[WS(rs, 15)]), ms, &(ii[WS(rs, 1)]));
			 T15 = LDW(&(W[TWVL * 28]));
			 T17 = LDW(&(W[TWVL * 29]));
			 T19 = VFMA(T15, T16, VMUL(T17, T18));
			 T20 = VFNMS(T17, T16, VMUL(T15, T18));
		    }
		    {
			 V T1m, T1o, T1l, T1n;
			 T1m = LD(&(ri[WS(rs, 11)]), ms, &(ri[WS(rs, 1)]));
			 T1o = LD(&(ii[WS(rs, 11)]), ms, &(ii[WS(rs, 1)]));
			 T1l = LDW(&(W[TWVL * 20]));
			 T1n = LDW(&(W[TWVL * 21]));
			 T1p = VFMA(T1l, T1m, VMUL(T1n, T1o));
			 T1X = VFNMS(T1n, T1m, VMUL(T1l, T1o));
		    }
		    {
			 V T1b, T1d, T1a, T1c;
			 T1b = LD(&(ri[WS(rs, 7)]), ms, &(ri[WS(rs, 1)]));
			 T1d = LD(&(ii[WS(rs, 7)]), ms, &(ii[WS(rs, 1)]));
			 T1a = LDW(&(W[TWVL * 12]));
			 T1c = LDW(&(W[TWVL * 13]));
			 T1e = VFMA(T1a, T1b, VMUL(T1c, T1d));
			 T21 = VFNMS(T1c, T1b, VMUL(T1a, T1d));
		    }
		    {
			 V T1h, T1j, T1g, T1i;
			 T1h = LD(&(ri[WS(rs, 3)]), ms, &(ri[WS(rs, 1)]));
			 T1j = LD(&(ii[WS(rs, 3)]), ms, &(ii[WS(rs, 1)]));
			 T1g = LDW(&(W[TWVL * 4]));
			 T1i = LDW(&(W[TWVL * 5]));
			 T1k = VFMA(T1g, T1h, VMUL(T1i, T1j));
			 T1W = VFNMS(T1i, T1h, VMUL(T1g, T1j));
		    }
		    T1f = VADD(T19, T1e);
		    T1q = VADD(T1k, T1p);
		    T2B = VSUB(T1f, T1q);
		    T2C = VADD(T20, T21);
		    T2D = VADD(T1W, T1X);
		    T2E = VSUB(T2C, T2D);
		    {
			 V T1V, T1Y, T22, T23;
			 T1V = VSUB(T19, T1e);
			 T1Y = VSUB(T1W, T1X);
			 T1Z = VSUB(T1V, T1Y);
			 T2j = VADD(T1V, T1Y);
			 T22 = VSUB(T20, T21);
			 T23 = VSUB(T1k, T1p);
			 T24 = VADD(T22, T23);
			 T2k = VSUB(T22, T23);
		    }
	       }
	       {
		    V TM, T1K, T12, T1R, TR, T1L, TX, T1Q;
		    {
			 V TJ, TL, TI, TK;
			 TJ = LD(&(ri[WS(rs, 1)]), ms, &(ri[WS(rs, 1)]));
			 TL = LD(&(ii[WS(rs, 1)]), ms, &(ii[WS(rs, 1)]));
			 TI = LDW(&(W[0]));
			 TK = LDW(&(W[TWVL * 1]));
			 TM = VFMA(TI, TJ, VMUL(TK, TL));
			 T1K = VFNMS(TK, TJ, VMUL(TI, TL));
		    }
		    {
			 V TZ, T11, TY, T10;
			 TZ = LD(&(ri[WS(rs, 13)]), ms, &(ri[WS(rs, 1)]));
			 T11 = LD(&(ii[WS(rs, 13)]), ms, &(ii[WS(rs, 1)]));
			 TY = LDW(&(W[TWVL * 24]));
			 T10 = LDW(&(W[TWVL * 25]));
			 T12 = VFMA(TY, TZ, VMUL(T10, T11));
			 T1R = VFNMS(T10, TZ, VMUL(TY, T11));
		    }
		    {
			 V TO, TQ, TN, TP;
			 TO = LD(&(ri[WS(rs, 9)]), ms, &(ri[WS(rs, 1)]));
			 TQ = LD(&(ii[WS(rs, 9)]), ms, &(ii[WS(rs, 1)]));
			 TN = LDW(&(W[TWVL * 16]));
			 TP = LDW(&(W[TWVL * 17]));
			 TR = VFMA(TN, TO, VMUL(TP, TQ));
			 T1L = VFNMS(TP, TO, VMUL(TN, TQ));
		    }
		    {
			 V TU, TW, TT, TV;
			 TU = LD(&(ri[WS(rs, 5)]), ms, &(ri[WS(rs, 1)]));
			 TW = LD(&(ii[WS(rs, 5)]), ms, &(ii[WS(rs, 1)]));
			 TT = LDW(&(W[TWVL * 8]));
			 TV = LDW(&(W[TWVL * 9]));
			 TX = VFMA(TT, TU, VMUL(TV, TW));
			 T1Q = VFNMS(TV, TU, VMUL(TT, TW));
		    }
		    TS = VADD(TM, TR);
		    T13 = VADD(TX, T12);
		    T2w = VSUB(TS, T13);
		    T2x = VADD(T1K, T1L);
		    T2y = VADD(T1Q, T1R);
		    T2z = VSUB(T2x, T2y);
		    {
			 V T1M, T1N, T1P, T1S;
			 T1M = VSUB(T1K, T1L);
			 T1N = VSUB(TX, T12);
			 T1O = VADD(T1M, T1N);
			 T2g = VSUB(T1M, T1N);
			 T1P = VSUB(TM, TR);
			 T1S = VSUB(T1Q, T1R);
			 T1T = VSUB(T1P, T1S);
			 T2h = VADD(T1P, T1S);
		    }
	       }
	       {
		    V T1J, T27, T3g, T3i, T26, T3h, T2a, T3d;
		    {
			 V T1x, T1I, T3e, T3f;
			 T1x = VSUB(T1t, T1w);
			 T1I = VMUL(LDK(KP707106781), VSUB(T1C, T1H));
			 T1J = VADD(T1x, T1I);
			 T27 = VSUB(T1x, T1I);
			 T3e = VMUL(LDK(KP707106781), VSUB(T2d, T2c));
			 T3f = VADD(T38, T37);
			 T3g = VADD(T3e, T3f);
			 T3i = VSUB(T3f, T3e);
		    }
		    {
			 V T1U, T25, T28, T29;
			 T1U = VFMA(LDK(KP923879532), T1O, VMUL(LDK(KP382683432), T1T));
			 T25 = VFNMS(LDK(KP923879532), T24, VMUL(LDK(KP382683432), T1Z));
			 T26 = VADD(T1U, T25);
			 T3h = VSUB(T25, T1U);
			 T28 = VFNMS(LDK(KP923879532), T1T, VMUL(LDK(KP382683432), T1O));
			 T29 = VFMA(LDK(KP382683432), T24, VMUL(LDK(KP923879532), T1Z));
			 T2a = VSUB(T28, T29);
			 T3d = VADD(T28, T29);
		    }
		    ST(&(ri[WS(rs, 11)]), VSUB(T1J, T26), ms, &(ri[WS(rs, 1)]));
		    ST(&(ii[WS(rs, 11)]), VSUB(T3g, T3d), ms, &(ii[WS(rs, 1)]));
		    ST(&(ri[WS(rs, 3)]), VADD(T1J, T26), ms, &(ri[WS(rs, 1)]));
		    ST(&(ii[WS(rs, 3)]), VADD(T3d, T3g), ms, &(ii[WS(rs, 1)]));
		    ST(&(ri[WS(rs, 15)]), VSUB(T27, T2a), ms, &(ri[WS(rs, 1)]));
		    ST(&(ii[WS(rs, 15)]), VSUB(T3i, T3h), ms, &(ii[WS(rs, 1)]));
		    ST(&(ri[WS(rs, 7)]), VADD(T27, T2a), ms, &(ri[WS(rs, 1)]));
		    ST(&(ii[WS(rs, 7)]), VADD(T3h, T3i), ms, &(ii[WS(rs, 1)]));
	       }
	       {
		    V T2v, T2H, T32, T34, T2G, T33, T2K, T2Z;
		    {
			 V T2r, T2u, T30, T31;
			 T2r = VSUB(T7, Ti);
			 T2u = VSUB(T2s, T2t);
			 T2v = VADD(T2r, T2u);
			 T2H = VSUB(T2r, T2u);
			 T30 = VSUB(TF, Tu);
			 T31 = VSUB(T2U, T2R);
			 T32 = VADD(T30, T31);
			 T34 = VSUB(T31, T30);
		    }
		    {
			 V T2A, T2F, T2I, T2J;
			 T2A = VADD(T2w, T2z);
			 T2F = VSUB(T2B, T2E);
			 T2G = VMUL(LDK(KP707106781), VADD(T2A, T2F));
			 T33 = VMUL(LDK(KP707106781), VSUB(T2F, T2A));
			 T2I = VSUB(T2z, T2w);
			 T2J = VADD(T2B, T2E);
			 T2K = VMUL(LDK(KP707106781), VSUB(T2I, T2J));
			 T2Z = VMUL(LDK(KP707106781), VADD(T2I, T2J));
		    }
		    ST(&(ri[WS(rs, 10)]), VSUB(T2v, T2G), ms, &(ri[0]));
		    ST(&(ii[WS(rs, 10)]), VSUB(T32, T2Z), ms, &(ii[0]));
		    ST(&(ri[WS(rs, 2)]), VADD(T2v, T2G), ms, &(ri[0]));
		    ST(&(ii[WS(rs, 2)]), VADD(T2Z, T32), ms, &(ii[0]));
		    ST(&(ri[WS(rs, 14)]), VSUB(T2H, T2K), ms, &(ri[0]));
		    ST(&(ii[WS(rs, 14)]), VSUB(T34, T33), ms, &(ii[0]));
		    ST(&(ri[WS(rs, 6)]), VADD(T2H, T2K), ms, &(ri[0]));
		    ST(&(ii[WS(rs, 6)]), VADD(T33, T34), ms, &(ii[0]));
	       }
	       {
		    V T2f, T2n, T3a, T3c, T2m, T3b, T2q, T35;
		    {
			 V T2b, T2e, T36, T39;
			 T2b = VADD(T1t, T1w);
			 T2e = VMUL(LDK(KP707106781), VADD(T2c, T2d));
			 T2f = VADD(T2b, T2e);
			 T2n = VSUB(T2b, T2e);
			 T36 = VMUL(LDK(KP707106781), VADD(T1C, T1H));
			 T39 = VSUB(T37, T38);
			 T3a = VADD(T36, T39);
			 T3c = VSUB(T39, T36);
		    }
		    {
			 V T2i, T2l, T2o, T2p;
			 T2i = VFMA(LDK(KP382683432), T2g, VMUL(LDK(KP923879532), T2h));
			 T2l = VFNMS(LDK(KP382683432), T2k, VMUL(LDK(KP923879532), T2j));
			 T2m = VADD(T2i, T2l);
			 T3b = VSUB(T2l, T2i);
			 T2o = VFNMS(LDK(KP382683432), T2h, VMUL(LDK(KP923879532), T2g));
			 T2p = VFMA(LDK(KP923879532), T2k, VMUL(LDK(KP382683432), T2j));
			 T2q = VSUB(T2o, T2p);
			 T35 = VADD(T2o, T2p);
		    }
		    ST(&(ri[WS(rs, 9)]), VSUB(T2f, T2m), ms, &(ri[WS(rs, 1)]));
		    ST(&(ii[WS(rs, 9)]), VSUB(T3a, T35), ms, &(ii[WS(rs, 1)]));
		    ST(&(ri[WS(rs, 1)]), VADD(T2f, T2m), ms, &(ri[WS(rs, 1)]));
		    ST(&(ii[WS(rs, 1)]), VADD(T35, T3a), ms, &(ii[WS(rs, 1)]));
		    ST(&(ri[WS(rs, 13)]), VSUB(T2n, T2q), ms, &(ri[WS(rs, 1)]));
		    ST(&(ii[WS(rs, 13)]), VSUB(T3c, T3b), ms, &(ii[WS(rs, 1)]));
		    ST(&(ri[WS(rs, 5)]), VADD(T2n, T2q), ms, &(ri[WS(rs, 1)]));
		    ST(&(ii[WS(rs, 5)]), VADD(T3b, T3c), ms, &(ii[WS(rs, 1)]));
	       }
	       {
		    V TH, T2L, T2W, T2Y, T1s, T2X, T2O, T2P;
		    {
			 V Tj, TG, T2Q, T2V;
			 Tj = VADD(T7, Ti);
			 TG = VADD(Tu, TF);
			 TH = VADD(Tj, TG);
			 T2L = VSUB(Tj, TG);
			 T2Q = VADD(T2s, T2t);
			 T2V = VADD(T2R, T2U);
			 T2W = VADD(T2Q, T2V);
			 T2Y = VSUB(T2V, T2Q);
		    }
		    {
			 V T14, T1r, T2M, T2N;
			 T14 = VADD(TS, T13);
			 T1r = VADD(T1f, T1q);
			 T1s = VADD(T14, T1r);
			 T2X = VSUB(T1r, T14);
			 T2M = VADD(T2x, T2y);
			 T2N = VADD(T2C, T2D);
			 T2O = VSUB(T2M, T2N);
			 T2P = VADD(T2M, T2N);
		    }
		    ST(&(ri[WS(rs, 8)]), VSUB(TH, T1s), ms, &(ri[0]));
		    ST(&(ii[WS(rs, 8)]), VSUB(T2W, T2P), ms, &(ii[0]));
		    ST(&(ri[0]), VADD(TH, T1s), ms, &(ri[0]));
		    ST(&(ii[0]), VADD(T2P, T2W), ms, &(ii[0]));
		    ST(&(ri[WS(rs, 12)]), VSUB(T2L, T2O), ms, &(ri[0]));
		    ST(&(ii[WS(rs, 12)]), VSUB(T2Y, T2X), ms, &(ii[0]));
		    ST(&(ri[WS(rs, 4)]), VADD(T2L, T2O), ms, &(ri[0]));
		    ST(&(ii[WS(rs, 4)]), VADD(T2X, T2Y), ms, &(ii[0]));
	       }
	  }
     }
     VLEAVE();
}

static const tw_instr twinstr[] = {
     VTW(0, 1),
     VTW(0, 2),
     VTW(0, 3),
     VTW(0, 4),
     VTW(0, 5),
     VTW(0, 6),
     VTW(0, 7),
     VTW(0, 8),
     VTW(0, 9),
     VTW(0, 10),
     VTW(0, 11),
     VTW(0, 12),
     VTW(0, 13),
     VTW(0, 14),
     VTW(0, 15),
     {TW_NEXT, (2 * VL), 0}
};

static const ct_desc desc = { 16, XSIMD_STRING("t1sv_16"), twinstr, &GENUS, {136, 46, 38, 0}, 0, 0, 0 };

void XSIMD(codelet_t1sv_16) (planner *p) {
     X(kdft_dit_register) (p, t1sv_16, &desc);
}
#endif				/* HAVE_FMA */
