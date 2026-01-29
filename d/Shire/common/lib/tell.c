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
			    The odd dwarf is devastated by your spell (nonmet)
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

	    {You feel a terrible pain!;(You) looks terrible}

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
#include "/d/Shire/common/defs.h"

#define BRACK "["
#define ENDBRACK "]"
#define BRACE "{"
#define DELIM ";"
#define ENDBRACE "}"

/*
#define QRACE(ob)   ob->query_race_name()
*/
#define VBFC1(fun, ob) "@@"+fun+":"+file_name(this_object)+"|"+file_name(ob)+"@@"

#define DESC_OTHER  1

inherit "/d/Shire/common/lib/stringfuns";

#define SYNTAX \
	    ({	"(You)", "(you)", "[Your]", "[your]",			 \
		"(Yourself)", "(yourself)",				 \
		"(Your)", "(your)", "[You]", "[you]",			 \
		"(are)", "(is)", "(s)", "[s]", "(es)", "[es]",		 \
		"(y)", "(ies)", 					 \
		"(Him)", "(him)", "[Him]", "[him]", "(himself)",	 \
		"(He)", "(he)", "[He]", "[he]", 			 \
		"[His]", "[his]", "(His)", "(his)"			 \
	    })

string
tell_me_one(string part, object me, object target)
{
    string tname = target->query_the_name(me);
    string Tname = target->query_The_name(me);
    part = replace_strings(part,
	    SYNTAX,
	    ({ "You", "you", "Your", "your", "Yourself", "yourself",
	       "Your", "your", "You", "you",
	       "are", "is", "s", "", "es", "", "y", "ies",
	       Tname, tname, CAP(HIM_HER(target)), HIM_HER(target), HIM_HER(target)+"self",
	       Tname, tname, CAP(HE_SHE(target)), HE_SHE(target),
	       CAP(HIS_HER(target)), HIS_HER(target),
	       LANG_POSS(Tname), LANG_POSS(tname)
	    })
	    );

    return part;
}

string
tell_me_me(string part, object me)
{
   return replace_strings(part, SYNTAX,
	    ({ "You", "you", "Your", "your", "Yourself", "yourself",
	       "Your", "your", "You", "you",
	       "are", "are", "", "", "", "", "y", "ies",
	       "Yourself", "yourself", "Yourself", "yourself", "yourself",
	       "You", "you", "You", "you",
	       "Your", "your", "Your", "your"
	    }));
}

string
tell_target_one(string part, object me, object target)
{
    string name = me->query_the_name(target);
    string Name = me->query_The_name(target);

    part = replace_strings(part,
	    SYNTAX,
	    ({ Name, name, CAP(HIS_HER(me)), HIS_HER(me),
	       CAP(HIM_HER(me))+"self", HIM_HER(me)+"self",
	       LANG_POSS(Name), LANG_POSS(name), CAP(HE_SHE(me)), HE_SHE(me),
	       "is", "are", "", "s", "", "es", "ies", "y",
	       "You", "you", "You", "you", "yourself",
	       "You", "you", "You", "you",
	       "Your", "your", "Your", "your"
	    }));
    return part;
}

string
tell_rest_one(string part, object me, object target, object watcher)
{
    string mname = me->query_the_name(watcher);
    string Mname = me->query_The_name(watcher);
    string tname = target->query_the_name(watcher);
    string Tname = target->query_The_name(watcher);

    part = replace_strings(part,
	    SYNTAX,
	    ({ Mname, mname, CAP(HIS_HER(me)), HIS_HER(me),
	       CAP(HIM_HER(me))+"self", HIM_HER(me)+"self",
	       LANG_POSS(Mname), LANG_POSS(mname), CAP(HE_SHE(me)), HE_SHE(me),
	       "is", "is", "s", "s", "es", "es", "ies", "ies",
	       Tname, tname, CAP(HIM_HER(target)), HIM_HER(target), HIM_HER(target)+"self",
	       CAP(HE_SHE(target)), HE_SHE(target), Tname, tname,
	       CAP(HIS_HER(target)), HIS_HER(target),
	       LANG_POSS(Tname), LANG_POSS(tname)
	    }));
    return part;
}

string
tell_rest_me(string part, object me, object watcher)
{
    string mname = me->query_the_name(watcher);
    string Mname = me->query_The_name(watcher);

    return replace_strings(part, SYNTAX,
	    ({ Mname, mname, CAP(HIS_HER(me)), HIS_HER(me),
	       CAP(HIM_HER(me))+"self", HIM_HER(me)+"self",
	       LANG_POSS(Mname), LANG_POSS(mname), CAP(HE_SHE(me)), HE_SHE(me),
	       "is", "is", "s", "s", "es", "es", "ies", "ies",
	       Mname, mname, CAP(HIM_HER(me))+"self", HIM_HER(me)+"self", HIM_HER(me)+"self",
	       Mname, mname, CAP(HE_SHE(me)), HE_SHE(me),
	       CAP(HIS_HER(me)), HIS_HER(me),
	       LANG_POSS(Mname), LANG_POSS(mname)
	    }));
}

string *
split_braces(string str)
{
    string *brk = ({ "", "", "" });
    string *p = ({ "", "", "" });
    int ind;
    string part, left;

    ind = index(str, BRACE);
    if(ind==-1)
	return ({ str, str, str });

    left = str;
    while(ind!=-1)
    {
	if(ind>0)
	{
	    brk[0] += str_to(left, ind);
	    brk[1] += str_to(left, ind);
	    brk[2] += str_to(left, ind);
	}

	left = str_from(left, ind);
	ind = index(left, ENDBRACE);
	part = str_to(left, ind);

	if(sscanf(part, "%s"+DELIM+"%s"+DELIM+"%s", p[0], p[1], p[2])==3)
	{
	    brk[0] += p[0];
	    brk[1] += p[1];
	    brk[2] += (p[2]=="*"?p[0]:p[2]);
	}
	else if(sscanf(part, "%s"+DELIM+"%s", p[0], p[1])==2)
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
void
tell_raw(object tp, object target, string str, int tell_bits = 1)
{
    object *watchers = FILTER_LIVE(all_inventory(ENV(tp)));
    string *split;
    int i;

    watchers -= ({ tp, target });

    if(tell_bits & 1)
	watchers = filter(watchers, "sees_fight", this_object());
    if(tell_bits & 2)
	watchers = FILTER_CAN_SEE(watchers, tp);
    if(tell_bits & 4 && living(target))
	watchers = FILTER_CAN_SEE(watchers, target);

    split = split_braces(str);

    if(target==0)
    {
	tp->catch_msg(tell_me_one(split[0], tp, target));
	for(i=0;i<sizeof(watchers);i++)
	    watchers[i]->catch_msg(tell_rest_one(split[2], tp, target, watchers[i]));
    }
    else if(tp==target)
    {
	tp->catch_msg(tell_me_me(split[1], tp));
	for(i=0;i<sizeof(watchers);i++)
	    watchers[i]->catch_msg(tell_rest_me(split[2], tp, watchers[i]));
    }
    else
    {
	tp->catch_msg(tell_me_one(split[0], tp, target));
	target->catch_msg(tell_target_one(split[1], tp, target));
	for(i=0;i<sizeof(watchers);i++)
	    watchers[i]->catch_msg(tell_rest_one(split[2], tp, target, watchers[i]));
    }
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
    tell_raw(subj, obj, format, 2);
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

tellem(object a, object v, string str, int tell_all)
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
    TP->catch_msg(tell_me_one(str, this_player(), target));
}
