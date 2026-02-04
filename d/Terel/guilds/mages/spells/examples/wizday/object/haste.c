#include "../spells.h"
#include "/d/Khalakhor/sys/defs.h"
#include <stdproperties.h>
#include <language.h>
#include <macros.h>

inherit SPELL_OBJECT;

// Prototypes
varargs void dispel_spell_effect(object dispeler);

public int
setup_spell_effect()
{
    set_spell_effect_desc("hasted reflexes");
    if (!::setup_spell_effect())
    {
	remove_spell_effect_object();
	return 0;
    }
    spell_target->add_prop(LIVE_I_QUICKNESS, 
      (int)spell_target->query_prop(LIVE_I_QUICKNESS) + 150);
    spell_target->query_combat_object()->cb_update_speed();
    spell_target->add_subloc(query_spell_effect_desc(), this_object());
    set_alarm(itof(300 + random(300)), 0.0, dispel_spell_effect);
    return 1;
}


varargs void
dispel_spell_effect(object dispeler)
{
    if (objectp(dispeler))
    {
	if (random(dispeler->query_avatar_level()) <
	  random(spell_caster->query_avatar_level()))
	{
	    dispeler->catch_tell("Your attempt to dispel the "+
	      query_spell_effect_desc()+" placed on "+
	      spell_target->query_the_name(dispeler) + " was "+
	      "unsuccessful.\n");
	    return;
	}
    }
    spell_target->catch_tell("You feel your reflexes slowing, to an "+
      "almost sluggish pace.\n");
    spell_target->add_prop(LIVE_I_QUICKNESS, 
      (int)spell_target->query_prop(LIVE_I_QUICKNESS) - 150);
    spell_target->query_combat_object()->cb_update_speed();
    spell_target->remove_subloc(query_spell_effect_desc());
    remove_spell_effect_object();
    return;
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) ||
      for_obj == on || subloc != query_spell_effect_desc())
	return "";

    return capitalize(HE_SHE(on)) + " seems to moving with an "+
    "unnatural quickness.\n";
}
