#include <language.h>
#include "defs.h"

void tell_me(string str) {
    object me;

    me = find_player("rogon");
    if (me) {
      switch (me->query_prop("_rogon_wants_debug")) 
	{
	  case "yes"  : me->catch_msg(str); break;
	  case "no"   : ;
	  case "log"  : log_file("SPELL_LIST", str); break;
	  case "both" : me->catch_msg(str); log_file("SPELL_LIST", str); break;
	  default: ;
	}
    }
    else
	log_file("SPELL_LIST",str);
}

/*
 * Function: level(object who)
 * Desc:     Makes an pseudo spell level of a caster dependant
 *           upon the realm of this_object() and the prime stat
 *           for this realm and opposing stats giving penalties.
 * Returns:  The level of the spellcaster.
 */
int
level(object who) 
{
    int lev;

    if (who->query_wiz_level())
	return ((lev = who->query_prop("_rogon_i_level")) == 0) ? 25 : lev;
    else
	return who->query_spell_level();
}

mixed trans_q = ({
    0, "",
    1, "esta",
    2, "atta",
    3, "nelde",
    4, "kanta",
    5, "lempe",
    6, "enque",
    7, "otso",
    8, "toldo",
    9, "nerte",
   10, "anwa"
});

string
num2quenya(int num)
{
    if (num < 0)
	return "";
    if (num > 10)
	num = 10;

    return trans_q[num*2 + 1];
}

int
quenya2num(string str) 
{
    int i;

    str = lower_case(str);
    i = member_array(str, trans_q);
    if (i == -1)
	return 0;
    else
	return trans_q[i-1];
}

int
is_class(string str)
{
    int d;
    str = lower_case(str);

    if (sscanf(str, "%d", d) == 1)
	return 1;
    if (member_array(str, ({"i","ii","iii","iv","v","x","true"}))>=0)
	return 1;
    if (member_array(str, trans_q)>=0)
	return 1;
    return 0;
}

int 
class2num(string str)
{
    int ret;
    str=lower_case(str);

    if (sscanf(str,"%d",ret) == 1)
	return ret;

    if (ret = quenya2num(str))
	return ret;

    return ([ "i":1, "ii":2, "iii":3, "iv":4, "v":5, "true":10, "x":10 ])[str];
}

mixed
parse_roman(string *words) 
{
    int d;
    string str;

    if (!sizeof(words))
	return ({ 1, ({}) });

    str = lower_case(words[0]);

    if (sscanf(str,"%d",d) == 1) 
    {
	words = exclude_array(words, 0, 0);
	return ({ d, words });
    }

    d = ([ "i":1, "ii":2, "iii":3, "iv":4, "v":5, "true":10, "x":10 ])[str];
    
    if (d == 0)
	return ({ 1, words });
    
    words = exclude_array(words, 0, 0);
    return ({ d, words });
}

string 
roman_str(int num) 
{
    switch (num) 
    {
    case 0: return "-";
    case 1: return "I";	    
    case 2: return "II";
    case 3: return "III";
    case 4: return "IV";
    case 5..9: return "V";
    case 10: return "true";
    default: return "" + num;
    }
}

string
num2order(int num) 
{
    switch (num%100) 
    {
        case 11..13: return num + "th";
    }
    switch (num%10) 
    {
        case 1: return num + "st";
	case 2: return num + "nd";
	case 3: return num + "rd";
	default: return num + "th";
    }
}


    
int medium(int t1, int t2)
{
    return (t1 + t2)/2;
}

int sort_fun(mixed arg1, mixed arg2)
{
    return arg1[0]-arg2[0];
}

mixed *den_values = ({});
int *den_indexes  = ({});

void
update_values()
{
    int *parts = ({ 12, 10, 8, 6, 4, 3, 2 });
    mixed *temp	= ({});
    mapping m  = ([]);
    int i,j;

    for (i = 0; i < sizeof(parts) ; i++)
	for (j = 1; j < parts[i]; j++)
	    m[j * 1000 / parts[i]] = ({ j, i });

    den_indexes = m_indexes(m);
    den_values	= m_values(m);
    
    for (i=0;i<sizeof(den_indexes);i++)
	temp += ({ ({ den_indexes[i], den_values[i] }) });

    temp = sort_array(temp, "sort_fun");
    den_indexes = ({}); den_values = ({});

    for (i=0;i<sizeof(temp);i++) 
    {
	den_indexes += ({ temp[i][0] });
	den_values  += ({ temp[i][1] });
    }
}

