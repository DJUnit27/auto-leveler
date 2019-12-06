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
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__out1 == 0) || (__out2 == 0) || (__out3 == 0) || (__out4 == 0) || (__out5 == 0) || (__out6 == 0) || (__out7 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample expr_1989 = ((samplerate * ((int)3000)) * ((t_sample)0.001));
		t_sample div_1982 = (expr_1989 * ((t_sample)0.25));
		t_sample mul_1981 = (div_1982 * ((int)2));
		t_sample mul_1980 = (div_1982 * ((int)3));
		t_sample omega = safediv(((t_sample)6283.1853071796), samplerate);
		t_sample sn = sin(omega);
		t_sample cs = cos(omega);
		t_sample b0 = safediv(((int)1), ((((t_sample)2.2589254117942) - (((t_sample)0.25892541179417) * cs)) + (((t_sample)1.5867737153067) * sn)));
		t_sample a0 = ((((t_sample)1.2589254117942) * ((((t_sample)2.2589254117942) + (((t_sample)0.25892541179417) * cs)) + (((t_sample)1.5867737153067) * sn))) * b0);
		t_sample a1 = ((((t_sample)-2.5178508235883) * (((t_sample)0.25892541179417) + (((t_sample)2.2589254117942) * cs))) * b0);
		t_sample a2 = ((((t_sample)1.2589254117942) * ((((t_sample)2.2589254117942) + (((t_sample)0.25892541179417) * cs)) - (((t_sample)1.5867737153067) * sn))) * b0);
		t_sample b1 = ((((int)2) * (((t_sample)0.25892541179417) - (((t_sample)2.2589254117942) * cs))) * b0);
		t_sample b2 = (((((t_sample)2.2589254117942) - (((t_sample)0.25892541179417) * cs)) - (((t_sample)1.5867737153067) * sn)) * b0);
		t_sample expr_1930 = a0;
		t_sample expr_1931 = a1;
		t_sample expr_1932 = a2;
		t_sample expr_1933 = b1;
		t_sample expr_1934 = b2;
		t_sample expr_1876 = ((samplerate * ((int)3000)) * ((t_sample)0.001));
		t_sample div_1869 = (expr_1876 * ((t_sample)0.25));
		t_sample mul_1868 = (div_1869 * ((int)2));
		t_sample mul_1867 = (div_1869 * ((int)3));
		t_sample omega_2009 = safediv(((t_sample)6283.1853071796), samplerate);
		t_sample sn_2010 = sin(omega_2009);
		t_sample cs_2001 = cos(omega_2009);
		t_sample b_2005 = safediv(((int)1), ((((t_sample)2.2589254117942) - (((t_sample)0.25892541179417) * cs_2001)) + (((t_sample)1.5867737153067) * sn_2010)));
		t_sample a_2006 = ((((t_sample)1.2589254117942) * ((((t_sample)2.2589254117942) + (((t_sample)0.25892541179417) * cs_2001)) + (((t_sample)1.5867737153067) * sn_2010))) * b_2005);
		t_sample a_2004 = ((((t_sample)-2.5178508235883) * (((t_sample)0.25892541179417) + (((t_sample)2.2589254117942) * cs_2001))) * b_2005);
		t_sample a_1998 = ((((t_sample)1.2589254117942) * ((((t_sample)2.2589254117942) + (((t_sample)0.25892541179417) * cs_2001)) - (((t_sample)1.5867737153067) * sn_2010))) * b_2005);
		t_sample b_2008 = ((((int)2) * (((t_sample)0.25892541179417) - (((t_sample)2.2589254117942) * cs_2001))) * b_2005);
		t_sample b_1999 = (((((t_sample)2.2589254117942) - (((t_sample)0.25892541179417) * cs_2001)) - (((t_sample)1.5867737153067) * sn_2010)) * b_2005);
		t_sample expr_1817 = a_2006;
		t_sample expr_1818 = a_2004;
		t_sample expr_1819 = a_1998;
		t_sample expr_1820 = b_2008;
		t_sample expr_1821 = b_1999;
		t_sample expr_1766 = ((((int)500) * samplerate) * ((t_sample)0.001));
		t_sample loadbang_next_2014 = fixdenorm(((int)0));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample out3 = m_history_1;
			t_sample mul_1996 = (in1 * m_history_1);
			t_sample out1 = mul_1996;
			t_sample mul_1995 = (in2 * m_history_1);
			t_sample out2 = mul_1995;
			t_sample tap_1984 = m_delay_38.read_linear(div_1982);
			t_sample tap_1979 = m_delay_37.read_linear(mul_1981);
			t_sample tap_1977 = m_delay_36.read_linear(mul_1980);
			t_sample mix_2042 = (m_y_27 + (((t_sample)0.014247103707103) * (mul_1995 - m_y_27)));
			t_sample mix_1923 = mix_2042;
			t_sample sub_1882 = (mul_1995 - mix_1923);
			t_sample mul_1888 = (m_history_34 * expr_1932);
			t_sample mul_1890 = (m_history_33 * expr_1931);
			t_sample mul_1893 = (sub_1882 * expr_1930);
			t_sample mul_1886 = (m_history_32 * expr_1933);
			t_sample mul_1884 = (m_history_35 * expr_1934);
			t_sample sub_1892 = (((mul_1893 + mul_1890) + mul_1888) - (mul_1884 + mul_1886));
			t_sample gen_1898 = sub_1892;
			t_sample history_1885_next_1894 = fixdenorm(m_history_32);
			t_sample history_1889_next_1895 = fixdenorm(m_history_33);
			t_sample history_1891_next_1896 = fixdenorm(sub_1882);
			t_sample history_1887_next_1897 = fixdenorm(sub_1892);
			t_sample gen_1938 = gen_1898;
			t_sample mix_2043 = (m_y_27 + (((t_sample)0.014247103707103) * (mul_1996 - m_y_27)));
			t_sample mix_1926 = mix_2043;
			t_sample sub_1883 = (mul_1996 - mix_1926);
			t_sample mul_1912 = (m_history_30 * expr_1932);
			t_sample mul_1914 = (m_history_29 * expr_1931);
			t_sample mul_1917 = (sub_1883 * expr_1930);
			t_sample mul_1910 = (m_history_28 * expr_1933);
			t_sample mul_1908 = (m_history_31 * expr_1934);
			t_sample sub_1916 = (((mul_1917 + mul_1914) + mul_1912) - (mul_1908 + mul_1910));
			t_sample gen_1922 = sub_1916;
			t_sample history_1909_next_1918 = fixdenorm(m_history_28);
			t_sample history_1913_next_1919 = fixdenorm(m_history_29);
			t_sample history_1915_next_1920 = fixdenorm(sub_1883);
			t_sample history_1911_next_1921 = fixdenorm(sub_1916);
			t_sample gen_1937 = gen_1922;
			t_sample y0_next_1935 = fixdenorm(mix_1923);
			t_sample y0_next_1936 = fixdenorm(mix_1926);
			t_sample add_1968 = (m_counter_25 + ((int)1));
			t_sample clamp_1965 = ((add_1968 <= ((int)0)) ? ((int)0) : ((add_1968 >= expr_1989) ? expr_1989 : add_1968));
			t_sample div_1961 = safediv(m_average_24, clamp_1965);
			t_sample gen_1974 = div_1961;
			t_sample delta_1969 = __m_delta_40(expr_1989);
			int eq_1962 = (delta_1969 == ((int)0));
			t_sample mul_1964 = (clamp_1965 * eq_1962);
			t_sample tap_1971 = m_delay_26.read_linear(expr_1989);
			int gte_1958 = (clamp_1965 >= expr_1989);
			t_sample mul_1959 = (tap_1971 * gte_1958);
			t_sample abs_1957 = fabs(gen_1937);
			t_sample add_1967 = (m_average_24 + abs_1957);
			t_sample sub_1966 = (add_1967 - mul_1959);
			t_sample mul_1963 = (sub_1966 * eq_1962);
			t_sample counter_next_1972 = fixdenorm(mul_1964);
			t_sample average_next_1973 = fixdenorm(mul_1963);
			t_sample add_1950 = (m_counter_22 + ((int)1));
			t_sample clamp_1947 = ((add_1950 <= ((int)0)) ? ((int)0) : ((add_1950 >= expr_1989) ? expr_1989 : add_1950));
			t_sample div_1943 = safediv(m_average_21, clamp_1947);
			t_sample gen_1956 = div_1943;
			t_sample delta_1951 = __m_delta_41(expr_1989);
			int eq_1944 = (delta_1951 == ((int)0));
			t_sample mul_1946 = (clamp_1947 * eq_1944);
			t_sample tap_1953 = m_delay_23.read_linear(expr_1989);
			int gte_1940 = (clamp_1947 >= expr_1989);
			t_sample mul_1941 = (tap_1953 * gte_1940);
			t_sample abs_1939 = fabs(gen_1938);
			t_sample add_1949 = (m_average_21 + abs_1939);
			t_sample sub_1948 = (add_1949 - mul_1941);
			t_sample mul_1945 = (sub_1948 * eq_1944);
			t_sample counter_next_1954 = fixdenorm(mul_1946);
			t_sample average_next_1955 = fixdenorm(mul_1945);
			t_sample add_1985 = (gen_1974 + gen_1956);
			t_sample expr_1988 = ((((add_1985 + tap_1984) + tap_1979) + tap_1977) * ((t_sample)0.25));
			t_sample gen_1994 = expr_1988;
			t_sample out4 = gen_1994;
			t_sample tap_1871 = m_delay_20.read_linear(div_1869);
			t_sample tap_1866 = m_delay_19.read_linear(mul_1868);
			t_sample tap_1864 = m_delay_18.read_linear(mul_1867);
			t_sample mix_2044 = (m_y_9 + (((t_sample)0.014247103707103) * (in1 - m_y_9)));
			t_sample mix_1813 = mix_2044;
			t_sample sub_1770 = (in1 - mix_1813);
			t_sample mul_1799 = (m_history_17 * expr_1819);
			t_sample mul_1801 = (m_history_15 * expr_1818);
			t_sample mul_1804 = (sub_1770 * expr_1817);
			t_sample mul_1797 = (m_history_14 * expr_1820);
			t_sample mul_1795 = (m_history_16 * expr_1821);
			t_sample sub_1803 = (((mul_1804 + mul_1801) + mul_1799) - (mul_1795 + mul_1797));
			t_sample gen_1809 = sub_1803;
			t_sample history_1800_next_1805 = fixdenorm(m_history_15);
			t_sample history_1796_next_1806 = fixdenorm(m_history_14);
			t_sample history_1802_next_1807 = fixdenorm(sub_1770);
			t_sample history_1798_next_1808 = fixdenorm(sub_1803);
			t_sample gen_1824 = gen_1809;
			t_sample mix_2045 = (m_y_9 + (((t_sample)0.014247103707103) * (in2 - m_y_9)));
			t_sample mix_1810 = mix_2045;
			t_sample sub_1769 = (in2 - mix_1810);
			t_sample mul_1775 = (m_history_13 * expr_1819);
			t_sample mul_1777 = (m_history_11 * expr_1818);
			t_sample mul_1780 = (sub_1769 * expr_1817);
			t_sample mul_1773 = (m_history_10 * expr_1820);
			t_sample mul_1771 = (m_history_12 * expr_1821);
			t_sample sub_1779 = (((mul_1780 + mul_1777) + mul_1775) - (mul_1771 + mul_1773));
			t_sample gen_1785 = sub_1779;
			t_sample history_1776_next_1781 = fixdenorm(m_history_11);
			t_sample history_1772_next_1782 = fixdenorm(m_history_10);
			t_sample history_1778_next_1783 = fixdenorm(sub_1769);
			t_sample history_1774_next_1784 = fixdenorm(sub_1779);
			t_sample gen_1825 = gen_1785;
			t_sample y0_next_1822 = fixdenorm(mix_1813);
			t_sample y0_next_1823 = fixdenorm(mix_1810);
			t_sample add_1855 = (m_counter_7 + ((int)1));
			t_sample clamp_1852 = ((add_1855 <= ((int)0)) ? ((int)0) : ((add_1855 >= expr_1876) ? expr_1876 : add_1855));
			t_sample div_1848 = safediv(m_average_6, clamp_1852);
			t_sample gen_1861 = div_1848;
			t_sample delta_1856 = __m_delta_42(expr_1876);
			int eq_1849 = (delta_1856 == ((int)0));
			t_sample mul_1851 = (clamp_1852 * eq_1849);
			t_sample tap_1858 = m_delay_8.read_linear(expr_1876);
			int gte_1845 = (clamp_1852 >= expr_1876);
			t_sample mul_1846 = (tap_1858 * gte_1845);
			t_sample abs_1844 = fabs(gen_1824);
			t_sample add_1854 = (m_average_6 + abs_1844);
			t_sample sub_1853 = (add_1854 - mul_1846);
			t_sample mul_1850 = (sub_1853 * eq_1849);
			t_sample counter_next_1859 = fixdenorm(mul_1851);
			t_sample average_next_1860 = fixdenorm(mul_1850);
			t_sample add_1837 = (m_counter_4 + ((int)1));
			t_sample clamp_1834 = ((add_1837 <= ((int)0)) ? ((int)0) : ((add_1837 >= expr_1876) ? expr_1876 : add_1837));
			t_sample div_1830 = safediv(m_average_3, clamp_1834);
			t_sample gen_1843 = div_1830;
			t_sample delta_1838 = __m_delta_43(expr_1876);
			int eq_1831 = (delta_1838 == ((int)0));
			t_sample mul_1833 = (clamp_1834 * eq_1831);
			t_sample tap_1840 = m_delay_5.read_linear(expr_1876);
			int gte_1827 = (clamp_1834 >= expr_1876);
			t_sample mul_1828 = (tap_1840 * gte_1827);
			t_sample abs_1826 = fabs(gen_1825);
			t_sample add_1836 = (m_average_3 + abs_1826);
			t_sample sub_1835 = (add_1836 - mul_1828);
			t_sample mul_1832 = (sub_1835 * eq_1831);
			t_sample counter_next_1841 = fixdenorm(mul_1833);
			t_sample average_next_1842 = fixdenorm(mul_1832);
			t_sample add_1872 = (gen_1861 + gen_1843);
			t_sample expr_1875 = ((((add_1872 + tap_1871) + tap_1866) + tap_1864) * ((t_sample)0.25));
			t_sample gen_1881 = expr_1875;
			t_sample out5 = gen_1881;
			int gt_1764 = (gen_1881 > m_targetLevel_39);
			int gen_1768 = gt_1764;
			int switch_1760 = (gt_1764 ? ((int)0) : ((int)60000));
			__m_count_44 = (m_loadbang_2 ? 0 : (fixdenorm(__m_count_44 + ((int)1))));
			int carry_45 = 0;
			if ((m_loadbang_2 != 0)) {
				__m_count_44 = 0;
				__m_carry_46 = 0;
				
			} else if (((expr_1766 > 0) && (__m_count_44 >= expr_1766))) {
				int wraps_47 = (__m_count_44 / expr_1766);
				__m_carry_46 = (__m_carry_46 + wraps_47);
				__m_count_44 = (__m_count_44 - (wraps_47 * expr_1766));
				carry_45 = 1;
				
			};
			int counter_1741 = __m_count_44;
			int counter_1742 = carry_45;
			int counter_1743 = __m_carry_46;
			__m_latch_48 = (((counter_1742 + m_loadbang_2) != 0) ? m_loadbang_2 : __m_latch_48);
			t_sample latch_1735 = __m_latch_48;
			int switch_1736 = (latch_1735 ? ((int)1) : ((int)0));
			int switch_1761 = (gt_1764 ? ((int)0) : ((int)1));
			int neq_1750 = (switch_1761 != ((int)1));
			int gt_1759 = (gen_1994 > m_targetLevel_39);
			int switch_1751 = (gt_1759 ? ((int)0) : ((int)15000));
			int switch_1746 = (neq_1750 ? switch_1751 : ((int)0));
			int switch_1755 = (gt_1759 ? ((int)3000) : ((int)0));
			int switch_1748 = (neq_1750 ? switch_1755 : ((int)0));
			int iffalse_49 = ((switch_1760 + switch_1748) + switch_1746);
			int switch_1745 = (switch_1736 ? ((int)1) : iffalse_49);
			t_sample expr_1765 = ((samplerate * switch_1745) * ((t_sample)0.001));
			t_sample add_1754 = (m_history_1 + ((t_sample)0.1));
			t_sample switch_1752 = (gt_1759 ? ((int)0) : add_1754);
			t_sample switch_1747 = (neq_1750 ? switch_1752 : ((int)0));
			t_sample sub_1758 = (m_history_1 - ((t_sample)0.1));
			t_sample switch_1756 = (gt_1759 ? sub_1758 : ((int)0));
			t_sample switch_1749 = (neq_1750 ? switch_1756 : ((int)0));
			t_sample iffalse_50 = ((switch_1761 + switch_1749) + switch_1747);
			t_sample switch_1734 = (switch_1736 ? ((int)1) : iffalse_50);
			t_sample clamp_1728 = ((switch_1734 <= ((int)0)) ? ((int)0) : ((switch_1734 >= ((int)1)) ? ((int)1) : switch_1734));
			t_sample iup_52 = (1 / maximum(1, abs(expr_1765)));
			t_sample idown_53 = (1 / maximum(1, abs(expr_1765)));
			__m_slide_51 = fixdenorm((__m_slide_51 + (((clamp_1728 > __m_slide_51) ? iup_52 : idown_53) * (clamp_1728 - __m_slide_51))));
			t_sample slide_1730 = __m_slide_51;
			t_sample gen_1767 = slide_1730;
			t_sample out7 = gen_1768;
			t_sample out6 = gen_1767;
			t_sample history_1726_next_2015 = fixdenorm(gen_1767);
			m_delay_38.write(add_1985);
			m_counter_22 = counter_next_1954;
			m_average_21 = average_next_1955;
			m_delay_23.write(abs_1939);
			m_counter_25 = counter_next_1972;
			m_average_24 = average_next_1973;
			m_delay_26.write(abs_1957);
			m_history_32 = history_1887_next_1897;
			m_history_33 = history_1891_next_1896;
			m_history_34 = history_1889_next_1895;
			m_history_31 = history_1909_next_1918;
			m_history_28 = history_1911_next_1921;
			m_history_29 = history_1915_next_1920;
			m_history_30 = history_1913_next_1919;
			m_y_27 = y0_next_1935;
			m_y_27 = y0_next_1936;
			m_history_35 = history_1885_next_1894;
			m_delay_36.write(add_1985);
			m_delay_37.write(add_1985);
			m_delay_20.write(add_1872);
			m_counter_4 = counter_next_1841;
			m_average_3 = average_next_1842;
			m_delay_5.write(abs_1826);
			m_counter_7 = counter_next_1859;
			m_average_6 = average_next_1860;
			m_delay_8.write(abs_1844);
			m_history_14 = history_1798_next_1808;
			m_history_15 = history_1802_next_1807;
			m_history_16 = history_1796_next_1806;
			m_history_13 = history_1776_next_1781;
			m_history_10 = history_1774_next_1784;
			m_history_11 = history_1778_next_1783;
			m_history_12 = history_1772_next_1782;
			m_y_9 = y0_next_1822;
			m_y_9 = y0_next_1823;
			m_history_17 = history_1800_next_1805;
			m_delay_18.write(add_1872);
			m_delay_19.write(add_1872);
			m_loadbang_2 = loadbang_next_2014;
			m_history_1 = history_1726_next_2015;
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
		m_targetLevel_39 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
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
