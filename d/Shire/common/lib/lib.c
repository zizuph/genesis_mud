/*
 * lib.c
 *
 * This files contains some useful routines which are called from a macro
 * in the file /d/Shire/common/include/lib.h
 *
 */

#include <composite.h>
#include <language.h>
#include <macros.h>
#include "defs.h"

inherit STRING_FILE;

#define REPLACE_BACK(what)  replace_strings(what, ({ "œœ", "¯" }), ({ "@@", "|" }))

object *gAll;
object gThisPlayer;
string gYou;

string
file_name(mixed what)
{
    if (stringp(what))
	return what;

    if (objectp(what))
	return efun::file_name(what);

    return 0;
}

string
late_cap(string vbfc)
{
    object for_obj;

    for_obj = previous_object(-2);
    if (!objectp(for_obj))
	for_obj = TP;
    if (!objectp(for_obj))
	for_obj = find_object("/std/object");

    vbfc = REPLACE_BACK(vbfc);

    return capitalize(for_obj->check_call(vbfc));
}

varargs string
late_break(string vbfc, int len = 76)
{
    object for_obj;

    for_obj = previous_object();
    if (!objectp(for_obj))
	for_obj = TP;
    if (!objectp(for_obj))
	for_obj = find_object("/std/object");

    vbfc = REPLACE_BACK(vbfc);

    return break_string(for_obj->check_call(vbfc), len);
}

/*
 * Function name:   break_it
 * Description:     breaks a string into a string array on the newlines.
 * Returns:	    Array of lines.
 */
string
break_it(string in, int dist)
{
    return break_string(in, dist);
}

/*
 * Function name:   smart_break_string
 * Description:     Similar to break_string, but fixes newline-chars.
 */
varargs string
smart_break_string(string str, int dis = 76)
{
    string *exp;
    string *brk;

    exp = explode(str, "\n");

    if (sizeof(exp) == 1)
	return break_string(str, dis);

    brk = map(exp, "break_it", TO, dis);

    return (str[0..0]=="\n"?"\n":"")
	 + implode(brk, "\n")
	 + (str[-1..-1]=="\n"?"\n":"");
}

string
vbfc_possessive(mixed who)
{
    object for_obj;

    who = find_object(who);
    if (!who || !living(who))
	return "someone wierd's";
    for_obj = previous_object(-2);
    if (for_obj == who)
	return "your";
    else
	return LANG_POSS(who->query_the_name(for_obj));
}

string
vbfc_cap_possessive(mixed who)
{
    object for_obj;

    who = find_object(who);
    if (!who || !living(who))
	return "Someone wierd's";
    for_obj = previous_object(-2);
    if (for_obj == who)
	return "Your";
    else
	return LANG_POSS(who->query_The_name(for_obj));
}

string
he_she(mixed who)
{
    object for_obj;

    who = find_object(who);
    if (!living(who))
	return "something";
    for_obj = previous_object(-2);
    if (for_obj == who)
	return "you";
    else
	return HE_SHE(who);
}

string
cap_he_she(mixed who)
{
    return CAP(he_she(who));
}

string
him_her(mixed who)
{
    object for_obj;

    who = find_object(who);
    if (!living(who))
	return "something";
    for_obj = previous_object(-2);
    if (for_obj == who)
	return "you";
    else
	return HIM_HER(who);
}

string
cap_him_her(mixed who)
{
    return CAP(him_her(who));
}

string
his_her(mixed who)
{
    object for_obj;

    who = find_object(who);
    if (!living(who))
	return "something's";
    for_obj = previous_object(-2);
    if (for_obj == who)
	return "your";
    else
	return HIS_HER(who);
}

string
cap_his_her(mixed who)
{
    return CAP(his_her(who));
}

string
qtname(mixed who)
{
    object for_obj;

    who = find_object(who);
    if (!living(who))
	return "something";
    for_obj = previous_object(-2);
    if (for_obj == who)
	return "you";
    else
	return who->query_the_name(for_obj);
}

