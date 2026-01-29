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
    return ret[1..(strlen(ret) - 2)];
}

string
replace_strings(string in, string *from, string *to)
{
    int i;

    if(sizeof(from)!=sizeof(to))
	return 0;

    for( i=0 ; i<sizeof(from) ; i++)
	in = replace_string(in, from[i], to[i]);

    return in;
}

int
is_vocal(string in)
{
    return in=="a"||in=="e"||in=="i"||
	   in=="o"||in=="u"||in=="y";
}


mapping irregulars =
([

]);

/* cut(s)
 * try - tries
 * cry - cries
 * buy - buys
 * spy - spies
 * lay - lays
 * walk - walks
 * knee - knees
 *
 *
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
	    return tmp + slask + "es";
    }
    return str+"s";
}
