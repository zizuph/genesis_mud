#include "defs.h"

inherit SPELL_FILE;

create_spellobj()
{
    set_form(FORM_DIVINATION, 10);
    set_elem(ELEMENT_LIFE, 10);
    set_spell_name("detect alignment");
    set_classes( ([1:6]) );
    set_desc(
	"Tells the alignment of any being.");
    set_syntax("in <what>");
}

object *
area_of_effect(string str)
{
    object *who;
    notify_fail(CAP(query_prop(SPELL_S_NAME)) + " in who?\n"+query_syntax());
    if (!str)
	return ({ caster });
    return parse_one_living(str, "'in'", 1);
}

string
abs_good_evil(object who)
{
    int al = who->query_alignment();

    if (al>=0)
	return "good";
    else
	return "evil";
}

string
good_evil(object who)
{
    int al = who->query_alignment();

    if (al>=200)
	return "good";
    else if (al>-200)
	return "neutral";
    else
	return "evil";
}

void
do_instant_effect(object *obs, int res)
{
    object ob = obs[0];
    int al = ob->query_alignment();
    string at = good_evil(ob);
    string str;

    if (ob==caster)
    {
	write("You are "+at+" and your aura is "+TP->query_align_text()+".\n");
	return;
    }

    str = QCTNAME(ob) + " is of " + LANG_ADDART(at) + " alignment.\n"
	+ CAP(HE_SHE(ob)) + " is " + ratio_str(ABS(al), ABS(caster->query_alignment()));

    at = abs_good_evil(ob);

    if (at != abs_good_evil(caster))
	str += " times as " + at + " as you are " + abs_good_evil(caster) + ".\n";
    else
	str += " times as " + at + " as you.\n";

    caster->catch_msg(str +
	CAP(HIS_HER(ob))+" aura is "+ob->query_align_text()+".\n");
}
