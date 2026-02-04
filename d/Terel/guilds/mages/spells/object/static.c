#include "../spells.h"
#include "/d/Terel/include/Terel.h"
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
    set_spell_effect_desc("static charge");
    if (!::setup_spell_effect())
    {
	remove_spell_effect_object();
	return 0;
    }
    shadow_me(spell_target);
    set_alarm(itof(300 + random(450)), 0.0, dispel_spell_effect);
    shadow_who->add_subloc(query_spell_effect_desc, this_object());
    shadow_who->add_prop(LIVE_S_EXTRA_SHORT,  " is covered in a sparkling static field.\n");
    return 1;
}

varargs int
dispel_spell_effect(object dispeler)
{
    /*
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
   */
    
    spell_target->catch_tell("The static charge, which which surrounds you. "+
			      "fizzles then fades away.\n");
    tell_room(environment(spell_target), "The static charge surrounding "+
      QTNAME(spell_target) + " fizzles then fades away.\n", spell_target);

    spell_target->remove_subloc(query_spell_effect_desc);
    spell_target->remove_prop(LIVE_S_EXTRA_SHORT);
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
	return "You covered by a complex web of sparkling white light.\n";
    }
    else
    {
	return capitalize(HE_SHE(on))+ " is covered in a complex sparkling web  "+
	"of white light.\n";
    }
}



// This shadow negates all magic resistance on a target.
int
query_magic_res(string prop)
{
    return 0;
}

int
query_mage_antimagic()
{
    return 1;
}
