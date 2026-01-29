/*
 * File: /d/Shire/common/lib/tell.c
 *
 * The redefined, easy to use and much faster tellem()-routine!!
 */

/*
 * Function name:   tellem
 * Arguments:	    subjective	(object)
 *			The object which is the subject of the action.
 *		    objective	(object)
 *			The object which is the object of the action.
 *		    text	(string)
 *			The special tellem format.
 *		    tell_all	(int)
 *			0 [default] : Tell only those who see fights.
 *			1	    : Tell all in this room.
 * Description:
 *	This routine is special, since it includes outputing of text
 *	to involved parties in one special tellem format. This format
 *	is specified below.
 */

/*

NAME
	tellem format	- The format used in the tellem style.

SYNOPSIS
	Information only to use with the tellem functions.

DESCRIPTION
	The tellem format is used to simply produce text in a standard
	fashion in a simple way. The format is supposed to be as flexible
	as possible, being fast and versatile.

	To understand it it is needed to know that the tellem format is
	just a formalazition of the usual write/say routines which use
	macros like QCTNAME and etc.

	In order to differenciate between special codes and pure text
	the following syntax is reserved:

	    (text)
	    [text]

	    {text}
	    {text1;text2}
	    {text1;text2;text3}

WARNING!!
	This routine is not as fast as macro functions using write()
	and say(), so unless you have good reason, you should *not*
	use this file.

PRONOUNS
	Defined pronouns are the following:

	you, your, yourself, he, him, his, himself
	You, Your, Yourself, He, Him, His.

	The gender is always defined as male, but if the subject, object is
	of another gender, it automatically gets right.

	Forms: () or [].

	If you use the ()-format, you will refer to the object by its name,
	[] refers to the no-name form. Examples:

	Subject: Galadriel, a garlanded elf, female champion.
	Object : Rogon, an odd dwarf. (male)

		     Subject		    |		 Object
	      Met	| Nonmet desc	    | Met	   | Nonmet
---------------------------------------------------------------------------------
(you)	    : you			    | Galadriel	   | the garlanded elf
(your)	    : your			    | Galadriel's  | the garlanded elf's
(yourself)  : yourself			    | herself	   | herself
(he)	    : Rogon	| the odd dwarf     | you
(him)	    : Rogon	| the odd dwarf     | you
(his)	    : Rogon's   | the odd dwarf's   | your
(himself)   : himself			    | yourself

(You)	    : You			    | Galadriel	   | The garlanded elf
(Your)	    : Your			    | Galadriel's  | The garlanded elf's
(Yourself)  : Yourself			    | Herself	   | Herself
(He)	    : Rogon	| The odd dwarf	    | You
(Him)	    : Rogon	| The odd dwarf     | You
(His)	    : Rogon's   | The odd dwarf's   | Your

[you]	    : you			    | she
[your]	    : your			    | her
[yourself]  : yourself			    | herself
[he]	    : he			    | you
[him]	    : him			    | you
[his]	    : his			    | your
[himself]   : himself			    | yourself

Ditto with capitalized [You] [Your] etc.
---------------------------------------------------------------------------------


VERBS
	For verbs to function a similar syntax is used:

	()'s for verb present forms means meant for the subject, not objects.
	[]'s for verb present forms means NOT meant for the subject.

	Defined are:
	    (is), (are), (s), [s], (es), [es], (y), (ies).

	Examples:

	(You) chant[s] a spell.

	    Galadriel gets: You chant a spell.
	    Rogon gets:	Galadriel chants a spell.	     (met)
			The garlanded elf chants a spell.    (nonmet)

	(He) (is) devastated by (your) spell.

	    Galadriel gets: Rogon is devastated by your spell.	      (met)
			    The odd dwarf is devastated by your spell.(nonmet)
	    Rogon gets:     You are devastated by Galadriel's spell.  (met)
			    You are devastated by the garlanded elf's spell.
								      (nonmet)

	(He) fumble(s) with [his] weapon.

	    Galadriel gets: Rogon fumbles with his weapon.		(met)
			    The odd dwarf fumbles with his weapon.	(nonmet)
	    Rogon gets:     You fumble with your weapon.


	(You) cr(y) out in pain!

	    Galadriel gets: You cry out in pain!
	    Rogon gets:     Galadriel cries out in pain!		(met)
			    The garlanded elf cries out in pain!	(nonmet)


ALTERNATIVE FORMS
	{text1;text2;text3} is used to give

	    text1: to the subject
	    text2: to the object
	    text3: to other living objects.

	{text1;text2} is used to give

	    text1: to the subject
	    text2: to the object and other livings.

	{text1;text2;*} is used to give

	    text1: to the subject and other livings.
	    text2: to the object

	{text1} is used to give

	    text1: to the subject only.

	NOTE: You can use () or [] forms within a {;;} construct:

	    {You feel a terrible pain!;(You) looks terribly hurt.}

	But you can not use {;;} within {;;}'s. (Why should you?)

EXAMPLES
	(You) hit[s] (him) nastily with [your] battle hammer.
	(He) cr(ies) like a baby when seeing that [his] hammer is lost.

IMPLEMENTATION
	The implementation uses the function replace_string and replace_strings
	from the file /d/Shire/common/lib/stringfuns.c

*/

