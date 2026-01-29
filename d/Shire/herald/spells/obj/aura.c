/*
 *  The light object of the Heralds of the Valar
 *  Modified from the candle.c
 *  by Sir Denbarra of Gondor
 *  7 May 1995
 *
 *  Modified and updated for the new Spellcasting system
 *  By Igneous Feb 1998
 */

#include "../spells.h"

inherit "/std/object";
inherit SPELL_OBJECT;

#define SUBLOC "_herald_light_aura_subloc"

//  Prototypes
varargs void dispell_spell_effect(object dispeller);

void
create_object() 
{
    set_name("aura");
    add_name("_herald_aura_");
    set_adj("light");
    set_no_show();

    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_M_NO_INS,  1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "This is the radiant aura of the Heralds of " +
      "the Valar guild, summoned to provide light.");
}

public int
start()
{
    int time, light;
    set_spell_effect_desc("light aura");
    if (!::start())
    {
	remove_spell_effect_object();
	return 0;
    }

    light = MAX(4, MIN(2, spell_power / 20));
    time = MAX(600, (spell_power * 10) + random(150));

    add_prop(OBJ_I_LIGHT, light);
    set_alarm(itof(time), 0.0, dispell_spell_effect);
    move(spell_target, 1);
    spell_target->add_subloc(SUBLOC, this_object());
    return 1;
}

varargs int
dispell_spell_effect(object dispeller)
{
    spell_target->catch_tell("Your radiant aura fades and disappears.\n");
    tell_room(environment(spell_target), "The radiant aura surrounding " + 
      QTNAME(spell_target) +" fades and vanishes.\n", spell_target);
    spell_caster->remove_subloc(SUBLOC);
    remove_prop(OBJ_I_LIGHT);
    remove_spell_effect_object();
    return 1;
}

string
show_subloc(string subloc, object on, object for_obj)
{
    string  str;

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) ||
      subloc != SUBLOC)
	return "";

    if (for_obj == on)
	str = "your";
    else
	str = on->query_possessive();

    str = "Outlining "+str+" body is a glowing, radiant aura.\n";

    return str;
}
