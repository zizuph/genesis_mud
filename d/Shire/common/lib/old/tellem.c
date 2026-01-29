/*
 * The redefined, easy to use and much faster tellem()-routine!!
 *
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

#define QRACE(ob)   ob->query_race_name()
#define VBFC1(fun, ob) "@@"+fun+":"+file_name(this_object)+"|"+file_name(ob)+"@@"

#define DESC_OTHER  1

inherit "/d/Shire/common/lib/stringfuns";


string
tell_me_one(string part, object me, object target)
{
    part = replace_strings(part,
	    ({ "[You]", "[you]", "[Your]", "[your]", "[Yourself]", "[yourself]",
	       "[Your's]", "[your's]", "[i]", "[you*]", "[yhe]", "[I]",
	       "[are]", "[is]", "[s]", "[*s]", "[es]", "[*es]" }),
	    ({ "You", "you", "Your", "your", "Yourself", "yourself",
	       "Your", "your", "you", "you", "you", "You",
	       "are", "is", "s", "", "es", "" })
	    );

    part = replace_string(part, "[oth]",     target->query_the_name(me));
    part = replace_string(part, "[Oth]",     target->query_The_name(me));
    part = replace_string(part, "[him]",     HIM_HER(target));
    part = replace_string(part, "[Him]",     CAP(HIM_HER(target)));
    part = replace_string(part, "[himself]", HIM_HER(target)+"self");
    part = replace_string(part, "[he]",      HE_SHE(target));
    part = replace_string(part, "[He]",      CAP(HE_SHE(target)));
    part = replace_string(part, "[his]",     HIS_HER(target));
    part = replace_string(part, "[His]",     CAP(HIS_HER(target)));
    part = replace_string(part, "[oth's]",   LANG_POSS(target->query_the_name(me)));
    part = replace_string(part, "[Oth's]",   LANG_POSS(target->query_The_name(me)));

    return part;
}

string
tell_target_one(string part, object me, object target)
{
    string name = me->query_the_name(target);

    part = replace_strings(part,
	    ({ "[You]", "[you]", "[Your]", "[your]",
	       "[Yourself]", "[yourself]",
	       "[Your's]", "[your's]", "[i]", "[you*]", "[yhe]", "[I]",
	       "[are]", "[is]", "[s]", "[*s]", "[es]", "[*es]",
	       "[Oth]", "[oth]", "[Him]", "[him]", "[himself]",
	       "[He]", "[he]", "[His]", "[his]", "[Oth's]", "[oth's]"
	    }),
	    ({ CAP(name), name, CAP(HIS_HER(me)), HIS_HER(me),
	       CAP(HIM_HER(me))+"self", HIM_HER(me)+"self",
	       LANG_POSS(CAP(name)), LANG_POSS(name), HE_SHE(me), HE_SHE(me), HE_SHE(me), CAP(HE_SHE(me)),
	       "is", "are", "", "s", "", "es",
	       "You", "you", "You", "you", "yourself",
	       "You", "you", "Your", "your", "Your", "your"
	    }));
    return part;
}

string
tell_rest_one(string part, object me, object target, object watcher)
{
    string mname = me->query_the_name(watcher);
    string tname = target->query_the_name(watcher);

    part = replace_strings(part,
	    ({ "[You]", "[you]", "[Your]", "[your]",
	       "[Yourself]", "[yourself]",
	       "[Your's]", "[your's]", "[i]", "[you*]", "[yhe]", "[I]",
	       "[are]", "[is]", "[s]", "[*s]", "[es]", "[*es]",
	       "[Oth]", "[oth]", "[Him]", "[him]", "[himself]",
	       "[He]", "[he]", "[His]", "[his]", "[Oth's]", "[oth's]"
	    }),
	    ({ CAP(mname), mname, CAP(HIS_HER(me)), HIS_HER(me),
	       CAP(HIM_HER(me))+"self", HIM_HER(me)+"self",
	       LANG_POSS(CAP(mname)), LANG_POSS(mname), HE_SHE(me), HE_SHE(me), HE_SHE(me), CAP(HE_SHE(me)),
	       "is", "is", "s", "s", "es", "es",
	       CAP(tname), tname, CAP(HIM_HER(target)), HIM_HER(target), HIM_HER(target)+"self",
	       CAP(HE_SHE(target)), HE_SHE(target), CAP(HIS_HER(target)), HIS_HER(target),
	       LANG_POSS(CAP(tname)), LANG_POSS(tname)
	    }));
    return part;
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
    if(tell_bits & 4)
	watchers = FILTER_CAN_SEE(watchers, target);

    split = split_braces(str);

    if(tp==target)
    {
	tp->catch_msg(tell_me_one(split[0], tp, target));
	for(i=0;i<sizeof(watchers);i++)
	    watchers[i]->catch_msg(tell_rest_one(split[2], tp, target, watchers[i]));
    }
    else
    {
	tp->catch_msg(tell_me_one(split[0], tp, target));
	target->catch_msg(tell_target_one(split[1], tp, target));
	for(i=0;i<sizeof(watchers);i++)
	    watchers[i]->catch_msg(tell_rest_one(split[2], tp, target, watchers[i]));
    }
}

void
TellRoom(object a, object v, string str)
{
    tell_raw(a,v,str,2);
}

void
Tell(object a, object v, string str)
{
    tell_raw(a,v,str,7);
}

tellem(object a, object v, string str, int tell_all)
{
    if(tell_all)
	tell_raw(a,v,str,6);
    else
	tell_raw(a,v,str,7);
}