#include <macros.h>
#include <filter_funs.h>
#include <composite.h>
#include <stdproperties.h>
#include "../defs.h"
#include "/d/Shire/common/include/lib.h"

#define BRACK "["
#define ENDBRACK "]"
#define BRACE "{"
#define DELIM ";"
#define ENDBRACE "}"

inherit "/d/Shire/common/lib/stringfuns";

string
replace_forms(string part, object subj, object obj)
{
    string ret = smart_replace(part,
	    ([
	       "(You)"	: VCTNAME(subj),
	       "(you)"	: VTNAME(subj),
	       "(Your)" : VCPOSS(subj),
	       "(your)" : VPOSS(subj),

	       "[You]"	: VCHE_SHE(subj),
	       "[you]"	: VHE_SHE(subj),
	       "[Your]" : VCHIS_HER(subj),
	       "[your]" : VHIS_HER(subj),

	       "(Yourself)"	: VCHIM_HER(subj)+"self",
	       "(yourself)"	: VHIM_HER(subj)+"self",

	       "(are)"	: V_IS(subj),
	       "(is)"	: V_IS(obj),
	       "(have)"	: V_HAS(subj),
	       "(has)"	: V_HAS(obj),

	       "(s)"	: V_S(subj),
	       "[s]"	: V_S(obj),
	       "(es)"	: V_ES(subj),
	       "[es]"	: V_ES(obj),
	       "(y)"	: V_IES(subj),
	       "(ies)"	: V_IES(obj),

	       "(Him)"	: VCTNAME(obj),
	       "(him)"	: VTNAME(obj),
	       "[Him]"	: VCHIM_HER(obj),
	       "[him]"	: VHIM_HER(obj),
	       "(himself)"	: VHIM_HER(obj)+"self",
	       "[He]"	: VCHE_SHE(obj),
	       "[he]"	: VHE_SHE(obj),
	       "(He)"	: VCTNAME(obj),
	       "(he)"	: VTNAME(obj),
	       "[His]"	: VCHIS_HER(obj),
	       "[his]"	: VHIS_HER(obj),
	       "(His)"	: VCPOSS(obj),
	       "(his)"	: VPOSS(obj)
	    ])
    );
    write("FORMS ret = " + ret + "\n");
    return ret;
}

string
replace_braces(string str, object subj, object obj)
{
    int ind;
    string ret = "";
    string left;
    string part;
    string *p = ({ "", "", "" });


    ind = index(str, BRACE);
    if (ind == -1)
	return str;

    left = str;

    write("   <START> str  = " + str + "\n");
    write("           left = " + left + "\n");
    write("           ind  = " + ind + "\n");
    while (ind != -1)
    {
	if (ind > 0)
	    ret = str_to(left, ind);

	left = str_from(left, ind);
	ind = index(left, ENDBRACE);
	part = str_to(left, ind);

	write("    <LOOP> ind  = " + ind + "\n");
	write("           ret  = " + ret + "\n");
	write("           left = " + left + "\n");
	write("           part = " + part + "\n");

	if (sscanf(part, "%s"+DELIM+"%s"+DELIM+"%s", p[0], p[1], p[2])==3)
	    ret += V_ALT(p[0], p[1], p[2], subj, obj);
	else if (sscanf(part, "%s"+DELIM+"%s", p[0], p[1])==2)
	    ret += V_ALT(p[0], p[1], AS_OBJ, subj, obj);
	else
	    ret += V_FOR(subj, part);

	write("    <SCAN> ret  = " + ret + "\n");

	left = str_from(left, ind);
	ind  = index(left, BRACE);

	write("     <END> ind  = " + ind + "\n");
	write("           left = " + left + "\n");
    }

    write("  <RETURN> ret = " + ret + "\n");
    return ret;
}

string
replace2vbfc(string str, object obj, object subj)
{
    str = replace_forms(str, obj, subj);
    str = replace_braces(str, obj, subj);
    return str;
}

string *
split_braces(string str)
{
    string *brk = ({ "", "", "" });
    string *p = ({ "", "", "" });
    int ind;
    string part, left;

    ind = index(str, BRACE);
    if (ind == -1)
	return ({ str, str, str });

    left = str;
    while (ind != -1)
    {
	if (ind>0)
	{
	    brk[0] += str_to(left, ind);
	    brk[1] += str_to(left, ind);
	    brk[2] += str_to(left, ind);
	}

	left = str_from(left, ind);
	ind = index(left, ENDBRACE);
	part = str_to(left, ind);

	if (sscanf(part, "%s"+DELIM+"%s"+DELIM+"%s", p[0], p[1], p[2])==3)
	{
	    brk[0] += p[0];
	    brk[1] += p[1];
	    brk[2] += (p[2]=="*"?p[0]:p[2]);
	}
	else if (sscanf(part, "%s"+DELIM+"%s", p[0], p[1])==2)
	{
	    brk[0] += p[0];
	    brk[1] += p[1];
	    brk[2] += p[1];
	}
	else
	{
	    brk[0] += part;
	}

	left = str_from(left, ind);
	ind  = index(left, BRACE);
    }

    brk[0] += left;
    brk[1] += left;
    brk[2] += left;

    return brk;
}

