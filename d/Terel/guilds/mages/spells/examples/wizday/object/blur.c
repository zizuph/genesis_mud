#include "../spells.h"
#include "/d/Khalakhor/sys/defs.h"
#include <language.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

inherit "/std/shadow";
inherit SPELL_OBJECT;

// Global Vars
static int gPercent;

// Prototypes
varargs void dispel_spell_effect(object dispeler);

public int
setup_spell_effect()
{
    set_spell_effect_desc("air barrier");
    if (!::setup_spell_effect())
    {
	remove_spell_effect_object();
	return 0;
    }
    shadow_me(spell_target);
    gPercent = max(20, min(35, spell_caster->query_avatar_level()));
    set_alarm(itof(300 + random(180)), 0.0, dispel_spell_effect);
    spell_target->add_subloc(query_spell_effect_desc(), this_object());
    return 1;
}

public int
query_not_attack_me(object who, int aid)
{
    string what, how;

    // See if another shadow blocked the attack.
    if (shadow_who->query_not_attack_me(who, aid))
	return 1;

    if (gPercent > random(100))
    {
	if (aid == -1)
	    what = "attack";
	else
	    what = who->query_combat_object()->cb_attack_desc(aid);
	how = ONE_OF(({"shifts in order to block", "manages to interfere with",
	    "knocks aside", "collides with"}));
	shadow_who->catch_msg("Your protective barrier of air " + how +
	  " " + LANG_POSS(QTNAME(who)) + " " + what + ".\n");
	who->catch_msg("An invisible barrier of air " + how +
	  " your " + what + " proctecting "+QTNAME(shadow_who)+".\n");
	shadow_who->tell_watcher("An invisible barrier of air "+ how +
	  " "+ LANG_POSS(QTNAME(who)) + " " + what + " proctecting "+
	  QTNAME(shadow_who) + " from harm.\n", ({who, shadow_who}));
	return 1;
    }

    return 0;
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
	      "unsucessful.\n");
	    return 0;
	}
    }
    spell_target->catch_tell("The protective barrier of air "+
      "which surrounds you suddenly vanishes from sight.\n");
    tell_room(environment(spell_target), "The protective barrier "+
      "of air which surrounds "+QTNAME(spell_target)+
      " suddenly vanishes from sight.\n", spell_target);
    shadow_who->remove_subloc(query_spell_effect_desc());
    remove_spell_effect_object();
    return 1;
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) ||
      subloc != query_spell_effect_desc())
	return shadow_who->show_subloc(subloc, on, for_obj);

    return "A blurred barrier of air surrounds "+ (for_obj == on ?
      "your" : HIS_HER(on))+ " body.\n";
}
int
query_avatar_blured()
{
    return 1;
}
