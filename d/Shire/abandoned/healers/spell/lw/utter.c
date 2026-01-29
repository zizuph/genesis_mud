/*
 * Utterlight
 *  As Light I, except it is equivalent of full daylight.
 *  It also cancels all magically created darkness.
 *  [Force spell. Duration: 1 min/lvl. Range: Touch.]
 *  Note: A class V/X spell will take 1/10 adjacent rooms
 *	  as well.
 *
 * Implementation.
 *  I will make this only a room spell. This will shadow the
 *  room and will always give the room a positive (10)
 *  return on query_prop(OBJ/ROOM_I_LIGHT).
 *
 *  Later I will perhaps think of how to implement this on
 *  things. Perhaps things should shadow the room as they go?
 */

#include "defs.h"

inherit SPELL_FILE;
inherit H_LIB_DIR + "getrooms";

create_spellobj()
{
    set_spell_name("utterlight");
    set_classes( ([1:9, 2:17, 5:27, 10:30 ]) );
    set_form(FORM_CONJURATION, 10);
    set_elem(ELEMENT_FIRE, 10);
    set_desc(
	"Cast a Light spell which cancels all darkness in an area "+
	"of equal depth as the spell class around you."
    );
    set_syntax("here");
    add_prop(SPELL_O_EFFECT, LW_DIR + "uttershd");
}

string type;

int
ok_room(object which)
{
    return which->query_prop(ROOM_I_IS) &&
	!(which->query_prop(ROOM_M_NO_MAGIC));
}

int
in_range(object room)
{
    return room->query_prop(ROOM_I_IS);
}

object *
area_of_effect(string str)
{
    object *targets;

    if(!strlen(str))
	type = "here";
    else
	type = str;
    if(query_spell_class()==1)
	targets = ({ ENV(caster) });
    else
	targets = get_rooms(ENV(caster), query_spell_class());
    return filter(targets, "ok_room", TO);
}
				

mixed
cast_utterlight(object *targets, int res)
{
    object ob = targets[0];
    object light;

	spell_message(caster, targets, "Utter Light", 1);

    caster->catch_msg("You cast a Utterlight spell "+type+".\n");
    tell_room(ENV(caster),
	      QCTNAME(TP)+" casts a spell "+type+".\n", caster);
    return 1;
}

void
do_instant_effect(object *targets, int res)
{
    string retval;

    retval = cast_utterlight(targets, res);
    if (stringp(retval))
	write(retval);
}

	
