/*
 * niktamati_obj.c
 *
 * This is the spell object for the niktamati (Night Eyes) spell for 
 * the Spirit Circle of Psuchae
 *
 * Spell Done in the late fall of 2006, Navarre.
 *
 * Oct 20th 2007, Navarre: Updated their darkness to atleast 2 levels,
 * instead of atleast 1 level.
 * Nov 16th 2008, Petros: Fixed spell so that it does not stack darkness
 *                        levels beyond what they pay for in the tax.
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


// Global variables
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

public void
spell_msg()
{
    if (spell_target->query_prop(NIKTAMATI_IS_PRESENT))
    {
        if (spell_target != spell_caster)
        {
            spell_target->catch_tell("Your vision flickers for a moment.\n");
            spell_caster->catch_msg("Your prayers are answered and the "
                + "gift of niktamati upon " + QTNAME(spell_target) + " "
                + "has been prolonged.\n");
        }
        else
        {
            spell_target->catch_tell("Your prayers are answered and the "
                + "gift of niktamati upon yourself has been prolonged.\n");
        }
        spell_target->remove_prop(NIKTAMATI_IS_PRESENT);
    }
    else
    {
        spell_target->catch_tell("Your vision flickers for a moment, and "
            + "the shadows in every corner brighten. You sense your "
            + "eyesight can pierce that of the darkness better than "
            + "before.\n");
        if (spell_target != spell_caster)
        {
            spell_caster->catch_msg("Your prayers are answered and the "
                + "gift of niktamati has been granted to " 
                + QTNAME(spell_target) + ".\n");
        }
    }
    tell_room(environment(spell_target),QCTPNAME(spell_target) 
        + " eyes flash brightly for a brief moment.\n", 
          ({ spell_caster, spell_target }));    
}


public int
start()
{
    int gstat, wis;

    set_spell_effect_desc("darkvision");    

    gstat = spell_caster->query_stat(SS_OCCUP);
    wis = spell_caster->query_stat(SS_WIS);

    // yields 1-3 for gstat and wis = 100, and 1-5 for gstat and wis = 150
    dark_value = 2+random(2+gstat/75)+random(2+wis/75);
    spell_target->add_prop(LIVE_I_SEE_DARK, 
                           spell_target->query_prop(LIVE_I_SEE_DARK) + 
                           dark_value);
    
    set_alarm(0.0, 0.0, &spell_msg());
    // 30 - 41 minutes duration
    set_alarm(itof(1200+3*gstat+2*wis+random(300)),
              0.0, &dispel_spell_effect(TO));
    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    if (!spell_target->query_prop(NIKTAMATI_IS_PRESENT))
    {
        // If the caster is renewing the effect, we don't have the
        // eyes fade to normal.
        spell_target->catch_tell("Your eyes fade to normal, and your "
            + "eyesight no longer pierces that of the darkness.\n");
    }
    spell_target->add_prop(LIVE_I_SEE_DARK,
                           spell_target->query_prop(LIVE_I_SEE_DARK) -
                           dark_value);
    remove_spell_effect_object();
    return 1;
}
