#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../spells.h"

inherit SPELL_OBJECT;
inherit "/std/shadow.c";

static int     strength;

mixed 
query_prop(string propname)
{
    mixed    ret = shadow_who->query_prop(propname);

    if (propname == LIVE_I_SEE_DARK)
    {
	if (!environment(shadow_who)->query_prop(ROOM_I_INSIDE))
	    ret += strength;
	else if (shadow_who->query_company() == "Gondor")
	    ret += MAX(1, strength/2);
    }
    return ret;
}

public int
setup_spell_effect()
{
    set_spell_effect_desc("nightvision");

    if (!::setup_spell_effect())
	return 0;


    if (shadow_me(spell_target) != 1)
    {
	spell_target->catch_tell("Nightvision failed, please leave "+
	  "bug report about this.\n");
	remove_spell_effect_object();
	return 0;
    }

    strength = max(1, spell_power/20);
    set_alarm(itof(spell_power * 15), 0.0, dispel_spell_effect);
    spell_target->catch_tell("Your eyes feel strange and more perceptive.\n");
    tell_room(ENV(spell_target), QCTNAME(spell_target) + " exclaims "+
      "'Elbereth!', and "+POSSESSIVE(spell_target)+" eyes start "+
      "glowing a faint emerald-green.\n", spell_target);
    spell_target->add_subloc(query_spell_effect_desc(), this_object());
    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    spell_target->catch_tell("Your nightvision slowly fades away.\n");
    tell_room(ENV(spell_target), QCTPNAME(spell_target) + " eyes slowly "+
      "stop glowing.\n", spell_target);
    spell_target->remove_subloc(query_spell_effect_desc());
    remove_spell_effect_object();
    return 1;
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    if (subloc == "eyes" && for_obj != on)
	return "";
    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) ||
      subloc != query_spell_effect_desc())
	return shadow_who->show_subloc(subloc, on, for_obj);

    if (for_obj != on)
    {
	return capitalize(POSSESSIVE(on)) +" eyes sparkle with "+
	"a strange emerald-green glow.\n";
    }
}
