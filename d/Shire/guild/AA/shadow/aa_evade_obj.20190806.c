/*
 * Angmar Army shield functions
 * by Milan
 *
 *  7/15/2008 Novo removed got_hit to shield, they were dulling too fast.
 * 12/23/2008 Petros - Removed guild stat from the evade stat calculation.
 *                     Was removed from other abilities back in October,
 *                     but neglected to do so for evade.
 * 1/6/2009   Petros - Adding logging to evade
 * 1/13/2009  Petros - Removing logging and putting in downward modifier
 *                     based on shield ac. See query_combat_aid_modifier
 */

#pragma strict_types
#pragma save_binary

#include "../guild.h"

inherit EVADE_OBJ_BASE;

#include <filter_funs.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <formulas.h>
#include <tasks.h>
#include <comb_mag.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

#define EVADE_LOG   AA_DIR+"log/evade_log"

/*
 * Function     : create_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{    
    //Evade combat aid is overridden with query_evade_combat_aid
    //For the various scenarios
    set_evade_skills(SS_SHIELD);
    set_evade_stats(TS_DEX);
    
    setuid();
    seteuid(getuid());
    
    set_name("_aa_evade_object_");
    add_name( ({"aa_evade_obj" }) );
    set_short("hidden aa shield evade object");    
    set_long("A basic evade object. One should not be able to see it "
           + "in their inventory.\n");    
}

static object who_defend;                 /* I am helping to defend   */


public int query_aa_evade_effect()
{
    return 1;
}

public nomask void
set_defend(object who)
{
    if (who_defend && who_defend!=effect_caster)
    {
        remove_evade_effect(who_defend);
    }
    who_defend = who;  
    if (who!=effect_caster)
    {
        add_evade_effect(who);
    }
}

public nomask void
clear_defend()
{
    if (who_defend && who_defend!=effect_caster)
    {
        remove_evade_effect(who_defend);
    }
    who_defend = 0;
}

public nomask object
query_defend()
{
    return who_defend;
}


/*
 * Function: attack_blocked
 * makes messages for watchers that we covered hit with shield
 */
public void
attack_blocked(object player,object attacker,int att_id)
{
    object * shields;
    
    if (!sizeof(shields = filter(effect_caster->query_armour(-1), 
        &operator(==)(A_SHIELD) @ &->query_at())))
    {
        return;
    }
    int pos=random(sizeof(shields));
    
    string shield=shields[pos]->short(effect_caster);

    //Removed - shields were dulling too quickly.
    //shields[pos]->got_hit(0,0,attacker,0,1);

    string attack_desc="attack";
    
    object cob=attacker->query_combat_object();
    if (cob && cob->query_attack(att_id))
    {
        attack_desc = cob->cb_attack_desc(att_id);
    }
    effect_caster->catch_msg("You cover "+QTNAME(attacker)+"'s "+
        attack_desc+" with your "+shield+".\n");
    attacker->catch_msg(QCTNAME(effect_caster)+" covers your "+
        attack_desc+" with "+HIS(effect_caster)+" "+shield+".\n");
    attacker->tell_watcher(QCTNAME(effect_caster)+" covers "+QTNAME(attacker)+
        "'s "+attack_desc+" with "+HIS(effect_caster)+
        " "+shield+".\n", ({ effect_caster }));
}

/*
 * Function name: query_combat_aid_modifier
 * Description  : Calculates the percentage of the maximum
 *                combat aid that applies to the current situation
 * Arguments    : player - player executing special
 * Returns      : number between 1 and 100
 */
static int query_combat_aid_modifier(object defender)
{
    int strength, shield_modifier;
    object * shields;
    
    // Per Eowul, shields will now adjust combat aid according
    // to the following scale:
    // Evade will start out at 50% of max, and grow up to
    // 100% of max depending on shield ac from 1-40.
    strength = 50; // starting percentage of max combat aid

    if (!sizeof(shields = filter(effect_caster->query_armour(-1), 
        &operator(==)(A_SHIELD) @ &->query_at())))
    {
        // No shield present, thus reduces to minimum combat aid.
        // Technically should never happen since query_evade_valid
        // should check it.
        return 1;
    }
    
    int pos = random(sizeof(shields));

    shield_modifier = (min(40, shields[pos]->query_ac()) * 50) / 40;
    strength += shield_modifier;
    
    if (defender->query_prop(AA_PUN) == 2) 
    {
        strength/=2;
    }    
    
    send_debug_message("aa_evade", "Combat aid modifier: " + strength);    
    return strength;
}


/*
 * Function     : query_evade_combat_aid
 * Description  : returns the evade combat aid for player
 * Arguments    : player - the player who is receiving combat aid
 * Returns      : combat aid number
 */
public int
query_evade_combat_aid(object player)
{
    if (query_defend())
    {
        if (IS_LAYMAN(effect_caster))
        {
            return 45;
        }
        return 95;
    }
    if (IS_LAYMAN(effect_caster))
    {
        return 10;        
    }
    return 25;
}

public int
query_evade_valid(object player, object attacker, int attack_id)
{
    if (!IS_MEMBER(player))
    {
        return 0;
    }
    if (!effect_caster)
    {
        return 0;
    }
    if (query_defend() && query_defend()!=player)
    {
        return 0;
    }
    
    if (player->query_aa_member_killer() > 1)
    {
        return 0;
    }
    if (ENV(player)!=ENV(attacker))
    {
        return 0;
    }
    if (ENV(player)!=ENV(effect_caster))
    {
        return 0;
    }
    if (player->query_prop(AA_PUN)>2)
    {
        return 0;
    }
    if (NPATTACK(effect_caster))
    {
        return 0;
    }
    object *
    shields = filter(effect_caster->query_armour(-1),
                     &operator(==)(A_SHIELD) @ &->query_at());
    if (sizeof(shields))
    {
        return 1;
    }
    
    return 0;
}

