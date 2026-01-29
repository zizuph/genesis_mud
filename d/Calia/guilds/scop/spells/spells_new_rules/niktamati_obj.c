/*
 * niktamati_obj.c
 *
 * This is the spell object for the niktamati (Night Eyes) spell for 
 * the Spirit Circle of Psuchae
 *
 * Spell Done in the late fall of 2006, Navarre.
 *
 */

#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/std/object";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "defs.h"
#include SPIRIT_HEADER


int dark_value = 0;

void 
create_object()
{
    set_name("_niktamati_object_");
    set_no_show();
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
}


public int
start()
{
    string desc;
    int gstat, wis;

    set_spell_effect_desc("darkvision");    


    gstat = spell_caster->query_stat(SS_OCCUP);
    wis = spell_caster->query_stat(SS_WIS);

    // yields 1-3 for gstat and wis = 100, and 1-5 for gstat and wis = 150
    dark_value = 1+random(1+gstat/75)+random(1+wis/75);
    spell_target->add_prop(LIVE_I_SEE_DARK, 
                           spell_target->query_prop(LIVE_I_SEE_DARK) + 
                           dark_value);
    
    desc = "You feel that your ability to see in darkness has improved.\n";
    // 30 - 41 minutes duration
    set_alarm(itof(1200+3*gstat+2*wis+random(300)),
              0.0, &dispel_spell_effect(TO));
    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    spell_target->catch_tell("You feel your eyes return to normal "+
                             "again.\n");
    spell_target->add_prop(LIVE_I_SEE_DARK,
                           spell_target->query_prop(LIVE_I_SEE_DARK) -
                           dark_value);
    remove_spell_effect_object();
    return 1;
}