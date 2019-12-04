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
		t_sample expr_748 = ((samplerate * ((int)3000)) * ((t_sample)0.001));
		t_sample div_741 = (expr_748 * ((t_sample)0.25));
		t_sample mul_740 = (div_741 * ((int)2));
		t_sample mul_739 = (div_741 * ((int)3));
		t_sample omega = safediv(((t_sample)6283.1853071796), samplerate);
		t_sample sn = sin(omega);
		t_sample cs = cos(omega);
		t_sample b0 = safediv(((int)1), ((((t_sample)2.2589254117942) - (((t_sample)0.25892541179417) * cs)) + (((t_sample)1.5867737153067) * sn)));
		t_sample a0 = ((((t_sample)1.2589254117942) * ((((t_sample)2.2589254117942) + (((t_sample)0.25892541179417) * cs)) + (((t_sample)1.5867737153067) * sn))) * b0);
		t_sample a1 = ((((t_sample)-2.5178508235883) * (((t_sample)0.25892541179417) + (((t_sample)2.2589254117942) * cs))) * b0);
		t_sample a2 = ((((t_sample)1.2589254117942) * ((((t_sample)2.2589254117942) + (((t_sample)0.25892541179417) * cs)) - (((t_sample)1.5867737153067) * sn))) * b0);
		t_sample b1 = ((((int)2) * (((t_sample)0.25892541179417) - (((t_sample)2.2589254117942) * cs))) * b0);
		t_sample b2 = (((((t_sample)2.2589254117942) - (((t_sample)0.25892541179417) * cs)) - (((t_sample)1.5867737153067) * sn)) * b0);
		t_sample expr_688 = a0;
		t_sample expr_689 = a1;
		t_sample expr_690 = a2;
		t_sample expr_691 = b1;
		t_sample expr_692 = b2;
		t_sample expr_862 = ((samplerate * ((int)3000)) * ((t_sample)0.001));
		t_sample div_855 = (expr_862 * ((t_sample)0.25));
		t_sample mul_854 = (div_855 * ((int)2));
		t_sample mul_853 = (div_855 * ((int)3));
		t_sample omega_875 = safediv(((t_sample)6283.1853071796), samplerate);
		t_sample sn_879 = sin(omega_875);
		t_sample cs_882 = cos(omega_875);
		t_sample b_880 = safediv(((int)1), ((((t_sample)2.2589254117942) - (((t_sample)0.25892541179417) * cs_882)) + (((t_sample)1.5867737153067) * sn_879)));
		t_sample a_881 = ((((t_sample)1.2589254117942) * ((((t_sample)2.2589254117942) + (((t_sample)0.25892541179417) * cs_882)) + (((t_sample)1.5867737153067) * sn_879))) * b_880);
		t_sample a_878 = ((((t_sample)-2.5178508235883) * (((t_sample)0.25892541179417) + (((t_sample)2.2589254117942) * cs_882))) * b_880);
		t_sample a_871 = ((((t_sample)1.2589254117942) * ((((t_sample)2.2589254117942) + (((t_sample)0.25892541179417) * cs_882)) - (((t_sample)1.5867737153067) * sn_879))) * b_880);
		t_sample b_877 = ((((int)2) * (((t_sample)0.25892541179417) - (((t_sample)2.2589254117942) * cs_882))) * b_880);
		t_sample b_872 = (((((t_sample)2.2589254117942) - (((t_sample)0.25892541179417) * cs_882)) - (((t_sample)1.5867737153067) * sn_879)) * b_880);
		t_sample expr_802 = a_881;
		t_sample expr_803 = a_878;
		t_sample expr_804 = a_871;
		t_sample expr_805 = b_877;
		t_sample expr_806 = b_872;
		t_sample expr_636 = ((((int)500) * samplerate) * ((t_sample)0.001));
		t_sample loadbang_next_887 = fixdenorm(((int)0));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample out3 = m_history_1;
			t_sample mul_868 = (in2 * m_history_1);
			t_sample out2 = mul_868;
			t_sample tap_743 = m_delay_38.read_linear(div_741);
			t_sample tap_738 = m_delay_37.read_linear(mul_740);
			t_sample tap_736 = m_delay_36.read_linear(mul_739);
			t_sample mix_902 = (m_y_27 + (((t_sample)0.014247103707103) * (in2 - m_y_27)));
			t_sample mix_681 = mix_902;
			t_sample sub_640 = (in2 - mix_681);
			t_sample mul_646 = (m_history_34 * expr_690);
			t_sample mul_648 = (m_history_33 * expr_689);
			t_sample mul_651 = (sub_640 * expr_688);
			t_sample mul_644 = (m_history_32 * expr_691);
			t_sample mul_642 = (m_history_35 * expr_692);
			t_sample sub_650 = (((mul_651 + mul_648) + mul_646) - (mul_642 + mul_644));
			t_sample gen_656 = sub_650;
			t_sample history_643_next_652 = fixdenorm(m_history_32);
			t_sample history_647_next_653 = fixdenorm(m_history_33);
			t_sample history_649_next_654 = fixdenorm(sub_640);
			t_sample history_645_next_655 = fixdenorm(sub_650);
			t_sample gen_696 = gen_656;
			t_sample mix_903 = (m_y_27 + (((t_sample)0.014247103707103) * (in1 - m_y_27)));
			t_sample mix_684 = mix_903;
			t_sample sub_641 = (in1 - mix_684);
			t_sample mul_670 = (m_history_30 * expr_690);
			t_sample mul_672 = (m_history_29 * expr_689);
			t_sample mul_675 = (sub_641 * expr_688);
			t_sample mul_668 = (m_history_28 * expr_691);
			t_sample mul_666 = (m_history_31 * expr_692);
			t_sample sub_674 = (((mul_675 + mul_672) + mul_670) - (mul_666 + mul_668));
			t_sample gen_680 = sub_674;
			t_sample history_667_next_676 = fixdenorm(m_history_28);
			t_sample history_671_next_677 = fixdenorm(m_history_29);
			t_sample history_673_next_678 = fixdenorm(sub_641);
			t_sample history_669_next_679 = fixdenorm(sub_674);
			t_sample gen_695 = gen_680;
			t_sample y0_next_693 = fixdenorm(mix_681);
			t_sample y0_next_694 = fixdenorm(mix_684);
			t_sample add_726 = (m_counter_25 + ((int)1));
			t_sample clamp_723 = ((add_726 <= ((int)0)) ? ((int)0) : ((add_726 >= expr_748) ? expr_748 : add_726));
			t_sample div_719 = safediv(m_average_24, clamp_723);
			t_sample gen_732 = div_719;
			t_sample delta_727 = __m_delta_40(expr_748);
			int eq_720 = (delta_727 == ((int)0));
			t_sample mul_722 = (clamp_723 * eq_720);
			t_sample tap_729 = m_delay_26.read_linear(expr_748);
			int gte_716 = (clamp_723 >= expr_748);
			t_sample mul_717 = (tap_729 * gte_716);
			t_sample abs_715 = fabs(gen_695);
			t_sample add_725 = (m_average_24 + abs_715);
			t_sample sub_724 = (add_725 - mul_717);
			t_sample mul_721 = (sub_724 * eq_720);
			t_sample counter_next_730 = fixdenorm(mul_722);
			t_sample average_next_731 = fixdenorm(mul_721);
			t_sample add_708 = (m_counter_22 + ((int)1));
			t_sample clamp_705 = ((add_708 <= ((int)0)) ? ((int)0) : ((add_708 >= expr_748) ? expr_748 : add_708));
			t_sample div_701 = safediv(m_average_21, clamp_705);
			t_sample gen_714 = div_701;
			t_sample delta_709 = __m_delta_41(expr_748);
			int eq_702 = (delta_709 == ((int)0));
			t_sample mul_704 = (clamp_705 * eq_702);
			t_sample tap_711 = m_delay_23.read_linear(expr_748);
			int gte_698 = (clamp_705 >= expr_748);
			t_sample mul_699 = (tap_711 * gte_698);
			t_sample abs_697 = fabs(gen_696);
			t_sample add_707 = (m_average_21 + abs_697);
			t_sample sub_706 = (add_707 - mul_699);
			t_sample mul_703 = (sub_706 * eq_702);
			t_sample counter_next_712 = fixdenorm(mul_704);
			t_sample average_next_713 = fixdenorm(mul_703);
			t_sample add_744 = (gen_732 + gen_714);
			t_sample atodb_734 = atodb(add_744);
			t_sample expr_747 = ((((atodb_734 + tap_743) + tap_738) + tap_736) * ((t_sample)0.25));
			t_sample gen_753 = expr_747;
			t_sample out5 = gen_753;
			t_sample mul_869 = (in1 * m_history_1);
			t_sample out1 = mul_869;
			t_sample tap_857 = m_delay_20.read_linear(div_855);
			t_sample tap_852 = m_delay_19.read_linear(mul_854);
			t_sample tap_850 = m_delay_18.read_linear(mul_853);
			t_sample mix_904 = (m_y_9 + (((t_sample)0.014247103707103) * (mul_868 - m_y_9)));
			t_sample mix_795 = mix_904;
			t_sample sub_754 = (mul_868 - mix_795);
			t_sample mul_760 = (m_history_17 * expr_804);
			t_sample mul_762 = (m_history_15 * expr_803);
			t_sample mul_765 = (sub_754 * expr_802);
			t_sample mul_758 = (m_history_14 * expr_805);
			t_sample mul_756 = (m_history_16 * expr_806);
			t_sample sub_764 = (((mul_765 + mul_762) + mul_760) - (mul_756 + mul_758));
			t_sample gen_770 = sub_764;
			t_sample history_761_next_766 = fixdenorm(m_history_15);
			t_sample history_757_next_767 = fixdenorm(m_history_14);
			t_sample history_763_next_768 = fixdenorm(sub_754);
			t_sample history_759_next_769 = fixdenorm(sub_764);
			t_sample gen_810 = gen_770;
			t_sample mix_905 = (m_y_9 + (((t_sample)0.014247103707103) * (mul_869 - m_y_9)));
			t_sample mix_798 = mix_905;
			t_sample sub_755 = (mul_869 - mix_798);
			t_sample mul_784 = (m_history_13 * expr_804);
			t_sample mul_786 = (m_history_11 * expr_803);
			t_sample mul_789 = (sub_755 * expr_802);
			t_sample mul_782 = (m_history_10 * expr_805);
			t_sample mul_780 = (m_history_12 * expr_806);
			t_sample sub_788 = (((mul_789 + mul_786) + mul_784) - (mul_780 + mul_782));
			t_sample gen_794 = sub_788;
			t_sample history_785_next_790 = fixdenorm(m_history_11);
			t_sample history_781_next_791 = fixdenorm(m_history_10);
			t_sample history_787_next_792 = fixdenorm(sub_755);
			t_sample history_783_next_793 = fixdenorm(sub_788);
			t_sample gen_809 = gen_794;
			t_sample y0_next_807 = fixdenorm(mix_795);
			t_sample y0_next_808 = fixdenorm(mix_798);
			t_sample add_840 = (m_counter_7 + ((int)1));
			t_sample clamp_837 = ((add_840 <= ((int)0)) ? ((int)0) : ((add_840 >= expr_862) ? expr_862 : add_840));
			t_sample div_833 = safediv(m_average_6, clamp_837);
			t_sample gen_846 = div_833;
			t_sample delta_841 = __m_delta_42(expr_862);
			int eq_834 = (delta_841 == ((int)0));
			t_sample mul_836 = (clamp_837 * eq_834);
			t_sample tap_843 = m_delay_8.read_linear(expr_862);
			int gte_830 = (clamp_837 >= expr_862);
			t_sample mul_831 = (tap_843 * gte_830);
			t_sample abs_829 = fabs(gen_809);
			t_sample add_839 = (m_average_6 + abs_829);
			t_sample sub_838 = (add_839 - mul_831);
			t_sample mul_835 = (sub_838 * eq_834);
			t_sample counter_next_844 = fixdenorm(mul_836);
			t_sample average_next_845 = fixdenorm(mul_835);
			t_sample add_822 = (m_counter_4 + ((int)1));
			t_sample clamp_819 = ((add_822 <= ((int)0)) ? ((int)0) : ((add_822 >= expr_862) ? expr_862 : add_822));
			t_sample div_815 = safediv(m_average_3, clamp_819);
			t_sample gen_828 = div_815;
			t_sample delta_823 = __m_delta_43(expr_862);
			int eq_816 = (delta_823 == ((int)0));
			t_sample mul_818 = (clamp_819 * eq_816);
			t_sample tap_825 = m_delay_5.read_linear(expr_862);
			int gte_812 = (clamp_819 >= expr_862);
			t_sample mul_813 = (tap_825 * gte_812);
			t_sample abs_811 = fabs(gen_810);
			t_sample add_821 = (m_average_3 + abs_811);
			t_sample sub_820 = (add_821 - mul_813);
			t_sample mul_817 = (sub_820 * eq_816);
			t_sample counter_next_826 = fixdenorm(mul_818);
			t_sample average_next_827 = fixdenorm(mul_817);
			t_sample add_858 = (gen_846 + gen_828);
			t_sample atodb_848 = atodb(add_858);
			t_sample expr_861 = ((((atodb_848 + tap_857) + tap_852) + tap_850) * ((t_sample)0.25));
			t_sample gen_867 = expr_861;
			t_sample out4 = gen_867;
			int gt_634 = (gen_753 > m_targetLevel_39);
			int gen_638 = gt_634;
			int switch_630 = (gt_634 ? ((int)0) : ((int)60000));
			__m_count_44 = (m_loadbang_2 ? 0 : (fixdenorm(__m_count_44 + ((int)1))));
			int carry_45 = 0;
			if ((m_loadbang_2 != 0)) {
				__m_count_44 = 0;
				__m_carry_46 = 0;
				
			} else if (((expr_636 > 0) && (__m_count_44 >= expr_636))) {
				int wraps_47 = (__m_count_44 / expr_636);
				__m_carry_46 = (__m_carry_46 + wraps_47);
				__m_count_44 = (__m_count_44 - (wraps_47 * expr_636));
				carry_45 = 1;
				
			};
			int counter_611 = __m_count_44;
			int counter_612 = carry_45;
			int counter_613 = __m_carry_46;
			__m_latch_48 = (((counter_612 + m_loadbang_2) != 0) ? m_loadbang_2 : __m_latch_48);
			t_sample latch_605 = __m_latch_48;
			int switch_606 = (latch_605 ? ((int)1) : ((int)0));
			int switch_631 = (gt_634 ? ((int)0) : ((int)1));
			int neq_620 = (switch_631 != ((int)1));
			int gt_629 = (gen_867 > m_targetLevel_39);
			int switch_621 = (gt_629 ? ((int)0) : ((int)15000));
			int switch_616 = (neq_620 ? switch_621 : ((int)0));
			int switch_625 = (gt_629 ? ((int)3000) : ((int)0));
			int switch_618 = (neq_620 ? switch_625 : ((int)0));
			int iffalse_49 = ((switch_630 + switch_618) + switch_616);
			int switch_615 = (switch_606 ? ((int)1) : iffalse_49);
			t_sample expr_635 = ((samplerate * switch_615) * ((t_sample)0.001));
			t_sample add_624 = (m_history_1 + ((t_sample)0.1));
			t_sample switch_622 = (gt_629 ? ((int)0) : add_624);
			t_sample switch_617 = (neq_620 ? switch_622 : ((int)0));
			t_sample sub_628 = (m_history_1 - ((t_sample)0.1));
			t_sample switch_626 = (gt_629 ? sub_628 : ((int)0));
			t_sample switch_619 = (neq_620 ? switch_626 : ((int)0));
			t_sample iffalse_50 = ((switch_631 + switch_619) + switch_617);
			t_sample switch_604 = (switch_606 ? ((int)1) : iffalse_50);
			t_sample clamp_598 = ((switch_604 <= ((int)0)) ? ((int)0) : ((switch_604 >= ((int)1)) ? ((int)1) : switch_604));
			t_sample iup_52 = (1 / maximum(1, abs(expr_635)));
			t_sample idown_53 = (1 / maximum(1, abs(expr_635)));
			__m_slide_51 = fixdenorm((__m_slide_51 + (((clamp_598 > __m_slide_51) ? iup_52 : idown_53) * (clamp_598 - __m_slide_51))));
			t_sample slide_600 = __m_slide_51;
			t_sample gen_637 = slide_600;
			t_sample out6 = gen_637;
			t_sample out7 = gen_638;
			t_sample history_596_next_888 = fixdenorm(gen_637);
			m_delay_38.write(atodb_734);
			m_counter_22 = counter_next_712;
			m_average_21 = average_next_713;
			m_delay_23.write(abs_697);
			m_counter_25 = counter_next_730;
			m_average_24 = average_next_731;
			m_delay_26.write(abs_715);
			m_history_32 = history_645_next_655;
			m_history_33 = history_649_next_654;
			m_history_34 = history_647_next_653;
			m_history_31 = history_667_next_676;
			m_history_28 = history_669_next_679;
			m_history_29 = history_673_next_678;
			m_history_30 = history_671_next_677;
			m_y_27 = y0_next_693;
			m_y_27 = y0_next_694;
			m_history_35 = history_643_next_652;
			m_delay_36.write(atodb_734);
			m_delay_37.write(atodb_734);
			m_delay_20.write(atodb_848);
			m_counter_4 = counter_next_826;
			m_average_3 = average_next_827;
			m_delay_5.write(abs_811);
			m_counter_7 = counter_next_844;
			m_average_6 = average_next_845;
			m_delay_8.write(abs_829);
			m_history_14 = history_759_next_769;
			m_history_15 = history_763_next_768;
			m_history_16 = history_757_next_767;
			m_history_13 = history_785_next_790;
			m_history_10 = history_783_next_793;
			m_history_11 = history_787_next_792;
			m_history_12 = history_781_next_791;
			m_y_9 = y0_next_807;
			m_y_9 = y0_next_808;
			m_history_17 = history_761_next_766;
			m_delay_18.write(atodb_848);
			m_delay_19.write(atodb_848);
			m_loadbang_2 = loadbang_next_887;
			m_history_1 = history_596_next_888;
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
