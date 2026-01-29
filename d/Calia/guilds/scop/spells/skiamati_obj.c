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
 * - November 2008, Petros, Fixed so that invis sight levels do not stack 
 *   with successive casting
 */

#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/std/object";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>

#include "defs.h"
#include SPIRIT_HEADER

// Defines
#define DURATION 600
#define SIGHT_LEVEL 10

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

public void
spell_msg()
{
    object player = spell_target;
    
    if (player->query_prop(SKIAMATI_IS_PRESENT))
    {
        player->catch_tell("Your prayers are answered and the gift of "
            + "skiamati is prolonged.\n");
        player->remove_prop(SKIAMATI_IS_PRESENT);
    }
    else
    {
        player->catch_tell("Your prayers are answered and you feel your "
            + "eyes cloud over with elemental energies, allowing you to "
            + "see that which is not visible to the naked eye.\n");
    }
    tell_room(environment(spell_target),QCTPNAME(spell_target)+" eyes flash "
        + "brightly for a brief moment.\n", ({ spell_target }));
}

public int
start()
{
    int gstat, wis, success, bonus;
    string desc;

    gstat = spell_caster->query_stat(SS_OCCUP);
    wis = spell_caster->query_stat(SS_WIS);
    set_spell_effect_desc("see_invisible");    
    success = spell_caster->resolve_task(TASK_DIFFICULT-120,
                            ({SKILL_WEIGHT, 30, SS_SPELLCRAFT,
                            SKILL_WEIGHT, 40, TS_OCC,
                            SKILL_WEIGHT, 20, TS_WIS,
                            SKILL_WEIGHT, 10, TS_INT}));

    spell_target->add_prop(LIVE_I_SEE_INVIS,
            (int)spell_target->query_prop(LIVE_I_SEE_INVIS) + SIGHT_LEVEL);
    set_alarm(0.0, 0.0, &spell_msg());
    
    if (success > 0)
    {
      bonus = 100+random(gstat);
    }
    else
    {
      bonus = 0;
    }   
    set_alarm(itof(DURATION+bonus), 0.0, &dispel_spell_effect(TO));

    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    if (!spell_target->query_prop(SKIAMATI_IS_PRESENT))
    {
        spell_target->catch_tell("Your eyes return to normal, and you no "
            + "longer perceive the immaterial.\n");            
        tell_room(environment(spell_target), QCTNAME(spell_target)+"'s eyes return to normal.\n",
            spell_target);
    }
    spell_target->add_prop(LIVE_I_SEE_INVIS,
                  (int)spell_target->query_prop(LIVE_I_SEE_INVIS) - SIGHT_LEVEL);
          
    remove_spell_effect_object();
    return 1;
}

