#include "defs.h"

inherit SPELL_FILE;

create_spellobj()
{
    set_form(FORM_CONJURATION, 10);
    set_elem(ELEMENT_FIRE, 10);
    set_spell_name("light");
    set_classes( ([1:2, 2:4, 3:8, 5:13, 10:15]) );
    set_desc(
	"Lights an object or an area. If the object moves, the light will follow it."
    );
    set_syntax("on <object> | on <living> | here");
}

string type;

object *
area_of_effect(string str)
{
    object *targets;
    string place;

    notify_fail("What do you want to cast light on?\n"+query_syntax());

    if (!strlen(str))
	return ({});

	if (sizeof(targets = parse_one_living(str, "[on]", 1, 1)))
    {
	add_prop(SPELL_O_EFFECT, LW_DIR + "lightobj");
	type = "_living";
	return ({ targets[0] });
    }


    if (sizeof(targets = parse_items(str, "[on]", 1)))
    {
	add_prop(SPELL_O_EFFECT, LW_DIR + "lightshd");
	type = "_object";
	return ({ targets[0] });
    }

    if (strlen(place = parse_place_in_room(str, 0)))
    {
	add_prop(SPELL_O_EFFECT, LW_DIR + "lightrom");
	type = place;
	return ({ EP });
    }
    return ({});
}

mixed
cast_light(object *targets, int res)
{
    object ob = targets[0];
    object light;

    if(type=="_object")
	spell_message(caster, targets, "Light spell", 1);
    else if(type=="_living")
	spell_message(caster, targets, "Light spell", 1);
    else
    {
	caster->catch_msg("You cast a Light spell on "+type+".\n");
	tell_room(ENV(caster),
	    QCTNAME(TP)+" casts a spell on "+type+".\n", caster);
    }
    return 1;
}

void
do_instant_effect(object *targets, int res)
{
    string retval;

    retval = cast_light(targets, res);
    if(stringp(retval))
	write(retval);
}
