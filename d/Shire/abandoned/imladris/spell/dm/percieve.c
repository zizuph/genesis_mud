#include "defs.h"

inherit SPELL_FILE;

create_spellobj()
{
    set_form(FORM_DIVINATION,	    10);
    set_elem(ELEMENT_LIFE,	    10);
    add_prop(SPELL_S_NAME,	    "percieve power");
    add_prop(SPELL_M_CLASSES,	    ([1:12]) );
    add_prop(SPELL_S_DESC,
	"Make you understand the powers of a living beings.");
    add_prop(SPELL_S_SYNTAX, "on <who>");
}

object *
area_of_effect(string str)
{
    return parse_one_living(str, "[on] [in]", 1);
}

string health_rank(object who)
{
    switch(HP(who)*100/MAX_HP(who)) {
	case 0..9: return "is holding on to life by a thread";
	case 10..19: return "has the glazed look of death in "+HIS_HER(who)+"eyes";
	case 20..29: return "won't last much longer";
	case 30..39: return "is bleeding profusely";
	case 40..49: return "is bleeding quite a bit";
	case 50..59: return "is quite sure "+HE_SHE(who)+" won't survive";
	case 60..69: return "is having serious doubts about surviving";
	case 70..79: return "looks very worried";
	case 80..89: return "looks worried";
	case 90..99: return "looks slightly worried";
	case 100: return "is at full health";
    }
}

string
desc_stats(object who)
{
    string *stat_str = ({ "strength", "dexterity", "constitution",
			  "intelligence", "wisdom", "discipline" });
    int i;
    string ret = "When percieving " + LANG_POSS(QTNAME(who)) + " statistics, comparing with\n"
	       + "your statistics, you understand that " + HIS_HER(who) + " : \n";

    for (i=0; i<6; i++)
	ret += sprintf("  * %s is %s of yours\n",
		   stat_str[i], ratio_str(who->query_stat(i), caster->query_stat(i)));

    return ret;
}

mixed
cast_percieve_power(object *targets, int res)
{
    object ob = targets[0];

    string str = "The name of the "+ob->query_race_name()+" is ";

    if(ob->query_real_name() && !ob->query_prop(LIVE_I_NEVERKNOWN))
    {
	str += CAP(ob->query_real_name())+". ";
	TP->add_introduced(ob->query_real_name());
    }
    else
	str += "not known. ";

    if(ob==TP) {
	if(MAX_HP(TP)==HP(TP))
	    str += "You are completely healed.\n";
	else
	    str += "You are hurt. You have "+
		   "about "+ratio_str(HP(TP), MAX_HP(TP))+
		   " of your health left.\n";
    } else {
	str += CAP(HIS_HER(ob))+" health is about "+ratio_str(MAX_HP(ob),MAX_HP(TP));
	str += " of your health, and "+health_rank(ob)+".\n";
	str += "\n" + desc_stats(ob) + "\n";
	ob->catch_msg("You didn't feel or see anything special though.\n");
    }

    TP->catch_msg(str);
}

void
do_instant_effect(object *targets, int res)
{
    string retval;

    spell_msg(1);

    retval = cast_percieve_power(targets, res);
    if(stringp(retval))
	write(retval);
}
