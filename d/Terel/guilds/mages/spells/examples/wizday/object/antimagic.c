#include "../spells.h"
#include "/d/Khalakhor/sys/defs.h"
#include <stdproperties.h>
#include <language.h>
#include <macros.h>

inherit SPELL_OBJECT;
inherit "/std/shadow";

// Prototypes
varargs void dispel_spell_effect(object dispeler);

public int
setup_spell_effect()
{
    set_spell_effect_desc("orb of negation");
    if (!::setup_spell_effect())
    {
	remove_spell_effect_object();
	return 0;
    }
    shadow_me(spell_target);
    set_alarm(itof(300 + random(450)), 0.0, dispel_spell_effect);
    shadow_who->add_subloc(query_spell_effect_desc, this_object());
    return 1;
}

varargs int
dispel_spell_effect(object dispeler)
{
    if (objectp(dispeler))
    {
	if (random(dispeler->query_avatar_level()) <
	  random(spell_caster->query_avatar_level()))
	{
	    dispeler->catch_tell("Your attempt tp dispel the "+
	      query_spell_effect_desc() + " placed on "+
	      spell_target->query_the_name(dispeler) + " was " +
	      "unsuccessful.\n");
	    return 0;
	}
    }

    spell_target->catch_tell("The orb, which was negating "+
      "your resistances to forms of magic, fades from existance.\n");
    tell_room(environment(spell_target), "The orb which was floating above "+
      QTNAME(spell_target) + " fades from existance.\n", spell_target);

    spell_target->remove_subloc(query_spell_effect_desc);
    remove_spell_effect_object();
    return 1;
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) ||
      subloc != query_spell_effect_desc())
	return shadow_who->show_subloc(subloc, on, for_obj);

    if (for_obj == on)
    {
	return "You have a strange crystal orb floating above you.\n";
    }
    else
    {
	return capitalize(HE_SHE(on))+ " has a strange crystal orb "+
	"floating above "+HIM_HER(on)+".\n";
    }
}

// This shadow negates all magic resistance on a target.
int
query_magic_res(string prop)
{
    return 0;
}

int
query_avatar_antimagic()
{
    return 1;
}
