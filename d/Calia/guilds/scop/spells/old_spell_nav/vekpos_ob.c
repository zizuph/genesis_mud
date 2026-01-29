/*
 * Spell effect object for the Vekpos (turn undead) spell for the
 * Spirit Circle of Psuchae.
 *
 * This object gives the target a shadow that makes them
 * run away at the sight of the caster.
 *
 */

#pragma strict_types

inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/std/object";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "defs.h"

#define FEAR_SHADOW "/d/Calia/guilds/scop/spells/fear_shadow"
#define FEARED_SHADOW "/d/Calia/guilds/scop/spells/feared_shadow"

void 
create_object()
{
    set_name("_scop_undead_turned_ob_");
    set_no_show();
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);
    add_prop(OBJ_S_WIZINFO,"This is the spell object for the Vekpos "+
        "spell of the Spirit Circle of Psuchae guild. It is a turn" +
        " undead spell, and this object sets up a shadow in both the" +
        " target and caster, so the the target flees at the sight of" +
        " the caster for the duration.\n");    

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
}

varargs public int
dispel_spell_effect(object dispeller)
{
    spell_target->catch_tell("Your fear of " + 
        spell_caster->query_the_name(spell_target) + " begins to subside.\n");
    
    spell_caster->catch_tell("You sense that " + 
        spell_target->query_the_name(spell_caster) + " is no longer under" +
        " the effect of Vekpos.\n");

    setuid();
    seteuid(getuid());
        
    spell_target->remove_shadow(FEAR_SHADOW);
    spell_caster->remove_shadow(FEARED_SHADOW);
    
    remove_spell_effect_object();
    
    return 1;

}

public int
start()
{
    int stat;
    object shadow;

    stat = spell_caster->query_stat(SS_WIS) +spell_caster->query_stat(SS_OCCUP)
        + spell_caster->query_casting_bonus();

    set_spell_effect_desc("fear");

    setuid();
    seteuid(getuid());
    
    shadow = clone_object(FEAR_SHADOW);
    shadow->shadow_me(spell_target);
    shadow = clone_object(FEARED_SHADOW);
    shadow->shadow_me(spell_caster);
    
    spell_caster->set_fear_target(spell_target);
    
    spell_target->fear_run_away(spell_caster);
    
    set_alarm(itof(stat), 0.0, &dispel_spell_effect());
    
    return 1;
}




