#include "defs.h"

inherit SPELL_FILE;

create_spellobj()
{
    set_form(FORM_ABJURATION, 10);
    set_elem(ELEMENT_LIFE, 10);
    set_spell_name("ease");

    add_prop(SPELL_M_CLASSES, ([1:1, 2:3, 5:6, 10:9 ]));

    set_desc("The targets fatigue is lowered, thereby easing his burdens.");
    set_syntax("[on] <living>");
}

object *
area_of_effect(string str)
{
    object *targets;
    if(!str)
	return 0;

    targets = parse_livings(str, "[on]", 1);

    if (!sizeof(targets)) {
	notify_fail("Ease who?\n");
	return ({});
    }
    return targets[0..0];
}

mixed
cast_ease(object *targets, int power)
{
    int i;
    object ob=targets[0];

    if (caster!=ob && !CAN_SEE(caster, ob))
    {
	write("The spell fails, as you fail to see the target of your spell.\n");
	return;
    }

    if (caster==ob)
    {
	caster->catch_msg("Your tired muscles recieve ease.\n");
	tell_room(ENV(caster),
	    QCTNAME(caster)+" casts a spell on "+HIM_HER(caster)+"self.\n", caster);
    }
    else
    {
	caster->catch_msg("You ease "+QTNAME(ob)+"'s tired muscles.\n");
	ob->catch_msg(QCTNAME(caster)+" touches you easing your tired muscles.\n");
	tell_room(ENV(caster),
	    QCTNAME(caster)+" touches "+QTNAME(ob)+
	    " easing "+HIS_HER(ob)+" tired muscles.\n", ({caster, ob}));
    }

    if (query_spell_class() == 10)
	ob->set_fatigue(ob->query_max_fatigue());
    else
	ob->add_fatigue(power+1); /* <class>d10 */
    return 1;
}

void
do_instant_effect(object *targets, int power)
{
    string retval;
    retval = cast_ease(targets, power);
    if(stringp(retval))
	write(retval);
}
