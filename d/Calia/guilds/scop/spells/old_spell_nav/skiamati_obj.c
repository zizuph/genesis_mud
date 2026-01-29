
/*
 * skiamati_obj.c
 *
 * This is the spell object for the skiamati (Shadow Eyes) spell for 
 * the Spirit Circle of Psuchae
 *
 * Copyright (C): Jaacar, July 31st, 2003
 *
 * Balance Review Done By Shiva - September 2003
 *
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
    set_name("_skiamati_object_");
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
    int gstat, wis, success;
    string desc;

    gstat = spell_caster->query_stat(SS_OCCUP);
    wis = spell_caster->query_stat(SS_WIS);
    
    set_spell_effect_desc("darkvision");    

    success = gstat + wis + spell_caster->query_casting_bonus();

    spell_target->add_prop(LIVE_I_SEE_DARK, 
        (int)spell_target->query_prop(LIVE_I_SEE_DARK) + 10);
    
    desc = "You feel that your ability to see in darkness has been greatly" +
        " improved.\n";
    
    if (success > 300)
    {
        spell_target->add_prop(LIVE_I_SEE_INVIS,
            (int)spell_target->query_prop(LIVE_I_SEE_INVIS) + 10);
        spell_target->add_prop("_skiamati_invis_too",1);
        desc = "You feel that your ability to see in darkness, as well as" +
            " to see invisible objects, has been greatly improved.\n";
    }

    set_alarm(itof(success*2), 0.0, &dispel_spell_effect(TO));

    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    spell_target->catch_tell("You feel your eyes return to normal "+
        "again.\n");
    spell_target->add_prop(LIVE_I_SEE_DARK,
        (int)spell_target->query_prop(LIVE_I_SEE_DARK) - 10);
        
    if (spell_target->query_prop("_skiamati_invis_too"))
    {
        spell_target->add_prop(LIVE_I_SEE_INVIS,
            (int)spell_target->query_prop(LIVE_I_SEE_INVIS) - 10);
        spell_target->remove_prop("_skiamati_invis_too");
    }
    
    remove_spell_effect_object();

    return 1;
}