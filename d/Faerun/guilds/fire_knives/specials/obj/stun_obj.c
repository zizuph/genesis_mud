#pragma strict_type

inherit "/d/Genesis/specials/std/stun_obj_base";

#include "../../guild.h"
#include <macros.h>
#include <options.h>
#include <formulas.h>
#include <files.h>
#include <adverbs.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

mixed   rage_alarm;

/*
 * Function     : create_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{
    set_name("fireknives_stun");
    add_name( ({"fireknives_stun_object" }) );
    set_short("hidden fireknives stun object");    
    set_long("This is a hidden fireknives stun object.\n");
    
    set_stun_stats( TS_DEX );
    set_stun_skills( SS_DEFENCE );
    // 25% combat aid == 20% stun
    set_stun_combat_aid(90);
    // By default stun always hits 100%
    set_stun_chance(100);
    // By default stun is always triggered at 100%
    set_stun_tohit(100);
    // Cycle time of 30 seconds == 15 seconds stun, 15 seconds cooldown
    // if the aid is 100%. At 25% combat aid, this equals 5 seconds
    // of stun, and 15 seconds of cooldown.
    set_stun_cycle_time(60);
    
    setuid();
    seteuid(getuid());
}


public void
hook_stun_cooldown_in_effect(object player)
{
    player->catch_msg("You shrug off the attempts to hinder your "
                    + "movements.\n");
                    
    player->tell_watcher(QCTNAME(player) + " shrugs off the attempt "
                       + "to hinder " + player->query_possessive()
                       + " movements.\n", ({ }));
}


public void
hook_stun_ended(object player)
{
    player->catch_msg("You feel like you can almost move freely again.\n");
    player->tell_watcher(QCTNAME(player) + " seems almost to be able to move "
                       + "freely again.\n");
}


public void
hook_stun_begin(object attacker, object target)
{
    if (!objectp(target))
    {
        return;
    }
    
    if (objectp(attacker))
    {            
        target->catch_msg(QCTNAME(attacker) + " stuns you!\n");
        target->tell_watcher(QCTNAME(attacker) + " stuns " + QCTNAME(target));
    }
    else
    {
        target->catch_msg("You have been stunned!\n");
        target->tell_watcher(QCTNAME(target) + " has been stunned!\n");
    }
}