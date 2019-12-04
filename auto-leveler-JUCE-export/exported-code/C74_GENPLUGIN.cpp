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
		m_targetLevel_39 = -14;
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
		t_sample * __out4 = __outs[3];
		t_sample * __out5 = __outs[4];
		t_sample * __out6 = __outs[5];
		t_sample * __out7 = __outs[6];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__out1 == 0) || (__out2 == 0) || (__out3 == 0) || (__out4 == 0) || (__out5 == 0) || (__out6 == 0) || (__out7 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample expr_1227 = ((samplerate * ((int)3000)) * ((t_sample)0.001));
		t_sample div_1220 = (expr_1227 * ((t_sample)0.25));
		t_sample mul_1219 = (div_1220 * ((int)2));
		t_sample mul_1218 = (div_1220 * ((int)3));
		t_sample omega = safediv(((t_sample)6283.1853071796), samplerate);
		t_sample sn = sin(omega);
		t_sample cs = cos(omega);
		t_sample b0 = safediv(((int)1), ((((t_sample)2.2589254117942) - (((t_sample)0.25892541179417) * cs)) + (((t_sample)1.5867737153067) * sn)));
		t_sample a0 = ((((t_sample)1.2589254117942) * ((((t_sample)2.2589254117942) + (((t_sample)0.25892541179417) * cs)) + (((t_sample)1.5867737153067) * sn))) * b0);
		t_sample a1 = ((((t_sample)-2.5178508235883) * (((t_sample)0.25892541179417) + (((t_sample)2.2589254117942) * cs))) * b0);
		t_sample a2 = ((((t_sample)1.2589254117942) * ((((t_sample)2.2589254117942) + (((t_sample)0.25892541179417) * cs)) - (((t_sample)1.5867737153067) * sn))) * b0);
		t_sample b1 = ((((int)2) * (((t_sample)0.25892541179417) - (((t_sample)2.2589254117942) * cs))) * b0);
		t_sample b2 = (((((t_sample)2.2589254117942) - (((t_sample)0.25892541179417) * cs)) - (((t_sample)1.5867737153067) * sn)) * b0);
		t_sample expr_1167 = a0;
		t_sample expr_1168 = a1;
		t_sample expr_1169 = a2;
		t_sample expr_1170 = b1;
		t_sample expr_1171 = b2;
		t_sample expr_1341 = ((samplerate * ((int)3000)) * ((t_sample)0.001));
		t_sample div_1334 = (expr_1341 * ((t_sample)0.25));
		t_sample mul_1333 = (div_1334 * ((int)2));
		t_sample mul_1332 = (div_1334 * ((int)3));
		t_sample omega_1354 = safediv(((t_sample)6283.1853071796), samplerate);
		t_sample sn_1358 = sin(omega_1354);
		t_sample cs_1352 = cos(omega_1354);
		t_sample b_1359 = safediv(((int)1), ((((t_sample)2.2589254117942) - (((t_sample)0.25892541179417) * cs_1352)) + (((t_sample)1.5867737153067) * sn_1358)));
		t_sample a_1360 = ((((t_sample)1.2589254117942) * ((((t_sample)2.2589254117942) + (((t_sample)0.25892541179417) * cs_1352)) + (((t_sample)1.5867737153067) * sn_1358))) * b_1359);
		t_sample a_1357 = ((((t_sample)-2.5178508235883) * (((t_sample)0.25892541179417) + (((t_sample)2.2589254117942) * cs_1352))) * b_1359);
		t_sample a_1350 = ((((t_sample)1.2589254117942) * ((((t_sample)2.2589254117942) + (((t_sample)0.25892541179417) * cs_1352)) - (((t_sample)1.5867737153067) * sn_1358))) * b_1359);
		t_sample b_1356 = ((((int)2) * (((t_sample)0.25892541179417) - (((t_sample)2.2589254117942) * cs_1352))) * b_1359);
		t_sample b_1351 = (((((t_sample)2.2589254117942) - (((t_sample)0.25892541179417) * cs_1352)) - (((t_sample)1.5867737153067) * sn_1358)) * b_1359);
		t_sample expr_1281 = a_1360;
		t_sample expr_1282 = a_1357;
		t_sample expr_1283 = a_1350;
		t_sample expr_1284 = b_1356;
		t_sample expr_1285 = b_1351;
		t_sample expr_1116 = ((((int)500) * samplerate) * ((t_sample)0.001));
		t_sample loadbang_next_1366 = fixdenorm(((int)0));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample out3 = m_history_1;
			t_sample mul_1348 = (in1 * m_history_1);
			t_sample out1 = mul_1348;
			t_sample tap_1222 = m_delay_38.read_linear(div_1220);
			t_sample tap_1217 = m_delay_37.read_linear(mul_1219);
			t_sample tap_1215 = m_delay_36.read_linear(mul_1218);
			t_sample mix_1686 = (m_y_27 + (((t_sample)0.014247103707103) * (in1 - m_y_27)));
			t_sample mix_1163 = mix_1686;
			t_sample sub_1120 = (in1 - mix_1163);
			t_sample mul_1149 = (m_history_34 * expr_1169);
			t_sample mul_1151 = (m_history_33 * expr_1168);
			t_sample mul_1154 = (sub_1120 * expr_1167);
			t_sample mul_1147 = (m_history_32 * expr_1170);
			t_sample mul_1145 = (m_history_35 * expr_1171);
			t_sample sub_1153 = (((mul_1154 + mul_1151) + mul_1149) - (mul_1145 + mul_1147));
			t_sample gen_1159 = sub_1153;
			t_sample history_1146_next_1155 = fixdenorm(m_history_32);
			t_sample history_1150_next_1156 = fixdenorm(m_history_33);
			t_sample history_1152_next_1157 = fixdenorm(sub_1120);
			t_sample history_1148_next_1158 = fixdenorm(sub_1153);
			t_sample gen_1174 = gen_1159;
			t_sample mix_1687 = (m_y_27 + (((t_sample)0.014247103707103) * (in2 - m_y_27)));
			t_sample mix_1160 = mix_1687;
			t_sample sub_1119 = (in2 - mix_1160);
			t_sample mul_1125 = (m_history_30 * expr_1169);
			t_sample mul_1127 = (m_history_29 * expr_1168);
			t_sample mul_1130 = (sub_1119 * expr_1167);
			t_sample mul_1123 = (m_history_28 * expr_1170);
			t_sample mul_1121 = (m_history_31 * expr_1171);
			t_sample sub_1129 = (((mul_1130 + mul_1127) + mul_1125) - (mul_1121 + mul_1123));
			t_sample gen_1135 = sub_1129;
			t_sample history_1122_next_1131 = fixdenorm(m_history_28);
			t_sample history_1126_next_1132 = fixdenorm(m_history_29);
			t_sample history_1128_next_1133 = fixdenorm(sub_1119);
			t_sample history_1124_next_1134 = fixdenorm(sub_1129);
			t_sample gen_1175 = gen_1135;
			t_sample y0_next_1172 = fixdenorm(mix_1163);
			t_sample y0_next_1173 = fixdenorm(mix_1160);
			t_sample add_1205 = (m_counter_25 + ((int)1));
			t_sample clamp_1202 = ((add_1205 <= ((int)0)) ? ((int)0) : ((add_1205 >= expr_1227) ? expr_1227 : add_1205));
			t_sample div_1198 = safediv(m_average_24, clamp_1202);
			t_sample gen_1211 = div_1198;
			t_sample delta_1206 = __m_delta_40(expr_1227);
			int eq_1199 = (delta_1206 == ((int)0));
			t_sample mul_1201 = (clamp_1202 * eq_1199);
			t_sample tap_1208 = m_delay_26.read_linear(expr_1227);
			int gte_1195 = (clamp_1202 >= expr_1227);
			t_sample mul_1196 = (tap_1208 * gte_1195);
			t_sample abs_1194 = fabs(gen_1174);
			t_sample add_1204 = (m_average_24 + abs_1194);
			t_sample sub_1203 = (add_1204 - mul_1196);
			t_sample mul_1200 = (sub_1203 * eq_1199);
			t_sample counter_next_1209 = fixdenorm(mul_1201);
			t_sample average_next_1210 = fixdenorm(mul_1200);
			t_sample add_1187 = (m_counter_22 + ((int)1));
			t_sample clamp_1184 = ((add_1187 <= ((int)0)) ? ((int)0) : ((add_1187 >= expr_1227) ? expr_1227 : add_1187));
			t_sample div_1180 = safediv(m_average_21, clamp_1184);
			t_sample gen_1193 = div_1180;
			t_sample delta_1188 = __m_delta_41(expr_1227);
			int eq_1181 = (delta_1188 == ((int)0));
			t_sample mul_1183 = (clamp_1184 * eq_1181);
			t_sample tap_1190 = m_delay_23.read_linear(expr_1227);
			int gte_1177 = (clamp_1184 >= expr_1227);
			t_sample mul_1178 = (tap_1190 * gte_1177);
			t_sample abs_1176 = fabs(gen_1175);
			t_sample add_1186 = (m_average_21 + abs_1176);
			t_sample sub_1185 = (add_1186 - mul_1178);
			t_sample mul_1182 = (sub_1185 * eq_1181);
			t_sample counter_next_1191 = fixdenorm(mul_1183);
			t_sample average_next_1192 = fixdenorm(mul_1182);
			t_sample add_1223 = (gen_1211 + gen_1193);
			t_sample atodb_1213 = atodb(add_1223);
			t_sample expr_1226 = ((((atodb_1213 + tap_1222) + tap_1217) + tap_1215) * ((t_sample)0.25));
			t_sample gen_1232 = expr_1226;
			t_sample out5 = gen_1232;
			t_sample mul_1347 = (in2 * m_history_1);
			t_sample out2 = mul_1347;
			t_sample tap_1336 = m_delay_20.read_linear(div_1334);
			t_sample tap_1331 = m_delay_19.read_linear(mul_1333);
			t_sample tap_1329 = m_delay_18.read_linear(mul_1332);
			t_sample mix_1688 = (m_y_9 + (((t_sample)0.014247103707103) * (mul_1348 - m_y_9)));
			t_sample mix_1277 = mix_1688;
			t_sample sub_1234 = (mul_1348 - mix_1277);
			t_sample mul_1263 = (m_history_16 * expr_1283);
			t_sample mul_1265 = (m_history_15 * expr_1282);
			t_sample mul_1268 = (sub_1234 * expr_1281);
			t_sample mul_1261 = (m_history_14 * expr_1284);
			t_sample mul_1259 = (m_history_17 * expr_1285);
			t_sample sub_1267 = (((mul_1268 + mul_1265) + mul_1263) - (mul_1259 + mul_1261));
			t_sample gen_1273 = sub_1267;
			t_sample history_1260_next_1269 = fixdenorm(m_history_14);
			t_sample history_1264_next_1270 = fixdenorm(m_history_15);
			t_sample history_1266_next_1271 = fixdenorm(sub_1234);
			t_sample history_1262_next_1272 = fixdenorm(sub_1267);
			t_sample gen_1288 = gen_1273;
			t_sample mix_1689 = (m_y_9 + (((t_sample)0.014247103707103) * (mul_1347 - m_y_9)));
			t_sample mix_1274 = mix_1689;
			t_sample sub_1233 = (mul_1347 - mix_1274);
			t_sample mul_1239 = (m_history_13 * expr_1283);
			t_sample mul_1241 = (m_history_11 * expr_1282);
			t_sample mul_1244 = (sub_1233 * expr_1281);
			t_sample mul_1237 = (m_history_10 * expr_1284);
			t_sample mul_1235 = (m_history_12 * expr_1285);
			t_sample sub_1243 = (((mul_1244 + mul_1241) + mul_1239) - (mul_1235 + mul_1237));
			t_sample gen_1249 = sub_1243;
			t_sample history_1240_next_1245 = fixdenorm(m_history_11);
			t_sample history_1236_next_1246 = fixdenorm(m_history_10);
			t_sample history_1242_next_1247 = fixdenorm(sub_1233);
			t_sample history_1238_next_1248 = fixdenorm(sub_1243);
			t_sample gen_1289 = gen_1249;
			t_sample y0_next_1286 = fixdenorm(mix_1277);
			t_sample y0_next_1287 = fixdenorm(mix_1274);
			t_sample add_1319 = (m_counter_7 + ((int)1));
			t_sample clamp_1316 = ((add_1319 <= ((int)0)) ? ((int)0) : ((add_1319 >= expr_1341) ? expr_1341 : add_1319));
			t_sample div_1312 = safediv(m_average_6, clamp_1316);
			t_sample gen_1325 = div_1312;
			t_sample delta_1320 = __m_delta_42(expr_1341);
			int eq_1313 = (delta_1320 == ((int)0));
			t_sample mul_1315 = (clamp_1316 * eq_1313);
			t_sample tap_1322 = m_delay_8.read_linear(expr_1341);
			int gte_1309 = (clamp_1316 >= expr_1341);
			t_sample mul_1310 = (tap_1322 * gte_1309);
			t_sample abs_1308 = fabs(gen_1288);
			t_sample add_1318 = (m_average_6 + abs_1308);
			t_sample sub_1317 = (add_1318 - mul_1310);
			t_sample mul_1314 = (sub_1317 * eq_1313);
			t_sample counter_next_1323 = fixdenorm(mul_1315);
			t_sample average_next_1324 = fixdenorm(mul_1314);
			t_sample add_1301 = (m_counter_4 + ((int)1));
			t_sample clamp_1298 = ((add_1301 <= ((int)0)) ? ((int)0) : ((add_1301 >= expr_1341) ? expr_1341 : add_1301));
			t_sample div_1294 = safediv(m_average_3, clamp_1298);
			t_sample gen_1307 = div_1294;
			t_sample delta_1302 = __m_delta_43(expr_1341);
			int eq_1295 = (delta_1302 == ((int)0));
			t_sample mul_1297 = (clamp_1298 * eq_1295);
			t_sample tap_1304 = m_delay_5.read_linear(expr_1341);
			int gte_1291 = (clamp_1298 >= expr_1341);
			t_sample mul_1292 = (tap_1304 * gte_1291);
			t_sample abs_1290 = fabs(gen_1289);
			t_sample add_1300 = (m_average_3 + abs_1290);
			t_sample sub_1299 = (add_1300 - mul_1292);
			t_sample mul_1296 = (sub_1299 * eq_1295);
			t_sample counter_next_1305 = fixdenorm(mul_1297);
			t_sample average_next_1306 = fixdenorm(mul_1296);
			t_sample add_1337 = (gen_1325 + gen_1307);
			t_sample atodb_1327 = atodb(add_1337);
			t_sample expr_1340 = ((((atodb_1327 + tap_1336) + tap_1331) + tap_1329) * ((t_sample)0.25));
			t_sample gen_1346 = expr_1340;
			t_sample out4 = gen_1346;
			int gt_1114 = (gen_1232 > m_targetLevel_39);
			int gen_1118 = gt_1114;
			int switch_1110 = (gt_1114 ? ((int)0) : ((int)60000));
			int switch_1111 = (gt_1114 ? ((int)0) : ((int)1));
			int neq_1100 = (switch_1111 != ((int)1));
			__m_count_44 = (m_loadbang_2 ? 0 : (fixdenorm(__m_count_44 + ((int)1))));
			int carry_45 = 0;
			if ((m_loadbang_2 != 0)) {
				__m_count_44 = 0;
				__m_carry_46 = 0;
				
			} else if (((expr_1116 > 0) && (__m_count_44 >= expr_1116))) {
				int wraps_47 = (__m_count_44 / expr_1116);
				__m_carry_46 = (__m_carry_46 + wraps_47);
				__m_count_44 = (__m_count_44 - (wraps_47 * expr_1116));
				carry_45 = 1;
				
			};
			int counter_1091 = __m_count_44;
			int counter_1092 = carry_45;
			int counter_1093 = __m_carry_46;
			__m_latch_48 = (((counter_1092 + m_loadbang_2) != 0) ? m_loadbang_2 : __m_latch_48);
			t_sample latch_1085 = __m_latch_48;
			int switch_1086 = (latch_1085 ? ((int)1) : ((int)0));
			int gt_1109 = (gen_1346 > m_targetLevel_39);
			int switch_1101 = (gt_1109 ? ((int)0) : ((int)15000));
			int switch_1096 = (neq_1100 ? switch_1101 : ((int)0));
			int switch_1105 = (gt_1109 ? ((int)3000) : ((int)0));
			int switch_1098 = (neq_1100 ? switch_1105 : ((int)0));
			int iffalse_49 = ((switch_1110 + switch_1098) + switch_1096);
			int switch_1095 = (switch_1086 ? ((int)1) : iffalse_49);
			t_sample expr_1115 = ((samplerate * switch_1095) * ((t_sample)0.001));
			t_sample sub_1108 = (m_history_1 - ((t_sample)0.1));
			t_sample switch_1106 = (gt_1109 ? sub_1108 : ((int)0));
			t_sample switch_1099 = (neq_1100 ? switch_1106 : ((int)0));
			t_sample add_1104 = (m_history_1 + ((t_sample)0.1));
			t_sample switch_1102 = (gt_1109 ? ((int)0) : add_1104);
			t_sample switch_1097 = (neq_1100 ? switch_1102 : ((int)0));
			t_sample iffalse_50 = ((switch_1097 + switch_1111) + switch_1099);
			t_sample switch_1084 = (switch_1086 ? ((int)1) : iffalse_50);
			t_sample clamp_1078 = ((switch_1084 <= ((int)0)) ? ((int)0) : ((switch_1084 >= ((int)1)) ? ((int)1) : switch_1084));
			t_sample iup_52 = (1 / maximum(1, abs(expr_1115)));
			t_sample idown_53 = (1 / maximum(1, abs(expr_1115)));
			__m_slide_51 = fixdenorm((__m_slide_51 + (((clamp_1078 > __m_slide_51) ? iup_52 : idown_53) * (clamp_1078 - __m_slide_51))));
			t_sample slide_1080 = __m_slide_51;
			t_sample gen_1117 = slide_1080;
			t_sample out7 = gen_1118;
			t_sample out6 = gen_1117;
			t_sample history_1076_next_1367 = fixdenorm(gen_1117);
			m_delay_38.write(atodb_1213);
			m_counter_22 = counter_next_1191;
			m_average_21 = average_next_1192;
			m_delay_23.write(abs_1176);
			m_counter_25 = counter_next_1209;
			m_average_24 = average_next_1210;
			m_delay_26.write(abs_1194);
			m_history_32 = history_1148_next_1158;
			m_history_33 = history_1152_next_1157;
			m_history_34 = history_1150_next_1156;
			m_history_31 = history_1122_next_1131;
			m_history_28 = history_1124_next_1134;
			m_history_29 = history_1128_next_1133;
			m_history_30 = history_1126_next_1132;
			m_y_27 = y0_next_1172;
			m_y_27 = y0_next_1173;
			m_history_35 = history_1146_next_1155;
			m_delay_36.write(atodb_1213);
			m_delay_37.write(atodb_1213);
			m_delay_20.write(atodb_1327);
			m_counter_4 = counter_next_1305;
			m_average_3 = average_next_1306;
			m_delay_5.write(abs_1290);
			m_counter_7 = counter_next_1323;
			m_average_6 = average_next_1324;
			m_delay_8.write(abs_1308);
			m_history_14 = history_1262_next_1272;
			m_history_15 = history_1266_next_1271;
			m_history_16 = history_1264_next_1270;
			m_history_13 = history_1240_next_1245;
			m_history_10 = history_1238_next_1248;
			m_history_11 = history_1242_next_1247;
			m_history_12 = history_1236_next_1246;
			m_y_9 = y0_next_1286;
			m_y_9 = y0_next_1287;
			m_history_17 = history_1260_next_1269;
			m_delay_18.write(atodb_1327);
			m_delay_19.write(atodb_1327);
			m_loadbang_2 = loadbang_next_1366;
			m_history_1 = history_1076_next_1367;
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
			(*(__out4++)) = out4;
			(*(__out5++)) = out5;
			(*(__out6++)) = out6;
			(*(__out7++)) = out7;
			
		};
		return __exception;
		
	};
	inline void set_targetLevel(t_param _value) {
		m_targetLevel_39 = (_value < -30 ? -30 : (_value > 0 ? 0 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 2;
int gen_kernel_numouts = 7;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 1; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "L In", "L In" };
const char *gen_kernel_outnames[] = { "out1", "out2", "out3", "out4", "out5", "out6", "out7" };

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
	pi->outputmin = -30;
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
