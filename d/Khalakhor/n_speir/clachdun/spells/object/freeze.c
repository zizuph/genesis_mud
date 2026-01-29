#include "../spells.h"
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

inherit "/std/shadow";
inherit SPELL_OBJECT;

//  Prototypes
varargs void dispell_spell_effect(object dispeller);

public int
start()
{
    set_spell_effect_desc("freeze object");
    if (!::start())
    {
	remove_spell_effect_object();
	return 0;
    }
    // The spell will take care of the starting messages.
    shadow_me(spell_target);
    spell_target->add_stun();
    set_alarm(45.0, 0.0, dispell_spell_effect);
    return 1;
}

string
short(object for_obj)
{
    return shadow_who->short(for_obj) + " encased in a block of ice";
}

public string
race_sound()
{
    return "mutters while "+shadow_who->query_possessive()+
    " teeth chatters";
}


int
second_life(object killer)
{
    set_alarm(0.0,0.0,remove_shadow);
    return shadow_who->second_life(killer);
}

varargs int
dispell_spell_effect(object dispeller)
{
    spell_target->remove_stun();

    spell_target->catch_tell("The ice crystals which surround you "+
      "suddenly melt away leaving you able to move again.\n");
    tell_room(environment(spell_target), "The ice crystals which "+
      "where encasing "+QTNAME(spell_target)+" suddenly melt away "+
      "leaving "+spell_target->query_objective()+" able "+
      "to move once again.\n", spell_target);

    // Damage the player from the defrosting
    spell_target->heal_hp(- random(F_PENMOD(60, 100)));
    if (spell_target->query_hp() <= 0)
	spell_target->do_die(spell_caster);
    destruct();
    return 1;
}

public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    if (how == "X")
	return shadow_who->move_living(how, to_dest, dont_follow, no_glance);

    shadow_who->catch_tell("You are unable to move while encased "+
      "in this block of ice.\n");
    return 0;
}

public int
query_clachdun_frozen()
{
    return 1;
}
