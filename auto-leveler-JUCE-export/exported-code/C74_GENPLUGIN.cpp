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
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__out1 == 0) || (__out2 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample expr_8572 = ((samplerate * ((int)3000)) * ((t_sample)0.001));
		t_sample div_8565 = (expr_8572 * ((t_sample)0.25));
		t_sample mul_8564 = (div_8565 * ((int)2));
		t_sample mul_8563 = (div_8565 * ((int)3));
		t_sample omega = safediv(((t_sample)6283.1853071796), samplerate);
		t_sample sn = sin(omega);
		t_sample cs = cos(omega);
		t_sample b0 = safediv(((int)1), ((((t_sample)2.2589254117942) - (((t_sample)0.25892541179417) * cs)) + (((t_sample)1.5867737153067) * sn)));
		t_sample a0 = ((((t_sample)1.2589254117942) * ((((t_sample)2.2589254117942) + (((t_sample)0.25892541179417) * cs)) + (((t_sample)1.5867737153067) * sn))) * b0);
		t_sample a1 = ((((t_sample)-2.5178508235883) * (((t_sample)0.25892541179417) + (((t_sample)2.2589254117942) * cs))) * b0);
		t_sample a2 = ((((t_sample)1.2589254117942) * ((((t_sample)2.2589254117942) + (((t_sample)0.25892541179417) * cs)) - (((t_sample)1.5867737153067) * sn))) * b0);
		t_sample b1 = ((((int)2) * (((t_sample)0.25892541179417) - (((t_sample)2.2589254117942) * cs))) * b0);
		t_sample b2 = (((((t_sample)2.2589254117942) - (((t_sample)0.25892541179417) * cs)) - (((t_sample)1.5867737153067) * sn)) * b0);
		t_sample expr_8512 = a0;
		t_sample expr_8513 = a1;
		t_sample expr_8514 = a2;
		t_sample expr_8515 = b1;
		t_sample expr_8516 = b2;
		t_sample expr_8458 = ((samplerate * ((int)3000)) * ((t_sample)0.001));
		t_sample div_8451 = (expr_8458 * ((t_sample)0.25));
		t_sample mul_8450 = (div_8451 * ((int)2));
		t_sample mul_8449 = (div_8451 * ((int)3));
		t_sample omega_8643 = safediv(((t_sample)6283.1853071796), samplerate);
		t_sample sn_8647 = sin(omega_8643);
		t_sample cs_8641 = cos(omega_8643);
		t_sample b_8648 = safediv(((int)1), ((((t_sample)2.2589254117942) - (((t_sample)0.25892541179417) * cs_8641)) + (((t_sample)1.5867737153067) * sn_8647)));
		t_sample a_8649 = ((((t_sample)1.2589254117942) * ((((t_sample)2.2589254117942) + (((t_sample)0.25892541179417) * cs_8641)) + (((t_sample)1.5867737153067) * sn_8647))) * b_8648);
		t_sample a_8646 = ((((t_sample)-2.5178508235883) * (((t_sample)0.25892541179417) + (((t_sample)2.2589254117942) * cs_8641))) * b_8648);
		t_sample a_8638 = ((((t_sample)1.2589254117942) * ((((t_sample)2.2589254117942) + (((t_sample)0.25892541179417) * cs_8641)) - (((t_sample)1.5867737153067) * sn_8647))) * b_8648);
		t_sample b_8645 = ((((int)2) * (((t_sample)0.25892541179417) - (((t_sample)2.2589254117942) * cs_8641))) * b_8648);
		t_sample b_8639 = (((((t_sample)2.2589254117942) - (((t_sample)0.25892541179417) * cs_8641)) - (((t_sample)1.5867737153067) * sn_8647)) * b_8648);
		t_sample expr_8398 = a_8649;
		t_sample expr_8399 = a_8646;
		t_sample expr_8400 = a_8638;
		t_sample expr_8401 = b_8645;
		t_sample expr_8402 = b_8639;
		t_sample expr_8347 = ((((int)500) * samplerate) * ((t_sample)0.001));
		t_sample loadbang_next_8654 = fixdenorm(((int)0));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample mul_8579 = (in1 * m_history_1);
			t_sample out1 = mul_8579;
			t_sample mul_8578 = (in2 * m_history_1);
			t_sample out2 = mul_8578;
			t_sample tap_8567 = m_delay_38.read_linear(div_8565);
			t_sample tap_8562 = m_delay_37.read_linear(mul_8564);
			t_sample tap_8560 = m_delay_36.read_linear(mul_8563);
			t_sample mix_8682 = (m_y_27 + (((t_sample)0.014247103707103) * (mul_8579 - m_y_27)));
			t_sample mix_8508 = mix_8682;
			t_sample sub_8465 = (mul_8579 - mix_8508);
			t_sample mul_8494 = (m_history_35 * expr_8514);
			t_sample mul_8496 = (m_history_33 * expr_8513);
			t_sample mul_8499 = (sub_8465 * expr_8512);
			t_sample mul_8492 = (m_history_32 * expr_8515);
			t_sample mul_8490 = (m_history_34 * expr_8516);
			t_sample sub_8498 = (((mul_8499 + mul_8496) + mul_8494) - (mul_8490 + mul_8492));
			t_sample gen_8504 = sub_8498;
			t_sample history_8495_next_8500 = fixdenorm(m_history_33);
			t_sample history_8491_next_8501 = fixdenorm(m_history_32);
			t_sample history_8497_next_8502 = fixdenorm(sub_8465);
			t_sample history_8493_next_8503 = fixdenorm(sub_8498);
			t_sample gen_8519 = gen_8504;
			t_sample mix_8683 = (m_y_27 + (((t_sample)0.014247103707103) * (mul_8578 - m_y_27)));
			t_sample mix_8505 = mix_8683;
			t_sample sub_8464 = (mul_8578 - mix_8505);
			t_sample mul_8470 = (m_history_31 * expr_8514);
			t_sample mul_8472 = (m_history_29 * expr_8513);
			t_sample mul_8475 = (sub_8464 * expr_8512);
			t_sample mul_8468 = (m_history_28 * expr_8515);
			t_sample mul_8466 = (m_history_30 * expr_8516);
			t_sample sub_8474 = (((mul_8475 + mul_8472) + mul_8470) - (mul_8466 + mul_8468));
			t_sample gen_8480 = sub_8474;
			t_sample history_8471_next_8476 = fixdenorm(m_history_29);
			t_sample history_8467_next_8477 = fixdenorm(m_history_28);
			t_sample history_8473_next_8478 = fixdenorm(sub_8464);
			t_sample history_8469_next_8479 = fixdenorm(sub_8474);
			t_sample gen_8520 = gen_8480;
			t_sample y0_next_8517 = fixdenorm(mix_8508);
			t_sample y0_next_8518 = fixdenorm(mix_8505);
			t_sample add_8550 = (m_counter_25 + ((int)1));
			t_sample clamp_8547 = ((add_8550 <= ((int)0)) ? ((int)0) : ((add_8550 >= expr_8572) ? expr_8572 : add_8550));
			t_sample div_8543 = safediv(m_average_24, clamp_8547);
			t_sample gen_8556 = div_8543;
			t_sample delta_8551 = __m_delta_40(expr_8572);
			int eq_8544 = (delta_8551 == ((int)0));
			t_sample mul_8546 = (clamp_8547 * eq_8544);
			t_sample tap_8553 = m_delay_26.read_linear(expr_8572);
			int gte_8540 = (clamp_8547 >= expr_8572);
			t_sample mul_8541 = (tap_8553 * gte_8540);
			t_sample abs_8539 = fabs(gen_8519);
			t_sample add_8549 = (m_average_24 + abs_8539);
			t_sample sub_8548 = (add_8549 - mul_8541);
			t_sample mul_8545 = (sub_8548 * eq_8544);
			t_sample counter_next_8554 = fixdenorm(mul_8546);
			t_sample average_next_8555 = fixdenorm(mul_8545);
			t_sample add_8532 = (m_counter_22 + ((int)1));
			t_sample clamp_8529 = ((add_8532 <= ((int)0)) ? ((int)0) : ((add_8532 >= expr_8572) ? expr_8572 : add_8532));
			t_sample div_8525 = safediv(m_average_21, clamp_8529);
			t_sample gen_8538 = div_8525;
			t_sample delta_8533 = __m_delta_41(expr_8572);
			int eq_8526 = (delta_8533 == ((int)0));
			t_sample mul_8528 = (clamp_8529 * eq_8526);
			t_sample tap_8535 = m_delay_23.read_linear(expr_8572);
			int gte_8522 = (clamp_8529 >= expr_8572);
			t_sample mul_8523 = (tap_8535 * gte_8522);
			t_sample abs_8521 = fabs(gen_8520);
			t_sample add_8531 = (m_average_21 + abs_8521);
			t_sample sub_8530 = (add_8531 - mul_8523);
			t_sample mul_8527 = (sub_8530 * eq_8526);
			t_sample counter_next_8536 = fixdenorm(mul_8528);
			t_sample average_next_8537 = fixdenorm(mul_8527);
			t_sample add_8568 = (gen_8556 + gen_8538);
			t_sample atodb_8558 = atodb(add_8568);
			t_sample expr_8571 = ((((atodb_8558 + tap_8567) + tap_8562) + tap_8560) * ((t_sample)0.25));
			t_sample gen_8577 = expr_8571;
			t_sample tap_8453 = m_delay_20.read_linear(div_8451);
			t_sample tap_8448 = m_delay_19.read_linear(mul_8450);
			t_sample tap_8446 = m_delay_18.read_linear(mul_8449);
			t_sample mix_8684 = (m_y_9 + (((t_sample)0.014247103707103) * (in2 - m_y_9)));
			t_sample mix_8391 = mix_8684;
			t_sample sub_8350 = (in2 - mix_8391);
			t_sample mul_8356 = (m_history_17 * expr_8400);
			t_sample mul_8358 = (m_history_15 * expr_8399);
			t_sample mul_8361 = (sub_8350 * expr_8398);
			t_sample mul_8354 = (m_history_14 * expr_8401);
			t_sample mul_8352 = (m_history_16 * expr_8402);
			t_sample sub_8360 = (((mul_8361 + mul_8358) + mul_8356) - (mul_8352 + mul_8354));
			t_sample gen_8366 = sub_8360;
			t_sample history_8357_next_8362 = fixdenorm(m_history_15);
			t_sample history_8353_next_8363 = fixdenorm(m_history_14);
			t_sample history_8359_next_8364 = fixdenorm(sub_8350);
			t_sample history_8355_next_8365 = fixdenorm(sub_8360);
			t_sample gen_8406 = gen_8366;
			t_sample mix_8685 = (m_y_9 + (((t_sample)0.014247103707103) * (in1 - m_y_9)));
			t_sample mix_8394 = mix_8685;
			t_sample sub_8351 = (in1 - mix_8394);
			t_sample mul_8380 = (m_history_13 * expr_8400);
			t_sample mul_8382 = (m_history_11 * expr_8399);
			t_sample mul_8385 = (sub_8351 * expr_8398);
			t_sample mul_8378 = (m_history_10 * expr_8401);
			t_sample mul_8376 = (m_history_12 * expr_8402);
			t_sample sub_8384 = (((mul_8385 + mul_8382) + mul_8380) - (mul_8376 + mul_8378));
			t_sample gen_8390 = sub_8384;
			t_sample history_8381_next_8386 = fixdenorm(m_history_11);
			t_sample history_8377_next_8387 = fixdenorm(m_history_10);
			t_sample history_8383_next_8388 = fixdenorm(sub_8351);
			t_sample history_8379_next_8389 = fixdenorm(sub_8384);
			t_sample gen_8405 = gen_8390;
			t_sample y0_next_8403 = fixdenorm(mix_8391);
			t_sample y0_next_8404 = fixdenorm(mix_8394);
			t_sample add_8436 = (m_counter_7 + ((int)1));
			t_sample clamp_8433 = ((add_8436 <= ((int)0)) ? ((int)0) : ((add_8436 >= expr_8458) ? expr_8458 : add_8436));
			t_sample div_8429 = safediv(m_average_6, clamp_8433);
			t_sample gen_8442 = div_8429;
			t_sample delta_8437 = __m_delta_42(expr_8458);
			int eq_8430 = (delta_8437 == ((int)0));
			t_sample mul_8432 = (clamp_8433 * eq_8430);
			t_sample tap_8439 = m_delay_8.read_linear(expr_8458);
			int gte_8426 = (clamp_8433 >= expr_8458);
			t_sample mul_8427 = (tap_8439 * gte_8426);
			t_sample abs_8425 = fabs(gen_8405);
			t_sample add_8435 = (m_average_6 + abs_8425);
			t_sample sub_8434 = (add_8435 - mul_8427);
			t_sample mul_8431 = (sub_8434 * eq_8430);
			t_sample counter_next_8440 = fixdenorm(mul_8432);
			t_sample average_next_8441 = fixdenorm(mul_8431);
			t_sample add_8418 = (m_counter_4 + ((int)1));
			t_sample clamp_8415 = ((add_8418 <= ((int)0)) ? ((int)0) : ((add_8418 >= expr_8458) ? expr_8458 : add_8418));
			t_sample div_8411 = safediv(m_average_3, clamp_8415);
			t_sample gen_8424 = div_8411;
			t_sample delta_8419 = __m_delta_43(expr_8458);
			int eq_8412 = (delta_8419 == ((int)0));
			t_sample mul_8414 = (clamp_8415 * eq_8412);
			t_sample tap_8421 = m_delay_5.read_linear(expr_8458);
			int gte_8408 = (clamp_8415 >= expr_8458);
			t_sample mul_8409 = (tap_8421 * gte_8408);
			t_sample abs_8407 = fabs(gen_8406);
			t_sample add_8417 = (m_average_3 + abs_8407);
			t_sample sub_8416 = (add_8417 - mul_8409);
			t_sample mul_8413 = (sub_8416 * eq_8412);
			t_sample counter_next_8422 = fixdenorm(mul_8414);
			t_sample average_next_8423 = fixdenorm(mul_8413);
			t_sample add_8454 = (gen_8442 + gen_8424);
			t_sample atodb_8444 = atodb(add_8454);
			t_sample expr_8457 = ((((atodb_8444 + tap_8453) + tap_8448) + tap_8446) * ((t_sample)0.25));
			t_sample gen_8463 = expr_8457;
			int gt_8345 = (gen_8463 > m_targetLevel_39);
			int gt_8302 = (gen_8577 > (-76));
			int switch_8341 = (gt_8345 ? ((int)0) : ((int)60000));
			int switch_8342 = (gt_8345 ? ((int)0) : ((int)1));
			int neq_8325 = (switch_8342 != ((int)1));
			__m_count_44 = (m_loadbang_2 ? 0 : (fixdenorm(__m_count_44 + ((int)1))));
			int carry_45 = 0;
			if ((m_loadbang_2 != 0)) {
				__m_count_44 = 0;
				__m_carry_46 = 0;
				
			} else if (((expr_8347 > 0) && (__m_count_44 >= expr_8347))) {
				int wraps_47 = (__m_count_44 / expr_8347);
				__m_carry_46 = (__m_carry_46 + wraps_47);
				__m_count_44 = (__m_count_44 - (wraps_47 * expr_8347));
				carry_45 = 1;
				
			};
			int counter_8316 = __m_count_44;
			int counter_8317 = carry_45;
			int counter_8318 = __m_carry_46;
			__m_latch_48 = (((counter_8317 + m_loadbang_2) != 0) ? m_loadbang_2 : __m_latch_48);
			t_sample latch_8310 = __m_latch_48;
			int switch_8311 = (latch_8310 ? ((int)1) : ((int)0));
			t_sample switch_8340 = (gt_8345 ? gen_8577 : ((int)0));
			t_sample dbtoa_8305 = dbtoa(switch_8340);
			int neq_8339 = (dbtoa_8305 != ((int)1));
			int switch_8335 = (neq_8339 ? ((int)0) : ((int)1000));
			t_sample switch_8336 = (neq_8339 ? ((int)0) : m_history_1);
			t_sample switch_8338 = (neq_8339 ? switch_8340 : ((int)0));
			int gt_8334 = (switch_8338 > m_targetLevel_39);
			int switch_8326 = (gt_8334 ? ((int)0) : ((int)15000));
			int switch_8321 = (neq_8325 ? switch_8326 : ((int)0));
			int switch_8330 = (gt_8334 ? ((int)3000) : ((int)0));
			int switch_8323 = (neq_8325 ? switch_8330 : ((int)0));
			int iftrue_49 = ((switch_8341 + switch_8323) + switch_8321);
			int switch_8303 = (gt_8302 ? iftrue_49 : switch_8335);
			int switch_8320 = (switch_8311 ? ((int)1) : switch_8303);
			t_sample expr_8346 = ((samplerate * switch_8320) * ((t_sample)0.001));
			t_sample add_8329 = (m_history_1 + ((t_sample)0.1));
			t_sample switch_8327 = (gt_8334 ? ((int)0) : add_8329);
			t_sample switch_8322 = (neq_8325 ? switch_8327 : ((int)0));
			t_sample sub_8333 = (m_history_1 - ((t_sample)0.1));
			t_sample switch_8331 = (gt_8334 ? sub_8333 : ((int)0));
			t_sample switch_8324 = (neq_8325 ? switch_8331 : ((int)0));
			t_sample iftrue_50 = ((switch_8342 + switch_8324) + switch_8322);
			t_sample switch_8304 = (gt_8302 ? iftrue_50 : switch_8336);
			t_sample switch_8309 = (switch_8311 ? ((int)1) : switch_8304);
			t_sample iup_52 = (1 / maximum(1, abs(expr_8346)));
			t_sample idown_53 = (1 / maximum(1, abs(expr_8346)));
			__m_slide_51 = fixdenorm((__m_slide_51 + (((switch_8309 > __m_slide_51) ? iup_52 : idown_53) * (switch_8309 - __m_slide_51))));
			t_sample slide_8301 = __m_slide_51;
			t_sample gen_8348 = slide_8301;
			t_sample history_8298_next_8655 = fixdenorm(gen_8348);
			m_delay_38.write(atodb_8558);
			m_counter_22 = counter_next_8536;
			m_average_21 = average_next_8537;
			m_delay_23.write(abs_8521);
			m_counter_25 = counter_next_8554;
			m_average_24 = average_next_8555;
			m_delay_26.write(abs_8539);
			m_history_32 = history_8493_next_8503;
			m_history_33 = history_8497_next_8502;
			m_history_34 = history_8491_next_8501;
			m_history_31 = history_8471_next_8476;
			m_history_28 = history_8469_next_8479;
			m_history_29 = history_8473_next_8478;
			m_history_30 = history_8467_next_8477;
			m_y_27 = y0_next_8517;
			m_y_27 = y0_next_8518;
			m_history_35 = history_8495_next_8500;
			m_delay_36.write(atodb_8558);
			m_delay_37.write(atodb_8558);
			m_delay_20.write(atodb_8444);
			m_counter_4 = counter_next_8422;
			m_average_3 = average_next_8423;
			m_delay_5.write(abs_8407);
			m_counter_7 = counter_next_8440;
			m_average_6 = average_next_8441;
			m_delay_8.write(abs_8425);
			m_history_14 = history_8355_next_8365;
			m_history_15 = history_8359_next_8364;
			m_history_16 = history_8353_next_8363;
			m_history_13 = history_8381_next_8386;
			m_history_10 = history_8379_next_8389;
			m_history_11 = history_8383_next_8388;
			m_history_12 = history_8377_next_8387;
			m_y_9 = y0_next_8403;
			m_y_9 = y0_next_8404;
			m_history_17 = history_8357_next_8362;
			m_delay_18.write(atodb_8444);
			m_delay_19.write(atodb_8444);
			m_loadbang_2 = loadbang_next_8654;
			m_history_1 = history_8298_next_8655;
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
			
		};
		return __exception;
		
	};
	inline void set_targetLevel(t_param _value) {
		m_targetLevel_39 = (_value < -70 ? -70 : (_value > 0 ? 0 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 2;
int gen_kernel_numouts = 2;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 1; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "L In", "L In" };
const char *gen_kernel_outnames[] = { "out1", "out2" };

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
	pi->outputmin = -70;
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
