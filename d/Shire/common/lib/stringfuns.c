string
str_to(string in, int to)
{
    return extract(in,0,to-1);
}

string
str_from(string in, int from)
{
    return extract(in,from+1);
}

/*
 * Function:	index
 * Description: Finds the index of a string in another string.
 * Arguments:	str, substr.
 * Returns:	index if found, -1 if not.
 */
static int
index(string str, string substr)
{
    string *brk;

    brk = explode(str, substr);

    if (sizeof(brk) > 1)
	return strlen(brk[0]);
    if (str[0..(strlen(substr) - 1)] == substr)
	return 0;
    if (str[(strlen(str) - strlen(substr))..(strlen(str) - 1)] == substr)
	return strlen(str)-1;
    return -1;
}

/*
 * Function:	replace_string
 * Description: Replaces all occurances of a string to another string of a string.
 * Arguments:	str  - Base string.
 *		from - Which occurances to change.
 *		to   - What to change it with.
 * Returns:	The changed string.
 */
string
replace_string(string str, string from, string to)
{
    string *brk;
    string ret;
    int i;

    brk = explode("_"+str+"_", from);

    if (sizeof(brk)==1)
	return str;

    ret = implode(brk, to);
    return ret[1..-2];
}

string
replace_strings(string in, string *from, string *to)
{
    int i;

    if(sizeof(from)!=sizeof(to))
	return 0;

    for(i=0;i<sizeof(from);i++)
	in = replace_string(in, from[i], to[i]);

    return in;
}

/*
 * Function name:   keep_explode
 * Arguments:	    string str	- String to explode.
 *		    string *on	- What to explode on.
 * Returns:	    An array of strings.
 * Description:     Returns an array of strings where the
 *		    strings that it is exploded on is in the
 *		    correct posision.
 * Examples:
 * keep_explode("A little, tiny text. Yes!", ({ ",", ".", "!", " "}))
 *  == ({ "A", " ", "little", ",", " ", "tiny", " ", "text", ".",
 *	  " ", "Yes", "!" })
 */

string *
keep_explode_str(mixed str, string on)
{
    string s1, s2;
    int i;
    string *ret = ({});

    if (pointerp(str))
    {
	for (i = 0; i < sizeof(str); i++)
	    ret += keep_explode_str(str[i], on);
	return ret;
    }

    if (!stringp(str) || strlen(str) == 0)
	return ({});

    if (sscanf(str, "%s"+on+"%s", s1, s2) != 2)
	return ({ str });

    if (strlen(s1))
	ret += ({ s1 });

    ret += ({ on });

    return ret + keep_explode_str(s2, on);
}

string *
keep_explode(string str, mixed on)
{
    int size;
    int i;
    string *ret;

    if (stringp(on))
	on = ({ on });
    if ((size=sizeof(on)) == 0)
	return ({});
    else if (size == 1)
	return keep_explode_str(str, on[0]);
    else
    {
	ret = keep_explode_str(str, on[0]);
	for (i=1; i<sizeof(on); i++)
	    ret = keep_explode_str(ret, on[i]);
	return ret + ({});
    }
}

varargs string
smart_replace(string str, ...)
{
    string *brk;
    string ret = "";
    int i;
    mapping from_to;

    if (sizeof(argv) == 1 && mappingp(argv[0]))
	from_to = argv[0];
    else if (sizeof(argv) == 2 && pointerp(argv[0]) && pointerp(argv[1]))
	from_to = mkmapping(argv[0], argv[1]);
    else if (sizeof(argv) == 2 && stringp(argv[0]) && stringp(argv[1]))
	from_to = ([ argv[0] : argv[1] ]);
    else
	return str;

    brk = keep_explode(str, m_indexes(from_to));

    for (i=0; i<sizeof(brk); i++)
	if (from_to[brk[i]])
	    ret += from_to[brk[i]];
	else
	    ret += brk[i];

    return ret;
}

int
is_vocal(string in)
{
    return in=="a"||in=="e"||in=="i"||
	   in=="o"||in=="u"||in=="y";
}


mapping irregulars =
([
    "are" : "is",
    "is"  : "are",
]);

/* cut(s)
 * try - tries
 * cry - cries
 * buy - buys
 * spy - spies
 * lay - lays
 * walk - walks
 * knee - knees
 * go	- goes
 */
string
verb_present(string str)
{
    string tmp, slask;
    int sl, ch;

    if (!str) return 0;

    if (irregulars[str])
	return irregulars[str];

    sl = strlen(str) - 1;
    if (sl < 2)
	return str;

    ch = str[sl];
    tmp = extract(str, 0, sl - 2);
    slask = extract(str, sl - 1, sl - 1);
    switch(ch)
    {
	case 'y':
	    if(is_vocal(slask))
		return tmp + slask + "s";
	    else
		return tmp + slask + "ies";
	case 'h':
	case 'x':
	case 's':
	case 'z':
	case 'o':
	    return tmp + slask + "es";
    }
    return str+"s";
}
