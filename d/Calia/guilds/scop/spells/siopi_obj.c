/*
 * siopi_obj.c
 *
 * This is the spell object for the siopi (Silence) spell for 
 * the Spirit Circle of Psuchae
 *
 * Copyright (C): Jaacar, July 30th, 2003
 *
 * Balance Review Done By Shiva - September 2003
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

void 
create_object()
{
    set_name("_siopi_object_");
    set_no_show();
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);
    add_prop(OBJ_S_WIZINFO, "This is a spell object created by the "+
        "siopi spell of the Spirit Circle of Psuchae.\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
}


public int
start()
{
    int stat;
    
    //Duration: Maximum of 30 seconds.
    stat = 10+random(11)+random(11);
   
    set_spell_effect_desc("mute");
   
    spell_target->add_prop(LIVE_M_MOUTH_BLOCKED,
        "You have been muted by a spell, you cannot speak!\n");   
    spell_target->add_prop("_silenced_by_scop_at", time());
    set_alarm(itof(stat), 0.0, dispel_spell_effect);

    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    spell_target->catch_tell("You feel your mouth relax and "+
        "untighten again.\nYou can speak once again!\n");
    tell_room(environment(spell_target), QCTNAME(spell_target) + 
        " appears to breathe a sigh of relief.\n", spell_target);

    if (spell_target->query_prop(LIVE_M_MOUTH_BLOCKED) ==
        "You have been muted by a spell, you cannot speak!\n")
    {
        spell_target->remove_prop(LIVE_M_MOUTH_BLOCKED);
    }
    
    remove_spell_effect_object();

    return 1;
}