#include "defs.h"

inherit SPELL_FILE;

create_spellobj()
{
    set_form(FORM_ABJURATION, 10);
    set_elem(ELEMENT_LIFE, 10);
	set_spell_name("regeneration");
    set_classes( ([ 1:5, 2:10, 3:15, 5:20, 10:30 ]) );
    set_desc(
	"Makes the target heal continuely over a period of time.");
    set_syntax("on <one living>");
}

int
has_not_regen(object who)
{
    return !present("_regen_obj_", who);
}

object *
area_of_effect(string str)
{
    object *targets;
    if(!str)
	return 0;

    targets = parse_livings(str, "[in] [on] [upon]", 1);

    if (sizeof(targets)==0)
    {
	notify_fail("Regenerate who?\n");
	return ({});
    }

    targets = filter(targets, "has_not_regen", TO);
    notify_fail("Target is already regenerating.\n");
    return targets[0..0];
}    

mixed
cast_regeneration(object *targets, int power)
{
    object reg_ob;
    object target;

    int class = query_prop(SPELL_I_CLASS);
    int strength, time;

    if(!sizeof(targets) || !(target=targets[0]) || !living(target) ||
       !CAN_SEE(caster, target))
    {
	WRITE("Your spell fails due to non-present target.\n");
	return;
    }

    spell_msg(1);

    time = class*60+random(power*120/1000);
    strength = 50*class + random(50*class);

    if (caster == target)
	strength *= 2;


    FIXEUID;

    reg_ob = clone_object(CW_DIR + "regenobj");
    reg_ob -> set_time(time); /* Range 1..1000 -> 1s..5 min */
    reg_ob -> set_interval(10);
    //reg_ob -> set_strength(strength);
	reg_ob -> set_power(strength);
    reg_ob -> move(target);
    reg_ob -> start_regeneration();
}

void
do_instant_effect(object *targets, int res)
{
    cast_regeneration(targets, res);
}
