#include "../spells.h"
#include <stdproperties.h>

inherit SPELL_OBJECT;

//  Prototypes
varargs void dispell_spell_effect(object dispeller);

public int
start()
{
    set_spell_effect_desc("darkness");
    if (!::start())
    {
	remove_spell_effect_object();
	return 0;
    }

    spell_target->add_prop(ROOM_I_LIGHT,
    spell_target->query_prop(ROOM_I_LIGHT) - 11);
    
    spell_target->update_light(1);
    spell_target->add_my_desc("A mist of darkness absorbs all light from the area.\n");
    spell_target->add_item(({"mist", "darkness"}),
      "The mist of darkness absorbs all traces of light. Its depth is undeterminable.\n");
    set_alarm(10.0, 0.0, dispell_spell_effect);
    return 1;
}

varargs int
dispell_spell_effect(object dispeller)
{
    spell_target->add_prop(ROOM_I_LIGHT,
      spell_target->query_prop(ROOM_I_LIGHT) + 11);
    spell_target->update_light(1);
    tell_room(spell_target, "You feel relieved as the mist of darkness slowly dissipates.\n");
    spell_target->remove_my_desc();
    spell_target->remove_item("mist");
    spell_target->remove_item("darkness");
    remove_spell_effect_object();
    return 1;
}