string
nth_str(int num, int den)
{
    int *parts = ({ 12, 10, 8, 6, 4, 3, 2 });
    string *parts_str = ({ "twelfths", "tenths", "eights",
			   "sixths", "fourths", "thirds", "halves" });
    string *part_str  = ({ "twelfth", "tenth", "eight",
			   "sixth", "fourth", "third", "half" });
    int *splits = ({});
    int i,j,no;

    if (den == 0 || num/den!=0)
	return "";

    if (!sizeof(den_indexes))
	update_values();
    no = sizeof(den_indexes)-1;

    num = num * 1000 / den;
    if (num <= medium(den_indexes[0], den_indexes[1]))
	return LANG_WNUM(1) + " " + part_str[0];
    if (num >= medium(den_indexes[no-1], den_indexes[no]) )
	return LANG_WNUM(den_values[no][0]) + " " + parts_str[den_values[no][1]];

    for (i = 1; i < sizeof(den_indexes) - 1; i++)
	splits += ({ medium(den_indexes[i], den_indexes[i+1]) });

    j = 0;
    for (i = 0; i < sizeof(splits); i++)
	if (num<splits[i]) 
	{
	    j = i;
	    break;
	}

    j ++;
    if (j >= 0 && j < sizeof(den_values) && sizeof(den_values[j]) == 2)
	return LANG_WNUM(den_values[j][0]) + "-" +
	       (den_values[j][0] == 1 ? part_str[den_values[j][1]] :
					parts_str[den_values[j][1]]);
    else
	return "Error!";
}

varargs string
ratio_str(int num, int den, string eq_str = "about the same")
{
    int dividend;

    if (num < 0)
	num = -num;
    if (den < 0)
	den = -den;

    if (num >= den) 
    {
	if (den == 0)
	    return "infinetely times";

	switch (dividend = num/den) 
	{
	case 1:
	    if (num == den)
		return eq_str;
	    else
		return "one and " + nth_str(num - den, den);
	case 2:
	    if (num == 2 * den)
		return "about twice";
	    else
		return "two and " + nth_str(num - 2 * den, den);
	case 3..12:
	    if (num == dividend * den)
		return "about " + LANG_WNUM(dividend) + " times";
	    else
		return LANG_WNUM(dividend) + " and " +
		    nth_str(num - dividend * den, den) + " times";
	    
	case 13..50: return "about " + LANG_WNUM(dividend /2 * 2)+" times";
	case 51..99: return "about " + LANG_WNUM(dividend /5 * 5)+" times";
	    
	case 100..199: return "about a hundred times";
	case 200..299: return "about two-hundred times";
	case 300..399: return "about three-hundred times";
	case 400..499: return "about four-hundred times";
	case 500..999: return "almost a thousand times";
	case 1000..1999: return "over a thousand times";
	case 2000..2999: return "over two thousand times";
	case 3000..3999: return "over three thousand times";
	case 4000..4999: return "over four thousand times";
	case 5000..5999: return "over five thousand times";
	case 6000..9999: return "almost ten thousand times";
	default: return "over ten thousand times";
	} /* Switch */
    } /* num < den */
    else 
	return nth_str(num,den);
}

/*
 * This function returns an array of size 'size'
 * of random numbers such that the sum of all 
 * the elements equals 'wanted_sum'.
 */
int *
rnd_dist(int size, int wanted_sum)
{
    int *a = allocate(size);
    int i, sum = 0;

    for (i = 0; i < sizeof(a); i++)
    {
	a[i] = random(1000)+1;
	sum += a[i];
    }
    
    for (i = 0; i < sizeof(a); i++)
	a[i] = a[i] * wanted_sum / sum;

    return a + ({ });
}

/*
 * Function name:   desc_diff
 * Arguments:	    diff
 * Returns:	    A string describing the difficulty of a task.
 */
string
desc_diff(int diff)
{
    if (diff < 50)
	return "mundane";

    switch ((diff+49)/100)
    {
	case 1: return "trivial";
	case 2: return "routine";
	case 3: return "easy";
	case 4: return "light";
	case 5: return "medium";
	case 6: return "hard";
	case 7: return "very hard";
	case 8: return "extremely hard";
	case 9: return "sheer folly";
	case 10: return "absurd";
	case 11: return "insane";
	case 12: return "phenomenal";
	case 13: return "supernatural";
	default: return "impossible";
    }
}
