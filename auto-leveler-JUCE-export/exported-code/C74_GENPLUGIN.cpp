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
		m_targetLevel_39 = 0.46;
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
		t_sample * __out8 = __outs[7];
		t_sample * __out9 = __outs[8];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__out1 == 0) || (__out2 == 0) || (__out3 == 0) || (__out4 == 0) || (__out5 == 0) || (__out6 == 0) || (__out7 == 0) || (__out8 == 0) || (__out9 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample expr_852 = ((samplerate * ((int)3000)) * ((t_sample)0.001));
		t_sample div_845 = (expr_852 * ((t_sample)0.25));
		t_sample mul_844 = (div_845 * ((int)2));
		t_sample mul_843 = (div_845 * ((int)3));
		t_sample omega = safediv(((t_sample)6283.1853071796), samplerate);
		t_sample sn = sin(omega);
		t_sample cs = cos(omega);
		t_sample b0 = safediv(((int)1), ((((t_sample)2.2589254117942) - (((t_sample)0.25892541179417) * cs)) + (((t_sample)1.5867737153067) * sn)));
		t_sample a0 = ((((t_sample)1.2589254117942) * ((((t_sample)2.2589254117942) + (((t_sample)0.25892541179417) * cs)) + (((t_sample)1.5867737153067) * sn))) * b0);
		t_sample a1 = ((((t_sample)-2.5178508235883) * (((t_sample)0.25892541179417) + (((t_sample)2.2589254117942) * cs))) * b0);
		t_sample a2 = ((((t_sample)1.2589254117942) * ((((t_sample)2.2589254117942) + (((t_sample)0.25892541179417) * cs)) - (((t_sample)1.5867737153067) * sn))) * b0);
		t_sample b1 = ((((int)2) * (((t_sample)0.25892541179417) - (((t_sample)2.2589254117942) * cs))) * b0);
		t_sample b2 = (((((t_sample)2.2589254117942) - (((t_sample)0.25892541179417) * cs)) - (((t_sample)1.5867737153067) * sn)) * b0);
		t_sample expr_793 = a0;
		t_sample expr_794 = a1;
		t_sample expr_795 = a2;
		t_sample expr_796 = b1;
		t_sample expr_797 = b2;
		t_sample expr_739 = ((samplerate * ((int)3000)) * ((t_sample)0.001));
		t_sample div_732 = (expr_739 * ((t_sample)0.25));
		t_sample mul_731 = (div_732 * ((int)2));
		t_sample mul_730 = (div_732 * ((int)3));
		t_sample omega_870 = safediv(((t_sample)6283.1853071796), samplerate);
		t_sample sn_873 = sin(omega_870);
		t_sample cs_863 = cos(omega_870);
		t_sample b_868 = safediv(((int)1), ((((t_sample)2.2589254117942) - (((t_sample)0.25892541179417) * cs_863)) + (((t_sample)1.5867737153067) * sn_873)));
		t_sample a_869 = ((((t_sample)1.2589254117942) * ((((t_sample)2.2589254117942) + (((t_sample)0.25892541179417) * cs_863)) + (((t_sample)1.5867737153067) * sn_873))) * b_868);
		t_sample a_867 = ((((t_sample)-2.5178508235883) * (((t_sample)0.25892541179417) + (((t_sample)2.2589254117942) * cs_863))) * b_868);
		t_sample a_860 = ((((t_sample)1.2589254117942) * ((((t_sample)2.2589254117942) + (((t_sample)0.25892541179417) * cs_863)) - (((t_sample)1.5867737153067) * sn_873))) * b_868);
		t_sample b_866 = ((((int)2) * (((t_sample)0.25892541179417) - (((t_sample)2.2589254117942) * cs_863))) * b_868);
		t_sample b_861 = (((((t_sample)2.2589254117942) - (((t_sample)0.25892541179417) * cs_863)) - (((t_sample)1.5867737153067) * sn_873)) * b_868);
		t_sample expr_680 = a_869;
		t_sample expr_681 = a_867;
		t_sample expr_682 = a_860;
		t_sample expr_683 = b_866;
		t_sample expr_684 = b_861;
		t_sample expr_627 = ((((int)500) * samplerate) * ((t_sample)0.001));
		t_sample loadbang_next_877 = fixdenorm(((int)0));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample out3 = m_history_1;
			t_sample mul_859 = (in1 * m_history_1);
			t_sample out1 = mul_859;
			t_sample mul_858 = (in2 * m_history_1);
			t_sample out2 = mul_858;
			t_sample tap_847 = m_delay_38.read_linear(div_845);
			t_sample tap_842 = m_delay_37.read_linear(mul_844);
			t_sample tap_840 = m_delay_36.read_linear(mul_843);
			t_sample mix_879 = (m_y_27 + (((t_sample)0.014247103707103) * (mul_858 - m_y_27)));
			t_sample mix_786 = mix_879;
			t_sample sub_745 = (mul_858 - mix_786);
			t_sample mul_751 = (m_history_34 * expr_795);
			t_sample mul_753 = (m_history_33 * expr_794);
			t_sample mul_756 = (sub_745 * expr_793);
			t_sample mul_749 = (m_history_32 * expr_796);
			t_sample mul_747 = (m_history_35 * expr_797);
			t_sample sub_755 = (((mul_756 + mul_753) + mul_751) - (mul_747 + mul_749));
			t_sample gen_761 = sub_755;
			t_sample history_748_next_757 = fixdenorm(m_history_32);
			t_sample history_752_next_758 = fixdenorm(m_history_33);
			t_sample history_754_next_759 = fixdenorm(sub_745);
			t_sample history_750_next_760 = fixdenorm(sub_755);
			t_sample gen_801 = gen_761;
			t_sample mix_880 = (m_y_27 + (((t_sample)0.014247103707103) * (mul_859 - m_y_27)));
			t_sample mix_789 = mix_880;
			t_sample sub_746 = (mul_859 - mix_789);
			t_sample mul_775 = (m_history_30 * expr_795);
			t_sample mul_777 = (m_history_29 * expr_794);
			t_sample mul_780 = (sub_746 * expr_793);
			t_sample mul_773 = (m_history_28 * expr_796);
			t_sample mul_771 = (m_history_31 * expr_797);
			t_sample sub_779 = (((mul_780 + mul_777) + mul_775) - (mul_771 + mul_773));
			t_sample gen_785 = sub_779;
			t_sample history_772_next_781 = fixdenorm(m_history_28);
			t_sample history_776_next_782 = fixdenorm(m_history_29);
			t_sample history_778_next_783 = fixdenorm(sub_746);
			t_sample history_774_next_784 = fixdenorm(sub_779);
			t_sample gen_800 = gen_785;
			t_sample y0_next_798 = fixdenorm(mix_786);
			t_sample y0_next_799 = fixdenorm(mix_789);
			t_sample add_831 = (m_counter_25 + ((int)1));
			t_sample clamp_828 = ((add_831 <= ((int)0)) ? ((int)0) : ((add_831 >= expr_852) ? expr_852 : add_831));
			t_sample div_824 = safediv(m_average_24, clamp_828);
			t_sample gen_837 = div_824;
			t_sample delta_832 = __m_delta_40(expr_852);
			int eq_825 = (delta_832 == ((int)0));
			t_sample mul_827 = (clamp_828 * eq_825);
			t_sample tap_834 = m_delay_26.read_linear(expr_852);
			int gte_821 = (clamp_828 >= expr_852);
			t_sample mul_822 = (tap_834 * gte_821);
			t_sample abs_820 = fabs(gen_800);
			t_sample add_830 = (m_average_24 + abs_820);
			t_sample sub_829 = (add_830 - mul_822);
			t_sample mul_826 = (sub_829 * eq_825);
			t_sample counter_next_835 = fixdenorm(mul_827);
			t_sample average_next_836 = fixdenorm(mul_826);
			t_sample add_813 = (m_counter_22 + ((int)1));
			t_sample clamp_810 = ((add_813 <= ((int)0)) ? ((int)0) : ((add_813 >= expr_852) ? expr_852 : add_813));
			t_sample div_806 = safediv(m_average_21, clamp_810);
			t_sample gen_819 = div_806;
			t_sample delta_814 = __m_delta_41(expr_852);
			int eq_807 = (delta_814 == ((int)0));
			t_sample mul_809 = (clamp_810 * eq_807);
			t_sample tap_816 = m_delay_23.read_linear(expr_852);
			int gte_803 = (clamp_810 >= expr_852);
			t_sample mul_804 = (tap_816 * gte_803);
			t_sample abs_802 = fabs(gen_801);
			t_sample add_812 = (m_average_21 + abs_802);
			t_sample sub_811 = (add_812 - mul_804);
			t_sample mul_808 = (sub_811 * eq_807);
			t_sample counter_next_817 = fixdenorm(mul_809);
			t_sample average_next_818 = fixdenorm(mul_808);
			t_sample add_848 = (gen_837 + gen_819);
			t_sample expr_851 = ((((add_848 + tap_847) + tap_842) + tap_840) * ((t_sample)0.25));
			t_sample gen_857 = expr_851;
			t_sample out4 = gen_857;
			t_sample tap_734 = m_delay_20.read_linear(div_732);
			t_sample tap_729 = m_delay_19.read_linear(mul_731);
			t_sample tap_727 = m_delay_18.read_linear(mul_730);
			t_sample mix_881 = (m_y_9 + (((t_sample)0.014247103707103) * (in1 - m_y_9)));
			t_sample mix_676 = mix_881;
			t_sample sub_633 = (in1 - mix_676);
			t_sample mul_662 = (m_history_16 * expr_682);
			t_sample mul_664 = (m_history_15 * expr_681);
			t_sample mul_667 = (sub_633 * expr_680);
			t_sample mul_660 = (m_history_14 * expr_683);
			t_sample mul_658 = (m_history_17 * expr_684);
			t_sample sub_666 = (((mul_667 + mul_664) + mul_662) - (mul_658 + mul_660));
			t_sample gen_672 = sub_666;
			t_sample history_659_next_668 = fixdenorm(m_history_14);
			t_sample history_663_next_669 = fixdenorm(m_history_15);
			t_sample history_665_next_670 = fixdenorm(sub_633);
			t_sample history_661_next_671 = fixdenorm(sub_666);
			t_sample gen_687 = gen_672;
			t_sample mix_882 = (m_y_9 + (((t_sample)0.014247103707103) * (in2 - m_y_9)));
			t_sample mix_673 = mix_882;
			t_sample sub_632 = (in2 - mix_673);
			t_sample mul_638 = (m_history_12 * expr_682);
			t_sample mul_640 = (m_history_11 * expr_681);
			t_sample mul_643 = (sub_632 * expr_680);
			t_sample mul_636 = (m_history_10 * expr_683);
			t_sample mul_634 = (m_history_13 * expr_684);
			t_sample sub_642 = (((mul_643 + mul_640) + mul_638) - (mul_634 + mul_636));
			t_sample gen_648 = sub_642;
			t_sample history_635_next_644 = fixdenorm(m_history_10);
			t_sample history_639_next_645 = fixdenorm(m_history_11);
			t_sample history_641_next_646 = fixdenorm(sub_632);
			t_sample history_637_next_647 = fixdenorm(sub_642);
			t_sample gen_688 = gen_648;
			t_sample y0_next_685 = fixdenorm(mix_676);
			t_sample y0_next_686 = fixdenorm(mix_673);
			t_sample add_718 = (m_counter_7 + ((int)1));
			t_sample clamp_715 = ((add_718 <= ((int)0)) ? ((int)0) : ((add_718 >= expr_739) ? expr_739 : add_718));
			t_sample div_711 = safediv(m_average_6, clamp_715);
			t_sample gen_724 = div_711;
			t_sample delta_719 = __m_delta_42(expr_739);
			int eq_712 = (delta_719 == ((int)0));
			t_sample mul_714 = (clamp_715 * eq_712);
			t_sample tap_721 = m_delay_8.read_linear(expr_739);
			int gte_708 = (clamp_715 >= expr_739);
			t_sample mul_709 = (tap_721 * gte_708);
			t_sample abs_707 = fabs(gen_687);
			t_sample add_717 = (m_average_6 + abs_707);
			t_sample sub_716 = (add_717 - mul_709);
			t_sample mul_713 = (sub_716 * eq_712);
			t_sample counter_next_722 = fixdenorm(mul_714);
			t_sample average_next_723 = fixdenorm(mul_713);
			t_sample add_700 = (m_counter_4 + ((int)1));
			t_sample clamp_697 = ((add_700 <= ((int)0)) ? ((int)0) : ((add_700 >= expr_739) ? expr_739 : add_700));
			t_sample div_693 = safediv(m_average_3, clamp_697);
			t_sample gen_706 = div_693;
			t_sample delta_701 = __m_delta_43(expr_739);
			int eq_694 = (delta_701 == ((int)0));
			t_sample mul_696 = (clamp_697 * eq_694);
			t_sample tap_703 = m_delay_5.read_linear(expr_739);
			int gte_690 = (clamp_697 >= expr_739);
			t_sample mul_691 = (tap_703 * gte_690);
			t_sample abs_689 = fabs(gen_688);
			t_sample add_699 = (m_average_3 + abs_689);
			t_sample sub_698 = (add_699 - mul_691);
			t_sample mul_695 = (sub_698 * eq_694);
			t_sample counter_next_704 = fixdenorm(mul_696);
			t_sample average_next_705 = fixdenorm(mul_695);
			t_sample add_735 = (gen_724 + gen_706);
			t_sample expr_738 = ((((add_735 + tap_734) + tap_729) + tap_727) * ((t_sample)0.25));
			t_sample gen_744 = expr_738;
			t_sample out5 = gen_744;
			int gt_625 = (gen_744 > m_targetLevel_39);
			int gen_629 = gt_625;
			int switch_621 = (gt_625 ? ((int)0) : ((int)60000));
			t_sample atodb_590 = atodb(m_history_1);
			t_sample add_615 = (atodb_590 + ((int)3));
			t_sample dbtoa_587 = dbtoa(add_615);
			t_sample gen_631 = dbtoa_587;
			t_sample sub_619 = (atodb_590 - ((int)3));
			t_sample dbtoa_589 = dbtoa(sub_619);
			t_sample gen_630 = dbtoa_589;
			__m_count_44 = (m_loadbang_2 ? 0 : (fixdenorm(__m_count_44 + ((int)1))));
			int carry_45 = 0;
			if ((m_loadbang_2 != 0)) {
				__m_count_44 = 0;
				__m_carry_46 = 0;
				
			} else if (((expr_627 > 0) && (__m_count_44 >= expr_627))) {
				int wraps_47 = (__m_count_44 / expr_627);
				__m_carry_46 = (__m_carry_46 + wraps_47);
				__m_count_44 = (__m_count_44 - (wraps_47 * expr_627));
				carry_45 = 1;
				
			};
			int counter_602 = __m_count_44;
			int counter_603 = carry_45;
			int counter_604 = __m_carry_46;
			__m_latch_48 = (((counter_603 + m_loadbang_2) != 0) ? m_loadbang_2 : __m_latch_48);
			t_sample latch_596 = __m_latch_48;
			int switch_597 = (latch_596 ? ((int)1) : ((int)0));
			int switch_622 = (gt_625 ? ((int)0) : ((int)1));
			int neq_611 = (switch_622 != ((int)1));
			int gt_620 = (gen_857 > m_targetLevel_39);
			int switch_612 = (gt_620 ? ((int)0) : ((int)15000));
			int switch_607 = (neq_611 ? switch_612 : ((int)0));
			int switch_616 = (gt_620 ? ((int)3000) : ((int)0));
			int switch_609 = (neq_611 ? switch_616 : ((int)0));
			int iffalse_49 = ((switch_621 + switch_609) + switch_607);
			int switch_606 = (switch_597 ? ((int)1) : iffalse_49);
			t_sample expr_626 = ((samplerate * switch_606) * ((t_sample)0.001));
			t_sample switch_613 = (gt_620 ? ((int)0) : dbtoa_587);
			t_sample switch_608 = (neq_611 ? switch_613 : ((int)0));
			t_sample switch_617 = (gt_620 ? dbtoa_589 : ((int)0));
			t_sample switch_610 = (neq_611 ? switch_617 : ((int)0));
			t_sample iffalse_50 = ((switch_622 + switch_610) + switch_608);
			t_sample switch_595 = (switch_597 ? ((int)1) : iffalse_50);
			t_sample clamp_591 = ((switch_595 <= ((int)0)) ? ((int)0) : ((switch_595 >= ((int)1)) ? ((int)1) : switch_595));
			t_sample iup_52 = (1 / maximum(1, abs(expr_626)));
			t_sample idown_53 = (1 / maximum(1, abs(expr_626)));
			__m_slide_51 = fixdenorm((__m_slide_51 + (((clamp_591 > __m_slide_51) ? iup_52 : idown_53) * (clamp_591 - __m_slide_51))));
			t_sample slide_593 = __m_slide_51;
			t_sample gen_628 = slide_593;
			t_sample out9 = gen_631;
			t_sample out6 = gen_628;
			t_sample out7 = gen_629;
			t_sample out8 = gen_630;
			t_sample history_585_next_878 = fixdenorm(gen_628);
			m_delay_38.write(add_848);
			m_counter_22 = counter_next_817;
			m_average_21 = average_next_818;
			m_delay_23.write(abs_802);
			m_counter_25 = counter_next_835;
			m_average_24 = average_next_836;
			m_delay_26.write(abs_820);
			m_history_32 = history_750_next_760;
			m_history_33 = history_754_next_759;
			m_history_34 = history_752_next_758;
			m_history_31 = history_772_next_781;
			m_history_28 = history_774_next_784;
			m_history_29 = history_778_next_783;
			m_history_30 = history_776_next_782;
			m_y_27 = y0_next_798;
			m_y_27 = y0_next_799;
			m_history_35 = history_748_next_757;
			m_delay_36.write(add_848);
			m_delay_37.write(add_848);
			m_delay_20.write(add_735);
			m_counter_4 = counter_next_704;
			m_average_3 = average_next_705;
			m_delay_5.write(abs_689);
			m_counter_7 = counter_next_722;
			m_average_6 = average_next_723;
			m_delay_8.write(abs_707);
			m_history_14 = history_661_next_671;
			m_history_15 = history_665_next_670;
			m_history_16 = history_663_next_669;
			m_history_13 = history_635_next_644;
			m_history_10 = history_637_next_647;
			m_history_11 = history_641_next_646;
			m_history_12 = history_639_next_645;
			m_y_9 = y0_next_685;
			m_y_9 = y0_next_686;
			m_history_17 = history_659_next_668;
			m_delay_18.write(add_735);
			m_delay_19.write(add_735);
			m_loadbang_2 = loadbang_next_877;
			m_history_1 = history_585_next_878;
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
			(*(__out8++)) = out8;
			(*(__out9++)) = out9;
			
		};
		return __exception;
		
	};
	inline void set_targetLevel(t_param _value) {
		m_targetLevel_39 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 2;
int gen_kernel_numouts = 9;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 1; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "L In", "L In" };
const char *gen_kernel_outnames[] = { "out1", "out2", "out3", "out4", "out5", "out6", "out7", "out8", "out9" };

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
	pi->outputmin = 0;
	pi->outputmax = 1;
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
