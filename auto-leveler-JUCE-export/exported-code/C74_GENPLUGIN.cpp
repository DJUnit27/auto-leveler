#include "C74_GENPLUGIN.h"

namespace C74_GENPLUGIN {

/*******************************************************************************************************************
Cycling '74 License for Max-Generated Code for Export
Copyright (c) 2016 Cycling '74
The code that Max generates automatically and that end users are capable of exporting and using, and any
  associated documentation files (the “Software”) is a work of authorship for which Cycling '74 is the author
  and owner for copyright purposes.  A license is hereby granted, free of charge, to any person obtaining a
  copy of the Software (“Licensee”) to use, copy, modify, merge, publish, and distribute copies of the Software,
  and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The Software is licensed to Licensee only for non-commercial use. Users who wish to make commercial use of the
  Software must contact the copyright owner to determine if a license for commercial use is available, and the
  terms and conditions for same, which may include fees or royalties. For commercial use, please send inquiries
  to licensing (at) cycling74.com.  The determination of whether a use is commercial use or non-commercial use is based
  upon the use, not the user. The Software may be used by individuals, institutions, governments, corporations, or
  other business whether for-profit or non-profit so long as the use itself is not a commercialization of the
  materials or a use that generates or is intended to generate income, revenue, sales or profit.
The above copyright notice and this license shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.
*******************************************************************************************************************/

// global noise generator
Noise noise;
static const int GENLIB_LOOPCOUNT_BAIL = 100000;


// The State struct contains all the state and procedures for the gendsp kernel
typedef struct State {
	CommonState __commonstate;
	Delay m_delay_26;
	Delay m_delay_18;
	Delay m_delay_37;
	Delay m_delay_38;
	Delay m_delay_19;
	Delay m_delay_23;
	Delay m_delay_20;
	Delay m_delay_8;
	Delay m_delay_36;
	Delay m_delay_5;
	Delta __m_delta_43;
	Delta __m_delta_42;
	Delta __m_delta_41;
	Delta __m_delta_40;
	int __exception;
	int vectorsize;
	t_sample m_history_29;
	t_sample __m_count_44;
	t_sample __m_carry_46;
	t_sample m_history_28;
	t_sample m_history_31;
	t_sample m_history_32;
	t_sample m_y_27;
	t_sample m_history_30;
	t_sample m_history_35;
	t_sample m_history_33;
	t_sample m_history_34;
	t_sample m_targetLevel_39;
	t_sample m_counter_22;
	t_sample m_average_24;
	t_sample m_counter_4;
	t_sample m_average_6;
	t_sample m_counter_7;
	t_sample m_y_9;
	t_sample m_average_3;
	t_sample m_history_1;
	t_sample m_loadbang_2;
	t_sample samplerate;
	t_sample m_counter_25;
	t_sample m_history_10;
	t_sample m_history_12;
	t_sample m_history_17;
	t_sample m_average_21;
	t_sample __m_latch_48;
	t_sample m_history_11;
	t_sample m_history_16;
	t_sample m_history_14;
	t_sample m_history_15;
	t_sample m_history_13;
	t_sample __m_slide_51;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_history_1 = ((int)0);
		m_loadbang_2 = ((int)1);
		m_average_3 = ((int)0);
		m_counter_4 = ((int)0);
		m_delay_5.reset("m_delay_5", ((int)1920000));
		m_average_6 = ((int)0);
		m_counter_7 = ((int)0);
		m_delay_8.reset("m_delay_8", ((int)1920000));
		m_y_9 = ((int)0);
		m_history_10 = ((int)0);
		m_history_11 = ((int)0);
		m_history_12 = ((int)0);
		m_history_13 = ((int)0);
		m_history_14 = ((int)0);
		m_history_15 = ((int)0);
		m_history_16 = ((int)0);
		m_history_17 = ((int)0);
		m_delay_18.reset("m_delay_18", ((int)1920000));
		m_delay_19.reset("m_delay_19", ((int)1920000));
		m_delay_20.reset("m_delay_20", ((int)1920000));
		m_average_21 = ((int)0);
		m_counter_22 = ((int)0);
		m_delay_23.reset("m_delay_23", ((int)1920000));
		m_average_24 = ((int)0);
		m_counter_25 = ((int)0);
		m_delay_26.reset("m_delay_26", ((int)1920000));
		m_y_27 = ((int)0);
		m_history_28 = ((int)0);
		m_history_29 = ((int)0);
		m_history_30 = ((int)0);
		m_history_31 = ((int)0);
		m_history_32 = ((int)0);
		m_history_33 = ((int)0);
		m_history_34 = ((int)0);
		m_history_35 = ((int)0);
		m_delay_36.reset("m_delay_36", ((int)1920000));
		m_delay_37.reset("m_delay_37", ((int)1920000));
		m_delay_38.reset("m_delay_38", ((int)1920000));
		m_targetLevel_39 = -20;
		__m_delta_40.reset(0);
		__m_delta_41.reset(0);
		__m_delta_42.reset(0);
		__m_delta_43.reset(0);
		__m_count_44 = 0;
		__m_carry_46 = 0;
		__m_latch_48 = 0;
		__m_slide_51 = 0;
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		const t_sample * __in2 = __ins[1];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		t_sample * __out3 = __outs[2];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__out1 == 0) || (__out2 == 0) || (__out3 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample expr_1274 = ((samplerate * ((int)3000)) * ((t_sample)0.001));
		t_sample div_1267 = (expr_1274 * ((t_sample)0.25));
		t_sample mul_1266 = (div_1267 * ((int)2));
		t_sample mul_1265 = (div_1267 * ((int)3));
		t_sample omega = safediv(((t_sample)6283.1853071796), samplerate);
		t_sample sn = sin(omega);
		t_sample cs = cos(omega);
		t_sample b0 = safediv(((int)1), ((((t_sample)2.2589254117942) - (((t_sample)0.25892541179417) * cs)) + (((t_sample)1.5867737153067) * sn)));
		t_sample a0 = ((((t_sample)1.2589254117942) * ((((t_sample)2.2589254117942) + (((t_sample)0.25892541179417) * cs)) + (((t_sample)1.5867737153067) * sn))) * b0);
		t_sample a1 = ((((t_sample)-2.5178508235883) * (((t_sample)0.25892541179417) + (((t_sample)2.2589254117942) * cs))) * b0);
		t_sample a2 = ((((t_sample)1.2589254117942) * ((((t_sample)2.2589254117942) + (((t_sample)0.25892541179417) * cs)) - (((t_sample)1.5867737153067) * sn))) * b0);
		t_sample b1 = ((((int)2) * (((t_sample)0.25892541179417) - (((t_sample)2.2589254117942) * cs))) * b0);
		t_sample b2 = (((((t_sample)2.2589254117942) - (((t_sample)0.25892541179417) * cs)) - (((t_sample)1.5867737153067) * sn)) * b0);
		t_sample expr_1214 = a0;
		t_sample expr_1215 = a1;
		t_sample expr_1216 = a2;
		t_sample expr_1217 = b1;
		t_sample expr_1218 = b2;
		t_sample expr_1160 = ((samplerate * ((int)3000)) * ((t_sample)0.001));
		t_sample div_1153 = (expr_1160 * ((t_sample)0.25));
		t_sample mul_1152 = (div_1153 * ((int)2));
		t_sample mul_1151 = (div_1153 * ((int)3));
		t_sample omega_1461 = safediv(((t_sample)6283.1853071796), samplerate);
		t_sample sn_1467 = sin(omega_1461);
		t_sample cs_1459 = cos(omega_1461);
		t_sample b_1464 = safediv(((int)1), ((((t_sample)2.2589254117942) - (((t_sample)0.25892541179417) * cs_1459)) + (((t_sample)1.5867737153067) * sn_1467)));
		t_sample a_1465 = ((((t_sample)1.2589254117942) * ((((t_sample)2.2589254117942) + (((t_sample)0.25892541179417) * cs_1459)) + (((t_sample)1.5867737153067) * sn_1467))) * b_1464);
		t_sample a_1469 = ((((t_sample)-2.5178508235883) * (((t_sample)0.25892541179417) + (((t_sample)2.2589254117942) * cs_1459))) * b_1464);
		t_sample a_1457 = ((((t_sample)1.2589254117942) * ((((t_sample)2.2589254117942) + (((t_sample)0.25892541179417) * cs_1459)) - (((t_sample)1.5867737153067) * sn_1467))) * b_1464);
		t_sample b_1463 = ((((int)2) * (((t_sample)0.25892541179417) - (((t_sample)2.2589254117942) * cs_1459))) * b_1464);
		t_sample b_1458 = (((((t_sample)2.2589254117942) - (((t_sample)0.25892541179417) * cs_1459)) - (((t_sample)1.5867737153067) * sn_1467)) * b_1464);
		t_sample expr_1100 = a_1465;
		t_sample expr_1101 = a_1469;
		t_sample expr_1102 = a_1457;
		t_sample expr_1103 = b_1463;
		t_sample expr_1104 = b_1458;
		t_sample expr_1453 = ((((int)500) * samplerate) * ((t_sample)0.001));
		t_sample loadbang_next_1473 = fixdenorm(((int)0));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample out3 = m_history_1;
			t_sample mul_1281 = (in1 * m_history_1);
			t_sample out1 = mul_1281;
			t_sample mul_1280 = (in2 * m_history_1);
			t_sample out2 = mul_1280;
			t_sample tap_1269 = m_delay_38.read_linear(div_1267);
			t_sample tap_1264 = m_delay_37.read_linear(mul_1266);
			t_sample tap_1262 = m_delay_36.read_linear(mul_1265);
			t_sample mix_1605 = (m_y_27 + (((t_sample)0.014247103707103) * (mul_1281 - m_y_27)));
			t_sample mix_1210 = mix_1605;
			t_sample sub_1167 = (mul_1281 - mix_1210);
			t_sample mul_1196 = (m_history_34 * expr_1216);
			t_sample mul_1198 = (m_history_33 * expr_1215);
			t_sample mul_1201 = (sub_1167 * expr_1214);
			t_sample mul_1194 = (m_history_32 * expr_1217);
			t_sample mul_1192 = (m_history_35 * expr_1218);
			t_sample sub_1200 = (((mul_1201 + mul_1198) + mul_1196) - (mul_1192 + mul_1194));
			t_sample gen_1206 = sub_1200;
			t_sample history_1193_next_1202 = fixdenorm(m_history_32);
			t_sample history_1197_next_1203 = fixdenorm(m_history_33);
			t_sample history_1199_next_1204 = fixdenorm(sub_1167);
			t_sample history_1195_next_1205 = fixdenorm(sub_1200);
			t_sample gen_1221 = gen_1206;
			t_sample mix_1606 = (m_y_27 + (((t_sample)0.014247103707103) * (mul_1280 - m_y_27)));
			t_sample mix_1207 = mix_1606;
			t_sample sub_1166 = (mul_1280 - mix_1207);
			t_sample mul_1172 = (m_history_31 * expr_1216);
			t_sample mul_1174 = (m_history_29 * expr_1215);
			t_sample mul_1177 = (sub_1166 * expr_1214);
			t_sample mul_1170 = (m_history_28 * expr_1217);
			t_sample mul_1168 = (m_history_30 * expr_1218);
			t_sample sub_1176 = (((mul_1177 + mul_1174) + mul_1172) - (mul_1168 + mul_1170));
			t_sample gen_1182 = sub_1176;
			t_sample history_1173_next_1178 = fixdenorm(m_history_29);
			t_sample history_1169_next_1179 = fixdenorm(m_history_28);
			t_sample history_1175_next_1180 = fixdenorm(sub_1166);
			t_sample history_1171_next_1181 = fixdenorm(sub_1176);
			t_sample gen_1222 = gen_1182;
			t_sample y0_next_1219 = fixdenorm(mix_1210);
			t_sample y0_next_1220 = fixdenorm(mix_1207);
			t_sample add_1252 = (m_counter_25 + ((int)1));
			t_sample clamp_1249 = ((add_1252 <= ((int)0)) ? ((int)0) : ((add_1252 >= expr_1274) ? expr_1274 : add_1252));
			t_sample div_1245 = safediv(m_average_24, clamp_1249);
			t_sample gen_1258 = div_1245;
			t_sample delta_1253 = __m_delta_40(expr_1274);
			int eq_1246 = (delta_1253 == ((int)0));
			t_sample mul_1248 = (clamp_1249 * eq_1246);
			t_sample tap_1255 = m_delay_26.read_linear(expr_1274);
			int gte_1242 = (clamp_1249 >= expr_1274);
			t_sample mul_1243 = (tap_1255 * gte_1242);
			t_sample abs_1241 = fabs(gen_1221);
			t_sample add_1251 = (m_average_24 + abs_1241);
			t_sample sub_1250 = (add_1251 - mul_1243);
			t_sample mul_1247 = (sub_1250 * eq_1246);
			t_sample counter_next_1256 = fixdenorm(mul_1248);
			t_sample average_next_1257 = fixdenorm(mul_1247);
			t_sample add_1234 = (m_counter_22 + ((int)1));
			t_sample clamp_1231 = ((add_1234 <= ((int)0)) ? ((int)0) : ((add_1234 >= expr_1274) ? expr_1274 : add_1234));
			t_sample div_1227 = safediv(m_average_21, clamp_1231);
			t_sample gen_1240 = div_1227;
			t_sample delta_1235 = __m_delta_41(expr_1274);
			int eq_1228 = (delta_1235 == ((int)0));
			t_sample mul_1230 = (clamp_1231 * eq_1228);
			t_sample tap_1237 = m_delay_23.read_linear(expr_1274);
			int gte_1224 = (clamp_1231 >= expr_1274);
			t_sample mul_1225 = (tap_1237 * gte_1224);
			t_sample abs_1223 = fabs(gen_1222);
			t_sample add_1233 = (m_average_21 + abs_1223);
			t_sample sub_1232 = (add_1233 - mul_1225);
			t_sample mul_1229 = (sub_1232 * eq_1228);
			t_sample counter_next_1238 = fixdenorm(mul_1230);
			t_sample average_next_1239 = fixdenorm(mul_1229);
			t_sample add_1270 = (gen_1258 + gen_1240);
			t_sample atodb_1260 = atodb(add_1270);
			t_sample expr_1273 = ((((atodb_1260 + tap_1269) + tap_1264) + tap_1262) * ((t_sample)0.25));
			t_sample gen_1279 = expr_1273;
			t_sample tap_1155 = m_delay_20.read_linear(div_1153);
			t_sample tap_1150 = m_delay_19.read_linear(mul_1152);
			t_sample tap_1148 = m_delay_18.read_linear(mul_1151);
			t_sample mix_1607 = (m_y_9 + (((t_sample)0.014247103707103) * (in2 - m_y_9)));
			t_sample mix_1093 = mix_1607;
			t_sample sub_1052 = (in2 - mix_1093);
			t_sample mul_1058 = (m_history_17 * expr_1102);
			t_sample mul_1060 = (m_history_15 * expr_1101);
			t_sample mul_1063 = (sub_1052 * expr_1100);
			t_sample mul_1056 = (m_history_14 * expr_1103);
			t_sample mul_1054 = (m_history_16 * expr_1104);
			t_sample sub_1062 = (((mul_1063 + mul_1060) + mul_1058) - (mul_1054 + mul_1056));
			t_sample gen_1068 = sub_1062;
			t_sample history_1059_next_1064 = fixdenorm(m_history_15);
			t_sample history_1055_next_1065 = fixdenorm(m_history_14);
			t_sample history_1061_next_1066 = fixdenorm(sub_1052);
			t_sample history_1057_next_1067 = fixdenorm(sub_1062);
			t_sample gen_1108 = gen_1068;
			t_sample mix_1608 = (m_y_9 + (((t_sample)0.014247103707103) * (in1 - m_y_9)));
			t_sample mix_1096 = mix_1608;
			t_sample sub_1053 = (in1 - mix_1096);
			t_sample mul_1082 = (m_history_12 * expr_1102);
			t_sample mul_1084 = (m_history_11 * expr_1101);
			t_sample mul_1087 = (sub_1053 * expr_1100);
			t_sample mul_1080 = (m_history_10 * expr_1103);
			t_sample mul_1078 = (m_history_13 * expr_1104);
			t_sample sub_1086 = (((mul_1087 + mul_1084) + mul_1082) - (mul_1078 + mul_1080));
			t_sample gen_1092 = sub_1086;
			t_sample history_1079_next_1088 = fixdenorm(m_history_10);
			t_sample history_1083_next_1089 = fixdenorm(m_history_11);
			t_sample history_1085_next_1090 = fixdenorm(sub_1053);
			t_sample history_1081_next_1091 = fixdenorm(sub_1086);
			t_sample gen_1107 = gen_1092;
			t_sample y0_next_1105 = fixdenorm(mix_1093);
			t_sample y0_next_1106 = fixdenorm(mix_1096);
			t_sample add_1138 = (m_counter_7 + ((int)1));
			t_sample clamp_1135 = ((add_1138 <= ((int)0)) ? ((int)0) : ((add_1138 >= expr_1160) ? expr_1160 : add_1138));
			t_sample div_1131 = safediv(m_average_6, clamp_1135);
			t_sample gen_1144 = div_1131;
			t_sample delta_1139 = __m_delta_42(expr_1160);
			int eq_1132 = (delta_1139 == ((int)0));
			t_sample mul_1134 = (clamp_1135 * eq_1132);
			t_sample tap_1141 = m_delay_8.read_linear(expr_1160);
			int gte_1128 = (clamp_1135 >= expr_1160);
			t_sample mul_1129 = (tap_1141 * gte_1128);
			t_sample abs_1127 = fabs(gen_1107);
			t_sample add_1137 = (m_average_6 + abs_1127);
			t_sample sub_1136 = (add_1137 - mul_1129);
			t_sample mul_1133 = (sub_1136 * eq_1132);
			t_sample counter_next_1142 = fixdenorm(mul_1134);
			t_sample average_next_1143 = fixdenorm(mul_1133);
			t_sample add_1120 = (m_counter_4 + ((int)1));
			t_sample clamp_1117 = ((add_1120 <= ((int)0)) ? ((int)0) : ((add_1120 >= expr_1160) ? expr_1160 : add_1120));
			t_sample div_1113 = safediv(m_average_3, clamp_1117);
			t_sample gen_1126 = div_1113;
			t_sample delta_1121 = __m_delta_43(expr_1160);
			int eq_1114 = (delta_1121 == ((int)0));
			t_sample mul_1116 = (clamp_1117 * eq_1114);
			t_sample tap_1123 = m_delay_5.read_linear(expr_1160);
			int gte_1110 = (clamp_1117 >= expr_1160);
			t_sample mul_1111 = (tap_1123 * gte_1110);
			t_sample abs_1109 = fabs(gen_1108);
			t_sample add_1119 = (m_average_3 + abs_1109);
			t_sample sub_1118 = (add_1119 - mul_1111);
			t_sample mul_1115 = (sub_1118 * eq_1114);
			t_sample counter_next_1124 = fixdenorm(mul_1116);
			t_sample average_next_1125 = fixdenorm(mul_1115);
			t_sample add_1156 = (gen_1144 + gen_1126);
			t_sample atodb_1146 = atodb(add_1156);
			t_sample expr_1159 = ((((atodb_1146 + tap_1155) + tap_1150) + tap_1148) * ((t_sample)0.25));
			t_sample gen_1165 = expr_1159;
			int gt_1047 = (gen_1165 > m_targetLevel_39);
			int gt_1451 = (gen_1279 > (-70));
			int switch_1043 = (gt_1047 ? ((int)0) : ((int)60000));
			__m_count_44 = (m_loadbang_2 ? 0 : (fixdenorm(__m_count_44 + ((int)1))));
			int carry_45 = 0;
			if ((m_loadbang_2 != 0)) {
				__m_count_44 = 0;
				__m_carry_46 = 0;
				
			} else if (((expr_1453 > 0) && (__m_count_44 >= expr_1453))) {
				int wraps_47 = (__m_count_44 / expr_1453);
				__m_carry_46 = (__m_carry_46 + wraps_47);
				__m_count_44 = (__m_count_44 - (wraps_47 * expr_1453));
				carry_45 = 1;
				
			};
			int counter_1018 = __m_count_44;
			int counter_1019 = carry_45;
			int counter_1020 = __m_carry_46;
			__m_latch_48 = (((counter_1019 + m_loadbang_2) != 0) ? m_loadbang_2 : __m_latch_48);
			t_sample latch_1012 = __m_latch_48;
			int switch_1013 = (latch_1012 ? ((int)1) : ((int)0));
			int switch_1044 = (gt_1047 ? ((int)0) : ((int)1));
			int neq_1027 = (switch_1044 != ((int)1));
			t_sample switch_1042 = (gt_1047 ? gen_1279 : ((int)0));
			t_sample dbtoa_1007 = dbtoa(switch_1042);
			int neq_1041 = (dbtoa_1007 != ((int)1));
			int switch_1037 = (neq_1041 ? ((int)0) : ((int)1000));
			t_sample switch_1040 = (neq_1041 ? switch_1042 : ((int)0));
			int gt_1036 = (switch_1040 > m_targetLevel_39);
			int switch_1028 = (gt_1036 ? ((int)0) : ((int)15000));
			int switch_1023 = (neq_1027 ? switch_1028 : ((int)0));
			int switch_1032 = (gt_1036 ? ((int)3000) : ((int)0));
			int switch_1025 = (neq_1027 ? switch_1032 : ((int)0));
			int iftrue_49 = ((switch_1043 + switch_1025) + switch_1023);
			int switch_1005 = (gt_1451 ? iftrue_49 : switch_1037);
			int switch_1022 = (switch_1013 ? ((int)1) : switch_1005);
			t_sample expr_1452 = ((samplerate * switch_1022) * ((t_sample)0.001));
			t_sample switch_1038 = (neq_1041 ? ((int)0) : m_history_1);
			t_sample add_1031 = (m_history_1 + ((t_sample)0.1));
			t_sample switch_1029 = (gt_1036 ? ((int)0) : add_1031);
			t_sample switch_1024 = (neq_1027 ? switch_1029 : ((int)0));
			t_sample sub_1035 = (m_history_1 - ((t_sample)0.1));
			t_sample switch_1033 = (gt_1036 ? sub_1035 : ((int)0));
			t_sample switch_1026 = (neq_1027 ? switch_1033 : ((int)0));
			t_sample iftrue_50 = ((switch_1044 + switch_1026) + switch_1024);
			t_sample switch_1006 = (gt_1451 ? iftrue_50 : switch_1038);
			t_sample switch_1011 = (switch_1013 ? ((int)1) : switch_1006);
			t_sample clamp_1358 = ((switch_1011 <= ((int)0)) ? ((int)0) : ((switch_1011 >= ((int)1)) ? ((int)1) : switch_1011));
			t_sample iup_52 = (1 / maximum(1, abs(expr_1452)));
			t_sample idown_53 = (1 / maximum(1, abs(expr_1452)));
			__m_slide_51 = fixdenorm((__m_slide_51 + (((clamp_1358 > __m_slide_51) ? iup_52 : idown_53) * (clamp_1358 - __m_slide_51))));
			t_sample slide_1003 = __m_slide_51;
			t_sample gen_1454 = slide_1003;
			t_sample history_1000_next_1474 = fixdenorm(gen_1454);
			m_delay_38.write(atodb_1260);
			m_counter_22 = counter_next_1238;
			m_average_21 = average_next_1239;
			m_delay_23.write(abs_1223);
			m_counter_25 = counter_next_1256;
			m_average_24 = average_next_1257;
			m_delay_26.write(abs_1241);
			m_history_32 = history_1195_next_1205;
			m_history_33 = history_1199_next_1204;
			m_history_34 = history_1197_next_1203;
			m_history_31 = history_1173_next_1178;
			m_history_28 = history_1171_next_1181;
			m_history_29 = history_1175_next_1180;
			m_history_30 = history_1169_next_1179;
			m_y_27 = y0_next_1219;
			m_y_27 = y0_next_1220;
			m_history_35 = history_1193_next_1202;
			m_delay_36.write(atodb_1260);
			m_delay_37.write(atodb_1260);
			m_delay_20.write(atodb_1146);
			m_counter_4 = counter_next_1124;
			m_average_3 = average_next_1125;
			m_delay_5.write(abs_1109);
			m_counter_7 = counter_next_1142;
			m_average_6 = average_next_1143;
			m_delay_8.write(abs_1127);
			m_history_14 = history_1057_next_1067;
			m_history_15 = history_1061_next_1066;
			m_history_16 = history_1055_next_1065;
			m_history_13 = history_1079_next_1088;
			m_history_10 = history_1081_next_1091;
			m_history_11 = history_1085_next_1090;
			m_history_12 = history_1083_next_1089;
			m_y_9 = y0_next_1105;
			m_y_9 = y0_next_1106;
			m_history_17 = history_1059_next_1064;
			m_delay_18.write(atodb_1146);
			m_delay_19.write(atodb_1146);
			m_loadbang_2 = loadbang_next_1473;
			m_history_1 = history_1000_next_1474;
			m_delay_5.step();
			m_delay_8.step();
			m_delay_18.step();
			m_delay_19.step();
			m_delay_20.step();
			m_delay_23.step();
			m_delay_26.step();
			m_delay_36.step();
			m_delay_37.step();
			m_delay_38.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			(*(__out3++)) = out3;
			
		};
		return __exception;
		
	};
	inline void set_targetLevel(t_param _value) {
		m_targetLevel_39 = (_value < -40 ? -40 : (_value > 0 ? 0 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 2;
int gen_kernel_numouts = 3;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 1; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "L In", "L In" };
const char *gen_kernel_outnames[] = { "out1", "out2", "out3" };

/// Invoke the signal process of a State object

int perform(CommonState *cself, t_sample **ins, long numins, t_sample **outs, long numouts, long n) {
	State* self = (State *)cself;
	return self->perform(ins, outs, n);
}

/// Reset all parameters and stateful operators of a State object

void reset(CommonState *cself) {
	State* self = (State *)cself;
	self->reset(cself->sr, cself->vs);
}

/// Set a parameter of a State object

void setparameter(CommonState *cself, long index, t_param value, void *ref) {
	State *self = (State *)cself;
	switch (index) {
		case 0: self->set_targetLevel(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_targetLevel_39; break;
		
		default: break;
	}
}

/// Get the name of a parameter of a State object

const char *getparametername(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].name;
	}
	return 0;
}

/// Get the minimum value of a parameter of a State object

t_param getparametermin(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmin;
	}
	return 0;
}

