#include "../spells.h"
#include <stdproperties.h>

inherit SPELL_OBJECT;

//  Prototypes
varargs void dispell_spell_effect(object dispeller);

public int
start()
{
    set_spell_effect_desc("sunbrust orb");
    if (!::start())
    {
	remove_spell_effect_object();
	return 0;
    }

    spell_target->add_prop(ROOM_I_LIGHT,
      spell_target->query_prop(ROOM_I_LIGHT) + 10);
    spell_target->add_prop("_room_i_sunlight",
      spell_target->query_prop("_room_i_sunlight") + 50);
    spell_target->update_light(1);
    spell_target->add_my_desc("A blazing fireball illuminates the area.\n");
    spell_target->add_item(({"fireball", "blazing fireball"}),
      "A blazing orb of fire nearly blinds you with its light as you "+
      "look upon it.\n");
    set_alarm(900.0, 0.0, dispell_spell_effect);
    return 1;
}

varargs int
dispell_spell_effect(object dispeller)
{
    spell_target->add_prop("_room_i_sunlight", 
      spell_target->query_prop("_room_i_sunlight") - 50);
    spell_target->add_prop(ROOM_I_LIGHT,
      spell_target->query_prop(ROOM_I_LIGHT) - 10);
    spell_target->update_light(1);
    tell_room(spell_target, "The blazing ball of fire suddenly fizzles out "+
      "and dies, leaving no trace of itself behind.\n");
    spell_target->remove_my_desc();
    spell_target->remove_item("fireball");
    spell_target->remove_item("blazing fireball");
    remove_spell_effect_object();
    return 1;
}
