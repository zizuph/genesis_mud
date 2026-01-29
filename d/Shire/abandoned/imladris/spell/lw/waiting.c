/*
 * Waiting Light.
 *  As Light I, except caster can delay the spell up to
 *  24 hours. It can be triggered by one of the following
 *  (decided by the caster):
 *    - time period
 *    - certain movements
 *    - certain sounds
 *    - touch
 *    - etc.
 *
 * Implementation.
 *  I will use a shadow on the object which triggers a light I spell.
 *  I believe I will have to clone an invisible living object which
 *  always attaches to this object.
 *
 * If target is an object:
 *  - Shadow the object.
 *  - If a living object is needed, the shadow must clone it,
 *    so that if the shadow moves, the object will go along with it.
 *  - The living object must trig on the correct triggers.
 *
 * If target is a room:
 *  - Shadow the room.
 *  - The shadow must place an invisible teller in the room.
 *
 * If target is a living:
 *  - Shadow the living
 *  - Mask the catch_msg function.
 *
 */

#include "defs.h"

inherit SPELL_FILE;
inherit PARSE_FILE;
inherit TELL_FILE;

create_spellobj()
{
    set_spell_name("waiting light");
    set_form(FORM_CONJURATION, 10);
    set_elem(ELEMENT_FIRE, 10);

    add_prop(SPELL_M_CLASSES,	    ([1:10]) );
    add_prop(SPELL_S_DESC,
	"As Light I, except the caster can delay the spell up to "+
	"24 hours. It can be triggered by one of the following "+
	"(decided by the caster):\n"+
	" - time period\n"+
	" - certain movements\n"+
	" - certain sounds\n"+
	" - touch\n"
    );
    add_prop(SPELL_S_SYNTAX,
	"(on <object> | here) triggering \n"+
	"(after <time period> | on movement | on sound <sound> | on touch)");
}

string type;
int time;

mixed
area_of_effect(string str)
{
    object *targets;
    string place;
    string s1, s2, ts;

    notify_fail("What do you want to cast a Waiting Light on?\n"+query_syntax());

    if (!strlen(str))
	return ({});

    if (sscanf(str, "%s triggering %s", s1, s2)==2)
	return ({});

    if (sscanf(s2, "after %s", ts)==1)
    {
	time = get_time(ts);
	if (!time)
	    return notify_fail("Sorry, could not parse your time period.\n");
    }

    if (sizeof(targets = parse_items(s1)))
    {
	add_prop(SPELL_O_EFFECT, LW_DIR + "waitshd");
	type = "_object";
	return ({ targets[0] });
    }
    if (sizeof(targets = parse_livings(s1, "[on]")))
    {
	add_prop(SPELL_O_EFFECT, LW_DIR + "waitshd");
	type = "_living";
	return ({ targets[0] });
    }
    if (strlen(place = parse_place_in_room(s1)))
    {
	add_prop(SPELL_O_EFFECT, LW_DIR + "waitshd");
	type = place;
	return ({ EP });
    }
    return ({});
}

mixed
cast_waiting_light(object *targets, int res)
{
    object ob = targets[0];
    object light;

    if(type=="_object")
	action("$You $cast a {Waiting Light spell;spell} on "+ob->short()+".\n");
    else if(type=="_living")
	TellRoom(TP, ob, "$You $cast a {Waiting Light spell;spell} on #n.\n");
    else
    {
	caster->catch_msg("You cast a Waiting Light spell "+type+".\n");
	tell_room(ENV(caster),
	    QCTNAME(TP)+" casts a spell "+type+".\n", caster);
    }
    return 1;
}

void
do_instant_effect(object *targets, int res)
{
    string retval;

    retval = cast_waiting_light(targets, res);
    if(stringp(retval))
	write(retval);
}