/// Get the maximum value of a parameter of a State object

t_param getparametermax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmax;
	}
	return 0;
}

/// Get parameter of a State object has a minimum and maximum value

char getparameterhasminmax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].hasminmax;
	}
	return 0;
}

/// Get the units of a parameter of a State object

const char *getparameterunits(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].units;
	}
	return 0;
}

/// Get the size of the state of all parameters of a State object

size_t getstatesize(CommonState *cself) {
	return genlib_getstatesize(cself, &getparameter);
}

/// Get the state of all parameters of a State object

short getstate(CommonState *cself, char *state) {
	return genlib_getstate(cself, state, &getparameter);
}

/// set the state of all parameters of a State object

short setstate(CommonState *cself, const char *state) {
	return genlib_setstate(cself, state, &setparameter);
}

/// Allocate and configure a new State object and it's internal CommonState:

void *create(t_param sr, long vs) {
	State *self = new State;
	self->reset(sr, vs);
	ParamInfo *pi;
	self->__commonstate.inputnames = gen_kernel_innames;
	self->__commonstate.outputnames = gen_kernel_outnames;
	self->__commonstate.numins = gen_kernel_numins;
	self->__commonstate.numouts = gen_kernel_numouts;
	self->__commonstate.sr = sr;
	self->__commonstate.vs = vs;
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(1 * sizeof(ParamInfo));
	self->__commonstate.numparams = 1;
	// initialize parameter 0 ("m_targetLevel_39")
	pi = self->__commonstate.params + 0;
	pi->name = "targetLevel";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_targetLevel_39;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -40;
	pi->outputmax = 0;
	pi->exp = 0;
	pi->units = "";		// no units defined
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // C74_GENPLUGIN::
