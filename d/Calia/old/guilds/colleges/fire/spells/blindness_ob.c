/*
  This is the spell object for the blindness spell the Fire College
  uses. 

  Coded by Bishop of Calia, July 2003.

 */

#pragma strict_types

inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/d/Calia/guilds/colleges/specials/common_functions";
inherit "/std/object";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "defs.h"

void 
create_object()
{
    set_name("_college_blindness_ob_");
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
    int stat = find_controlling_stat("fire", spell_caster);

    //Duration: 30 to 120 seconds.
    stat = min(30 + (random(stat) + random(stat))/2, 120);
   
    set_spell_effect_desc("blindness");
   
    spell_target->add_prop(LIVE_I_SEE_DARK,
        (int)spell_target->query_prop(LIVE_I_SEE_DARK) -10);   
   
    set_alarm(itof(stat), 0.0, dispel_spell_effect);

    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    spell_target->catch_tell("You gradually regain your" +
        " eyesight.\n");
    tell_room(environment(spell_target), QCTNAME(spell_target) + 
        " appears to regain " + spell_target->query_possessive() + 
        " eyesight.\n", spell_target);

    spell_target->add_prop(LIVE_I_SEE_DARK,
        (int)spell_target->query_prop(LIVE_I_SEE_DARK) + 10);    
    
    remove_spell_effect_object();

    return 1;
}