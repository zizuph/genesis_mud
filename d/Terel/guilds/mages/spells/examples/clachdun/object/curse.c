#include "../spells.h"
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

inherit "/std/shadow";
inherit SPELL_OBJECT;

// Global Vars
static int gSpell_active;

//  Prototypes
varargs void dispell_spell_effect(object dispeller);

public int
start()
{
    set_spell_effect_desc("curse");
    if (!::start())
    {
	remove_spell_effect_object();
	return 0;
    }
    // The spell will take care of the starting messages.
    shadow_me(spell_target);
    set_alarm(itof(120 + random(120)), 0.0, dispell_spell_effect);
    gSpell_active = 1;
    map(spell_target->query_weapon(-1), spell_target->update_weapon);
    return 1;
}

int
second_life(object killer)
{
    set_alarm(0.0,0.0,remove_shadow);
    return shadow_who->second_life(killer);
}

public int
query_skill(int skill)
{
    if (!gSpell_active)
	return shadow_who->query_skill(skill);
    return shadow_who->query_skill(skill) / 2;
}

varargs int
dispell_spell_effect(object dispeller)
{
    spell_target->catch_tell("The wave of despair finally leaves your "+
      "heart and you once again feel confident in your abilities.\n");
    gSpell_active = 0;
    map(spell_target->query_weapon(-1), spell_target->update_weapon);
    destruct();
    return 1;
}

int
query_clachdun_cursed()
{
    return 1;
}
