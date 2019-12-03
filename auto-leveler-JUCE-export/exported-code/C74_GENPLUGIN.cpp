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
		t_sample expr_591 = ((samplerate * ((int)3000)) * ((t_sample)0.001));
		t_sample div_584 = (expr_591 * ((t_sample)0.25));
		t_sample mul_583 = (div_584 * ((int)2));
		t_sample mul_582 = (div_584 * ((int)3));
		t_sample omega = safediv(((t_sample)6283.1853071796), samplerate);
		t_sample sn = sin(omega);
		t_sample cs = cos(omega);
		t_sample b0 = safediv(((int)1), ((((t_sample)2.2589254117942) - (((t_sample)0.25892541179417) * cs)) + (((t_sample)1.5867737153067) * sn)));
		t_sample a0 = ((((t_sample)1.2589254117942) * ((((t_sample)2.2589254117942) + (((t_sample)0.25892541179417) * cs)) + (((t_sample)1.5867737153067) * sn))) * b0);
		t_sample a1 = ((((t_sample)-2.5178508235883) * (((t_sample)0.25892541179417) + (((t_sample)2.2589254117942) * cs))) * b0);
		t_sample a2 = ((((t_sample)1.2589254117942) * ((((t_sample)2.2589254117942) + (((t_sample)0.25892541179417) * cs)) - (((t_sample)1.5867737153067) * sn))) * b0);
		t_sample b1 = ((((int)2) * (((t_sample)0.25892541179417) - (((t_sample)2.2589254117942) * cs))) * b0);
		t_sample b2 = (((((t_sample)2.2589254117942) - (((t_sample)0.25892541179417) * cs)) - (((t_sample)1.5867737153067) * sn)) * b0);
		t_sample expr_531 = a0;
		t_sample expr_532 = a1;
		t_sample expr_533 = a2;
		t_sample expr_534 = b1;
		t_sample expr_535 = b2;
		t_sample expr_477 = ((samplerate * ((int)3000)) * ((t_sample)0.001));
		t_sample div_470 = (expr_477 * ((t_sample)0.25));
		t_sample mul_469 = (div_470 * ((int)2));
		t_sample mul_468 = (div_470 * ((int)3));
		t_sample omega_603 = safediv(((t_sample)6283.1853071796), samplerate);
		t_sample sn_607 = sin(omega_603);
		t_sample cs_601 = cos(omega_603);
		t_sample b_608 = safediv(((int)1), ((((t_sample)2.2589254117942) - (((t_sample)0.25892541179417) * cs_601)) + (((t_sample)1.5867737153067) * sn_607)));
		t_sample a_609 = ((((t_sample)1.2589254117942) * ((((t_sample)2.2589254117942) + (((t_sample)0.25892541179417) * cs_601)) + (((t_sample)1.5867737153067) * sn_607))) * b_608);
		t_sample a_606 = ((((t_sample)-2.5178508235883) * (((t_sample)0.25892541179417) + (((t_sample)2.2589254117942) * cs_601))) * b_608);
		t_sample a_599 = ((((t_sample)1.2589254117942) * ((((t_sample)2.2589254117942) + (((t_sample)0.25892541179417) * cs_601)) - (((t_sample)1.5867737153067) * sn_607))) * b_608);
		t_sample b_605 = ((((int)2) * (((t_sample)0.25892541179417) - (((t_sample)2.2589254117942) * cs_601))) * b_608);
		t_sample b_612 = (((((t_sample)2.2589254117942) - (((t_sample)0.25892541179417) * cs_601)) - (((t_sample)1.5867737153067) * sn_607)) * b_608);
		t_sample expr_417 = a_609;
		t_sample expr_418 = a_606;
		t_sample expr_419 = a_599;
		t_sample expr_420 = b_605;
		t_sample expr_421 = b_612;
		t_sample expr_366 = ((((int)500) * samplerate) * ((t_sample)0.001));
		t_sample loadbang_next_616 = fixdenorm(((int)0));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample mul_598 = (in1 * m_history_1);
			t_sample out1 = mul_598;
			t_sample mul_597 = (in2 * m_history_1);
			t_sample out2 = mul_597;
			t_sample tap_586 = m_delay_38.read_linear(div_584);
			t_sample tap_581 = m_delay_37.read_linear(mul_583);
			t_sample tap_579 = m_delay_36.read_linear(mul_582);
			t_sample mix_618 = (m_y_27 + (((t_sample)0.014247103707103) * (mul_598 - m_y_27)));
			t_sample mix_527 = mix_618;
			t_sample sub_484 = (mul_598 - mix_527);
			t_sample mul_518 = (sub_484 * expr_531);
			t_sample mul_515 = (m_history_33 * expr_532);
			t_sample mul_513 = (m_history_34 * expr_533);
			t_sample mul_509 = (m_history_35 * expr_535);
			t_sample mul_511 = (m_history_32 * expr_534);
			t_sample sub_517 = (((mul_513 + mul_515) + mul_518) - (mul_511 + mul_509));
			t_sample gen_523 = sub_517;
			t_sample history_510_next_519 = fixdenorm(m_history_32);
			t_sample history_514_next_520 = fixdenorm(m_history_33);
			t_sample history_516_next_521 = fixdenorm(sub_484);
			t_sample history_512_next_522 = fixdenorm(sub_517);
			t_sample gen_538 = gen_523;
			t_sample mix_619 = (m_y_27 + (((t_sample)0.014247103707103) * (mul_597 - m_y_27)));
			t_sample mix_524 = mix_619;
			t_sample sub_483 = (mul_597 - mix_524);
			t_sample mul_494 = (sub_483 * expr_531);
			t_sample mul_491 = (m_history_29 * expr_532);
			t_sample mul_489 = (m_history_31 * expr_533);
			t_sample mul_485 = (m_history_30 * expr_535);
			t_sample mul_487 = (m_history_28 * expr_534);
			t_sample sub_493 = (((mul_489 + mul_491) + mul_494) - (mul_487 + mul_485));
			t_sample gen_499 = sub_493;
			t_sample history_490_next_495 = fixdenorm(m_history_29);
			t_sample history_486_next_496 = fixdenorm(m_history_28);
			t_sample history_492_next_497 = fixdenorm(sub_483);
			t_sample history_488_next_498 = fixdenorm(sub_493);
			t_sample gen_539 = gen_499;
			t_sample y0_next_536 = fixdenorm(mix_527);
			t_sample y0_next_537 = fixdenorm(mix_524);
			t_sample add_569 = (m_counter_25 + ((int)1));
			t_sample clamp_566 = ((add_569 <= ((int)0)) ? ((int)0) : ((add_569 >= expr_591) ? expr_591 : add_569));
			t_sample div_562 = safediv(m_average_24, clamp_566);
			t_sample gen_575 = div_562;
			t_sample delta_570 = __m_delta_40(expr_591);
			int eq_563 = (delta_570 == ((int)0));
			t_sample mul_565 = (clamp_566 * eq_563);
			t_sample tap_572 = m_delay_26.read_linear(expr_591);
			int gte_559 = (clamp_566 >= expr_591);
			t_sample mul_560 = (tap_572 * gte_559);
			t_sample abs_558 = fabs(gen_538);
			t_sample add_568 = (m_average_24 + abs_558);
			t_sample sub_567 = (add_568 - mul_560);
			t_sample mul_564 = (sub_567 * eq_563);
			t_sample counter_next_573 = fixdenorm(mul_565);
			t_sample average_next_574 = fixdenorm(mul_564);
			t_sample add_551 = (m_counter_22 + ((int)1));
			t_sample clamp_548 = ((add_551 <= ((int)0)) ? ((int)0) : ((add_551 >= expr_591) ? expr_591 : add_551));
			t_sample div_544 = safediv(m_average_21, clamp_548);
			t_sample gen_557 = div_544;
			t_sample delta_552 = __m_delta_41(expr_591);
			int eq_545 = (delta_552 == ((int)0));
			t_sample mul_547 = (clamp_548 * eq_545);
			t_sample tap_554 = m_delay_23.read_linear(expr_591);
			int gte_541 = (clamp_548 >= expr_591);
			t_sample mul_542 = (tap_554 * gte_541);
			t_sample abs_540 = fabs(gen_539);
			t_sample add_550 = (m_average_21 + abs_540);
			t_sample sub_549 = (add_550 - mul_542);
			t_sample mul_546 = (sub_549 * eq_545);
			t_sample counter_next_555 = fixdenorm(mul_547);
			t_sample average_next_556 = fixdenorm(mul_546);
			t_sample add_587 = (gen_575 + gen_557);
			t_sample atodb_577 = atodb(add_587);
			t_sample expr_590 = ((((atodb_577 + tap_586) + tap_581) + tap_579) * ((t_sample)0.25));
			t_sample gen_596 = expr_590;
			t_sample tap_472 = m_delay_20.read_linear(div_470);
			t_sample tap_467 = m_delay_19.read_linear(mul_469);
			t_sample tap_465 = m_delay_18.read_linear(mul_468);
			t_sample mix_620 = (m_y_9 + (((t_sample)0.014247103707103) * (in1 - m_y_9)));
			t_sample mix_413 = mix_620;
			t_sample sub_370 = (in1 - mix_413);
			t_sample mul_404 = (sub_370 * expr_417);
			t_sample mul_401 = (m_history_15 * expr_418);
			t_sample mul_399 = (m_history_17 * expr_419);
			t_sample mul_395 = (m_history_16 * expr_421);
			t_sample mul_397 = (m_history_14 * expr_420);
			t_sample sub_403 = (((mul_399 + mul_401) + mul_404) - (mul_397 + mul_395));
			t_sample gen_409 = sub_403;
			t_sample history_400_next_405 = fixdenorm(m_history_15);
			t_sample history_396_next_406 = fixdenorm(m_history_14);
			t_sample history_402_next_407 = fixdenorm(sub_370);
			t_sample history_398_next_408 = fixdenorm(sub_403);
			t_sample gen_424 = gen_409;
			t_sample mix_621 = (m_y_9 + (((t_sample)0.014247103707103) * (in2 - m_y_9)));
			t_sample mix_410 = mix_621;
			t_sample sub_369 = (in2 - mix_410);
			t_sample mul_380 = (sub_369 * expr_417);
			t_sample mul_377 = (m_history_11 * expr_418);
			t_sample mul_375 = (m_history_13 * expr_419);
			t_sample mul_371 = (m_history_12 * expr_421);
			t_sample mul_373 = (m_history_10 * expr_420);
			t_sample sub_379 = (((mul_375 + mul_377) + mul_380) - (mul_373 + mul_371));
			t_sample gen_385 = sub_379;
			t_sample history_376_next_381 = fixdenorm(m_history_11);
			t_sample history_372_next_382 = fixdenorm(m_history_10);
			t_sample history_378_next_383 = fixdenorm(sub_369);
			t_sample history_374_next_384 = fixdenorm(sub_379);
			t_sample gen_425 = gen_385;
			t_sample y0_next_422 = fixdenorm(mix_413);
			t_sample y0_next_423 = fixdenorm(mix_410);
			t_sample add_455 = (m_counter_7 + ((int)1));
			t_sample clamp_452 = ((add_455 <= ((int)0)) ? ((int)0) : ((add_455 >= expr_477) ? expr_477 : add_455));
			t_sample div_448 = safediv(m_average_6, clamp_452);
			t_sample gen_461 = div_448;
			t_sample delta_456 = __m_delta_42(expr_477);
			int eq_449 = (delta_456 == ((int)0));
			t_sample mul_451 = (clamp_452 * eq_449);
			t_sample tap_458 = m_delay_8.read_linear(expr_477);
			int gte_445 = (clamp_452 >= expr_477);
			t_sample mul_446 = (tap_458 * gte_445);
			t_sample abs_444 = fabs(gen_424);
			t_sample add_454 = (m_average_6 + abs_444);
			t_sample sub_453 = (add_454 - mul_446);
			t_sample mul_450 = (sub_453 * eq_449);
			t_sample counter_next_459 = fixdenorm(mul_451);
			t_sample average_next_460 = fixdenorm(mul_450);
			t_sample add_437 = (m_counter_4 + ((int)1));
			t_sample clamp_434 = ((add_437 <= ((int)0)) ? ((int)0) : ((add_437 >= expr_477) ? expr_477 : add_437));
			t_sample div_430 = safediv(m_average_3, clamp_434);
			t_sample gen_443 = div_430;
			t_sample delta_438 = __m_delta_43(expr_477);
			int eq_431 = (delta_438 == ((int)0));
			t_sample mul_433 = (clamp_434 * eq_431);
			t_sample tap_440 = m_delay_5.read_linear(expr_477);
			int gte_427 = (clamp_434 >= expr_477);
			t_sample mul_428 = (tap_440 * gte_427);
			t_sample abs_426 = fabs(gen_425);
			t_sample add_436 = (m_average_3 + abs_426);
			t_sample sub_435 = (add_436 - mul_428);
			t_sample mul_432 = (sub_435 * eq_431);
			t_sample counter_next_441 = fixdenorm(mul_433);
			t_sample average_next_442 = fixdenorm(mul_432);
			t_sample add_473 = (gen_461 + gen_443);
			t_sample atodb_463 = atodb(add_473);
			t_sample expr_476 = ((((atodb_463 + tap_472) + tap_467) + tap_465) * ((t_sample)0.25));
			t_sample gen_482 = expr_476;
			int gt_364 = (gen_482 > m_targetLevel_39);
			int gt_321 = (gen_596 > (-76));
			int switch_360 = (gt_364 ? ((int)0) : ((int)60000));
			__m_count_44 = (m_loadbang_2 ? 0 : (fixdenorm(__m_count_44 + ((int)1))));
			int carry_45 = 0;
			if ((m_loadbang_2 != 0)) {
				__m_count_44 = 0;
				__m_carry_46 = 0;
				
			} else if (((expr_366 > 0) && (__m_count_44 >= expr_366))) {
				int wraps_47 = (__m_count_44 / expr_366);
				__m_carry_46 = (__m_carry_46 + wraps_47);
				__m_count_44 = (__m_count_44 - (wraps_47 * expr_366));
				carry_45 = 1;
				
			};
			int counter_335 = __m_count_44;
			int counter_336 = carry_45;
			int counter_337 = __m_carry_46;
			__m_latch_48 = (((m_loadbang_2 + counter_336) != 0) ? m_loadbang_2 : __m_latch_48);
			t_sample latch_329 = __m_latch_48;
			int switch_330 = (latch_329 ? ((int)1) : ((int)0));
			int switch_361 = (gt_364 ? ((int)0) : ((int)1));
			int neq_344 = (switch_361 != ((int)1));
			t_sample switch_359 = (gt_364 ? gen_596 : ((int)0));
			t_sample dbtoa_324 = dbtoa(switch_359);
			int neq_358 = (dbtoa_324 != ((int)1));
			int switch_354 = (neq_358 ? ((int)0) : ((int)1000));
			t_sample switch_357 = (neq_358 ? switch_359 : ((int)0));
			int gt_353 = (switch_357 > m_targetLevel_39);
			int switch_349 = (gt_353 ? ((int)3000) : ((int)0));
			int switch_342 = (neq_344 ? switch_349 : ((int)0));
			int switch_345 = (gt_353 ? ((int)0) : ((int)15000));
			int switch_340 = (neq_344 ? switch_345 : ((int)0));
			int iftrue_49 = ((switch_340 + switch_342) + switch_360);
			int switch_322 = (gt_321 ? iftrue_49 : switch_354);
			int switch_339 = (switch_330 ? ((int)1) : switch_322);
			t_sample expr_365 = ((samplerate * switch_339) * ((t_sample)0.001));
			t_sample switch_355 = (neq_358 ? ((int)0) : m_history_1);
			t_sample sub_352 = (m_history_1 - ((t_sample)0.1));
			t_sample switch_350 = (gt_353 ? sub_352 : ((int)0));
			t_sample switch_343 = (neq_344 ? switch_350 : ((int)0));
			t_sample add_348 = (m_history_1 + ((t_sample)0.1));
			t_sample switch_346 = (gt_353 ? ((int)0) : add_348);
			t_sample switch_341 = (neq_344 ? switch_346 : ((int)0));
			t_sample iftrue_50 = ((switch_341 + switch_343) + switch_361);
			t_sample switch_323 = (gt_321 ? iftrue_50 : switch_355);
			t_sample switch_328 = (switch_330 ? ((int)1) : switch_323);
			t_sample clamp_318 = ((switch_328 <= ((int)0)) ? ((int)0) : ((switch_328 >= ((int)1)) ? ((int)1) : switch_328));
			t_sample iup_52 = (1 / maximum(1, abs(expr_365)));
			t_sample idown_53 = (1 / maximum(1, abs(expr_365)));
			__m_slide_51 = fixdenorm((__m_slide_51 + (((clamp_318 > __m_slide_51) ? iup_52 : idown_53) * (clamp_318 - __m_slide_51))));
			t_sample slide_320 = __m_slide_51;
			t_sample gen_367 = slide_320;
			t_sample history_316_next_617 = fixdenorm(gen_367);
			m_delay_38.write(atodb_577);
			m_counter_22 = counter_next_555;
			m_average_21 = average_next_556;
			m_delay_23.write(abs_540);
			m_counter_25 = counter_next_573;
			m_average_24 = average_next_574;
			m_delay_26.write(abs_558);
			m_history_32 = history_512_next_522;
			m_history_33 = history_516_next_521;
			m_history_34 = history_514_next_520;
			m_history_31 = history_490_next_495;
			m_history_28 = history_488_next_498;
			m_history_29 = history_492_next_497;
			m_history_30 = history_486_next_496;
			m_y_27 = y0_next_536;
			m_y_27 = y0_next_537;
			m_history_35 = history_510_next_519;
			m_delay_36.write(atodb_577);
			m_delay_37.write(atodb_577);
			m_delay_20.write(atodb_463);
			m_counter_4 = counter_next_441;
			m_average_3 = average_next_442;
			m_delay_5.write(abs_426);
			m_counter_7 = counter_next_459;
			m_average_6 = average_next_460;
			m_delay_8.write(abs_444);
			m_history_14 = history_398_next_408;
			m_history_15 = history_402_next_407;
			m_history_16 = history_396_next_406;
			m_history_13 = history_376_next_381;
			m_history_10 = history_374_next_384;
			m_history_11 = history_378_next_383;
			m_history_12 = history_372_next_382;
			m_y_9 = y0_next_422;
			m_y_9 = y0_next_423;
			m_history_17 = history_400_next_405;
			m_delay_18.write(atodb_463);
			m_delay_19.write(atodb_463);
			m_loadbang_2 = loadbang_next_616;
			m_history_1 = history_316_next_617;
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
		m_targetLevel_39 = (_value < -30 ? -30 : (_value > 0 ? 0 : _value));
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