int
sees_fight(object ob)
{
    return ob->query_see_blood();
}

/*
 * Function name:   break_tell
 * Arguments:	    object who	- who to catch the message
 *		    string what - what to catch
 *		    int width	- the line width (default = 76)
 */
varargs void
break_tell(object who, string what, int width = 76)
{
    who->catch_msg(break_string(what, 76));
}

/*
 * Function name:   tell_raw
 *
 * Arguments:	    tp	   - the subject
 *		    target - the object
 *		    str    - the tellem format string
 *		    tell_bits - tell bits
 *			1 : Filter not seeing fights.
 *			2 : Filter can not see subject.
 *			4 : Filter can not see object.
 *
 * Description:     This is the main tellem routine, which all
 *		    tellem-based routines are based upon.
 */
varargs void
tell_raw(object tp, object target, string str, int tell_bits = 1, object *tell_not = ({}))
{
    object *watchers = FILTER_LIVE(all_inventory(ENV(tp)));
    string *split;
    int i;

    watchers -= ({ tp, target });

    if (sizeof(tell_not))
	watchers -= tell_not;

    if(tell_bits & 1)
	watchers = filter(watchers, "sees_fight", this_object());
    if(tell_bits & 2)
	watchers = FILTER_CAN_SEE(watchers, tp);
    if(tell_bits & 4 && living(target))
	watchers = FILTER_CAN_SEE(watchers, target);

    split = split_braces(str);

    tp->catch_msg(replace_forms(split[0], tp, target));

    if (target && tp != target)
	target->catch_msg(replace_forms(split[1], tp, target));

    if (sizeof(watchers))
	watchers->catch_msg(replace_forms(split[2], tp, target));
}

/*
 * Function name:   TellRoom
 * Arguments:	    object subj     - The subject.
 *		    object obj	    - The object.
 *		    string format   - The tellem format string.
 * Description:     Produces a text to all in a room.
 */
void
TellRoom(object subj, object obj, string format)
{
    tell_room(ENV(subj), T_SYNTAX(format, subj, obj));
}


/*
 * Function name:   Tell
 * Arguments:	    object subj     - The subject.
 *		    object obj	    - The object.
 *		    string format   - The tellem format string.
 * Description:     Produces a text to all in a room, where only
 *		    those seeing fights also seeing both the
 *		    subject and the object (if it is a living)
 *		    get any text.
 */
void
Tell(object subj, object obj, string format)
{
    tell_raw(subj, obj, format, 7);
}

varargs void
Write(mixed arg1, mixed arg2 = TP)
{
    object tp;
    string str;

    if(stringp(arg1))
	str = arg1;
    if(objectp(arg1))
	tp = arg1;
    if(stringp(arg2))
	str = arg2;
    tell_raw(tp,0,str,2);
}

/*
 * Function name:   tellem
 * Arguments:	    object a	 - The attacker (subject)
 *		    object v	 - The victim	(object)
 *		    string str	 - The tellem format string.
 *		    int tell_all - Tell all, or just those seeing fights?
 * Description:     Uses the tellem format for use when one object (attacker)
 *		    does something with another object (victim).
 * Examples:
 *  tellem(find_player("rogon"), find_player("casanova"),
 *	"(You) hew[s] (his) head off with a mighty swing!\n" +
 *	"{"+
 *	   (His) head rolls at the floor as [his] blood gushes and covers\n"+
 *	   "the earth in front of (you).\n" +
 *	";"+
 *	   "You die in a terrible scene of blood as your head is decapitated!\n"+
 *	";*}", 1);
 *
 * Rogon will get:
 *     You hew Casanova's head off with a mighty swing!
 *     Casanova's head rolls at the floor as his blood gushes and covers
 *     the earth in front of you.
 * Casanova will get:
 *     Rogon hews your head off with a mighty swing!
 *     You die in a terrible scene of blood as your head is decapitated!
 * Other will get:
 *     The white-bearded dwarf wizard hews Casanova's head off with a mighty swing!
 *     Casanova's head rolls at the floor as his blood gushes and covers
 *     the earth in front of the white-bearded dwarf wizard.
 * (Assuming that they have met Casanova, but not Rogon, and that
 *  Casanova and Rogon have met.)
 */

varargs void
tellem(object a, object v, string str, int tell_all = 0)
{
    if(tell_all)
	tell_raw(a,v,str,6);
    else
	tell_raw(a,v,str,7);
}

void
Writeln(string str)
{
    Write(TP, str + "\n");
}

varargs void
Tellbb(string str, object target, object tp = TP)
{
    tell_raw(tp, target, str, 6);
}

void
Tellme(string str, object target)
{
    TP->catch_msg(replace_forms(str, this_player(), target));
}
