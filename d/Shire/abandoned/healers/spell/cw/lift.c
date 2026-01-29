#include "defs.h"
#include <filter_funs.h>

inherit SPELL_FILE;

create_spellobj()
{
    set_form(FORM_ABJURATION, 10);
    set_elem(ELEMENT_LIFE, 10);
    set_spell_name("lift");
    set_classes( ([1:7, 5:12, 10:20]) );
    set_desc("Lifts poisons from a living.");
    set_syntax("<poison-type> from <living>");
}

string poison_type;

mixed
pre_parse(string str)
{
    string *words;
    string s1, s2;

    words = explode(str, " ");

    if(words[0]=="poison"||words[1]=="poisons") {
	poison_type = "all";
	return implode(exclude_array(words, 0, 0), " ");
    } else if(words[0]=="all" && words[1]=="poisons") {
	poison_type = "all";
	return implode(exclude_array(words, 0, 1), " ");
    } else
	if(sscanf(str, "%s from %s", s1, s2)==2 ||
	   sscanf(str, "%s upon %s", s1, s2)==2 ||
	   sscanf(str, "%s on %s", s1, s2)==2)
	{
	    poison_type = s1;
	    return s2;
	}
	else
	    return notify_fail("Syntax: Lift <what> from <who>\n");
}


object *
find_targets(string str)
{
    object *targets;
    if(!str)
	return 0;

    targets = parse_livings(str, "[from] [on]", 1);
    if(sizeof(targets)==0) {
	notify_fail("Lift "+poison_type+" from who?\n");
	return ({});
    }
    return targets;
}

void
lift_one(object target, int power)
{
    int i;
    object *inv = all_inventory(target);
    int msg;

    for (i = 0; i < sizeof(inv) && power>0; i++ )
    {
        if (function_exists("cure_poison", inv[i]))
	{
	    inv[i]->cure_poison( ({ poison_type }), power);
	    power /= 2;
        }
    }
}

void
cast_lift(object *target, int res)
{
    int i;
    mixed succ;
    int no;
    string comp_str;

    target = FILTER_CAN_SEE(FILTER_PRESENT_LIVE(target), TP);
    no = sizeof(target);
    if (no==0)
    {
	write("Your spell failed.\n");
	caster->catch_msg(Your spell failed!\n");
	tell_room(ENV(caster),QCTNAME(TP)+"'s spell failed.\n", caster);
	//tellem(caster, 0, "(Your) spell failed.\n");
	return;
    }

    spell_message(caster, target, "Lift Poison", 1);

    if(poison_type == "all")
	res /= 10;

    succ = rnd_dist(no, res);
    for(i=0;i<no;i++)
	lift_one(target[i], succ[i]);
}

void
do_instant_effect(object *targets, int res)
{
    cast_lift(targets, res);
}
