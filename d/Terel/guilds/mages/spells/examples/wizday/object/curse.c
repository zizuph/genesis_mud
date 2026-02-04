#include "../spells.h"
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

inherit "/std/shadow";
inherit SPELL_OBJECT;

// Global Vars
static int gSpell_active;
static int gPercent;

//  Prototypes
varargs void dispel_spell_effect(object dispeler);

public int
setup_spell_effect()
{
    set_spell_effect_desc("curse");
    if (!::setup_spell_effect())
    {
	remove_spell_effect_object();
	return 0;
    }
    // The spell will take care of the starting messages.
    shadow_me(spell_target);
    set_alarm(itof(180 + random(120)), 0.0, dispel_spell_effect);
    gSpell_active = 1;
    gPercent = spell_caster->query_avatar_level();
    map(spell_target->query_weapon(-1), spell_target->update_weapon);
    return 1;
}

public int
query_skill(int skill)
{
    if (!gSpell_active)
	return shadow_who->query_skill(skill);
    return (100 - gPercent) * shadow_who->query_skill(skill) / 100;
}

varargs int
dispel_spell_effect(object dispeler)
{
    if (objectp(dispeler))
    {
	if (random(dispeler->query_avatar_level()) <
	  random(spell_caster->query_avatar_level()))
	{
	    dispeler->catch_tell("Your attempt to dispel the "+
	      query_spell_effect_desc()+" placed on "+
	      spell_target->query_the_name(dispeler) +" was "+
	      "unsuccessful.\n");
	    return 0;
	}
    }
    spell_target->catch_tell("The wave of despair finally leaves your "+
      "heart and you once again feel confident in your abilities.\n");
    gSpell_active = 0;
    map(spell_target->query_weapon(-1), spell_target->update_weapon);
    remove_spell_effect_object();
    return 1;
}

int
query_avatar_cursed()
{
    return 1;
}