string
qctname(mixed who)
{
    object for_obj;

    who = find_object(who);
    if (!living(who))
	return "Something";
    for_obj = previous_object(-2);
    if (for_obj == who)
	return "You";
    else
	return who->query_The_name(for_obj);
}

string
ending(string for_other, string for_me, mixed who)
{
    object for_obj;

    who = find_object(who);
    if (!living(who))
	return for_other;

    for_obj = previous_object(-2);
    if (for_obj == who)
	return for_me;
    else
	return for_other;
}

/*
 * Alternative forms for subject, object and others respectively.
 */
string
alternative_form(
    string str_subj, string str_obj, string str_other,
    mixed subj, mixed obj)
{
    object for_obj;

    subj = find_object(subj);
    if (!living(subj))
	return "#ERROR#";

    if (stringp(obj))
	obj = find_object(obj);

    for_obj = previous_object(-2);

    if (for_obj == subj)
	return REPLACE_BACK(str_subj);
    if (for_obj == obj)
	return REPLACE_BACK(str_obj);

    if (str_other == "**")
	return REPLACE_BACK(str_obj);

    if (str_other == "*")
	return REPLACE_BACK(str_subj);

    return REPLACE_BACK(str_other);
}

/*
 * Form for just one living.
 */
string
for_object(string vbfc, mixed who)
{
    object for_obj;

    who = find_object(who);
    if (!living(who))
	return "";

    for_obj = previous_object(-2);

    if (for_obj == who)
	return REPLACE_BACK(vbfc);
    else
	return "";
}


varargs string
composite_live(object *livs, string ytext = "you", object tp = TP)
{
    int pos = member_array(tp, livs);
    object *oth;
    string str;

    gAll = livs;
    gYou = ytext;

    if (pos >= 0)
    {
	gThisPlayer = tp;
	gAll -= ({ tp });

	switch (sizeof(gAll))
	{
	    case 0:
		return ytext;
	    case 1:
		return ytext + " and " + QTNAME(gAll[0]);
	    default:
		return ytext + ", " + COMPOSITE_LIVE(gAll);
	}
    }
    else
    {
	gThisPlayer = 0;
	return COMPOSITE_LIVE(gAll);
    }
}

varargs string
fo_composite_live(object for_who = previous_object())
{
    object *oth;
    int pos = member_array(for_who, gAll);
    string str;

    if (pos>=0)
    {
	oth = exclude_array(gAll, pos, pos);

	if (gThisPlayer)
	{
	    str = HIM_HER(gThisPlayer) + "self";

	    switch (sizeof(oth))
	    {
		case 0:
		    return gYou + " and " + str;
		case 1:
		    return gYou + ", " + str + " and " + QTNAME(oth[0]);
		default:
		    return gYou + ", " + str + ", " + COMPOSITE_LIVE(oth);
	    }
	}
	else
	    switch (sizeof(oth))
	    {
		case 0:
		    return gYou;
		case 1:
		    return gYou + " and " + QTNAME(oth[0]);
		default:
		    return gYou + ", " + COMPOSITE_LIVE(oth);
	    }
    }
    else if (gThisPlayer)
    {
	str = HIM_HER(gThisPlayer) + "self";
	switch (sizeof(gAll))
	{
	    case 0:
		return str;
	    case 1:
		return str + " and " + QTNAME(gAll[0]);
	    default:
		return str + ", " + COMPOSITE_LIVE(gAll);
	}
    }
    else
	return COMPOSITE_LIVE(gAll);
}

/*
tell_room(
   CTNAME(TP) + VERB("is") + " hit as " + CHE_SHE(TP) + " " + VERB("walks")
*/

string
do_verb(string verb, mixed who)
{
    object for_obj;

    who = find_object(who);
    if (!living(who))
	return verb;

    for_obj = previous_object(-2);

    if (for_obj == who)
	return verb;
    else
	return STRING_FILE->verb_present(verb);
}
