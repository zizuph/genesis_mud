/*
    Spell effect object for the pagos (ice weapon) spell for the Elemental
    Worshippers of Calia.

    Bishop of Calia, August 2004.
*/

#pragma strict_types

inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/std/shadow";

#include <tasks.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "defs.h"

int modifier = 3;
string adj = "cold";

int
query_pen()
{
    return shadow_who->query_pen() + modifier;
}

int
query_hit()
{
    return shadow_who->query_hit() + modifier;
}


public varargs string
short(object for_obj)
{
    return (adj + " " + shadow_who->short(for_obj));
}

public varargs string
long(string str, object for_obj)
{
    if (!str)
    {
        return (shadow_who->long(str, for_obj) + "This weapon has been" +
            " enchanted, and radiates freezing cold.\n");
    }
    else
        return shadow_who->long(str, for_obj);
}


/*
 * Function name: did_hit
 * Description:   Tells us that we hit something. Should produce combat
 *                messages to all relevant parties. If the weapon
 *                chooses not to handle combat messages then a default
 *                message is generated.
 * Arguments:     aid:   The attack id
 *                hdesc: The hitlocation description.
 *                phurt: The %hurt made on the enemy
 *                enemy: The enemy who got hit
 *                dt:    The current damagetype
 *                phit:  The %success that we made with our weapon
 *                dam:   The actual damage caused by this weapon in hit points
 *                hid:   The hitlocation id
 * Returns:       True if it handled combat messages, returning a 0 will let
 *                the normal routines take over
 */
public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
                int phit, int dam, int hid)
{
    int var = 0;
    object wielder = shadow_who->query_wielded();

    if (shadow_who->did_hit(aid, hdesc, phurt, enemy, dt, phit, dam, hid) != 0)
    {
        var = 1;
    }

    if (!random(30))
    {
        wielder->catch_msg("The freezing cold from your " + 
            short() + " stuns " +
            enemy->query_the_name(wielder) + "!\n");
        enemy->catch_msg("The freezing cold from " + 
            LANG_POSS(wielder->query_the_name(enemy)) + " " + 
            short() + " stuns you!\n");
        wielder->tell_watcher("The freezing cold from " + 
            LANG_POSS(QTNAME(wielder)) + " " + short() + " stuns "+
            QTNAME(enemy) + "!\n", ({enemy}));
        
        enemy->add_attack_delay(3 * modifier);
    }
    
    return var;
}

int
has_pagos_shadow()
{
    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    object wielder;
    
    if (wielder = shadow_who->query_wielded())
    {
        wielder->catch_msg("Your " + shadow_who->short() +
             " returns to normal as" +
            " its cold aura dissipates.\n");
        say(LANG_POSS(QCTNAME(wielder)) + " " + 
            shadow_who->short() + " returns to" +
            " normal as its cold aura dissipates.\n", wielder);
    }
    else
    if (living(wielder = environment(shadow_who)))
    {
        wielder->catch_msg("Your " + shadow_who->short() + 
            " returns to normal as" +
            " its cold aura dissipates.\n");
    }
    else
    if (environment(shadow_who)->query_prop(ROOM_I_IS))
    {
        tell_room(environment(shadow_who),"The " + shadow_who->short() + 
            " returns to normal as its cold aura" +
            " dissipates.\n");
    }


    if (shadow_who->query_prop(OBJ_M_NO_SELL) == 
        "You do not want to sell your enchanted weapon!\n")
    {
        shadow_who->remove_prop(OBJ_M_NO_SELL);
    }

    shadow_who->remove_adj(adj);
        
    remove_spell_effect_object();

    return 1;
}

int
start()
{
    int stat;

    stat = spell_caster->query_stat(SS_WIS) + 
        spell_caster->query_stat(SS_LAYMAN);

    if (!shadow_me(spell_target))
    {
        return 0;
    }

    if (stat > 150)
    {
        modifier = 4;
        adj = "icy";
    }
    if (stat > 250)
    {
        modifier = 5;
        adj = "freezing";
    }

    
    if (!shadow_who->query_prop(OBJ_M_NO_SELL))
    {
        shadow_who->add_prop(OBJ_M_NO_SELL, "You do not want to sell your" +
            " enchanted weapon!\n");
    }
    
    shadow_who->set_likely_break(shadow_who->query_likely_break() + 5);    
    
    shadow_who->add_adj(adj);
    spell_caster->update_weapon(shadow_who);
 
    set_alarm(itof(900 + 3*stat), 0.0, &dispel_spell_effect());
    
    return 1;
}

