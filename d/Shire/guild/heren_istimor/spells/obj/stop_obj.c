#include "../spells.h"

inherit SPELL_OBJECT;

//    Prototypes
varargs int dispell_spell_effect(object dispeller);

static int destruct_id;
static int no_m_att, no_att;

int
start()
{
    object *objs;
    int i, time;

    set_spell_effect_desc("orome peace");
    if (!::start())
    {
	remove_spell_effect_object();
	return 0;
    }

    objs = all_inventory(environment(spell_caster));
    objs = filter(objs, living);
    /* Make 'em all stop */
    i = -1;
    while (++i < sizeof(objs))
	objs[i]->stop_fight(objs - ({objs[i]}));

    no_att = spell_target->query_prop(ROOM_I_NO_ATTACK);
    no_m_att = spell_target->query_prop(ROOM_I_NO_MAGIC_ATTACK);
    spell_target->add_prop(ROOM_I_NO_ATTACK, 1);
    spell_target->add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
    time = spell_power * 10 / 4;
    destruct_id = set_alarm(itof(time),0.0, dispell_spell_effect);
    return 1;
}


varargs int
dispell_spell_effect(object dispeller)
{
    spell_target->add_prop(ROOM_I_NO_ATTACK, no_att);
    spell_target->add_prop(ROOM_I_NO_MAGIC_ATTACK, no_m_att);
    tell_room(spell_target, "The solemn mood in the room has "+
      "disappeared.  The air of peace and tranquility is gone.\n");
    remove_spell_effect_object();
    return 1;
}
